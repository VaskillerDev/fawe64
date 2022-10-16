#pragma once
#include "libs.h"
#include "hp.h"
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

    uint_8 bulletSpeed;
    uint_8 bulletLifetime;
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
    Vec2 moveDir;
    uint_8 movDist;
    uint_8 delay;

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