#include "enemy.h"
#include "player.h"

Enemy *new_enemy(Level *level)
{
    Enemy *enemy = (Enemy *)malloc(sizeof(Enemy));
    enemy->level = level;
    enemy->health = hp_new(1, enemy, 10, 10);
    eventEmitter_on(&enemy->health.emitter, E_HP_POINTS_OVER, &enemy_death);

    return enemy;
}

void enemy_death(HpPointsOverEvent eData)
{
    Enemy *enemy = (Enemy *)eData.parent;
    trace("dead");
    level_deleteObject(enemy->level, enemy->sprite);
    level_deleteEnemy(enemy->level, enemy);
}

void enemy_update(Enemy *enemy)
{
    void (*tactics) () = enemy->tactics;
    tactics(enemy);

    if(enemy->delay > 0)
    {
         --enemy->delay;
         return;
    }

    if (enemy->movDist > 0)
    {
        if (!player_checkCollision(enemy->sprite, enemy->level, enemy->moveDir))
        {
            enemy->sprite->pos = vec2_add(enemy->sprite->pos, enemy->moveDir);
            --enemy->movDist;
        }
        else
            enemy->movDist = 0;
    }
}