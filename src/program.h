#ifndef __PROGRAM_H__
#define __PROGRAM_H__

#include <Arduino.h>

// ----------------------------------------------------------------------------
// Constant definitions
// ----------------------------------------------------------------------------

#define VALVE_OPEN_MAX_TIME     (2*60) // Valve can be open for 2 min maximum, otherwise a leakage detected
#define HEATER_ON_TIMEOUT_FOR_30C   (5*60)      // A Timeout of 5 min for heater to be on to reach 30C, otherwise heater malfuction detected
#define HEATER_ON_TIMEOUT_FOR_40C   (8*60)      // A Timeout of 8 min for heater to be on to reach 40C, otherwise heater malfuction detected
#define HEATER_ON_TIMEOUT_FOR_60C   (10*60)     // A Timeout of 10 min for heater to be on to reach 60C, otherwise heater malfuction detected
#define HEATER_ON_TIMEOUT_FOR_90C   (20*60)     // A Timeout of 20 min for heater to be on to reach 90C, otherwise heater malfuction detected

// ----------------------------------------------------------------------------
// Type definitions
// ----------------------------------------------------------------------------

// Rotation directions
typedef enum rotation_direction_en {
    ROTATE_CW = 0,                      // Rotate the drum clock-wise
    ROTATE_CCW                          // Rotate the drum counter clock-wise
} rotation_direction_t;

// Rotation speeds
typedef enum rotation_speed_en {
    SPEED_20RPM = 0,
    SPEED_40RPM,
    SPEED_60RPM,
    SPEED_100RPM,
    SPEED_200RPM,
    SPEED_400RPM,
    SPEED_600RPM,
    SPEED_800RPM
} rotation_speed_t;

// Water levels
typedef enum water_level_en {
    WATER_LEVEL_EMPTY = 0,              // No water
    WATER_LEVEL_LOW,                    // Water on the low level
    WATER_LEVEL_MIDDLE,                 // Water on the middle level
    WATER_LEVEL_HIGH
} water_level_t;

// Heater temperatures
typedef enum heater_temperature_en {
    TEMPERATURE_IDX_NO_HEAT = 0,     // No heat
    TEMPERATURE_IDX_30C,             // Preheat to 30C
    TEMPERATURE_IDX_40C,             // Preheat to 40C
    TEMPERATURE_IDX_60C,             // Preheat to 60C
    TEMPERATURE_IDX_90C              // Preheat to 90C
} heater_temperature_t;

typedef enum valve_type_en {
    VALVE_TYPE_COLD = 0,                // Cold water valve
    VALVE_TYPE_HOT                      // Hot water valve
} valve_type_t;

// ----------------------------------------------------------------------------

// Wash steps definitions
typedef enum sub_program_step_en {
    SP_STEP_IDLE = 0,
    SP_STEP_TURN_DRUM,
    SP_STEP_ADJUST_WATER_LEVEL,
    SP_STEP_HEATER_ON
} step_type_t;

// ----------------------------------------------------------------------------


#define UNDEFINED_SETUP_VALUE   UINT8_MAX

typedef struct wash_setup_st {
    uint8_t prewash_time_idx;
    uint8_t wash_time_idx;
    uint8_t temperature_idx;
    uint8_t spin_rpm_idx;
    uint8_t rinse_cnt;
} wash_setup_t;

// ----------------------------------------------------------------------------

// Sub-program definition
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
        struct {
            water_level_t water_level;
            valve_type_t valve_type;
            uint16_t timeout;
        } valve;
        struct {
            heater_temperature_t temperature;
            uint16_t timeout;
        } heater;
        //uint8_t temperature;
    } step_param;
} sub_program_step_t;

// Program cicle definition
typedef struct program_cicle_st {
    struct {
        sub_program_step_t *sub_program_steps;    // S - список шагов подпрограммы в цикле
        uint8_t sub_program_steps_num;      // количество шагов подпрограммы в списке шагов
    } *sub_program_ptr;
    uint8_t sub_program_num;            // количество подпрограмм в программе
    uint8_t sub_program_repetition_num; // В - количество повторов подпрограммы
    uint8_t user_repetition_num;        // С - количество повторов подпрограммы определяемое пользователем
} program_cicle_t;                      // время цикла Т = A*t(S) * B * C 



// Program definition 
typedef struct program_st {
    program_cicle_t *program_cicle;
    uint8_t program_cicle_num;
} program_t;


#endif //__PROGRAM_H__
