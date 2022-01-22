#include "libs.h"

UT_icd object_icd = {sizeof (Sprite *), NULL, NULL, NULL};

Level *level_new()
{
    Level *newLevel = (Level *)malloc(sizeof(Level));
    newLevel->levelName = "test";
    utarray_new(newLevel->objects, &object_icd);
    newLevel->objects->d = 0;
    newLevel->objects->i = 0;
    newLevel->objects->n = 0;
    return newLevel;
}

Sprite *level_spawnObject (Level *level)
{
  Sprite *newObject = (Sprite *) malloc (sizeof (Sprite));
  utarray_push_back(level->objects, &newObject);
  return newObject;
}

void level_draw (Level *level)
{
  if (level->imagePool == NULL) {
      trace ("imagePool not found!");
      return;
  }

  if (level->levelChunk == NULL) {
      trace ("levelChunk not found!");
      return;
  }

  tiledLevelChunk_draw(level->levelChunk,level->imagePool);

  Sprite **currentObject = NULL;
  while ((currentObject = (Sprite **) utarray_next(level->objects, currentObject)))
    sprite_Draw (*currentObject);
}

void level_setChunk(Level * level, TiledLevelChunk* levelChunk) {
  tiledLevelChunk_read (levelChunk, 0, 0);
  level->levelChunk = levelChunk;
}

void level_setImagePool(Level * level, ImagePool* pool) {
  level->imagePool = pool;
}