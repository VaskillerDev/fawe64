// Код главного меню
// Created by user on 15.01.2022.
//
#pragma once
#include "stdbool.h"

/**
 * 
 * Дефолтный конструктор состояния меню
 * @return
 */
struct MenuState menuState_new (void);

/**
 * Обработка ввода
 * @param state
 */
void menu_processInput (struct MenuState *state, struct GameState *gameState);

/**
 * Отрисовать меню
 * @param state
 */
void menu_draw_logo (struct MenuState *state);

/**
 * Отрисовать меню
 * @param state
 */
void menu_draw_options (struct MenuState *state, bool isCanContinue);

/**
 *
 * @param imagePool
 */
void menu_setImagePool(MenuState* menu, ImagePool* imagePool);

/**
 * Опции меню
 */
enum MenuOptionType {
    CONTINUE_GAME = 1,
    NEW_GAME,
    SETTINGS,
    CREDITS
};

struct Sprite;

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

    ImagePool* imagePool;
   struct Sprite* logo;

} MenuState;

void menu_setEventEmitter (MenuState *state, EventEmitter *emitter);
