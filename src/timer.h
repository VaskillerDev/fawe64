#pragma once
#include "event.h"

typedef struct Timer {
    uint16_t startTime;
    uint16_t time;
    bool isLoop;
    bool isPause;

    EventEmitter emitter;
} Timer;

Timer timer_new(uint16_t time, bool isLoop);
void timer_reload(Timer* timer);
void timer_start(Timer* timer);
void timer_pause(Timer* timer);
void timer_resume(Timer* timer);
void timer_update(Timer* timer);
bool timer_isOut(Timer* timer);