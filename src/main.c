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
  menu_processInput (&menuState);
  menu_draw_logo (&menuState);
  menu_draw_options(&menuState, &gameSate);
}
