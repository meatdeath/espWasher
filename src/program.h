#ifndef __PROGRAM_H__
#define __PROGRAM_H__

#include <Arduino.h>

typedef enum rotation_direction_en {
    ROTATE_CLOCKWISE = 0,
    ROTATE_COUNTER_CLOCKWISE
} rotation_direction_t;

typedef enum rotation_speed_en {
    SPEED_10RPM = 0,
    SPEED_20RPM,
    SPEED_30RPM,
    SPEED_100RPM,
    SPEED_200RPM,
    SPEED_400RPM,
    SPEED_600RPM,
    SPEED_800RPM
} rotation_speed_t;

typedef enum sub_program_step_en {
    SP_STEP_IDLE = 0,
    SP_STEP_TURN_DRUM,
    SP_STEP_ADJUST_WATER_LEVEL_FOR_HEATER,
    SP_STEP_HEATER_ON
} step_type_t;

typedef struct sub_program_step_st {
    step_type_t step_type;
    union step_params_un {
        struct {
            uint8_t duration;
            rotation_direction_t direction;
            rotation_speed_t speed;
        } rotation;
        struct {
            uint8_t duration;
        } idle;
        //uint8_t temperature;
    } step_param;
} sub_program_step_t;



#endif //__PROGRAM_H__