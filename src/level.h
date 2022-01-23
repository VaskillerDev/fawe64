#pragma once
#include "libs.h"

/**
 * Класс, отвечающий за игровой уровень
 */
struct Level
{
    char* levelName;
    UT_array* objects;
    UT_array* enemys;
    TiledLevelChunk* levelChunk;
    ImagePool* imagePool;
};
typedef struct Level Level;

Level* level_new();
void level_setChunk(Level* level, TiledLevelChunk* chunk);
void level_setImagePool(Level* level, ImagePool* pool);
struct Sprite* level_spawnObject(Level *level);
struct Enemy* level_spawnEnemy(Level *level);
struct EnemyType_1 level_spawnEnemyType_1(Level *level);
void level_draw(Level* level);
void level_update(Level* level);
Level level_create();

void level_deleteObject(Level* level, struct Sprite* object);
void level_deleteEnemy(Level* level, struct Enemy* enemy);

void level_spawnCollisionByTiles(Level* level);