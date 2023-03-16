//
// Created by user on 17.01.2022.
//
#pragma once
#include "libs.h"
#define MAX_EVENTS 64

typedef enum EventName {
    E_UNKNOWN = 0,
    // MENU: 1
    /**
     * В меню была выбрана опция
     */
    E_MENU_CURRENT_OPTION_CHANGED = 10,

    E_HP_POINTS_CHANGED = 20,
    E_HP_POINTS_FILLED  = 21,
    E_HP_POINTS_OVER    = 22,

    E_BOUNDING_VOLUME_COLLIDED = 23,
    E_ENEMY_ACTION_STATE_CHANGED = 30,
    E_ENEMY_ATTACK_BULLET = 31,
    E_ENEMY_HAS_GOT_BULLET_COLLISION = 32,
    E_SWORD_ATTACK_HIT = 33,
    E_PLAYER_ATTACK_ANIMATION_TIMEOUT = 34,
    E_PLAYER_HAS_GOT_BULLET_COLLISION = 35,
    E_PLAYER_ENTER_DUNGEON = 36,
    E_PLAYER_LEAVE_DUNGEON = 37,
    E_LEVEL_BORDER_CONTACT = 38,
    E_LEVEL_CHUNK_MOVED = 39,
    E_TIMER_EXPIRED = 40
} EventName;

/**
 * Пара ключ-значение
 */
typedef struct EventKeyValue {
    enum EventName eventNameAsKey;
    void *lambdaRefAsValue;
} EventKeyValue;

/**
 * Эмиттер
 */
typedef struct EventEmitter {
    /**
     * Контейнер с прослушиваемыми событиями
     */
    EventKeyValue events[MAX_EVENTS];
    /**
     * Кол-во прослушиваемых событий в текущий момент
     */
    int listeningEventCount;
} EventEmitter;

EventEmitter eventEmitter_new (void);

/**
 * Подписаться на событие
 * @param emitter
 * @param name
 * @param lambda
 */
void eventEmitter_on (EventEmitter *emitter, enum EventName name, void *lambda);

/**
 * Оповестить о событии
 * @param emitter
 * @param name
 * @param args
 */
void eventEmitter_emit (EventEmitter *emitter, enum EventName name, void *args);

typedef struct CurrentOptionChangedEvent {
    GameState* gameState;
    MenuOptionType currentOption;
} CurrentOptionChangedEvent;

typedef struct HpPointsChangedEvent {
    uint8_t id;
    uint8_t currentPoints;
    void* parent;
} HpPointsChangedEvent;

typedef struct HpPointsOverEvent {
    uint8_t id;
    void* parent;
} HpPointsOverEvent;

typedef struct HpPointsFilledEvent {
    uint8_t id;
} HpPointsFilledEvent;

typedef struct EnemyActionStateChangedEvent {
    Enemy* enemy;
    uint_8 state;
} EnemyActionStateChangedEvent;

typedef struct EnemySwordAttackHitEvent {
    Player* player;
    Sword* sword;
    Sprite* target;
} EnemySwordAttackHitEvent;

typedef struct PlayerAttackAnimationTimeoutEvent {
    uint_8 timeout;
    Player* player;
} PlayerAttackAnimationTimeoutEvent;

typedef struct PlayerLevelChunkMovedEvent {
    Level* level;
    Vec2 startPosition;
} PlayerLevelChunkMovedEvent;

typedef struct EnemyAttackBulletEvent {
    Level* level;
    Enemy* enemy;
} EnemyAttackBulletEvent;

typedef struct LevelEnemyAttackBulletEvent {
    Enemy* enemy;
    uint_8 lifetimeMs;
} LevelEnemyAttackBulletEvent;

typedef struct LevelBorderContactEvent {
    uint_8 direction; // 0 left 1 top 2 right 3 bottom
} LevelBorderContactEvent;

typedef struct PlayerHasGotBulletCollisionEvent {
    uint_8 damage;
} PlayerHasGotBulletCollisionEvent;

typedef struct TimerExpiredEvent {
    uint_8 id;
    Timer* timer;
} TimerExpiredEvent;

typedef struct BoundingVolumeCollidedEvent {
    BoundingVolume *bv1;
    BoundingVolume *bv2;
} BoundingVolumeCollidedEvent;

typedef struct PlayerEnterDungeonEvent {
    Vec2f startPosition;
}PlayerEnterDungeonEvent;

typedef struct EnemyHasGotBulletCollisionEvent {
    uint_8 damage;
    Enemy* enemy;
} EnemyHasGotBulletCollisionEvent;