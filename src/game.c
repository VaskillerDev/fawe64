//
// Created by user on 15.01.2022.
//
#include "libs.h"

struct GameState gameState_new(void) {
  struct GameState gameState = {
      .isCanContinue = false
  };

  return gameState;
}