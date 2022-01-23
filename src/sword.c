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
    sword.hit = false;
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

void sword_update(Sword *sword, Sprite *parent, Level *level)
{
    if (sword->usage)
    {
        if (!sword->hit && sword->damageRange.x >= sword->counter && sword->counter <= sword->damageRange.y)
        {
            Sprite **currentObject = NULL;
            while ((currentObject = (Sprite **)utarray_next(level->objects, currentObject)))
            {
                if (*currentObject == parent || *currentObject == sword->sprite)
                    continue;

                if (CheckCollision(&sword->sprite->boundingVolume, &(*currentObject)->boundingVolume) && (*currentObject)->health)
                {
                    hp_substract((*currentObject)->health, sword->damage);
                    sword->hit = true;
                    tone(150, 2 | (50 << 8), 40, TONE_NOISE | TONE_MODE1);
                    break;
                }
            }
        }

        ++sword->counter;
        if (sword->counter >= sword->attackDelay)
        {
            sword->usage = false;
            sword->hit = false;
        }
    }
}

void sword_attack(Sword *sword)
{
    if (sword->usage)
        return;

    sword->usage = true;
    sword->counter = 0;
}