#include "screens.h"
#include "common.h"
#include "program.h"
#include "sw_timers.h"
#include "lg240644-s8.h"
#include "lg24064-fonts.h"

#define SYMBOL_CODE_GRADUS 127
#define SCR_LINE_V_SIZE 16
#define SCR_Y_LINE0 (0 * SCR_LINE_V_SIZE)
#define SCR_Y_LINE1 (1 * SCR_LINE_V_SIZE)
#define SCR_Y_LINE2 (2 * SCR_LINE_V_SIZE)
#define SCR_Y_LINE3 (3 * SCR_LINE_V_SIZE)

#define SCR_COLOR_WHITE 15
#define SCR_COLOR_GREY  8
#define SCR_COLOR_BLACK 0

const char *main_menu_str[WASH_MODE_NUM] = {
    "Обычная",     //стирка
    "Бережная",    //стирка
    "Интенсивная", //стирка
    "Полоскание",
    "Отжим",
    "Слив"};
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
    "0:02"};

const char *prewash_time_str[PREWASH_PARAM_STR_NUM] = {
    "-     ",
    "15мин ",
    "30мин ",
    "45мин ",
    "60мин "};

const char *temperature_str[TEMPERATURE_PARAM_STR_NUM] = {
    "-   ",
    "30\x7FС ",
    "40\x7FС ",
    "60\x7FС ",
    "90\x7FС "};

const char *wash_time_str[WASH_PARAM_STR_NUM] = {
    "-     "
    "15мин ",
    "30мин ",
    "45мин ",
    "60мин "};

const char *rinse_short_str[RINSE_PARAM_STR_NUM] = {
    "-  ",
    "1x ",
    "2x ",
    "3x ",
    "4x ",
};
const char *rinse_long_str[RINSE_PARAM_STR_NUM] = {
    "-      ",
    "1 цикл ",
    "2 цикла",
    "3 цикла",
    "4 цикла",
};

const char *spin_short_str[SPIN_PARAM_STR_NUM] = {
    "-           ",
    "400об/м ",
    "600об/м ",
    "800об/м ",
    "1000об/м"};
const char *spin_long_str[SPIN_PARAM_STR_NUM] = {
    "-         ",
    "400об/мин ",
    "600об/мин ",
    "800об/мин ",
    "1000об/мин"};

char tmp_str[40];

extern wash_setup_t wash_setup[WASH_MODE_NUM];

//---------------------------------------------------------------------------------------

void screen_main(uint8_t mode)
{
    strcpy(tmp_str, main_menu_str[mode]);
    int len = strlen(tmp_str) / 2;
    while (len++ < 12)
        strcat(tmp_str, " ");
    lcd_print_font(6, 0, tmp_str, &font[FONT_ARIALBOLD20], SCR_COLOR_WHITE, SCR_COLOR_BLACK);
    lcd_print_font(12, 30, (mode < 3) ? "стирка" : "        ", &font[FONT_ARIALBOLD20], SCR_COLOR_WHITE, SCR_COLOR_BLACK);
    lcd_print_font(180, 30, main_menu_time[mode], &font[FONT_ARIALBOLD20], SCR_COLOR_WHITE, SCR_COLOR_BLACK);
}

//---------------------------------------------------------------------------------------

uint8_t screen_param_color(uint8_t mode_idx, uint8_t param_idx)
{
    uint8_t color = SCR_COLOR_WHITE;
    switch (param_idx)
    {
        case WASH_PARAM_PREWASH_TIME:
        case WASH_PARAM_WASH_TIME:
        case WASH_PARAM_TEMPERATURE:
            if (mode_idx > WASH_MODE_INTENSIVE) color = SCR_COLOR_GREY;
            break;
        case WASH_PARAM_RINSE_CNT:
            if (mode_idx > WASH_MODE_RINSE) color = SCR_COLOR_GREY;
            break;
        case WASH_PARAM_SPIN_RPM:
            if (mode_idx > WASH_MODE_SPIN) color = SCR_COLOR_GREY;
            break;
    }
    return color;
}

//---------------------------------------------------------------------------------------

