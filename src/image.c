#include "image.h"
#include <stdlib.h>
#include <string.h>

Image* image_new(void* dataPtr, uint_32 w, uint_32 h, uint_16 colors[4])
{

    Image* newImage = (Image*)malloc(sizeof(Image));
    newImage->data = dataPtr;
    newImage->width = w;
    newImage->height = h;
   
    memcpy((void*)newImage->colors, (void*)colors, sizeof(uint_16) * 4);
    return newImage;
}