#include "libs.h"
#include <math.h>

#define BUTTON_LUP (BUTTON_LEFT + BUTTON_UP)
#define BUTTON_LDOWN (BUTTON_LEFT + BUTTON_DOWN)
#define BUTTON_RUP (BUTTON_RIGHT + BUTTON_UP)
#define BUTTON_RDOWN (BUTTON_RIGHT + BUTTON_DOWN)

bool player_checkCollision (Sprite *player, Level *level, Vec2 dir)
{
  Sprite **currentObject = NULL;
  while ((currentObject = (Sprite **) utarray_next(level->objects, currentObject)))
    {
      if (player == *currentObject)
        continue;

      if ((*currentObject)->boundingVolume.shape == BOX_TRIGGER)
        continue;

      bool isClash = CheckCollision (&player->boundingVolume, &(*currentObject)->boundingVolume);
      if (!isClash)
        continue;

      Vec2f rayDir = vec2_normalize (vec2_sub ((*currentObject)->pos, player->pos));
      if (fabsf (fabsf (rayDir.x) - fabsf (rayDir.y)) < 0.00000001)
        continue;

      (fabsf (rayDir.x) > fabsf (rayDir.y)) ? (rayDir.y = 0) : (rayDir.x = 0);
      rayDir = vec2f_normalize (rayDir);

      if (vec2f_dot (rayDir, vec2f_fromVec2 (dir)) > 0)
        return true;
    }

  return false;
}

Player player_new (Level *level)
{

  level->imagePool;

  struct Player player = {
      .actionState = PlayerAction_Idle,
      .movementDirection = PlayerDir_Bottom,
      .level = level,
      .sprite = NULL,

      .idleRightFrames = {
          imagePool_getImage (level->imagePool, PoolIdx_PiligrimIdleRight0),
          imagePool_getImage (level->imagePool, PoolIdx_PiligrimIdleRight1),
          imagePool_getImage (level->imagePool, PoolIdx_PiligrimIdleRight2)
      },
      .goRightFrames = {
          imagePool_getImage (level->imagePool, PoolIdx_PiligrimGoRight0),
          imagePool_getImage (level->imagePool, PoolIdx_PiligrimGoRight1),
          imagePool_getImage (level->imagePool, PoolIdx_PiligrimGoRight2)
      },
      .idleUpFrames = {
          imagePool_getImage (level->imagePool, PoolIdx_PiligrimIdleUp0),
          imagePool_getImage (level->imagePool, PoolIdx_PiligrimIdleUp1),
          imagePool_getImage (level->imagePool, PoolIdx_PiligrimIdleUp2)
      },
      .goUpFrames = {
          imagePool_getImage (level->imagePool, PoolIdx_PiligrimGoUp0),
          imagePool_getImage (level->imagePool, PoolIdx_PiligrimGoUp1),
          imagePool_getImage (level->imagePool, PoolIdx_PiligrimGoUp2)
      },
      .idleLeftFrames = {
          imagePool_getImage (level->imagePool, PoolIdx_PiligrimIdleLeft0),
          imagePool_getImage (level->imagePool, PoolIdx_PiligrimIdleLeft1),
          imagePool_getImage (level->imagePool, PoolIdx_PiligrimIdleLeft2)
      },
      .goLeftFrames = {
          imagePool_getImage (level->imagePool, PoolIdx_PiligrimGoLeft0),
          imagePool_getImage (level->imagePool, PoolIdx_PiligrimGoLeft1),
          imagePool_getImage (level->imagePool, PoolIdx_PiligrimGoLeft2)
      },
      .idleBottomFrames = {
          imagePool_getImage (level->imagePool, PoolIdx_PiligrimIdleBottom0),
          imagePool_getImage (level->imagePool, PoolIdx_PiligrimIdleBottom1),
          imagePool_getImage (level->imagePool, PoolIdx_PiligrimIdleBottom2)
      },
      .goBottomFrames = {
          imagePool_getImage (level->imagePool, PoolIdx_PiligrimGoBottom0),
          imagePool_getImage (level->imagePool, PoolIdx_PiligrimGoBottom1),
          imagePool_getImage (level->imagePool, PoolIdx_PiligrimGoBottom2)
      },
  };

  Sprite *playerSprite = level_spawnObject(level);
  sprite_animated_init(playerSprite, player.idleBottomFrames, 3, 10);
  player.sprite = playerSprite;

  sprite_initBoundingVolume (player.sprite, BOX);
  player.speed = 1.5f;

  player.sword = sword_new (level);
  player.sword.damage = 1;
  player.sword.attackDelay = 30;
  return player;
}

