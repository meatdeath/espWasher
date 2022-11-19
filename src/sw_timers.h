#ifndef __SW_TIMERS_H__
#define __SW_TIMERS_H__

#include <Arduino.h>

enum sw_timers_en {
    SW_TIMER_ACCELEROMETER_UPDATE,
    SW_TIMER_MAX
};

typedef struct soft_timer_st {
    bool triggered;
    bool autoupdate;
    uint16_t updatetime;
    uint16_t downcounter;
} soft_timer_t;

extern volatile soft_timer_t sw_timer[SW_TIMER_MAX];

void swTimerInit();
void swTimerSetTriggered( enum sw_timers_en sw_timer_index, bool value );
bool swTimerIsTriggered( enum sw_timers_en sw_timer, bool autoreset );

#endif //__SW_TIMERS_H__
