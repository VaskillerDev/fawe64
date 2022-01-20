#pragma once
#include "libs.h"

struct Player
{
    Sprite* sprite;
    Level* level;
    float speed;
};

typedef struct Player Player;

bool player_checkCollision(Player* player, Vec2 dir);
void player_move_left(Player* player);
void player_move_right(Player* player);
void player_move_up(Player* player);
void player_move_down(Player* player);

void player_update(Player* player);