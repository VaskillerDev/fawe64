#pragma once
#include "sprite.h"
#include "vec2.h"
#include "stdint.h"
#include "image.h"

typedef enum BulletSenderType {
    BulletSenderType_Unknown,
    BulletSenderType_Enemy,
    BulletSenderType_Player
} BulletSenderType;

typedef struct BulletMetaData {
    BulletSenderType senderType;
    Sprite* owner;
    Vec2 startPosition;
    uint8_t lifetime;
    uint8_t speed;
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
    uint8_t lastIndex;
} BulletManager;

BulletManager bulletManager_new();

void bulletManager_createBullet(BulletManager* manager, BulletMetaData metaData);

void bulletManager_update(BulletManager* manager);

void bulletManager_draw(BulletManager* manager);

static bool bullet_checkLevelBounds(Vec2f position);

