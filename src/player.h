#pragma once
#include "libs.h"

struct Player
{
    Sprite* sprite;
    Level* level;
    float speed;
    Vec2f speedDir;

    Sword sword;
    Hp heath;
    EventEmitter emitter;
};

typedef struct Player Player;


Player player_new(Level* level);

bool player_checkCollision(Player* player, Vec2 dir);
void player_move_left(Player* player);
void player_move_right(Player* player);
void player_move_up(Player* player);
void player_move_down(Player* player);

void player_update(Player* player);