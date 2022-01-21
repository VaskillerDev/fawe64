//
// Created by user on 20.01.2022.
//
#include "libs.h"

TileData tileData_new(uint_8 data) {
  bool fh = 0;
  bool fv = 0;
  uint_8 id = 0;

  if (data >= 100) { // есть horizontal
    fh = true;
    fv = (data - 100) >= 10;
    id = (data - (100 + fv * 10));
    goto returnTile;
  }

  if (data >= 10) { // есть vertical
    fv = 1;
    id = data - 10;

    goto returnTile;
  }

  id = data;

  returnTile:{}

  struct TileData tileData = {
      .flip_horizontal = fh,
      .flip_vertical = fv,
      .id = id
  };

  return tileData;
}

void tileData_debug(TileData* tileData) {
  tracef ("flip_horizontal: %d", tileData->flip_horizontal);
  tracef ("flip_vertical: %d", tileData->flip_vertical);
  tracef ("id: %d", tileData->id);
}

struct TiledLevelChunk tiledLevelChunk_read(uint_8 x, uint_8 y) {

  struct TiledLevelChunk chunk = {
      .x = x,
      .y = y
  };

  for (uint_8 i = 0; i < 64; i++) {
    TileData tile = tileData_new (PLAIN_LEVEL[x][y][i]);

    chunk.tiles[i] = &tile;
  }

  return chunk;
}