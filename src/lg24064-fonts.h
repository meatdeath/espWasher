#ifndef __LG24064_FONTS_H__
#define __LG24064_FONTS_H__

#include "types.h"


typedef struct font_desc_st {
    const char name[20];
    const uint8_t *fontData;
    const uint8_t rowsPerSymbol;
    const uint8_t colsMaxPerSymbol;
    const uint8_t bytesPerColumn;
    const uint8_t firstCode;
    const uint8_t lastCode;
} font_desc_t;




extern const uint8_t Tahoma16x32[];
#define FONT_BIG_CLOCK_COLUMNS          16
#define FONT_BIG_CLOCK_ROWS             32
#define FONT_BIG_CLOCK_FIRST_CODE       48
#define FONT_BIG_CLOCK_LAST_CODE        59

extern const uint8_t Tahoma24x37[];
#define FONT_BIG_CLOCK_2_COLUMNS        24
#define FONT_BIG_CLOCK_2_ROWS           37
#define FONT_BIG_CLOCK_2_FIRST_CODE     48
#define FONT_BIG_CLOCK_2_LAST_CODE      59

extern const uint8_t Tahoma21x42[];
#define FONT_MIDDLE_COLUMNS             21
#define FONT_MIDDLE_ROWS                40
#define FONT_MIDDLE_FIRST_CODE          192
#define FONT_MIDDLE_LAST_CODE           255

extern const uint8_t ArialBold27x32[];
#define FONT_ARIALBOLD20_COLUMNS             27
#define FONT_ARIALBOLD20_ROWS                32
#define FONT_ARIALBOLD20_FIRST_CODE          32
#define FONT_ARIALBOLD20_LAST_CODE           191

extern const uint8_t Arial10[];
#define FONT_SMALL_ROWS                 16
#define FONT_SMALL_COLUMNS              13
#define FONT_SMALL_FIRST_CODE           32
#define FONT_SMALL_LAST_CODE            191

#define FONT_BYTES_PER_COLUMN(rows)     ((rows+7)/8)

enum font_en {
    FONT_BIG_CLOCK,
    FONT_BIG_CLOCK_2,
    FONT_MIDDLE,
    FONT_SMALL,
    FONT_ARIALBOLD20,
    FONT_NUM
};

extern font_desc_t font[FONT_NUM];

void lcd_print_font( uint8_t x, uint8_t y, String string, font_desc_t *font, uint8_t fore_color, uint8_t back_color, uint8_t spacing=1 );

#endif //__LG24064_FONTS_H__