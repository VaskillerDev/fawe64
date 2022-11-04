#pragma once
#include "libs.h"
#include "event.h"
#include "hp.h"

struct Sprite
{
    Image* currentImage;
    Hp* health;
    Image** images;
    
    uint_32 currentImageIndex;
    uint_32 imageCount;
    uint_32 frameCounter;
    uint_32 animDelay;

    Vec2 position;
    Vec2 size;
    BoundingVolume boundingVolume;

    bool isTile;
    bool isHide;
    bool isFlipH;
    bool useCustomColors;
    uint_16 colors[4];
};

typedef struct Sprite Sprite;

Sprite* sprite_new(Image* image);
void sprite_delete(Sprite* sprite);
Sprite* sprite_animated_init(Sprite* sprite, Image* images[], uint_32 imageCount, uint_32 animDelay);
Sprite* sprite_init(Sprite* sprite, Image* image);

void sprite_setFlipH(Sprite* sprite, bool flip);

void sprite_initBoundingVolume(Sprite* sprite, BoundingVolumeShape shape, BoundingVolumeTag tag);

void sprite_draw(Sprite* sprite);