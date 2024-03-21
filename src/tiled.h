//
// Created by user on 20.01.2022.
//

#pragma once
#include "types.h"
#include "stdbool.h"
#include "stdint.h"

/**
 * Информация о тайле
 */
typedef struct TileData {
    /**
     * Ипсользовать 2BPP для изображения
     */
    bool isUse2BPP;
    /**
     * Используется ли горизонтальный поворот
     */
    bool flip_horizontal;
    /**
     * Используется ли вертикальный поворот
     */
     bool flip_vertical;
     /**
      * Используется ли диагональный поворот
      */
     bool flip_diagonal;
     bool collision;
     /**
      * id тайла
      */
      uint8_t id;
} TileData;

/**
 * Конструктор тайла
 * @param data gid
 * @return
 */
TileData tileData_new(uint8_t data);

void tileData_debug(TileData* tileData);

/**
 * Чанк уровня
 */
typedef struct TiledLevelChunk {
    /**
     * Позиция чанка по x
     */
    uint32_t x;
    /**
     * Позиция чанка по y
     */
    uint32_t y;
    /**
     * Тайлы чанка
     */
    TileData tiles [64];
} TiledLevelChunk;

void tiledLevelChunk_read(TiledLevelChunk* chunk, uint8_t x, uint8_t y);

void tiledLevelChunk_draw(TiledLevelChunk* chunk, ImagePool* imagePool);