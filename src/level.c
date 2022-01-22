#include "libs.h"

UT_icd object_icd = {sizeof(Sprite *), NULL, NULL, NULL};

Level *level_new()
{
  Level *newLevel = (Level *)malloc(sizeof(Level));
  newLevel->levelName = "test";
  utarray_new(newLevel->objects, &object_icd);
  utarray_reserve(newLevel->objects, 100);
  newLevel->objects->d = 0;
  newLevel->objects->i = 0;
  newLevel->objects->n = 0;
  return newLevel;
}

Sprite *level_spawnObject(Level *level)
{
  Sprite *newObject = (Sprite *)malloc(sizeof(Sprite));
  utarray_push_back(level->objects, &newObject);
  return newObject;
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

void level_setChunk(Level *level, TiledLevelChunk *levelChunk)
{
  tiledLevelChunk_read(levelChunk, 0, 0);
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