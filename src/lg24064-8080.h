#ifndef __LG24064_8080_H__
#define __LG24064_8080_H__

//*******************************************************************/

#define	uchar unsigned char	
#define uint unsigned int

//*************** �˿ڵ�ַ���� **************************************

//#define LCD_BUS 	P0	//DB0-DB7->P0, P0����I/O��ʱ��Ҫ��10Kŷ����������
#define LCD_D0 23
#define LCD_D1 22
#define LCD_D2 21
#define LCD_D3 19
#define LCD_D4 18
#define LCD_D5 5
#define LCD_D6 17
#define LCD_D7 16

#define LCD_CD  25    //P1_0					//CD ->P1.0
#define LCD_WR  14    //P1_1					//WR ->P1.1
#define LCD_RD  12    //P1_2					//RD ->P1.2
#define LCD_CS  26    //P1_3					//CS ->P1.3
//#define LCD_RST     //P1_6					//RST->P1.6

//*****************�����б�******************************************

#define delay_ms delay

//void delay_ms(uint);						// ��ʱ 1 ms
void wr_ctrl(uint8_t ctrlcode);				// дָ��
void wr_data(uint8_t disdata);				// д����
void setcursor(uint8_t x,uint8_t y);
void clr_screen(void);						// ����
void byte_extend(uint8_t dat);
void byte_extend_6(uint8_t dat);
void byte_extend_ch(uint8_t dat);				
void byte_extend_hz(uint8_t dat);				
void one_word(uint8_t x,uint8_t y,uint8_t *Lib,uint8_t ch_num,uint8_t widthw);
void dis_word(uint8_t x,uint8_t y,uint8_t *str,uint8_t ch8_16);
void lcd_init(void);
void lcd_main(void);

#endif //__LG24064_8080_H__