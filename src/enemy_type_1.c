#include "enemy_type_1.h"

#define RANDOMIZE(a, b) (a) + ((float)rand() / (float)RAND_MAX * (b - a))

EnemyType_1 EnemyType_1_new(Enemy *enemy, Level *level)
{
    enemy->sprite = level_spawnObject(level);
    enemy->sprite->health = &enemy->health;

    Image *frames[3] = {
        imagePool_getImage(level->imagePool, PoolIdx_PiligrimIdleBottom0),
        imagePool_getImage(level->imagePool, PoolIdx_PiligrimIdleBottom1),
        imagePool_getImage(level->imagePool, PoolIdx_PiligrimIdleBottom2)};

    sprite_animated_init(enemy->sprite, frames, 3, 10);
    sprite_initBoundingVolume(enemy->sprite, BOX);
    enemy->sprite->pos = vec2_new(80, 100);

    EnemyType_1 newEnemy;
    newEnemy.enemy = enemy;
    newEnemy.enemy->tactics = &EnemyTactics_1;
    return newEnemy;
}

void EnemyTactics_1(Enemy *enemy)
{
    if (enemy->movDist == 0)
    {
        enemy->delay = 120;
        enemy->movDist = RANDOMIZE(20, 30);

        uint_32 dir = RANDOMIZE(1, 4);

        if (dir == 1)
            enemy->moveDir = vec2_new(0, -1);
        if (dir == 2)
            enemy->moveDir = vec2_new(0, 1);
        if (dir == 3)
            enemy->moveDir = vec2_new(-1, 0);
        if (dir == 4)
            enemy->moveDir = vec2_new(1, 0);
    }
}