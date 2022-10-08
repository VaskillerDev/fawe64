#include "libs.h"
#include "enemy.h"
#include "enemy_unit.h"

UT_icd object_icd = {sizeof(Sprite *), NULL, NULL, NULL};
UT_icd enemy_icd = {sizeof(Enemy *), NULL, NULL, NULL};

Level *level_new()
{
  Level *level = (Level *)malloc(sizeof(Level));

  utarray_new(level->objects, &object_icd);
  utarray_reserve(level->objects, 100);
  utarray_new(level->enemies, &enemy_icd);
  utarray_reserve(level->enemies, 20);
  level->objects->d = 0;
  level->objects->i = 0;
  level->objects->n = 0;
  level->bulletManager = bulletManager_new();
  level->isTilesActive = true;

  level->emitter = eventEmitter_new();
  eventEmitter_on (&level->emitter, E_LEVEL_BORDER_CONTACT, &on_level_border_contact);
  eventEmitter_on (&level->emitter, E_ENEMY_ATTACK_BULLET, &on_level_enemy_attack_bullet);
  
  return level;
}

void on_level_border_contact(LevelBorderContactEvent event) {
  Dungeon* dungeon = &player_getInstance ()->level->dungeon;
  if (dungeon->isActive) {
      eventEmitter_emit (&dungeon->emitter, E_LEVEL_BORDER_CONTACT, &event);
  }
}

void on_level_enemy_attack_bullet(LevelEnemyAttackBulletEvent* event) {
  BulletManager* bm = &event->enemy->level->bulletManager;
  Vec2 startPosition = event->enemy->sprite->position;
  UnitMetaData unitMetaData = event->enemy->metaData;

  BulletMetaData bulletMetaData = {
      .startPosition = startPosition,
      .speed = unitMetaData.bulletSpeed,
      .lifetime = unitMetaData.bulletLifetime,
      .senderType = BulletSenderType_Enemy,
  };

  bulletManager_createBullet (bm, bulletMetaData);
}

void level_clear(Level* level) {
  Sprite **currentObject = NULL;
  while ((currentObject = (Sprite **)utarray_next(level->objects, currentObject)))
    sprite_delete(*currentObject);

  utarray_clear(level->objects);
  utarray_clear(level->enemies);

  level->imagePool = NULL;
  level->levelChunk = NULL;
}

Sprite *level_spawnObject(Level *level)
{
  Sprite *sprite = sprite_new (NULL);
  utarray_push_back(level->objects, &sprite);
  return sprite;
}

Enemy *level_spawnEnemy(Level *level)
{
  Enemy *newEnemy = new_enemy(level);
  utarray_push_back(level->enemies, &newEnemy);
  return newEnemy;
}

struct EnemyUnit level_spawnUnit(Level *level, EnemyTypeName type)
{
  Enemy* enemy = level_spawnEnemy(level);

  EnemyUnitNewArgs args = {
      .level = level,
      .enemy = enemy,
      .type = type
  };

  EnemyUnit enemyType1 = enemyUnit_new(args);
  return enemyType1;
}

void level_draw(Level *level)
{
  if (level->imagePool == NULL)
  {
    trace("imagePool not found!");
    return;
  }

  if (level->levelChunk == NULL)
  {
    trace("levelChunk not found!");
    return;
  }

  if (level->isTilesActive) tiledLevelChunk_draw(level->levelChunk, level->imagePool);

  Sprite **currentObject = NULL;
  while ((currentObject = (Sprite **)utarray_next(level->objects, currentObject))) {
      if (*currentObject == NULL) continue;
      sprite_draw (*currentObject);
      if ((*currentObject)->imageCount == 0 && (*currentObject)->size.x > 16) {
          trace ("a");
      }
  }
  bulletManager_draw(&level->bulletManager);
}

Enemy* level_findNearestEnemy(Level* level, Vec2 position) {
  uint_32 i = 0;

  float minDistance = (float)INT32_MAX;
  Enemy* result;
  Enemy **currentObject = NULL;

  while ((currentObject = (Enemy **)utarray_next(level->enemies, currentObject)))
  {
      Vec2 enemyPosition = (*currentObject)->sprite->position;
      Vec2 dir = vec2_fromPoints(position,enemyPosition);
      float distance = vec2_getLength(dir);
      if (distance < minDistance) {
        result = (Enemy *) *currentObject;
        minDistance = distance;
      }
      ++i;
  }

  return result;
}

