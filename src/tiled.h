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
     * Используется ли горизонтальный поворот
     */
    bool flip_horizontal;
    /**
     * Используется ли вертикальный поворот
     */
     bool flip_vertical;
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
 * Тип уровня
 */
typedef enum LevelType {
    PLAIN,
    FOREST,
    DUNGEON
}LevelType;

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
    TileData *tiles [64];
} TiledLevelChunk;

struct TiledLevelChunk tiledLevelChunk_read(uint_8 x, uint_8 y);

