#ifndef __COMMON_H__
#define __COMMON_H__

#define MOTOR_PWM_PIN   16
#define ZC_PIN          35
#define SYNCHRO_PIN     32

#define SYNCHRO_TICKS_AT_1HZ_RPM        80

#define SYNCHRO_TICKS_PER_S_ON_60_RPM   80      // 1Hz => 8 sesor ticks * 10 scaler
#define SYNCHRO_TICKS_PER_S_ON_120_RPM  160     // 2Hz
#define SYNCHRO_TICKS_PER_S_ON_180_RPM  240     // 3Hz
#define SYNCHRO_TICKS_PER_S_ON_240_RPM  320     // 4Hz
#define SYNCHRO_TICKS_PER_S_ON_300_RPM  450     // 5,6Hz
#define SYNCHRO_TICKS_PER_S_ON_400_RPM  533     // 6,67Hz
#define SYNCHRO_TICKS_PER_S_ON_600_RPM  800     // 10Hz
#define SYNCHRO_TICKS_PER_S_ON_800_RPM  1067    // 13,3Hz
#define SYNCHRO_TICKS_PER_S_ON_1000_RPM 1333    // 16,7Hz

#define RPM_TO_TICKS(RPM)   (RPM*SYNCHRO_TICKS_AT_1HZ_RPM/60)
#define TICKS_TO_RPM(TICKS) ((uint32_t)TICKS*60/SYNCHRO_TICKS_AT_1HZ_RPM)

typedef enum screen_index_en {
    SCREEN_MAIN_MENU = 0,
    SCREEN_PREVIEW,
    SCREEN_WORKING,
    SCREEN_NUM
} screen_index_t;

enum wash_mode_en { 
    WASH_MODE_NORMAL = 0,
    WASH_MODE_DELICATE,
    WASH_MODE_INTENSIVE,
    WASH_MODE_RINSE,
    WASH_MODE_SPIN,
    WASH_MODE_DRAIN,
    WASH_MODE_NUM
};

typedef enum wash_param_en {
    WASH_PARAM_PREWASH_TIME = 0,
    WASH_PARAM_WASH_TIME,
    WASH_PARAM_TEMPERATURE,
    WASH_PARAM_RINSE_CNT,
    WASH_PARAM_SPIN_RPM,
    WASH_PARAM_NUM
} wash_param_t;

typedef enum setup_speed_rpm_en {
    SETUP_SPEED_NO,
    SETUP_SPEED_400RPM,
    SETUP_SPEED_600RPM,
    SETUP_SPEED_800RPM,
    SETUP_SPEED_1000RPM,
    SETUP_SPEED_NUM
} setup_speed_rpm_t;

#define MIN(A,B)    ((A>B)?B:A)


extern volatile bool scr_redraw;
extern volatile uint32_t synchro_counter;
extern volatile uint16_t measured_synchro_ticks;
extern volatile uint32_t measured_rpm;

#endif // __COMMON_H__
