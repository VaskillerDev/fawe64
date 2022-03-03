#pragma once
#include"enemy.h"

enum EnemyTypeName {
    Warlock,
    Bat
};

struct EnemyUnit {
    const EnemyTypeName name;
    Enemy* enemy;
};

struct EnemyUnitNewArgs {
    EnemyTypeName type;
    Enemy* enemy;
    Level* level;
};

EnemyUnit enemyUnit_new(EnemyUnitNewArgs args);

// warlock
typedef struct EnemyUnit EnemyWarlock;
EnemyWarlock warlock_new(Enemy* enemy, Level* level);
void warlock_behaviour(Enemy * enemy);

// bat
typedef struct EnemyUnit EnemyBat;
EnemyUnit bat_new(Enemy* enemy, Level* level);
void bat_behaviour(Enemy* enemy);