#pragma once
#include "stdint.h"

struct Image* image_new(void* dataPtr, uint32_t w, uint32_t h, uint16_t colors[4], uint32_t flags);

struct Image
{
    void* data;
    uint32_t width;
    uint32_t height;
    uint16_t colors[4];
    uint32_t flags;
};

typedef struct Image Image;