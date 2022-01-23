#include "libs.h"
#include "enemy_type_1.h"

EventEmitter emitter;
MenuState menuState;
GameState gameSate;
//Test
ImagePool imgPool;
Level *level;
Player player;
EnemyType_1 enemy;

TiledLevelChunk chunk = {};
void start()
{
  SetPaletteColor_1 (0xa46422);
  SetPaletteColor_2 (0xeb8931);
  SetPaletteColor_3 (0xd8d3cd);
  SetPaletteColor_4 (0x493c2b);

  emitter = eventEmitter_new();
  gameSate = gameState_new();
  menuState = menuState_new();

  //Test
  imagePool_init(&imgPool);
  menu_setImagePool(&menuState, &imgPool);

  level = level_new();
  level_setImagePool(level, &imgPool);
  level_setChunk(level, &chunk);

  player = player_new(level);

  game_setEventEmitter(&gameSate, &emitter);
  menu_setEventEmitter(&menuState, &emitter);

  enemy = level_spawnEnemyType_1(level);
  enemy.enemy->movDist = 100;
  enemy.enemy->moveDir = vec2_new(0, -1);
}

void update()
{

  player_update(&player, level);

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
    menu_processInput(&menuState, &gameSate);
    menu_draw_logo(&menuState);
    menu_draw_options(&menuState, gameSate.isCanContinue);
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
    level_update(level);
    level_draw(level);
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
}
