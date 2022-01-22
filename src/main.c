#include "libs.h"

EventEmitter emitter;
MenuState menuState;
GameState gameSate;
//Test
ImagePool imgPool;
Level* level;
Player player;
void start()
{
  emitter = eventEmitter_new();
  gameSate = gameState_new();
  menuState = menuState_new();

  //Test
  imagePool_init(&imgPool);
  menu_setImagePool (&menuState, &imgPool);

  TiledLevelChunk chunk = {};

  level = level_new();
  level_setImagePool (level, &imgPool);
  level_setChunk (level, &chunk);

  player = player_new (level);


  game_setEventEmitter(&gameSate, &emitter);
  menu_setEventEmitter(&menuState, &emitter);
}

void update()
{

  player_update(&player);

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
    level_draw(level);
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