void player_move_left (Player *player)
{
  if (!player_checkCollision (player->sprite, player->level, vec2_new (-1, 0))) {
      player->speedDir = vec2f_add (player->speedDir, vec2f_new (-1, 0));
      player->movementDirection = PlayerDirLeft;
  }

}

void player_move_right (Player *player)
{
  if (!player_checkCollision (player->sprite, player->level, vec2_new (1, 0))) {
      player->speedDir = vec2f_add (player->speedDir, vec2f_new (1, 0));player->speedDir = vec2f_add (player->speedDir, vec2f_new (1, 0));
      player->movementDirection = PlayerDir_Right;
  }

}

void player_move_up (Player *player)
{
  if (!player_checkCollision (player->sprite, player->level, vec2_new (0, -1))) {
      player->speedDir = vec2f_add (player->speedDir, vec2f_new (0, -1));
      player->movementDirection = PlayerDir_Up;
  }

}

void player_move_down (Player *player)
{
  if (!player_checkCollision (player->sprite, player->level, vec2_new (0, 1))) {
      player->speedDir = vec2f_add (player->speedDir, vec2f_new (0, 1));
      player->movementDirection = PlayerDir_Bottom;
  }
}

void player_update (Player *player, Level *level)
{
  uint8_t gamepad = *GAMEPAD1;
  player->speedDir = vec2f_new (0, 0);

  bool button_1 = gamepad & BUTTON_1;
  bool button_2 = gamepad & BUTTON_2;

  if (button_1)
    gamepad -= 1;
  if (button_2)
    gamepad -= 2;

  if (gamepad == 16)
    {
      player_move_left (player);
      player->sword.dir = vec2_new (-1, 0);
      goto MOVE_PLAYER;
    }
  if (gamepad == 32)
    {
      player_move_right (player);
      player->sword.dir = vec2_new (1, 0);
      goto MOVE_PLAYER;
    }
  if (gamepad == 128)
    {
      player_move_down (player);
      player->sword.dir = vec2_new (0, 1);
      goto MOVE_PLAYER;
    }
  if (gamepad == 64)
    {
      player_move_up (player);
      player->sword.dir = vec2_new (0, -1);
      goto MOVE_PLAYER;
    }

  MOVE_PLAYER:

  player->actionState = vec2f_getLength (player->speedDir) > 0 ? PlayerAction_Go : PlayerAction_Idle;

  //tracef ("actionState %d", player->actionState);
  //tracef ("dir %d", player->movementDirection);

  if (player->actionState == PlayerAction_Go)
    {
      player->speedDir = vec2f_normalize (player->speedDir);
      player->sprite->pos = vec2_add (player->sprite->pos, vec2_fromVec2f (vec2f_mul (player->speedDir, vec2f_new (player->speed, player->speed))));
    }

  sword_updatePosition (&player->sword, player->sprite);
  sword_update (&player->sword, player->sprite, level);
  if (button_2)
    {
      sword_attack (&player->sword);
    }
}

void player_draw (Player *player, Level *level)
{
  level;
  switch (player->actionState)
    {
      case PlayerAction_Idle:
        {
          switch (player->movementDirection)
            {
              case PlayerDir_Right:player->sprite->images = player->idleRightFrames;
              break;
              case PlayerDir_Up: player->sprite->images = player->idleUpFrames;
              break;
              case PlayerDirLeft: player->sprite->images = player->idleLeftFrames;
              break;
              case PlayerDir_Bottom: player->sprite->images = player->idleBottomFrames;
              break;
            }
          
        };
      break;
      case PlayerAction_Go:
        {
          switch (player->movementDirection)
            {
              case PlayerDir_Right: player->sprite->images = player->goRightFrames;
              break;
              case PlayerDir_Up: player->sprite->images = player->goUpFrames;
              break;
              case PlayerDirLeft: player->sprite->images = player->goLeftFrames;
              break;
              case PlayerDir_Bottom: player->sprite->images = player->goBottomFrames;
              break;
            }
        };
      break;
      case PlayerAction_Attack:
        {
          switch (player->movementDirection)
            {
              case PlayerDir_Right: {

                };
              break;
              case PlayerDir_Up: {

                };
              break;
              case PlayerDirLeft: {

                };
              break;
              case PlayerDir_Bottom: {

                }
              break;
            }
        };
      break;
    }
}