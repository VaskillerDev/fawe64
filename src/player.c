#include "libs.h"

void player_move_left(Player *player)
{
    player->sprite->pos = vec2_add(player->sprite->pos, vec2_new(-1, 0));
}

void player_move_right(Player *player)
{
    player->sprite->pos = vec2_add(player->sprite->pos, vec2_new(1, 0));
}

void player_move_up(Player *player)
{
    player->sprite->pos = vec2_add(player->sprite->pos, vec2_new(0, -1));
}

void player_move_down(Player *player)
{
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