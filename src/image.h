#pragma once
#include "types.h"

struct Image* image_new(void* dataPtr, uint_32 w, uint_32 h, uint_16 colors[4]);

struct Image
{
    void* data;
    uint_32 width;
    uint_32 height;
    uint_16 colors[4];
};

typedef struct Image Image;