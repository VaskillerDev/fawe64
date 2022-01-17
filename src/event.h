//
// Created by user on 17.01.2022.
//
#ifndef _EVENT_H_
#define _EVENT_H_

#define MAX_EVENTS 64

typedef enum EventName {
    E_UNKNOWN = 0,
    // MENU: 1
    /**
     * В меню была выбрана опция
     */
    E_MENU_CURRENT_OPTION_CHANGED = 10
} EventName;

typedef struct EventKeyValue {
    int eventNameAsKey;
    void *lambdaRefAsValue;
} EventKeyValue;

typedef struct EventEmitter {
    EventKeyValue map[MAX_EVENTS];
} EventEmitter;

EventEmitter eventEmitter_new (void);

void eventEmitter_on (EventEmitter *emitter, enum EventName name, void *lambda);
void eventEmitter_emit (EventEmitter *emitter, enum EventName name, void *args);

#endif //_EVENT_H_
