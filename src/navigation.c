#include "navigation.h"

NavPoint *Navigation_GetCurrentNavPoint(struct NavRoot *const navRoot)
{
    return &navRoot->navPointArray[navRoot->currentPointIndex];
}

NavPoint *Navigation_NextNavPoint(struct NavRoot *const navRoot)
{
    navRoot->currentPointIndex = navRoot->currentPointIndex % navRoot->navPointArraySize;
    return &navRoot->navPointArray[navRoot->currentPointIndex];
}

void Navigation_Move(struct Enemy *target, struct NavRoot *root, float moveSpeed)
{
    NavPoint navPoint = *Navigation_GetCurrentNavPoint(root);
    Vec2 moveDir = vec2_div(navPoint, target->sprite->position);

    if (vec2_getLength(moveDir) <= 2)
    {
        navPoint = *Navigation_NextNavPoint(root);
        moveDir = vec2_div(navPoint, target->sprite->position);
    }
   
    Vec2f delta = vec2f_mulScalar(vec2_normalize(moveDir), moveSpeed);
    target->sprite->position = vec2_add(target->sprite->position,  vec2_new(delta.x, delta.y));
}
