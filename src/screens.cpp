#include "screens.h"
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

const char *zamachivanie[] = {
    "-    ",
    "15мин",
    "30мин",
    "45мин",
    "60мин"
};

const char *temperature[] = {
    "40\x7FС",
    "50\x7FС",
    "60\x7FС",
    "70\x7FС",
    "80\x7FС",
    "90\x7FС"
};
const char *wash_time[] = {
    "15мин",
    "30мин",
    "45мин",
    "60мин"
};
const char *rinse_short[] = {
    "- ",
    "1x",
    "2x",
    "3x",
    "4x",
};
const char *rinse_long[] = {
    "-      ",
    "1 цикл ",
    "2 цикла",
    "3 цикла",
    "4 цикла",
};
const char *spin_short[] = {
    "-    ",
    "400об/м",
    "600об/м",
    "800об/м",
    "1000об/м"
};
const char *spin_long[] = {
    "-     ",
    "400об/мин",
    "600об/мин",
    "800об/мин",
    "1000об/мин"
};

char mode_str[40];

void screen_main(uint8_t mode) {
    // lcd_print_font(  0, 15,  main_menu_str[mode], &font[FONT_ARIALBOLD20], 15, 0);
    // lcd_print_font(148, 13, main_menu_time[mode], &font[FONT_BIG_CLOCK_2], 15, 0);
    
    strcpy(mode_str, main_menu_str[mode]);
    int len = strlen(mode_str)/2;
    while(len++<12) 
        strcat(mode_str, " ");
    lcd_print_font(  6, 0,  mode_str, &font[FONT_ARIALBOLD20], 15, 0);
    lcd_print_font(  12, 30, (mode<3)?"стирка":"        ", &font[FONT_ARIALBOLD20], 15, 0);
    lcd_print_font(180, 30, main_menu_time[mode], &font[FONT_ARIALBOLD20], 15, 0);
}


void screen_preview(uint8_t mode){
    lcd_print_font(  0, 0,  "                              ", &font[FONT_SMALL], 0, 15);
    strcpy(mode_str, main_menu_str[mode]);
    if (mode<3) strcat(mode_str, " стирка");
    lcd_print_font(  6, 0,  mode_str, &font[FONT_SMALL], 0, 15);
    lcd_print_font(205, 0, main_menu_time[mode], &font[FONT_SMALL], 0, 15);
    switch(mode) {
        case WASH_MODE_NORMAL:
        case WASH_MODE_DELICATE:
        case WASH_MODE_INTENSIVE:
            lcd_print_font( 6, 16, wash_param_str[WASH_PARAM_ZAMACHIVANIE], &font[FONT_SMALL], 15, 0);
            lcd_print_font( 6, 32, wash_param_str[WASH_PARAM_TEMPERATURE], &font[FONT_SMALL], 15, 0);
            lcd_print_font( 6, 48, wash_param_str[WASH_PARAM_RINSE], &font[FONT_SMALL], 15, 0);
            lcd_print_font( 138, 16, wash_param_str[WASH_PARAM_STIRKA], &font[FONT_SMALL], 15, 0);
            lcd_print_font( 138, 32, wash_param_str[WASH_PARAM_SPIN], &font[FONT_SMALL], 15, 0);

            lcd_print_font( 84, 16, ":", &font[FONT_SMALL], 15, 0);
            lcd_print_font( 84, 32, ":", &font[FONT_SMALL], 15, 0);
            lcd_print_font( 84, 48, ":", &font[FONT_SMALL], 15, 0);
            lcd_print_font( 180, 16, ":", &font[FONT_SMALL], 15, 0);
            lcd_print_font( 180, 32, ":", &font[FONT_SMALL], 15, 0);
            
            lcd_print_font( 90, 16, zamachivanie[1], &font[FONT_SMALL], 15, 0);
            lcd_print_font( 90, 32, temperature[2], &font[FONT_SMALL], 15, 0);
            lcd_print_font( 90, 48, rinse_short[3], &font[FONT_SMALL], 15, 0);
            lcd_print_font( 186, 16, wash_time[2], &font[FONT_SMALL], 15, 0);
            lcd_print_font( 186, 32, spin_short[2], &font[FONT_SMALL], 15, 0);
            break;
        case WASH_MODE_RINSE:
            break;
        case WASH_MODE_SPIN:
            break;
        case WASH_MODE_DRAIN:
            break;
    }
}

void screen_edit(uint8_t mode){

}

void screen_working(uint8_t mode){

}