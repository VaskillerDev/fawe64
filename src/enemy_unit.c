#include "enemy_unit.h"

EnemyWarlock ENEMY_WARLOCK_PROTOTYPE = {
    .name = Warlock
};

EnemyBat ENEMY_BAT_PROTOTYPE = {
    .name = Bat
};

EnemyUnit enemyUnit_new(EnemyUnitNewArgs args) {
  switch (args.type)
  {
      case Warlock: return warlock_new (args.enemy, args.level);
      case Bat: return bat_new(args.enemy, args.level);
      //default: return warlock_new (args.enemy, args.level);
  }
}

EnemyWarlock warlock_new(Enemy *enemy, Level *level)
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
    enemy->sprite->position = vec2_new(80, 100);

    EnemyWarlock warlock = ENEMY_WARLOCK_PROTOTYPE;
    warlock.enemy = enemy;
    warlock.enemy->tactics = &warlock_behaviour;
    return warlock;
}

void warlock_behaviour(Enemy *enemy)
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
                sprite_setFlipH (enemy->sprite, false);
              } break;
          }
        return;
    }
}

EnemyUnit bat_new(Enemy* enemy, Level* level) {
  enemy->sprite = level_spawnObject(level);
  enemy->direction = EnemyDir_Right;
  enemy->actionState = EnemyAction_Idle;

  Image *frames[3] = {
      imagePool_getImage(level->imagePool, PoolIdx_Enemy1Go0),
      imagePool_getImage(level->imagePool, PoolIdx_Enemy1Go1),
      imagePool_getImage(level->imagePool, PoolIdx_Enemy1Go2)
  };

  for (uint_8 i = 0; i < 3; i++) {
      enemy->goFrames[i] = frames[i];
    }

  Image *attackFrames[3] = {
      imagePool_getImage(level->imagePool, PoolIdx_Enemy1Go0),
      imagePool_getImage(level->imagePool, PoolIdx_Enemy1Go1),
      imagePool_getImage(level->imagePool, PoolIdx_Enemy1Go2)
  };

  for (uint_8 i = 0; i < 3; i++) {
      enemy->attackFrame[i] = attackFrames[i];
    }

  sprite_animated_init(enemy->sprite, enemy->goFrames, 3, 10);
  sprite_initBoundingVolume(enemy->sprite, BOX);

  enemy->sprite->health = &enemy->health;
  enemy->sprite->position = vec2_new(80, 100);

  EnemyWarlock bat = ENEMY_BAT_PROTOTYPE;
  bat.enemy = enemy;
  bat.enemy->tactics = &bat_behaviour;
  return bat;
}

void bat_behaviour(Enemy* enemy) {
  enemy->actionState = EnemyAction_Go;
  bool isFlipH = player_getInstance()->sprite->position.x < enemy->sprite->position.x;
  sprite_setFlipH (enemy->sprite, isFlipH);

  if (enemy->movDist == 0)
    {
      enemy->delay = 30;
      enemy->movDist = RANDOMIZE(100, 100);

      enemy->direction = (EnemyMovementDirection) RANDOMIZE(1, 5);

      switch (enemy->direction)
        {
          case EnemyDir_Bottom: {
              enemy->moveDir = vec2_new(-1, -1);
            } break;
          case EnemyDir_Up: {
              enemy->moveDir = vec2_new(1, 1);
            } break;
          case EnemyDir_Left: {
              //sprite_setFlipH (enemy->sprite, true);
              enemy->moveDir = vec2_new(-1, 1);
            } break;
          case EnemyDir_Right: {
              //sprite_setFlipH (enemy->sprite, false);
              enemy->moveDir = vec2_new(1, -1);
            } break;
        }
      return;
    }
}