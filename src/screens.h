#ifndef __SCREENS_H__
#define __SCREENS_H__

#include <Arduino.h>

#define PREWASH_PARAM_STR_NUM       5
#define TEMPERATURE_PARAM_STR_NUM   5
#define WASH_PARAM_STR_NUM          4
#define RINSE_PARAM_STR_NUM         5
#define SPIN_PARAM_STR_NUM          5 

void screen_main(uint8_t mode);
void screen_preview(uint8_t mode);
void screen_edit_prewash_time(uint8_t mode);
void screen_edit_wash_time(uint8_t mode);
void screen_edit_temperature(uint8_t mode);
void screen_edit_rinse(uint8_t mode);
void screen_edit_spin(uint8_t mode);

void screen_working(uint8_t mode);


void SelectNextParam(uint8_t mode);
void SelectPrevParam(uint8_t mode);

#endif //__SCREENS_H__
