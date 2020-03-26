/*
 * Raw_GFX_ST7789.h
 *
 * Created: 3/22/2020 1:27:04 AM
 *  Author: Mohannad Rawashdeh
 */ 


#ifndef RAW_GFX_ST7789_H_
#define RAW_GFX_ST7789_H_
#include "Graphics_Lib/Display_ST7789/ST7789_SPI_driver.h"
#include "Graphics_Lib/Font/fonts.h"
#define Min(a, b) (((a) < (b)) ? (a) : (b))
#define swap(a, b){ int16_t t = a; a = b; b = t; }
struct Raw_GFX_ST7789_p
{
	uint16_t height;
	uint16_t width;
	uint8_t rotation;
	uint8_t *image;
	 
};

void ST7789_drawAbsoultePixel(struct ST7789_param *gfx,int16_t x, int16_t y, uint16_t color);
void ST7789_drawPixel(struct ST7789_param *gfx,int16_t x, int16_t y, uint16_t color);
void ST7789_drawLine(struct ST7789_param *gfx,int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint16_t color);
void ST7789_drawFastVLine(struct ST7789_param *gfx,int16_t x, int16_t y, int16_t h, uint16_t color);
void ST7789_drawFastHLine(struct ST7789_param *gfx,int16_t x, int16_t y, int16_t w, uint16_t color);
void ST7789_drawRect(struct ST7789_param *gfx,int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color);
//void ST7789_fillRect(struct ST7789_param *gfx,int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color);
void ST7789_fillRect(struct ST7789_param *gfx,const int16_t x,const int16_t y,const int16_t w,const int16_t h,const uint16_t color);
void ST7789_fillScreen(struct ST7789_param *gfx,uint16_t color);
void ST7789_invertDisplay(struct ST7789_param *gfx,bool i);
void ST7789_drawCircle(struct ST7789_param *gfx,int16_t x0, int16_t y0, int16_t r,uint16_t color);
void ST7789_fillCircle(struct ST7789_param *gfx,int16_t x0, int16_t y0, int16_t r,uint16_t color);
void ST7789_fillCircleHelper(struct ST7789_param *gfx, int16_t x0, int16_t y0,int16_t r,uint8_t cornername,int16_t delta, uint16_t color);

void ST7789_DrawCharAt(struct ST7789_param *gfx,int x, int y, char ascii_char,sFONT *font,uint8_t font_size ,int colored);
void ST7789_DrawStringAt(struct ST7789_param *gfx,int x, int y, const char* text, sFONT* font,uint8_t font_size ,int colored);

void ST7789_drawBitmap(struct ST7789_param *gfx,int16_t x, int16_t y,const uint8_t *bitmap, int16_t w, int16_t h,uint16_t color);
#endif /* RAW_GFX_ST7789_H_ */