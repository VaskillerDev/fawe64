#include "libs.h"
#include <math.h>

#define ATTACK_ANIMATION_TIMEOUT_VALUE 30

#define GAMEPAD_UP 64
#define GAMEPAD_DOWN 128
#define GAMEPAD_LEFT 16
#define GAMEPAD_RIGHT 32

static Player *globalPlayerRef = NULL;
static Player globalPlayer = {};

bool player_checkTileCollision(Sprite *player, Level *level, Vec2 dir)
{
  Vec2 originalPos = vec2_new(player->position.x, player->position.y);
  Vec2 pos = vec2_new((originalPos.x - 24 + 8) / 16, (originalPos.y - 24 + 8) / 16);
  Vec2 targetPos = vec2_add(pos, dir);

  if (targetPos.x < 0 || targetPos.x > 7)
    return true;

  if (targetPos.y < 0 || targetPos.y > 7)
    return true;

  return level->levelChunk->tiles[targetPos.y * 8 + targetPos.x].collision;
}

bool player_checkCollision(Sprite *player, Level *level, Vec2 dir)
{
  if (player->position.x <= 23 && dir.x == -1)
  {
    return true;
  }

  if (player->position.x >= 137 && dir.x == 1)
  {
    return true;
  }

  if (player->position.y <= 23 && dir.y == -1)
  {
    return true;
  }

  if (player->position.y >= 137 && dir.y == 1)
  {
    return true;
  }

  Sprite **currentObject = NULL;
  while ((currentObject = (Sprite **)utarray_next(level->objects, currentObject)))
  {
    if (player == *currentObject)
      continue;

    if ((*currentObject)->boundingVolume.shape == BOX_TRIGGER)
      continue;

    if ((*currentObject)->isTile && !level->isTilesActive)
      continue;

    bool isClash = CheckCollision(&player->boundingVolume, &(*currentObject)->boundingVolume);
    if (!isClash)
      continue;

    Vec2 objPos = (*currentObject)->position;

    if ((*currentObject)->size.x == 16 && (*currentObject)->size.y == 16)
    {
    RAY_CASTING:
      currentObject;
      Vec2f rayDir = vec2_normalize(vec2_sub(objPos, player->position));
      if (fabsf(fabsf(rayDir.x) - fabsf(rayDir.y)) < 0.00000001)
        continue;

      (fabsf(rayDir.x) > fabsf(rayDir.y)) ? (rayDir.y = 0) : (rayDir.x = 0);
      rayDir = vec2f_normalize(rayDir);

      if (vec2f_dot(rayDir, vec2f_fromVec2(dir)) > 0)
        return true;
    }
    else
    {
      bool horizontal = (*currentObject)->size.x > (*currentObject)->size.y;

      Vec2f rayDir = vec2_normalize(vec2_sub(objPos, player->position));

      if (horizontal)
      {
        if (abs((*currentObject)->position.y - player->position.y) < 8)
          goto RAY_CASTING;

        if (abs(dir.y) > 0)
          if ((rayDir.y > 0 && dir.y > 0) || (rayDir.y < 0 && dir.y < 0))
          {
            if (abs((*currentObject)->position.x - player->position.x) < (*currentObject)->size.x / 2)
            {
              return true;
            }
          }
      }

      if (!horizontal)
      {
        if (abs((*currentObject)->position.x - player->position.x) < 8)
          goto RAY_CASTING;

        if (abs(dir.x) > 0)
          if ((rayDir.x > 0 && dir.x > 0) || (rayDir.x < 0 && dir.x < 0))
          {
            if (abs((*currentObject)->position.y - player->position.y) < (*currentObject)->size.y / 2)
            {
              return true;
            }
          }
      }
    }
  }

  return false;
}

Player *player_getInstance()
{
  if (globalPlayerRef == NULL)
  {
    trace("Player instance reference not found");
  }
  return globalPlayerRef;
}

