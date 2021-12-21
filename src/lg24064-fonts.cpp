//*******************************************************************
//  ���������ֿ�		
//*******************************************************************

#include "lg240644-s8.h"
#include "lg24064-fonts.h"
#include "types.h"

font_desc_t font[FONT_NUM] = {
    {
        "BIG CLOCK",
        Tahoma16x32,
        FONT_BIG_CLOCK_ROWS,
        FONT_BIG_CLOCK_COLUMNS,
        FONT_BYTES_PER_COLUMN(FONT_BIG_CLOCK_ROWS),
        FONT_BIG_CLOCK_FIRST_CODE,
        FONT_BIG_CLOCK_LAST_CODE
    },
    {
        "BIG CLOCK 2",
        Tahoma24x37,
        FONT_BIG_CLOCK_2_ROWS,
        FONT_BIG_CLOCK_2_COLUMNS,
        FONT_BYTES_PER_COLUMN(FONT_BIG_CLOCK_2_ROWS),
        FONT_BIG_CLOCK_2_FIRST_CODE,
        FONT_BIG_CLOCK_2_LAST_CODE
    },
    {
        "MIDDLE",
        Tahoma21x42,
        FONT_MIDDLE_ROWS,
        FONT_MIDDLE_COLUMNS,
        FONT_BYTES_PER_COLUMN(FONT_MIDDLE_ROWS),
        FONT_MIDDLE_FIRST_CODE,
        FONT_MIDDLE_LAST_CODE
    },
    {
        "ARIAL 10",
        Arial10,
        FONT_SMALL_ROWS,
        FONT_SMALL_COLUMNS,
        FONT_BYTES_PER_COLUMN(FONT_SMALL_ROWS),
        FONT_SMALL_FIRST_CODE,
        FONT_SMALL_LAST_CODE
    },
    {
        "ARIAL BOLD 20",
        ArialBold27x32,
        FONT_ARIALBOLD20_ROWS,
        FONT_ARIALBOLD20_COLUMNS,
        FONT_BYTES_PER_COLUMN(FONT_ARIALBOLD20_ROWS),
        FONT_ARIALBOLD20_FIRST_CODE,
        FONT_ARIALBOLD20_LAST_CODE
    }
};

//*******************************************************************


void lcd_print_font( uint8_t x, uint8_t y, String string, font_desc_t *font, uint8_t fore_color, uint8_t back_color, uint8_t spacing ) {
	const char *str = string.c_str();
	//Serial.println("Codes -------------------------------");
	//for( int i = 0; i < string.length(); i++) Serial.println(string[i],HEX);
	// Serial.println("End ---------------------------------");
	//int str_len = string.length();
	uint64_t ch_mask = 0;
	x /= 6;
	x *= 6;
	uint16_t x_coord = x;
	//Serial.printf("Print with font font \"%s\" ---------------------------------------------------------\n", font->name);
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
			if( str[i] == 0xD0 ) // russian (208)
			{
				i++;
				correction += 0x80 - 0x90; // 0x90 -> 0x80 //0xC0 - 0x90; //   0x90 ->0xC0	А-Яа-п
			}
			else if( str[i] == 0xD1 ) // russian (209) 	
			{
				i++;
				correction += 0x80 + 48 - 0x80;// 0x80 -> (0x80+48) //0xF0 - 0x80; //	0x80 -> 0xF0(240) р-я
			}
			int font_data_index = ( font->colsMaxPerSymbol * font->bytesPerColumn + 1) * (str[i] + correction);

			if( font_data_index < 0 || font_data_index > ((font->lastCode - font->firstCode + 1)*((font->colsMaxPerSymbol) * (font->bytesPerColumn) + 1)) )
			{
				//Serial.printf("Symbol with '%c'(code=%d) has no description! Correction=%d, font_data_index=%d\n", str[i], str[i], correction, font_data_index);
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
				for( uint8_t space = 0; space < spacing; space++ )
					lcd_point( back_color ); // space between charters
				x_coord += *symbol_data + spacing;
				
			} else {
				break;
			}
		}
			while( (x_coord%6) != 0 ) {
				lcd_point( back_color );
				x_coord++;
			}
		// Serial.println("End ---------------------------------");
		lcd_points_flush();
		x_coord = x;
	}
}

