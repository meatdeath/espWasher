#ifndef __SCREENS_H__
#define __SCREENS_H__

#include <Arduino.h>

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
    WASH_PARAM_ZAMACHIVANIE = 0,
    WASH_PARAM_STIRKA,
    WASH_PARAM_TEMPERATURE,
    WASH_PARAM_RINSE,
    WASH_PARAM_SPIN,
    WASH_PARAM_NUM
} wash_submode_t;

void screen_main(uint8_t mode);
void screen_preview(uint8_t mode);
void screen_edit(uint8_t mode);
void screen_working(uint8_t mode);

#endif //__SCREENS_H__
