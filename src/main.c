#include "libs.h"

EventEmitter emitter;
MenuState menuState;
GameState gameSate;
//Test
ImagePool imgPool;
Level *level;
Player player;
void start()
{
  emitter = eventEmitter_new();
  gameSate = gameState_new();
  menuState = menuState_new();

  //Test
  imagePool_init(&imgPool);
  level = level_new();

  Image *frames[3] = {
      imagePool_getImage(&imgPool, 1),
      imagePool_getImage(&imgPool, 2),
      imagePool_getImage(&imgPool, 3)};

  // s = sprite_animated_init(level_spawnObject(level), frames, 3, 10 );
  //s = sprite_animated_new(frames, 3, 10);
  player.sprite = level_spawnObject(level);
  sprite_animated_init(player.sprite, frames, 3, 10);
  sprite_initBoundingVolume(player.sprite, BOX);
  player.speed = 0.25;
  player.level = level;


  Sprite* s = level_spawnObject(level);
  sprite_animated_init(s, frames, 3, 10);
  sprite_initBoundingVolume(s, BOX);

 s->pos.x = 80;
 s->pos.y = 80;

  /*for(int i = 0; i < 10; i++)
for(int j = 0; j < 10; j++)
{ 
  Sprite* s1 = level_spawnObject(level);
 s1 = sprite_animated_init(s1, frames, 3, 10);
 s1->pos.x = 10 + i * 20;
 s1->pos.y = 10 + j * 20;
}*/

  game_setEventEmitter(&gameSate, &emitter);
  menu_setEventEmitter(&menuState, &emitter);
}

void update()
{

  //sprite_Draw(s);
  //player_move_down(&player);
  player_update(&player);

  switch (gameSate.currentScreen)
  {
  case UNKNOWN:
  {
    gameSate.currentScreen = IN_MENU;
  }
  /**
       * Входная точка экрана с игровым меню
       */
  case IN_MENU:
  {
    level_draw(level);
    menu_processInput(&menuState, &gameSate);
    //   menu_draw_logo(&menuState);
    //  menu_draw_options(&menuState, gameSate.isCanContinue);
  }
  break;
  case IN_MENU_SETTINGS:
    break;
  case IN_MENU_CREDITS:
    break;
  /**
       * Входная точка экрана уровня
       */
  case IN_GAME_LEVEL:
  {
    //level_draw(level);
  }
  break;
  /**
       * Входная точка экрана открытого инвентаря
       */
  case IN_GAME_INVENTORY:
  {
  }
  break;
  }

  //tracef ("currentScreen: %d", gameSate.currentScreen);
}
