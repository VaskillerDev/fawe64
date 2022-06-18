#pragma once
#include"enemy.h"

struct EnemyUnit {
    UnitMetaData metaData;
    Enemy* enemy;
};

struct EnemyUnitNewArgs {
    EnemyTypeName type;
    Enemy* enemy;
    Level* level;
};

EnemyUnit enemyUnit_new(EnemyUnitNewArgs args);

void enemyUnit_updateAttackNameForEnemy(EnemyUnit* unit);

// warlock
typedef struct EnemyUnit EnemyWarlock;
EnemyWarlock warlock_new(Enemy* enemy, Level* level);
void warlock_behaviour(Enemy * enemy);

// bat
typedef struct EnemyUnit EnemyBat;
EnemyUnit bat_new(Enemy* enemy, Level* level);
void bat_behaviour(Enemy* enemy);

// rock
typedef struct EnemyUnit EnemyRock;
EnemyUnit rock_new(Enemy* enemy, Level* level);
void rock_behaviour(Enemy* enemy);