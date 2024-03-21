#pragma once
#include "sword.h"
#include "types.h"
#include "vec2.h"
#include "hp.h"
#include "image.h"
#include "timer.h"

enum PlayerMovementDirection {
    PlayerDir_Right,
    PlayerDir_Up,
    PlayerDir_Left,
    PlayerDir_Bottom
};

enum PlayerActionState {
    PlayerAction_Idle,
    PlayerAction_Go,
    PlayerAction_Attack
};

enum PlayerItemType
{
    PlayerItem_Potion,
    PlayerItem_Bomb,
    PlayerItem_DirectBomb,
    PlayerItem_Count
};

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
    Timer collisionBulletTimer;
    EventEmitter emitter;

    GameState* gameState;

    uint8_t attackAnimationTimeout;

    uint8_t itemsCount[PlayerItem_Count];
    Image* itemImages[PlayerItem_Count];
    uint8_t selectorIndex;
};

/**
 * Сигнатура взятия инстанса игрока при первом создании
 */
struct PlayerInitInstanceArgs {
    Level* level;
    GameState* gameState;
    Vec2 spawnPosition;
};

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

bool player_checkTileCollision(Sprite *player, Level *level, Vec2 dir);
bool player_checkCollision(struct Sprite *player, Level* level, Vec2 dir);
void player_move_left(Player *player);
void player_move_right(Player *player);
void player_move_up(Player *player);
void player_move_down(Player *player);

void player_update(Player *player, Level *level);
void player_draw(Player *player, Level *level);
void player_postUpdate(Player *player);
void player_useItem();
void on_player_death(HpPointsOverEvent* e);
void on_player_attack(EnemySwordAttackHitEvent e);
void on_player_attack_animation_timeout(PlayerAttackAnimationTimeoutEvent* e);
void on_player_level_chunk_moved(PlayerLevelChunkMovedEvent* e);
void on_player_has_got_bullet_collision(PlayerHasGotBulletCollisionEvent* e);
void on_player_enter_dungeon(PlayerEnterDungeonEvent* e);
void on_collision_bullet_timer_expired(TimerExpiredEvent* e);