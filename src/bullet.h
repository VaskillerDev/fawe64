#pragma once
#include "libs.h"


typedef struct Bullet {
    Vec2f position;
    Vec2 direction;
    int speed;
} Bullet;

void bullet_new(Bullet* bullet, Vec2 startPosition);

void bullet_update(Bullet* bullet);

void bullet_draw(Bullet* bullet);

typedef struct BulletManager {
    Bullet bulletArray[8];
    uint_8 lastIndex;
} BulletManager;

BulletManager bulletManager_new();

void bulletManager_createBullet(BulletManager* manager, Vec2 startPosition);

void bulletManager_update(BulletManager* manager);

void bulletManager_draw(BulletManager* manager);

static bool bullet_checkLevelBounds(Vec2f position);

