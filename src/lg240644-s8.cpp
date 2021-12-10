//*******************************************************************/
// Эта программа представляет собой пример программы для 
// точечно-матричного графического ЖК-модуля.
// Модель контроллера LCD: UC1698 или другой совместимый контроллер
// MCU привода: AT89C52
//*******************************************************************/

#include <Arduino.h>
#include "lg240644-s8.h"
#include "types.h"

//*************** �˿ڵ�ַ���� **************************************

#define LCD_CD      25
#define LCD_CS      33
#define LCD_SCL     27
#define LCD_SDA     26

#define LCD_SET_CD(level)   digitalWrite(LCD_CD,level)
#define LCD_SET_SDA(level)  digitalWrite(LCD_SDA,level)
#define LCD_SET_SCL(level)  digitalWrite(LCD_SCL,level)
#define LCD_SET_CS(level)   digitalWrite(LCD_CS,level)

//*****************�����б�******************************************

#define delay_ms delay

void lcd_wr_ctrl(uint8_t ctrlcode);
void lcd_wr_data(uint8_t disdata);
void lcd_setcursor(uint8_t x, uint8_t y);
void lcd_clr_screen(void);
void lcd_byte_extend(uint8_t dat);
void lcd_byte_extend_6(uint8_t dat);
void lcd_byte_extend_ch(uint8_t dat);				
void lcd_byte_extend_hz(uint8_t dat);				
void lcd_one_word(uint8_t x, uint8_t y, uint8_t *Lib, uint8_t ch_num, uint8_t widthw);
void lcd_dis_word(uint8_t x, uint8_t y, uint8_t *str, uint8_t ch8_16);
void lcd_init(void);

//******************�����б�*****************************************

//*******************************************************************
//�����ַ�������		
//*******************************************************************

uchar STR1[]        = {0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x00};
uchar STR2[]        = {0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8a,0x8b,0x8c,0x00};
uchar STR_24064_3[] = "LAUREL CO., LTD.";			
uchar STR_24064_4[] = "  240X64  DOTS  ";
uchar STR_24064_5[] = " GRAPHIC MODULE ";
uchar STR_24064_6[] = "AAAAAAAA";
uchar STR_24064_7[] =
					"ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789-:!@"
          			"abcdefghijklmnopqrstuvwxyz0123456789(),."
          			"0123456789-:!@ABCDEFGHIJKLMNOPQRSTUVWXYZ"
          			"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmn"
                    "opqrstuvwxyz0123456789(),.-:!ABCDEFGHIJK"
                    "LMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxy"
                    "z0123456789(),.-:!ABCDEFGHIJKLMNOPQRSTUV";



//*******************************************************************
// �����ֿ����
//******************************************************************* 

uint dis_col, dis_line;
bool ch_68;


//*******************************************************************
// Send bits
//*******************************************************************

void lcd_SendBit(uint8_t dat, uint8_t bitcnt)
{
    uint8_t i;
    for( i = 0; i < bitcnt; i++ )
    {
        LCD_SET_SCL(LOW); 
        if( (dat&0x80) == 0 )
            LCD_SET_SDA(LOW);
        else
            LCD_SET_SDA(HIGH); 
        LCD_SET_SCL(HIGH); 
        dat = dat<<1;  
    }
}

//*******************************************************************
//д Write lcd control word
//*******************************************************************

void lcd_wr_ctrl(uint8_t ctrlcode) 
{
    LCD_SET_CS(LOW);
    LCD_SET_CD(LOW);
    lcd_SendBit(ctrlcode,8);
    LCD_SET_CD(HIGH);
    LCD_SET_CS(HIGH);
}

//*******************************************************************
// Write lcd data word
//******************************************************************* 

void lcd_wr_data(uint8_t dispdata) 
{
    LCD_SET_CS(LOW);
    LCD_SET_CD(HIGH);
    lcd_SendBit(dispdata,8);
    LCD_SET_CD(LOW);
    LCD_SET_CS(HIGH);
}

//*******************************************************************
// set cursor address
//*******************************************************************

