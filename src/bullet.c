#include "libs.h"

UT_icd bullet_icd = {sizeof(Bullet ), NULL, NULL, NULL};

static const struct Bullet EMPTY_BULLET_TEMPLATE;

void bullet_new(Bullet* bullet, Vec2 startPosition) {
  bullet->speed = 2;
  bullet->position = vec2f_fromVec2 (startPosition);
  Vec2 playerPosition = player_getInstance()->sprite->position;
  bullet->direction = vec2_fromPoints (
      vec2_fromVec2f (bullet->position), playerPosition
      );
}

void bullet_update(Bullet* bullet) {
  Vec2f normalizeDir = vec2_normalize(bullet->direction);
  bullet->position = vec2f_add(bullet->position, normalizeDir);
}

void bullet_draw(Bullet* bullet) {
  uint16_t* col  = DRAW_COLORS;
  *DRAW_COLORS = 0x33;
  oval (bullet->position.x, bullet->position.y, 4, 4);
  *DRAW_COLORS = *col;
}

static bool bullet_checkLevelBounds(Vec2f position) {
  float addingValue = 10;
  float rightOrUpSide = 160 + addingValue;
  float leftOrDown = 0 - addingValue;

  if (position.x >= rightOrUpSide || position.y >= rightOrUpSide) {
      return true;
  }
  if (position.x <= leftOrDown || position.y <= leftOrDown) {
      return true;
  }
  return false;
}

// manager

BulletManager bulletManager_new() {
  struct BulletManager manager = {
      .bulletArray = {},
      .lastIndex = 0,
  };

  return manager;
}

void bulletManager_createBullet(BulletManager* manager, Vec2 startPosition) {
  Bullet* bullet = (Bullet*) malloc (sizeof (Bullet));
  bullet_new (bullet, startPosition);

  int len = (sizeof (manager->bulletArray) / sizeof (Bullet)) - 1;
  for (int i = 0; i < len; i++) {
      Bullet* b = &manager->bulletArray[i];
      if (b->speed == 0) {
          manager->bulletArray[i] = *bullet;
          manager->lastIndex +=1;
          break;
      }
  }
}

void bulletManager_update(BulletManager* manager) {

  int len = (sizeof (manager->bulletArray) / sizeof (Bullet)) - 1;
  if (len <= 0) return;

  for (int i = 0; i < len; i++)
  {
      Bullet* b = &manager->bulletArray[i];
      if (b->speed == 0) continue;
      bullet_update (b);
      bullet_draw (b);

      bool isExitLevel = bullet_checkLevelBounds (b->position);
      if (isExitLevel) {
        manager->bulletArray[i] = EMPTY_BULLET_TEMPLATE;
        manager->lastIndex -=1;
      }
  }
}

void bulletManager_draw(BulletManager* manager) {
  int len = (sizeof (manager->bulletArray) / sizeof (Bullet)) - 1;
  if (len <= 0) return;

  for (int i = 0; i < len; i++)
    {
      Bullet* b = &manager->bulletArray[i];
      if (b->speed == 0) continue;
      bullet_draw (b);
    }
}