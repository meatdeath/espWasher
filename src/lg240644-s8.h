#ifndef __LG240644_S8_H__
#define __LG240644_S8_H__

#include "types.h"

void setcursor(uchar x,uchar y);
void clr_screen(void);						// ����
void byte_extend(uchar dat);
void byte_extend_6(uchar dat);
void byte_extend_ch(uchar dat);				
void byte_extend_hz(uchar dat);				
void one_word(uchar x,uchar y,uchar *Lib,uchar ch_num,uchar widthw);
void dis_word(uchar x,uchar y,uchar *str,uchar ch8_16);
void lcd_init(void);
void lcd_main(void);
// void dis_square(void);
// void dis_small_pic(void);
// void lcd_init2(void);

#endif //__LG240644_S8_H__