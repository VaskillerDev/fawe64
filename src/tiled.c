//
// Created by user on 20.01.2022.
//
#include "libs.h"

TileData tileData_new (uint_8 data)
{
  bool fh = 0;
  bool fv = 0;
  uint_8 id = 0;

  if (data >= 100)
    { // есть horizontal
      fh = true;
      fv = (data - 100) >= 10;
      id = (data - (100 + fv * 10));
      goto returnTile;
    }

  if (data >= 10)
    { // есть vertical
      fv = 1;
      id = data - 10;

      goto returnTile;
    }

  id = data;

  returnTile:
  {}

  struct TileData tileData = {
      .flip_horizontal = fh,
      .flip_vertical = fv,
      .id = id
  };

  return tileData;
}

void tileData_debug (TileData *tileData)
{
  tracef ("flip_horizontal: %d", tileData->flip_horizontal);
  tracef ("flip_vertical: %d", tileData->flip_vertical);
  tracef ("id: %d", tileData->id);
}

void tiledLevelChunk_read (TiledLevelChunk* chunk, uint_8 x, uint_8 y)
{
  chunk->x = x;
  chunk->y = y;

  for (uint_8 i = 0; i < 64; i++)
    {
      uint_8 dataFromAssets = PLAIN_LEVEL[x][y][i];
      chunk->tiles[i] = tileData_new (dataFromAssets);
    }
  return;
}

void tiledLevelChunk_draw(TiledLevelChunk* chunk, ImagePool* imagePool)
{

  //DrawImage (tile0Img, 0, 0, true);

  uint_8 tileI = 0;

  for (uint_8 y = 0; y < 8 ; y++) {
    for (uint_8 x = 0; x < 8 ; x++) {

      TileData * data = &chunk->tiles[tileI];
      Image * img = NULL;


      if (data->id == 0) {
        img = imagePool_getImage (imagePool, PoolIdx_Tile0);
      } else if (data->id == 1) {
          img = imagePool_getImage (imagePool, PoolIdx_Tile1);
      } else if (data->id == 2) {
          img = imagePool_getImage (imagePool, PoolIdx_Tile2);
      } else if (data->id == 3) {
          img = imagePool_getImage (imagePool, PoolIdx_Tile3);
      } else if (data->id == 4) {
          img = imagePool_getImage (imagePool, PoolIdx_Tile4);
      } else if (data->id == 5) {
          img = imagePool_getImage (imagePool, PoolIdx_Tile5);
      } else if (data->id == 6) {
          img = imagePool_getImage (imagePool, PoolIdx_Tile6);
      } else if (data->id == 7) {
          img = imagePool_getImage (imagePool, PoolIdx_Tile7);
      }

      /*if (data->flip_horizontal == true) {
        img->flags &= BLIT_FLIP_X;
      }

        if (data->flip_vertical == true) {
            img->flags &= BLIT_FLIP_Y;
        }*/

      DrawImage (img, x * 16, y * 16, true);
      tileI +=1;
    }
  }

//chunk->tiles
}