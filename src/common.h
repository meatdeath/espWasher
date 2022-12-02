#ifndef __COMMON_H__
#define __COMMON_H__

typedef enum screen_index_en {
    SCREEN_MAIN_MENU = 0,
    SCREEN_PREVIEW,
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

#endif // __COMMON_H__
