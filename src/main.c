#include "libs.h"

EventEmitter emitter;
MenuState menuState;
GameState gameSate;

void start ()
{
  emitter = eventEmitter_new();
  gameSate = gameState_new ();
  menuState = menuState_new ();

  game_setEventEmitter (&gameSate, &emitter);
  menu_setEventEmitter (&menuState, &emitter);
}

void update ()
{

  switch (gameSate.currentScreen)
    {
      case UNKNOWN: {
          gameSate.currentScreen = IN_MENU;
      }
      /**
       * Входная точка экрана с игровым меню
       */
      case IN_MENU: {
          menu_processInput (&menuState, &gameSate);
          menu_draw_logo (&menuState);
          menu_draw_options(&menuState, gameSate.isCanContinue);
      }
      break;
      case IN_MENU_SETTINGS: break;
      case IN_MENU_CREDITS: break;
      /**
       * Входная точка экрана уровня
       */
      case IN_GAME_LEVEL: {

      }
      break;
      /**
       * Входная точка экрана открытого инвентаря
       */
      case IN_GAME_INVENTORY: {

      }
      break;
    }
}
