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

    EventEmitter emitter;
    BulletManager bulletManager;
    BombManager bombManager;
    Dungeon dungeon;
   
    bool pause;
    bool isTilesActive;
} Level;

/**
 * Сигнатура для функции загрузки чанка
 */
typedef struct LoadLevelArgs {
    Level* level;
    ImagePool* imagePool;
    TiledLevelChunk* newChunk;
    Vec2 newChunkPosition;
} LoadLevelArgs;

typedef struct LoadDungeonArgs {

}LoadDungeonArgs;

typedef struct ChunkMovingArgs {
    Level* level;
    ImagePool* imagePool;
    TiledLevelChunk* newChunk;
} ChunkMovingArgs;

enum ChunkMovingDirection {
    ChunkMovingDirection_Right,
    ChunkMovingDirection_Up,
    ChunkMovingDirection_Left,
    ChunkMovingDirection_Bottom
};

Level* level_new();
void level_clear(Level* level);
void level_delete(Level* level);
void level_setChunk(Level* level, Vec2 chunkCoords, TiledLevelChunk* chunk);
void level_setImagePool(Level* level, ImagePool* pool);
struct Sprite* level_spawnObject(Level *level);
struct Enemy* level_spawnEnemy(Level *level);
struct EnemyUnit level_spawnUnit(Level *level, EnemyTypeName type);
void level_draw(Level* level);
Enemy* level_findNearestEnemy(Level* level, Vec2 position);
Sprite* level_findNearestTile(Level* level, Vec2 position);

/**
 * Обработать логику перемещения между чанками
 * @param args
 * @param player
 */
bool level_processChunkMoving(LoadLevelArgs* args, Player* player);
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
void level_loadLevel(LoadLevelArgs* args, ChunkMovingDirection direction);

void level_loadDungeon(LoadDungeonArgs* args);

/**
 * Сдвинуться на указанный вектор и загрузить уровень
 * @param direction
 */
void level_moveAndLoadLevel(LoadLevelArgs* args, ChunkMovingDirection direction);

Vec2 level_directionAsStartPosition(ChunkMovingDirection direction);

void on_level_enemy_attack_bullet(LevelEnemyAttackBulletEvent* event);

void on_dungeon_enter(BoundingVolumeCollidedEvent event);

void on_level_border_contact(LevelBorderContactEvent event);

