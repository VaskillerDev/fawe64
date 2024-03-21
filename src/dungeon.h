#pragma once
#include "types.h"
#include "event.h"
#include "vec2.h"

typedef enum DungeonType {
    DungeonType_Reward,
    DungeonType_Boss
} DungeonType;

typedef struct Dungeon {
    EventEmitter emitter;

    Vec2f lastLevelPosition;
    bool isActive;
} Dungeon;

Dungeon dungeon_new(Vec2f lastPosition);

void dungeon_enter(Dungeon* dungeon);

void dungeon_leave(Dungeon* dungeon, uint8_t direction);

void on_dungeon_level_border_contact(LevelBorderContactEvent event);