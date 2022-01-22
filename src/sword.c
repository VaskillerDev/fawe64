#include "libs.h"
#include <math.h>

Sword sword_new(Level *level)
{
    Sword sword;
    sword.damage = 1;
    sword.sprite = level_spawnObject(level);
    sword.sprite->boundingVolume.position = &sword.sprite->pos;
    sword.sprite->boundingVolume.shape = BOX_TRIGGER;
    sword.sprite->animDelay = 0;
    sword.sprite->currentImage = NULL;
    return sword;
}

void sword_updatePosition(Sword *sword, Sprite *parent)
{
    Vec2 dir = sword->dir;
    sword->sprite->boundingVolume.shape = BOX_TRIGGER;
    sword->sprite->boundingVolume.size = vec2_add(vec2_new(4, 4), vec2_mul(vec2_new(abs(dir.x), abs(dir.y)), vec2_new(4, 4)));

    sword->sprite->pos = vec2_add(parent->pos, vec2_mul(dir, 
        vec2_new((parent->size.x + sword->sprite->boundingVolume.size.x) / 2, (parent->size.y + sword->sprite->boundingVolume.size.y) / 2)));
}