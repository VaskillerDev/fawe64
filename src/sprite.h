#pragma once
#include "types.h"
#include "event.h"
#include "bounding_volume.h"
#include "image.h"
#include "hp.h"

struct Sprite
{
    Image* currentImage;
    Hp* health;
    Image** images;
    
    uint32_t currentImageIndex;
    uint32_t imageCount;
    uint32_t frameCounter;
    uint32_t animDelay;

    Vec2 position;
    Vec2 size;
    BoundingVolume boundingVolume;

    bool isTile;
    bool isHide;
    bool isFlipH;
    bool useCustomColors;
    uint16_t colors[4];
};

typedef struct Sprite Sprite;

Sprite* sprite_new(Image* image);
void sprite_delete(Sprite* sprite);
Sprite* sprite_animated_init(Sprite* sprite, Image* images[], uint32_t imageCount, uint32_t animDelay);
Sprite* sprite_init(Sprite* sprite, Image* image);

void sprite_setFlipH(Sprite* sprite, bool flip);

void sprite_initBoundingVolume(Sprite* sprite, BoundingVolumeShape shape, BoundingVolumeTag tag);

void sprite_draw(Sprite* sprite);