/*
 * Raw_GFX_ST7789.c
 *
 * Created: 3/22/2020 1:26:53 AM
 *  Author: Mohannad Rawashdeh
 */ 

#include "atmel_start.h"
#include "Graphics_Lib/Display_ST7789/ST7789.h"
#include "Graphics_Lib/Display_ST7789/ST7789_SPI_driver.h"
#include "Graphics_Lib/Font/fonts.h"
#include <math.h>
#include <fastmath.h>
#include "stdlib.h"
struct spi_xfer xf;
void ST7789_drawAbsoultePixel(struct ST7789_param *gfx,int16_t x, int16_t y, uint16_t color)
{
	/*
	in this method , prepare the data you want to send on one array and send them at once together
	SPI @CPU 8MHz is so slow to send , this would slightly increase the speed of writing data 
	to display
	
	*/
		if((x < 0) ||(x >= gfx->width) || (y < 0) || (y >= gfx->height)) return;
		gfx->buf_data[0]=ST7789_CASET;
		gfx->buf_data[1]=x & 0xFF;
		gfx->buf_data[2]=(x+1) >> 8;
		gfx->buf_data[3]=(x+1) & 0xFF;
		gfx->buf_size=1;
		/*finish the communication*/		
		set_ST7789_SPI_driver_pin(gfx->cs_pin,false);
		/*send the command for Col.... */
		ST7789_Sendspiburst(gfx,false);
		gfx->buf_data[0]=x >> 8;
		gfx->buf_size=4;
		/*send the data .... */
		ST7789_Sendspiburst(gfx,true);
		gfx->buf_data[1]=y ;
		gfx->buf_data[2]=(y+1) >> 8;
		gfx->buf_data[3]=y+1 ;
		gfx->buf_data[0]=ST7789_PASET;
		gfx->buf_size=1;
		/*send the command for Rows .... */
		ST7789_Sendspiburst(gfx,false); // Row addr set
		gfx->buf_data[0]=y >> 8;
		gfx->buf_size=4;
		/*send the data .... */
		ST7789_Sendspiburst(gfx,true);
		gfx->buf_data[0]=ST7789_RAMWR;
		gfx->buf_size=1;
		ST7789_Sendspiburst(gfx,false);
		/*send the color of the pixel*/
		gfx->buf_data[0]=(color >> 8);
		gfx->buf_data[1]=color;
		gfx->buf_size=2;
		set_ST7789_SPI_driver_pin(gfx->dc_pin,true);
		spi_transfer_ST7789(gfx);
		/*finish the communication*/
		set_ST7789_SPI_driver_pin(gfx->cs_pin,true);
}
void ST7789_drawPixel(struct ST7789_param *gfx,int16_t x, int16_t y, uint16_t color)
{
	
	if((x < 0) ||(x >= gfx->width) || (y < 0) || (y >= gfx->height)) return;

//	if (hwSPI) spi_begin();
	ST7789_setAddrWindow(gfx,x,y,x+1,y+1);
	/*could be replaced by ST7789_pushColor command*/
	gfx->buf_data[0]=(color >> 8);
	gfx->buf_data[1]=color;
	gfx->buf_size=2;
	set_ST7789_SPI_driver_pin(gfx->dc_pin,true);
	set_ST7789_SPI_driver_pin(gfx->cs_pin,false);
	spi_transfer_ST7789(gfx);
	set_ST7789_SPI_driver_pin(gfx->cs_pin,true);
}
void ST7789_drawLine(struct ST7789_param *gfx,int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint16_t color)
{
	
	 int16_t steep = abs(y1 - y0) > abs(x1 - x0);
	 printf("steep=%d\r\n",steep);
	 if (steep) {
		 swap(x0, y0);
		 swap(x1, y1);
	 }

	 if (x0 > x1) {
		 swap(x0, x1);
		 swap(y0, y1);
	 }
	
	 int16_t dx, dy;
	 dx = x1 - x0;
	 dy = abs(y1 - y0);

	 int16_t err = dx / 2;
	 int16_t ystep;

	 if (y0 < y1) {
		 ystep = 1;
		 } else {
		 ystep = -1;
	 }
	set_ST7789_SPI_driver_pin(gfx->cs_pin,false);
	 for (; x0<=x1; x0++) {
		 
		 if (steep) {
			 ST7789_drawAbsoultePixel(gfx,y0, x0, color);
			 } else {
			 ST7789_drawAbsoultePixel(gfx,x0, y0, color);
		 }
		 err -= dy;
		 if (err < 0) {
			 y0 += ystep;
			 err += dx;
		 }
	 }
set_ST7789_SPI_driver_pin(gfx->cs_pin,true);
}
void ST7789_drawFastVLine(struct ST7789_param *gfx,int16_t x, int16_t y, int16_t h, uint16_t color)
{
	 if((x >= gfx->width) || (y >= gfx->height)) return;
	 if((y+h-1) >= gfx->height)
	 h = gfx->height-y;
	 ST7789_setAddrWindow(gfx,x, y, x, y+h-1);
	 uint16_t count=0;
	 while (count<h*2)
	 {
		 gfx->buf_data[count++]= color >> 8;
		 gfx->buf_data[count++]= color;
	 }
	 gfx->buf_size=count-1;
	set_ST7789_SPI_driver_pin(gfx->dc_pin,true);
	set_ST7789_SPI_driver_pin(gfx->cs_pin,false);
	spi_transfer_ST7789(gfx);
	set_ST7789_SPI_driver_pin(gfx->cs_pin,true);
}
void ST7789_drawFastHLine(struct ST7789_param *gfx,int16_t x, int16_t y, int16_t w, uint16_t color)
{
	 // Rudimentary clipping
	 if((x >= gfx->width) || (y >= gfx->height)) return;
	 if((x+w-1) >= gfx->width)  w = gfx->width -x;
	 ST7789_setAddrWindow(gfx,x, y, x+w-1, y);
	 uint16_t count=0;
	 while (count<w*2)
	 {
		 gfx->buf_data[count++]= color >> 8;
		 gfx->buf_data[count++]= color;
	 }
	 
	 gfx->buf_size=count-1;
	 set_ST7789_SPI_driver_pin(gfx->dc_pin,true);
	 set_ST7789_SPI_driver_pin(gfx->cs_pin,false);	 
	 spi_transfer_ST7789(gfx);	  
	 set_ST7789_SPI_driver_pin(gfx->cs_pin,true);
}
void ST7789_drawRect(struct ST7789_param *gfx,int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color)
{
	  ST7789_drawFastHLine(gfx,x, y, w, color);
	  ST7789_drawFastHLine(gfx,x, y+h-1, w, color);
	  ST7789_drawFastVLine(gfx,x, y, h, color);
	  ST7789_drawFastVLine(gfx,x+w-1, y, h, color);
}
void ST7789_fillRect(struct ST7789_param *gfx,const int16_t x,const int16_t y,const int16_t w,const int16_t h,const uint16_t color)
{
	const uint16_t tot=x+w;
	ST7789_setAddrWindow(gfx,x, y, x+w-1, y+h-1);
	for (uint16_t i=0;i<tot*2;i+=2)
	{
		gfx->buf_data[i]= color >> 8;
		gfx->buf_data[i+1]= color;
	}
	gfx->buf_size=tot*2;
	set_ST7789_SPI_driver_pin(gfx->dc_pin,true);
	set_ST7789_SPI_driver_pin(gfx->cs_pin,false);
	  for (int16_t i=x; i<tot; i++) 
	  {
		  spi_transfer_ST7789(gfx);
	  }
	  set_ST7789_SPI_driver_pin(gfx->cs_pin,true);
}
void ST7789_fillScreen(struct ST7789_param *gfx,uint16_t color)
{
	uint16_t x=0;
	uint16_t y=0;
	uint16_t w=gfx->width;
	uint16_t h=gfx->height;
	const uint16_t tot=x+w;
	
	ST7789_setAddrWindow(gfx,x, y, x+w-1, y+h-1);
	for (uint16_t i=0;i<tot*2;i+=2)
	{
		gfx->buf_data[i]= color >> 8;
		gfx->buf_data[i+1]= color;
	}
	gfx->buf_size=tot*2;
	set_ST7789_SPI_driver_pin(gfx->dc_pin,true);
	set_ST7789_SPI_driver_pin(gfx->cs_pin,false);
	for (int16_t i=x; i<tot; i++) 
	{
		spi_transfer_ST7789(gfx);
	}
	set_ST7789_SPI_driver_pin(gfx->cs_pin,true);
}
void ST7789_invertDisplay(struct ST7789_param *gfx,bool i)
{
	
}

