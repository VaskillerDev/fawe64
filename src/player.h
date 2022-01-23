#pragma once
#include "libs.h"

typedef enum PlayerMovementDirection {
    PlayerDir_Right,
    PlayerDir_Up,
    PlayerDirLeft,
    PlayerDir_Bottom
} PlayerMovementState;

typedef enum PlayerActionState {
    PlayerAction_Idle,
    PlayerAction_Go,
    PlayerAction_Attack
} PlayerActionState;

struct Player
{
    struct Sprite *sprite;

    Image* idleLeftFrames[3];
    Image* goLeftFrames[3];
    Image* idleRightFrames[3];
    Image* goRightFrames[3];
    Image* idleUpFrames[3];
    Image* goUpFrames[3];
    Image* idleBottomFrames[3];
    Image* goBottomFrames[3];


    Level *level;
    float speed;
    Vec2f speedDir;

    /**
     * Направление игрока
     */
    enum PlayerMovementDirection movementDirection;

    /**
     * Текущеее действие игрока
     */
    enum PlayerActionState actionState;

    Sword sword;
    EventEmitter emitter;
};

typedef struct Player Player;

Player player_new(Level *level);

bool player_checkCollision(struct Sprite *player, Level* level, Vec2 dir);
void player_move_left(Player *player);
void player_move_right(Player *player);
void player_move_up(Player *player);
void player_move_down(Player *player);

void player_update(Player *player, Level *level);
void player_draw(Player *player, Level *level);