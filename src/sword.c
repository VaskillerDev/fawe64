#include "sword.h"
#include "math.h"
#include "image_pool.h"
#include "sprite.h"
#include "level.h"
#include "wasm4.h"
#include "player.h"

Sword sword_new(Level *level)
{
  Image* lSwordImage = imagePool_getImage (level->imagePool, PoolIdx_SwordLeft);
  Image* rSwordImage = imagePool_getImage (level->imagePool, PoolIdx_SwordRight);

    struct Sword sword = {
        .damage = 1,
        .sprite = level_spawnObject(level),
        .hit = false,
        .attackDelay = 30,
        .lSwordFrames = {
            lSwordImage,
            lSwordImage,
            lSwordImage
        },
        .rSwordFrames = {
            rSwordImage,
            rSwordImage,
            rSwordImage
        },
        .upSwordFrames = {
            imagePool_getImage (level->imagePool, PoolIdx_SwordUp),
            imagePool_getImage (level->imagePool, PoolIdx_SwordUp),
            imagePool_getImage (level->imagePool, PoolIdx_SwordUp)
        },
        .bottomSwordFrames = {
            imagePool_getImage (level->imagePool, PoolIdx_SwordBottom),
            imagePool_getImage (level->imagePool, PoolIdx_SwordBottom),
            imagePool_getImage (level->imagePool, PoolIdx_SwordBottom)
        }
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
  event.sword->hit = true;
  if (event.target == NULL) return;
  if(event.target->health->swordResistance) return;
  
  hp_substract(event.target->health, event.sword->damage);
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

  if (!sword->usage) return;

  struct EnemySwordAttackHitEvent event = {
      .player = player,
      .sword = sword,
  };

  bool isCanAttack = !sword->hit
      && sword->damageRange.x >= (float) sword->counter
      && (float) sword->counter <= sword->damageRange.y;

  if (isCanAttack)
  {
      Sprite **currentObject = NULL;
      while ((currentObject = (Sprite **)utarray_next(level->objects, currentObject)))
      {
          if (*currentObject == parent || *currentObject == sword->sprite)
              continue;

          if (CheckCollision(&sword->sprite->boundingVolume, &(*currentObject)->boundingVolume) && (*currentObject)->health)
          {
              event.target = *currentObject; // 'отловили' объект, который получит урон
              break;
          }
      }

      // отсюда начнется вся цепочка обратных вызовов, связанных с анимацией атаки
      eventEmitter_emit(&sword->emitter, E_SWORD_ATTACK_HIT, &event);
  }

  sword->counter += 1;
  if (sword->counter >= sword->attackDelay)
  {
      sword->usage = false;
      sword->hit = false;
  }

}

void sword_attack(Sword *sword)
{
    if (sword->usage)
        return;

    sword->usage = true;
    sword->counter = 0;
}