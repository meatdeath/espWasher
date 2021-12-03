//*******************************************************************
//  ���������ֿ�		
//*******************************************************************

#include "lg240644-s8.h"
#include "lg24064-fonts.h"
#include "types.h"



font_desc_t font[FONT_NUM] = {
    {
        .name = "BIG CLOCK"
        .fontData = Tahoma16x32,
        .rowsPerSymbol = FONT_BIG_CLOCK_ROWS,
        .colsMaxPerSymbol = FONT_BIG_CLOCK_COLUMNS,
        .bytesPerColumn = FONT_BYTES_PER_COLUMN(FONT_BIG_CLOCK_ROWS),
        .firstCode = FONT_BIG_CLOCK_FIRST_CODE,
        .lastCode = FONT_BIG_CLOCK_LAST_CODE,
    }
};

uchar  hz16_tab[]=
	{
    	    
    0x00,0x00,0x7F,0xFC,0x44,0x04,0x47,0xE4,
    0x44,0x44,0x4A,0x84,0x71,0x04,0x42,0xC4,
    0x4C,0x3C,0x71,0x14,0x40,0x84,0x42,0x04,
    0x41,0x84,0x41,0x04,0x7F,0xFC,0x40,0x04,/*"ͼ",0*/
    
    0x00,0x04,0x7F,0x86,0x12,0x0C,0x12,0x10,
    0x12,0x20,0x12,0x08,0xFF,0xCC,0x12,0x18,
    0x12,0x20,0x12,0x44,0x12,0x86,0x12,0x0C,
    0x22,0x10,0x22,0x20,0x42,0x40,0x80,0x80,/*"��",1*/
    
    0x40,0x40,0x20,0x20,0x27,0xFE,0x09,0x20,
    0x89,0x20,0x52,0x7C,0x52,0x44,0x16,0xA8,
    0x2B,0x98,0x22,0x50,0xE2,0x20,0x22,0x30,
    0x22,0x50,0x22,0x88,0x23,0x0E,0x22,0x04,/*"Һ",2*/
    
    0x00,0x00,0x0F,0xF0,0x08,0x10,0x0F,0xF0,
    0x08,0x10,0x0F,0xF0,0x08,0x10,0x00,0x00,
    0x7E,0x7E,0x42,0x42,0x7E,0x7E,0x42,0x42,
    0x42,0x42,0x7E,0x7E,0x42,0x42,0x00,0x00,/*"��",3*/
    
    0x00,0x00,0x1F,0xF0,0x10,0x10,0x1F,0xF0,
    0x10,0x10,0x1F,0xF0,0x04,0x40,0x04,0x40,
    0x44,0x48,0x24,0x48,0x14,0x50,0x14,0x60,
    0x04,0x40,0xFF,0xFE,0x00,0x00,0x00,0x00,/*"��",4*/
    
    0x00,0x00,0x1F,0xF8,0x00,0x00,0x00,0x00,
    0x00,0x00,0x7F,0xFE,0x01,0x00,0x01,0x00,
    0x11,0x20,0x11,0x10,0x21,0x08,0x41,0x0C,
    0x81,0x04,0x01,0x00,0x05,0x00,0x02,0x00,/*"ʾ",5*/
    
    0x20,0x90,0x20,0x90,0x27,0xFC,0x20,0x90,
    0xFB,0xF8,0x22,0x08,0x73,0xF8,0x6A,0x08,
    0xA3,0xF8,0xA0,0x40,0x27,0xFE,0x20,0x40,
    0x20,0xA0,0x20,0x98,0x21,0x0E,0x26,0x04,/*"ģ",6*/
    
    0x20,0x80,0x20,0x80,0x20,0x80,0x23,0xF8,
    0xF8,0x88,0x20,0x88,0x20,0x88,0x20,0x88,
    0x2F,0xFE,0x20,0x80,0x39,0x40,0xE1,0x20,
    0x42,0x18,0x02,0x0E,0x04,0x04,0x08,0x00,/*"��",7*/
    
    0x0D,0xF8,0x71,0x08,0x11,0x08,0x11,0x08,
    0xFD,0x08,0x11,0xF8,0x30,0x00,0x3B,0xFC,
    0x54,0x40,0x50,0x40,0x93,0xFC,0x10,0x40,
    0x10,0x40,0x10,0x40,0x17,0xFE,0x10,0x00,/*"��",8*/
    
    0x01,0x00,0x00,0x80,0x3F,0xFE,0x20,0x00,
    0x27,0xF8,0x21,0x10,0x20,0xA0,0x20,0x40,
    0x2F,0xFE,0x20,0x44,0x20,0x40,0x20,0x40,
    0x20,0x40,0x40,0x40,0x41,0x40,0x80,0x80,/*"��",9*/
    };
     
