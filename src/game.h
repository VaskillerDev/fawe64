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
struct GameState gameState_new(void);

/**
 * Структура содержащая глобальное состояние игры
 */
typedef struct GameState {
    /**
     * Можно ли продолжить текущую игру
     */
    bool isCanContinue;
} GameState;

#endif //_GAME_H_
