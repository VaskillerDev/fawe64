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
                tracef("%f;%f \n", rayDir.x, rayDir.y);
                 tracef("%f;%f \n", vec2f_fromVec2(dir).x, vec2f_fromVec2(dir).y);
                tracef("%f \n", vec2f_dot(rayDir, vec2f_fromVec2(dir)));
                if (vec2f_dot(rayDir, vec2f_fromVec2(dir)) > 0.00001)
                    return true;
            }
    }

    return false;
}

void player_move_left(Player *player)
{
    if (!player_checkCollision(player, vec2_new(-1, 0)))
        player->sprite->pos = vec2_add(player->sprite->pos, vec2_new(-1, 0));
}

void player_move_right(Player *player)
{
    if (!player_checkCollision(player, vec2_new(1, 0)))
        player->sprite->pos = vec2_add(player->sprite->pos, vec2_new(1, 0));
}

void player_move_up(Player *player)
{
    if (!player_checkCollision(player, vec2_new(0, -1)))
        player->sprite->pos = vec2_add(player->sprite->pos, vec2_new(0, -1));
}

void player_move_down(Player *player)
{
    if (!player_checkCollision(player, vec2_new(0, 1)))
        player->sprite->pos = vec2_add(player->sprite->pos, vec2_new(0, 1));
}

void player_update(Player *player)
{
    uint8_t gamepad = *GAMEPAD1;

    if (gamepad & BUTTON_LEFT)
    {
        player_move_left(player);
    }
    else if (gamepad & BUTTON_RIGHT)
    {
        player_move_right(player);
    }
    else if (gamepad & BUTTON_DOWN)
    {
        player_move_down(player);
    }
    else if (gamepad & BUTTON_UP)
    {
        player_move_up(player);
    }
}