Player *player_initInstance(PlayerInitInstanceArgs args)
{
  if (globalPlayerRef == NULL)
  {
    globalPlayer = player_new(args.level, args.gameState, args.spawnPosition);
    globalPlayerRef = &globalPlayer;
  }

  return globalPlayerRef;
}

Player player_new(Level *level, GameState *gameState, Vec2 spawnPosition)
{

  struct Player player = {
      .actionState = PlayerAction_Idle,
      .movementDirection = PlayerDir_Bottom,
      .sprite = NULL,
      .gameState = gameState,
      .level = level,
      .speed = 1.5f,
      .emitter = eventEmitter_new(),
      .collisionBulletTimer = timer_new(32, false),

      .idleRightFrames = {
          imagePool_getImage(level->imagePool, PoolIdx_PiligrimIdleRight0),
          imagePool_getImage(level->imagePool, PoolIdx_PiligrimIdleRight1),
          imagePool_getImage(level->imagePool, PoolIdx_PiligrimIdleRight2)},
      .goRightFrames = {imagePool_getImage(level->imagePool, PoolIdx_PiligrimGoRight0), imagePool_getImage(level->imagePool, PoolIdx_PiligrimGoRight1), imagePool_getImage(level->imagePool, PoolIdx_PiligrimGoRight2)},
      .idleUpFrames = {imagePool_getImage(level->imagePool, PoolIdx_PiligrimIdleUp0), imagePool_getImage(level->imagePool, PoolIdx_PiligrimIdleUp1), imagePool_getImage(level->imagePool, PoolIdx_PiligrimIdleUp2)},
      .goUpFrames = {imagePool_getImage(level->imagePool, PoolIdx_PiligrimGoUp0), imagePool_getImage(level->imagePool, PoolIdx_PiligrimGoUp1), imagePool_getImage(level->imagePool, PoolIdx_PiligrimGoUp2)},
      .idleLeftFrames = {imagePool_getImage(level->imagePool, PoolIdx_PiligrimIdleLeft0), imagePool_getImage(level->imagePool, PoolIdx_PiligrimIdleLeft1), imagePool_getImage(level->imagePool, PoolIdx_PiligrimIdleLeft2)},
      .goLeftFrames = {imagePool_getImage(level->imagePool, PoolIdx_PiligrimGoLeft0), imagePool_getImage(level->imagePool, PoolIdx_PiligrimGoLeft1), imagePool_getImage(level->imagePool, PoolIdx_PiligrimGoLeft2)},
      .idleBottomFrames = {imagePool_getImage(level->imagePool, PoolIdx_PiligrimIdleBottom0), imagePool_getImage(level->imagePool, PoolIdx_PiligrimIdleBottom1), imagePool_getImage(level->imagePool, PoolIdx_PiligrimIdleBottom2)},
      .goBottomFrames = {imagePool_getImage(level->imagePool, PoolIdx_PiligrimGoBottom0), imagePool_getImage(level->imagePool, PoolIdx_PiligrimGoBottom1), imagePool_getImage(level->imagePool, PoolIdx_PiligrimGoBottom2)},
      .attackLeft = {
          imagePool_getImage(level->imagePool, PoolIdx_PiligrimAttackLeft),
          imagePool_getImage(level->imagePool, PoolIdx_PiligrimAttackLeft),
          imagePool_getImage(level->imagePool, PoolIdx_PiligrimAttackLeft),
      },
      .attackRight = {
          imagePool_getImage(level->imagePool, PoolIdx_PiligrimAttackRight),
          imagePool_getImage(level->imagePool, PoolIdx_PiligrimAttackRight),
          imagePool_getImage(level->imagePool, PoolIdx_PiligrimAttackRight),
      },
      .attackUp = {
          imagePool_getImage(level->imagePool, PoolIdx_PiligrimAttackUp),
          imagePool_getImage(level->imagePool, PoolIdx_PiligrimAttackUp),
          imagePool_getImage(level->imagePool, PoolIdx_PiligrimAttackUp),
      },
      .attackBottom = {
          imagePool_getImage(level->imagePool, PoolIdx_PiligrimAttackBottom),
          imagePool_getImage(level->imagePool, PoolIdx_PiligrimAttackBottom),
          imagePool_getImage(level->imagePool, PoolIdx_PiligrimAttackBottom),
      },
      .sword = sword_new(level),
      .attackAnimationTimeout = ATTACK_ANIMATION_TIMEOUT_VALUE,
      .itemsCount = {10, 10, 10},
      .selectorIndex = PlayerItem_Count};

  Sprite *playerSprite = level_spawnObject(level);
  sprite_animated_init(playerSprite, player.idleBottomFrames, 3, 10);
  player.sprite = playerSprite;
  player.sprite->position = spawnPosition;

  sprite_initBoundingVolume(player.sprite, BOX, BoundingVolumeTag_Player);
  player.health = hp_new(2, &player, 20, 20, false);

  player.sprite->boundingVolume.size = vec2_new(12, 12);

  eventEmitter_on(&player.health.emitter, E_HP_POINTS_OVER, &on_player_death);
  eventEmitter_on(&player.sword.emitter, E_SWORD_ATTACK_HIT, &on_player_attack);
  eventEmitter_on(&player.emitter, E_PLAYER_HAS_GOT_BULLET_COLLISION, &on_player_has_got_bullet_collision);
  eventEmitter_on(&player.emitter, E_PLAYER_ATTACK_ANIMATION_TIMEOUT, &on_player_attack_animation_timeout);
  eventEmitter_on(&player.emitter, E_LEVEL_CHUNK_MOVED, &on_player_level_chunk_moved);
  eventEmitter_on(&player.emitter, E_PLAYER_ENTER_DUNGEON, &on_player_enter_dungeon);
  eventEmitter_on(&player.collisionBulletTimer.emitter, E_TIMER_EXPIRED, &on_collision_bullet_timer_expired);

  player.itemImages[0] = player.goBottomFrames[0];
  player.itemImages[1] = level->imagePool->images[PoolIdx_Bomb];
  player.itemImages[2] = player.goBottomFrames[0];

  return player;
}

