#pragma once
#include "libs.h"

struct Vec2
{
    int_32 x;
    int_32 y;
};

struct Vec2f
{
    float x;
    float y;
};

typedef struct Vec2 Vec2;
typedef struct Vec2f Vec2f;

Vec2 vec2_new(int_32 x, int_32 y);
Vec2 vec2_sub(Vec2 p1, Vec2 p2);
Vec2 vec2_add(Vec2 p1, Vec2 p2);
Vec2 vec2_mul(Vec2 v1, Vec2 v2);
Vec2 vec2_div(Vec2 v1, Vec2 v2);
Vec2 vec2_fromPoints(Vec2 p1, Vec2 p2);
float vec2_dot(Vec2 v1, Vec2 v2);
float vec2_getLength(Vec2 vec);
Vec2f vec2_normalize(Vec2 vec);
Vec2 vec2_fromVec2f(Vec2f vec);

Vec2f vec2f_new(float x, float y);
Vec2f vec2f_mulScalar(Vec2f vec, float scalar);