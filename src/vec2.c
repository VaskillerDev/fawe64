#include "vec2.h"
#include <math.h>

Vec2 vec2_new(int_32 x, int_32 y)
{
    Vec2 newVec;
    newVec.x = x;
    newVec.y = y;
    return newVec;
}

Vec2 vec2_sub(Vec2 p1, Vec2 p2)
{
    Vec2 newVec;
    newVec.x = p1.x - p2.x;
    newVec.y = p1.y - p2.y;
    return newVec;
}

Vec2 vec2_add(Vec2 p1, Vec2 p2)
{
    Vec2 newVec;
    newVec.x = p1.x + p2.x;
    newVec.y = p1.y + p2.y;
    return newVec;
}

Vec2 vec2_mul(Vec2 v1, Vec2 v2)
{
    Vec2 newVec;
    newVec.x = v1.x * v2.x;
    newVec.y = v1.y * v2.y;
    return newVec;
}

Vec2 vec2_div(Vec2 v1, Vec2 v2)
{
    Vec2 newVec;
    newVec.x = v1.x / v2.x;
    newVec.y = v1.y / v2.y;
    return newVec;
}

Vec2 vec2_fromPoints(Vec2 p1, Vec2 p2)
{
    return vec2_sub(p2, p1);
}

float vec2_dot(Vec2 v1, Vec2 v2)
{
    return v1.x * v2.x + v2.y * v2.y;
}

float vec2_getLength(Vec2 vec)
{
    return sqrt(vec2_dot(vec, vec));
}