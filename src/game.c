//
// Created by user on 15.01.2022.
//
#include "libs.h"

struct GameState gameState_new (void)
{
  struct GameState gameState = {
      .isCanContinue = false,
      .currentTab = IN_MENU
  };

  return gameState;
}

void _onMenuCurrentOptionChanged(MenuOptionType option) {
  tracef ("current option %d", option);
}

void game_setEventEmitter (GameState *state, EventEmitter *emitter)
{
  state->emitter = emitter;

  eventEmitter_on (emitter, E_MENU_CURRENT_OPTION_CHANGED, &_onMenuCurrentOptionChanged);
}