#ifndef __COMMON_H__
#define __COMMON_H__

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
} wash_submode_t;


typedef enum screen_index_en {
    SCREEN_MAIN_MENU = 0,
    SCREEN_PREVIEW,
    SCREEN_EDIT_PREWASH_TIME,
    SCREEN_EDIT_TEMPERATURE,
    SCREEN_EDIT_WASH_TIME,
    SCREEN_EDIT_RINSE,
    SCREEN_EDIT_SPIN,
    SCREEN_NUM
} screen_index_t;

typedef enum setup_speed_rpm_en {
    SETUP_SPEED_NO,
    SETUP_SPEED_400RPM,
    SETUP_SPEED_600RPM,
    SETUP_SPEED_800RPM,
    SETUP_SPEED_1000RPM,
} nsetup_spped_rpm_t;

#endif // __COMMON_H__
