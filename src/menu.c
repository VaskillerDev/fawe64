//
// Created by user on 15.01.2022.
//
#include "libs.h"
#include "render.h"

struct MenuState menuState_new(void)
{
  struct MenuState menuState = {
      .logoYPos = 0,
      .isDraw = false,
      .currentOption = NEW_GAME
  };

  return menuState;
}

void menu_setImagePool(MenuState* menuState, ImagePool* imagePool) {
  menuState->imagePool = imagePool;
  menuState->logo = sprite_new(imagePool_getImage(menuState->imagePool, PoolIdx_MenuImage));
  menuState->logo->pos.y = 14;
}

const uint8_t logoYPosMax = 4;
MenuOptionType prevCurrentOption = 0;

uint8_t prevGamepad = 0;
const uint8_t optionXPos = 34;
const uint8_t optionYPos = 146;

void menu_processInput(struct MenuState *state, struct GameState *gameState)
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

    struct CurrentOptionChangedEvent event = {
        .currentOption = state->currentOption,
        .gameState = gameState,
    };

    eventEmitter_emit(state->emitter, E_MENU_CURRENT_OPTION_CHANGED, (void *) &event);
  }
  prevGamepad = gamepad;
}

void menu_draw_logo(struct MenuState *state)
{
  uint_16 textColors[4] = {3, 0, 0, 0};
  DrawText ("FAWE 64", 8, state->logoYPos,textColors);
  sprite_Draw(state->logo);

  if (state->isDraw == true) {
    return;
  }
  state->logoYPos = state->logoYPos >= logoYPosMax ? logoYPosMax : (state->logoYPos += 1);
  state->isDraw = state->logoYPos == logoYPosMax;
}

// readonly gameState
void menu_draw_options(struct MenuState *state, bool isCanContinue)
{
  char *textContent = "none";
  switch (state->currentOption)
  {
  case 1:
    textContent = "CONTINUE >";
    break;
  case 2:
    textContent = isCanContinue ? "< NEW GAME >" : " NEW GAME >";
    break;
  case 3:
    textContent = "< SETTINGS >";
    break;
  case 4:
    textContent = "< CREDITS";
    break;
  }

  uint_16 textColors[4] = {3, 0, 0, 0};
  DrawText(textContent, optionXPos, optionYPos, textColors);
}

void menu_setEventEmitter(MenuState *state, EventEmitter *emitter)
{
  state->emitter = emitter;
}