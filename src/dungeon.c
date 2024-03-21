#include "dungeon.h"
#include "player.h"
#include "sprite.h"
#include "level.h"

Dungeon dungeon_new(Vec2f lastPosition) {
  return (Dungeon) {
    .emitter = eventEmitter_new(),
    .lastLevelPosition = lastPosition
  };
}

void dungeon_enter(Dungeon* dungeon) {
  if (dungeon->isActive) return;
  dungeon->isActive = true;
  eventEmitter_on (&dungeon->emitter, E_LEVEL_BORDER_CONTACT,on_dungeon_level_border_contact);

  PlayerEnterDungeonEvent event = {
      .startPosition = vec2f_new (80, 60)
  };

  eventEmitter_emit (&player_getInstance()->emitter, E_PLAYER_ENTER_DUNGEON, &event);
}

void on_dungeon_level_border_contact(LevelBorderContactEvent event) {
  event;
  Dungeon* dungeon = &player_getInstance()->level->dungeon;
  dungeon_leave(dungeon, event.direction);
}

void dungeon_leave(Dungeon* dungeon, uint8_t direction) {
  direction;
  dungeon->isActive = false;
  player_getInstance()->level->isTilesActive = true;
  player_getInstance()->sprite->position = vec2_new (80,80);
}