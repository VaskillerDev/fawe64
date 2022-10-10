#include "enemy_unit.h"

EnemyWarlock ENEMY_WARLOCK_PROTOTYPE = {
    .metaData ={
      .name = EnemyTypeName_Warlock,
      .attackName = EnemyAttackTypeName_Range,
      .bulletLifetime = 100,
      .bulletSpeed = 1,
      .swordResistance = false
    }
};

EnemyBat ENEMY_BAT_PROTOTYPE = {
    .metaData ={
        .name = EnemyTypeName_Bat,
        .attackName = EnemyAttackTypeName_Melee,
        .bulletLifetime = 4,
        .bulletSpeed = 4,
        .swordResistance = false
    }
};

EnemyRock ENEMY_ROCK_PROTOTYPE = {
    .metaData = {
        .name = EnemyTypeName_Rock,
        .attackName = EnemyAttackTypeName_None,
        .bulletLifetime = 1,
        .bulletSpeed = 0,
        .swordResistance = true
    }
};

EnemyUnit enemyUnit_new(EnemyUnitNewArgs args) {
  switch (args.type)
  {
      case EnemyTypeName_Warlock: return warlock_new (args.enemy, args.level);
      case EnemyTypeName_Bat: return bat_new(args.enemy, args.level);
      case EnemyTypeName_Rock: return rock_new (args.enemy, args.level);

      case EnemyTypeName_Unknown:
      default: return warlock_new (args.enemy, args.level);
  }
}

void enemyUnit_updateAttackNameForEnemy(EnemyUnit* unit) {
  unit->enemy ->metaData = unit->metaData;
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
    sprite_initBoundingVolume(enemy->sprite, BOX, BoundingVolumeTag_Enemy);

    enemy->sprite->health = &enemy->health;
    enemy->sprite->position = vec2_new(80, 100);

    EnemyWarlock warlock = ENEMY_WARLOCK_PROTOTYPE;
    warlock.enemy = enemy;
    enemy->sprite->health->swordResistance = warlock.metaData.swordResistance;
    enemyUnit_updateAttackNameForEnemy(&warlock);
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
  sprite_initBoundingVolume(enemy->sprite, BOX, BoundingVolumeTag_Enemy);

  enemy->sprite->health = &enemy->health;
  enemy->sprite->position = vec2_new(80, 100);

  EnemyBat bat = ENEMY_BAT_PROTOTYPE;
  bat.enemy = enemy;
  enemy->sprite->health->swordResistance = bat.metaData.swordResistance;
  enemyUnit_updateAttackNameForEnemy(&bat);
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

      enemy->actionState = EnemyAction_Idle;
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
              enemy->moveDir = vec2_new(-1, 1);
            } break;
          case EnemyDir_Right: {
              enemy->moveDir = vec2_new(1, -1);
            } break;
        }
      return;
    }
}

EnemyUnit rock_new(Enemy* enemy, Level* level) {
  enemy->sprite = level_spawnObject(level);
  enemy->direction = EnemyDir_Left;
  enemy->actionState = EnemyAction_Idle;

  Image *frames[1] = {
      imagePool_getImage(level->imagePool, PoolIdx_Rock)
  };

  enemy->goFrames[0] = frames[0];

  sprite_animated_init(enemy->sprite, enemy->goFrames, 1, 10);
  sprite_initBoundingVolume(enemy->sprite, BOX, BoundingVolumeTag_Enemy);

  enemy->sprite->health = &enemy->health;
  enemy->sprite->position = vec2_new(80, 100);

  EnemyRock rock = ENEMY_ROCK_PROTOTYPE;
  rock.enemy = enemy;
  enemy->sprite->health->swordResistance = rock.metaData.swordResistance;
  enemyUnit_updateAttackNameForEnemy(&rock);
  rock.enemy->tactics = &rock_behaviour;
  return rock;
}

void rock_behaviour(Enemy* enemy) {
  enemy->actionState = EnemyAction_Idle;
  sprite_setFlipH (enemy->sprite, false);
  Vec2 playerPosition = player_getInstance()->sprite->position;
  Vec2 rockPosition = enemy->sprite->position;

  float distance = vec2_getLength(vec2_sub(playerPosition, rockPosition));

  if (distance < 24) {
      uint_16 color = *DRAW_COLORS;
      *DRAW_COLORS = 0x30;
      rect (rockPosition.x - 9, rockPosition.y - 9, 18, 18);
      *DRAW_COLORS =color;
  }
}