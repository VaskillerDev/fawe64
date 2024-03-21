#include "navigation.h"
#include "enemy.h"
#include "math.h"
#include "sprite.h"

NavPoint *Navigation_GetCurrentNavPoint(struct NavRoot *const navRoot)
{
    return &navRoot->navPointArray[navRoot->currentPointIndex];
}

NavPoint *Navigation_NextNavPoint(struct NavRoot *const navRoot)
{
    ++navRoot->currentPointIndex;

    if(navRoot->currentPointIndex >= navRoot->navPointArraySize
    || navRoot->navPointArray[navRoot->currentPointIndex].x == 101)
    {
        navRoot->currentPointIndex = 0;
    }

    return &navRoot->navPointArray[navRoot->currentPointIndex];
}

void Navigation_Move(struct Enemy *target, struct NavRoot *root, float moveSpeed)
{
    NavPoint navPoint = *Navigation_GetCurrentNavPoint(root);
    Vec2 moveDir = vec2_sub(navPoint, target->sprite->position);

    if (vec2_getLength(moveDir) <= 2)
    {
        navPoint = *Navigation_NextNavPoint(root);
        moveDir = vec2_sub(navPoint, target->sprite->position);
    }
   
    Vec2f delta = vec2f_mulScalar(vec2_normalize(moveDir), moveSpeed);
    Vec2f newPos = vec2f_add(vec2f_fromVec2(target->sprite->position), delta);
    target->sprite->position = vec2_new(round(newPos.x), round(newPos.y));
}