Sprite* level_findNearestTile(Level* level, Vec2 position) {
  uint_32 i = 0;

  float minDistance = (float)INT32_MAX;
  Sprite* result;
  Sprite **currentObject = NULL;

  while ((currentObject = (Sprite **)utarray_next(level->objects, currentObject)))
    {
      if (!(*currentObject)->isTile) continue;
      Vec2 tilePosition = (*currentObject)->position;

      Vec2 dir = vec2_fromPoints(position,tilePosition);
      float distance = vec2_getLength(dir);
      if (distance < minDistance) {
          result = (Sprite *) *currentObject;
          minDistance = distance;
        }
      ++i;
    }

  return result;
}

void level_setChunk(Level *level, Vec2 chunkCoords, TiledLevelChunk *levelChunk)
{
  tiledLevelChunk_read(levelChunk, chunkCoords.x, chunkCoords.y);
  level->levelChunk = levelChunk;
  level_spawnCollisionByTiles(level);
}

void level_setImagePool(Level *level, ImagePool *pool)
{
  level->imagePool = pool;
}

void on_dungeon_enter(BoundingVolumeCollidedEvent event) {
  if (event.bv1->tag == BoundingVolumeTag_Player || event.bv2->tag == BoundingVolumeTag_Player) {
      LoadDungeonArgs args = {};
      level_loadDungeon (&args);
  }
}

void level_loadDungeon(LoadDungeonArgs* args) {
  args;
  Level* l = player_getInstance()->level;
  Vec2f lastPosition = vec2f_fromVec2 (player_getInstance()->sprite->position);
  l->dungeon = dungeon_new (lastPosition);
  l->isTilesActive = false;
  dungeon_enter(&l->dungeon);
}

void level_spawnCollisionByTiles(Level *level)
{
  for (int i = 0; i < 64; ++i)
  {
    uint_8 id = level->levelChunk->tiles[i].id;

    Sprite *newCollisionBox = NULL;

    if (id == 0 ||
        id == 1 ||
        id == 4 ||
        id == 5)
    {
      newCollisionBox = level_spawnObject(level);
      newCollisionBox->size = vec2_new(16, 16);
      newCollisionBox->position.y = i / 8 * 16 + level->levelChunk->y + 24;
      newCollisionBox->position.x = i % 8 * 16 + level->levelChunk->x + 24;
      newCollisionBox->currentImage = NULL;
      newCollisionBox->animDelay = 0;
      newCollisionBox->images = NULL;
      newCollisionBox->imageCount = 0;
      newCollisionBox->health = NULL;
      newCollisionBox->isTile = true;

      sprite_initBoundingVolume(newCollisionBox, BOX, BoundingVolumeTag_Tile);
      newCollisionBox->boundingVolume.emitter = (const struct EventEmitter){0};
      newCollisionBox->boundingVolume.isEmitterExist = false;
    }

    if ( id == 4) {
        newCollisionBox->boundingVolume.isEmitterExist = true;
        newCollisionBox->boundingVolume.emitter = eventEmitter_new();

        eventEmitter_on(&newCollisionBox->boundingVolume.emitter, E_BOUNDING_VOLUME_COLLIDED, on_dungeon_enter);
    }
  }
}

void level_deleteObject(Level *level, Sprite *object)
{
  uint_32 i = 0;
  Sprite **currentObject = NULL;
  while ((currentObject = (Sprite **)utarray_next(level->objects, currentObject)))
  {

    if (*currentObject == object)
    {
      utarray_erase(level->objects, i, 1);
      sprite_delete(object);
      break;
    }
    ++i;
  }
}

void level_deleteEnemy(Level *level, struct Enemy *enemy)
{
  uint_32 i = 0;
  Enemy **currentObject = NULL;
  while ((currentObject = (Enemy **)utarray_next(level->enemies, currentObject)))
  {

    if (*currentObject == enemy)
    {
      utarray_erase(level->enemies, i, 1);
      free(enemy);
      level_deleteObject(level, enemy->sprite);
      break;
    }
    ++i;
  }
}

void level_update(Level *level)
{
  if (level->pause)
  {
    Enemy **currentEnemy = NULL;
    while ((currentEnemy = (Enemy **)utarray_next(level->enemies, currentEnemy)))
    {
      enemy_update(*currentEnemy);
    }
    bulletManager_update(&level->bulletManager);
  }
}

bool level_isDone(Level *level)
{
  return utarray_len(level->enemies) == 0;
}

