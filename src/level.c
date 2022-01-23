#include "libs.h"
#include "enemy.h"
#include "enemy_type_1.h"

UT_icd object_icd = {sizeof(Sprite *), NULL, NULL, NULL};
UT_icd enemy_icd = {sizeof(Enemy *), NULL, NULL, NULL};

Level *level_new()
{
  Level *newLevel = (Level *)malloc(sizeof(Level));
  newLevel->levelName = "test";
  utarray_new(newLevel->objects, &object_icd);
  utarray_reserve(newLevel->objects, 100);
  utarray_new(newLevel->enemys, &enemy_icd);
  utarray_reserve(newLevel->enemys, 20);
  newLevel->objects->d = 0;
  newLevel->objects->i = 0;
  newLevel->objects->n = 0;
  return newLevel;
}

void level_delete(Level *level)
{
  Sprite **currentObject = NULL;
  while ((currentObject = (Sprite **)utarray_next(level->objects, currentObject)))
    sprite_delete(*currentObject);

    utarray_free(level->objects);
    utarray_free(level->enemys);

    free(level);
}

Sprite *level_spawnObject(Level *level)
{
  Sprite *newObject = (Sprite *)malloc(sizeof(Sprite));
  utarray_push_back(level->objects, &newObject);
  return newObject;
}

Enemy *level_spawnEnemy(Level *level)
{
  Enemy *newEnemy = new_enemy(level);
  utarray_push_back(level->enemys, &newEnemy);
  return newEnemy;
}

struct EnemyType_1 level_spawnEnemyType_1(Level *level)
{
  return EnemyType_1_new(level_spawnEnemy(level), level);
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
  while ((currentObject = (Sprite **)utarray_next(level->objects, currentObject)))
    sprite_Draw(*currentObject);
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
      newCollisionBox->pos.y = i / 8 * 16 + level->levelChunk->y + 24;
      newCollisionBox->pos.x = i % 8 * 16 + level->levelChunk->x + 24;
      newCollisionBox->currentImage = NULL;
      newCollisionBox->animDelay = 0;

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
  while ((currentObject = (Enemy **)utarray_next(level->enemys, currentObject)))
  {

    if (*currentObject == enemy)
    {
      utarray_erase(level->enemys, i, 1);
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
  while ((currentEnemy = (Enemy **)utarray_next(level->enemys, currentEnemy)))
    enemy_update(*currentEnemy);
}

bool level_isDone(Level* level)
{
  return utarray_len(level->enemys) == 0;
}