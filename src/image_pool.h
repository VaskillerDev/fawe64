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
    PoolIdx_Tile7,

    PoolIdx_PiligrimGoBottom0,
    PoolIdx_PiligrimGoBottom1,
    PoolIdx_PiligrimGoBottom2,

    PoolIdx_PiligrimAttackBottom,

    PoolIdx_PiligrimIdleLeft0,
    PoolIdx_PiligrimIdleLeft1,
    PoolIdx_PiligrimIdleLeft2,

    PoolIdx_PiligrimGoLeft0,
    PoolIdx_PiligrimGoLeft1,
    PoolIdx_PiligrimGoLeft2,

    PoolIdx_PiligrimAttackLeft,

    PoolIdx_PiligrimIdleRight0,
    PoolIdx_PiligrimIdleRight1,
    PoolIdx_PiligrimIdleRight2,

    PoolIdx_PiligrimGoRight0,
    PoolIdx_PiligrimGoRight1,
    PoolIdx_PiligrimGoRight2,

    PoolIdx_PiligrimAttackRight,

    PoolIdx_PiligrimIdleUp0,
    PoolIdx_PiligrimIdleUp1,
    PoolIdx_PiligrimIdleUp2,

    PoolIdx_PiligrimGoUp0,
    PoolIdx_PiligrimGoUp1,
    PoolIdx_PiligrimGoUp2,

    PoolIdx_PiligrimAttackUp,

    PoolIdx_SwordBottom,
    PoolIdx_SwordLeft,
    PoolIdx_SwordRight,
    PoolIdx_SwordUp,

    PoolIdx_Enemy0Go0,
    PoolIdx_Enemy0Go1,
    PoolIdx_Enemy0Go2,
    PoolIdx_Enemy0Attack,

    PoolIdx_Enemy1Go0,
    PoolIdx_Enemy1Go1,
    PoolIdx_Enemy1Go2,

} ImagePoolIndex;

void imagePool_init(ImagePool* pool);
Image* imagePool_addImage(ImagePool* pool, void* dataPtr, uint_32 size, uint_32 w, uint_32 h, uint_16 colors[4], uint_32 flags);
Image* imagePool_getImage(ImagePool* pool, uint_32 index);