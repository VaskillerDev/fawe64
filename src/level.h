#pragma once
#include "libs.h"

struct Level
{
    char* levelName;
    UT_array* objects;
};
typedef struct Level Level;

Level* level_new();
Sprite* level_spawnObject(Level *level);
void level_draw(Level* level);