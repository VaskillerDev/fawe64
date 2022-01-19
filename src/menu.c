//
// Created by user on 15.01.2022.
//
#include "libs.h"
#include "render.h"
#include "game.h"
#include "types.h"

struct MenuState menuState_new(void)
{
  struct MenuState menuState = {
      .logoYPos = 0,
      .isDraw = false,
      .currentOption = NEW_GAME};

  imagePool_init(&menuState.imagePool);

  menuState.logo = sprite_new(imagePool_getImage(&menuState.imagePool, 0));
  menuState.logo->pos.y = 14;

  Image *frames[3] = {
      imagePool_getImage(&menuState.imagePool, 1),
      imagePool_getImage(&menuState.imagePool, 2),
      imagePool_getImage(&menuState.imagePool, 3)};

  menuState.sprite = sprite_animated_new(frames, 3, 20);
  menuState.sprite->pos.y = 96;
  menuState.sprite->pos.x = 50;
 // menuState.sprite->size.x = 40;
//menuState.sprite->size.y = 40;

  sprite_initBoundingVolume(menuState.sprite, SPHERE);

  menuState.sprite2 = sprite_animated_new(frames, 3, 20);
  menuState.sprite2->pos.y = 87;
  menuState.sprite2->pos.x = 98;
  menuState.sprite2->size.x = 80;
  // menuState.sprite2->size.y = 80;
  sprite_initBoundingVolume(menuState.sprite2, BOX);

  return menuState;
}

const uint8_t logoYPosMax = 4;
MenuOptionType prevCurrentOption = NEW_GAME;

uint8_t prevGamepad = 0;
const uint8_t optionXPos = 34;
const uint8_t optionYPos = 146;

void menu_processInput(struct MenuState *state, struct GameState *gameState)
{
  if(gameState)
   gameState;
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
    eventEmitter_emit(state->emitter, E_MENU_CURRENT_OPTION_CHANGED, (void *)state->currentOption);
  }
  prevGamepad = gamepad;
}

void menu_draw_logo(struct MenuState *state)
{
  sprite_Draw(state->logo);
  sprite_Draw(state->sprite);
    sprite_Draw(state->sprite2);

if(CheckCollision(&state->sprite->boundingVolume, &state->sprite2->boundingVolume))
  {
    tracef("yes");
  }
//printf("%d\n", CheckCollision(&state->sprite->boundingVolume, &state->sprite2->boundingVolume));

  if (state->isDraw == true)
    return;
  state->logoYPos = state->logoYPos >= logoYPosMax ? logoYPosMax : (state->logoYPos += 1);
  state->isDraw = state->logoYPos == logoYPosMax;
}

// readonly gameState
void menu_draw_options(struct MenuState *state, bool isCanContinue)
{
  state;
  isCanContinue;
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

  uint_16 textColors[4] = {4, 0, 0, 0};
  DrawText(textContent, optionXPos, optionYPos, textColors);
}

void menu_setEventEmitter(MenuState *state, EventEmitter *emitter)
{
  state->emitter = emitter;
}