uchar hz12_tab[]=
	{

    0x7F,0xE0,0x48,0x20,0x5F,0x20,0x6A,0x20,
    0x44,0x20,0x4A,0x20,0x75,0xA0,0x42,0x20,
    0x4C,0x20,0x42,0x20,0x7F,0xE0,0x00,0x00,/*"ͼ",0*/
    
    0x04,0x40,0xFE,0x40,0x24,0x80,0x25,0x00,
    0xFE,0x40,0x24,0x80,0x25,0x00,0x26,0x20,
    0x44,0x40,0x45,0x80,0x86,0x00,0x00,0x00,/*"��",1*/
    
    0x81,0x00,0x5F,0xE0,0x25,0x00,0x85,0xC0,
    0xAA,0x40,0x4E,0xC0,0x5A,0x40,0x49,0x80,
    0xC8,0x80,0x49,0x40,0x4E,0x20,0x00,0x00,/*"Һ",2*/
    
    0x1F,0x80,0x10,0x80,0x1F,0x80,0x10,0x80,
    0x1F,0x80,0x00,0x00,0x7B,0xE0,0x4A,0x20,
    0x7B,0xE0,0x4A,0x20,0x7B,0xE0,0x00,0x00,/*"��",3*/
    
    0x3F,0x80,0x20,0x80,0x3F,0x80,0x20,0x80,
    0x3F,0x80,0x00,0x00,0x4A,0x40,0x2A,0x40,
    0x2A,0x80,0x0B,0x00,0xFF,0xE0,0x00,0x00,/*"��",4*/
    
    0x00,0x80,0x7F,0xC0,0x00,0x00,0x00,0x00,
    0xFF,0xE0,0x04,0x00,0x14,0x80,0x24,0x40,
    0x44,0x20,0x84,0x20,0x1C,0x00,0x00,0x00,/*"ʾ",5*/
    
    0x2F,0xE0,0x22,0x80,0xF7,0xC0,0x24,0x40,
    0x67,0xC0,0x74,0x40,0xA7,0xC0,0xA1,0x00,
    0x2F,0xE0,0x22,0x80,0x2C,0x60,0x00,0x00,/*"ģ",6*/
    
    0x42,0x00,0x42,0x00,0x4F,0xC0,0xF2,0x40,
    0x42,0x40,0x42,0x40,0x5F,0xE0,0x42,0x00,
    0xF5,0x00,0x88,0x80,0x30,0x60,0x00,0x00,/*"��",7*/
    
    0x7F,0xE0,0x40,0x40,0x90,0x00,0x1F,0xC0,
    0x10,0x00,0x20,0x00,0x3F,0xC0,0x00,0x40,
    0xFF,0x40,0x00,0x40,0x03,0x80,0x00,0x00,/*"д",0*/
    
    0x40,0x40,0x2F,0xE0,0x04,0x40,0x94,0x40,
    0x54,0x80,0x22,0x80,0x22,0x80,0xC1,0x00,
    0x42,0x80,0x44,0x40,0x58,0x20,0x00,0x00,/*"��",1*/
    
    0x04,0x00,0x7F,0xE0,0xC0,0x20,0x3F,0x80,
    0x02,0x00,0x04,0x00,0xFF,0xE0,0x04,0x00,
    0x04,0x00,0x04,0x00,0x1C,0x00,0x00,0x00,/*"��",2*/

    0x37,0xC0,0xE4,0x40,0x24,0x40,0xF7,0xC0,
    0x20,0x00,0x6F,0xE0,0x71,0x00,0xA7,0xC0,
    0xA1,0x00,0x21,0x00,0x2F,0xE0,0x00,0x00,/*"��",8*/
    
    0x04,0x00,0x7F,0xE0,0x40,0x00,0x5F,0x80,
    0x45,0x00,0x42,0x00,0x7F,0xE0,0x42,0x40,
    0x42,0x00,0x82,0x00,0x8E,0x00,0x00,0x00,/*"��",9*/

	};

//*******************************************************************
// ����ASCII�ֿ�6��*8��		
//*******************************************************************

