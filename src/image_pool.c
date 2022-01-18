#include "image_pool.h"
#include "assets.h"
#include <stdlib.h>
#include <string.h>

void imagePool_init(ImagePool *pool)
{
    pool->imageCount = 4;
    pool->data = malloc(sizeof(uint8_t) * (64 * 3 + 2560));
    pool->images = (Image **)malloc(sizeof(Image) * pool->imageCount);
    pool->offset = 0;

    *pool->images = imagePool_addImage(pool, (void*)menuImg, 2560, 160, 128, menuImgColors, BLIT_1BPP);
    *(pool->images + 1) = imagePool_addImage(pool,(void*) piligrim_idle_b_img_0, 64, 16, 16, menuImgColors, BLIT_2BPP);
    *(pool->images + 2) = imagePool_addImage(pool, (void*)piligrim_idle_b_img_1, 64, 16, 16, menuImgColors, BLIT_2BPP);
    *(pool->images + 3) = imagePool_addImage(pool, (void*)piligrim_idle_b_img_2, 64, 16, 16, menuImgColors, BLIT_2BPP);
}

Image *imagePool_addImage(ImagePool *pool, void *dataPtr, uint_32 size, uint_32 w, uint_32 h, uint_16 colors[4], uint_32 flags)
{
    void* newImageDataPtr = (uint_8*)pool->data + pool->offset;
    memcpy(newImageDataPtr, dataPtr, size);
    pool->offset += size;

    return image_new(newImageDataPtr, w, h, colors, flags);
}

Image* imagePool_getImage(ImagePool* pool,uint_32 index)
{
    return *(pool->images + index);
}