void screen_preview(uint8_t mode)
{
    lcd_print_font(0, SCR_Y_LINE0, "                              ", &font[FONT_SMALL], SCR_COLOR_BLACK, SCR_COLOR_WHITE);
    strcpy(tmp_str, main_menu_str[mode]);
    if (mode < 3) strcat(tmp_str, " стирка");
    lcd_print_font(   6, SCR_Y_LINE0, tmp_str, &font[FONT_SMALL], SCR_COLOR_BLACK, SCR_COLOR_WHITE);
    lcd_print_font( 205, SCR_Y_LINE0, main_menu_time[mode], &font[FONT_SMALL], SCR_COLOR_BLACK, SCR_COLOR_WHITE);

    lcd_print_font(   0, SCR_Y_LINE1, wash_param_str[WASH_PARAM_PREWASH_TIME], 
                    &font[FONT_SMALL], screen_param_color(mode,WASH_PARAM_PREWASH_TIME), SCR_COLOR_BLACK);
    lcd_print_font(   0, SCR_Y_LINE2, wash_param_str[WASH_PARAM_TEMPERATURE], 
                    &font[FONT_SMALL], screen_param_color(mode,WASH_PARAM_TEMPERATURE), SCR_COLOR_BLACK);
    lcd_print_font(   0, SCR_Y_LINE3, wash_param_str[WASH_PARAM_RINSE_CNT], 
                    &font[FONT_SMALL], screen_param_color(mode,WASH_PARAM_RINSE_CNT), SCR_COLOR_BLACK);
    lcd_print_font (132, SCR_Y_LINE1, wash_param_str[WASH_PARAM_WASH_TIME], 
                    &font[FONT_SMALL], screen_param_color(mode,WASH_PARAM_WASH_TIME), SCR_COLOR_BLACK);
    lcd_print_font( 132, SCR_Y_LINE2, wash_param_str[WASH_PARAM_SPIN_RPM], 
                    &font[FONT_SMALL], screen_param_color(mode,WASH_PARAM_SPIN_RPM), SCR_COLOR_BLACK);

    lcd_print_font(  78, SCR_Y_LINE1, ":", &font[FONT_SMALL], screen_param_color(mode,WASH_PARAM_PREWASH_TIME), SCR_COLOR_BLACK);
    lcd_print_font(  78, SCR_Y_LINE2, ":", &font[FONT_SMALL], screen_param_color(mode,WASH_PARAM_TEMPERATURE), SCR_COLOR_BLACK);
    lcd_print_font(  78, SCR_Y_LINE3, ":", &font[FONT_SMALL], screen_param_color(mode,WASH_PARAM_RINSE_CNT), SCR_COLOR_BLACK);
    lcd_print_font( 174, SCR_Y_LINE1, ":", &font[FONT_SMALL], screen_param_color(mode,WASH_PARAM_WASH_TIME), SCR_COLOR_BLACK);
    lcd_print_font( 174, SCR_Y_LINE2, ":", &font[FONT_SMALL], screen_param_color(mode,WASH_PARAM_SPIN_RPM), SCR_COLOR_BLACK);

    if (wash_setup[mode].prewash_time_idx != UNDEFINED_SETUP_VALUE) strcpy(tmp_str, prewash_time_str[wash_setup[mode].prewash_time_idx]);
    else strcpy(tmp_str, "-     ");
    lcd_print_font(  84, SCR_Y_LINE1, tmp_str, &font[FONT_SMALL], screen_param_color(mode,WASH_PARAM_PREWASH_TIME), SCR_COLOR_BLACK);

    if (wash_setup[mode].temperature_idx != UNDEFINED_SETUP_VALUE) strcpy(tmp_str, temperature_str[wash_setup[mode].temperature_idx]);
    else strcpy(tmp_str, "-    ");
    lcd_print_font(  84, SCR_Y_LINE2, tmp_str, &font[FONT_SMALL], screen_param_color(mode,WASH_PARAM_TEMPERATURE), SCR_COLOR_BLACK);
    
    if (wash_setup[mode].rinse_cnt != UNDEFINED_SETUP_VALUE) strcpy(tmp_str, rinse_short_str[wash_setup[mode].rinse_cnt]);
    else strcpy(tmp_str, "-  ");
    lcd_print_font(  84, SCR_Y_LINE3, tmp_str, &font[FONT_SMALL], screen_param_color(mode,WASH_PARAM_RINSE_CNT), SCR_COLOR_BLACK);
    
    if (wash_setup[mode].wash_time_idx != UNDEFINED_SETUP_VALUE) strcpy(tmp_str, wash_time_str[wash_setup[mode].wash_time_idx]);
    else strcpy(tmp_str, "-     ");
    lcd_print_font( 180, SCR_Y_LINE1, tmp_str, &font[FONT_SMALL], screen_param_color(mode,WASH_PARAM_WASH_TIME), SCR_COLOR_BLACK);
    
    if (wash_setup[mode].spin_rpm_idx != UNDEFINED_SETUP_VALUE) strcpy(tmp_str, spin_short_str[wash_setup[mode].spin_rpm_idx]);
    else strcpy(tmp_str, "-       ");
    lcd_print_font( 180, SCR_Y_LINE2, tmp_str, &font[FONT_SMALL], screen_param_color(mode,WASH_PARAM_SPIN_RPM), SCR_COLOR_BLACK);
    
}

//---------------------------------------------------------------------------------------

void screen_working(uint8_t mode)
{
    sprintf(tmp_str, "Test motor speed... %drpm   ", 0);
    lcd_print_font(0, SCR_Y_LINE0, tmp_str, &font[FONT_SMALL], SCR_COLOR_BLACK, SCR_COLOR_WHITE);
    sprintf(tmp_str, "Actual rpm: %d   ", measured_rpm);
    lcd_print_font(0, SCR_Y_LINE1, tmp_str, &font[FONT_SMALL], SCR_COLOR_BLACK, SCR_COLOR_WHITE);
    sprintf(tmp_str, "Time left... %d second(s)   ", 0);
    lcd_print_font(0, SCR_Y_LINE2, tmp_str, &font[FONT_SMALL], SCR_COLOR_BLACK, SCR_COLOR_WHITE);
}

//---------------------------------------------------------------------------------------