uchar ASC_6[]={
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,// " "
    0x30,0x78,0x78,0x30,0x30,0x00,0x30,0x00,// "!"
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x18,0x30,0x60,0x60,0x60,0x30,0x18,0x00,// "("
    0x60,0x30,0x18,0x18,0x18,0x30,0x60,0x00,// ")"
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x20,0x20,0xF8,0x20,0x20,0x00,0x00,0x00,// "+"
    0x00,0x00,0x00,0x00,0x00,0x60,0x60,0xC0,// ","
    0x00,0x00,0x00,0xFC,0x00,0x00,0x00,0x00,// "-"
    0x00,0x00,0x00,0x00,0x00,0x60,0x60,0x00,// "."
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x30,0x48,0x48,0x48,0x48,0x48,0x48,0x30,// "0"
    0x10,0x30,0x10,0x10,0x10,0x10,0x10,0x38,// "1"
    0x30,0x48,0x08,0x08,0x10,0x20,0x40,0x78,// "2"
    0x30,0x48,0x08,0x30,0x08,0x08,0x48,0x30,// "3"
    0x08,0x18,0x18,0x28,0x28,0x48,0x7C,0x08,// "4"
    0x78,0x40,0x40,0x78,0x04,0x04,0x44,0x38,// "5"
    0x30,0x48,0x40,0x70,0x48,0x48,0x48,0x30,// "6"
    0x78,0x48,0x08,0x10,0x10,0x20,0x20,0x20,// "7"
    0x30,0x48,0x48,0x30,0x48,0x48,0x48,0x30,// "8"
    0x30,0x48,0x48,0x48,0x38,0x08,0x48,0x30,// "9"
    0x00,0x00,0x30,0x30,0x00,0x30,0x30,0x00,// ":"
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x70,0x88,0xB8,0xA8,0xB8,0x80,0x70,0x00,// "@"
    0x30,0x48,0x48,0x48,0x48,0x78,0x48,0x48,// "A"
    0x78,0x44,0x44,0x78,0x44,0x44,0x44,0x78,// "B"
    0x38,0x44,0x40,0x40,0x40,0x40,0x44,0x38,// "C"
    0x78,0x44,0x44,0x44,0x44,0x44,0x44,0x78,// "D"
    0x7C,0x40,0x40,0x78,0x40,0x40,0x40,0x7C,// "E"
    0x7C,0x40,0x40,0x78,0x40,0x40,0x40,0x40,// "F"
    0x38,0x44,0x40,0x40,0x5C,0x44,0x44,0x38,// "G"
    0x44,0x44,0x44,0x7C,0x44,0x44,0x44,0x44,// "H"
    0x38,0x10,0x10,0x10,0x10,0x10,0x10,0x38,// "I"
    0x1C,0x08,0x08,0x08,0x08,0x48,0x48,0x30,// "J"
    0x44,0x48,0x50,0x60,0x50,0x48,0x44,0x44,// "K"
    0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x7C,// "L"
    0x44,0x6C,0x54,0x54,0x54,0x44,0x44,0x44,// "M"
    0x44,0x64,0x64,0x54,0x54,0x4C,0x4C,0x44,// "N"
    0x38,0x44,0x44,0x44,0x44,0x44,0x44,0x38,// "O"
    0x78,0x44,0x44,0x44,0x78,0x40,0x40,0x40,// "P"
    0x38,0x44,0x44,0x44,0x44,0x54,0x48,0x34,// "Q"
    0x78,0x44,0x44,0x44,0x78,0x50,0x48,0x44,// "R"
    0x38,0x44,0x40,0x30,0x08,0x04,0x44,0x38,// "S"
    0x7C,0x10,0x10,0x10,0x10,0x10,0x10,0x10,// "T"
    0x44,0x44,0x44,0x44,0x44,0x44,0x44,0x38,// "U"
    0x44,0x44,0x44,0x28,0x28,0x28,0x10,0x10,// "V"
    0x44,0x44,0x54,0x54,0x54,0x28,0x28,0x28,// "W"
    0x44,0x44,0x28,0x10,0x10,0x28,0x44,0x44,// "X"
    0x44,0x44,0x28,0x28,0x10,0x10,0x10,0x10,// "Y"
    0x7C,0x04,0x08,0x10,0x10,0x20,0x40,0x7C,// "Z"
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x38,0x04,0x3C,0x44,0x3C,// "a"
    0x40,0x40,0x40,0x78,0x44,0x44,0x44,0x78,// "b"
    0x00,0x00,0x00,0x38,0x44,0x40,0x44,0x38,// "c"
    0x04,0x04,0x04,0x3C,0x44,0x44,0x44,0x3C,// "d"
    0x00,0x00,0x00,0x38,0x44,0x7C,0x40,0x38,// "e"
    0x08,0x10,0x10,0x7C,0x10,0x10,0x10,0x10,// "f"
    0x00,0x3C,0x44,0x44,0x44,0x3C,0x04,0x38,// "g"
    0x40,0x40,0x40,0x70,0x48,0x48,0x48,0x48,// "h"
    0x00,0x00,0x10,0x00,0x10,0x10,0x10,0x10,// "i"
    0x00,0x08,0x08,0x08,0x08,0x08,0x08,0x30,// "j"
    0x40,0x40,0x40,0x48,0x50,0x60,0x50,0x48,// "k"
    0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x38,// "l"
    0x00,0x00,0x00,0x68,0x54,0x54,0x54,0x54,// "m"
    0x00,0x00,0x00,0x50,0x68,0x48,0x48,0x48,// "n"
    0x00,0x00,0x00,0x38,0x44,0x44,0x44,0x38,// "o"
    0x00,0x78,0x44,0x44,0x44,0x78,0x40,0x40,// "p"
    0x00,0x3C,0x44,0x44,0x44,0x3C,0x04,0x04,// "q"
    0x00,0x00,0x00,0x58,0x64,0x40,0x40,0x40,// "r"
    0x00,0x00,0x00,0x3C,0x40,0x38,0x04,0x78,// "s"
    0x00,0x10,0x10,0x38,0x10,0x10,0x10,0x08,// "t"
    0x00,0x00,0x00,0x44,0x44,0x44,0x4C,0x34,// "u"
    0x00,0x00,0x00,0x44,0x44,0x28,0x28,0x10,// "v"
    0x00,0x00,0x00,0x44,0x54,0x54,0x28,0x28,// "w"
    0x00,0x00,0x00,0x44,0x28,0x10,0x28,0x44,// "x"
    0x00,0x44,0x44,0x44,0x44,0x3C,0x04,0x38,// "y"
    0x00,0x00,0x00,0x7C,0x08,0x10,0x20,0x7C,// "z"
};

//*******************************************************************
// ����ASCII�ֿ�8��*8��		
//*******************************************************************

