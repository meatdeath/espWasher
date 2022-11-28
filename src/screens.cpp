#include "screens.h"
#include "common.h"
#include "program.h"
#include "sw_timers.h"
#include "lg240644-s8.h"
#include "lg24064-fonts.h"

#define SYMBOL_CODE_GRADUS   127

const char *main_menu_str[WASH_MODE_NUM] = {
    "Обычная",//"Нормально ",
    "Бережная",
    "Интенсивная",
    "Полоскание",
    "Отжим",
    "Слив"
};
const char *wash_param_str[WASH_PARAM_NUM] = {
    "Замачивание",
    "Стирка",
    "Температура",
    "Полоскания",
    "Отжим",
};

const char *main_menu_time[] = {
    "1:20",
    "1:50",
    "1:20",
    "0:30",
    "0:10",
    "0:02"
};

const char *prewash_time_str[PREWASH_PARAM_STR_NUM] = {
    "-    ",
    "15мин",
    "30мин",
    "45мин",
    "60мин"
};

const char *temperature_str[TEMPERATURE_PARAM_STR_NUM] = {
    "-",
    "30\x7FС",
    "40\x7FС",
    "60\x7FС",
    "90\x7FС"
};

const char *wash_time_str[WASH_PARAM_STR_NUM] = {
    "15мин",
    "30мин",
    "45мин",
    "60мин"
};

const char *rinse_short_str[RINSE_PARAM_STR_NUM] = {
    "- ",
    "1x",
    "2x",
    "3x",
    "4x",
};
const char *rinse_long_str[RINSE_PARAM_STR_NUM] = {
    "-      ",
    "1 цикл ",
    "2 цикла",
    "3 цикла",
    "4 цикла",
};

const char *spin_short_str[SPIN_PARAM_STR_NUM] = {
    "-    ",
    "400об/м",
    "600об/м",
    "800об/м",
    "1000об/м"
};
const char *spin_long_str[SPIN_PARAM_STR_NUM] = {
    "-     ",
    "400об/мин",
    "600об/мин",
    "800об/мин",
    "1000об/мин"
};


char tmp_str[40];

extern wash_setup_t wash_setup[WASH_MODE_NUM];

void screen_main(uint8_t mode) {
    // lcd_print_font(  0, 15,  main_menu_str[mode], &font[FONT_ARIALBOLD20], 15, 0);
    // lcd_print_font(148, 13, main_menu_time[mode], &font[FONT_BIG_CLOCK_2], 15, 0);
    
    strcpy(tmp_str, main_menu_str[mode]);
    int len = strlen(tmp_str)/2;
    while(len++<12) 
        strcat(tmp_str, " ");
    lcd_print_font(  6, 0,  tmp_str, &font[FONT_ARIALBOLD20], 15, 0);
    lcd_print_font(  12, 30, (mode<3)?"стирка":"        ", &font[FONT_ARIALBOLD20], 15, 0);
    lcd_print_font(180, 30, main_menu_time[mode], &font[FONT_ARIALBOLD20], 15, 0);
}


void screen_preview(uint8_t mode){
    lcd_print_font(  0, 0,  "                              ", &font[FONT_SMALL], 0, 15);
    strcpy(tmp_str, main_menu_str[mode]);
    if (mode<3) strcat(tmp_str, " стирка");
    lcd_print_font(  6, 0,  tmp_str, &font[FONT_SMALL], 0, 15);
    lcd_print_font(205, 0, main_menu_time[mode], &font[FONT_SMALL], 0, 15);
    switch(mode) {
        case WASH_MODE_NORMAL:
        case WASH_MODE_DELICATE:
        case WASH_MODE_INTENSIVE:
            lcd_print_font( 0, 16, wash_param_str[WASH_PARAM_PREWASH_TIME], &font[FONT_SMALL], 15, 0);
            lcd_print_font( 0, 32, wash_param_str[WASH_PARAM_TEMPERATURE], &font[FONT_SMALL], 15, 0);
            lcd_print_font( 0, 48, wash_param_str[WASH_PARAM_RINSE_CNT], &font[FONT_SMALL], 15, 0);
            lcd_print_font( 132, 16, wash_param_str[WASH_PARAM_WASH_TIME], &font[FONT_SMALL], 15, 0);
            lcd_print_font( 132, 32, wash_param_str[WASH_PARAM_SPIN_RPM], &font[FONT_SMALL], 15, 0);

            lcd_print_font( 78, 16, ":", &font[FONT_SMALL], 15, 0);
            lcd_print_font( 78, 32, ":", &font[FONT_SMALL], 15, 0);
            lcd_print_font( 78, 48, ":", &font[FONT_SMALL], 15, 0);
            lcd_print_font( 174, 16, ":", &font[FONT_SMALL], 15, 0);
            lcd_print_font( 174, 32, ":", &font[FONT_SMALL], 15, 0);
            
            lcd_print_font( 84, 16, prewash_time_str[wash_setup[mode].prewash_time_idx], &font[FONT_SMALL], 15, 0);
            lcd_print_font( 84, 32, temperature_str[wash_setup[mode].temperature_idx], &font[FONT_SMALL], 15, 0);
            lcd_print_font( 84, 48, rinse_short_str[wash_setup[mode].rinse_cnt], &font[FONT_SMALL], 15, 0);
            lcd_print_font( 180, 16, wash_time_str[wash_setup[mode].wash_time_idx], &font[FONT_SMALL], 15, 0);
            lcd_print_font( 180, 32, spin_short_str[wash_setup[mode].spin_rpm_idx], &font[FONT_SMALL], 15, 0);
            break;
        case WASH_MODE_RINSE:
            break;
        case WASH_MODE_SPIN:
            break;
        case WASH_MODE_DRAIN:
            break;
    }
}

