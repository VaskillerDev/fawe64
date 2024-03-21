#pragma once
#include "types.h"
#include "event.h"
#include "stdint.h"
#include "stdbool.h"
#include "image.h"

struct Sword
{
   struct Sprite* sprite;

    uint8_t attackDelay;
    uint8_t counter;
    uint8_t damage;
    Vec2 dir;
    Vec2f damageRange;
    bool usage;
    bool hit;

    // фреймы для спрайта
    Image* lSwordFrames[3];
    Image* rSwordFrames[3];
    Image* upSwordFrames[3];
    Image* bottomSwordFrames[3];

    EventEmitter emitter;
};

Sword sword_new(Level* level);
Sword sword_empty();
void sword_updatePosition(Sword* sword, struct Sprite* parent);
void sword_update(Player* player , Level* level);
void sword_attack(Sword* sword);
void sword_hit(EnemySwordAttackHitEvent event);