#include "libs.h"

MenuState menuState;
GameState gameSate;

void start ()
{
  menuState = menuState_new();
  gameSate = gameState_new();
}

void update ()
{
  menu_init(&menuState);
  menu_draw(&menuState, &gameSate);
}
