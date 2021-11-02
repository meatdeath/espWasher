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
void wr_ctrl(uchar ctrlcode);				// дָ��
void wr_data(uchar disdata);				// д����
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

#endif //__LG24064_8080_H__