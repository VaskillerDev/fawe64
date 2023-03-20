#pragma once
#include "enemy.h"

const int BOSS_ATTACK_DELAY = 180;

typedef enum BossStage {
    BossStage_Early,
    BossStage_Middle,
    BossStage_Late
} BossStage;

typedef struct BossState {
    EventEmitter emitter;
    BossStage stage;
    Timer bossHandAttackTimer;
    Enemy* head;
    Enemy* handLeft;
    Enemy* handRight;
    bool hasLeftHand;
} BossState;

static BossState BOSS_STATE = {0};

void on_boss_timer_for_double_hand_attack(BossTimerExpiredEvent* e);
void on_boss_timer_for_fire_expired(BossTimerExpiredEvent* e);
void bossState_appendHand(Enemy* enemy);
void bossState_fire();

void bossState_new(Enemy* enemy) {
    BossState state = {
            .handLeft = false,
            .head = enemy,
            .stage = BossStage_Early,
            .emitter = eventEmitter_new(),
            .bossHandAttackTimer = timer_new(BOSS_ATTACK_DELAY, true),
    };

    eventEmitter_on(&state.bossHandAttackTimer.emitter,
                    E_TIMER_EXPIRED,
                    &on_boss_timer_for_double_hand_attack);

    timer_start(&state.bossHandAttackTimer);

    BOSS_STATE = state;
}

void bossState_appendHand(Enemy* enemy) {
    BOSS_STATE.hasLeftHand ?
    (BOSS_STATE.handRight = enemy) :
    (BOSS_STATE.handLeft = enemy);

    BOSS_STATE.hasLeftHand = true;
}

void bossState_update() {
    Enemy* head = BOSS_STATE.head;
    timer_update(&BOSS_STATE.bossHandAttackTimer);

    int proc = (float)((float)head->health.currentPoints / (float)head->health.maxPoints) * 100;
    DrawProgressBar(proc);

    head->direction = 0;
    head->moveDir = vec2_new(0, 0);
    head->actionState = EnemyAction_Go;
    Navigation_Move(head, head->navRoot, 1);
}

void bossState_fire() {
    struct EnemyAttackBulletEvent attackEvent = {
            .enemy = BOSS_STATE.head,
            .level = BOSS_STATE.head->level
    };
    eventEmitter_emit (&BOSS_STATE.head->emitter, E_ENEMY_ATTACK_BULLET, &attackEvent);
}

void on_boss_timer_for_double_hand_attack(BossTimerExpiredEvent* e) {
    e;
    Navigation_Move(BOSS_STATE.handLeft, BOSS_STATE.handLeft->navRoot, 1);
}

void on_boss_timer_for_fire_expired(BossTimerExpiredEvent* e) {
    e;
    BOSS_STATE.head->actionState = EnemyAction_Idle;
    bossState_fire();
}

