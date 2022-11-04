#include "libs.h"
#include "allocator.h"
Image* image_new(void* dataPtr, uint_32 w, uint_32 h, uint_16 colors[4], uint_32 flags)
{

    Image* newImage = (Image*)allocate(sizeof(Image));
    newImage->data = dataPtr;
    newImage->width = w;
    newImage->height = h;
    newImage->flags = flags;

    memcpy((void*)newImage->colors, (void*)colors, sizeof(uint_16) * 4);
    return newImage;
}