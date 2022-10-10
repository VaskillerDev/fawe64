#include "libs.h"

Enemy *new_enemy(Level *level)
{
  Enemy *enemy = (Enemy *)malloc(sizeof(Enemy));
  enemy->level = level;
  // todo: hp only for test. rm later
  enemy->health = hp_new(1, enemy, 2, 1, false);
  enemy->sprite = NULL;
  enemy->prevActionState = -1;
  UnitMetaData metaData = {
      .attackName = EnemyAttackTypeName_None,
      .name = EnemyTypeName_Unknown
  };
  enemy->metaData = metaData;
  enemy->emitter = eventEmitter_new();
  enemy->moveDir = vec2_new (0,0);

  eventEmitter_on (&enemy->emitter, E_ENEMY_HAS_GOT_BULLET_COLLISION, &on_enemy_has_got_bullet_collision);
  eventEmitter_on (&enemy->emitter, E_ENEMY_ACTION_STATE_CHANGED, &on_enemy_change_animation);
  eventEmitter_on (&enemy->emitter, E_ENEMY_ATTACK_BULLET, &on_enemy_attack_bullet);
  eventEmitter_on(&enemy->health.emitter, E_HP_POINTS_OVER, &enemy_death);

  return enemy;
}

void on_enemy_has_got_bullet_collision(EnemyHasGotBulletCollisionEvent* e) {
  hp_substract (&e->enemy->health, e->damage);
}

void on_enemy_attack_bullet(EnemyAttackBulletEvent* event) {
  struct LevelEnemyAttackBulletEvent attackEvent = {
      .enemy = event->enemy
  };
  eventEmitter_emit (&event->level->emitter, E_ENEMY_ATTACK_BULLET, (void*) &attackEvent);
}

void on_enemy_change_animation(EnemyActionStateChangedEvent event) {
  switch ((EnemyActionState)event.state)
    {
      case EnemyAction_Idle: {
        event.enemy->sprite->images = event.enemy->attackFrame;

        struct EnemyAttackBulletEvent attackEvent = {
            .enemy = event.enemy,
            .level = event.enemy->level
        };
        eventEmitter_emit (&event.enemy->emitter, E_ENEMY_ATTACK_BULLET,  &attackEvent);
      } break;
      case EnemyAction_Go: {
          event.enemy->sprite->images = event.enemy->goFrames;
      } break;
    }
}

void enemy_death(HpPointsOverEvent eData)
{
    Enemy *enemy = (Enemy *)eData.parent;
    level_deleteEnemy(enemy->level, enemy);
}

void enemy_update(Enemy *enemy)
{
    enemy->prevActionState = enemy->actionState;
    void (*tactics) () = enemy->tactics;
    tactics(enemy);

  if (enemy->actionState != enemy->prevActionState) {

    struct EnemyActionStateChangedEvent event = {
        .enemy = enemy,
        .state = enemy->actionState
    };

    eventEmitter_emit (&enemy->emitter, E_ENEMY_ACTION_STATE_CHANGED, &event);
  }

    if(enemy->delay > 0)
    {
         --enemy->delay;
         return;
    }

    if (enemy->movDist > 0)
    {
        if (!player_checkCollision(enemy->sprite, enemy->level, enemy->moveDir))
        {
            enemy->sprite->position = vec2_add(enemy->sprite->position, enemy->moveDir);
            --enemy->movDist;
        }
        else
            enemy->movDist = 0;
    }
}