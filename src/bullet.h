#pragma once
#include "libs.h"

typedef enum BulletSenderType {
    BulletSenderType_Unknown,
    BulletSenderType_Enemy,
    BulletSenderType_Player
} BulletSenderType;

typedef struct BulletMetaData {
    BulletSenderType senderType;
    Sprite* owner;
    Vec2 startPosition;
    Vec2 direction;
    uint_8 lifetime;
    uint_8 speed;
} BulletMetaData;

typedef struct Bullet {
    Vec2f position;
    Vec2 direction;
    BulletMetaData metaData;
    /**
     * Факт столкновения
     */
    bool wasCollision;
} Bullet;

void bullet_new(Bullet* bullet, BulletMetaData metaData);

void bullet_update(Bullet* bullet);

void bullet_draw(Bullet* bullet);

bool bullet_isEmpty(Bullet* bullet);

typedef struct BulletManager {
    Bullet bulletArray[8];
    uint_8 lastIndex;
} BulletManager;

BulletManager bulletManager_new();

void bulletManager_createBullet(BulletManager* manager, BulletMetaData metaData);

void bulletManager_update(BulletManager* manager);

void bulletManager_draw(BulletManager* manager);

static bool bullet_checkLevelBounds(Vec2f position);