void player_respawn(PlayerInitInstanceArgs args)
{
  Player *currentPlayer = player_getInstance();

  uint_8 currentHP = currentPlayer->health.currentPoints;
  uint_8 currentSelector = currentPlayer->selectorIndex;
  uint_8 currentItemCount[PlayerItem_Count];

  for (uint_8 i = 0; i < PlayerItem_Count; ++i)
  {
    currentItemCount[i] = currentPlayer->itemsCount[i];
  }

  globalPlayerRef = NULL;
  currentPlayer = player_initInstance(args);

  currentPlayer->health.currentPoints = currentHP;
  currentPlayer->selectorIndex = currentSelector;

  for (uint_8 i = 0; i < PlayerItem_Count; ++i)
  {
    currentPlayer->itemsCount[i] = currentItemCount[i];
  }
}

void on_player_enter_dungeon(PlayerEnterDungeonEvent *e)
{
  player_getInstance()->sprite->position = vec2_fromVec2f(e->startPosition);
}

void on_collision_bullet_timer_expired(TimerExpiredEvent *e)
{
  timer_reload(e->timer);
}

void on_player_has_got_bullet_collision(PlayerHasGotBulletCollisionEvent *e)
{
  Player *player = player_getInstance();
  Timer *timer = &player->collisionBulletTimer;

  if (timer->isPause)
  {
    timer_start(timer);
    hp_substract(&player->health, e->damage);
  }
}

/**
 * Вызывается в момент начала атаки игроком
 * @param e
 */
