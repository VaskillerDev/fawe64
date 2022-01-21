#include"libs.h"

void imagePool_init(ImagePool *pool)
{
    pool->imageCount = 5;
    pool->data = malloc(sizeof(uint8_t) * (32 * 3 + 64 * 8 + 2560));
    pool->images = (Image **)malloc(sizeof(Image) * pool->imageCount);
    pool->offset = 0;

    *pool->images = imagePool_addImage(pool, (void*)menuImg, 2560, 160, 128, menuImgColors, BLIT_1BPP);
    *(pool->images + 1) = imagePool_addImage(pool,(void*) piligrim_idle_b_img_0, 64, 16, 16, menuImgColors, BLIT_2BPP);
    *(pool->images + 2) = imagePool_addImage(pool, (void*)piligrim_idle_b_img_1, 64, 16, 16, menuImgColors, BLIT_2BPP);
    *(pool->images + 3) = imagePool_addImage(pool, (void*)piligrim_idle_b_img_2, 64, 16, 16, menuImgColors, BLIT_2BPP);

    *(pool->images + 4) = imagePool_addImage (pool, (void*)tile0, 64, 16, 16, menuImgColors, BLIT_2BPP);
    *(pool->images + 5) = imagePool_addImage (pool, (void*)tile1, 64, 16, 16, menuImgColors, BLIT_2BPP);
    *(pool->images + 6) = imagePool_addImage (pool, (void*)tile2, 32, 16, 16, menuImgColors, BLIT_1BPP);
    *(pool->images + 7) = imagePool_addImage (pool, (void*)tile3, 32, 16, 16, menuImgColors, BLIT_1BPP);
    *(pool->images + 8) = imagePool_addImage (pool, (void*)tile4, 64, 16, 16, menuImgColors, BLIT_2BPP);
    *(pool->images + 9) = imagePool_addImage (pool, (void*)tile5, 32, 16, 16, menuImgColors, BLIT_1BPP);
    *(pool->images + 10) = imagePool_addImage (pool, (void*)tile6, 64, 16, 16, menuImgColors, BLIT_2BPP);
    *(pool->images + 11) = imagePool_addImage (pool, (void*)tile7, 64, 16, 16, menuImgColors, BLIT_2BPP);
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