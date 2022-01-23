#pragma once
#include "sprite.h"

struct Enemy
{
    Level* level;
    Sprite* sprite;
    Hp health;

    void* tactics;
    Vec2 moveDir;
    uint_32 movDist;
    uint_32 delay;
};

typedef struct Enemy Enemy;

Enemy* new_enemy(Level* level);
void enemy_death(HpPointsOverEvent eData);
void enemy_update(Enemy* enemy);