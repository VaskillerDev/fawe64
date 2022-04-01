#include "libs.h"

Dungeon dungeon_new(Vec2f lastPosition) {
  return (Dungeon) {
    .emitter = eventEmitter_new(),
    .lastLevelPosition = lastPosition
  };
}

void dungeon_enter(Dungeon* dungeon) {
  if (dungeon->isActive) return;
  dungeon->isActive = true;

  PlayerEnterDungeonEvent event = {
      .startPosition = vec2f_new (80, 60)
  };

  eventEmitter_emit (&player_getInstance()->emitter, E_PLAYER_ENTER_DUNGEON, &event);
}

void dungeon_leave(Dungeon* dungeon) {
  dungeon->isActive = false;
}