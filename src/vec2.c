#include "libs.h"
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
    return v1.x * v2.x + v1.y * v2.y;
}

float vec2_getLength(Vec2 vec)
{
    return sqrt(vec2_dot(vec, vec));
}

Vec2f vec2_normalize(Vec2 vec)
{
    float x = vec.x;
    float y = vec.y;
    float l = vec2_getLength(vec);
    return vec2f_new(x / l, y / l);
}

Vec2 vec2_fromVec2f(Vec2f vec)
{
    Vec2 newVec;
    newVec.x = vec.x;
    newVec.y = vec.y;
    return newVec;
}

Vec2f vec2f_fromVec2(Vec2 vec)
{
    Vec2f newVec;
    newVec.x = vec.x;
    newVec.y = vec.y;
    return newVec;
}

Vec2f vec2f_new(float x, float y)
{
    Vec2f newVec;
    newVec.x = x;
    newVec.y = y;
    return newVec;
}

Vec2f vec2f_mulScalar(Vec2f vec, float scalar)
{
    vec.x *= scalar;
    vec.y *= scalar;
    return vec;
}

float vec2f_dot(Vec2f v1, Vec2f v2)
{
    return v1.x * v2.x + v1.y * v2.y;
}

float vec2f_getLength(Vec2f vec)
{
       return sqrt(vec2f_dot(vec, vec));
}

Vec2f vec2f_normalize(Vec2f vec)
{
    float x = vec.x;
    float y = vec.y;
    float l = vec2f_getLength(vec);
    return vec2f_new(x / l, y / l);
}