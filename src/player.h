#pragma once
#include "libs.h"

typedef enum PlayerMovementDirection {
    PlayerDir_Right,
    PlayerDir_Up,
    PlayerDir_Left,
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

    Image* attackUp[3];
    Image* attackBottom[3];
    Image* attackLeft[3];
    Image* attackRight[3];

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

    Hp health;

    Sword sword;
    EventEmitter emitter;

    GameState* gameState;

    uint_8 attackAnimationTimeout;
};

typedef struct Player Player;

/**
 * Сигнатура взятия инстанса игрока при первом создании
 */
typedef struct PlayerInitInstanceArgs {
    Level* level;
    GameState* gameState;
    Vec2 spawnPosition;
} PlayerInitInstanceArgs;

Player player_new(Level *level, GameState* gameState, Vec2 spawnPosition);


void player_removeInstance();

/**
 * Получить инстанс игрока
 * @return
 */
Player* player_getInstance();
/**
 * Инициализировать инстанс игрока на старте
 * @param args
 * @return
 */
Player* player_initInstance(PlayerInitInstanceArgs args);

bool player_checkCollision(struct Sprite *player, Level* level, Vec2 dir);
void player_move_left(Player *player);
void player_move_right(Player *player);
void player_move_up(Player *player);
void player_move_down(Player *player);

void player_update(Player *player, Level *level);
void player_draw(Player *player, Level *level);
void player_postUpdate(Player *player);
void on_player_death(HpPointsOverEvent eData);
void on_player_attack(EnemySwordAttackHitEvent e);
void on_player_attack_animation_timeout(PlayerAttackAnimationTimeoutEvent* e);
void on_player_level_chunk_moved(PlayerLevelChunkMovedEvent* e);