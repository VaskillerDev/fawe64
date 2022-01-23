#pragma once
#include"enemy.h"

struct EnemyType_1
{
    Enemy* enemy;
};

typedef struct EnemyType_1 EnemyType_1;

EnemyType_1 EnemyType_1_new(Enemy* enemy, Level* level);

void EnemyTactics_1(Enemy* enemy);