#pragma once
#include "libs.h"
#include "hp.h"

typedef enum EnemyMovementDirection {
    EnemyDir_Bottom = 1,
    EnemyDir_Up = 2,
    EnemyDir_Left = 3,
    EnemyDir_Right = 4,
} EnemyMovementDirection;

typedef enum EnemyActionState {
    EnemyAction_Idle,
    EnemyAction_Go
} EnemyActionState;

struct Enemy
{
    Image* goFrames[3];
    Image* attackFrame[3];

    Level* level;
    struct Sprite* sprite;
    Hp health;

    void* tactics;
    Vec2 moveDir;
    uint_32 movDist;
    uint_32 delay;

    EnemyMovementDirection direction;

    EnemyActionState actionState;
    EnemyActionState prevActionState;

    EventEmitter emitter;
};

typedef struct Enemy Enemy;

Enemy* new_enemy(Level* level);
void enemy_death(HpPointsOverEvent eData);
void enemy_update(Enemy* enemy);
void enemy_change_animation(EnemyActionStateChangedEvent event);