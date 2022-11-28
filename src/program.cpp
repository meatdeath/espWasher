#include "program.h"
#include "common.h"

#define SUB_PROGRAM_WASH_NORMAL_IN_STEPS_NUM    5
#define SUB_PROGRAM_WASH_NORMAL_STEPS_NUM       4
#define SUB_PROGRAM_HEATER_ON_STEPS_NUM         2

enum wash_cycle_duration_en {
    DURATION_NO,
    DURATION_15MIN,
    DURATION_30MIN,
    DURATION_45MIN,
    DURATION_60MIN,
    DURATION_NUM
};

wash_setup_t wash_setup[WASH_MODE_NUM] = {
    { .prewash_time_idx = DURATION_15MIN, .wash_time_idx = DURATION_30MIN, .temperature_idx = TEMPERATURE_IDX_60C, .spin_rpm_idx = SETUP_SPEED_800RPM, .rinse_cnt = 3},   // Normal
    { .prewash_time_idx = DURATION_15MIN, .wash_time_idx = DURATION_30MIN, .temperature_idx = TEMPERATURE_IDX_40C, .spin_rpm_idx = SETUP_SPEED_600RPM, .rinse_cnt = 3},   // Delicate
    { .prewash_time_idx = DURATION_15MIN, .wash_time_idx = DURATION_30MIN, .temperature_idx = TEMPERATURE_IDX_60C, .spin_rpm_idx = SETUP_SPEED_800RPM, .rinse_cnt = 4},   // Intensive
    { .prewash_time_idx = UNDEFINED_SETUP_VALUE, .wash_time_idx = UNDEFINED_SETUP_VALUE, .temperature_idx = UNDEFINED_SETUP_VALUE, .spin_rpm_idx = SETUP_SPEED_800RPM, .rinse_cnt = 3},   //Rinse
    { .prewash_time_idx = UNDEFINED_SETUP_VALUE, .wash_time_idx = UNDEFINED_SETUP_VALUE, .temperature_idx = UNDEFINED_SETUP_VALUE, .spin_rpm_idx = SETUP_SPEED_800RPM, .rinse_cnt = UNDEFINED_SETUP_VALUE},   // Spin
    { .prewash_time_idx = UNDEFINED_SETUP_VALUE, .wash_time_idx = UNDEFINED_SETUP_VALUE, .temperature_idx = UNDEFINED_SETUP_VALUE, .spin_rpm_idx = SETUP_SPEED_800RPM, .rinse_cnt = UNDEFINED_SETUP_VALUE}    // Drain
};

sub_program_step_t sp_heater_on[SUB_PROGRAM_HEATER_ON_STEPS_NUM] = {
    { 
        .step_type = SP_STEP_ADJUST_WATER_LEVEL,
        .step_param = { .valve      = { .water_level = WATER_LEVEL_HIGH, .valve_type = VALVE_TYPE_COLD, .timeout = VALVE_OPEN_MAX_TIME } }
    },
    { 
        .step_type = SP_STEP_HEATER_ON,
        .step_param = { .heater     = { .temperature = TEMPERATURE_IDX_60C, .timeout = HEATER_ON_TIMEOUT_FOR_60C } }
    }
};

sub_program_step_t sp_wash_normal_in[SUB_PROGRAM_WASH_NORMAL_IN_STEPS_NUM] = {
    {
        .step_type = SP_STEP_ADJUST_WATER_LEVEL,
        .step_param = { .valve      = { .water_level = WATER_LEVEL_HIGH, .valve_type = VALVE_TYPE_COLD, .timeout = VALVE_OPEN_MAX_TIME } }
    },
    {   
        .step_type = SP_STEP_TURN_DRUM,   
        .step_param = { .rotation   = { .duration = 7, .direction = ROTATE_CW, .speed = SPEED_20RPM }} 
    },
    { 
        .step_type = SP_STEP_IDLE,        
        .step_param = { .idle       = { .duration = 3 } } 
    },
    { 
        .step_type = SP_STEP_TURN_DRUM,   
        .step_param = { .rotation   = { .duration = 7, .direction = ROTATE_CCW, .speed = SPEED_20RPM } } 
    },
    { 
        .step_type = SP_STEP_IDLE,        
        .step_param = { .idle       = { .duration = 3 } } 
    }
};

sub_program_step_t sp_wash_normal[SUB_PROGRAM_WASH_NORMAL_STEPS_NUM] = {
    { 
        .step_type = SP_STEP_TURN_DRUM,   
        .step_param = { .rotation   = { .duration = 17, .direction = ROTATE_CW, .speed = SPEED_20RPM } } 
    },
    { 
        .step_type = SP_STEP_IDLE,        
        .step_param = { .idle       = { .duration = 3 } } 
    },
    { 
        .step_type = SP_STEP_TURN_DRUM,   
        .step_param = { .rotation   = { .duration = 17, .direction = ROTATE_CCW, .speed = SPEED_20RPM } 
        } 
    },
    { 
        .step_type = SP_STEP_IDLE,        
        .step_param = { .idle       = { .duration = 3 } } 
    }
};


