#include "libs.h"
#include "enemy_unit.h"

EventEmitter emitter;
MenuState menuState;
GameState gameSate;
//Test
ImagePool imgPool;
Level *level = NULL;
EnemyUnit enemy;

TiledLevelChunk chunk = {};

void start ()
{
  SetPaletteColor_1 (0xa46422);
  SetPaletteColor_2 (0xeb8931);
  SetPaletteColor_3 (0xd8d3cd);
  SetPaletteColor_4 (0x493c2b);

  emitter = eventEmitter_new ();
  gameSate = gameState_new ();
  menuState = menuState_new ();

  imagePool_init (&imgPool);
  menu_setImagePool (&menuState, &imgPool);

  game_setEventEmitter (&gameSate, &emitter);
  menu_setEventEmitter (&menuState, &emitter);
}

void update ()
{
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
          menu_processInput (&menuState, &gameSate);
          menu_draw_logo (&menuState);
          menu_draw_options (&menuState, gameSate.isCanContinue);
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

          if (level == NULL) {

              level = level_new ();
              level_setImagePool (level, &imgPool);
              level_setChunk (level, vec2_new (0, 0), &chunk);
              level_spawnEnemies(level);

              const struct PlayerInitInstanceArgs args = {
                  .spawnPosition = vec2_new (80,80),
                  .gameState = &gameSate,
                  .level = level
              };

              player_initInstance(args);
          }

          struct LoadLevelArgs chunkMovingArgs = {
              .level = level,
              .newChunk = &chunk,
              .imagePool = &imgPool,
              .newChunkPosition = vec2_new(chunk.x, chunk.y)};

          level_processChunkMoving(&chunkMovingArgs, player_getInstance());
          level_update(level);
          level_draw(level);

          Player* player = player_getInstance();
          player_update (player, level);
          player_draw (player, level);
          player_postUpdate(player);
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
