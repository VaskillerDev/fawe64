#include "libs.h"
#include <math.h>

const uint_8 POITION_EFFECT = 5;

void usePoition()
{
    Player *player = player_getInstance();
    player->health.currentPoints += POITION_EFFECT;

    if (player->health.currentPoints > player->health.maxPoints)
    {
        player->health.currentPoints = player->health.maxPoints;
    }
}

bool setupBomb()
{
    Player *player = player_getInstance();

    Vec2 spawnPoint = player->sprite->position;

    switch (player->movementDirection)
    {
    case PlayerDir_Right:
        if (!player_checkTileCollision(player->sprite, player->level, vec2_new(1, 0)))
        {
            spawnPoint = vec2_add(spawnPoint, vec2_new(16, 0));
        }
        else
        {
            return false;
        }
        break;
    case PlayerDir_Left:
        if (!player_checkTileCollision(player->sprite, player->level, vec2_new(-1, 0)))
        {
            spawnPoint = vec2_add(spawnPoint, vec2_new(-16, 0));
        }
        else
        {
            return false;
        }
        break;
    case PlayerDir_Up:
        if (!player_checkTileCollision(player->sprite, player->level, vec2_new(0, -1)))
        {
            spawnPoint = vec2_add(spawnPoint, vec2_new(0, -16));
        }
        else
        {
            return false;
        }
        break;
    case PlayerDir_Bottom:
        if (!player_checkTileCollision(player->sprite, player->level, vec2_new(0, 1)))
        {
            spawnPoint = vec2_add(spawnPoint, vec2_new(0, 16));
        }
        else
        {
            return false;
        }
        break;

    default:
        return false;
    }

    Sprite *e = level_spawnObject(player->level);
    e->images = &player->level->imagePool->images[PoolIdx_Bomb];
    e->position = spawnPoint;
    e->imageCount = 1;
    e->currentImage = 0;
    e->size.x = player->level->imagePool->images[PoolIdx_Bomb]->width;
    e->size.y = player->level->imagePool->images[PoolIdx_Bomb]->height;
    e->currentImage = e->images[0];

    return true;
}