void ST7789_drawCircle(struct ST7789_param *gfx,int16_t x0, int16_t y0, int16_t r,uint16_t color) {
	int16_t f = 1 - r;
	int16_t ddF_x = 1;
	int16_t ddF_y = -2 * r;
	int16_t x = 0;
	int16_t y = r;

	ST7789_drawAbsoultePixel(gfx,x0  , y0+r, color);
	ST7789_drawAbsoultePixel(gfx,x0  , y0-r, color);
	ST7789_drawAbsoultePixel(gfx,x0+r, y0  , color);
	ST7789_drawAbsoultePixel(gfx,x0-r, y0  , color);

	while (x<y) {
		if (f >= 0) {
			y--;
			ddF_y += 2;
			f += ddF_y;
		}
		x++;
		ddF_x += 2;
		f += ddF_x;
		
		ST7789_drawAbsoultePixel(gfx,x0 + x, y0 + y, color);
		ST7789_drawAbsoultePixel(gfx,x0 - x, y0 + y, color);
		ST7789_drawAbsoultePixel(gfx,x0 + x, y0 - y, color);
		ST7789_drawAbsoultePixel(gfx,x0 - x, y0 - y, color);
		ST7789_drawAbsoultePixel(gfx,x0 + y, y0 + x, color);
		ST7789_drawAbsoultePixel(gfx,x0 - y, y0 + x, color);
		ST7789_drawAbsoultePixel(gfx,x0 + y, y0 - x, color);
		ST7789_drawAbsoultePixel(gfx,x0 - y, y0 - x, color);
	}
}

