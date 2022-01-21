#pragma once
#include "wasm4.h"
typedef int32_t int_32;
typedef uint32_t uint_32;
typedef uint16_t uint_16;
typedef uint8_t uint_8;

typedef struct MenuState MenuState;
typedef struct GameState GameState;
typedef struct EventEmitter EventEmitter;

static const unsigned TLD_FLIPPED_HORIZONTALLY_FLAG  = 0x80000000;
static const unsigned TLD_FLIPPED_VERTICALLY_FLAG    = 0x40000000;
static const unsigned TLD_FLIPPED_DIAGONALLY_FLAG    = 0x20000000;
static const int TLD_FLAGS = ~(TLD_FLIPPED_HORIZONTALLY_FLAG | TLD_FLIPPED_VERTICALLY_FLAG | TLD_FLIPPED_DIAGONALLY_FLAG);