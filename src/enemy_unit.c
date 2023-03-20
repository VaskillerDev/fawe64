#include "enemy_unit.h"
#include "bossState.h"

const uint_8 BOSS0_HEAD_DELAY = 240;

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

EnemyBoss0Head ENEMY_BOSS0_HEAD_PROTOTYPE = {
        .metaData = {
                .name = EnemyTypeName_Boss0Head,
                .attackName = EnemyAttackTypeName_Melee,
                .bulletLifetime = 32,
                .bulletSpeed = 2,
                .swordResistance = false
        }
};

EnemyBoss0Hand  ENEMY_BOSS0_HAND_PROTOTYPE = {
        .metaData = {
                .name = EnemyTypeName_Boss0Hand,
                .attackName = EnemyAttackTypeName_Melee,
                .bulletLifetime = 5,
                .bulletSpeed = 2,
                .swordResistance = true
        }
};

EnemyUnit enemyUnit_new(EnemyUnitNewArgs args) {
  switch (args.type)
  {
      case EnemyTypeName_Warlock: return warlock_new (args.enemy, args.level);
      case EnemyTypeName_Bat: return bat_new(args.enemy, args.level);
      case EnemyTypeName_Rock: return rock_new (args.enemy, args.level);
      case EnemyTypeName_Boss0Head: return boss0Head_new(args.enemy, args.level);
      case EnemyTypeName_Boss0Hand: return boss0Hand_new(args.enemy, args.level);

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
      if(enemy->navRoot)
        {
          Navigation_Move(enemy, enemy->navRoot, 1);
        }
      enemy->actionState = EnemyAction_Go;
    } else if (enemy->movDist == 0)
    {
        enemy->delay = 30;
        enemy->movDist = RANDOMIZE(20, 60);
        if(enemy->navRoot)
        {
          Navigation_Move(enemy, enemy->navRoot, 1);
          enemy->delay = 60;
          enemy->direction = 0;
        }
        else
        {
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
    else
    {
      if(enemy->navRoot)
      {
         enemy->direction = 0;
         enemy->moveDir = vec2_new(0, 0);
        Navigation_Move(enemy, enemy->navRoot, 1);
      }
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

Enemy* bossHead = NULL;

EnemyUnit boss0Head_new(Enemy* enemy, Level* level) {
    bossHead = enemy;
    enemy->sprite = level_spawnObject(level);
    enemy->direction = EnemyDir_Bottom;
    enemy->actionState = EnemyAction_Idle;
    enemy->health.maxPoints = 15;
    enemy->health.currentPoints = enemy->health.maxPoints;

    Image *frames[4] = {
            imagePool_getImage(level->imagePool, PoolIdx_Boss0Idle0),
            imagePool_getImage(level->imagePool, PoolIdx_Boss0Idle1),
            imagePool_getImage(level->imagePool, PoolIdx_Boss0Idle2),
            imagePool_getImage(level->imagePool, PoolIdx_Boss0Idle3),
    };

    for (uint_8 i = 0; i < 4; i++) {
        enemy->goFrames[i] = frames[i];
    }

    Image *attackFrames[3] = {
            imagePool_getImage(level->imagePool, PoolIdx_Boss0Idle0),
            imagePool_getImage(level->imagePool, PoolIdx_Boss0Idle0),
            imagePool_getImage(level->imagePool, PoolIdx_Boss0Idle0)
    };

    for (uint_8 i = 0; i < 3; i++) {
        enemy->attackFrame[i] = attackFrames[i];
    }

    sprite_animated_init(enemy->sprite, enemy->goFrames, 4, 10);
    sprite_initBoundingVolume(enemy->sprite, BOX, BoundingVolumeTag_Enemy);

    enemy->sprite->health = &enemy->health;
    enemy->sprite->position = vec2_new(80, 100);

    EnemyBoss0Head head = ENEMY_BOSS0_HEAD_PROTOTYPE;
    head.enemy = enemy;
    enemy->sprite->health->swordResistance = head.metaData.swordResistance;
    enemyUnit_updateAttackNameForEnemy(&head);
    head.enemy->tactics = &boss0Head_behaviour;

    // navigation
    enemy->navRoot->navPointArray[0] = vec2_new(2 * 16,3 * 16);
    enemy->navRoot->navPointArray[1] = vec2_new(8 * 16,3 * 16);
    enemy->navRoot->navPointArray[2] = vec2_new(101,0);

    enemy->delay = BOSS0_HEAD_DELAY;

    bossState_new(enemy);
    return head;
}

void boss0Head_behaviour(Enemy* enemy) {
    enemy;
    bossState_update();
}

EnemyUnit boss0Hand_new(Enemy* enemy, Level* level) {
    bossState_appendHand(enemy);

    enemy->sprite = level_spawnObject(level);
    enemy->direction = EnemyDir_Bottom;
    enemy->actionState = EnemyAction_Idle;
    enemy->health.maxPoints = 15;
    enemy->health.currentPoints = enemy->health.maxPoints;

    Image *frames[3] = {
            imagePool_getImage(level->imagePool, PoolIdx_Boss0HandClose),
            imagePool_getImage(level->imagePool, PoolIdx_Boss0HandClose),
            imagePool_getImage(level->imagePool, PoolIdx_Boss0HandClose),
    };

    for (uint_8 i = 0; i < 3; i++) {
        enemy->goFrames[i] = frames[i];
    }

    Image *attackFrames[3] = {
            imagePool_getImage(level->imagePool, PoolIdx_Boss0HandOpen),
            imagePool_getImage(level->imagePool, PoolIdx_Boss0HandOpen),
            imagePool_getImage(level->imagePool, PoolIdx_Boss0HandOpen),
    };

    for (uint_8 i = 0; i < 3; i++) {
        enemy->attackFrame[i] = attackFrames[i];
    }

    sprite_animated_init(enemy->sprite, enemy->goFrames, 3, 10);
    sprite_initBoundingVolume(enemy->sprite, BOX, BoundingVolumeTag_Enemy);

    enemy->sprite->health = &enemy->health;
    enemy->sprite->position = vec2_new(160, 160);

    EnemyBoss0Hand hand = ENEMY_BOSS0_HAND_PROTOTYPE;
    hand.enemy = enemy;
    enemy->sprite->health->swordResistance = hand.metaData.swordResistance;
    enemyUnit_updateAttackNameForEnemy(&hand);
    hand.enemy->tactics = &boss0Hand_behaviour;

    // navigation
    enemy->navRoot->navPointArray[0] = vec2_new(3 * 16,4 * 16);
    enemy->navRoot->navPointArray[1] = vec2_new(9 * 16,4 * 16);
    enemy->navRoot->navPointArray[2] = vec2_new(101,0);

    enemy->delay = BOSS0_HEAD_DELAY;

    return hand;
}

void boss0Hand_behaviour(Enemy* enemy) {
    enemy->actionState = EnemyAction_Go;

    if (enemy->delay <= 0) {
        enemy->actionState = EnemyAction_Idle;
        enemy->delay = BOSS0_HEAD_DELAY;
        //enemy->sprite->position = vec2_add(enemy->sprite->position, vec2_new(-1,0));
    }

    if (bossHead != NULL) {
        //enemy->sprite->position = vec2_add(bossHead->sprite->position, vec2_new(-16,5));
    }


    //enemy->direction = 0;
    //enemy->moveDir = vec2_new(0, 0);
   // Navigation_Move(enemy, enemy->navRoot, 1);
}