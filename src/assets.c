//
// Created by user on 15.01.2022.
//
#include "libs.h"

// menu
const uint8_t menuImg[2560] = {0x00, 0x00, 0x03, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x01, 0xff, 0xff,
                               0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
                               0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0x00, 0x1f, 0xff, 0xf0, 0x1f, 0xff, 0xff, 0xff, 0xff,
                               0xff, 0xff, 0xff, 0xff, 0xfc, 0x00, 0x00, 0x07, 0xff, 0xff, 0xfc, 0x1f, 0xff, 0xff, 0xff,
                               0x00, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
                               0xf8, 0x00, 0x7f, 0xff, 0xc0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0,
                               0x00, 0x00, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x01, 0xff, 0xff, 0xff, 0xff,
                               0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe0, 0x01, 0xff, 0xff, 0x00,
                               0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc0, 0x00, 0x00, 0x7f, 0xff, 0xff,
                               0xff, 0xff, 0xff, 0xff, 0xff, 0x07, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
                               0xff, 0xff, 0xff, 0xff, 0xff, 0x80, 0x07, 0xff, 0xfc, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff,
                               0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x3f, 0xff, 0xff, 0xff, 0xff,
                               0x00, 0x00, 0x00, 0x7f, 0xfe, 0x00, 0x00, 0x7f, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0xfe,
                               0x00, 0x00, 0x00, 0x00, 0x7f, 0x07, 0xff, 0xff, 0xff, 0xff, 0xe7, 0xff, 0xff, 0xfc, 0x00,
                               0x00, 0x00, 0x00, 0x3f, 0xff, 0xff, 0xf7, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x1f, 0xf8,
                               0x00, 0x00, 0x1f, 0xff, 0xf0, 0x00, 0x0f, 0xff, 0xff, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x1f,
                               0x07, 0xff, 0xff, 0xff, 0xff, 0xe7, 0xff, 0xff, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x0f, 0xff,
                               0xff, 0xf7, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x07, 0xe0, 0x00, 0x00, 0x07, 0xff, 0xc0,
                               0x00, 0x00, 0x1f, 0xff, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0xff, 0xff, 0xff,
                               0xff, 0xfc, 0xff, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x03, 0xff, 0xff, 0xff, 0xc0, 0xff, 0xff,
                               0x00, 0x00, 0x00, 0x01, 0x80, 0x00, 0x00, 0x01, 0xfe, 0x00, 0x00, 0x00, 0x00, 0xff, 0x80,
                               0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                               0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                               0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                               0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                               0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                               0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x00, 0x00, 0x00, 0x00,
                               0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                               0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                               0x00, 0x00, 0x00, 0x00, 0x00, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                               0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x80, 0x00, 0x00, 0x00,
                               0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                               0xff, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                               0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                               0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xe0, 0x00, 0x00, 0x00,
                               0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                               0xff, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                               0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                               0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xfc, 0x00, 0x00, 0x00,
                               0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                               0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                               0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                               0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x80, 0x00, 0x00,
                               0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                               0xff, 0xff, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                               0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                               0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xc0, 0x00, 0x00,
                               0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                               0xff, 0xff, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                               0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                               0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xf0, 0x00, 0x00,
                               0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                               0xff, 0xff, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                               0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                               0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xf8, 0x00, 0x00,
                               0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                               0xff, 0xff, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                               0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                               0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xfc, 0x00, 0x00,
                               0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                               0xff, 0xff, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                               0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                               0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xf0, 0x00, 0x00,
                               0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                               0xff, 0xff, 0xe0, 0x00, 0x00, 0x01, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                               0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xc0, 0x00, 0x00, 0x02, 0x40, 0x00, 0x00, 0x00,
                               0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xe0, 0x00, 0x00,
                               0x04, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                               0xff, 0xff, 0xf0, 0x00, 0x00, 0x08, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                               0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xf8, 0x00, 0x00, 0x10, 0x18, 0x00, 0x00, 0x00,
                               0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xf8, 0x00, 0x00,
                               0x20, 0x3c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                               0xff, 0xff, 0xf0, 0x00, 0x00, 0x40, 0x7e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                               0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xe0, 0x00, 0x00, 0x80, 0xff, 0x00, 0x00, 0x00,
                               0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xc0, 0x00, 0x01,
                               0x01, 0xff, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x01, 0x1c, 0x00, 0x00,
                               0xff, 0xff, 0xc0, 0x00, 0x02, 0x03, 0xff, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x01, 0x40, 0x00,
                               0x00, 0x03, 0x1c, 0x00, 0x00, 0xff, 0xff, 0xf0, 0x00, 0x04, 0x07, 0xff, 0xe0, 0x00, 0x00,
                               0x00, 0x00, 0x02, 0x20, 0x00, 0x00, 0x07, 0x1c, 0x00, 0x00, 0xff, 0xff, 0xf0, 0x00, 0x08,
                               0x0f, 0xff, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x04, 0x10, 0x00, 0x00, 0x0f, 0x1c, 0x00, 0x00,
                               0xff, 0xff, 0xf0, 0x00, 0x10, 0x1f, 0xff, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x08, 0x18, 0x00,
                               0x00, 0x1f, 0x1c, 0x00, 0x00, 0xff, 0xff, 0xe0, 0x00, 0x20, 0x3f, 0xff, 0xfc, 0x00, 0x00,
                               0x00, 0x00, 0x10, 0x3c, 0x00, 0x00, 0x3f, 0x1c, 0x00, 0x00, 0xff, 0xff, 0x80, 0x00, 0x40,
                               0x7f, 0xff, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x20, 0x7e, 0x00, 0x00, 0x7f, 0x1c, 0x00, 0x00,
                               0xff, 0xff, 0x00, 0x00, 0x80, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x40, 0xff, 0x00,
                               0x00, 0xff, 0x1c, 0x00, 0x00, 0xff, 0xff, 0x80, 0x01, 0xff, 0xff, 0xff, 0xff, 0x80, 0x00,
                               0x00, 0x00, 0xff, 0xff, 0x80, 0x00, 0xff, 0x1c, 0xe0, 0x01, 0xff, 0xff, 0xc0, 0x03, 0xff,
                               0xff, 0xff, 0xff, 0xc0, 0x00, 0x00, 0x01, 0xff, 0xff, 0xc0, 0x08, 0xff, 0x1c, 0xe0, 0x03,
                               0xff, 0xff, 0xe0, 0x07, 0xff, 0xff, 0xff, 0xff, 0xe0, 0x00, 0x00, 0x03, 0xff, 0xff, 0xe0,
                               0x0a, 0xff, 0x1c, 0xe4, 0x07, 0xff, 0xff, 0xe0, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xf0, 0x00,
                               0x00, 0x07, 0xff, 0xff, 0xf0, 0x0a, 0xff, 0x1c, 0xe4, 0x0f, 0xff, 0xff, 0xe0, 0x1f, 0xff,
                               0xff, 0xff, 0xff, 0xf8, 0x00, 0x00, 0x0f, 0xff, 0xff, 0xf8, 0x2a, 0xff, 0x1c, 0xe4, 0x1f,
                               0xff, 0xff, 0xc0, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xfc, 0x00, 0x00, 0x1f, 0xff, 0xff, 0xfc,
                               0xaa, 0xff, 0x1c, 0xe4, 0x3f, 0xff, 0xff, 0x00, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00,
                               0x00, 0x3f, 0xff, 0xff, 0xfe, 0xaa, 0xff, 0x1c, 0xe4, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff,
                               0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 0xff,
                               0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
                               0xff, 0xff, 0xff, 0xff, 0xff, 0xf8, 0x7c, 0x00, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
                               0xff, 0xff, 0xff, 0xff, 0xff, 0x80, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xc0, 0x00,
                               0x01, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00,
                               0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                               0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0x00, 0x00, 0x3f, 0xfb, 0xff, 0xff, 0xff, 0xff, 0xff,
                               0xff, 0x8f, 0xff, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x00, 0x00, 0x00, 0x00,
                               0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                               0xe0, 0x00, 0x00, 0x00, 0x00, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x80, 0x00, 0x00,
                               0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                               0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x00, 0x00, 0x00, 0x00,
                               0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                               0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                               0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                               0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x00, 0x00, 0x00, 0x00,
                               0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                               0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                               0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                               0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x00, 0x00, 0x00, 0x00,
                               0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                               0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                               0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                               0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x00, 0x00, 0x00, 0x00,
                               0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                               0xe0, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                               0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x00, 0x30, 0x3c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                               0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x00, 0x30, 0x7c, 0x00,
                               0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                               0xe0, 0x00, 0x30, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                               0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x00, 0x30, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                               0x00, 0x00, 0x00, 0x00, 0x07, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe0, 0x00, 0x00, 0x7c, 0x00,
                               0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                               0xe0, 0x00, 0x00, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                               0x00, 0x00, 0x03, 0xff, 0xff, 0xe0, 0x00, 0x00, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                               0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x00, 0x01, 0xfe, 0x00,
                               0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xff, 0xff, 0xff,
                               0xe0, 0x00, 0x01, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                               0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x00, 0x01, 0xff, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff,
                               0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe0, 0x00, 0x01, 0xff, 0x80,
                               0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                               0xe0, 0x00, 0x03, 0xff, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                               0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x00, 0x03, 0xfe, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00,
                               0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfe, 0x00, 0x03, 0xfe, 0x70,
                               0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                               0xfe, 0x00, 0x03, 0xfe, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                               0x00, 0x00, 0x00, 0x00, 0x00, 0xfe, 0x00, 0x00, 0x44, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                               0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfe, 0x00, 0x3f, 0xff, 0xe0,
                               0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                               0xff, 0x07, 0xff, 0xff, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                               0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x7f, 0xff, 0xff, 0xff, 0xc0, 0x00, 0x00, 0x00, 0x00,
                               0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff,
                               0xff, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                               0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                               0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x80, 0x00,
                               0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff,
                               0xff, 0xff, 0xff, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                               0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                               0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 0x00,
                               0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff,
                               0xff, 0xff, 0xff, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                               0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                               0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0x00,
                               0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff,
                               0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00,
                               0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                               0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
                               0xff, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff,
                               0xff, 0xff, 0xff, 0xff, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                               0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe0, 0x00, 0x00,
                               0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc0,
                               0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff,
                               0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
                               0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00,
                               0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe0,
                               0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

uint_16 menuImgColors[4] = {0, 4, 2, 3};
uint_16 pliligrimLeftColors[4] = {0, 4, 3, 2 };
uint_16 pliligrimUpAttackColors[4] = {4,0,2,3};
uint16_t enemy0ImgColors[4] = {0, 2, 4, 3};
uint16_t rockImgColors[4] = {2, 0, 4, 0};
uint_16 tile4Colors[4] = {4, 1, 2, 3};

// piligrim
const uint8_t piligrim_idle_b_img_0[64] = { 0x00,0x15,0x54,0x00,0x00,0x55,0x55,0x00,0x01,0x55,0x55,0x40,0x00,0xab,0xea,0x00,0x00,0xbb,0xee,0x00,0x00,0xab,0xea,0x00,0x00,0x1b,0xe4,0x00,0x00,0xd5,0x5f,0x00,0x03,0xd5,0x77,0xc1,0x03,0xd5,0xd7,0xc5,0x0a,0xd7,0x57,0x95,0x0a,0x9d,0x56,0xa4,0x02,0xb5,0x57,0xa8,0x03,0xd5,0x57,0xe0,0x00,0xd5,0x57,0x40,0x00,0x55,0x05,0x00 };
const uint8_t piligrim_idle_b_img_1[64] = { 0x00,0x00,0x00,0x00,0x00,0x15,0x54,0x00,0x00,0x55,0x55,0x00,0x01,0x55,0x55,0x40,0x00,0xab,0xea,0x00,0x00,0xbb,0xee,0x00,0x00,0xab,0xea,0x00,0x00,0xdb,0xe7,0x00,0x03,0xd5,0x77,0xc1,0x03,0xd5,0xd7,0xc5,0x0a,0xd7,0x57,0x95,0x0a,0x9d,0x56,0xa4,0x02,0xb5,0x57,0xa8,0x03,0xd5,0x57,0xe0,0x00,0xd5,0x57,0x40,0x00,0x55,0x05,0x00 };
const uint8_t piligrim_idle_b_img_2[64] = { 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x15,0x54,0x00,0x00,0x55,0x55,0x00,0x01,0x55,0x55,0x40,0x00,0xab,0xea,0x00,0x00,0xbb,0xee,0x00,0x00,0xab,0xea,0x00,0x00,0xdb,0xe7,0x00,0x03,0xd5,0x77,0xc1,0x03,0xd5,0xd7,0xc5,0x0a,0xd7,0x57,0x95,0x0a,0x9d,0x56,0xa4,0x02,0xb5,0x57,0xa8,0x03,0xd5,0x57,0xe0,0x00,0x55,0x05,0x00 };

const uint8_t piligrim_go_b_img_0[64] = { 0x00,0x00,0x00,0x00,0x00,0x15,0x54,0x00,0x00,0x55,0x55,0x00,0x01,0x55,0x55,0x40,0x00,0xab,0xea,0x00,0x00,0xbb,0xee,0x00,0x00,0xab,0xea,0x00,0x00,0x1b,0xe4,0x00,0x00,0xd5,0x7f,0x05,0x03,0xd5,0xd7,0xd5,0x0b,0xd7,0x57,0x95,0x0b,0xdd,0x56,0xa4,0x03,0xf5,0x57,0xa8,0x03,0xd5,0x57,0xe0,0x00,0xd5,0x57,0x40,0x00,0x55,0x05,0x00 };
const uint8_t piligrim_go_b_img_1[64] = { 0x00,0x15,0x54,0x00,0x00,0x55,0x55,0x00,0x01,0x55,0x55,0x40,0x00,0xab,0xea,0x00,0x00,0xbb,0xee,0x00,0x00,0xab,0xea,0x00,0x00,0x1b,0xe4,0x00,0x00,0xd5,0x5f,0x00,0x03,0xd5,0x77,0xc4,0x03,0xd5,0xd7,0xd4,0x0a,0xd7,0x57,0x94,0x0a,0xdd,0x57,0xa0,0x02,0xf5,0x57,0xa0,0x03,0xd5,0x57,0xc0,0x00,0xd5,0x57,0x00,0x00,0x55,0x15,0x00 };
const uint8_t piligrim_go_b_img_2[64] = { 0x00,0x00,0x00,0x00,0x00,0x15,0x54,0x00,0x00,0x55,0x55,0x00,0x01,0x55,0x55,0x40,0x00,0xab,0xea,0x00,0x00,0xbb,0xee,0x00,0x00,0xab,0xea,0x00,0x00,0x1b,0xe4,0x00,0x00,0xd5,0x7f,0x00,0x03,0xd5,0xd7,0xc4,0x0a,0xd7,0x57,0xd4,0x0a,0x9d,0x57,0xd0,0x02,0xb5,0x57,0xe0,0x03,0xd5,0x57,0xc0,0x00,0xd5,0x57,0x00,0x00,0x50,0x55,0x00 };

const uint8_t piligrim_attack_b_img[64] = { 0x00,0x00,0x00,0x00,0x00,0x15,0x54,0x00,0x00,0x55,0x55,0x00,0x01,0x55,0x55,0x40,0x00,0xab,0xea,0x00,0x00,0xbb,0xee,0x00,0x00,0xab,0xea,0x00,0x00,0x1b,0xe4,0x00,0x00,0xd5,0x7c,0x00,0x03,0xd5,0xff,0x00,0x0b,0xd7,0xff,0x00,0x0b,0xdf,0xff,0x00,0x03,0x77,0xaf,0x00,0x01,0x57,0xab,0x00,0x00,0x57,0x9b,0x00,0x00,0x05,0x55,0x00 };

const uint8_t pligrim_idle_l_img_0[64] = { 0x00,0x15,0x54,0x00,0x00,0x55,0x55,0x00,0x01,0x55,0x55,0x40,0x00,0xaf,0xf4,0x00,0x00,0xae,0xf4,0x00,0x00,0xaf,0x54,0x00,0x00,0xad,0xa9,0x00,0x00,0x56,0xa9,0x00,0x00,0x5a,0xa9,0x00,0x00,0x66,0xbd,0x00,0x00,0x96,0xbd,0x00,0x15,0x55,0x5d,0x40,0x05,0x55,0x69,0x00,0x00,0x55,0x55,0x00,0x00,0x55,0x55,0x00,0x00,0x15,0x15,0x00 };
const uint8_t pligrim_idle_l_img_1[64] = { 0x00,0x00,0x00,0x00,0x00,0x15,0x54,0x00,0x00,0x55,0x55,0x00,0x01,0x55,0x55,0x40,0x00,0xaf,0xf4,0x00,0x00,0xae,0xf4,0x00,0x00,0xaf,0x54,0x00,0x00,0xad,0xa9,0x00,0x00,0x56,0xa9,0x00,0x00,0x5a,0xa9,0x00,0x00,0x66,0xbd,0x00,0x00,0x96,0xbd,0x00,0x00,0x55,0x5d,0x40,0x15,0x55,0x69,0x00,0x05,0x55,0x55,0x00,0x00,0x15,0x15,0x00 };
const uint8_t pligrim_idle_l_img_2[64] = { 0x00,0x00,0x00,0x00,0x00,0x15,0x54,0x00,0x00,0x55,0x55,0x00,0x01,0x55,0x55,0x40,0x00,0xaf,0xf4,0x00,0x00,0xae,0xf4,0x00,0x00,0xaf,0x54,0x00,0x00,0xad,0xa9,0x00,0x00,0x56,0xa9,0x00,0x00,0x5a,0xa9,0x00,0x00,0x66,0xa9,0x00,0x00,0x96,0xbd,0x00,0x00,0x55,0x7d,0x00,0x00,0x55,0x5d,0x40,0x15,0x55,0x55,0x00,0x05,0x55,0x15,0x00 };

const uint8_t pligrim_go_l_img_0[64] = { 0x00,0x00,0x00,0x00,0x00,0x15,0x54,0x00,0x00,0x55,0x55,0x00,0x01,0x55,0x55,0x40,0x00,0xaf,0xf4,0x00,0x00,0xae,0xf4,0x00,0x00,0xaf,0x54,0x00,0x00,0xad,0xa9,0x00,0x00,0x56,0xa9,0x00,0x00,0x5a,0xa9,0x00,0x00,0x66,0xbd,0x00,0x00,0x96,0xbd,0x00,0x15,0x55,0x5d,0x40,0x05,0x55,0x69,0x00,0x00,0x55,0x55,0x00,0x00,0x54,0x14,0x00 };
const uint8_t pligrim_go_l_img_1[64] = { 0x00,0x15,0x54,0x00,0x00,0x55,0x55,0x00,0x01,0x55,0x55,0x40,0x00,0xaf,0xf4,0x00,0x00,0xae,0xf4,0x00,0x00,0xaf,0x54,0x00,0x00,0xad,0xa9,0x00,0x00,0x56,0xa9,0x00,0x00,0x5a,0xa9,0x00,0x00,0x66,0xf9,0x00,0x00,0x96,0xf9,0x00,0x00,0x55,0x75,0x00,0x05,0x55,0x69,0x00,0x01,0x55,0x55,0x00,0x00,0x55,0x55,0x00,0x00,0x05,0x54,0x00 };
const uint8_t pligrim_go_l_img_2[64] = { 0x00,0x00,0x00,0x00,0x00,0x15,0x54,0x00,0x00,0x55,0x55,0x00,0x01,0x55,0x55,0x40,0x00,0xaf,0xf4,0x00,0x00,0xae,0xf4,0x00,0x00,0xaf,0x54,0x00,0x00,0xad,0xa9,0x00,0x00,0x56,0xa9,0x00,0x00,0x5a,0xf9,0x00,0x00,0x67,0xf9,0x00,0x00,0x97,0xd9,0x00,0x03,0x55,0x69,0x00,0x05,0x55,0x55,0x00,0x01,0x55,0x55,0x00,0x00,0x14,0x15,0x00 };

const uint8_t piligrim_attack_l_img[64] = { 0x01,0x55,0x40,0x00,0x05,0x55,0x50,0x00,0x15,0x55,0x54,0x00,0x0a,0xff,0x40,0x00,0x0a,0xef,0x40,0x00,0x0a,0xf5,0x40,0x00,0x0a,0xd5,0x50,0x00,0x01,0x5a,0x90,0x00,0x41,0xaa,0x94,0x00,0x7e,0xaa,0x97,0x00,0x7e,0x9a,0x97,0x00,0x41,0x5a,0x94,0x00,0x00,0x5a,0x95,0x00,0x00,0x55,0x55,0x00,0x01,0x55,0x55,0x00,0x00,0x00,0x15,0x00 };

const uint8_t piligrim_idle_r_img_0[64] = { 0x00,0x15,0x54,0x00,0x00,0x55,0x55,0x00,0x01,0x55,0x55,0x40,0x00,0x1a,0xaf,0x00,0x00,0x1a,0xef,0x00,0x00,0x15,0xaf,0x00,0x00,0x7f,0x6f,0x00,0x00,0x7f,0xd5,0x00,0x00,0x7f,0xf5,0x00,0x00,0x6b,0xdd,0x00,0x00,0x6b,0xd7,0x00,0x01,0x6b,0xd5,0x00,0x00,0x7f,0xd5,0x54,0x00,0x55,0x55,0x50,0x00,0x55,0x55,0x00,0x00,0x54,0x54,0x00 };
const uint8_t piligrim_idle_r_img_1[64] = { 0x00,0x00,0x00,0x00,0x00,0x15,0x54,0x00,0x00,0x55,0x55,0x00,0x01,0x55,0x55,0x40,0x00,0x1a,0xaf,0x00,0x00,0x1a,0xef,0x00,0x00,0x15,0xaf,0x00,0x00,0x7f,0x6f,0x00,0x00,0x7f,0xd5,0x00,0x00,0x7f,0xf5,0x00,0x00,0x6b,0xdd,0x00,0x01,0x6b,0xd7,0x00,0x00,0x6b,0xd5,0x54,0x00,0x55,0x55,0x50,0x00,0x55,0x55,0x00,0x00,0x54,0x54,0x00 };
const uint8_t piligrim_idle_r_img_2[64] = { 0x00,0x00,0x00,0x00,0x00,0x15,0x54,0x00,0x00,0x55,0x55,0x00,0x01,0x55,0x55,0x40,0x00,0x1a,0xaf,0x00,0x00,0x1a,0xef,0x00,0x00,0x15,0xaf,0x00,0x00,0x7f,0x6f,0x00,0x00,0x7f,0xd5,0x00,0x00,0x7f,0xf5,0x00,0x00,0x7f,0xdd,0x00,0x00,0x6b,0xd7,0x00,0x01,0x6b,0xd5,0x00,0x00,0x69,0x55,0x54,0x00,0x55,0x55,0x50,0x00,0x54,0x54,0x00 };

const uint8_t piligrim_go_r_img_0[64] = { 0x00,0x15,0x54,0x00,0x00,0x55,0x55,0x00,0x01,0x55,0x55,0x40,0x00,0x1a,0xaf,0x00,0x00,0x1a,0xef,0x00,0x00,0x15,0xaf,0x00,0x00,0x7f,0x6f,0x00,0x00,0x7f,0xd5,0x00,0x00,0x7f,0xf5,0x00,0x00,0x6b,0xdd,0x00,0x00,0x6b,0xd7,0x00,0x01,0x6b,0xd5,0x00,0x00,0x7f,0xd5,0x54,0x00,0x55,0x55,0x50,0x00,0x55,0x55,0x00,0x00,0x14,0x55,0x00 };
const uint8_t piligrim_go_r_img_1[64] = { 0x00,0x00,0x00,0x00,0x00,0x15,0x54,0x00,0x00,0x55,0x55,0x00,0x01,0x55,0x55,0x40,0x00,0x1a,0xaf,0x00,0x00,0x1a,0xef,0x00,0x00,0x15,0xaf,0x00,0x00,0x7f,0x6f,0x00,0x00,0x7f,0xf5,0x00,0x00,0x7a,0xdd,0x00,0x00,0x7a,0xd7,0x00,0x00,0x7a,0xd5,0x00,0x01,0x7f,0xd5,0x50,0x00,0x55,0x55,0x40,0x00,0x55,0x55,0x00,0x00,0x15,0x50,0x00 };
const uint8_t piligrim_go_r_img_2[64] = { 0x00,0x00,0x00,0x00,0x00,0x15,0x54,0x00,0x00,0x55,0x55,0x00,0x01,0x55,0x55,0x40,0x00,0x1a,0xaf,0x00,0x00,0x1a,0xef,0x00,0x00,0x15,0xaf,0x00,0x00,0x7f,0x6f,0x00,0x00,0x7f,0xf5,0x00,0x00,0x6b,0xdd,0x00,0x00,0x6b,0xd7,0x00,0x01,0x6b,0xd5,0x50,0x00,0x6b,0xd5,0x40,0x00,0x55,0x55,0x00,0x00,0x55,0x55,0x00,0x00,0x55,0x15,0x00 };

const uint8_t piligrim_attack_r_img[64] = { 0x00,0x01,0x55,0x40,0x00,0x05,0x55,0x50,0x00,0x15,0x55,0x54,0x00,0x01,0xaa,0xf0,0x00,0x01,0xae,0xf0,0x00,0x01,0x5a,0xf0,0x00,0x05,0x56,0xf0,0x00,0x07,0xf5,0x40,0x00,0x0f,0xf5,0x41,0x00,0x0a,0xf5,0x69,0x00,0x0a,0xf5,0x69,0x00,0x0a,0xf5,0x41,0x00,0x55,0x55,0x00,0x00,0x55,0x55,0x00,0x00,0x55,0x55,0x40,0x00,0x54,0x00,0x00 };

const uint8_t piligrim_idle_u_img_0[64] = { 0x00,0x15,0x54,0x00,0x00,0x55,0x55,0x00,0x01,0x55,0x55,0x40,0x00,0xaa,0xaa,0x00,0x00,0xaa,0xaa,0x00,0x00,0x55,0x55,0x00,0x00,0x15,0x54,0x00,0x00,0xff,0xff,0x00,0x43,0xff,0xff,0xc0,0x53,0xff,0xff,0xc0,0x57,0xff,0xff,0xc0,0x1b,0xff,0xff,0xc0,0x2b,0xff,0xff,0xe0,0x0b,0xff,0xff,0xe0,0x00,0xff,0xff,0xc0,0x00,0x14,0x14,0x00 };
const uint8_t piligrim_idle_u_img_1[64] = { 0x00,0x00,0x00,0x00,0x00,0x15,0x54,0x00,0x00,0x55,0x55,0x00,0x01,0x55,0x55,0x40,0x00,0xaa,0xaa,0x00,0x00,0xaa,0xaa,0x00,0x00,0x55,0x55,0x00,0x00,0x15,0x54,0x00,0x40,0xff,0xff,0x00,0x53,0xff,0xff,0xc0,0x57,0xff,0xff,0xc0,0x1b,0xff,0xff,0xc0,0x2b,0xff,0xff,0xe0,0x0b,0xff,0xff,0xe0,0x00,0xff,0xff,0xc0,0x00,0x14,0x14,0x00 };
const uint8_t piligrim_idle_u_img_2[64] = { 0x00,0x00,0x00,0x00,0x00,0x15,0x54,0x00,0x00,0x55,0x55,0x00,0x01,0x55,0x55,0x40,0x00,0xaa,0xaa,0x00,0x00,0xaa,0xaa,0x00,0x00,0x55,0x55,0x00,0x00,0x15,0x54,0x00,0x00,0xff,0xff,0x00,0x43,0xff,0xff,0xc0,0x53,0xff,0xff,0xc0,0x57,0xff,0xff,0xc0,0x1b,0xff,0xff,0xc0,0x2b,0xff,0xff,0xe0,0x0a,0xff,0xff,0xe0,0x00,0x14,0x14,0x00 };

const uint8_t piligrim_go_u_img_0[64] = { 0x00,0x15,0x54,0x00,0x00,0x55,0x55,0x00,0x01,0x55,0x55,0x40,0x00,0xaa,0xaa,0x00,0x00,0xaa,0xaa,0x00,0x00,0x55,0x55,0x00,0x00,0x15,0x54,0x00,0x00,0xff,0xff,0x00,0x43,0xff,0xff,0xc0,0x53,0xff,0xff,0xc0,0x57,0xff,0xff,0xc0,0x1b,0xff,0xff,0xc0,0x2a,0xff,0xff,0xe0,0x0a,0xff,0xff,0xe0,0x00,0xff,0xff,0xc0,0x00,0x14,0x15,0x40 };
const uint8_t piligrim_go_u_img_1[64] = { 0x00,0x00,0x00,0x00,0x00,0x15,0x54,0x00,0x00,0x55,0x55,0x00,0x01,0x55,0x55,0x40,0x00,0xaa,0xaa,0x00,0x00,0xaa,0xaa,0x00,0x00,0x55,0x55,0x00,0x00,0x15,0x54,0x00,0x40,0xff,0xff,0x00,0x53,0xff,0xff,0xc0,0x57,0xff,0xff,0xc0,0x1b,0xff,0xff,0xc0,0x2b,0xff,0xff,0xe0,0x0b,0xff,0xff,0xe0,0x00,0xff,0xff,0xf0,0x00,0x15,0x55,0x00 };
const uint8_t piligrim_go_u_img_2[64] = { 0x00,0x00,0x00,0x00,0x00,0x15,0x54,0x00,0x00,0x55,0x55,0x00,0x01,0x55,0x55,0x40,0x00,0xaa,0xaa,0x00,0x00,0xaa,0xaa,0x00,0x00,0x55,0x55,0x00,0x40,0x15,0x54,0x00,0x50,0xff,0xff,0x00,0x57,0xff,0xff,0xc0,0x1b,0xff,0xff,0xc0,0x2b,0xff,0xff,0xe0,0x0b,0xff,0xff,0xe0,0x03,0xff,0xff,0xc0,0x03,0xff,0xff,0x00,0x00,0x15,0x45,0x00 };

const uint8_t piligrim_attack_u_img[64] = { 0x00,0x00,0x01,0x55,0x50,0x00,0x00,0x55,0x5a,0x00,0x00,0x15,0x5b,0xaa,0xaa,0x55,0x5b,0xaa,0xaa,0x55,0x5f,0x00,0x00,0x55,0x5f,0xc0,0x01,0x55,0x5f,0xff,0xfd,0x55,0x57,0xff,0xff,0x55,0x57,0xff,0xff,0x55,0x57,0xff,0xfa,0x55,0x57,0xff,0xfa,0x55,0x57,0xff,0xff,0x55,0x55,0xff,0xff,0x55,0x55,0x00,0x7c,0x55,0x55,0x55,0x50,0x55 };

const uint8_t sword_b_img[32] = { 0x02,0xe8,0x00,0xe0,0x00,0xe0,0x00,0xe0,0x00,0xe0,0x00,0xe0,0x00,0xe0,0x00,0xe0,0x00,0xe0,0x00,0xe0,0x00,0x40,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00 };
const uint8_t sword_lr_img[32] = { 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x00,0x00,0x07,0xff,0x03,0xff,0x00,0x00,0x00,0x01,0x00,0x00,0x00,0x00,0x00,0x00 };
const uint8_t sword_u_img[32] = { 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x10,0x00,0x38,0x00,0x38,0x00,0x38,0x00,0x38,0x00,0x38,0x00,0x38,0x00,0x38,0x00,0x38,0x00,0x38,0x00,0xba,0x00 };

// enemy 0
const uint8_t enmy0_go_img_0[64] = { 0x00,0x15,0x55,0x00,0x00,0x55,0xa9,0x00,0x00,0x56,0xaa,0x00,0x01,0x56,0xaa,0x00,0x01,0x56,0xaa,0x00,0x01,0x56,0xaa,0x00,0x00,0x56,0xaa,0x00,0x00,0x55,0xa9,0x00,0x00,0x55,0x55,0x00,0x01,0x55,0x55,0x00,0x0f,0x55,0x55,0xc0,0x0f,0x55,0x55,0xc0,0x0f,0x55,0x55,0x00,0x01,0x55,0x55,0x00,0x05,0x55,0x55,0x00,0x15,0x55,0x55,0x40 };
const uint8_t enmy0_go_img_1[64] = { 0x00,0x00,0x00,0x00,0x00,0x01,0x55,0x50,0x00,0x05,0x5a,0x90,0x00,0x05,0x6a,0xa0,0x00,0x15,0x6a,0xa0,0x00,0x15,0x6a,0xa0,0x00,0x15,0x6a,0xa0,0x00,0x05,0x6a,0xa0,0x00,0x05,0x5a,0x90,0x00,0x15,0x55,0x40,0x00,0x55,0x55,0x40,0x00,0x55,0x55,0x40,0x00,0x55,0x55,0x40,0x00,0x55,0x55,0x40,0x01,0x55,0x55,0x40,0x05,0x55,0x55,0x40 };
const uint8_t enmy0_go_img_2[64] = { 0x00,0x15,0x55,0x00,0x00,0x55,0xa9,0x00,0x00,0x56,0xaa,0x00,0x01,0x56,0xaa,0x00,0x01,0x56,0xaa,0x00,0x01,0x56,0xaa,0x00,0x00,0x56,0xaa,0x00,0x00,0x55,0xa9,0x00,0x00,0x55,0x55,0x00,0x01,0x55,0x55,0x00,0x01,0x55,0x57,0xc0,0x0d,0x55,0x57,0xc0,0x0d,0x55,0x57,0xc0,0x01,0x55,0x55,0x00,0x01,0x55,0x55,0x00,0x05,0x55,0x55,0x40 };
const uint8_t enmy0_attack_img[64] = { 0x00,0x15,0x55,0x00,0x00,0x56,0xa5,0x00,0x00,0x5a,0xa9,0x00,0x01,0x5a,0xa9,0x00,0x01,0x6a,0xaa,0x00,0x01,0x5a,0xa9,0x00,0x00,0x5a,0xa9,0x00,0x00,0x56,0xa5,0x00,0x00,0x55,0x55,0x00,0x01,0x55,0x55,0x00,0x01,0x57,0xf5,0x00,0x01,0x57,0xf5,0x00,0x01,0x57,0xf5,0x00,0x01,0x55,0x55,0x00,0x01,0x55,0x55,0x00,0x05,0x55,0x55,0x40 };


// enemy 1
const uint8_t enmy1_go_img_0[64] = { 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x10,0x00,0x00,0x04,0x54,0x00,0x00,0x15,0x55,0x00,0x00,0x55,0x55,0x40,0x01,0x55,0x55,0x50,0x05,0x55,0x55,0x55,0x55,0x55,0x55,0x56,0xa5,0x55,0x55,0x45,0x51,0x55,0x14,0x04,0x10,0x14,0x00,0x14,0x50,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00 };
const uint8_t enmy1_go_img_1[64] = { 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x55,0x55,0x55,0x55,0x05,0x56,0xa5,0x50,0x00,0x05,0x50,0x00,0x00,0x04,0x10,0x00,0x00,0x14,0x50,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00 };
const uint8_t enmy1_go_img_2[64] = { 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x15,0x40,0x01,0x54,0x55,0x50,0x05,0x55,0x55,0x55,0x55,0x55,0x40,0x06,0xa0,0x01,0x00,0x05,0x50,0x00,0x00,0x04,0x10,0x00,0x00,0x14,0x50,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00 };

// камень
const uint8_t rock_img[64] = { 0xea,0xaa,0xaa,0xab,0x81,0x66,0x60,0x46,0x85,0xa8,0x61,0x56,0xaa,0xa1,0x65,0x5a,0xa0,0x19,0x59,0xaa,0xa1,0x56,0xaa,0xaa,0x99,0x55,0xa8,0x12,0x96,0x56,0xa1,0x56,0xaa,0x6a,0xa5,0x6a,0x81,0xaa,0x9a,0xaa,0x96,0x01,0x16,0x56,0x96,0x15,0x59,0xaa,0x99,0x55,0x60,0x46,0xaa,0x55,0x91,0x5a,0x96,0xa6,0x55,0xa6,0xea,0xaa,0xaa,0xab };

const uint8_t bomb_img[64] = { 0xaa,0xaa,0xaa,0xaa,0xaa,0xaa,0xaa,0x94,0xaa,0xa5,0x5a,0x60,0xaa,0x55,0x55,0x68,0xa9,0x41,0x55,0x6a,0xa5,0x15,0x55,0x5a,0xa4,0x55,0x55,0x5a,0x95,0x55,0x55,0x56,0x95,0x55,0x55,0x56,0x95,0x55,0x55,0x56,0xa5,0x55,0x55,0x5a,0xa5,0x55,0x55,0x5a,0xa9,0x55,0x55,0x6a,0xaa,0x55,0x55,0xaa,0xaa,0xa5,0x5a,0xaa,0xaa,0xaa,0xaa,0xaa };

// тайлы
const uint8_t tile0[64] = { 0x00,0x00,0x00,0x05,0x00,0x22,0x80,0x50,0x00,0x00,0x05,0x00,0x22,0xa0,0x50,0x00,0x00,0x01,0x02,0x8a,0x0a,0x04,0x00,0x00,0x00,0x12,0xa2,0xa2,0x20,0x42,0xa2,0xa2,0x01,0x00,0x00,0x00,0x01,0x2a,0xaa,0xaa,0x04,0x2a,0x8a,0x8a,0x04,0x20,0x00,0x08,0x10,0xa2,0xa2,0xa8,0x12,0xa2,0xa2,0xa8,0x40,0x20,0x00,0x08,0x4a,0xa2,0xa2,0xa8 };
const uint8_t tile1[64] = { 0x00,0x00,0x00,0x00,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x6a,0x6a,0x6a,0x6a,0x6a,0x6a,0x6a,0x6a,0x55,0x55,0x55,0x55,0xa9,0xa9,0xa9,0xa9,0xa9,0xa9,0xa9,0xa9,0x55,0x55,0x55,0x55,0x6a,0x6a,0x6a,0x6a,0x6a,0x6a,0x6a,0x6a,0x55,0x55,0x55,0x55,0xa9,0xa9,0xa9,0xa9,0xa9,0xa9,0xa9,0xa9,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55 };
const uint8_t tile2[32] = { 0x00,0x00,0x75,0x68,0x00,0x00,0x00,0x00,0x00,0x00,0x12,0x3c,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x39,0xc8,0x00,0x00,0x06,0x00,0x00,0x00,0x00,0x00 };
const uint8_t tile3[32] = { 0x00,0x00,0x00,0x00,0x00,0x68,0x00,0x00,0x73,0x90,0x00,0x00,0x00,0x00,0x00,0x00,0x09,0x1e,0x00,0x00,0x00,0x1a,0x00,0x00,0x1d,0x40,0x00,0x00,0x00,0x00,0x00,0x00 };
const uint8_t tile4[64] = { 0x1a,0xaa,0xaa,0xa9,0x15,0x55,0x55,0x55,0x1a,0xaa,0xaa,0xaa,0x15,0x55,0xa6,0xa6,0x00,0x01,0x55,0x65,0x10,0x01,0xa6,0xa6,0x11,0x01,0xa6,0xa6,0x11,0x11,0x55,0x65,0x11,0x11,0x9a,0xaa,0x11,0x11,0xaa,0xaa,0x11,0x11,0x55,0x56,0x11,0x01,0xa6,0xa6,0x10,0x01,0xa6,0xa6,0x00,0x01,0x55,0x56,0x15,0x55,0xaa,0x6a,0x1a,0xaa,0xaa,0x6a };
const uint8_t tile5[32] = { 0x08,0x91,0xff,0xdf,0x00,0x11,0x22,0x11,0xff,0xbf,0x21,0x11,0x21,0x11,0xff,0xbf,0x22,0x21,0x00,0x21,0xff,0x7f,0x21,0x11,0x21,0x11,0xff,0x7f,0x42,0x21,0x42,0x21 };
const uint8_t tile6[64] = { 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x54,0x00,0x00,0x01,0x80,0x40,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x20,0x08,0xa8,0x00,0x00,0x00,0x00,0x00,0x00,0x54,0x00,0x00,0x00,0x65,0x40,0x0a,0x05,0x44,0x40,0x00,0x04,0x44,0x00,0x00,0x00,0x00,0x00 };
const uint8_t tile7[64] = { 0x01,0x44,0x00,0x00,0x00,0x00,0x00,0x00,0x54,0x10,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x02,0xa0,0x00,0x00,0x09,0x48,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xa0,0x00,0x00,0x02,0x08,0x00,0x00,0x00,0x00,0x00,0x15,0x01,0x04,0x00,0x00,0x00,0x00,0x00,0x05,0x00,0x00 };

 // чанки уровня
const uint8_t PLAIN_LEVEL [8][8][64] = {
    { // 0
      {131,2,3,3,21,5,5,5,131,3,2,2,21,5,5,5,110,7,2,2,21,5,5,5,7,2,7,7,10,111,111,111,2,3,7,7,3,2,2,2,2,3,7,2,6,7,6,3,6,7,3,6,6,3,6,6,2,2,2,2,2,2,2,2},
      {3,2,3,3,21,5,5,5,4,3,2,2,21,5,5,5,110,7,2,2,21,5,5,5,7,2,7,7,10,111,111,111,2,3,7,7,3,2,2,2,2,3,7,2,6,7,6,3,6,7,3,6,6,3,6,6,2,2,2,2,2,2,2,2},
      {},
      {},
      {},
      {},
      {},
      {}
      },
    { // 1
        {},
        {},
        {},
        {},
        {},
        {},
        {},
        {}
    },
    { // 2
        {},
        {},
        {},
        {},
        {},
        {},
        {},
        {}
    },
    { // 3
        {},
        {},
        {},
        {},
        {},
        {},
        {},
        {}
    },
    { // 4
        {},
        {},
        {},
        {},
        {},
        {},
        {},
        {}
    },
    { // 5
        {},
        {},
        {},
        {},
        {},
        {},
        {},
        {}
    },
    { // 6
        {},
        {},
        {},
        {},
        {},
        {},
        {},
        {}
    },
    { // 7
        {},
        {},
        {},
        {},
        {},
        {},
        {},
        {}
    },
};