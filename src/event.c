//
// Created by user on 17.01.2022.
//
#include "event.h"
#include "wasm4.h"

EventEmitter eventEmitter_new (void)
{
  struct EventEmitter emitter = {
      .events = {},
      .listeningEventCount = 0
  };
  return emitter;
}

void eventEmitter_on (EventEmitter *emitter, enum EventName name, void *lambda)
{
  struct EventKeyValue kv = {
      .eventNameAsKey = name,
      .lambdaRefAsValue = lambda
  };

  emitter->events[emitter->listeningEventCount] = kv;
  ++emitter->listeningEventCount;
}

void eventEmitter_emit (EventEmitter *emitter, enum EventName name, void *args)
{
  if (emitter->listeningEventCount == 0) {
    return;
  }

  for (uint8_t i = 0; i < emitter->listeningEventCount; i++) {
      if (emitter->events[i].eventNameAsKey != name) {
        continue;
      }

      void* lambdaPtr = emitter->events[i].lambdaRefAsValue;
      if (lambdaPtr == NULL)
        {
          tracef ("calling %d event: is NULL", name);
          return;
        }
      
      if(args == NULL)
      {
         void (*lambda) () = lambdaPtr;
        lambda();
      }
      else
      {
         void (*lambda) (void*) = lambdaPtr;
        lambda (args);
      }
  }

}