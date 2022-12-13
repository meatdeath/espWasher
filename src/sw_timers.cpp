#include "sw_timers.h"
#include "common.h"


hw_timer_t * timer = NULL;

volatile bool blink = false;
volatile uint8_t faded_blink = 0;


void rpm_measure()
{
    measured_synchro_ticks = synchro_counter;
    synchro_counter = 0;
}

void setMotorPwmLow()
{
    digitalWrite(MOTOR_PWM_PIN, 0);
}

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
        .enable = true,
        .triggered = true,
        .autoupdate = true,
        .updatetime = SW_TIMEOUT_40MS,
        .downcounter = SW_TIMEOUT_40MS,
        .callback = &blink_callback
    },
    {   // SW_TIMER_ACCELEROMETER_UPDATE
        .enable = true,
        .triggered = false,
        .autoupdate = true,
        .updatetime = SW_TIMEOUT_1S,
        .downcounter = SW_TIMEOUT_1S,
        .callback = NULL
    },
    {   // SW_TIMER_MOTOR_CTL
        .enable = true,
        .triggered = false,
        .autoupdate = true,
        .updatetime = SW_TIMEOUT_1S,
        .downcounter = SW_TIMEOUT_1S,
        .callback = &rpm_measure
    },
    {
        // SW_TIMER_READ_PORT_A
        .enable = true,
        .triggered = false,
        .autoupdate = true,
        .updatetime = SW_TIMEOUT_40MS,
        .downcounter = SW_TIMEOUT_40MS,
        .callback = NULL
    },
    {
        // SW_TIMER_MOTOR_PWM
        .enable = false,
        .triggered = false,
        .autoupdate = false,
        .updatetime = 1,
        .downcounter = 1,
        .callback = setMotorPwmLow
    }
};

void swTimerStart( enum sw_timers_en sw_timer_index )
{
    sw_timer[sw_timer_index].triggered = false;
    sw_timer[sw_timer_index].downcounter = sw_timer[sw_timer_index].updatetime;
    sw_timer[sw_timer_index].enable = true;
}

void swTimerStop( enum sw_timers_en sw_timer_index )
{
    sw_timer[sw_timer_index].enable = false;
}

void swTimerConfigureUpdateTime( enum sw_timers_en sw_timer_index, uint32_t update_time )
{
    sw_timer[sw_timer_index].updatetime = update_time;
}

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
        if( sw_timer[i].enable && sw_timer[i].downcounter ) {
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
    timer = timerBegin(0, 800, true);	// timer tick every 10us
    timerAttachInterrupt(timer, &onTimer, true);
    timerAlarmWrite(timer, 10, true);   // timer event every 100us
    timerAlarmEnable(timer);
}
