#pragma once
#include "types.h"
#include "event.h"
#include "hp.h"
#include "image.h"

#define RANDOMIZE(a, b) (a) + ((float)rand() / (float)RAND_MAX * (b - a))

enum EnemyTypeName {
    EnemyTypeName_Unknown,
    EnemyTypeName_Warlock,
    EnemyTypeName_Bat,
    EnemyTypeName_Rock,
};

enum EnemyAttackTypeName {
    EnemyAttackTypeName_None,
    EnemyAttackTypeName_Melee,
    EnemyAttackTypeName_Range
};

typedef struct UnitMetaData {
    EnemyAttackTypeName attackName;
    EnemyTypeName name;
    uint8_t hp;
    uint8_t bulletSpeed;
    uint8_t bulletLifetime;
    bool swordResistance;
} UnitMetaData;

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
    void* tactics;
    Level* level;
    struct Sprite* sprite;
    struct NavRoot* navRoot;

    Hp health;
    int hitAnimationMaxTimerValue;
    int hitAnimationTimer;

    Vec2 moveDir;
    uint8_t movDist;
    uint8_t delay;

    UnitMetaData metaData;

    EnemyMovementDirection direction;

    EnemyActionState actionState;
    EnemyActionState prevActionState;

    EventEmitter emitter;
};

typedef struct Enemy Enemy;

Enemy* new_enemy(Level* level);
void enemy_death(HpPointsOverEvent eData);
void enemy_update(Enemy* enemy);
void on_enemy_change_animation(EnemyActionStateChangedEvent event);
void on_enemy_attack_bullet(EnemyAttackBulletEvent* event);
void on_enemy_has_got_bullet_collision(EnemyHasGotBulletCollisionEvent* e);
void enemy_start_hitAnimation(HpPointsChangedEvent* eData);