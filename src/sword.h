#pragma once
#include "libs.h"

struct Sword
{
   struct Sprite* sprite;

    uint_8 attackDelay;
    uint_8 counter;
    uint_8 damage;
    Vec2 dir;
    Vec2f damageRange;
    bool usage;
    bool hit;

    EventEmitter emitter;
};

typedef struct Sword Sword;

Sword sword_new(Level* level);
Sword sword_empty();
void sword_updatePosition(Sword* sword, struct Sprite* parent);
void sword_update(Sword* sword, struct Sprite* parent, Level* level);
void sword_attack(Sword* sword);
void sword_hit(EnemySwordAttackHitEvent event);