#pragma once
#include"libs.h"

struct ImagePool
{
    void* data;
    Image** images;
    uint_32 imageCount;
    uint_32 offset;
};

/**
 * Индексы изображений в пуле изображений
 */
typedef enum ImagePoolIndex {
    PoolIdx_MenuImage,

    PoolIdx_PiligrimIdleBottom0,
    PoolIdx_PiligrimIdleBottom1,
    PoolIdx_PiligrimIdleBottom2,

    PoolIdx_Tile0,
    PoolIdx_Tile1,
    PoolIdx_Tile2,
    PoolIdx_Tile3,
    PoolIdx_Tile4,
    PoolIdx_Tile5,
    PoolIdx_Tile6,
    PoolIdx_Tile7
} ImagePoolIndex;

void imagePool_init(ImagePool* pool);
Image* imagePool_addImage(ImagePool* pool, void* dataPtr, uint_32 size, uint_32 w, uint_32 h, uint_16 colors[4], uint_32 flags);
Image* imagePool_getImage(ImagePool* pool, uint_32 index);