#include "libs.h"

#define DEBUG_BOUNDING_VOLUME 1
#define MAX(a, b) (((a) > (b)) ? (a) : (b))
#define MIN(a, b) (((a) < (b)) ? (a) : (b))

Sprite *sprite_animated_new(Image *images[], uint_32 imageCount, uint_32 animDelay)
{
    Sprite *newSprite = (Sprite *)malloc(sizeof(Sprite));
    newSprite->health = NULL;
    return sprite_animated_init(newSprite, images, imageCount, animDelay);
}

Sprite *sprite_new(Image *image)
{
    Sprite *newSprite = (Sprite *)malloc(sizeof(Sprite));
    newSprite->health = NULL;
    return sprite_init(newSprite, image);
}

Sprite *sprite_animated_init(Sprite *sprite, Image *images[], uint_32 imageCount, uint_32 animDelay)
{
    sprite->frameCounter = 0;
    sprite->animDelay = animDelay;
    sprite->imageCount = imageCount;
    sprite->currentImageIndex = 0;

    sprite->images = (Image **)malloc(sizeof(Image *) * imageCount);

    for (uint_32 i = 0; i < imageCount; ++i)
        *(sprite->images + i) = images[i];

    sprite->currentImage = *sprite->images;
    sprite->size.x = sprite->currentImage->width;
    sprite->size.y = sprite->currentImage->height;
    return sprite;
}

Sprite *sprite_init(Sprite *sprite, Image *image)
{
    sprite->frameCounter = 0;
    sprite->animDelay = 0;
    sprite->imageCount = 1;
    sprite->currentImageIndex = 0;
    sprite->currentImage = image;

    return sprite;
}

void sprite_Draw(Sprite *sprite)
{
    if(sprite->currentImage)
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
    else if (shape == BOX || shape == BOX_TRIGGER)
    {
        sprite->boundingVolume.size = sprite->size;
    }
    else
        return;
}