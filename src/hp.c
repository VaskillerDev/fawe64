//
// Created by stepaniuk on 21.01.2022.
//
#include "libs.h"

Hp hp_new (uint8_t id, uint8_t maxPoints, uint8_t currentPoints)
{
  struct Hp hp = {
      .maxPoints = maxPoints,
      .currentPoints = currentPoints,
      .id = id
  };

  hp.emitter = eventEmitter_new();
}

void hp_substract(Hp* hp, uint8_t points) {

  if (hp->currentPoints >= points) {
      hp->currentPoints = 0;
  } else {
    hp->currentPoints -= points;
  }

  struct HpPointsChangedEvent changedEvent = {
      .id = hp->id,
      .currentPoints = hp->currentPoints
  };

  eventEmitter_emit (&hp->emitter, E_HP_POINTS_CHANGED, (void *) &changedEvent);

  if (hp->currentPoints == 0) {

      struct HpPointsOverEvent event = {
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