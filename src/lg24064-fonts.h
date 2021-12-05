#ifndef __LG24064_FONTS_H__
#define __LG24064_FONTS_H__

#include "types.h"

extern uchar hz16_tab[];
extern uchar hz12_tab[];
extern uchar ASC_6[];
extern uchar ASC_8[];
extern uchar ASC_16[];


typedef struct font_desc_st {
    const char name[20];
    const uint8_t *fontData;
    const uint8_t rowsPerSymbol;
    const uint8_t colsMaxPerSymbol;
    const uint8_t bytesPerColumn;
    const uint8_t firstCode;
    const uint8_t lastCode;
} font_desc_t;

extern const uint8_t Verdana12x14en[];
extern const uint8_t Verdana12x14ru[];



extern const uint8_t Tahoma16x32[];
#define FONT_BIG_CLOCK_COLUMNS          16
#define FONT_BIG_CLOCK_ROWS             32
#define FONT_BIG_CLOCK_FIRST_CODE       48
#define FONT_BIG_CLOCK_LAST_CODE        59

extern const uint8_t Tahoma24x37[];
#define FONT_BIG_CLOCK_2_COLUMNS          24
#define FONT_BIG_CLOCK_2_ROWS             37
#define FONT_BIG_CLOCK_2_FIRST_CODE       48
#define FONT_BIG_CLOCK_2_LAST_CODE        59

#define FONT_BYTES_PER_COLUMN(rows)     ((rows+7)/8)

enum font_en {
    FONT_BIG_CLOCK,
    FONT_BIG_CLOCK_2,
    FONT_NUM
};

extern font_desc_t font[FONT_NUM];

#endif //__LG24064_FONTS_H__