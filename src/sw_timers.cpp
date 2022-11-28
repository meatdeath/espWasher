#include "sw_timers.h"

#define SW_TIMEOUT_40MS     40
#define SW_TIMEOUT_100MS    100
#define SW_TIMEOUT_1S       1000


hw_timer_t * timer = NULL;

volatile bool blink = false;
volatile uint8_t faded_blink = 0;

extern volatile bool scr_redraw;

void blink_callback()
{
    if(faded_blink == FADED_BLINK_MAX || faded_blink == FADED_BLINK_MIN) {
        blink = !blink;
    }
    if( blink ) {
        faded_blink++;
    } else {
        faded_blink--;
    }
    scr_redraw = true;
}

volatile soft_timer_t sw_timer[SW_TIMER_MAX] = {
    {   // SW_TIMER_BLINK
        .triggered = true,
        .autoupdate = true,
        .updatetime = SW_TIMEOUT_40MS,
        .downcounter = SW_TIMEOUT_40MS,
        .callback = &blink_callback
    },
    {   // SW_TIMER_ACCELEROMETER_UPDATE
        .triggered = false,
        .autoupdate = true,
        .updatetime = SW_TIMEOUT_1S,
        .downcounter = SW_TIMEOUT_1S,
        .callback = NULL
    },
    {
        // SW_TIMER_READ_PORT_A
        .triggered = false,
        .autoupdate = true,
        .updatetime = SW_TIMEOUT_40MS,
        .downcounter = SW_TIMEOUT_40MS,
        .callback = NULL
    }
};


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
                if(sw_timer[i].callback) 
                    sw_timer[i].callback();
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
