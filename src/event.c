//
// Created by user on 17.01.2022.
//
#include "libs.h"

EventEmitter eventEmitter_new(void) {
struct EventEmitter emitter = {
    .map = {},
};
return emitter;
}

void eventEmitter_on(EventEmitter* emitter, enum EventName name, void* lambda) {

  struct EventKeyValue kv = {
      .eventNameAsKey = name,
      .lambdaRefAsValue = lambda
  };

  emitter->map[name] = kv;
}

void eventEmitter_emit(EventEmitter* emitter, enum EventName name, void* args) {
  void (*lambda)() = emitter->map[name].lambdaRefAsValue;
  if (lambda == NULL) {
      tracef ("calling %d event: is NULL", name);
      return;
  }
  args == NULL ? lambda() : lambda(args);
}