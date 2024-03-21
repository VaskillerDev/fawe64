//
// Created by stepaniuk on 21.01.2022.
//
#pragma once
#include "types.h"
#include "event.h"

#include "stdbool.h"
#include "stdlib.h"

struct Hp {

    uint8_t id;

    void* parent;

    EventEmitter emitter;
    /**
     * Текущее здоровье
     */
    uint8_t currentPoints;

    /**
     *  Максимальное здоровье
     */
     uint8_t maxPoints;

     bool swordResistance;
};

Hp hp_new(uint8_t id, void* parent, uint8_t maxPoints, uint8_t currentPoints, bool swordResistance);

/**
 * Отнять очки здоровья
 * @param points
 */
void hp_substract(Hp* hp, uint8_t points);

/**
 * Добавить очки здоровья
 * @param points
 */
void hp_add(Hp* hp, uint8_t points);