void lcd_setcursor(uint8_t x, uint8_t y)
{  	
	lcd_wr_ctrl( LCD_CMD_SET_ROW_ADDR_LSB | (x&0xF) );	// lcd_wr_ctrl((x&0x0F)|0x60);	        // row address LSB
	lcd_wr_ctrl( LCD_CMD_SET_ROW_ADDR_MSB | (x>>4) );	// lcd_wr_ctrl((x>>4)|0x70);		        // row address MSB 
	
	lcd_wr_ctrl( LCD_CMD_SET_COLUMN_ADDR_MSB | (y>>4) );	// lcd_wr_ctrl(|0x10);				// column address MSB
	lcd_wr_ctrl( LCD_CMD_SET_COLUMN_ADDR_LSB | (y&0xF) );	// lcd_wr_ctrl(|0x00);			// column address LSB
}

//*******************************************************************
// Clear LCD screen		
//*******************************************************************

void lcd_clr_screen(void)
{
    uint16_t x, y;						
                    
    for( x = 0; x < dis_line; x++ )			// write dis_line row
    {
        lcd_setcursor( x, 0 );				// set cursor
        for( y = 0; y < dis_col/2; y++ ) 	// write dis_col/2 column 
        {
            lcd_wr_data(0x00);			// write display data 0x00
            lcd_wr_data(0x00);
            lcd_wr_data(0x00);				
        }
    }
}

//*******************************************************************
// Draw square
//*******************************************************************

void lcd_dis_square(void)
{
	uint16_t  x,y;

	lcd_clr_screen();
	lcd_setcursor( 0, 0 );					// set cursor
	for( y = 0; y < dis_col/2; y++ ) 		// write dis_col/2 column
	{
		lcd_wr_data(0xff);				// write display data 
		lcd_wr_data(0xff);
		lcd_wr_data(0xff);				
	}				
	for( x = 1; x < dis_line-1; x++ )		// write dis_line-2 row
	{
		lcd_setcursor( x, 0 );				// set cursor
		lcd_wr_data(0xf0);				// write display data 
		lcd_wr_data(0x00);				
		lcd_wr_data(0x00);
		for( y = 1; y < dis_col/2-1; y++ ) 	// write dis_col/2-2 column 
		{
			lcd_wr_data(0x00);			// write display data
			lcd_wr_data(0x00);
			lcd_wr_data(0x00);				
		}					
		lcd_wr_data(0x00);
		lcd_wr_data(0x00);				// write display data 
		lcd_wr_data(0x0f);	
	}
	lcd_setcursor( dis_line-1, 0 );		// set cursor
	for( y = 0; y < dis_col/2; y++ ) 		// write dis_col/2 column 
	{
		lcd_wr_data(0xff);				// write display data 
		lcd_wr_data(0xff);
		lcd_wr_data(0xff);				
	}
}
    
//*******************************************************************/
// byte extend 64k color mode			
//*******************************************************************

void lcd_byte_extend_ch(uint8_t dat)			
{
	uint8_t i, j, dat1, dat2;
	for( i = 0; i < 8; )					// extend D7--->D0 bit data
	{
		dat1 = 0;
		dat2 = 0;
		for( j = 0; j < 3; )				// 3 dot data extend to 2 8bit data
		{
			if( (dat&0x80>>i) > 0 )		// first extend D7(i=0)
				dat1 = 0xF8;				// "D7"=1; dat1=0xF8
			else 
				dat1=0x00;			// "D7"=0; dat1=0x00
			j++;
			i++;				// circle variable add 1
			if( (dat&0x80>>i) > 0 )		// second extend D6(i=1)
			{
				dat1 = dat1|0x07;		// "D6"=1; dat1=dat1|0x07
				dat2 = 0xE0;			// dat2=0xE0
			}				
			else 
			{
				dat1 = dat1|0x00;	// "D6"=0; dat1=dat1|0x00
				dat2 = 0x00;
			}
			j++;
			i++;				// circle variable add 1
			if( (dat&0x80>>i) > 0 )		// second extend D6(i=1)
				dat2 = dat2|0x1F;			// "D6"=1; dat1=dat1|0x1F
			else 
				dat2 = dat2|0x00;	// "D6"=0; dat1=dat1|0x00
			lcd_wr_data(dat1);			// write extend data
			lcd_wr_data(dat2);			// write extend data
			j++;
			i++;				// circle variable add 1
		}
	}
}

//*******************************************************************
// byte extend 4k color mode 6*8ch			
//*******************************************************************

