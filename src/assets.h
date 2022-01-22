// Статичные файлы игры
// Created by user on 15.01.2022.
//


#ifndef _ASSETS_H_
#define _ASSETS_H_

#include "types.h"

#define menuImgWidth 160
#define menuImgHeight 128
#define menuImgFlags BLIT_1BPP
extern uint_16 menuImgColors[4];
extern const uint8_t menuImg[2560];

#define piligrimWidth 16
#define piligrimHeight 16
#define piligrimFlags BLIT_2BPP
extern const uint8_t piligrim_idle_b_img_0[64];
extern const uint8_t piligrim_idle_b_img_1[64];
extern const uint8_t piligrim_idle_b_img_2[64];

extern const uint8_t tile0[64];
extern const uint8_t tile1[64];
extern const uint8_t tile2[32];
extern const uint8_t tile3[32];
extern const uint8_t tile4[64];
extern const uint8_t tile5[32];
extern const uint8_t tile6[64];
extern const uint8_t tile7[64];

extern const uint8_t PLAIN_LEVEL[8][8][64];

#endif //_ASSETS_H_