void on_player_attack(EnemySwordAttackHitEvent e)
{

  Vec2 offsetPosition = {0, 0};

  switch (e.player->movementDirection)
  {
  case PlayerDir_Left:
  {
    offsetPosition = vec2_new(-4, 0);
    sprite_animated_init(e.sword->sprite, e.sword->lSwordFrames, 3, 10);
  }
  break;
  case PlayerDir_Right:
  {
    offsetPosition = vec2_new(4, 0);
    sprite_animated_init(e.sword->sprite, e.sword->lSwordFrames, 3, 10);
    sprite_setFlipH(e.sword->sprite, true);
  }
  break;
  case PlayerDir_Bottom:
  {
    offsetPosition = vec2_new(0, 4);
    sprite_animated_init(e.sword->sprite, e.sword->bottomSwordFrames, 3, 10);
  }
  break;
  case PlayerDir_Up:
  {
    offsetPosition = vec2_new(0, -4);
    sprite_animated_init(e.sword->sprite, e.sword->upSwordFrames, 3, 10);
  }
  break;
  }
  e.sword->sprite->position = vec2_add(e.sword->sprite->position, offsetPosition);
  e.player->actionState = PlayerAction_Attack;
}

void player_move_left(Player *player)
{
  player->movementDirection = PlayerDir_Left;
  if (!player_checkCollision(player->sprite, player->level, vec2_new(-1, 0)))
  {
    player->speedDir = vec2f_add(player->speedDir, vec2f_new(-1, 0));
  }
}

void player_move_right(Player *player)
{
  player->movementDirection = PlayerDir_Right;
  if (!player_checkCollision(player->sprite, player->level, vec2_new(1, 0)))
  {
    player->speedDir = vec2f_add(player->speedDir, vec2f_new(1, 0));
    player->speedDir = vec2f_add(player->speedDir, vec2f_new(1, 0));
  }
}

void player_move_up(Player *player)
{
  player->movementDirection = PlayerDir_Up;
  if (!player_checkCollision(player->sprite, player->level, vec2_new(0, -1)))
  {
    player->speedDir = vec2f_add(player->speedDir, vec2f_new(0, -1));
  }
}

void player_move_down(Player *player)
{
  player->movementDirection = PlayerDir_Bottom;
  if (!player_checkCollision(player->sprite, player->level, vec2_new(0, 1)))
  {
    player->speedDir = vec2f_add(player->speedDir, vec2f_new(0, 1));
  }
}

