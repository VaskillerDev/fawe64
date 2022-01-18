//
// Created by user on 17.01.2022.
//
#pragma once

#define MAX_EVENTS 64

typedef enum EventName {
    E_UNKNOWN = 0,
    // MENU: 1
    /**
     * В меню была выбрана опция
     */
    E_MENU_CURRENT_OPTION_CHANGED = 10
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