bool level_processChunkMoving(LoadLevelArgs* args, Player* player) {
  if (!level_isDone(args->level)) return false;
  if (player->sprite->position.x <= 24)
    {
      LevelBorderContactEvent event = {
          .direction = 2
      };


      level_moveAndLoadLevel(args,ChunkMovingDirection_Left);
      eventEmitter_emit(&args->level->emitter, E_LEVEL_BORDER_CONTACT, &event);
      return true;
    }

  if (player->sprite->position.x >= 136)
    {
      LevelBorderContactEvent event = {
          .direction = 0
      };

      level_moveAndLoadLevel(args, ChunkMovingDirection_Right);
      eventEmitter_emit(&args->level->emitter, E_LEVEL_BORDER_CONTACT, &event);
      return true;
    }

  if (player->sprite->position.y <= 24)
    {
      LevelBorderContactEvent event = {
          .direction = 1
      };

      level_moveAndLoadLevel(args,ChunkMovingDirection_Up);
      eventEmitter_emit(&args->level->emitter, E_LEVEL_BORDER_CONTACT, &event);
      return true;
    }

  if (player->sprite->position.y >= 136)
    {
      LevelBorderContactEvent event = {
          .direction = 3
      };

      level_moveAndLoadLevel(args,ChunkMovingDirection_Bottom);
      eventEmitter_emit (&args->level->emitter, E_LEVEL_BORDER_CONTACT, &event);
      return true;
    }
  return false;
}

void level_spawnEnemies(Level *level)
{
  uint_32 enemyCount = RANDOMIZE(1, 1);

  for (uint_32 i = 0; i < enemyCount; i++)
  {
    EnemyUnit newEnemy = level_spawnUnit (level, EnemyTypeName_Rock);

    newEnemy.enemy->sprite->position.x = RANDOMIZE(30, 60);
    newEnemy.enemy->sprite->position.y = RANDOMIZE(30, 130);
    uint_32 tryCount = 0;
    while (tryCount < 10 && (player_checkCollision(newEnemy.enemy->sprite, level, vec2_new(1, 0)) ||
           player_checkCollision(newEnemy.enemy->sprite, level, vec2_new(-1, 0)) ||
           player_checkCollision(newEnemy.enemy->sprite, level, vec2_new(0, 1)) ||
           player_checkCollision(newEnemy.enemy->sprite, level, vec2_new(0, -1))))
    {
      newEnemy.enemy->sprite->position.x = RANDOMIZE(25, 135);
      newEnemy.enemy->sprite->position.y = RANDOMIZE(25, 135);
      tryCount++;
    }

    if (tryCount >= 9)
    {
      HpPointsOverEvent e;
      e.parent = newEnemy.enemy;
      enemy_death(e);
    }
  }
}



void level_loadLevel(LoadLevelArgs* args, ChunkMovingDirection to) {

  level_clear (args->level);
  level_setImagePool (args->level, args->imagePool);
  level_setChunk (args->level, args->newChunkPosition, args->newChunk);
  level_spawnEnemies (args->level);

  Vec2 startPosition;
  switch (to) {
    case ChunkMovingDirection_Right: startPosition = vec2_new (144,64); break;
    case ChunkMovingDirection_Up: startPosition = vec2_new (64, 144); break;
    case ChunkMovingDirection_Left: startPosition = vec2_new (16, 64); break;
    case ChunkMovingDirection_Bottom: startPosition = vec2_new (64,16); break;
    default: startPosition = vec2_new (0,0); break;
  }

  struct PlayerLevelChunkMovedEvent event = {
      .level = args->level,
      .startPosition = startPosition
  };

  eventEmitter_emit (&player_getInstance()->emitter, E_LEVEL_CHUNK_MOVED, (void*) &event);
}

void level_moveAndLoadLevel(LoadLevelArgs* args, ChunkMovingDirection to) {
  int_32 chunkX = (int_32) args->level->levelChunk->x;
  int_32 chunkY = (int_32) args->level->levelChunk->y;

  Vec2 from = vec2_new (chunkX, chunkY);
  Vec2 addingTo = level_directionAsStartPosition(to);
  Vec2 newMovingPosition = vec2_add (from, addingTo);

  bool isDungeonActive = args->level->dungeon.isActive;
  bool isWorldBorderContact = newMovingPosition.x > 15
      || newMovingPosition.y > 15
      || newMovingPosition.x < 0
      || newMovingPosition.y < 0;

  if (isWorldBorderContact || isDungeonActive) {
      return;
  }
  args->newChunkPosition = newMovingPosition;
  level_loadLevel(args, to);
}

Vec2 level_directionAsStartPosition(ChunkMovingDirection direction) {
  switch(direction) {
      case ChunkMovingDirection_Right: return vec2_new (1,0);
      case ChunkMovingDirection_Up: return vec2_new (0,1);
      case ChunkMovingDirection_Left: return vec2_new (-1,0);
      case ChunkMovingDirection_Bottom: return vec2_new (0,-1);
      default:return vec2_new (0,0);
  }
}