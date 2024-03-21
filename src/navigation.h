#pragma once
#include "types.h"
#include "vec2.h"

typedef Vec2 NavPoint;

typedef struct NavRoot
{
    NavPoint navPointArray[8];
    uint32_t navPointArraySize;
    uint32_t currentPointIndex;
    uint8_t entityId;
} NavRoot;
 
NavPoint *Navigation_GetCurrentNavPoint(struct NavRoot *const navRoot);
NavPoint *Navigation_NextNavPoint(struct NavRoot *const navRoot);
void Navigation_Move(struct Enemy *target, struct NavRoot *root, float moveSpeed);