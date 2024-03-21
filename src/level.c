#include "level.h"
#include "assets.h"
#include "allocator.h"
#include "enemy_unit.h"
#include "player.h"

UT_icd object_icd = {sizeof(Sprite *), NULL, NULL, NULL};
UT_icd enemy_icd = {sizeof(Enemy *), NULL, NULL, NULL};

Level *level_new()
{
  Level *level = (Level *)allocate(sizeof(Level));

  utarray_new(level->objects, &object_icd);
  utarray_new(level->enemies, &enemy_icd);
  level->objects->d = 0;
  level->objects->i = 0;
  level->objects->n = 0;
  level->bulletManager = bulletManager_new();
  level->bombManager = bombManager_new();
  level->isTilesActive = true;
  level->pause = false;

  level->emitter = eventEmitter_new();
  eventEmitter_on(&level->emitter, E_LEVEL_BORDER_CONTACT, &on_level_border_contact);
  eventEmitter_on(&level->emitter, E_ENEMY_ATTACK_BULLET, &on_level_enemy_attack_bullet);

  for (uint8_t i = 0; i < sizeof(level->destroyedRocks) / (4 * sizeof(uint8_t)); ++i)
  {
    level->destroyedRocks[i][0] = 100;
  }

  return level;
}

void on_level_border_contact(LevelBorderContactEvent event)
{
  Dungeon *dungeon = &player_getInstance()->level->dungeon;
  if (dungeon->isActive)
  {
    eventEmitter_emit(&dungeon->emitter, E_LEVEL_BORDER_CONTACT, &event);
  }
}

void on_level_enemy_attack_bullet(LevelEnemyAttackBulletEvent *event)
{
  BulletManager *bm = &event->enemy->level->bulletManager;
  Vec2 startPosition = event->enemy->sprite->position;
  UnitMetaData unitMetaData = event->enemy->metaData;

  BulletMetaData bulletMetaData = {
      .startPosition = startPosition,
      .speed = unitMetaData.bulletSpeed,
      .lifetime = unitMetaData.bulletLifetime,
      .senderType = BulletSenderType_Enemy,
      .owner = event->enemy->sprite
  };

  bulletManager_createBullet(bm, bulletMetaData);
}

void level_clear(Level *level)
{
  Enemy **currentEnemy = NULL;
DELETE_ENEMY:
  currentEnemy = NULL;
  while ((currentEnemy = (Enemy **)utarray_next(level->enemies, currentEnemy)))
  {
    level_deleteEnemy(level, *currentEnemy);
    goto DELETE_ENEMY;
  }

  Sprite **currentObject = NULL;
DELETE_OBJECT:
  currentObject = NULL;
  while ((currentObject = (Sprite **)utarray_next(level->objects, currentObject)))
  {
    level_deleteObject(level, *currentObject);
    goto DELETE_OBJECT;
  }

  level->bombManager = bombManager_new();

  utarray_clear(level->objects);
  utarray_clear(level->enemies);

  level->imagePool = NULL;
  level->levelChunk = NULL;
}

Sprite *level_spawnObject(Level *level)
{
  Sprite *sprite = sprite_new(NULL);
  utarray_push_back(level->objects, &sprite);
  return sprite;
}

Enemy *level_spawnEnemy(Level *level)
{
  Enemy *newEnemy = new_enemy(level);
  utarray_push_back(level->enemies, &newEnemy);
  return newEnemy;
}

struct EnemyUnit level_spawnUnit(Level *level, EnemyTypeName type, NavRoot *navRoot)
{
  Enemy *enemy = level_spawnEnemy(level);
  enemy->navRoot = navRoot;

  EnemyUnitNewArgs args = {
      .level = level,
      .enemy = enemy,
      .type = type};

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

  if (level->isTilesActive)
    tiledLevelChunk_draw(level->levelChunk, level->imagePool);

  Sprite **currentObject = NULL;
  while ((currentObject = (Sprite **)utarray_next(level->objects, currentObject)))
  {
    if (*currentObject == NULL)
      continue;
    sprite_draw(*currentObject);
    if ((*currentObject)->imageCount == 0 && (*currentObject)->size.x > 16)
    {
      // trace("a");
    }
  }
  bulletManager_draw(&level->bulletManager);
}

Enemy *level_findNearestEnemy(Level *level, Vec2 position)
{
  uint32_t i = 0;

  float minDistance = (float)INT32_MAX;
  Enemy *result;
  Enemy **currentObject = NULL;

  while ((currentObject = (Enemy **)utarray_next(level->enemies, currentObject)))
  {
    Vec2 enemyPosition = (*currentObject)->sprite->position;
    Vec2 dir = vec2_fromPoints(position, enemyPosition);
    float distance = vec2_getLength(dir);
    if (distance < minDistance)
    {
      result = (Enemy *)*currentObject;
      minDistance = distance;
    }
    ++i;
  }

  return result;
}

