#include "libs.h"
#include "enemy.h"
#include "enemy_type_1.h"

UT_icd object_icd = {sizeof(Sprite *), NULL, NULL, NULL};
UT_icd enemy_icd = {sizeof(Enemy *), NULL, NULL, NULL};

Level *level_new()
{
  Level *newLevel = (Level *)malloc(sizeof(Level));
  level_clear(newLevel);
  return newLevel;
}

void level_clear(Level* level) {
  utarray_new(level->objects, &object_icd);
  utarray_reserve(level->objects, 100);
  utarray_new(level->enemies, &enemy_icd);
  utarray_reserve(level->enemies, 20);
  level->objects->d = 0;
  level->objects->i = 0;
  level->objects->n = 0;

  level->imagePool = NULL;
  level->levelChunk = NULL;
}

void level_delete(Level *level)
{
  Sprite **currentObject = NULL;
  while ((currentObject = (Sprite **)utarray_next(level->objects, currentObject)))
    sprite_delete(*currentObject);

  utarray_free(level->objects);
  utarray_free(level->enemies);

  free(level);
}

Sprite *level_spawnObject(Level *level)
{
  Sprite *newObject = (Sprite *)malloc(sizeof(Sprite));
  newObject->animDelay = 0;
  newObject->currentImage = NULL;
  newObject->currentImageIndex = 0;
  newObject->isCollisionBox = false;
  newObject->flipH = 0;
  newObject->frameCounter = 0;
  newObject->health = NULL;
  newObject->imageCount = 0;
  newObject->images = NULL;
  utarray_push_back(level->objects, &newObject);
  return newObject;
}

Enemy *level_spawnEnemy(Level *level)
{
  Enemy *newEnemy = new_enemy(level);
  utarray_push_back(level->enemies, &newEnemy);
  return newEnemy;
}

struct EnemyType_1 level_spawnEnemyType_1(Level *level)
{
  Enemy* enemy = level_spawnEnemy(level);
  EnemyType_1 enemyType1 = EnemyType_1_new(enemy, level);
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

  tiledLevelChunk_draw(level->levelChunk, level->imagePool);

  Sprite **currentObject = NULL;
  while ((currentObject = (Sprite **)utarray_next(level->objects, currentObject))) {
      sprite_Draw(*currentObject);
      if ((*currentObject)->imageCount == 0 && (*currentObject)->size.x > 16) {
          trace ("a");
      }
  }
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

void level_spawnCollisionByTiles(Level *level)
{
  for (int i = 0; i < 64; ++i)
  {
    if (level->levelChunk->tiles[i].id == 0 ||
        level->levelChunk->tiles[i].id == 1 ||
        level->levelChunk->tiles[i].id == 4 ||
        level->levelChunk->tiles[i].id == 5)
    {
      Sprite *newCollisionBox = level_spawnObject(level);
      newCollisionBox->size = vec2_new(16, 16);
      newCollisionBox->position.y = i / 8 * 16 + level->levelChunk->y + 24;
      newCollisionBox->position.x = i % 8 * 16 + level->levelChunk->x + 24;
      newCollisionBox->currentImage = NULL;
      newCollisionBox->animDelay = 0;
      newCollisionBox->images = NULL;
      newCollisionBox->imageCount = 0;
      newCollisionBox->health = NULL;
      newCollisionBox->isCollisionBox = true;


      sprite_initBoundingVolume(newCollisionBox, BOX);
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
  Enemy **currentEnemy = NULL;
  while ((currentEnemy = (Enemy **)utarray_next(level->enemies, currentEnemy)))
    enemy_update(*currentEnemy);
}

bool level_isDone(Level *level)
{
  return utarray_len(level->enemies) == 0;
}

bool level_processChunkMoving(LoadLevelArgs* args, Player* player) {
  if (player->sprite->position.x <= 24)
    {
      level_moveAndLoadLevel(args,ChunkMovingDirection_Left);
      return true;
    }

  if (player->sprite->position.x >= 136)
    {
      level_moveAndLoadLevel(args, ChunkMovingDirection_Right);
      return true;
    }

  if (player->sprite->position.y <= 24)
    {
      level_moveAndLoadLevel(args,ChunkMovingDirection_Up);
      return true;
    }

  if (player->sprite->position.y >= 136)
    {
      level_moveAndLoadLevel(args,ChunkMovingDirection_Bottom);
      return true;
    }
  return false;
}

void level_spawnEnemies(Level *level)
{
  uint_32 enemyCount = RANDOMIZE(1, 1);

  for (uint_32 i = 0; i < enemyCount; i++)
  {
    EnemyType_1 newEnemy = level_spawnEnemyType_1(level);

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
  level_delete (args->level);

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
  if (!level_isDone(args->level)) return;
  int_32 chunkX = (int_32) args->level->levelChunk->x;
  int_32 chunkY = (int_32) args->level->levelChunk->y;

  Vec2 from = vec2_new (chunkX, chunkY);
  Vec2 addingTo = level_directionAsStartPosition(to);
  Vec2 newMovingPosition = vec2_add (from, addingTo);

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