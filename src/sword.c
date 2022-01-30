#include "libs.h"
#include <math.h>



Sword sword_empty() {

  struct Sword sword = {
  .sprite = NULL,
  .counter = 0,
  .hit = false,
  .usage = false,
  .damage = 0,
  .emitter = {},
  .attackDelay = 0,
  .dir = vec2_new (0,0),
  .damageRange = vec2f_new (0,0)
  };

  return sword;
}

Sword sword_new(Level *level)
{
    struct Sword sword = {
        .damage = 1,
        .sprite = level_spawnObject(level),
        .hit = false
    };

    sword.sprite->boundingVolume.position = &sword.sprite->position;
    sword.sprite->boundingVolume.shape = BOX_TRIGGER;
    sword.sprite->animDelay = 0;
    sword.sprite->currentImage = NULL;

    sword.emitter = eventEmitter_new();
    eventEmitter_on (&sword.emitter, E_SWORD_ATTACK_HIT, &sword_hit);

    return sword;
}

void sword_hit(EnemySwordAttackHitEvent event) {
  hp_substract(event.target->health, event.sword->damage);
  event.sword->hit = true;
  tone(150, 2 | (50 << 8), 40, TONE_NOISE | TONE_MODE1);
}

void sword_updatePosition(Sword *sword, Sprite *parent)
{
    Vec2 dir = sword->dir;
    sword->sprite->boundingVolume.shape = BOX_TRIGGER;
    sword->sprite->boundingVolume.size = vec2_add(vec2_new(4, 4), vec2_mul(vec2_new(abs(dir.x), abs(dir.y)), vec2_new(4, 4)));

    sword->sprite->position = vec2_add(parent->position, vec2_mul(dir,
                                                                  vec2_new((parent->size.x + sword->sprite->boundingVolume.size.x) / 2, (parent->size.y + sword->sprite->boundingVolume.size.y) / 2)));
}

void sword_update(Player* player , Level* level)
{
  Sword* sword = &player->sword;
  Sprite* parent = player->sprite;

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
                    struct EnemySwordAttackHitEvent event = {
                        .player = player,
                        .sword = sword,
                        .target = *currentObject
                    };

                    eventEmitter_emit(&sword->emitter, E_SWORD_ATTACK_HIT, &event);
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