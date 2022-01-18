#include "sprite.h"
#include "render.h"
#include <stdlib.h>
#include <string.h>

Sprite *sprite_new(Image* images[], uint_32 imageCount, uint_32 animDelay)
{
    Sprite *newSprite = (Sprite *)malloc(sizeof(Sprite));
    newSprite->frameCounter = 0;
    newSprite->animDelay = animDelay;
    newSprite->imageCount = imageCount;
    newSprite->currentImageIndex = 0;

    newSprite->images = (Image**)malloc(sizeof(Image*) * imageCount);
    
    for(uint_32 i = 0; i < imageCount; ++i)
     *(newSprite->images + i) = images[i];

    newSprite->currentImage =  *newSprite->images;

    return newSprite;
}

void sprite_Draw(Sprite *sprite)
{
    DrawImage(sprite->currentImage, sprite->pos.x, sprite->pos.y, true);
    ++sprite->frameCounter;

    if (sprite->frameCounter >= sprite->animDelay)
    {
        sprite->currentImageIndex = ++sprite->currentImageIndex % sprite->imageCount; 
        sprite->frameCounter = 0;

        sprite->currentImage = *(sprite->images + sprite->currentImageIndex);
    }
}