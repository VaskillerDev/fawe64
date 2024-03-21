//
// Created by user on 17.01.2022.
//
#pragma once
#include "types.h"
#include "stdlib.h"
#include "vec2.h"
#include "menu.h"

#define MAX_EVENTS 64

enum EventName {
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
};

/**
 * Пара ключ-значение
 */
struct EventKeyValue {
    enum EventName eventNameAsKey;
    void *lambdaRefAsValue;
};

/**
 * Эмиттер
 */
struct EventEmitter {
    /**
     * Контейнер с прослушиваемыми событиями
     */
    EventKeyValue events[MAX_EVENTS];
    /**
     * Кол-во прослушиваемых событий в текущий момент
     */
    int listeningEventCount;
};

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

struct CurrentOptionChangedEvent {
    GameState* gameState;
    MenuOptionType currentOption;
};

struct HpPointsChangedEvent {
    uint8_t id;
    uint8_t currentPoints;
    void* parent;
};

struct HpPointsOverEvent {
    uint8_t id;
    void* parent;
};

struct HpPointsFilledEvent {
    uint8_t id;
};

struct EnemyActionStateChangedEvent {
    Enemy* enemy;
    uint8_t state;
};

struct EnemySwordAttackHitEvent {
    Player* player;
    Sword* sword;
    Sprite* target;
};

struct PlayerAttackAnimationTimeoutEvent {
    uint8_t timeout;
    Player* player;
};

struct PlayerLevelChunkMovedEvent {
    Level* level;
    Vec2 startPosition;
};

struct EnemyAttackBulletEvent {
    Level* level;
    Enemy* enemy;
};

struct LevelEnemyAttackBulletEvent {
    Enemy* enemy;
    uint8_t lifetimeMs;
};

struct LevelBorderContactEvent {
    uint8_t direction; // 0 left 1 top 2 right 3 bottom
};

struct PlayerHasGotBulletCollisionEvent {
    uint8_t damage;
};

struct TimerExpiredEvent {
    uint8_t id;
    Timer* timer;
};

struct BoundingVolumeCollidedEvent {
    BoundingVolume *bv1;
    BoundingVolume *bv2;
};

struct PlayerEnterDungeonEvent {
    Vec2f startPosition;
};

struct EnemyHasGotBulletCollisionEvent {
    uint8_t damage;
    Enemy* enemy;
};