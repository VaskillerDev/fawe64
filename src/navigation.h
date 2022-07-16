#include "libs.h"

typedef Vec2 NavPoint;

struct NavRoot
{
    NavPoint navPointArray[16];
    uint_32 navPointArraySize;
    uint_32 currentPointIndex;
};

NavPoint *Navigation_GetCurrentNavPoint(struct NavRoot *const navRoot);
NavPoint *Navigation_NextNavPoint(struct NavRoot *const navRoot);
void Navigation_Move(struct Enemy *target, struct NavRoot *root, float moveSpeed);