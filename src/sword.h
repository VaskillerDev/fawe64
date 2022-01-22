#pragma once
#include "libs.h"

struct Sword
{
    Sprite* sprite;

    uint_8 attackDelay;
    uint_8 counter;
    uint_8 damage;
    Vec2 dir;
    Vec2f damageRange;
    bool usage;
};

typedef struct Sword Sword;

Sword sword_new(Level* level);
void sword_updatePosition(Sword* sword, Sprite* parent);