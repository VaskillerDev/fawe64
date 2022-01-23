#include "enemy_type_1.h"

EnemyType_1 EnemyType_1_new(Enemy *enemy, Level *level)
{
    enemy->sprite = level_spawnObject(level);
    enemy->direction = EnemyDir_Right;
    enemy->actionState = EnemyAction_Idle;

    Image *frames[3] = {
        imagePool_getImage(level->imagePool, PoolIdx_Enemy0Go0),
        imagePool_getImage(level->imagePool, PoolIdx_Enemy0Go1),
        imagePool_getImage(level->imagePool, PoolIdx_Enemy0Go2)
    };

    for (uint_8 i = 0; i < 3; i++) {
        enemy->goFrames[i] = frames[i];
    }

  Image *attackFrames[3] = {
      imagePool_getImage(level->imagePool, PoolIdx_Enemy0Attack),
      imagePool_getImage(level->imagePool, PoolIdx_Enemy0Attack),
      imagePool_getImage(level->imagePool, PoolIdx_Enemy0Attack)
  };

  for (uint_8 i = 0; i < 3; i++) {
      enemy->attackFrame[i] = attackFrames[i];
    }

    sprite_animated_init(enemy->sprite, enemy->goFrames, 3, 10);
    sprite_initBoundingVolume(enemy->sprite, BOX);

    enemy->sprite->health = &enemy->health;
    enemy->sprite->pos = vec2_new(80, 100);
    EnemyType_1 newEnemy;
    newEnemy.enemy = enemy;

    newEnemy.enemy->tactics = &EnemyTactics_1;
    return newEnemy;
}

void EnemyTactics_1(Enemy *enemy)
{

  /**
   * TODO: Пока delay > 0 movDist не тратится
   */
  if (enemy->delay > 0) {
    enemy->actionState = EnemyAction_Idle;
  } else if(enemy->movDist > 0)
    {
      enemy->actionState = EnemyAction_Go;
    } else if (enemy->movDist == 0)
    {
        enemy->delay = 30;
        enemy->movDist = RANDOMIZE(20, 60);

        enemy->direction = (EnemyMovementDirection) RANDOMIZE(1, 5);

        switch (enemy->direction)
          {
            case EnemyDir_Bottom: {
                enemy->moveDir = vec2_new(0, -1);
                sprite_setFlipH (enemy->sprite, false);
              } break;
            case EnemyDir_Up: {
                enemy->moveDir = vec2_new(0, 1);
              } break;
            case EnemyDir_Left: {
                enemy->moveDir = vec2_new(-1, 0);
                sprite_setFlipH (enemy->sprite, true);
              } break;
            case EnemyDir_Right: {
                enemy->moveDir = vec2_new(1, 0);
              } break;
          }
        return;
    }
}