void player_update(Player *player, Level *level)
{
  uint8_t gamepad = *GAMEPAD1;
  player->speedDir = vec2f_new(0, 0);

  static bool button_1_prev = false;
  static bool button_2_prev = false;
  static uint8_t button_1_pressTime = 0;
  static uint8_t button_2_pressTime = 0;
  static uint8_t button_L_pressTime = 0;
  static uint8_t button_R_pressTime = 0;
  static uint8_t pauseOff_time = 0;

  bool button_1 = gamepad & BUTTON_1;
  bool button_2 = gamepad & BUTTON_2;

  if (button_1)
  {
    ++button_1_pressTime;
    gamepad -= BUTTON_1;

    if (level->pause)
    {
      level->pause = false;
      pauseOff_time = 0;
    }
  }
  else
  {
    if (pauseOff_time > 15 && button_1_pressTime > 0 && button_1_pressTime < 20)
    {
      player_useItem();
    }

    button_1_pressTime = 0;
  }

  if (!level->pause)
    ++pauseOff_time;

  if (button_2)
  {
    ++button_2_pressTime;
    gamepad -= BUTTON_2;
  }
  else
  {
    button_2_pressTime = 0;
  }

  if (button_1_pressTime >= 20)
  {
    level->pause = true;
  }

  if (level->pause)
  {
    if (gamepad == GAMEPAD_LEFT)
    {
      ++button_L_pressTime;

      if (button_L_pressTime % 15 == 0)
      {
      MOVE_SELECTOR_LEFT:
        if (player->selectorIndex > 0)
        {
          if (player->selectorIndex == PlayerItem_Count)
          {
            player->selectorIndex = 0;
          }
          else
          {
            --player->selectorIndex;
          }
        }
      }
    }
    else
    {
      if (button_L_pressTime > 0 && button_L_pressTime < 10)
      {
        button_L_pressTime = 0;
        goto MOVE_SELECTOR_LEFT;
      }
      button_L_pressTime = 0;
    }

    if (gamepad == GAMEPAD_RIGHT)
    {
      ++button_R_pressTime;
      if (button_R_pressTime % 15 == 0)
      {
      MOVE_SELECTOR_RIGHT:
        if (player->selectorIndex == PlayerItem_Count)
        {
          player->selectorIndex = PlayerItem_Count - 1;
        }
        else
        {
          if (player->selectorIndex < PlayerItem_Count - 1)
          {
            ++player->selectorIndex;
          }
        }
      }
    }
    else
    {
      if (button_R_pressTime > 0 && button_R_pressTime < 10)
      {
        button_R_pressTime = 0;
        goto MOVE_SELECTOR_RIGHT;
      }
      button_R_pressTime = 0;
    }

    return;
  }

  if (gamepad > 0)
  {
    if (player->sprite->frameCounter == player->sprite->animDelay - 1 && player->sprite->currentImageIndex == 2)
      tone(1000, 1 | (10 << 8), 3, TONE_NOISE | TONE_MODE4);
  }

  if (gamepad == GAMEPAD_LEFT)
  {
    if (player->actionState != PlayerAction_Attack)
    {
      player_move_left(player);
    }
    player->sword.dir = vec2_new(-1, 0);
    goto MOVE_PLAYER;
  }
  if (gamepad == GAMEPAD_RIGHT)
  {
    if (player->actionState != PlayerAction_Attack)
    {
      player_move_right(player);
    }
    player->sword.dir = vec2_new(1, 0);
    goto MOVE_PLAYER;
  }
  if (gamepad == GAMEPAD_DOWN)
  {
    if (player->actionState != PlayerAction_Attack)
    {
      player_move_down(player);
    }
    player->sword.dir = vec2_new(0, 1);
    goto MOVE_PLAYER;
  }
  if (gamepad == GAMEPAD_UP)
  {
    if (player->actionState != PlayerAction_Attack)
    {
      player_move_up(player);
    }
    player->sword.dir = vec2_new(0, -1);
    goto MOVE_PLAYER;
  }

MOVE_PLAYER:

  if (player->actionState == PlayerAction_Attack)
  {
    return;
  }

  player->actionState = vec2f_getLength(player->speedDir) > 0 ? PlayerAction_Go : PlayerAction_Idle;

  // tracef ("actionState %d", player->actionState);
  // tracef ("dir %d", player->movementDirection);

  if (player->actionState == PlayerAction_Go)
  {
    player->speedDir = vec2f_normalize(player->speedDir);
    player->sprite->position = vec2_add(player->sprite->position, vec2_fromVec2f(vec2f_mul(player->speedDir, vec2f_new(player->speed, player->speed))));
  }

  if (button_2)
  {
    sword_attack(&player->sword);
  }

  sword_updatePosition(&player->sword, player->sprite);
  sword_update(player, level);
  timer_update(&player->collisionBulletTimer);

  button_1_prev = button_1;
  button_2_prev = button_2;
}

