//
// Created by user on 15.01.2022.
//
#include "libs.h"

struct GameState gameState_new (void)
{
  struct GameState gameState = {
      .isCanContinue = false,
      .currentScreen = IN_MENU,
  };

  return gameState;
}

void _onMenuCurrentOptionChanged(CurrentOptionChangedEvent e) {
  switch (e.currentOption)
    {
      case CONTINUE_GAME: e.gameState->currentScreen = IN_GAME_LEVEL; break;
      case NEW_GAME: e.gameState->currentScreen = IN_GAME_LEVEL; break;
      case SETTINGS: e.gameState->currentScreen = IN_MENU_SETTINGS; break;
      case CREDITS: e.gameState->currentScreen = IN_MENU_CREDITS; break;
    }
}

void game_setEventEmitter (GameState *state, EventEmitter *emitter)
{
  state->emitter = emitter;

  eventEmitter_on (state->emitter, E_MENU_CURRENT_OPTION_CHANGED, &_onMenuCurrentOptionChanged);
}