void lcd_byte_extend_6(uint8_t dat)			
{
	uint8_t i, dat1;
	for( i = 0; i < 3; i++ )			// extend D7--->D0 bit data
	{
		dat1 = 0x00;
		if(dat&0x80)		    // first extend D7(i=0)
			dat1 = dat1|0xF0;			
		else 
			dat1 = dat1|0x00;	
		dat <<= 1;
		if( dat&0x80 )		    // second extend D6(i=1)
			dat1 = dat1|0x0f;			
		else 
			dat1 = dat1|0x00;	
		lcd_wr_data(dat1);			// write extend data
		dat<<=1;				
	}
}
    
//*******************************************************************
// byte extend 4k color mode 		
//*******************************************************************

void lcd_byte_extend(uint8_t dat)			
{
	uint8_t i, dat1;
	for( i = 0; i < 4; i++ )			// extend D7--->D0 bit data
	{
		dat1 = 0x00;
		if( dat&0x80 )		    // first extend D7(i=0)
			dat1 = dat1|0xF0;			
		else 
			dat1 = dat1|0x00;	
		dat <<= 1;
		if( dat&0x80 )		    // second extend D6(i=1)
			dat1 = dat1|0x0f;			
		else 
			dat1 = dat1|0x00;	
		lcd_wr_data(dat1);			// write extend data
		dat <<= 1;				
	}
}

//*******************************************************************
// display "A"			
//*******************************************************************

void lcd_byte_extend_gr(uint8_t dat)			
{
	uint8_t i, j, k, dat1, dat2;
	
	for( k = 0; k < 32; )						//write 30 8bit data
	{
		dat2 = dat;						
		for( i = 0; i < 8; )					// extend D7--->D0 bit data
		{
			for( j = 0; j < 2; )				// 2 dot data extend to one 8bit data
			{
				if( (dat2&0x80>>i) > 0 )	// first extend D7(i=0)
					dat1 = 0xF0;				// "D7"=1; dat1=0xF0
				else 
					dat1 = 0x00;			// "D7"=0; dat1=0x00
				j++;
				i++;				// circle variable add 1
				if( (dat2&0x80>>i) > 0 )	// second extend D6(i=1)
					dat1 = dat1|0x0F;			// "D6"=1; dat1=dat1|0x0F
				else 
					dat1 = dat1|0x00;	// "D6"=0; dat1=dat1|0x00
				lcd_wr_data(dat1);			// write extend data
				j++;
				i++;				// circle variable add 1
			}
		}
		k++;
	}
}

//*******************************************************************
//   �ַ��������������			
//*******************************************************************

void lcd_one_word( uint8_t x, uint8_t y, uint8_t *Lib, uint8_t ch_num, uint8_t widthw )
	{
		uint8_t i, j, ch_x, ch_y, row, col;
		int xi;
		
		row = x;
		col = y;
		xi = ch_num * widthw;	
		if ( widthw == 32 )					    
		{
			ch_x = 16;
			ch_y = 2;
		}
		else if ( widthw == 24 )					    
		{
			ch_x = 12;
			ch_y = 2;
		}
        else {
			ch_x = widthw; 
			ch_y = 1;
		}
		for( i = 0; i < ch_x; i++ )
		{
			lcd_setcursor( row, col );
			for( j = 0; j < ch_y; j++ )
			{   
				if( ch_y == 1 )
				{
                    if( ch_68 == 0 ) 
						lcd_byte_extend_6(Lib[xi]);
                    else
                    {
                        lcd_wr_ctrl(0xd6);
                        lcd_byte_extend_ch(Lib[xi]);
                       	lcd_wr_ctrl(0xd5);
                    }
                }	
				else 
					lcd_byte_extend(Lib[xi]);
				xi++;
			}								
			row++;
			col=y;	
		}
	}								

//*******************************************************************
//	һ���ִ������			
//*******************************************************************

