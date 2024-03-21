#include "timer.h"

Timer timer_new(uint16_t time, bool isLoop) {
  return (Timer) {
     .time = time,
    .isLoop = isLoop,
    .isPause = true,
    .startTime = time,
    .emitter = eventEmitter_new(),
  };
}

void timer_reload(Timer* timer) {
  timer->time = timer->startTime;
}

void timer_start(Timer* timer) {
  timer->isPause = false;
}

void timer_pause(Timer* timer) {
  timer->isPause = true;
}

void timer_resume(Timer* timer) {
  timer->isPause = false;
}

void timer_update(Timer* timer) {
  if (timer->isPause) 
    return;
  
  timer->time -=1;
  
  if (timer->time != 0) 
    return;

  TimerExpiredEvent event = {.id = 1, timer};
  eventEmitter_emit (&timer->emitter, E_TIMER_EXPIRED, &event);

  if (timer->isLoop) {
    timer->time = timer->startTime;
  }
  timer->isPause = timer->isLoop? false : true;
}

bool timer_isOut(Timer* timer) {
  return timer->time == 0;
}