void ST7789_fillCircle(struct ST7789_param *gfx,int16_t x0, int16_t y0, int16_t r,uint16_t color)
{
	ST7789_drawFastVLine(gfx,x0, y0-r, 2*r+1, color);
	ST7789_fillCircleHelper(gfx,x0, y0, r, 3, 1,color);
	/*
	for (uint16_t r_angle=0;r_angle<180;r_angle++)
	{
		//ST7789_drawFastHLine(gfx,x0 - x, y0 + y, x0 + x, y0 + y);
		//ST7789_drawLine(gfx,x0-(r/2), y0-(r/2), x0+(r/2)+2,y0+(r/2), color);
	}
	*/
}

void ST7789_fillCircleHelper(struct ST7789_param *gfx, int16_t x0, int16_t y0,int16_t r,uint8_t cornername,int16_t delta, uint16_t color)
{
	
 int16_t f     = 1 - r;
 int16_t ddF_x = 1;
 int16_t ddF_y = -2 * r;
 int16_t x     = 0;
 int16_t y     = r;

 while (x<y) {
	 if (f >= 0) {
		 y--;
		 ddF_y += 2;
		 f     += ddF_y;
	 }
	 x++;
	 ddF_x += 2;
	 f+= ddF_x;

	 if (cornername & 0x1) 
	 {
		 
		 ST7789_drawFastVLine(gfx,x0+x, y0-y, 2*y+1+delta, color);
		 ST7789_drawFastVLine(gfx,x0+y, y0-x, 2*x+1+delta, color);
	 }
	 if (cornername & 0x2) {
		 ST7789_drawFastVLine(gfx,x0-x, y0-y, 2*y+1+delta, color);
		 ST7789_drawFastVLine(gfx,x0-y, y0-x, 2*x+1+delta, color);
	 }
 }
	
}


void ST7789_DrawCharAt(struct ST7789_param *gfx,int x, int y, char ascii_char,sFONT *font,uint8_t font_size ,int colored)
{
	int i, j;
	unsigned int char_offset = (ascii_char - ' ') * font->Height * (font->Width / 8 + (font->Width % 8 ? 1 : 0));
	const unsigned char* ptr = &font->table[char_offset];
	//  printf("char %c\r\n",ascii_char);
	for (j = 0; j < font->Height; j++) {
		for (i = 0; i < font->Width; i++) {
			// printf("ft[%d]=%d\r\n",char_offset,font->table[char_offset]);
			if ((font->table[char_offset]) & (0x80 >> (i % 8))) 
			{
				if (font_size == 1)
				{
					ST7789_drawAbsoultePixel(gfx,x + i, y + j, colored);
				}
				else
				{
					ST7789_fillRect(gfx,x+(i*font_size),y+(j*font_size),font_size,font_size, colored);
				}
				
			}
			if (i % 8 == 7) {
				ptr++;
				char_offset++;
			}
		}
		if (font->Width % 8 != 0) {
			ptr++;
			char_offset++;
		}
	}
}

void ST7789_DrawStringAt(struct ST7789_param *gfx,int x, int y, const char* text, sFONT* font,uint8_t font_size ,int colored)
	{
		const char* p_text = text;
		unsigned int counter = 0;
		int refcolumn = x;
		
		/* Send the string character by character on EPD */
		while (*p_text != 0) {
			/* Display one character on EPD */
			ST7789_DrawCharAt(gfx,refcolumn, y, *p_text, font,font_size ,colored);
			/* Decrement the column position by 16 */
			refcolumn += (font->Width*font_size);
			/* Point on the next character */
			p_text++;
			counter++;
		}
	}
	
void ST7789_drawBitmap(struct ST7789_param *gfx,int16_t x, int16_t y,const uint8_t *bitmap, int16_t w, int16_t h,uint16_t color)
{
		int16_t i, j, byteWidth = (w + 7) / 8;
		for(j=0; j<h; j++) 
		{
			for(i=0; i<w; i++ ) 
			{
			/*	printf("eq=%d\r\n",j * byteWidth + i / 8); 
				printf("bitmap[%d]=%d, ",count,bitmap[count]);
			*/
				if(bitmap[j * byteWidth + i / 8] & (128 >> (i & 7)))//(1 << (shift % 8)))
				{
					ST7789_drawAbsoultePixel(gfx,x+i, y+j, color);	

				}
			}
		}
}
	