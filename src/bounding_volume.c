#include"libs.h"

bool CheckCollision(BoundingVolume *bv1, BoundingVolume *bv2)
{
    if (bv1->shape == SPHERE && bv2->shape == SPHERE)
    {
        Vec2 dir = vec2_fromPoints(*bv1->position, *bv2->position);
        float distance = vec2_getLength(dir);

        if (distance < bv1->size.x + bv2->size.x)
        {
            return true;
        }
    }
    else if (bv1->shape == BOX && bv2->shape == BOX)
    {
        Vec2 pos1 = *bv1->position;
        Vec2 hSize1 = vec2_div(bv1->size, vec2_new(2, 2));
        Vec2 rect1[4];

        Vec2 pos2 = *bv2->position;
        Vec2 hSize2 = vec2_div(bv2->size, vec2_new(2, 2));
        Vec2 rect2[4];

        rect1[0] = vec2_add(pos1, vec2_mul(hSize1, vec2_new(1, -1)));
        rect1[1] = vec2_add(pos1, vec2_mul(hSize1, vec2_new(-1, -1)));
        rect1[2] = vec2_add(pos1, vec2_mul(hSize1, vec2_new(-1, 1)));
        rect1[3] = vec2_add(pos1, hSize1);

        rect2[0] = vec2_add(pos2, vec2_mul(hSize2, vec2_new(1, -1)));
        rect2[1] = vec2_add(pos2, vec2_mul(hSize2, vec2_new(-1, -1)));
        rect2[2] = vec2_add(pos2, vec2_mul(hSize2, vec2_new(-1, 1)));
        rect2[3] = vec2_add(pos2, hSize2);

        if (rect1[0].x >= rect2[1].x && rect1[0].x <= rect2[0].x)
            if (rect1[0].y >= rect2[0].y && rect1[0].y <= rect2[2].y)
                return true;

        if (rect1[1].x >= rect2[1].x && rect1[1].x <= rect2[0].x)
            if (rect1[1].y >= rect2[0].y && rect1[1].y <= rect2[2].y)
                return true;

        if (rect1[2].x >= rect2[1].x && rect1[2].x <= rect2[0].x)
            if (rect1[2].y >= rect2[0].y && rect1[2].y <= rect2[2].y)
                return true;

        if (rect1[3].x >= rect2[1].x && rect1[3].x <= rect2[0].x)
            if (rect1[3].y >= rect2[0].y && rect1[3].y <= rect2[2].y)
                return true;
        /////////////////////////////////////////////////////////////////////////////////////
        if (rect2[0].x >= rect1[1].x && rect2[0].x <= rect1[0].x)
            if (rect2[0].y >= rect1[0].y && rect2[0].y <= rect1[2].y)
                return true;

        if (rect2[1].x >= rect1[1].x && rect2[1].x <= rect1[0].x)
            if (rect2[1].y >= rect1[0].y && rect2[1].y <= rect1[2].y)
                return true;

        if (rect2[2].x >= rect1[1].x && rect2[2].x <= rect1[0].x)
            if (rect2[2].y >= rect1[0].y && rect2[2].y <= rect1[2].y)
                return true;

        if (rect2[3].x >= rect1[1].x && rect2[3].x <= rect1[0].x)
            if (rect2[3].y >= rect1[0].y && rect2[3].y <= rect1[2].y)
                return true;
    }
    else if (bv1->shape != bv2->shape)
    {
        if (bv1->shape != SPHERE)
        {
            BoundingVolume *t = bv2;
            bv2 = bv1;
            bv1 = t;
        }

        float r = bv1->size.x;
        Vec2 spherePos = *bv1->position;
        Vec2 pos = *bv2->position;
        Vec2 hSize = vec2_div(bv2->size, vec2_new(2, 2));
        Vec2 rect1[4];

        rect1[0] = vec2_add(pos, vec2_mul(hSize, vec2_new(1, -1)));
        rect1[1] = vec2_add(pos, vec2_mul(hSize, vec2_new(-1, -1)));
        rect1[2] = vec2_add(pos, vec2_mul(hSize, vec2_new(-1, 1)));
        rect1[3] = vec2_add(pos, hSize);

        if (spherePos.x >= rect1[1].x && spherePos.x <= rect1[0].x)
            if (spherePos.y >= rect1[0].y && spherePos.y <= rect1[2].y)
                return true;

        if (vec2_getLength(vec2_sub(spherePos, rect1[0])) <= r)
            return true;
        if (vec2_getLength(vec2_sub(spherePos, rect1[1])) <= r)
            return true;
        if (vec2_getLength(vec2_sub(spherePos, rect1[2])) <= r)
            return true;
        if (vec2_getLength(vec2_sub(spherePos, rect1[3])) <= r)
            return true;

        Vec2f rDir = vec2f_mulScalar(vec2_normalize(vec2_sub(*bv2->position, *bv1->position)), r);

        Vec2 rPoint = vec2_add(spherePos, vec2_fromVec2f(rDir));

        if (rPoint.x >= rect1[1].x && rPoint.x <= rect1[0].x)
            if (rPoint.y >= rect1[0].y && rPoint.y <= rect1[2].y)
                return true;
    }

    return false;
}