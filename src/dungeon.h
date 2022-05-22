#pragma once
#include "libs.h"

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

void dungeon_leave(Dungeon* dungeon, uint_8 direction);

void on_dungeon_level_border_contact(LevelBorderContactEvent event);