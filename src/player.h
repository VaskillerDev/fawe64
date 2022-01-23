#pragma once
#include "libs.h"

struct Player
{
    struct Sprite *sprite;
    Level *level;
    float speed;
    Vec2f speedDir;

    Hp health;
    Sword sword;
    EventEmitter emitter;

    GameState* gameState;
};

typedef struct Player Player;

Player player_new(Level *level, GameState* gameState);

bool player_checkCollision(struct Sprite *player, Level* level, Vec2 dir);
void player_move_left(Player *player);
void player_move_right(Player *player);
void player_move_up(Player *player);
void player_move_down(Player *player);

void player_update(Player *player, Level *level);

void player_death(HpPointsOverEvent eData);