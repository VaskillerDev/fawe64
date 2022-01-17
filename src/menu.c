//
// Created by user on 15.01.2022.
//
#include "libs.h"

struct MenuState menuState_new (void)
{
  struct MenuState menuState = {
      .logoYPos = 0,
      .isDraw = false,
      .currentOption = NEW_GAME
  };

  return menuState;
}

const uint8_t logoYPosMax = 4;
MenuOptionType prevCurrentOption = NEW_GAME;

uint8_t prevGamepad = 0;
const uint8_t optionXPos = 34;
const uint8_t optionYPos = 146;

void menu_processInput (struct MenuState *state)
{
  uint8_t gamepad = *GAMEPAD1;
  uint8_t pressedThisFrame = gamepad & (gamepad ^ prevGamepad);

  if (pressedThisFrame & BUTTON_RIGHT)
    {
      state->currentOption += 1;
    }

  if (pressedThisFrame & BUTTON_LEFT)
    {
      state->currentOption -= 1;
    }

  state->currentOption = state->currentOption > 4 ? 4 : state->currentOption;
  state->currentOption = state->currentOption < 2 ? 2 : state->currentOption;

  bool clickedButton1 = pressedThisFrame == BUTTON_1;

  if (clickedButton1 && prevCurrentOption != state->currentOption)
    {
      prevCurrentOption = state->currentOption;
      eventEmitter_emit (state->emitter, E_MENU_CURRENT_OPTION_CHANGED,  (void*) state->currentOption);
    }
  prevGamepad = gamepad;
}

void menu_draw_logo (struct MenuState *state) {
  uint16_t colors = *DRAW_COLORS;
  *DRAW_COLORS = 0x42;
  blit (menuImg, 0, 14, 160, 128, BLIT_1BPP);
  *DRAW_COLORS = 0x4;
  text ("FAWE 64", 8, state->logoYPos);
  *DRAW_COLORS = colors;

  if (state->isDraw == true) return;
  state->logoYPos = state->logoYPos >= logoYPosMax ? logoYPosMax : (state->logoYPos += 1);
  state->isDraw = state->logoYPos == logoYPosMax;
}

// readonly gameState
void menu_draw_options (struct MenuState *state, struct GameState *gameState)
{
  uint16_t colors = *DRAW_COLORS;
  *DRAW_COLORS = 0x4;

  char *textContent = "none";
  switch (state->currentOption)
    {
      case 1:
        textContent = "CONTINUE >";
      break;
      case 2:
        textContent = gameState->isCanContinue ? "< NEW GAME >" : " NEW GAME >";
      break;
      case 3:
        textContent = "< SETTINGS >";
      break;
      case 4:
        textContent = "< CREDITS";
      break;
    }
  text (textContent, optionXPos, optionYPos);
  *DRAW_COLORS = colors;
}

void menu_setEventEmitter (MenuState *state, EventEmitter *emitter) {
  state->emitter = emitter;
}