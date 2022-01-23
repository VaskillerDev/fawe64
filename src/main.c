#include "libs.h"
#include "enemy_type_1.h"

EventEmitter emitter;
MenuState menuState;
GameState gameSate;
//Test
ImagePool imgPool;
Level *level;
Player player;
EnemyType_1 enemy;

TiledLevelChunk chunk = {};

void LoadLevel(Vec2 dir)
{
  if (level_isDone(level))
  {
    level_delete(level);

    level = level_new();
    level_setImagePool(level, &imgPool);
    level_setChunk(level, vec2_add(vec2_new(chunk.x, chunk.y), dir), &chunk);

    player = player_new(level, &gameSate);
    player.sprite->pos = vec2_add(vec2_new(80, 80), vec2_mul(vec2_new(54, 54), dir));

    level_spawnEnemys(level);
  }
}

void start()
{
  SetPaletteColor_1(0xa46422);
  SetPaletteColor_2(0xeb8931);
  SetPaletteColor_3(0xd8d3cd);
  SetPaletteColor_4(0x493c2b);

  emitter = eventEmitter_new();
  gameSate = gameState_new();
  menuState = menuState_new();

  //Test
  imagePool_init(&imgPool);
  menu_setImagePool(&menuState, &imgPool);

  level = level_new();
  level_setImagePool(level, &imgPool);
  level_setChunk(level, vec2_new(0, 0), &chunk);

  player = player_new(level, &gameSate);
  player.health.parent = &player;
  eventEmitter_on(&player.health.emitter, E_HP_POINTS_OVER, &player_death);

  game_setEventEmitter(&gameSate, &emitter);
  menu_setEventEmitter(&menuState, &emitter);

  //level_spawnEnemys(level);
}

void update()
{
  switch (gameSate.currentScreen)
  {
  case UNKNOWN:
  {
    gameSate.currentScreen = IN_MENU;
  }
  /**
       * Входная точка экрана с игровым меню
       */
  case IN_MENU:
  {
    menu_processInput(&menuState, &gameSate);
    menu_draw_logo(&menuState);
    menu_draw_options(&menuState, gameSate.isCanContinue);
  }
  break;
  case IN_MENU_SETTINGS:
    break;
  case IN_MENU_CREDITS:
    break;
  /**
       * Входная точка экрана уровня
       */
  case IN_GAME_LEVEL:
  {
    player_update(&player, level);
    player_draw(&player, level);

    level_update(level);
    level_draw(level);

    if (player.sprite->pos.x <= 24)
    {
      LoadLevel(vec2_new(-1, 0));
      return;
    }

    if (player.sprite->pos.x >= 136)
    {
      LoadLevel(vec2_new(1, 0));
      return;
    }

    if (player.sprite->pos.y <= 24)
    {
      LoadLevel(vec2_new(0, 1));
      return;
    }

    if (player.sprite->pos.y >= 136)
    {
      LoadLevel(vec2_new(0, -1));
      return;
    }
  }
  break;
  /**
       * Входная точка экрана открытого инвентаря
       */
  case IN_GAME_INVENTORY:
  {
  }
  break;
  }
}