void lcd_dis_word( uint8_t x, uint8_t y, uint8_t *str, uint8_t ch8_16 )
	{
		uint row,col,ch_x,ch_y;
						    			
		row = x;
		col = y;
		
		while( *str != 0x00 )
		{
			else if( ch8_16 == 6*8 )
			{
				ch_y = 1;
				ch_x = 8;
                ch_68 = 0;
				lcd_one_word( row, col, ASC_6, *str-0x20, 8 );
			}
			else if( ch8_16 == 8*8 )
			{
				ch_y = 1;
				ch_x = 8;
                ch_68 = 1;
				lcd_one_word( row, col, ASC_8, *str-0x20, 8) ;
			}
            else
			{
				ch_y = 1;
				ch_x = 16;
			 	lcd_one_word( row, col, ASC_16, *str-0x20, 16 );
			}	
			if ( *str&0x80 )
			{
                if( ch8_16 == 12 )
                	col = col+ch_y*2;
                else if( ch8_16 == 16 )
                	col = col+ch_y*2+1;
            }
            else if( ch8_16 == 6*8 )
				col = col+ch_y*2;
            else 
				col = col+ch_y*3;
			if ( col >= dis_col )
            {
                if( ch8_16 == 6*8 )
				{
					col = y;
					row += ch_x+1;
				}
                else 
				{
					col=y;
					row+=ch_x;
				}		
            }
			if ( row >= dis_line ) row = x;
			str++;	
		}  
	}

//*******************************************************************
// display ch	
//*******************************************************************

void lcd_dis_ch( uint8_t x, uint8_t y, uint8_t *str, uint8_t i )
{
	uint8_t j, row, word;
	int xi;
	
	for (j=0;j<i;j++)
	{	
		word = str[j];
		xi = (word-0x20)*8;
		for( row = 0; row < 8; row++ )
		{
			lcd_setcursor( x+j*8+row, y );
			lcd_byte_extend_gr( ASC_8[xi] );
			xi++;
		}
	}
}

//*******************************************************************/ 
//�Աȶ�����			
//*******************************************************************

void lcd_set_contrast(uint8_t flag)
{
	lcd_wr_ctrl(LCD_CMD_SET_VBIAS_POTENTIOMETER);
	switch(flag)
	{
	case 1: 
		lcd_wr_ctrl(0x25); break;	//VOP=13.2V	    
	case 2: 
		lcd_wr_ctrl(0x32); break;   //VOP+0.3V  
	case 3: 
		lcd_wr_ctrl(0x40); break;   //VOP+0.6V  
	case 4: 
		lcd_wr_ctrl(0x18); break;   //VOP-0.3V  
	case 5: 
		lcd_wr_ctrl(0x0b); break;   //VOP-0.6V  
	}
}
    	
//*******************************************************************/ 
//Һ������ʼ��			
//*******************************************************************

void lcd_init(void)					    
{
	pinMode(LCD_CD,OUTPUT);
	pinMode(LCD_SDA,OUTPUT);
	pinMode(LCD_SCL,OUTPUT);
	pinMode(LCD_CS,OUTPUT);

	digitalWrite(LCD_CD,HIGH);
	digitalWrite(LCD_SDA,HIGH);
	digitalWrite(LCD_SCL,HIGH);
	digitalWrite(LCD_CS,HIGH);

	delay_ms(150);
	lcd_wr_ctrl(0x26);			//set Temp.		
	lcd_wr_ctrl(0xA2);			//set Line Rate	
	lcd_wr_ctrl(0xD5);			//set color mode
	lcd_wr_ctrl(0xE9);			//set LCD bias ratio
	
	lcd_set_contrast(3);        // contrast value
	lcd_wr_ctrl(0x2A);			//set power control
	lcd_wr_ctrl(0xF1);			//set COM end
	lcd_wr_ctrl(0x3F);			//64  Line
	//lcd_wr_ctrl(0xD0);		//set color pattern	BGR
	//lcd_wr_ctrl(0xc2);		//set MX=1, SEG output reverse direction		
							//set MY=0, COM output normal direction
	lcd_wr_ctrl(0xD1);		    //set color pattern	RGB
	lcd_wr_ctrl(0xc4);		    //set MX=0, SEG output normal direction		
							//set MY=1, COM output reverse direction
	lcd_wr_ctrl(0x89);			//set RAM address control
	lcd_wr_ctrl(0xAf);   		//set display enable  

	dis_col = 80; 
	dis_line = 64; 
}
    	
//*******************************************************************
//������
//*******************************************************************

