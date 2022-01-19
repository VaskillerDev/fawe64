//
// Created by user on 20.01.2022.
//

#pragma once
#include "libs.h"

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

TileData tileData_new(int_32 data);

void tileData_debug(TileData* tileData);