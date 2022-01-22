#pragma once
#include "libs.h"

/**
 * Класс, отвечающий за игровой уровень
 */
struct Level
{
    char* levelName;
    UT_array* objects;
    TiledLevelChunk* levelChunk;
    ImagePool* imagePool;
};
typedef struct Level Level;

Level* level_new();
void level_setChunk(Level* level, TiledLevelChunk* chunk);
void level_setImagePool(Level* level, ImagePool* pool);
Sprite* level_spawnObject(Level *level);
void level_draw(Level* level);
struct Level level_create();