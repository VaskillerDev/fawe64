#include "libs.h"

#define DEBUG_BOUNDING_VOLUME 1
#define MAX(a, b) (((a) > (b)) ? (a) : (b))
#define MIN(a, b) (((a) < (b)) ? (a) : (b))

Sprite *sprite_animated_new(Image *images[], uint_32 imageCount, uint_32 animDelay)
{
    Sprite *newSprite = (Sprite *)malloc(sizeof(Sprite));
    newSprite->frameCounter = 0;
    newSprite->animDelay = animDelay;
    newSprite->imageCount = imageCount;
    newSprite->currentImageIndex = 0;

    newSprite->images = (Image **)malloc(sizeof(Image *) * imageCount);

    for (uint_32 i = 0; i < imageCount; ++i)
        *(newSprite->images + i) = images[i];

    newSprite->currentImage = *newSprite->images;
    newSprite->size.x = newSprite->currentImage->width;
    newSprite->size.y = newSprite->currentImage->height;
    return newSprite;
}

Sprite *sprite_new(Image *image)
{
    Sprite *newSprite = (Sprite *)malloc(sizeof(Sprite));
    newSprite->frameCounter = 0;
    newSprite->animDelay = 0;
    newSprite->imageCount = 1;
    newSprite->currentImageIndex = 0;
    newSprite->currentImage = image;

    return newSprite;
}

void sprite_Draw(Sprite *sprite)
{
    DrawImage(sprite->currentImage, sprite->pos.x - sprite->size.x / 2, sprite->pos.y - sprite->size.y / 2, true);

    if (DEBUG_BOUNDING_VOLUME)
        DrawBoundingVolume(&sprite->boundingVolume);

    if (sprite->animDelay == 0)
        return;

    ++sprite->frameCounter;

    if (sprite->frameCounter >= sprite->animDelay)
    {
        sprite->currentImageIndex = ++sprite->currentImageIndex % sprite->imageCount;
        sprite->frameCounter = 0;

        sprite->currentImage = *(sprite->images + sprite->currentImageIndex);
    }
}

void sprite_initBoundingVolume(Sprite *sprite, BoundingVolumeShape shape)
{
    sprite->boundingVolume.shape = shape;
    sprite->boundingVolume.position = &sprite->pos;
    if (shape == SPHERE)
    {
        sprite->boundingVolume.size.x = MAX(sprite->size.x / 2, sprite->size.y / 2);
        sprite->boundingVolume.size.y = MIN(sprite->size.x / 2, sprite->size.y / 2);
    }
    else if (shape == BOX)
    {
        sprite->boundingVolume.size = sprite->size;
    }
    else
        return;
}