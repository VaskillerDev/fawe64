#include "libs.h"

typedef Vec2 NavPoint;

struct NavRoot
{
    NavPoint navPointArray[16];
    uint_32 navPointArraySize = 0;
    uint_32 currentPointIndex = 0;
};

NavPoint *Navigation_GetCurrentNavPoint(NavRoot *const navRoot)
{
    return &navRoot->navPointArray[navRoot->currentPointIndex];
}

NavPoint *Navigation_NextNavPoint(NavRoot *const navRoot)
{
    navRoot->currentPointIndex = navRoot->currentPointIndex % navRoot->navPointArraySize;
    return &navRoot->navPointArray[navRoot->currentPointIndex];
}

void Navigation_Move(Enemy *target, NavRoot *root, float moveSpeed)
{
    NavPoint *navPoint = Navigation_GetCurrentNavPoint(root);
    Vec2 moveDir = vec2_div(navPoint, target->sprite->position);

    if (vec2_getLength(moveDir) <= 2)
    {
        navPoint = Navigation_NextNavPoint(root);
        moveDir = vec2_div(navPoint, target->sprite->position);
    }

    target->sprite->position = vec2_add(target->sprite->position, vec2_normalize(moveDir) * moveSpeed);
}
