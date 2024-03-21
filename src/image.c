#include "image.h"
#include "allocator.h"

Image* image_new(void* dataPtr, uint32_t w, uint32_t h, uint16_t colors[4], uint32_t flags)
{

    Image* newImage = (Image*)allocate(sizeof(Image));
    newImage->data = dataPtr;
    newImage->width = w;
    newImage->height = h;
    newImage->flags = flags;

    memcpy((void*)newImage->colors, (void*)colors, sizeof(uint16_t) * 4);
    return newImage;
}