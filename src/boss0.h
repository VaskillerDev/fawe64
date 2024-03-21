#pragma once
#include "enemy.h"

typedef struct Boss0State {
} Boss0State;

typedef enum Boss0Stage {
    Boss0Stage_Early,
    Boss0Stage_Middle,
    Boss0Stage_Late
} Boss0Stage;

typedef struct Boss0 {
    EventEmitter emitter;
    Enemy* head;
    Enemy* handL;
    Enemy* handR;
    Boss0Stage stage;
    Boss0State state;
} Boss0;
static Boss0 bossOInstance = {};
static bool isBoss0Init = false;

Boss0 boss0_init(Enemy* head,
                 Enemy* handL,
                 Enemy* handR);

Boss0 boss0_getInstance();

EnemyUnit boss0_headInit(Boss0* boss0);
void boss0_headBehaviour(Enemy* enemy);

EnemyUnit boss0_handInit(Boss0* boss0, bool isLeft);
void boss0_handBehaviour(Enemy* enemy);
