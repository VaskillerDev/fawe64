// Код главного меню
// Created by user on 15.01.2022.
//
#ifndef FAWE64_MENU_H
#define FAWE64_MENU_H
#include "libs.h"
/**
 * Дефолтный конструктор состояния меню
 * @return
 */
struct MenuState menuState_new (void);

/**
 * Обработка ввода
 * @param state
 */
void menu_processInput (struct MenuState *state);

/**
 * Отрисовать меню
 * @param state
 */
void menu_draw_logo (struct MenuState *state);

/**
 * Отрисовать меню
 * @param state
 */
void menu_draw_options (struct MenuState *state, struct GameState *gameState);

/**
 * Опции меню
 */
typedef enum {
    CONTINUE_GAME = 1,
    NEW_GAME,
    SETTINGS,
    CREDITS
} MenuOptionType;

/**
 * Состояние меню
 */
typedef struct MenuState {
    /**
     * Позиция логотипа
     */
    uint8_t logoYPos;
    /**
     * Можно ли отрисовать само меню
     */
    bool isDraw;
    /**
     * Текущая опция
     */
    MenuOptionType currentOption;

    /**
     * Эмиттер событий
     */
    EventEmitter *emitter;
} MenuState;

void menu_setEventEmitter (MenuState *state, EventEmitter *emitter);

#endif //FAWE64_MENU_H