Sprite *level_findNearestTile(Level *level, Vec2 position)
{
  uint32_t i = 0;

  float minDistance = (float)INT32_MAX;
  Sprite *result;
  Sprite **currentObject = NULL;

  while ((currentObject = (Sprite **)utarray_next(level->objects, currentObject)))
  {
    if (!(*currentObject)->isTile)
      continue;
    Vec2 tilePosition = (*currentObject)->position;

    Vec2 dir = vec2_fromPoints(position, tilePosition);
    float distance = vec2_getLength(dir);
    if (distance < minDistance)
    {
      result = (Sprite *)*currentObject;
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

void on_dungeon_enter(BoundingVolumeCollidedEvent event)
{
  if (event.bv1->tag == BoundingVolumeTag_Player || event.bv2->tag == BoundingVolumeTag_Player)
  {
    LoadDungeonArgs args = {};
    level_loadDungeon(&args);
  }
}

void level_loadDungeon(LoadDungeonArgs *args)
{
  args;
  Level *l = player_getInstance()->level;
  Vec2f lastPosition = vec2f_fromVec2(player_getInstance()->sprite->position);
  l->dungeon = dungeon_new(lastPosition);
  l->isTilesActive = false;
  dungeon_enter(&l->dungeon);
}

void level_spawnCollisionByTiles(Level *level)
{
  bool collisionMap[8][8] = {0};

  for (int i = 0; i < 64; ++i)
  {
    uint8_t tileCollision = level->levelChunk->tiles[i].collision;

    if (tileCollision)
    {
      uint8_t collisionDirs = 0;
      collisionDirs += (i + 1 < 64 && (i % 8 != 1) && level->levelChunk->tiles[i + 1].collision);
      collisionDirs += (i - 1 >= 0 && (i % 8 != 0) && level->levelChunk->tiles[i - 1].collision);
      collisionDirs += (i + 8 < 64 && level->levelChunk->tiles[i + 8].collision);
      collisionDirs += (i - 8 >= 0 && level->levelChunk->tiles[i - 8].collision);

      int edges = 0;
      edges += (i % 8 == 0);
      if (i > 8 && i <= 55)
      {
        edges += (i % 8 == 1);
      }
      edges += (i <= 7) || (i > 55);

      if (4 - edges <= collisionDirs)
        continue;

      collisionMap[i / 8][i - i / 8 * 8] = true;
    }
  }

  Sprite *newCollisionBox = NULL;

  for (int i = 0; i < 8; ++i)
  {
    if (newCollisionBox)
    {
      sprite_initBoundingVolume(newCollisionBox, BOX, BoundingVolumeTag_Tile);
      newCollisionBox->boundingVolume.emitter = (const struct EventEmitter){0};
      newCollisionBox->boundingVolume.isEmitterExist = false;

      if (level->levelChunk->tiles[i].id == 4)
      {
        newCollisionBox->boundingVolume.isEmitterExist = true;
        newCollisionBox->boundingVolume.emitter = eventEmitter_new();

        eventEmitter_on(&newCollisionBox->boundingVolume.emitter, E_BOUNDING_VOLUME_COLLIDED, on_dungeon_enter);
      }
      newCollisionBox = NULL;
    }
    for (int j = 0; j < 8; ++j)
    {
      if (collisionMap[i][j])
      {
        if (newCollisionBox == NULL)
        {
          newCollisionBox = level_spawnObject(level);
          newCollisionBox->size = vec2_new(16, 16);

          newCollisionBox->position.y = i * 16 + 24;
          newCollisionBox->position.x = j * 16 + 24;
          newCollisionBox->currentImage = NULL;
          newCollisionBox->animDelay = 0;
          newCollisionBox->images = NULL;
          newCollisionBox->imageCount = 0;
          newCollisionBox->health = NULL;
          newCollisionBox->isTile = true;
        }
        else
        {
          newCollisionBox->size.x += 16;
          newCollisionBox->position.x += 8;
        }
      }
      else
      {
        if (newCollisionBox)
        {
          sprite_initBoundingVolume(newCollisionBox, BOX, BoundingVolumeTag_Tile);
          newCollisionBox->boundingVolume.emitter = (const struct EventEmitter){0};
          newCollisionBox->boundingVolume.isEmitterExist = false;

          if (level->levelChunk->tiles[i].id == 4)
          {
            newCollisionBox->boundingVolume.isEmitterExist = true;
            newCollisionBox->boundingVolume.emitter = eventEmitter_new();

            eventEmitter_on(&newCollisionBox->boundingVolume.emitter, E_BOUNDING_VOLUME_COLLIDED, on_dungeon_enter);
          }

          newCollisionBox = NULL;
        }
      }
    }
  }

  if (newCollisionBox)
  {
    sprite_initBoundingVolume(newCollisionBox, BOX, BoundingVolumeTag_Tile);
    newCollisionBox->boundingVolume.emitter = (const struct EventEmitter){0};
    newCollisionBox->boundingVolume.isEmitterExist = false;
  }
}

void level_deleteObject(Level *level, Sprite *object)
{
  uint32_t i = 0;
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
  uint32_t i = 0;
  Enemy **currentObject = NULL;
  while ((currentObject = (Enemy **)utarray_next(level->enemies, currentObject)))
  {

    if (*currentObject == enemy)
    {
      level_deleteObject(level, enemy->sprite);
      alloc_free(enemy);
      utarray_erase(level->enemies, i, 1);
      break;
    }
    ++i;
  }
}

void level_update(Level *level)
{
  if (level->pause)
  {
    return;
  }

  Enemy **currentEnemy = NULL;
  while ((currentEnemy = (Enemy **)utarray_next(level->enemies, currentEnemy)))
  {
    enemy_update(*currentEnemy);
  }
  bulletManager_update(&level->bulletManager);
  bombManager_update(level, &level->bombManager);
}

bool level_isDone(Level *level)
{
  Enemy **currentObject = NULL;
  while ((currentObject = (Enemy **)utarray_next(level->enemies, currentObject)))
  {
    if ((*currentObject)->metaData.name != EnemyTypeName_Rock)
      return false;
  }

  level->clearedArea[level->levelChunk->x][level->levelChunk->y] = true;

  return true;
}

bool level_processChunkMoving(LoadLevelArgs *args, Player *player)
{
  if (!level_isDone(args->level))
    return false;

  if (player->sprite->position.x <= 24)
  {
    LevelBorderContactEvent event = {
        .direction = 2};

    level_moveAndLoadLevel(args, ChunkMovingDirection_Left);
    eventEmitter_emit(&args->level->emitter, E_LEVEL_BORDER_CONTACT, &event);
    return true;
  }

  if (player->sprite->position.x >= 136)
  {
    LevelBorderContactEvent event = {
        .direction = 0};

    level_moveAndLoadLevel(args, ChunkMovingDirection_Right);
    eventEmitter_emit(&args->level->emitter, E_LEVEL_BORDER_CONTACT, &event);
    return true;
  }

  if (player->sprite->position.y <= 24)
  {
    LevelBorderContactEvent event = {
        .direction = 1};

    level_moveAndLoadLevel(args, ChunkMovingDirection_Up);
    eventEmitter_emit(&args->level->emitter, E_LEVEL_BORDER_CONTACT, &event);
    return true;
  }

  if (player->sprite->position.y >= 136)
  {
    LevelBorderContactEvent event = {
        .direction = 3};

    level_moveAndLoadLevel(args, ChunkMovingDirection_Bottom);
    eventEmitter_emit(&args->level->emitter, E_LEVEL_BORDER_CONTACT, &event);
    return true;
  }
  return false;
}

void level_spawnEnemies(Level *level)
{
  
  level_spawnRocks(level);
  
  if(level->clearedArea[level->levelChunk->x][level->levelChunk->y])
    return;

  uint32_t enemyCount = level->navRootCount;

  for (uint32_t i = 0; i < enemyCount; i++)
  {
    EnemyUnit newEnemy = level_spawnUnit(level, level->navRoots[i].entityId, &level->navRoots[i]);

    newEnemy.enemy->sprite->position.x = level->navRoots[i].navPointArray[0].x;
    newEnemy.enemy->sprite->position.y = level->navRoots[i].navPointArray[0].y;

    if(newEnemy.enemy->navRoot->navPointArraySize == 1)
    {
      newEnemy.enemy->navRoot = NULL;
    }

  }
}

void level_spawnRocks(Level *level)
{
  for (unsigned long i = 0; i < sizeof(ROCK_LEVEL) / (sizeof(uint8_t) * 4); ++i)
  {
    if (level->levelChunk->x == ROCK_LEVEL[i][0] && level->levelChunk->y == ROCK_LEVEL[i][1])
    {

      bool destroyed = false;

      for (unsigned long j = 0; j < sizeof(level->destroyedRocks) / (sizeof(uint8_t) * 4); ++j)
      {
        if (level->destroyedRocks[j][0] == level->levelChunk->x && level->destroyedRocks[j][1] == level->levelChunk->y && level->destroyedRocks[j][2] == ROCK_LEVEL[i][2] && level->destroyedRocks[j][3] == ROCK_LEVEL[i][3])
        {
          destroyed = true;
        }
      }

      if (destroyed)
      {
        continue;
      }

      EnemyUnit newEnemy = level_spawnUnit(level, EnemyTypeName_Rock, NULL);

      newEnemy.enemy->sprite->position.x = 24 + 16 * ROCK_LEVEL[i][2];
      newEnemy.enemy->sprite->position.y = 24 + 16 * ROCK_LEVEL[i][3];
    }
  }
}

void level_loadNavRoots(Level *level)
{
  level->navRootCount = 0;

  for (uint8_t i = 0; i < 32; ++i)
  {
    if (LEVEL_PATH[i][0] == level->levelChunk->x && LEVEL_PATH[i][1] == level->levelChunk->y)
    {
      struct NavRoot *currentRoot = &level->navRoots[level->navRootCount];

      currentRoot->navPointArraySize = 0;
      currentRoot->currentPointIndex = 0;
      currentRoot->entityId = LEVEL_PATH[i][2];

      for (uint8_t j = 0; j < 8; ++j)
      {
        currentRoot->navPointArray[j].x = 24 + LEVEL_PATH[i][3 + j * 2] * 16;
        currentRoot->navPointArray[j].y = 24 + LEVEL_PATH[i][3 + j * 2 + 1] * 16;

        if (LEVEL_PATH[i][3 + j * 2] == 101 && currentRoot->navPointArraySize == 0)
        {
          currentRoot->navPointArraySize = j;
        }
      }

      if (currentRoot->navPointArraySize == 0)
      {
        currentRoot->navPointArraySize = 8;
      }

      ++level->navRootCount;
    }
  }
}

void level_loadLevel(LoadLevelArgs *args, ChunkMovingDirection to)
{
  Level *level = args->level;

  level_clear(level);
  level_setImagePool(level, args->imagePool);
  level_setChunk(level, args->newChunkPosition, args->newChunk);
  level_loadNavRoots(level);
  level_spawnEnemies(level);

  Vec2 startPosition;
  switch (to)
  {
  case ChunkMovingDirection_Right:
    startPosition = vec2_new(30, 80);
    break;
  case ChunkMovingDirection_Up:
    startPosition = vec2_new(80, 130);
    break;
  case ChunkMovingDirection_Left:
    startPosition = vec2_new(130, 80);
    break;
  case ChunkMovingDirection_Bottom:
    startPosition = vec2_new(80, 32);
    break;
  default:
    startPosition = vec2_new(0, 0);
    break;
  }

  struct PlayerLevelChunkMovedEvent event = {
      .level = args->level,
      .startPosition = startPosition};

  eventEmitter_emit(&player_getInstance()->emitter, E_LEVEL_CHUNK_MOVED, (void *)&event);
}

void level_moveAndLoadLevel(LoadLevelArgs *args, ChunkMovingDirection to)
{
  int32_t chunkX = (int32_t)args->level->levelChunk->x;
  int32_t chunkY = (int32_t)args->level->levelChunk->y;

  Vec2 from = vec2_new(chunkX, chunkY);
  Vec2 addingTo = level_directionAsStartPosition(to);
  Vec2 newMovingPosition = vec2_add(from, addingTo);

  bool isDungeonActive = args->level->dungeon.isActive;
  bool isWorldBorderContact = newMovingPosition.x > 15 || newMovingPosition.y > 15 || newMovingPosition.x < 0 || newMovingPosition.y < 0;

  if (isWorldBorderContact || isDungeonActive)
  {
    return;
  }
  args->newChunkPosition = newMovingPosition;

  level_loadLevel(args, to);
}

Vec2 level_directionAsStartPosition(ChunkMovingDirection direction)
{
  switch (direction)
  {
  case ChunkMovingDirection_Right:
    return vec2_new(1, 0);
  case ChunkMovingDirection_Up:
    return vec2_new(0, 1);
  case ChunkMovingDirection_Left:
    return vec2_new(-1, 0);
  case ChunkMovingDirection_Bottom:
    return vec2_new(0, -1);
  default:
    return vec2_new(0, 0);
  }
}

void level_addDestroyedRock(Level *level, Vec2 pos)
{
  for (uint8_t i = 0; i < sizeof(level->destroyedRocks) / (4 * sizeof(uint8_t)); ++i)
  {
    if (level->destroyedRocks[i][0] == 100)
    {
      level->destroyedRocks[i][0] = level->levelChunk->x;
      level->destroyedRocks[i][1] = level->levelChunk->y;
      level->destroyedRocks[i][2] = (pos.x - 24) / 16;
      level->destroyedRocks[i][3] = (pos.y - 24) / 16;

      break;
    }
  }
}