uchar ASC_8[]={
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,// " "
    0x30,0x78,0x78,0x30,0x30,0x00,0x30,0x00,// "!"
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x18,0x30,0x60,0x60,0x60,0x30,0x18,0x00,// "("
    0x60,0x30,0x18,0x18,0x18,0x30,0x60,0x00,// ")"
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x20,0x20,0xF8,0x20,0x20,0x00,0x00,0x00,// "+"
    0x00,0x00,0x00,0x00,0x00,0x60,0x60,0xC0,// ","
    0x00,0x00,0x00,0xFC,0x00,0x00,0x00,0x00,// "-"
    0x00,0x00,0x00,0x00,0x00,0x60,0x60,0x00,// "."
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x7C,0xC6,0xCE,0xDE,0xF6,0xE6,0x7C,0x00,// "0"
    0x30,0x70,0x30,0x30,0x30,0x30,0x78,0x00,// "1"
    0x78,0xCC,0x0C,0x38,0x60,0xC0,0xFC,0x00,// "2"
    0x78,0xCC,0x0C,0x38,0x0C,0xCC,0x78,0x00,// "3"
    0x3C,0x6C,0xCC,0xCC,0xFE,0x0C,0x1E,0x00,// "4"
    0xFC,0xC0,0xF8,0x0C,0x0C,0xCC,0x78,0x00,// "5"
    0x38,0x60,0xC0,0xF8,0xCC,0xCC,0x78,0x00,// "6"
    0xFC,0xCC,0x0C,0x18,0x30,0x30,0x30,0x00,// "7"
    0x78,0xCC,0xCC,0x78,0xCC,0xCC,0x78,0x00,// "8"
    0x78,0xCC,0xCC,0x7C,0x0C,0xCC,0x78,0x00,// "9"
    0x00,0x00,0x30,0x30,0x00,0x30,0x30,0x00,// ":"
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x70,0x88,0xB8,0xA8,0xB8,0x80,0x70,0x00,// "@"
    0x30,0x78,0xCC,0xCC,0xFC,0xCC,0xCC,0x00,// "A"
    0xFC,0x66,0x66,0x7C,0x66,0x66,0xFC,0x00,// "B"
    0x3C,0x66,0xC0,0xC0,0xC0,0x66,0x3C,0x00,// "C"
    0xF8,0x6C,0x66,0x66,0x66,0x6C,0xF8,0x00,// "D"
    0xFE,0x66,0x60,0x78,0x60,0x66,0xFE,0x00,// "E"
    0xFE,0x62,0x68,0x78,0x68,0x60,0xF0,0x00,// "F"
    0x3C,0x66,0xC0,0xC0,0xCE,0x66,0x3E,0x00,// "G"
    0xCC,0xCC,0xCC,0xFC,0xCC,0xCC,0xCC,0x00,// "H"
    0x78,0x30,0x30,0x30,0x30,0x30,0x78,0x00,// "I"
    0xFC,0x18,0x18,0x18,0x18,0x98,0xF8,0x00,// "J"
    0xCC,0xD8,0xF0,0xE0,0xF0,0xD8,0xCC,0x00,// "K"
    0xF0,0x60,0x60,0x60,0x62,0x66,0xFE,0x00,// "L"
    0xC6,0xEE,0xFE,0xD6,0xD6,0xC6,0xC6,0x00,// "M"
    0xC6,0xE6,0xF6,0xDE,0xCE,0xC6,0xC6,0x00,// "N"
    0x38,0x6C,0xC6,0xC6,0xC6,0x6C,0x38,0x00,// "O"
    0xFC,0x66,0x66,0x7C,0x60,0x60,0xE0,0x00,// "P"
    0x38,0x6C,0xC6,0xC6,0xD6,0x6C,0x3A,0x00,// "Q"
    0xFC,0x66,0x66,0x7C,0x6C,0x66,0xE6,0x00,// "R"
    0x78,0xCC,0xE0,0x70,0x1C,0xCC,0x78,0x00,// "S"
    0xFC,0xB4,0x30,0x30,0x30,0x30,0x78,0x00,// "T"
    0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,0xFC,0x00,// "U"
    0xC6,0xC6,0xC6,0x6C,0x6C,0x28,0x38,0x00,// "V"
    0xC6,0xC6,0xD6,0xD6,0xFE,0xEE,0xC6,0x00,// "W"
    0xC6,0x6C,0x28,0x38,0x38,0x6C,0xC6,0x00,// "X"
    0xCC,0xCC,0xCC,0x78,0x30,0x30,0x78,0x00,// "Y"
    0xFE,0x86,0x0C,0x18,0x30,0x62,0xFE,0x00,// "Z"
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x70,0x0C,0x7C,0x8C,0x76,0x00,// "a"
    0xC0,0xC0,0xDC,0xE6,0xC6,0xC6,0xFC,0x00,// "b"
    0x00,0x00,0x78,0xCC,0xC0,0xCC,0x78,0x00,// "c"
    0x1C,0x0C,0x0C,0x7C,0xCC,0xCC,0x76,0x00,// "d"
    0x00,0x00,0x78,0xCC,0xFC,0xC0,0x78,0x00,// "e"
    0x38,0x6C,0x60,0xF0,0x60,0x60,0xF0,0x00,// "f"
    0x00,0x00,0x76,0xCC,0xCC,0x7C,0x0C,0xF8,// "g"
    0xE0,0x60,0x6C,0x76,0x66,0x66,0xE6,0x00,// "H"
    0x30,0x00,0x70,0x30,0x30,0x30,0x78,0x00,// "i"
    0x00,0x0C,0x00,0x1C,0x0C,0x0C,0xCC,0x78,// "j"
    0xE0,0x60,0x66,0x6C,0x78,0x6C,0xE6,0x00,// "k"
    0x70,0x30,0x30,0x30,0x30,0x30,0x78,0x00,// "l"
    0x00,0x00,0xC6,0xFE,0xFE,0xD6,0xC6,0x00,// "m"
    0x00,0x00,0xF8,0xCC,0xCC,0xCC,0xCC,0x00,// "n"
    0x00,0x00,0x78,0xCC,0xCC,0xCC,0x78,0x00,// "o"
    0x00,0x00,0xDC,0x66,0x66,0x7C,0x60,0xF0,// "p"
    0x00,0x00,0x7E,0xCC,0xCC,0x7C,0x0C,0x1E,// "q"
    0x00,0x00,0xDC,0x76,0x66,0x60,0xF0,0x00,// "r"
    0x00,0x00,0x7C,0xC0,0x78,0x0C,0xF8,0x00,// "s"
    0x10,0x30,0x7C,0x30,0x30,0x34,0x18,0x00,// "t"
    0x00,0x00,0xCC,0xCC,0xCC,0xCC,0x76,0x00,// "u"
    0x00,0x00,0xCC,0xCC,0xCC,0x78,0x30,0x00,// "v"
    0x00,0x00,0xC6,0xD6,0xFE,0xFE,0x6C,0x00,// "w"
    0x00,0x00,0xC6,0x6C,0x38,0x6C,0xC6,0x00,// "x"
    0x00,0x00,0xCC,0xCC,0xCC,0x7C,0x0C,0xF8,// "y"
    0x00,0x00,0xFC,0x18,0x30,0x60,0xFC,0x00 // "z"
};										   

