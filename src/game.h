// Код состояний игры
// Хранит все промежуточные состояния, настройки игры, прогресс
// Created by user on 15.01.2022.
//
#ifndef _GAME_H_
#define _GAME_H_

/**
 * Конструктор состояния игры
 * @return
 */
struct GameState gameState_new (void);

/**
 * Игровая вкладка.
 * Под вкладкой понимается то, где находится игрок.
 * К примеру: находясь на уровне мы находимся в IN_GAME_LEVEL,
 * но если откроем главное меню, то перейдем в IN_MENU
 */
typedef enum InGameTab {
    /**
     * Неизвестно
     */
    UNKNOWN = -1,
    /**
     * Мы находимся на уровне
     */
    IN_GAME_LEVEL,
    /**
     * Мы в игровом инвенторе
     */
    IN_GAME_INVENTORY,
    /**
     * Мы в главном меню
     */
    IN_MENU
} InGameTab;

/**
 * Структура содержащая глобальное состояние игры
 */
typedef struct GameState {
    /**
     * Можно ли продолжить текущую игру
     */
    bool isCanContinue;
    /**
     * Текущая игровая вкладка
     */
    InGameTab currentTab;

    EventEmitter *emitter;
} GameState;

void game_setEventEmitter (GameState *state, EventEmitter *emitter);

#endif //_GAME_H_
