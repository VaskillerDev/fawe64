//
// Created by user on 15.01.2022.
//
#include "libs.h"

struct MenuState menuState_new (void)
{
  struct MenuState menuState = {
      .logoYPos = 0,
      .isDraw = false,
      .currentOption = 0
  };

  return menuState;
}

const uint8_t logoYPosMax = 4;

void menu_init (struct MenuState *state)
{
  uint16_t colors = *DRAW_COLORS;
  *DRAW_COLORS = 0x42;
  blit(menuImg, 0, 14, 160,128, BLIT_1BPP);
  *DRAW_COLORS = 0x4;
  text ("FAWE 64", 8, state->logoYPos);
  *DRAW_COLORS = colors;

  if (state->isDraw == true) return;
  state->logoYPos = state->logoYPos >= logoYPosMax ? logoYPosMax : (state->logoYPos += 1);
  state->isDraw = state->logoYPos == logoYPosMax;
}

uint8_t previousGamepad = 0;
const uint8_t optionXPos = 34;
const uint8_t optionYPos = 146;

void menu_draw (struct MenuState *state, struct GameState *gameState)
{
  uint8_t gamepad = *GAMEPAD1;

  uint8_t pressedThisFrame = gamepad & (gamepad ^ previousGamepad);
  previousGamepad = gamepad;

  if (pressedThisFrame & BUTTON_RIGHT)
    {
      state->currentOption += 1;
    }

  if (pressedThisFrame & BUTTON_LEFT)
    {
      state->currentOption -= 1;
    }

  state->currentOption = state->currentOption > 2 ? 2 : state->currentOption;
  state->currentOption = state->currentOption < 0 ? 0 : state->currentOption;

  uint16_t colors = *DRAW_COLORS;
  *DRAW_COLORS = 0x4;

  char* textContent = "none";
  switch (state->currentOption)
    {
      case -1: textContent = "CONTINUE >";
      break;
      case 0: textContent = gameState->isCanContinue ? "< NEW GAME >" : " NEW GAME >";
      break;
      case 1: textContent = "< SETTINGS >";
      break;
      case 2: textContent = "< CREDITS";
      break;
    }
  text (textContent, optionXPos, optionYPos);
  *DRAW_COLORS = colors;
}