#define MIN(A,B)    ((A>B)?B:A)
#define MAX_PARAM_PER_SCREEN 3

void screen_edit_param( const char *param_name, const char *param_str[], uint8_t param_num, uint8_t param_idx);

void screen_edit_prewash_time(uint8_t mode){
    screen_edit_param(wash_param_str[WASH_PARAM_PREWASH_TIME], prewash_time_str, PREWASH_PARAM_STR_NUM, wash_setup[mode].prewash_time_idx );
}

void screen_edit_wash_time(uint8_t mode){
    screen_edit_param(wash_param_str[WASH_PARAM_WASH_TIME], wash_time_str, WASH_PARAM_STR_NUM, wash_setup[mode].wash_time_idx );
}

void screen_edit_temperature(uint8_t mode){
    screen_edit_param(wash_param_str[WASH_PARAM_TEMPERATURE], temperature_str, TEMPERATURE_PARAM_STR_NUM, wash_setup[mode].temperature_idx );
}

void screen_edit_rinse(uint8_t mode){
    screen_edit_param(wash_param_str[WASH_PARAM_RINSE_CNT], rinse_long_str, RINSE_PARAM_STR_NUM, wash_setup[mode].rinse_cnt );
}

void screen_edit_spin(uint8_t mode){
    screen_edit_param(wash_param_str[WASH_PARAM_SPIN_RPM], spin_long_str, SPIN_PARAM_STR_NUM, wash_setup[mode].spin_rpm_idx );
}

void screen_edit_param( const char *param_name, const char *param_str[], uint8_t param_num, uint8_t param_idx) {
    lcd_print_font(  0, 0,  "                              ", &font[FONT_SMALL], 0, 15);
    strcpy(tmp_str, param_name);
    lcd_print_font(  6, 0,  tmp_str, &font[FONT_SMALL], 0, 15);

    uint8_t offset = param_idx;
    if( offset == (param_num-1) && offset > 2) offset--;
    if( offset > 0 ) offset--;
    for( uint i = 0; i < MIN(param_num,MAX_PARAM_PER_SCREEN); i++) {
        // strcpy(tmp_str, " ");
        // strcat(tmp_str, param_str[offset+i]);
        // uint8_t colour1 = 15, colour2 = 0;
        // // if( blink && (i+offset) == param_idx ) {
        // //     colour1 = 0; 
        // //     colour2 = 15;
        // // }
        // if( (i+offset) == param_idx ) {
        //     colour1 = faded_blink; 
        //     colour2 = FADED_BLINK_MAX-faded_blink;
        // }
        // lcd_print_font(6, 16*(i+1), "                            ", &font[FONT_SMALL], colour1, colour2);
        // lcd_print_font(6, 16*(i+1), tmp_str,  &font[FONT_SMALL], colour1, colour2);
        uint8_t colour = 15;
        strcpy(tmp_str, " ");
        if( (i+offset) == param_idx ) {
            colour = faded_blink; 
            strcat(tmp_str, "> ");
        } else {
            strcat(tmp_str, "  ");
        }

        lcd_print_font(0, 16*(i+1), tmp_str,  &font[FONT_SMALL], colour, 0);

        strcpy(tmp_str, param_str[offset+i]);
        strcat(tmp_str, "        ");
        lcd_print_font(12, 16*(i+1), tmp_str,  &font[FONT_SMALL], colour, 0);
    }
}

void screen_working(uint8_t mode){

}

extern uint8_t screen_index;
void SelectNextParam(uint8_t mode)
{
    switch(screen_index)
    {
        case SCREEN_EDIT_PREWASH_TIME:  
            if(wash_setup[mode].prewash_time_idx < (PREWASH_PARAM_STR_NUM-1))
                wash_setup[mode].prewash_time_idx++; 
            break;
        case SCREEN_EDIT_WASH_TIME:
            if(wash_setup[mode].wash_time_idx < (WASH_PARAM_STR_NUM-1))
                wash_setup[mode].wash_time_idx++; 
            break;
        case SCREEN_EDIT_TEMPERATURE:
            if(wash_setup[mode].temperature_idx < (TEMPERATURE_PARAM_STR_NUM-1))
                wash_setup[mode].temperature_idx++; 
            break;
        case SCREEN_EDIT_RINSE:
            if(wash_setup[mode].rinse_cnt < (RINSE_PARAM_STR_NUM-1))
                wash_setup[mode].rinse_cnt++; 
            break;
        case SCREEN_EDIT_SPIN:
            if(wash_setup[mode].spin_rpm_idx < (SPIN_PARAM_STR_NUM-1))
                wash_setup[mode].spin_rpm_idx++; 
            break;
    }
}

void SelectPrevParam(uint8_t mode)
{
    switch(screen_index)
    {
        case SCREEN_EDIT_PREWASH_TIME:  
            if(wash_setup[mode].prewash_time_idx > 0)
                wash_setup[mode].prewash_time_idx--; 
            break;
        case SCREEN_EDIT_WASH_TIME:
            if(wash_setup[mode].wash_time_idx > 0)
                wash_setup[mode].wash_time_idx--; 
            break;
        case SCREEN_EDIT_TEMPERATURE:
            if(wash_setup[mode].temperature_idx > 0)
                wash_setup[mode].temperature_idx--; 
            break;
        case SCREEN_EDIT_RINSE:
            if(wash_setup[mode].rinse_cnt > 0)
                wash_setup[mode].rinse_cnt--; 
            break;
        case SCREEN_EDIT_SPIN:
            if(wash_setup[mode].spin_rpm_idx > 0)
                wash_setup[mode].spin_rpm_idx--; 
            break;
    }
}