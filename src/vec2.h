#pragma once
#include "types.h"

struct Vec2
{
    int_32 x;
    int_32 y;
};

typedef struct Vec2 Vec2;

Vec2 vec2_new(int_32 x, int_32 y);
Vec2 vec2_sub(Vec2 p1, Vec2 p2);
Vec2 vec2_add(Vec2 p1, Vec2 p2);
Vec2 vec2_mul(Vec2 v1, Vec2 v2);
Vec2 vec2_div(Vec2 v1, Vec2 v2);
Vec2 vec2_fromPoints(Vec2 p1, Vec2 p2);
float vec2_dot(Vec2 v1, Vec2 v2);
float vec2_getLength(Vec2 vec);