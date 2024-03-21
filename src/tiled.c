//
// Created by user on 20.01.2022.
//
#include "tiled.h"
#include "image_pool.h"
#include "render.h"
#include "wasm4.h"
#include "assets.h"

TileData tileData_new (uint8_t data)
{
  bool fh = 0;
  bool fv = 0;
  bool fd = 0;
  uint8_t id = 0;

  if (data >= 100)
    { // есть horizontal
      fh = true;

      uint8_t f2 = (data - 100);
      uint8_t f2r = f2 / 10;

      if (f2r == 0) {
         fv = false;
          fd = false;
      }
      fv = f2r == 1;
      fd = f2r == 2;
      if (f2r == 3) {
        fv = true;
        fd = true;
      }

      id = (data - (100 + f2r * 10));
      goto returnTile;
    }

  if (data >= 10)
    { // есть (vertical,diagonal)
      uint8_t f2r = data / 10;
      fv = f2r == 1;
      fd = f2r == 2;
      if (f2r == 3) {
          fv = true;
          fd = true;
        }

      id = data - 10 * f2r;

      goto returnTile;
    }

  id = data;

  returnTile:
  {}

  struct TileData tileData = {
      .flip_horizontal = fh,
      .flip_vertical = fv,
      .flip_diagonal = fd,
      .id = id,
      .isUse2BPP = id == 0 || id == 1 || id == 4 || id == 6,
      .collision = id == 0 || id == 1 || id == 4 || id == 5
  };

  return tileData;
}

void tileData_debug (TileData *tileData)
{
  tracef ("flip_horizontal: %d", tileData->flip_horizontal);
  tracef ("flip_vertical: %d", tileData->flip_vertical);
  tracef ("id: %d", tileData->id);
}

void tiledLevelChunk_read (TiledLevelChunk* chunk, uint8_t x, uint8_t y)
{
  chunk->x = x;
  chunk->y = y;

  for (uint8_t i = 0; i < 64; i++)
    {
      uint8_t dataFromAssets = PLAIN_LEVEL[x][y][i];
      chunk->tiles[i] = tileData_new (dataFromAssets);
    }
  return;
}

void tiledLevelChunk_draw(TiledLevelChunk* chunk, ImagePool* imagePool)
{
  const uint8_t drawOffset = 16;
  uint8_t tileI = 0;

  for (uint8_t y = 0; y < 8 ; y++) {
    for (uint8_t x = 0; x < 8 ; x++) {

      TileData * data = &chunk->tiles[tileI];
      Image * img = NULL;


      if (data->id == 0) {
        img = imagePool_getImage (imagePool, PoolIdx_Tile0);
      } else if (data->id == 1) {
          img = imagePool_getImage (imagePool, PoolIdx_Tile1);
          img->colors[1] = (uint16_t)0;
          img->colors[0] = (uint16_t)4;
      } else if (data->id == 2) {
          img = imagePool_getImage (imagePool, PoolIdx_Tile2);
          img->colors[1] = (uint16_t)2;
      } else if (data->id == 3) {
          img = imagePool_getImage (imagePool, PoolIdx_Tile3);
          img->colors[1] = (uint16_t)2;
      } else if (data->id == 4) {
          img = imagePool_getImage (imagePool, PoolIdx_Tile4);
      } else if (data->id == 5) {
          img = imagePool_getImage (imagePool, PoolIdx_Tile5);
          img->colors[0] = (uint16_t)2;
          img->colors[1] = (uint16_t)1;
      } else if (data->id == 6) {
          img = imagePool_getImage (imagePool, PoolIdx_Tile6);
      } else if (data->id == 7) {
          tileI +=1; // ignore tile
          continue;
      }

      uint32_t flag = BLIT_1BPP;

      if (data->isUse2BPP == true) flag |= BLIT_2BPP;
      if (data->flip_vertical == true)  flag |= BLIT_FLIP_Y;
      if (data->flip_horizontal == true)  flag |= BLIT_FLIP_X;
      if (data->flip_diagonal == true)  flag |= BLIT_ROTATE;

      img->flags = flag;

      DrawImage (img, drawOffset + x * 16, drawOffset + y * 16);
      tileI +=1;
    }
  }

//chunk->tiles
}