#include "boss0.h"
#include "enemy_unit.h"
#include "player.h"
#include "wasm4.h"
#include "render.h"

const uint8_t BOSS0_HEAD_DELAY = 240;
const uint8_t BOSS0_HAND_DELAY = 100;

/**
 * Prototype of boss.head instance
 */
EnemyBoss0Head ENEMY_BOSS0_HEAD_PROTOTYPE = {
        .metaData = {
                .name = EnemyTypeName_Boss0Head,
                .attackName = EnemyAttackTypeName_Melee,
                .bulletLifetime = 32,
                .bulletSpeed = 2,
                .swordResistance = false
        }
};

/**
 * Prototype of boss.hand instance
 */
EnemyBoss0Hand  ENEMY_BOSS0_HAND_PROTOTYPE = {
        .metaData = {
                .name = EnemyTypeName_Boss0Hand,
                .attackName = EnemyAttackTypeName_Melee,
                .bulletLifetime = 5,
                .bulletSpeed = 2,
                .swordResistance = true
        }
};

/**
 * get Boss global instance
 * @return
 */
Boss0 boss0_getInstance() {
    return boss0_init(NULL, NULL, NULL);
}

/**
 * init Boss
 * @param head
 * @param handL
 * @param handR
 * @return
 */
Boss0 boss0_init(Enemy* head,
                        Enemy* handL,
                        Enemy* handR) {
    if (isBoss0Init) {
        return bossOInstance;
    }

    Boss0 newInstance = {
            .emitter = eventEmitter_new(),
            .head = head,
            .handL = handL,
            .handR = handR
    };

    bossOInstance = newInstance;
    boss0_headInit(&bossOInstance);

    isBoss0Init = true;
    return bossOInstance;
}


EnemyUnit boss0_headInit(Boss0* boss0) {
    Enemy* enemy = boss0->head;
    Level* level = enemy->level;

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

    for (uint8_t i = 0; i < 4; i++) {
        enemy->goFrames[i] = frames[i];
    }

    Image *attackFrames[3] = {
            imagePool_getImage(level->imagePool, PoolIdx_Boss0Idle0),
            imagePool_getImage(level->imagePool, PoolIdx_Boss0Idle0),
            imagePool_getImage(level->imagePool, PoolIdx_Boss0Idle0)
    };

    for (uint8_t i = 0; i < 3; i++) {
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
    head.enemy->tactics = &boss0_headBehaviour;

    // navigation
    enemy->navRoot->navPointArray[0] = vec2_new(2 * 16,3 * 16);
    enemy->navRoot->navPointArray[1] = vec2_new(8 * 16,3 * 16);
    enemy->navRoot->navPointArray[2] = vec2_new(101,0);

    enemy->delay = BOSS0_HEAD_DELAY;

    return head;
}

/**
 * Use boss.head behavoiur
 * @param boss0
 */
void boss0_headBehaviour(Enemy* enemy) {

    int proc = (float)((float)enemy->health.currentPoints / (float)enemy->health.maxPoints) * 100;
    DrawProgressBar(proc);

    enemy->actionState = EnemyAction_Go;
    bool isFlipH = player_getInstance()->sprite->position.x < enemy->sprite->position.x;
    sprite_setFlipH (enemy->sprite, isFlipH);

    if (enemy->delay <= 0) {
        enemy->actionState = EnemyAction_Idle;
        enemy->delay = BOSS0_HEAD_DELAY;
    }

    enemy->direction = 0;
    enemy->moveDir = vec2_new(0, 0);
    Navigation_Move(enemy, enemy->navRoot, 1);
}

EnemyUnit boss0_handInit(Boss0* boss0, bool isLeft) {
    Enemy* enemy = isLeft ? boss0->handL : boss0->handR;
    Level* level = enemy-> level;

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

    for (uint8_t i = 0; i < 3; i++) {
        enemy->goFrames[i] = frames[i];
    }

    Image *attackFrames[3] = {
            imagePool_getImage(level->imagePool, PoolIdx_Boss0HandOpen),
            imagePool_getImage(level->imagePool, PoolIdx_Boss0HandOpen),
            imagePool_getImage(level->imagePool, PoolIdx_Boss0HandOpen),
    };

    for (uint8_t i = 0; i < 3; i++) {
        enemy->attackFrame[i] = attackFrames[i];
    }

    sprite_animated_init(enemy->sprite, enemy->goFrames, 3, 10);
    sprite_initBoundingVolume(enemy->sprite, BOX, BoundingVolumeTag_Enemy);

    enemy->sprite->health = &enemy->health;

    EnemyBoss0Hand hand = ENEMY_BOSS0_HAND_PROTOTYPE;
    hand.enemy = enemy;
    enemy->sprite->health->swordResistance = hand.metaData.swordResistance;
    enemyUnit_updateAttackNameForEnemy(&hand);
    hand.enemy->tactics = &boss0_handBehaviour;

    enemy->delay = BOSS0_HEAD_DELAY;

    return hand;
}

Enemy* bossHead = NULL;
bool isUseHand = false;
int useHandTimeMax = 50;
int useHandTime = 0;
bool isReverseHand = false;
void boss0_handBehaviour(Enemy* enemy) {
    enemy->actionState = EnemyAction_Go;

    if (enemy->delay <= 0) {
        isUseHand = true;
        enemy->actionState = EnemyAction_Idle;
        enemy->delay = BOSS0_HAND_DELAY;
    }

    if (bossHead != NULL) {
        if (!isUseHand) {
            enemy->sprite->position = vec2_add(bossHead->sprite->position, vec2_new(-16 ,5));
        }
    }

    if (isUseHand && useHandTime <= useHandTimeMax) {
        Vec2 vec2 = isReverseHand ? vec2_new(0,-1) : vec2_new(0,1);
        enemy->sprite->position = vec2_add(enemy->sprite->position, vec2);
        useHandTime += 1;
    }

    bool isTimeExpired = useHandTime >= useHandTimeMax;
    if (isTimeExpired) {
        useHandTime = 0;
        isReverseHand = true;
    }

    if (isReverseHand &&isTimeExpired ) {
        tracef("n");
    }

    enemy->direction = 0;
    enemy->moveDir = vec2_new(0, 0);
}