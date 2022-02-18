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

    E_ENEMY_ACTION_STATE_CHANGED = 30,
    E_SWORD_ATTACK_HIT = 31,
    E_PLAYER_ATTACK_ANIMATION_TIMEOUT = 32,
    E_LEVEL_CHUNK_MOVED = 33
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