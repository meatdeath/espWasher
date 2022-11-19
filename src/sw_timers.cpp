#include "sw_timers.h"

volatile soft_timer_t sw_timer[SW_TIMER_MAX] = {
    {   // SW_TIMER_ACCELEROMETER_UPDATE
        .triggered = false,
        .autoupdate = true,
        .updatetime = 1000,
        .downcounter = 1000
    }
};


hw_timer_t * timer = NULL;

void swTimerSetTriggered( enum sw_timers_en sw_timer_index, bool value )
{
    sw_timer[sw_timer_index].triggered = value;
}

bool swTimerIsTriggered( enum sw_timers_en sw_timer_index, bool autoreset )
{
    bool triggered = false;
    if( sw_timer[sw_timer_index].triggered ) {
        triggered = true;
        if( autoreset )
            sw_timer[sw_timer_index].triggered = false;
    }
    return triggered;
}

inline void swTimerUpdate(void) {
    for( int i = 0; i < SW_TIMER_MAX; i++ ) {
        if( sw_timer[i].downcounter ) {
            sw_timer[i].downcounter--;
            if( sw_timer[i].downcounter == 0 ) {
                sw_timer[i].triggered = true;
                if(sw_timer[i].autoupdate) {
                    sw_timer[i].downcounter = sw_timer[i].updatetime;
                }
            }
        }
    }
}

void IRAM_ATTR onTimer() {
    swTimerUpdate();
}

void swTimerInit() {
    timer = timerBegin(0, 8000, true);	// 1/10 ms
    timerAttachInterrupt(timer, &onTimer, true);
    timerAlarmWrite(timer, 10, true);
    timerAlarmEnable(timer);
}
