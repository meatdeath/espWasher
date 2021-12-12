#include "program.h"

#define SUB_PROGRAM_WASH_NORMAL_IN_STEPS_NUM    4
#define SUB_PROGRAM_WASH_NORMAL_STEPS_NUM       4
#define SUB_PROGRAM_HEATER_ON_STEPS_NUM         2

sub_program_step_t sp_heater_on[SUB_PROGRAM_HEATER_ON_STEPS_NUM] = {
    { .step_type = SP_STEP_ADJUST_WATER_LEVEL_FOR_HEATER },
    { .step_type = SP_STEP_HEATER_ON }
};

sub_program_step_t sp_wash_normal_in[SUB_PROGRAM_WASH_NORMAL_IN_STEPS_NUM] = {
    { .step_type = SP_STEP_TURN_DRUM,   .step_param = { .rotation   = { 
                                                            .duration = 7, 
                                                            .direction = ROTATE_CLOCKWISE, 
                                                            .speed = SPEED_20RPM 
    } } },
    { .step_type = SP_STEP_IDLE,        .step_param = { .idle       = { .duration = 3 } } },
    { .step_type = SP_STEP_TURN_DRUM,   .step_param = { .rotation   = { 
                                                            .duration = 7, 
                                                            .direction = ROTATE_COUNTER_CLOCKWISE,
                                                            .speed = SPEED_20RPM
    } } },
    { .step_type = SP_STEP_IDLE,        .step_param = { .idle       = { .duration = 3 } } }
};

sub_program_step_t sp_wash_normal[SUB_PROGRAM_WASH_NORMAL_IN_STEPS_NUM] = {
    { .step_type = SP_STEP_TURN_DRUM,   .step_param = { .rotation   = { 
                                                            .duration = 7, 
                                                            .direction = ROTATE_CLOCKWISE, 
                                                            .speed = SPEED_20RPM 
    } } },
    { .step_type = SP_STEP_IDLE,        .step_param = { .idle       = { .duration = 3 } } },
    { .step_type = SP_STEP_TURN_DRUM,   .step_param = { .rotation   = { 
                                                            .duration = 7, 
                                                            .direction = ROTATE_COUNTER_CLOCKWISE,
                                                            .speed = SPEED_20RPM
    } } },
    { .step_type = SP_STEP_IDLE,        .step_param = { .idle       = { .duration = 3 } } }
};