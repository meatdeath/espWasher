#ifndef __SW_TIMERS_H__
#define __SW_TIMERS_H__

#include <Arduino.h>

enum sw_timers_en {
    SW_TIMER_BLINK,
    SW_TIMER_ACCELEROMETER_UPDATE,
    SW_TIMER_READ_PORT_A,
    SW_TIMER_MAX
};


#define FADED_BLINK_MIN 0
#define FADED_BLINK_MAX 15

typedef struct soft_timer_st {
    bool triggered;
    bool autoupdate;
    uint16_t updatetime;
    uint16_t downcounter;
    void (*callback)();
} soft_timer_t;

extern volatile soft_timer_t sw_timer[SW_TIMER_MAX];

extern volatile bool blink;
extern volatile uint8_t faded_blink; // 0-15

void swTimerInit();
void swTimerSetTriggered( enum sw_timers_en sw_timer_index, bool value );
bool swTimerIsTriggered( enum sw_timers_en sw_timer, bool autoreset );

#endif //__SW_TIMERS_H__
