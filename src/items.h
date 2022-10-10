#pragma once
#include "libs.h"

typedef struct Bomb
{
    Sprite* sprite;
    Timer timer;
    bool directionalExplosion;
} Bomb;

Bomb bomb_new(Level* level, Vec2 spawnPoint);
bool bomb_isEmpty(Bomb* bomb);
void bomb_update(Level* level, Bomb *bomb);

Bomb directedBomb_new(Level* level, Vec2 spawnPoint);
void directedBomb_update(Level* level, Bomb *bomb);

typedef struct BombManager
{
    Bomb bombs[10];
} BombManager;

BombManager bombManager_new();
void bombManager_addBomb(Level* level, Vec2 position, bool directed);
void bombManager_update(Level* level, BombManager* bombManager);

void usePoition();
bool setupBomb();
bool setupDirectedBomb();