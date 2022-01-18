#pragma once
#include "types.h"
#include "vec2.h"
#include <stdbool.h>

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