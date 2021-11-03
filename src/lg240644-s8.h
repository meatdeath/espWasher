#ifndef __LG240644_S8_H__
#define __LG240644_S8_H__

#include "types.h"

#define LCD_CMD_SET_COLUMN_ADDR_LSB                     0b00000000  // 0x00
#define LCD_CMD_SET_COLUMN_ADDR_MSB                     0b00010000  // 0x10
#define LCD_CMD_SET_TEMP_COMPENSATION                   0b00100100  // 0x24
#define LCD_CMD_SET_POWER_CONTROL                       0b00101000  // 0x28
#define LCD_CMD_SET_ADV_PROG_CONTROL                    0b00110000  // 0x30
#define LCD_CMD_SET_SCROLL_LINE_LSB                     0b01000000  // 0x40
#define LCD_CMD_SET_SCROLL_LINE_MSB                     0b01010000  // 0x50
#define LCD_CMD_SET_ROW_ADDR_LSB                        0b01100000  // 0x60
#define LCD_CMD_SET_ROW_ADDR_MSB                        0b01110000  // 0x70
#define LCD_CMD_SET_VBIAS_POTENTIOMETER                 0b10000001  // 0x81
#define LCD_CMD_SET_PART_DISPLAY_CTRL                   0b10000100  // 0x84
#define LCD_CMD_SET_RAM_CONTROL                         0b10001000  // 0x88
#define LCD_CMD_SET_FIXED_LINES                         0b10010000  // 0x90
#define LCD_CMD_SET_LINE_RATE                           0b10100000  // 0xa0
#define LCD_CMD_SET_ALL_PIXEL_ON                        0b10100100  // 0xa4
#define LCD_CMD_SET_INVERS_DISPLAY                      0b10100110  // 0xa6
#define LCD_CMD_SET_DISPLAY_ENABLE                      0b10101000  // 0xa8
#define LCD_CMD_SET_LCD_MAPPING_CONTROL                 0b11000000  // 0xc0
#define LCD_CMD_SET_N_LINE_INVERSION                    0b11001000  // 0xc8
#define LCD_CMD_SET_COLOR_PATTERN                       0b11010000  // 0xd0
#define LCD_CMD_SET_COLOR_MODE                          0b11010100  // 0xd4
#define LCD_CMD_SET_COM_SCAN_FUNCTION                   0b11011000  // 0xd6
#define LCD_CMD_SYSTEM_RESET                            0b11100010  // 0xe2
#define LCD_CMD_NOP                                     0b11100011  // 0xe3
#define LCD_CMD_SET_TEST_CONTROL                        0b11100100  // 0xe4
#define LCD_CMD_SET_LCD_BIAS_RATIO                      0b11101000  // 0xe8
#define LCD_CMD_SET_COM_END                             0b11110001  // 0xf1
#define LCD_CMD_SET_PART_DISPLAY_START                  0b11110010  // 0xf2
#define LCD_CMD_SET_PART_DISPLAY_END                    0b11110011  // 0xf3
#define LCD_CMD_SET_WINDOW_PROGRAM_STARTING_COLUMN_ADDR 0b11110100  // 0xf4
#define LCD_CMD_SET_WINDOW_PROGRAM_STARTING_ROW_ADDR    0b11110101  // 0xf5
#define LCD_CMD_SET_WINDOW_PROGRAM_ENDING_COLUMN_ADDR   0b11110110  // 0xf6
#define LCD_CMD_SET_WINDOW_PROGRAM_ENDING_ROW_ADDR      0b11110111  // 0xf7
#define LCD_CMD_SET_WINDOW_PROGRAM_MODE                 0b11111000  // 0xf8
#define LCD_CMD_SET_MTP_OPERATION_CONTROL               0b10111000  // 0xb8
#define LCD_CMD_SET_MTP_WRITE_MASK                      0b10111001  // 0xb9
#define LCD_CMD_SET_V_MTP1_POTENTIOMETER                0b11110100  // 0xf4
#define LCD_CMD_SET_V_MTP2_POTENTIOMETER                0b11110101  // 0xf5
#define LCD_CMD_SET_MTP_WRITE_TIMER                     0b11110110  // 0xf6
#define LCD_CMD_SET_MTP_READ_TIMER                      0b11110111  // 0xf7


void lcd_setcursor(uchar x,uchar y);
void lcd_clr_screen(void);						// ����
void lcd_byte_extend(uchar dat);
void lcd_byte_extend_6(uchar dat);
void lcd_byte_extend_ch(uchar dat);				
void lcd_byte_extend_hz(uchar dat);				
void lcd_one_word(uchar x,uchar y,uchar *Lib,uchar ch_num,uchar widthw);
void lcd_dis_word(uchar x,uchar y,uchar *str,uchar ch8_16);
void lcd_init(void);
void lcd_main(void);

#endif //__LG240644_S8_H__