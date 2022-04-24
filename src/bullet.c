#include "libs.h"

UT_icd bullet_icd = {sizeof(Bullet ), NULL, NULL, NULL};

static const struct Bullet EMPTY_BULLET_TEMPLATE;

void bullet_new(Bullet* bullet, BulletMetaData metaData) {
  bullet->metaData = metaData;
  bullet->position = vec2f_fromVec2 (bullet->metaData.startPosition);
  Vec2 playerPosition = player_getInstance()->sprite->position;
  bullet->direction = vec2_fromPoints (
      vec2_fromVec2f (bullet->position), playerPosition
      );
}

bool bullet_isEmpty(Bullet* bullet) {
  return
  (uint_8)bullet->position.x == (uint_8)EMPTY_BULLET_TEMPLATE.position.x
  && (uint_8)bullet->position.y == (uint_8)EMPTY_BULLET_TEMPLATE.position.y
  && bullet->metaData.speed == EMPTY_BULLET_TEMPLATE.metaData.speed;
}

void bullet_update(Bullet* bullet) {
  Vec2f normalizeDir = vec2_normalize(bullet->direction);
  bullet->position = vec2f_add(bullet->position,
                               vec2f_mulScalar(normalizeDir, bullet->metaData.speed));
  bullet->metaData.lifetime -= 1;

  Vec2 position = vec2_fromVec2f (bullet->position);

  if (bullet->metaData.senderType == BulletSenderType_Enemy) { // отправитель - противник
      Vec2 playerPosition = player_getInstance()->sprite->position;
      Vec2 distance = vec2_sub(playerPosition, position);

      if (vec2_getLength (distance) < 8) {
          PlayerHasGotBulletCollisionEvent event = {
              .damage = 2,
          };
          eventEmitter_emit (&player_getInstance()->emitter, E_PLAYER_HAS_GOT_BULLET_COLLISION, &event);
        }
      return;
  }

  if (bullet->metaData.senderType == BulletSenderType_Player) { // отправитель - игрок
      Level* l = player_getInstance()->level;
      Enemy* nearEnemy = level_findNearestEnemy (l, position);
      if (nearEnemy != NULL) {
          Vec2 distance = vec2_sub(nearEnemy->sprite->position, position);

          if (vec2_getLength (distance) < 8) {
              EnemyHasGotBulletCollisionEvent event = {
                  .damage = 2,
                  .enemy = nearEnemy
              };
              eventEmitter_emit (&nearEnemy->emitter, E_ENEMY_HAS_GOT_BULLET_COLLISION, &event);
          }
      }
      return;
  }

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

void bulletManager_createBullet(BulletManager* manager, BulletMetaData metaData) {
  Bullet* bullet = (Bullet*) malloc (sizeof (Bullet));
  bullet_new (bullet, metaData);

  int len = (sizeof (manager->bulletArray) / sizeof (Bullet)) - 1;
  for (int i = 0; i < len; i++) {
      Bullet* b = &manager->bulletArray[i];
      if (bullet_isEmpty(b)) {
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
      if (bullet_isEmpty(b)) continue;
      bullet_update (b);
      bullet_draw (b);

      bool isOutOfLevel = bullet_checkLevelBounds (b->position);
      bool isLifetimeExpired = b->metaData.lifetime <= 0;
      if (isOutOfLevel || isLifetimeExpired) {
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
      if (bullet_isEmpty(b)) continue;
      bullet_draw (b);
    }
}