void player_draw(Player *player, Level *level)
{
  switch (player->actionState)
  {
  case PlayerAction_Idle:
  {
    switch (player->movementDirection)
    {
    case PlayerDir_Right:
      player->sprite->images = player->idleRightFrames;
      break;
    case PlayerDir_Up:
      player->sprite->images = player->idleUpFrames;
      break;
    case PlayerDir_Left:
      player->sprite->images = player->idleLeftFrames;
      break;
    case PlayerDir_Bottom:
      player->sprite->images = player->idleBottomFrames;
      break;
    }
  };
  break;
  case PlayerAction_Go:
  {
    switch (player->movementDirection)
    {
    case PlayerDir_Right:
      player->sprite->images = player->goRightFrames;
      break;
    case PlayerDir_Up:
      player->sprite->images = player->goUpFrames;
      break;
    case PlayerDir_Left:
      player->sprite->images = player->goLeftFrames;
      break;
    case PlayerDir_Bottom:
      player->sprite->images = player->goBottomFrames;
      break;
    }
  };
  break;
  case PlayerAction_Attack:
  {
    switch (player->movementDirection)
    {
    case PlayerDir_Right:
      player->sprite->images = player->attackRight;
      break;
    case PlayerDir_Up:
      player->sprite->images = player->attackUp;
      break;
    case PlayerDir_Left:
      player->sprite->images = player->attackLeft;
      break;
    case PlayerDir_Bottom:
      player->sprite->images = player->attackBottom;
      break;
    }
  };
  break;
  }

  char lText[3];
  lText[0] = player->health.currentPoints / 10 + '0';
  lText[1] = player->health.currentPoints % 10 + '0';
  lText[2] = '\0';
  uint_16 textColors[4] = {4, 0, 0, 0};
  DrawText(lText, 16, 150, textColors);

  if (player->selectorIndex != PlayerItem_Count)
  {
    lText[0] = player->itemsCount[player->selectorIndex] / 10 + '0';
    lText[1] = player->itemsCount[player->selectorIndex] % 10 + '0';
    lText[2] = '\0';
    uint_16 textColors[4] = {4, 0, 0, 0};
    DrawText(lText, 120, 150, textColors);
  }

  if (player->selectorIndex < PlayerItem_Count)
  {
    Image *itemImage = player->itemImages[player->selectorIndex];
    DrawImage(itemImage, 155 - itemImage->width, 155 - itemImage->height, true);
  }

  if (level->pause)
  {
    uint_16 selectorColors[4] = {2, 4, 0, 0};
    textColors[0] = 3;
    textColors[1] = 4;

    for (uint_8 i = 0; i < PlayerItem_Count; i++)
    {
      if (i == player->selectorIndex)
        selectorColors[1] = 3;

      DrawRectangle(45 + 34 * i, 80, 32, 32, selectorColors);
      DrawImage(player->itemImages[i], 45 + 34 * i - player->itemImages[i]->width / 2, 80 - player->itemImages[i]->height / 2, true);

      char amountlText[3];
      amountlText[0] = player->itemsCount[i] / 10 + '0';
      amountlText[1] = player->itemsCount[i] % 10 + '0';
      amountlText[2] = '\0';
      DrawText(amountlText, 45 + 34 * i - 8, 100, textColors);

      if (i == player->selectorIndex)
        selectorColors[1] = 4;
    }
  }
}

void player_postUpdate(Player *player)
{
  if (player->actionState == PlayerAction_Attack)
  {

    uint_8 *timeout = &player->attackAnimationTimeout;
    *timeout -= 1;
    if (*timeout <= 0)
    {

      PlayerAttackAnimationTimeoutEvent event = {
          .timeout = ATTACK_ANIMATION_TIMEOUT_VALUE,
          .player = player};
      eventEmitter_emit(&player->emitter, E_PLAYER_ATTACK_ANIMATION_TIMEOUT, &event);
    }
  }
}

void on_player_death(HpPointsOverEvent *e)
{
  e;
  player_getInstance()->gameState->currentScreen = IN_MENU;
}

void on_player_attack_animation_timeout(PlayerAttackAnimationTimeoutEvent *e)
{
  e->player->sword.sprite->isHide = true;
  e->player->actionState = PlayerAction_Idle;
  e->player->attackAnimationTimeout = e->timeout;
}

void on_player_level_chunk_moved(PlayerLevelChunkMovedEvent *e)
{
  GameState *gs = player_getInstance()->gameState;
  const struct PlayerInitInstanceArgs initArgs = {
      .spawnPosition = e->startPosition,
      .gameState = gs,
      .level = e->level};

  player_respawn(initArgs);
}

void player_useItem()
{
  Player *player = player_getInstance();

  if (player->selectorIndex == PlayerItem_Count)
  {
    return;
  }

  if (player->itemsCount[player->selectorIndex] == 0)
  {
    return;
  }

  switch (player->selectorIndex)
  {
  case PlayerItem_Potion:
    usePoition();
    break;
  case PlayerItem_Bomb:
    if (!setupBomb())
      return;
    break;
  case PlayerItem_PlasticExplosive:
    if (!setupDirectedBomb())
      return;
    break;

  default:
    break;
  }

  --player->itemsCount[player->selectorIndex];
}