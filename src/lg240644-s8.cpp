//*******************************************************************/
// Эта программа представляет собой пример программы для 
// точечно-матричного графического ЖК-модуля.
// Модель контроллера LCD: UC1698 или другой совместимый контроллер
// MCU привода: AT89C52
//*******************************************************************/

#include <Arduino.h>
#include "lg240644-s8.h"
#include "lg24064-fonts.h"
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
void lcd_main(void);

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

uint dis_col,dis_line;
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

void wr_data(uint8_t dispdata) 
{
    digitalWrite(LCD_CS,LOW);//LCD_CS = 0;
    digitalWrite(LCD_CD,HIGH);//LCD_CD = 1;
    lcd_SendBit(dispdata,8);
    digitalWrite(LCD_CD,LOW);//LCD_CD = 0;
    digitalWrite(LCD_CS,HIGH);//LCD_CS = 1;
}

//*******************************************************************
// set cursor address
//*******************************************************************

void lcd_setcursor(uint8_t x, uint8_t y)
	{  	
   		lcd_wr_ctrl((x&0x0F)|0x60);	        // row address LSB
		lcd_wr_ctrl((x>>4)|0x70);		        // row address MSB  
		lcd_wr_ctrl((y>>4)|0x10);				// column address MSB
		lcd_wr_ctrl((y&0x0F)|0x00);			// column address LSB
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

void dis_square(void)
	{
		uint16_t  x,y;

		clr_screen();
        setcursor(0,0);					// set cursor
   		for(y=0;y<dis_col/2;y++) 		// write dis_col/2 column
		{
			wr_data(0xff);				// write display data 
			wr_data(0xff);
            wr_data(0xff);				
		}				
		for(x=1;x<dis_line-1;x++)		// write dis_line-2 row
		{
			setcursor(x,0);				// set cursor
			wr_data(0xf0);				// write display data 
			wr_data(0x00);				
   			wr_data(0x00);
            for(y=1;y<dis_col/2-1;y++) 	// write dis_col/2-2 column 
			{
				wr_data(0x00);			// write display data
				wr_data(0x00);
                wr_data(0x00);				
			}					
			wr_data(0x00);
            wr_data(0x00);				// write display data 
			wr_data(0x0f);	
		}
		setcursor(dis_line-1,0);		// set cursor
   		for(y=0;y<dis_col/2;y++) 		// write dis_col/2 column 
		{
			wr_data(0xff);				// write display data 
			wr_data(0xff);
            wr_data(0xff);				
		}
	}
    
//*******************************************************************/
// byte extend 64k color mode			
//*******************************************************************

void byte_extend_ch(uchar dat)			
	{
		uchar i,j,dat1,dat2;
		
		
		for(i=0;i<8;)					// extend D7--->D0 bit data
		{
			dat1=0;dat2=0;
			for(j=0;j<3;)				// 3 dot data extend to 2 8bit data
			{
				if((dat&0x80>>i)>0)		// first extend D7(i=0)
				dat1=0xF8;				// "D7"=1; dat1=0xF8
				else dat1=0x00;			// "D7"=0; dat1=0x00
				j++;i++;				// circle variable add 1
				if((dat&0x80>>i)>0)		// second extend D6(i=1)
				{dat1=dat1|0x07;		// "D6"=1; dat1=dat1|0x07
				dat2=0xE0;}				// dat2=0xE0
				else {dat1=dat1|0x00;	// "D6"=0; dat1=dat1|0x00
					 dat2=0x00;}
				j++;i++;				// circle variable add 1
				if((dat&0x80>>i)>0)		// second extend D6(i=1)
				dat2=dat2|0x1F;			// "D6"=1; dat1=dat1|0x1F
				else dat2=dat2|0x00;	// "D6"=0; dat1=dat1|0x00
				wr_data(dat1);			// write extend data
				wr_data(dat2);			// write extend data
				j++;i++;				// circle variable add 1
			}
		}
	}

//*******************************************************************
// byte extend 4k color mode 6*8ch			
//*******************************************************************

void byte_extend_6(uchar dat)			
	{
		uchar i,dat1;
		for(i=0;i<3;i++)			// extend D7--->D0 bit data
		{
			dat1=0x00;
            if(dat&0x80)		    // first extend D7(i=0)
			dat1=dat1|0xF0;			
			else dat1=dat1|0x00;	
			dat<<=1;
			if(dat&0x80)		    // second extend D6(i=1)
			dat1=dat1|0x0f;			
			else dat1=dat1|0x00;	
			wr_data(dat1);			// write extend data
			dat<<=1;				
		}
	}
    
//*******************************************************************
// byte extend 4k color mode 		
//*******************************************************************

void byte_extend(uchar dat)			
	{
		uchar i,dat1;
		for(i=0;i<4;i++)			// extend D7--->D0 bit data
		{
			dat1=0x00;
            if(dat&0x80)		    // first extend D7(i=0)
			dat1=dat1|0xF0;			
			else dat1=dat1|0x00;	
			dat<<=1;
			if(dat&0x80)		    // second extend D6(i=1)
			dat1=dat1|0x0f;			
			else dat1=dat1|0x00;	
			wr_data(dat1);			// write extend data
			dat<<=1;				
		}
	}

//*******************************************************************
// display "A"			
//*******************************************************************

void byte_extend_gr(uchar dat)			
	{
		uchar i,j,k,dat1,dat2;
		
		for(k=0;k<32;)						//write 30 8bit data
		{
			dat2=dat;						
			for(i=0;i<8;)					// extend D7--->D0 bit data
			{
				for(j=0;j<2;)				// 2 dot data extend to one 8bit data
				{
					if((dat2&0x80>>i)>0)	// first extend D7(i=0)
					dat1=0xF0;				// "D7"=1; dat1=0xF0
					else dat1=0x00;			// "D7"=0; dat1=0x00
					j++;i++;				// circle variable add 1
					if((dat2&0x80>>i)>0)	// second extend D6(i=1)
					dat1=dat1|0x0F;			// "D6"=1; dat1=dat1|0x0F
					else dat1=dat1|0x00;	// "D6"=0; dat1=dat1|0x00
					wr_data(dat1);			// write extend data
					j++;i++;				// circle variable add 1
				}
			}
			k++;
		}
	}

//*******************************************************************
//   �ַ��������������			
//*******************************************************************

void one_word(uchar x,uchar y,uchar *Lib,uchar ch_num,uchar widthw)
	{
		uint i,j,ch_x,ch_y,row,col;
		int xi;							//ƫ�������ַ����ٵĿ��Զ���ΪUchar	
		
		row=x;col=y;
		xi=ch_num * widthw;				//ÿ���ַ�ȡģ���׵�ַ	
		if (widthw==32)					    
		{ch_x=16;ch_y=2;}				//���ְ�������,����
		else if (widthw==24)					    
		{ch_x=12;ch_y=2;}				//���ְ�������,����
        else {ch_x=widthw; ch_y=1;}	    //8X16�ַ���8X8�ַ���������,����
		for(i=0;i<ch_x;i++)				//дch_x��
		{
			setcursor(row,col);
			for(j=0;j<ch_y;j++)			//дch_y bit data
			{   
				if(ch_y==1)
				{
                    if(ch_68==0)byte_extend_6(Lib[xi]);	//д���һ�ֽ�
                    else
                    {
                        lcd_wr_ctrl(0xd6);
                        lcd_byte_extend_ch(Lib[xi]);	//д���һ�ֽ�
                       	lcd_wr_ctrl(0xd5);
                    }
                }	
				else byte_extend(Lib[xi]);	//д���һ�ֽ�
				xi++;				    //next bit data
			}								
			row++;						//ָ���°���ַ���
			col=y;	
		}
	}								

//*******************************************************************
//	һ���ִ������			
//*******************************************************************

void dis_word(uchar x,uchar y,uchar *str,uchar ch8_16)
	{
		uint row,col,ch_x,ch_y;		  				//����ֲ�����
						    			
		row=x;col=y;
		
		while(*str!=0x00)								//д�ַ�����'\0'����
		{
			if (*str&0x80)		      					//�ж�
			{
				if(ch8_16==12)
                {
                    ch_y=2;				  					//�ַ�����������
    				ch_x=12;				  				//�ַ�����������						   
    				one_word(row,col,hz12_tab,*str&0x7f,24);	//ֻ������7λ��дһ������
                }
                else if(ch8_16==16)
                {
                    ch_y=2;				  					//�ַ�����������
    				ch_x=16;				  				//�ַ�����������						   
    				one_word(row,col,hz16_tab,*str&0x7f,32);	//ֻ������7λ��дһ������
                }	
			}
			else if(ch8_16==6*8)		  				//ch8_16==0 8X8�ַ�/ ch8_16==1 8X16�ַ�
			{
				ch_y=1;		   	  						//�ַ�����������
				ch_x=8;		      						//�ַ�����������
                ch_68=0;
				one_word(row,col,ASC_6,*str-0x20,8);	//ascii�����0x20��ʼ
			}
			else if(ch8_16==8*8)		  					//ch8_16==0 8X8�ַ�/ ch8_16==1 8X16�ַ�
			{
				ch_y=1;		   	  						//�ַ�����������
				ch_x=8;		      						//�ַ�����������
                ch_68=1;
				one_word(row,col,ASC_8,*str-0x20,8);	//ascii�����0x20��ʼ
			}
            else
			{
				ch_y=1;		  	 						//�ַ�����������
				ch_x=16;		   	 					//�ַ�����������
			 	one_word(row,col,ASC_16,*str-0x20,16);	//ascii�����0x20��ʼ
			}	
			if (*str&0x80)		      					//�ж�
			{
                if(ch8_16==12)
                col=col+ch_y*2;
                else if(ch8_16==16)
                col=col+ch_y*2+1;
            }
            else if(ch8_16==6*8)col=col+ch_y*2;
            else col=col+ch_y*3;				     	//��һ���ַ��е�ַ
			if (col>=dis_col)
            {
                if(ch8_16==6*8){col=y;row+=ch_x+1;}
                else {col=y;row+=ch_x;}		
            }
			if (row>=dis_line) row=x;		 			//�����Խ�磬��������	
			str++;	
		}  
	}

//*******************************************************************
// display ch	
//*******************************************************************

void dis_ch(uchar x,uchar y,uchar *str,uchar i)
	{
		uchar j,row,word;		  			//����ֲ�����
		int xi;
		
		for (j=0;j<i;j++)		  				//��ʾ���ַ���
		{	
			word = str[j];						//ȡ�ַ�
			xi=(word-0x20)*8; 					//����ģ��ַ
			for(row=0;row<8;row++)				//д8��
			{
				setcursor(x+j*8+row,y);			//���ַ
				byte_extend_gr(ASC_8[xi]);		//д��ģ����
				xi++;
			}
		}
	}

//*******************************************************************/ 
//�Աȶ�����			
//*******************************************************************

void set_contrast(uchar flag)
	{
		switch(flag)
		{
			case 1: 
			wr_ctrl(0x25); break;	//VOP=13.2V	    
			case 2: 
			wr_ctrl(0x32); break;   //VOP+0.3V  
			case 3: 
			wr_ctrl(0x40); break;   //VOP+0.6V  
			case 4: 
			wr_ctrl(0x18); break;   //VOP-0.3V  
			case 5: 
			wr_ctrl(0x0b); break;   //VOP-0.6V  
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
		wr_ctrl(0x26);			//set Temp.		
		wr_ctrl(0xA2);			//set Line Rate	
		wr_ctrl(0xD5);			//set color mode
		wr_ctrl(0xE9);			//set LCD bias ratio
		wr_ctrl(0x81);	        //Electronic volume mode set
		set_contrast(1);        // contrast value
        wr_ctrl(0x2A);			//set power control
		wr_ctrl(0xF1);			//set COM end
   		wr_ctrl(0x3F);			//64  Line
		//wr_ctrl(0xD0);		//set color pattern	BGR
		//wr_ctrl(0xc2);		//set MX=1, SEG output reverse direction		
	 							//set MY=0, COM output normal direction
		wr_ctrl(0xD1);		    //set color pattern	RGB
		wr_ctrl(0xc4);		    //set MX=0, SEG output normal direction		
	 							//set MY=1, COM output reverse direction
		wr_ctrl(0x89);			//set RAM address control
		wr_ctrl(0xAf);   		//set display enable  
	}
    	
//*******************************************************************
//������
//*******************************************************************

void lcd_main(void)						    
	{
		//P0 = P1 = P2 = 0xFF;

		dis_col=80; dis_line=64; 
		
		lcd_init();						//��ʼ��LCD
		while(1)
		{ 		
			clr_screen();
			dis_square();
            dis_word(8,24,STR_24064_4,6*8);
            dis_word(24,16,STR_24064_5,8*8);
			dis_word(40,16,STR1,16);			
            delay_ms(1000);
			clr_screen();
			dis_word(8,16,STR_24064_5,8*8);
            dis_word(24,16,STR2,12);
            dis_word(40,16,STR1,16);
            delay_ms(800);
            wr_ctrl(0xA7);
			delay_ms(1000);
            wr_ctrl(0xA6);
            clr_screen();
			dis_ch(1,0,STR_24064_6,8);
			delay_ms(800);
		}	
	}


