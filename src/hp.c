//
// Created by stepaniuk on 21.01.2022.
//
#include "hp.h"

Hp hp_new (uint8_t id, void* parent, uint8_t maxPoints, uint8_t currentPoints, bool swordResistance)
{
  struct Hp hp = {
      .maxPoints = maxPoints,
      .currentPoints = currentPoints,
      .id = id,
      .parent = parent,
      .swordResistance = swordResistance
  };

  hp.emitter = eventEmitter_new();

  return hp;
}

void hp_substract(Hp* hp, uint8_t points) {
  if (points >= hp->currentPoints) {
      hp->currentPoints = 0;
  } else {
    hp->currentPoints -= points;
  }

  struct HpPointsChangedEvent changedEvent = {
      .id = hp->id,
      .currentPoints = hp->currentPoints,
      .parent = hp->parent
  };

  eventEmitter_emit (&hp->emitter, E_HP_POINTS_CHANGED, (void *) &changedEvent);

  if (hp->currentPoints == 0) {

      struct HpPointsOverEvent event = {
          .parent = hp->parent,
          .id = hp->id
      };

      eventEmitter_emit (&hp->emitter, E_HP_POINTS_OVER, (void *) &event);
  }
}

void hp_add(Hp* hp, uint8_t points) {
  if (hp->currentPoints >= points) {
      hp->currentPoints = hp->maxPoints;
    } else {
      hp->currentPoints += points;
    }

  struct HpPointsChangedEvent changedEvent = {
      .id = hp->id,
      .currentPoints = hp->currentPoints
  };

  eventEmitter_emit (&hp->emitter, E_HP_POINTS_CHANGED, (void *) &changedEvent);

  if (hp->currentPoints == hp->maxPoints) {

      struct HpPointsFilledEvent event = {
          .id = hp->id
      };

      eventEmitter_emit (&hp->emitter, E_HP_POINTS_FILLED, (void *) &event);
    }
}