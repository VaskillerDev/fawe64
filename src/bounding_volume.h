#pragma once
#include "event.h"
#include "enemy.h"

typedef enum BoundingVolumeTag {
    BoundingVolumeTag_Unknown,
    BoundingVolumeTag_Player,
    BoundingVolumeTag_Enemy,
    BoundingVolumeTag_Tile,
} BoundingVolumeTag;

typedef enum BoundingVolumeShape
{
    SPHERE,
    BOX,
    BOX_TRIGGER
} BoundingVolumeShape;

struct BoundingVolume
{
    BoundingVolumeShape shape;
    BoundingVolumeTag tag;
    Vec2* position;
    Vec2 size;

    EventEmitter emitter;
    bool isEmitterExist;
};


bool CheckCollision(BoundingVolume* bv1, BoundingVolume* bv2);
bool IsBox(BoundingVolume* bv);

void on_collision(BoundingVolume *bv1, BoundingVolume *bv2);