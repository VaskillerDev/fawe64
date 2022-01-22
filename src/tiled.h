//
// Created by user on 20.01.2022.
//

#pragma once
#include "libs.h"

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
     /**
      * id тайла
      */
      uint_8 id;
} TileData;

/**
 * Конструктор тайла
 * @param data gid
 * @return
 */
TileData tileData_new(uint_8 data);

void tileData_debug(TileData* tileData);

/**
 * Чанк уровня
 */
typedef struct TiledLevelChunk {
    /**
     * Позиция чанка по x
     */
    uint_32 x;
    /**
     * Позиция чанка по y
     */
    uint_32 y;
    /**
     * Тайлы чанка
     */
    TileData tiles [64];
} TiledLevelChunk;

void tiledLevelChunk_read(TiledLevelChunk* chunk, uint_8 x, uint_8 y);

void tiledLevelChunk_draw(TiledLevelChunk* chunk, ImagePool* imagePool);