//*******************************************************************
// ����ASCII�ֿ�8��*16��		
//*******************************************************************

uchar ASC_16[]={
   0x00, 0x00, 0x03, 0x06, 0x0C, 0x0C, 0x0C, 0x0C,
   0x0C, 0x0C, 0x0C, 0x0C, 0x06, 0x03, 0x00, 0x00,
   0x00, 0x00, 0xE0, 0x30, 0x18, 0x18, 0x18, 0x18,
   0x18, 0x18, 0x18, 0x18, 0x30, 0xE0, 0x00, 0x00,//      ;��
   0x00, 0x00, 0x00, 0x03, 0x01, 0x01, 0x01, 0x01,
   0x01, 0x01, 0x01, 0x01, 0x01, 0x03, 0x00, 0x00,
   0x00, 0x00, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
   0x80, 0x80, 0x80, 0x80, 0x80, 0xC0, 0x00, 0x00,//      ;��
   0x00, 0x00, 0x03, 0x06, 0x0C, 0x0C, 0x00, 0x00,
   0x00, 0x00, 0x01, 0x03, 0x06, 0x0F, 0x00, 0x00,
   0x00, 0x00, 0xC0, 0x60, 0x30, 0x30, 0x30, 0x30,
   0x60, 0xC0, 0x80, 0x10, 0x10, 0xF0, 0x00, 0x00,//      ;��
   0x00, 0x00, 0x03, 0x06, 0x0C, 0x00, 0x00, 0x01,
   0x00, 0x00, 0x00, 0x0C, 0x06, 0x03, 0x00, 0x00,
   0x00, 0x00, 0xC0, 0x60, 0x30, 0x30, 0x60, 0xC0,
   0x60, 0x30, 0x30, 0x30, 0x60, 0xC0, 0x00, 0x00,//      ;��
   0x00, 0x00, 0x00, 0x01, 0x03, 0x02, 0x06, 0x0C,
   0x0C, 0x18, 0x1F, 0x00, 0x00, 0x01, 0x00, 0x00,
   0x00, 0x40, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0,
   0xC0, 0xC0, 0xF0, 0xC0, 0xC0, 0xE0, 0x00, 0x00,//      ;��
   0x00, 0x00, 0x0F, 0x0C, 0x0C, 0x0C, 0x0F, 0x0E,
   0x00, 0x00, 0x00, 0x0C, 0x06, 0x03, 0x00, 0x00,
   0x00, 0x00, 0xF0, 0x00, 0x00, 0x00, 0xC0, 0x60,
   0x30, 0x30, 0x30, 0x30, 0x60, 0xC0, 0x00, 0x00,//      ;��
   0x00, 0x00, 0x03, 0x06, 0x0C, 0x0C, 0x0D, 0x0E,
   0x0C, 0x0C, 0x0C, 0x0C, 0x06, 0x03, 0x00, 0x00,
   0x00, 0x00, 0xC0, 0x60, 0x30, 0x00, 0xC0, 0x60,
   0x30, 0x30, 0x30, 0x30, 0x60, 0xC0, 0x00, 0x00,//      ;��
   0x00, 0x00, 0x0F, 0x0F, 0x08, 0x00, 0x00, 0x00,
   0x01, 0x01, 0x03, 0x03, 0x03, 0x03, 0x00, 0x00,
   0x00, 0x00, 0xF0, 0xF0, 0x30, 0x60, 0xC0, 0xC0,
   0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,//      ;��
   0x00, 0x00, 0x03, 0x06, 0x0C, 0x0C, 0x06, 0x03,
   0x06, 0x0C, 0x0C, 0x0C, 0x06, 0x03, 0x00, 0x00,
   0x00, 0x00, 0xC0, 0x60, 0x30, 0x30, 0x60, 0xC0,
   0x60, 0x30, 0x30, 0x30, 0x60, 0xC0, 0x00, 0x00,//      ;��
   0x00, 0x00, 0x03, 0x06, 0x0C, 0x0C, 0x0C, 0x0C,
   0x06, 0x03, 0x00, 0x0C, 0x06, 0x03, 0x00, 0x00,
   0x00, 0x00, 0xC0, 0x60, 0x30, 0x30, 0x30, 0x30,
   0x70, 0xF0, 0x30, 0x30, 0x60, 0xC0, 0x00, 0x00,//      ;��
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x0F,
   0x0F, 0x06, 0x00, 0x06, 0x0F, 0x0F, 0x06, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,//      ;��
   0x00, 0x00, 0x00, 0x00, 0x00, 0x0C, 0x1E, 0x1E,
   0x0C, 0x00, 0x0C, 0x1E, 0x1E, 0x0C, 0x0C, 0x18,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,//      ;��
   0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x04,
   0x08, 0x04, 0x02, 0x01, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x40, 0x80, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x80, 0x40, 0x00, 0x00,//      ;��
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1F, 0x00,
   0x00, 0x1F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF8, 0x00,
   0x00, 0xF8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,//      ;��
   0x00, 0x00, 0x02, 0x01, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x01, 0x02, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x80, 0x40, 0x20, 0x10,
   0x20, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00,//      ;��
   0x00, 0x00, 0x07, 0x18, 0x30, 0x38, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x01, 0x03, 0x01, 0x00,
   0x00, 0x00, 0xF0, 0x18, 0x0C, 0x0C, 0x38, 0xE0,
   0xC0, 0x80, 0x00, 0x00, 0x80, 0xC0, 0x80, 0x00,//      ;��
   0x00, 0x00, 0x03, 0x04, 0x08, 0x11, 0x12, 0x12,
   0x12, 0x12, 0x11, 0x08, 0x04, 0x03, 0x00, 0x00,
   0x00, 0x00, 0xE0, 0x10, 0x08, 0xC4, 0x24, 0x24,
   0x24, 0x34, 0xCC, 0x00, 0x08, 0xF0, 0x00, 0x00,//      ;��
   0x00, 0x00, 0x00, 0x01, 0x01, 0x02, 0x02, 0x04,
   0x04, 0x07, 0x0C, 0x08, 0x08, 0x1C, 0x00, 0x00,
   0x00, 0x00, 0x80, 0xC0, 0x40, 0x60, 0x60, 0x30,
   0x30, 0xF0, 0x38, 0x18, 0x18, 0x3C, 0x00, 0x00,//      ;��
   0x00, 0x00, 0x1F, 0x0C, 0x0C, 0x0C, 0x0C, 0x0F,
   0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x1F, 0x00, 0x00,
   0x00, 0x00, 0xE0, 0x38, 0x18, 0x18, 0x30, 0xF0,
   0x18, 0x0C, 0x0C, 0x0C, 0x38, 0xE0, 0x00, 0x00,//      ;��
   0x00, 0x00, 0x03, 0x06, 0x0C, 0x18, 0x18, 0x18,
   0x18, 0x18, 0x18, 0x0C, 0x06, 0x03, 0x00, 0x00,
   0x00, 0x00, 0xE0, 0x38, 0x18, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x08, 0x30, 0xE0, 0x00, 0x00,//      ;��
   0x00, 0x00, 0x1F, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C,
   0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x1F, 0x00, 0x00,
   0x00, 0x00, 0xC0, 0x70, 0x18, 0x0C, 0x0C, 0x0C,
   0x0C, 0x0C, 0x0C, 0x18, 0x70, 0xC0, 0x00, 0x00,//      ;��
   0x00, 0x00, 0x1F, 0x0C, 0x0C, 0x0C, 0x0C, 0x0F,
   0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x1F, 0x00, 0x00,
   0x00, 0x00, 0xF8, 0x18, 0x08, 0x00, 0x20, 0xE0,
   0x20, 0x00, 0x00, 0x08, 0x18, 0xF8, 0x00, 0x00,//      ;��
   0x00, 0x00, 0x1F, 0x0C, 0x0C, 0x0C, 0x0C, 0x0F,
   0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x1E, 0x00, 0x00,
   0x00, 0x00, 0xF8, 0x18, 0x08, 0x00, 0x20, 0xE0,
   0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,//      ;��
   0x00, 0x00, 0x03, 0x06, 0x0C, 0x18, 0x18, 0x18,
   0x18, 0x18, 0x18, 0x0C, 0x06, 0x03, 0x00, 0x00,
   0x00, 0x00, 0xF0, 0x1C, 0x0C, 0x04, 0x00, 0x00,
   0x00, 0x3C, 0x18, 0x18, 0x18, 0xF0, 0x00, 0x00,//      ;��
   0x00, 0x00, 0x1E, 0x0C, 0x0C, 0x0C, 0x0C, 0x0F,
   0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x1E, 0x00, 0x00,
   0x00, 0x00, 0x3C, 0x18, 0x18, 0x18, 0x18, 0xF8,
   0x18, 0x18, 0x18, 0x18, 0x18, 0x3C, 0x00, 0x00,//      ;��
   0x00, 0x00, 0x03, 0x01, 0x01, 0x01, 0x01, 0x01,
   0x01, 0x01, 0x01, 0x01, 0x01, 0x03, 0x00, 0x00,
   0x00, 0x00, 0xC0, 0x80, 0x80, 0x80, 0x80, 0x80,
   0x80, 0x80, 0x80, 0x80, 0x80, 0xC0, 0x00, 0x00,//      ;��
   0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x38, 0x18, 0x0F, 0x00, 0x00,
   0x00, 0x00, 0xE0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0,
   0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0x80, 0x00, 0x00,//      ;��
   0x00, 0x00, 0x1E, 0x0C, 0x0C, 0x0C, 0x0D, 0x0F,
   0x0C, 0x0C, 0x0C, 0x0C, 0x1E, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x7C, 0x30, 0x60, 0xC0, 0x80, 0x80,
   0xE0, 0x70, 0x38, 0x1C, 0x1E, 0x00, 0x00, 0x00,//      ;��
   0x00, 0x00, 0x1E, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C,
   0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x1F, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x08, 0x18, 0xF8, 0x00, 0x00,//      ;��
   0x00, 0x00, 0x38, 0x18, 0x1C, 0x16, 0x16, 0x13,
   0x13, 0x11, 0x11, 0x10, 0x10, 0x38, 0x00, 0x00,
   0x00, 0x00, 0x0E, 0x0C, 0x1C, 0x2C, 0x2C, 0x6C,
   0x4C, 0x4C, 0xCC, 0x8C, 0x8C, 0x1E, 0x00, 0x00,//      ;��
   0x00, 0x00, 0x1C, 0x0E, 0x0B, 0x0B, 0x09, 0x09,
   0x08, 0x08, 0x08, 0x08, 0x08, 0x1C, 0x00, 0x00,
   0x00, 0x00, 0x38, 0x10, 0x10, 0x10, 0x90, 0x90,
   0xD0, 0xD0, 0x70, 0x70, 0x30, 0x10, 0x00, 0x00,//      ;��
   0x00, 0x00, 0x03, 0x06, 0x0C, 0x18, 0x18, 0x18,
   0x18, 0x18, 0x18, 0x0C, 0x06, 0x03, 0x00, 0x00,
   0x00, 0x00, 0xE0, 0x30, 0x18, 0x0C, 0x0C, 0x0C,
   0x0C, 0x0C, 0x0C, 0x18, 0x30, 0xE0, 0x00, 0x00,//      ;��
   0x00, 0x00, 0x1F, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C,
   0x0F, 0x0C, 0x0C, 0x0C, 0x0C, 0x1E, 0x00, 0x00,
   0x00, 0x00, 0xE0, 0x30, 0x18, 0x18, 0x18, 0x30,
   0xE0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,//      ;��
   0x00, 0x00, 0x03, 0x0E, 0x18, 0x18, 0x18, 0x18,
   0x18, 0x18, 0x0D, 0x06, 0x03, 0x00, 0x00, 0x00,
   0x00, 0x00, 0xE0, 0x38, 0x0C, 0x0C, 0x0C, 0x0C,
   0x0C, 0x8C, 0x4C, 0x58, 0xF0, 0x40, 0x48, 0x30,//      ;��
   0x00, 0x00, 0x1F, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C,
   0x0F, 0x0C, 0x0C, 0x0C, 0x0C, 0x1E, 0x00, 0x00,
   0x00, 0x00, 0xE0, 0x30, 0x18, 0x18, 0x18, 0x30,
   0xE0, 0xC0, 0x70, 0x30, 0x38, 0x1C, 0x00, 0x00,//      ;��
   0x00, 0x00, 0x07, 0x0C, 0x18, 0x18, 0x0E, 0x03,
   0x00, 0x00, 0x00, 0x10, 0x1C, 0x17, 0x00, 0x00,
   0x00, 0x00, 0xE8, 0x18, 0x08, 0x00, 0x00, 0xE0,
   0x30, 0x18, 0x18, 0x18, 0x30, 0xC0, 0x00, 0x00,//      ;��
   0x00, 0x00, 0x3F, 0x31, 0x21, 0x21, 0x01, 0x01,
   0x01, 0x01, 0x01, 0x01, 0x01, 0x03, 0x00, 0x00,
   0x00, 0x00, 0xFC, 0x8C, 0x84, 0x84, 0x80, 0x80,
   0x80, 0x80, 0x80, 0x80, 0x80, 0xC0, 0x00, 0x00,//      ;��
   0x00, 0x00, 0x1E, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C,
   0x0C, 0x0C, 0x0C, 0x0C, 0x06, 0x03, 0x00, 0x00,
   0x00, 0x00, 0x1C, 0x08, 0x08, 0x08, 0x08, 0x08,
   0x08, 0x08, 0x08, 0x18, 0x30, 0xE0, 0x00, 0x00,//      ;��
   0x00, 0x00, 0x3C, 0x18, 0x18, 0x18, 0x0C, 0x0C,
   0x0C, 0x06, 0x06, 0x02, 0x03, 0x01, 0x00, 0x00,
   0x00, 0x00, 0x1C, 0x08, 0x08, 0x10, 0x10, 0x20,
   0x20, 0x40, 0x40, 0x80, 0x80, 0x00, 0x00, 0x00,//      ;��
   0x00, 0x00, 0x3D, 0x18, 0x18, 0x18, 0x0C, 0x0C,
   0x0D, 0x0D, 0x0D, 0x06, 0x06, 0x06, 0x00, 0x00,
   0x00, 0x00, 0xEE, 0xC4, 0xC4, 0xC4, 0xC4, 0xC8,
   0x68, 0x68, 0x68, 0x28, 0x30, 0x10, 0x00, 0x00,//      ;��
   0x00, 0x00, 0x1E, 0x0C, 0x06, 0x07, 0x03, 0x01,
   0x01, 0x03, 0x06, 0x04, 0x08, 0x1C, 0x00, 0x00,
   0x00, 0x00, 0x1C, 0x08, 0x18, 0x30, 0x60, 0xC0,
   0xC0, 0x60, 0x60, 0x30, 0x18, 0x3C, 0x00, 0x00,//      ;��
   0x00, 0x00, 0x7C, 0x38, 0x1C, 0x0E, 0x07, 0x03,
   0x01, 0x01, 0x01, 0x01, 0x01, 0x03, 0x00, 0x00,
   0x00, 0x00, 0x1E, 0x0C, 0x18, 0x30, 0x60, 0xC0,
   0x80, 0x80, 0x80, 0x80, 0x80, 0xC0, 0x00, 0x00,//      ;��
   0x00, 0x00, 0x3F, 0x20, 0x00, 0x00, 0x00, 0x01,
   0x03, 0x06, 0x0C, 0x18, 0x30, 0x3F, 0x00, 0x00,
   0x00, 0x00, 0xF8, 0x18, 0x30, 0x60, 0xC0, 0x80,
   0x00, 0x00, 0x00, 0x08, 0x18, 0xF8, 0x00, 0x00,//      ;��
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x0C,
   0x00, 0x07, 0x0C, 0x0C, 0x07, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, 0x60,
   0x60, 0xE0, 0x60, 0x60, 0xD8, 0x00, 0x00, 0x00,//      ;��
   0x00, 0x00, 0x0E, 0x06, 0x06, 0x06, 0x07, 0x06,
   0x06, 0x06, 0x06, 0x06, 0x0B, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xE0, 0x18,
   0x18, 0x18, 0x18, 0x18, 0xF0, 0x00, 0x00, 0x00,//      ;��
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x0C,
   0x0C, 0x0C, 0x0C, 0x0C, 0x07, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xE0, 0x30,
   0x00, 0x00, 0x00, 0x30, 0xE0, 0x00, 0x00, 0x00,//      ;��
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x0C,
   0x0C, 0x0C, 0x0C, 0x0C, 0x07, 0x00, 0x00, 0x00,
   0x00, 0x00, 0xE0, 0x60, 0x60, 0x60, 0xE0, 0x60,
   0x60, 0x60, 0x60, 0x60, 0xD0, 0x00, 0x00, 0x00,//      ;��
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x0C,
   0x0C, 0x0F, 0x0C, 0x0C, 0x07, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xE0, 0x30,
   0x30, 0xF0, 0x00, 0x30, 0xE0, 0x00, 0x00, 0x00,//      ;��
   0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x07, 0x01,
   0x01, 0x01, 0x01, 0x01, 0x03, 0x00, 0x00, 0x00,
   0x00, 0x00, 0xF0, 0x98, 0x80, 0x80, 0xE0, 0x80,
   0x80, 0x80, 0x80, 0x80, 0xC0, 0x00, 0x00, 0x00,//      ;��
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x0C,
   0x0C, 0x07, 0x0C, 0x0F, 0x1C, 0x18, 0x0C, 0x07,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF0, 0xC0,
   0xC0, 0x80, 0x00, 0x80, 0xE0, 0x60, 0xC0, 0x80,//      ;��
   0x00, 0x00, 0x0E, 0x06, 0x06, 0x06, 0x06, 0x07,
   0x06, 0x06, 0x06, 0x06, 0x0E, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xE0, 0x30,
   0x30, 0x30, 0x30, 0x30, 0x78, 0x00, 0x00, 0x00,//      ;��
   0x00, 0x00, 0x00, 0x01, 0x01, 0x00, 0x03, 0x01,
   0x01, 0x01, 0x01, 0x01, 0x03, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x80, 0x80, 0x00, 0x80, 0x80,
   0x80, 0x80, 0x80, 0x80, 0xC0, 0x00, 0x00, 0x00,//      ;��
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x0C, 0x0C, 0x07, 0x00,
   0x00, 0x00, 0x00, 0xC0, 0xC0, 0x00, 0xC0, 0xC0,
   0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0x80, 0x00,//      ;��
   0x00, 0x00, 0x0E, 0x06, 0x06, 0x06, 0x06, 0x06,
   0x06, 0x07, 0x07, 0x06, 0x0E, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x78, 0x30,
   0x60, 0xC0, 0x60, 0x30, 0x3C, 0x00, 0x00, 0x00,//      ;��
   0x00, 0x00, 0x03, 0x01, 0x01, 0x01, 0x01, 0x01,
   0x01, 0x01, 0x01, 0x01, 0x03, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
   0x80, 0x80, 0x80, 0x80, 0xC0, 0x00, 0x00, 0x00,//      ;��
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x6F, 0x18,
   0x18, 0x18, 0x18, 0x18, 0x3D, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7C, 0xC6,
   0xC6, 0xC6, 0xC6, 0xC6, 0xEF, 0x00, 0x00, 0x00,//      ;��
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x37, 0x0C,
   0x0C, 0x0C, 0x0C, 0x0C, 0x1E, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xE0, 0x30,
   0x30, 0x30, 0x30, 0x30, 0x78, 0x00, 0x00, 0x00,//      ;��
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x06,
   0x06, 0x06, 0x06, 0x06, 0x03, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xE0, 0x30,
   0x30, 0x30, 0x30, 0x30, 0xE0, 0x00, 0x00, 0x00,//      ;��
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x19, 0x06,
   0x06, 0x06, 0x06, 0x06, 0x07, 0x06, 0x06, 0x0F,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF0, 0x18,
   0x18, 0x18, 0x18, 0x18, 0xE0, 0x00, 0x00, 0x00,//      ;��
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x06,
   0x06, 0x06, 0x06, 0x03, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xE8, 0x30,
   0x30, 0x30, 0x30, 0xF0, 0x30, 0x30, 0x30, 0x78,//      ;��
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0D, 0x06,
   0x06, 0x06, 0x06, 0x06, 0x0F, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF0, 0x18,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,//      ;��
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x06,
   0x03, 0x01, 0x00, 0x06, 0x03, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xE0, 0x30,
   0x00, 0xE0, 0x30, 0x30, 0xE0, 0x00, 0x00, 0x00,//      ;��
   0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x07, 0x01,
   0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x80, 0x80, 0x80, 0xE0, 0x80,
   0x80, 0x80, 0x90, 0x90, 0xE0, 0x00, 0x00, 0x00,//      ;��
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1C, 0x0C,
   0x0C, 0x0C, 0x0C, 0x0C, 0x07, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x70, 0x30,
   0x30, 0x30, 0x30, 0x70, 0xD8, 0x00, 0x00, 0x00,//      ;��
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3C, 0x18,
   0x0C, 0x06, 0x03, 0x01, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1C, 0x08,
   0x10, 0x20, 0x40, 0xC0, 0x80, 0x00, 0x00, 0x00,//      ;��
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3D, 0x18,
   0x08, 0x0D, 0x05, 0x06, 0x02, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xEE, 0xC4,
   0xCC, 0x68, 0x28, 0x30, 0x10, 0x00, 0x00, 0x00,//      ;��
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3C, 0x0C,
   0x03, 0x01, 0x03, 0x0C, 0x3E, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3C, 0x30,
   0x60, 0xC0, 0x60, 0x30, 0x7C, 0x00, 0x00, 0x00,//      ;��
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1F, 0x0E,
   0x06, 0x03, 0x03, 0x01, 0x01, 0x02, 0x04, 0x18,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1C, 0x08,
   0x10, 0x20, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00,//      ;��
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x04,
   0x00, 0x01, 0x03, 0x06, 0x07, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF0, 0x30,
   0x60, 0x80, 0x00, 0x10, 0xF0, 0x00, 0x00, 0x00,//      ;��
}; 