void lcd_main(void)	
{					    
		//P0 = P1 = P2 = 0xFF;
						//��ʼ��LCD
			lcd_clr_screen();
			lcd_dis_square();
            lcd_dis_word(8,24,STR_24064_4,6*8);
            lcd_dis_word(24,16,STR_24064_5,8*8);
            delay_ms(1000);
			
			// lcd_set_contrast(1);
            // lcd_clr_screen();
			// for( int y = 0; y < 12; y++ ) {
			// 	lcd_setcursor( y, 0 );
			// 	for( int intensity = 0; intensity < 0x10; intensity++ ) {
			// 		for( int i = 0; i < 6; i++ ) {
			// 			lcd_wr_data(intensity<<4|intensity);
			// 		}
			// 	}
			// }
			// delay(2000);
		while(1)
		{ 		
			// lcd_clr_screen();
			//lcd_print_sys_12x14( 5, 20, "Съешь еще этих мягких французских булок" );
			// lcd_print_sys_12x14( 5, 20, "TEST test 1234567890" );
            // delay_ms(1000);
			lcd_clr_screen();
			//lcd_print_sys_12x14( 5, 20, "Съешь еще этих мягких французских булок" );
			lcd_print_sys_12x14( 0, 0, "АБВ абв ABC abc" );
			lcd_print_sys_12x14( 0, 16, "АБВ абв ABC abc", 0, 0xF );
			lcd_print_sys_12x14( 0, 32, "Тестовая строка", 0, 0x4 );
			lcd_print_sys_12x14( 0, 48, "Test string", 0xF, 0x2 );
			delay_ms(500);
			lcd_clr_screen();
			lcd_print_font(0,13,"0123456789",&font[FONT_BIG_CLOCK_2],15,0);
			delay(1000);
			lcd_clr_screen();
			for( int i = 107; i >= 0; i-- ) {
				char clock_str[10];
				sprintf( clock_str, "%d:%02d",i/60, i%60);
				String clock_string = clock_str;
				// clock_str += i/60;
				// clock_str += ":";
				// clock_str += i%60;
				Serial.println(clock_string);
				lcd_print_font(155,13,clock_str,&font[FONT_BIG_CLOCK_2],15,0);
				delay_ms(1000);
			}
			while(1);


			lcd_clr_screen();
			lcd_dis_word(1,1,STR_24064_7,8*8);
            delay_ms(5000);
			lcd_clr_screen();
			lcd_dis_word(1,1,STR_24064_7,6*8);
            delay_ms(5000);
			lcd_clr_screen();
			lcd_dis_word(1,1,STR_24064_7,16*16);
            delay_ms(5000);
		}	
	}

//----------------------------------------------------------------------------------

void lcd_point(uint8_t color);
void lcd_points_flush( void );

void lcd_print_font( uint8_t x, uint8_t y, String string, font_desc_t *font, uint8_t fore_color, uint8_t back_color ) {
	const char *str = string.c_str();
	//Serial.println("Codes -------------------------------");
	for( int i = 0; i < string.length(); i++) Serial.println(string[i],HEX);
	// Serial.println("End ---------------------------------");
	int str_len = string.length();
	uint64_t ch_mask = 0;
	uint16_t x_coord = x;
	for( int line = 0; line < font->rowsPerSymbol; line++ )
	{
		x_coord = x;
		//Serial.printf("Print line %d\r\n", line);
		ch_mask = (uint64_t)1<<line;
		lcd_setcursor( y+line, x/3 );
		for( int i = 0; i < strlen(str); i++ ) 
		{
			const uint8_t *symbol_data;
			int correction = -font->firstCode;
			if( str[i] == 208 ) // russian
			{
				i++;
				correction += -112;
			}
			else if( str[i] == 209 ) // russian
			{
				i++;
				correction += 48;
			}
			int font_data_index = ((font->colsMaxPerSymbol) * (font->bytesPerColumn) + 1) * (str[i] + correction);
			
				// Serial.printf("A=%d, B=%d\n",(font->colsMaxPerSymbol) * (font->bytesPerColumn) + 1, str[i] + correction);

			if( font_data_index < 0 || font_data_index > ((font->lastCode - font->firstCode)*(font->colsMaxPerSymbol) * (font->bytesPerColumn) + 1) )
			{
				// Serial.printf("Symbol with '%c'(code=%d) has no description in font \"%s\"!\n", str[i], str[i], font->name);
				// Serial.printf("Correction=%d, font_data_index=%d\n", correction, font_data_index);
				continue; // dont display garbage
			}
			symbol_data = &font->fontData[ font_data_index ]; // pointer to font char descriptor
			//Serial.printf("Print line %d symbol 0x%x, len %d\r\n", line, str[i], *ch_data);
			//Serial.printf("x=%d symsize=%d\r\n", x_coord, *symbol_data );
			if( (x_coord+(*symbol_data)) < LG240644_SCREEN_SIZE_X )
			{
				for( uint8_t col = 0; col < *symbol_data && col < font->colsMaxPerSymbol; col++ ) 
				{
					uint64_t symbol_column_word = 0;
					for( int j = font->bytesPerColumn-1; j >= 0; j-- )
					{
						symbol_column_word <<= 8;
						symbol_column_word |= symbol_data[1 + col*font->bytesPerColumn + j];
					}
					uint8_t color = (symbol_column_word & ch_mask) ? fore_color : back_color;
					
					//Serial.printf("data_word=0x%04x, ch_mask=0x%016x, color=0x%x\r\n", symbol_column_word, ch_mask, color );
					lcd_point( color );
				}
				lcd_point( back_color ); // space between charters
				x_coord += *symbol_data + 1;
				
			} else {
				break;
			}
		}
		// Serial.println("End ---------------------------------");
		lcd_points_flush();
		x_coord = x;
	}
}

