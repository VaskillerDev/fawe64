#pragma once
#include"libs.h"

typedef enum BoundingVolumeShape
{
    SPHERE,
    BOX
} BoundingVolumeShape;

struct BoundingVolume
{
    BoundingVolumeShape shape;
    Vec2* position;
    Vec2 size;
};

typedef struct BoundingVolume BoundingVolume;

bool CheckCollision(BoundingVolume* bv1, BoundingVolume* bv2);