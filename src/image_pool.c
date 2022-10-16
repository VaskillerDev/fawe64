#include"libs.h"
#include "allocator.h"

void imagePool_init(ImagePool *pool)
{
    pool->imageCount = 50;
    pool->data = allocate(sizeof(uint8_t) * (32 * 7 + 64 * 43 + 2560));
    pool->images = (Image **)allocate(sizeof(Image) * pool->imageCount);
    pool->offset = 0;

    *pool->images = imagePool_addImage(pool, (void*)menuImg, 2560, 160, 128, menuImgColors, BLIT_1BPP);
    *(pool->images + 1) = imagePool_addImage(pool,(void*) piligrim_idle_b_img_0, 64, 16, 16, menuImgColors, BLIT_2BPP);
    *(pool->images + 2) = imagePool_addImage(pool, (void*)piligrim_idle_b_img_1, 64, 16, 16, menuImgColors, BLIT_2BPP);
    *(pool->images + 3) = imagePool_addImage(pool, (void*)piligrim_idle_b_img_2, 64, 16, 16, menuImgColors, BLIT_2BPP);

    *(pool->images + 4) = imagePool_addImage (pool, (void*)tile0, 64, 16, 16, menuImgColors, BLIT_2BPP);
    *(pool->images + 5) = imagePool_addImage (pool, (void*)tile1, 64, 16, 16, menuImgColors, BLIT_2BPP);
    *(pool->images + 6) = imagePool_addImage (pool, (void*)tile2, 32, 16, 16, menuImgColors, BLIT_1BPP);
    *(pool->images + 7) = imagePool_addImage (pool, (void*)tile3, 32, 16, 16, menuImgColors, BLIT_1BPP);
    *(pool->images + 8) = imagePool_addImage (pool, (void*)tile4, 64, 16, 16, tile4Colors, BLIT_1BPP);
    *(pool->images + 9) = imagePool_addImage (pool, (void*)tile5, 32, 16, 16, menuImgColors, BLIT_1BPP);
    *(pool->images + 10) = imagePool_addImage (pool, (void*)tile6, 64, 16, 16, menuImgColors, BLIT_2BPP);
    *(pool->images + 11) = imagePool_addImage (pool, (void*)tile7, 64, 16, 16, menuImgColors, BLIT_2BPP);

    *(pool->images + 12) = imagePool_addImage (pool, (void*)piligrim_go_b_img_0, 64, 16, 16, menuImgColors, BLIT_2BPP);
    *(pool->images + 13) = imagePool_addImage (pool, (void*)piligrim_go_b_img_1, 64, 16, 16, menuImgColors, BLIT_2BPP);
    *(pool->images + 14) = imagePool_addImage (pool, (void*)piligrim_go_b_img_2, 64, 16, 16, menuImgColors, BLIT_2BPP);

  *(pool->images + 15) = imagePool_addImage (pool, (void*)piligrim_attack_b_img, 64, 16, 16, menuImgColors, BLIT_2BPP);

  *(pool->images + 16) = imagePool_addImage (pool, (void*)pligrim_idle_l_img_0, 64, 16, 16, pliligrimLeftColors, BLIT_2BPP);
  *(pool->images + 17) = imagePool_addImage (pool, (void*)pligrim_idle_l_img_1, 64, 16, 16, pliligrimLeftColors, BLIT_2BPP);
  *(pool->images + 18) = imagePool_addImage (pool, (void*)pligrim_idle_l_img_2, 64, 16, 16, pliligrimLeftColors, BLIT_2BPP);

  *(pool->images + 19) = imagePool_addImage (pool, (void*)pligrim_go_l_img_0, 64, 16, 16, pliligrimLeftColors, BLIT_2BPP);
  *(pool->images + 20) = imagePool_addImage (pool, (void*)pligrim_go_l_img_1, 64, 16, 16, pliligrimLeftColors, BLIT_2BPP);
  *(pool->images + 21) = imagePool_addImage (pool, (void*)pligrim_go_l_img_2, 64, 16, 16, pliligrimLeftColors, BLIT_2BPP);

  *(pool->images + 22) = imagePool_addImage (pool, (void*)piligrim_attack_l_img, 64, 16, 16, pliligrimLeftColors, BLIT_2BPP);

  *(pool->images + 23) = imagePool_addImage (pool, (void*)piligrim_idle_r_img_0, 64, 16, 16, menuImgColors, BLIT_2BPP);
  *(pool->images + 24) = imagePool_addImage (pool, (void*)piligrim_idle_r_img_1, 64, 16, 16, menuImgColors, BLIT_2BPP);
  *(pool->images + 25) = imagePool_addImage (pool, (void*)piligrim_idle_r_img_2, 64, 16, 16, menuImgColors, BLIT_2BPP);

  *(pool->images + 26) = imagePool_addImage (pool, (void*)piligrim_go_r_img_0, 64, 16, 16, menuImgColors, BLIT_2BPP);
  *(pool->images + 27) = imagePool_addImage (pool, (void*)piligrim_go_r_img_1, 64, 16, 16, menuImgColors, BLIT_2BPP);
  *(pool->images + 28) = imagePool_addImage (pool, (void*)piligrim_go_r_img_2, 64, 16, 16, menuImgColors, BLIT_2BPP);

  *(pool->images + 29) = imagePool_addImage (pool, (void*)piligrim_attack_r_img, 64, 16, 16, menuImgColors, BLIT_2BPP);

  *(pool->images + 30) = imagePool_addImage (pool, (void*)piligrim_idle_u_img_0, 64, 16, 16, menuImgColors, BLIT_2BPP);
  *(pool->images + 31) = imagePool_addImage (pool, (void*)piligrim_idle_u_img_1, 64, 16, 16, menuImgColors, BLIT_2BPP);
  *(pool->images + 32) = imagePool_addImage (pool, (void*)piligrim_idle_u_img_2, 64, 16, 16, menuImgColors, BLIT_2BPP);

  *(pool->images + 33) = imagePool_addImage (pool, (void*)piligrim_go_u_img_0, 64, 16, 16, menuImgColors, BLIT_2BPP);
  *(pool->images + 34) = imagePool_addImage (pool, (void*)piligrim_go_u_img_1, 64, 16, 16, menuImgColors, BLIT_2BPP);
  *(pool->images + 35) = imagePool_addImage (pool, (void*)piligrim_go_u_img_2, 64, 16, 16, menuImgColors, BLIT_2BPP);

  *(pool->images + 36) = imagePool_addImage (pool, (void*)piligrim_attack_u_img, 64, 16, 16, pliligrimUpAttackColors, BLIT_2BPP);

  *(pool->images + 37) = imagePool_addImage (pool, (void*)sword_b_img, 32, 16, 16, menuImgColors, BLIT_1BPP);
  *(pool->images + 38) = imagePool_addImage (pool, (void*)sword_lr_img, 32, 16, 16, menuImgColors, BLIT_1BPP);
  *(pool->images + 39) = imagePool_addImage (pool, (void*)sword_lr_img, 32, 16, 16, menuImgColors, BLIT_1BPP | BLIT_FLIP_X);
  *(pool->images + 40) = imagePool_addImage (pool, (void*)sword_u_img, 32, 16, 16, menuImgColors, BLIT_1BPP);

  *(pool->images + 41) = imagePool_addImage (pool, (void*)enmy0_go_img_0, 64, 16, 16, enemy0ImgColors, BLIT_2BPP);
  *(pool->images + 42) = imagePool_addImage (pool, (void*)enmy0_go_img_1, 64, 16, 16, enemy0ImgColors, BLIT_2BPP);
  *(pool->images + 43) = imagePool_addImage (pool, (void*)enmy0_go_img_2, 64, 16, 16, enemy0ImgColors, BLIT_2BPP);
  *(pool->images + 44) = imagePool_addImage (pool, (void*)enmy0_attack_img, 64, 16, 16, enemy0ImgColors, BLIT_2BPP);

  *(pool->images + 45) = imagePool_addImage (pool, (void*)enmy1_go_img_0, 64, 16, 16, menuImgColors, BLIT_2BPP);
  *(pool->images + 46) = imagePool_addImage (pool, (void*)enmy1_go_img_1, 64, 16, 16, menuImgColors, BLIT_2BPP);
  *(pool->images + 47) = imagePool_addImage (pool, (void*)enmy1_go_img_2, 64, 16, 16, menuImgColors, BLIT_2BPP);

  *(pool->images + 48) = imagePool_addImage (pool, (void*)rock_img, 64, 16, 16, rockImgColors, BLIT_2BPP);
  *(pool->images + 49) = imagePool_addImage (pool, (void*)bomb_img, 64, 16, 16, rockImgColors, BLIT_2BPP);
  *(pool->images + 50) = imagePool_addImage (pool, (void*)potion_img, 64, 16, 16, rockImgColors, BLIT_2BPP);
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