void lcd_print_sys_12x14( uint8_t x, uint8_t y, String string, uint8_t fore_color, uint8_t back_color ) {
	const char *str = string.c_str();
	Serial.println("Codes -------------------------------");
	for( int i = 0; i < string.length(); i++) Serial.println(string[i],HEX);
	// Serial.println("End ---------------------------------");
	int str_len = string.length();
	uint16_t ch_mask = 0;
	uint16_t x_coord = x;
	for( int line = 0; line < 14; line++ )
	{
		//Serial.printf("Print line %d\r\n", line);
		ch_mask = 1<<line;
		lcd_setcursor( y+line, x );
		for( int i = 0; i < strlen(str); i++ ) 
		{
			const uint8_t *ch_data;
			if( str[i] == 208 ) // russian
			{
				Serial.print(str[i],HEX);
				Serial.print("-");
				i++;
				Serial.println(str[i],HEX);
				ch_data = &Verdana12x14ru[ 25 * (str[i]-144) ]; // pointer to font char descriptor
			}
			else if( str[i] == 209 ) // russian
			{
				Serial.print(str[i],HEX);
				Serial.print("-");
				i++;
				Serial.println(str[i],HEX);
				ch_data = &Verdana12x14ru[ 25 * (str[i]-80) ]; // pointer to font char descriptor
			}
			else
			{
				ch_data = &Verdana12x14en[ 25 * (str[i]-32) ]; // pointer to font char descriptor
			}
			//Serial.printf("Print line %d symbol 0x%x, len %d\r\n", line, str[i], *ch_data);
			if( (x_coord+(*ch_data)) < 240 )
			{
				for( uint8_t col = 0; col < *ch_data; col++ ) 
				{
					uint16_t ch_data_word = 0;
					ch_data_word = ch_data[1+col*2+1];
					ch_data_word <<= 8;
					ch_data_word |= ch_data[1+col*2];
					uint8_t color = (ch_data_word & ch_mask)?fore_color:back_color;
					
					//Serial.printf("data_word=0x%04x, ch_mask=0x%04x, color=0x%x\r\n", ch_data_word, ch_mask, color );
					lcd_point( color );
				}
				lcd_point( back_color ); // space between charters
				x_coord += *ch_data + 1;
				
			} else {
				break;
			}
		}
		Serial.println("End ---------------------------------");
		lcd_points_flush();
		x_coord = x;
	}
}

static uint8_t pts_cnt = 0;
static uint8_t offset = 4;
static uint8_t color_data[3] = {0};

void lcd_point(uint8_t color) 
{
	color_data[pts_cnt>>1] |= color << offset;
	pts_cnt++;
	if( pts_cnt == 6 ) 
	{
		lcd_points_flush();
	}
	else if( offset == 0 ) offset = 4; else offset = 0;
}
void lcd_points_flush( void )
{
	if( pts_cnt )
	{
		lcd_wr_data(color_data[0]);
		lcd_wr_data(color_data[1]);
		lcd_wr_data(color_data[2]);
		pts_cnt = 0;
		offset = 4;
		color_data[0] = 0;
		color_data[1] = 0;
		color_data[2] = 0;
	}
}
//----------------------------------------------------------------------------------


