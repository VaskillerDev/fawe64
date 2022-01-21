#pragma once
#include "libs.h"

struct Sprite
{
    uint_32 currentImageIndex;
    Image* currentImage;
    Image** images;
    uint_32 imageCount;
    uint_32 frameCounter;
    uint_32 animDelay;

    Vec2 pos;
    Vec2 size;
    BoundingVolume boundingVolume;
};

typedef struct Sprite Sprite;

Sprite* sprite_animated_new(Image* images[], uint_32 imageCount, uint_32 animDelay);
Sprite* sprite_new(Image* image);
Sprite* sprite_animated_init(Sprite* sprite, Image* images[], uint_32 imageCount, uint_32 animDelay);
Sprite* sprite_init(Sprite* sprite, Image* image);


void sprite_initBoundingVolume(Sprite* sprite, BoundingVolumeShape shape);

void sprite_Draw(Sprite* sprite);