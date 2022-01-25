#include "libs.h"
#include <math.h>

static Player* globalPlayerRef = NULL;
static Player globalPlayer = {};

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

      bool isClash = CheckCollision (&player->boundingVolume, &(*currentObject)->boundingVolume);
      if (!isClash)
        continue;

      Vec2f rayDir = vec2_normalize (vec2_sub ((*currentObject)->position, player->position));
      if (fabsf (fabsf (rayDir.x) - fabsf (rayDir.y)) < 0.00000001)
        continue;

      (fabsf (rayDir.x) > fabsf (rayDir.y)) ? (rayDir.y = 0) : (rayDir.x = 0);
      rayDir = vec2f_normalize (rayDir);

      if (vec2f_dot (rayDir, vec2f_fromVec2 (dir)) > 0)
        return true;
    }

  return false;
}

Player* player_getInstance() {
  if (globalPlayerRef == NULL) {
      trace ("Player instance reference not found");
  }
  return globalPlayerRef;
}

Player* player_initInstance(PlayerInitInstanceArgs args)
{
  if (globalPlayerRef == NULL)
    {
      globalPlayer = player_new (args.level, args.gameState, args.spawnPosition);
      globalPlayerRef = &globalPlayer;
    }

  return globalPlayerRef;
}

Player player_new(Level *level, GameState* gameState, Vec2 spawnPosition)
{

  struct Player player = {
      .actionState = PlayerAction_Idle,
      .movementDirection = PlayerDir_Bottom,
      .sprite = NULL,
      .gameState = gameState,
      .level = level,
      .speed = 1.5f,
      .emitter = eventEmitter_new(),

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
      .attackLeft = imagePool_getImage (level->imagePool, PoolIdx_PiligrimAttackLeft),
      .sword = sword_new(level)
  };

  Sprite *playerSprite = level_spawnObject(level);
  sprite_animated_init(playerSprite, player.idleBottomFrames, 3, 10);
  player.sprite = playerSprite;
  player.sprite->position = spawnPosition;

  sprite_initBoundingVolume (player.sprite, BOX);
  player.health = hp_new(2, &player, 20, 20);

  eventEmitter_on (&player.health.emitter, E_HP_POINTS_OVER, &player_death);
  eventEmitter_on (&player.sword.emitter, E_SWORD_ATTACK_HIT, &on_player_attack);

  return player;
}

void on_player_attack(EnemySwordAttackHitEvent e) {

}

void player_move_left (Player *player)
{
  player->movementDirection = PlayerDirLeft;
  if (!player_checkCollision (player->sprite, player->level, vec2_new (-1, 0))) {
      player->speedDir = vec2f_add (player->speedDir, vec2f_new (-1, 0));
  }

}

void player_move_right (Player *player)
{
  player->movementDirection = PlayerDir_Right;
  if (!player_checkCollision (player->sprite, player->level, vec2_new (1, 0))) {
      player->speedDir = vec2f_add (player->speedDir, vec2f_new (1, 0));player->speedDir = vec2f_add (player->speedDir, vec2f_new (1, 0));
  }

}

void player_move_up (Player *player)
{
  player->movementDirection = PlayerDir_Up;
  if (!player_checkCollision (player->sprite, player->level, vec2_new (0, -1))) {
      player->speedDir = vec2f_add (player->speedDir, vec2f_new (0, -1));
  }

}

void player_move_down (Player *player)
{
  player->movementDirection = PlayerDir_Bottom;
  if (!player_checkCollision (player->sprite, player->level, vec2_new (0, 1))) {
      player->speedDir = vec2f_add (player->speedDir, vec2f_new (0, 1));
  }
}


void player_update(Player *player, Level *level)
{
  uint8_t gamepad = *GAMEPAD1;
  player->speedDir = vec2f_new (0, 0);

  bool button_1 = gamepad & BUTTON_1;
  bool button_2 = gamepad & BUTTON_2;

  if (button_1) {
      gamepad -= 1;
  }

  if (button_2) {
      gamepad -= 2;
  }


    if (gamepad > 0)
      {
        if (player->sprite->frameCounter == player->sprite->animDelay - 1 && player->sprite->currentImageIndex == 2)
          tone (1000, 1 | (10 << 8), 3, TONE_NOISE | TONE_MODE4);
      }

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
      player->sprite->position = vec2_add (player->sprite->position, vec2_fromVec2f (vec2f_mul (player->speedDir, vec2f_new (player->speed, player->speed))));
    }

    sword_updatePosition(&player->sword, player->sprite);
    sword_update(&player->sword, player->sprite, level);
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

                }
              break;
              case PlayerDir_Up: {

                }
              break;
              case PlayerDirLeft: {

                }
              break;
              case PlayerDir_Bottom: {

                }
              break;
            }
        };
      break;
    }

    char lText[3];
    lText[0] = player->health.currentPoints / 10 + '0';
    lText[1] = player->health.currentPoints % 10 + '0';
    lText[2] = '\0';
    uint_16 textColors[4] = {4, 2, 0, 0};
    DrawText(lText, 16, 150, textColors);
}

void player_death(HpPointsOverEvent event)
{
    Player* player = (Player*)event.parent;
    player->gameState->currentScreen = IN_MENU;
}