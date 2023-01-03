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
extern uint_16 bombImgColors[4];
extern uint_16 bomb2ImgColors[4];
extern uint_16 pliligrimLeftColors[4];
extern uint_16 pliligrimUpAttackColors[4];
extern uint_16 boss0ImgColors[4];
extern uint_16 boss0ImgColors1[4];
extern uint16_t enemy0ImgColors[4];
extern uint_16 tile4Colors[4];
extern uint_16 rockImgColors[4];
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
extern const uint8_t ROCK_LEVEL[32][2 + 2];
extern const uint8_t LEVEL_PATH[32][2 + 1 + (8 * 2)];

extern const uint8_t piligrim_go_b_img_0[64];
extern const uint8_t piligrim_go_b_img_1[64];
extern const uint8_t piligrim_go_b_img_2[64];

extern const uint8_t piligrim_attack_b_img[64];

extern const uint8_t pligrim_idle_l_img_0[64];
extern const uint8_t pligrim_idle_l_img_1[64];
extern const uint8_t pligrim_idle_l_img_2[64];

extern const uint8_t pligrim_go_l_img_0[64];
extern const uint8_t pligrim_go_l_img_1[64];
extern const uint8_t pligrim_go_l_img_2[64];

extern const uint8_t piligrim_attack_l_img[64];

extern const uint8_t piligrim_idle_r_img_0[64];
extern const uint8_t piligrim_idle_r_img_1[64];
extern const uint8_t piligrim_idle_r_img_2[64];

extern const uint8_t piligrim_go_r_img_0[64];
extern const uint8_t piligrim_go_r_img_1[64];
extern const uint8_t piligrim_go_r_img_2[64];

extern const uint8_t piligrim_attack_r_img[64];

extern const uint8_t piligrim_idle_u_img_0[64];
extern const uint8_t piligrim_idle_u_img_1[64];
extern const uint8_t piligrim_idle_u_img_2[64];

extern const uint8_t piligrim_go_u_img_0[64];
extern const uint8_t piligrim_go_u_img_1[64];
extern const uint8_t piligrim_go_u_img_2[64];

extern const uint8_t piligrim_attack_u_img[64];

extern const uint8_t sword_b_img[32];
extern const uint8_t sword_lr_img[32];
extern const uint8_t sword_u_img[32];

extern const uint8_t enmy0_go_img_0[64];
extern const uint8_t enmy0_go_img_1[64];
extern const uint8_t enmy0_go_img_2[64];
extern const uint8_t enmy0_attack_img[64];

extern const uint8_t enmy1_go_img_0[64];
extern const uint8_t enmy1_go_img_1[64];
extern const uint8_t enmy1_go_img_2[64];

extern const uint8_t rock_img[64];
extern const uint8_t bomb_img[64];
extern const uint8_t bomb2_img[64];
extern const uint8_t potion_img[64];

extern const uint8_t boss0_img_0[64];
extern const uint8_t boss0_img_1[64];
extern const uint8_t boss0_img_2[64];
extern const uint8_t boss0_img_3[64];
extern const uint8_t boss0_img_4[64];
extern const uint8_t boss0_img_5[64];

#endif //_ASSETS_H_