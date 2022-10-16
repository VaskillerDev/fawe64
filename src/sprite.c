#include "libs.h"
#include "allocator.h"

#define DEBUG_BOUNDING_VOLUME 0
#define MAX(a, b) (((a) > (b)) ? (a) : (b))
#define MIN(a, b) (((a) < (b)) ? (a) : (b))

Sprite *sprite_new(Image *image)
{
    Sprite *newSprite = (Sprite *)allocate(sizeof(Sprite));

    newSprite->animDelay = 0;
    newSprite->currentImage = NULL;
    newSprite->currentImageIndex = 0;
    newSprite->isFlipH = false;
    newSprite->frameCounter = 0;
    newSprite->health = NULL;
    newSprite->imageCount = 0;
    newSprite->images = NULL;
    newSprite->isHide = false;
    newSprite->isTile = false;

    return sprite_init(newSprite, image);
}

void sprite_delete(Sprite *sprite)
{
    if (sprite->images && sprite->imageCount > 1)
    {
        //alloc_free(sprite->images);
    }

    if (sprite->health)
    {
        //alloc_free(sprite->health);
    }

    alloc_free(sprite);
}

Sprite *sprite_animated_init(Sprite *sprite, Image *images[], uint_32 imageCount, uint_32 animDelay)
{
    sprite->frameCounter = 0;
    sprite->animDelay = animDelay;
    sprite->imageCount = imageCount;
    sprite->currentImageIndex = 0;
    sprite->isFlipH = false;
    sprite->health = NULL;
    sprite->isHide = false;
    if (sprite->imageCount > 0)
    {
        sprite->images = images;

        //for (uint_32 i = 0; i < imageCount; ++i)
         //   sprite->images[i] = images[i];
    }

    sprite->currentImage = *sprite->images;
    sprite->size.x = sprite->currentImage->width;
    sprite->size.y = sprite->currentImage->height;
    return sprite;
}

void sprite_setFlipH(Sprite *sprite, bool flip)
{
  sprite->isFlipH = flip;
}

Sprite *sprite_init(Sprite *sprite, Image *image)
{
    sprite->frameCounter = 0;
    sprite->animDelay = 0;
    sprite->imageCount = 1;
    sprite->currentImageIndex = 0;
    sprite->currentImage = image;
    sprite->health = NULL;
    sprite->isHide = false;

    return sprite;
}

void sprite_draw(Sprite *sprite)
{
    if (sprite->isHide == true) return;

    if (sprite->currentImage)
    {
        sprite->isFlipH ? (sprite->currentImage->flags |= BLIT_FLIP_X) : (sprite->currentImage->flags &= ~BLIT_FLIP_X);
        DrawImage(sprite->currentImage, sprite->position.x - sprite->size.x / 2, sprite->position.y - sprite->size.y / 2, true);
    }

    if (DEBUG_BOUNDING_VOLUME)
        DrawBoundingVolume(&sprite->boundingVolume);

    if (sprite->animDelay == 0)
        return;

    ++sprite->frameCounter;

    if (sprite->frameCounter >= sprite->animDelay && sprite->imageCount > 0)
    {
        sprite->currentImageIndex +=1;
        sprite->currentImageIndex = sprite->currentImageIndex % sprite->imageCount;
        sprite->frameCounter = 0;

        sprite->currentImage = *(sprite->images + sprite->currentImageIndex);
    }
}

void sprite_initBoundingVolume(Sprite *sprite, BoundingVolumeShape shape, BoundingVolumeTag tag)
{
    sprite->boundingVolume.shape = shape;
    sprite->boundingVolume.position = &sprite->position;
    sprite->boundingVolume.tag = tag;
    if (shape == SPHERE)
    {
        sprite->boundingVolume.size.x = MAX(sprite->size.x / 2, sprite->size.y / 2);
        sprite->boundingVolume.size.y = MIN(sprite->size.x / 2, sprite->size.y / 2);
    }
    else if (shape == BOX || shape == BOX_TRIGGER)
    {
        sprite->boundingVolume.size = sprite->size;
    }
}