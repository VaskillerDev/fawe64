//
// Created by user on 20.01.2022.
//
#include "libs.h"

TileData tileData_new(int_32 data) {
  bool fh = (data & TLD_FLIPPED_HORIZONTALLY_FLAG);
  bool fv = (data & TLD_FLIPPED_VERTICALLY_FLAG);

  uint_8 id = data & TLD_FLAGS;

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