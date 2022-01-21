#include "libs.h"
#include <math.h>
bool player_checkCollision(Player *player, Vec2 dir)
{
    Sprite **currentObject = NULL;
    while ((currentObject = (Sprite **)utarray_next(player->level->objects, currentObject)))
    {
        if (player->sprite != *currentObject)
            if (CheckCollision(&player->sprite->boundingVolume, &(*currentObject)->boundingVolume))
            {
                Vec2f rayDir = vec2_normalize(vec2_sub((*currentObject)->pos, player->sprite->pos));

                if (fabsf(rayDir.x) > fabsf(rayDir.y))
                    rayDir.y = 0;
                else
                    rayDir.x = 0;

                rayDir = vec2f_normalize(rayDir);
                if (vec2f_dot(rayDir, vec2f_fromVec2(dir)) > 0.00001)
                    return true;
            }
    }

    return false;
}

void player_move_left(Player *player)
{
    if (!player_checkCollision(player, vec2_new(-1, 0)))
        player->speedDir = vec2f_add(player->speedDir, vec2f_new(-1, 0));
}

void player_move_right(Player *player)
{
    if (!player_checkCollision(player, vec2_new(1, 0)))
        player->speedDir = vec2f_add(player->speedDir, vec2f_new(1, 0));
}

void player_move_up(Player *player)
{
    if (!player_checkCollision(player, vec2_new(0, -1)))
        player->speedDir = vec2f_add(player->speedDir, vec2f_new(0, -1));
}

void player_move_down(Player *player)
{
    if (!player_checkCollision(player, vec2_new(0, 1)))
        player->speedDir = vec2f_add(player->speedDir, vec2f_new(0, 1));
}

void player_update(Player *player)
{
    uint8_t gamepad = *GAMEPAD1;
    player->speedDir = vec2f_new(0, 0);

    if (gamepad & BUTTON_LEFT)
    {
        player_move_left(player);
    }
    if (gamepad & BUTTON_RIGHT)
    {
        player_move_right(player);
    }
    if (gamepad & BUTTON_DOWN)
    {
        player_move_down(player);
    }
    if (gamepad & BUTTON_UP)
    {
        player_move_up(player);
    }

    if (vec2f_getLength(player->speedDir) > 0)
    {
        player->speedDir = vec2f_normalize(player->speedDir);
        player->sprite->pos = vec2_add(player->sprite->pos, vec2_fromVec2f(vec2f_mul(player->speedDir, vec2f_new(player->speed, player->speed))));
    }
}