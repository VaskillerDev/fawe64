#pragma once
#include "libs.h"

/**
 * Класс, отвечающий за игровой уровень
 */
typedef struct Level
{
    UT_array* objects;
    UT_array* enemies;
    TiledLevelChunk* levelChunk;
    ImagePool* imagePool;
} Level;

/**
 * Сигнатура для функции загрузки чанка
 */
typedef struct LoadLevelArgs {
    Level* level;
    Vec2 newChunkPosition;
    ImagePool* imagePool;
    TiledLevelChunk* newChunk;
} LoadLevelArgs;

typedef struct ChunkMovingArgs {
    Level* level;
    ImagePool* imagePool;
    TiledLevelChunk* newChunk;
} ChunkMovingArgs;

Level* level_new();
void level_delete(Level* level);
void level_setChunk(Level* level, Vec2 chunkCoords, TiledLevelChunk* chunk);
void level_setImagePool(Level* level, ImagePool* pool);
struct Sprite* level_spawnObject(Level *level);
struct Enemy* level_spawnEnemy(Level *level);
struct EnemyType_1 level_spawnEnemyType_1(Level *level);
void level_draw(Level* level);
/**
 * Обработать логику перемещения между чанками
 * @param args
 * @param player
 */
void level_processChunkMoving(LoadLevelArgs args, Player* player);
void level_update(Level* level);

void level_deleteObject(Level* level, struct Sprite* object);
void level_deleteEnemy(Level* level, struct Enemy* enemy);

void level_spawnCollisionByTiles(Level* level);

bool level_isDone(Level* level);

void level_spawnEnemies(Level* level);

/**
 * Загрузить уровень (тайлы, противников, героя)
 * @param args
 */
void level_loadLevel(LoadLevelArgs args);

/**
 * Сдвинуться на указанный вектор и загрузить уровень
 * @param direction
 */
void level_moveAndLoadLevel(LoadLevelArgs args, Vec2 direction);


