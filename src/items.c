#include "libs.h"
#include <math.h>

const uint_8 POITION_EFFECT = 5;

Bomb bomb_new(Level *level, Vec2 spawnPoint)
{
    Sprite *sprite = level_spawnObject(level);
    sprite->useCustomColors = true;
    sprite->images = &level->imagePool->images[PoolIdx_Bomb];
    memcpy(sprite->colors, sprite->images[0]->colors, sizeof(uint_16) * 4);
    sprite->position = spawnPoint;
    sprite->imageCount = 1;
    sprite->currentImage = 0;
    sprite->size.x = level->imagePool->images[PoolIdx_Bomb]->width;
    sprite->size.y = level->imagePool->images[PoolIdx_Bomb]->height;
    sprite->currentImage = sprite->images[0];

    Bomb bomb =
        {
            .sprite = sprite,
            .timer = timer_new(120, false),
            .directionalExplosion = false};

    timer_start(&bomb.timer);

    return bomb;
}

bool bomb_isEmpty(Bomb *bomb)
{
    return bomb->sprite == NULL;
}

void bomb_update(Level *level, Bomb *bomb)
{
    timer_update(&bomb->timer);

    if (timer_isOut(&bomb->timer))
    {
        Vec2 bombPos = bomb->sprite->position;
        bombPos.x += 8;
        bombPos.y += 8;

        Enemy **currentObject = NULL;
    BOOM:
        currentObject = NULL;
        while ((currentObject = (Enemy **)utarray_next(level->enemies, currentObject)))
        {
            Vec2 enemyPosition = (*currentObject)->sprite->position;
            enemyPosition.x += 8;
            enemyPosition.y += 8;

            Vec2 dir = vec2_fromPoints(bombPos, enemyPosition);
            float distance = vec2_getLength(dir);
            if (distance <= 32)
            {
                hp_substract(&(*currentObject)->health, 1);
                level_addDestroyedRock(level, enemyPosition);
                goto BOOM;
            }
        }

        level_deleteObject(level, bomb->sprite);
        bomb->sprite = NULL;
        tone(100, 2 | (50 << 8), 40, TONE_NOISE | TONE_MODE2);
    }
}

Bomb directedBomb_new(Level *level, Vec2 spawnPoint)
{
    Sprite *sprite = level_spawnObject(level);
    sprite->position = spawnPoint;

    Bomb bomb =
        {
            .sprite = sprite,
            .timer = timer_new(1, false),
            .directionalExplosion = true};

    timer_start(&bomb.timer);

    return bomb;
}

void directedBomb_update(Level *level, Bomb *bomb)
{
    timer_update(&bomb->timer);

    if (timer_isOut(&bomb->timer))
    {
        Vec2 bombPos = bomb->sprite->position;
        bombPos.x += 8;
        bombPos.y += 8;

        Enemy **currentObject = NULL;
    BOOM:
        currentObject = NULL;
        while ((currentObject = (Enemy **)utarray_next(level->enemies, currentObject)))
        {
            Vec2 enemyPosition = (*currentObject)->sprite->position;
            enemyPosition.x += 8;
            enemyPosition.y += 8;

            Vec2 dir = vec2_fromPoints(bombPos, enemyPosition);
            float distance = vec2_getLength(dir);
            if (distance <= 8)
            {
                hp_substract(&(*currentObject)->health, 1);
                level_addDestroyedRock(level, enemyPosition);
                goto BOOM;
            }
        }

        level_deleteObject(level, bomb->sprite);
        bomb->sprite = NULL;
        tone(125, 2 | (50 << 8), 40, TONE_NOISE | TONE_MODE2);
    }
}

BombManager bombManager_new()
{
    BombManager bombManager;
    int len = (sizeof(bombManager.bombs) / sizeof(Bomb)) - 1;

    for (int i = 0; i < len; ++i)
    {
        bombManager.bombs[i].sprite = NULL;
        timer_reload(&bombManager.bombs[i].timer);
    }

    return bombManager;
}

void bombManager_addBomb(Level *level, Vec2 position, bool directed)
{
    int len = (sizeof(level->bombManager.bombs) / sizeof(Bomb)) - 1;
    if (len <= 0)
        return;

    for (int i = 0; i < len; i++)
    {
        Bomb *bomb = &level->bombManager.bombs[i];

        if (bomb_isEmpty(bomb))
        {
            if (directed)
            {
                *bomb = directedBomb_new(level, position);
            }
            else
            {
                *bomb = bomb_new(level, position);
            }
            break;
        }
    }
}

void bombManager_update(Level *level, BombManager *bombManager)
{
    int len = (sizeof(bombManager->bombs) / sizeof(Bomb)) - 1;
    if (len <= 0)
        return;

    for (int i = 0; i < len; i++)
    {
        Bomb *bomb = &bombManager->bombs[i];

        if (bomb_isEmpty(bomb))
            continue;

        if(bomb->timer.time % (3 + bomb->timer.time / 16) == 0)
        {
            uint_16 t = bomb->sprite->colors[0];
            bomb->sprite->colors[0] = bomb->sprite->colors[1];
            bomb->sprite->colors[1] = t;
        }

        if (bomb->directionalExplosion)
        {
            directedBomb_update(level, bomb);
        }
        else
        {
            bomb_update(level, bomb);
        }
    }
}

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

    bombManager_addBomb(player->level, spawnPoint, false);

    return true;
}

bool setupDirectedBomb()
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

    bombManager_addBomb(player->level, spawnPoint, true);

    return true;
}