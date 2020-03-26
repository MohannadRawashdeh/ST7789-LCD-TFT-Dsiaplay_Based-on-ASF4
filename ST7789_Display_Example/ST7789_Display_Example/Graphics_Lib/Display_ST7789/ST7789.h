/*
 * ST7789.h
 *
 * Created: 3/21/2020 11:48:18 PM
 *  Author: Mohannad Rawashdeh
 */ 


#ifndef ST7789_H_
#define ST7789_H_

#include "Graphics_Lib/Raw_GFX/Raw_GFX_ST7789.h"

#define ST7789_TFTWIDTH  240
#define ST7789_TFTHEIGHT 240

#define ST7789_CASET   0x2A
#define ST7789_PASET   0x2B
#define ST7789_RAMWR   0x2C


// Color definitions
#define	ST7789_BLACK   0x0000
#define	ST7789_BLUE    0x001F
#define	ST7789_RED     0xF800
#define	ST7789_GREEN   0x07E0
#define ST7789_CYAN    0x07FF
#define ST7789_MAGENTA 0xF81F
#define ST7789_YELLOW  0xFFE0
#define ST7789_WHITE   0xFFFF


int  ST7789_Init(struct ST7789_param *st7789,
						uint16_t Disp_Height,uint16_t Disp_Width,
						uint8_t CS_pin,uint8_t DC_pin,uint8_t RST_pin);
void ST7789_SendCommand(struct ST7789_param *st7789,uint8_t command);
void ST7789_SendData(struct ST7789_param *st7789,uint8_t data);
void ST7789_Sendspiburst(struct ST7789_param *st7789,uint8_t dc_status);
void ST7789_Reset(struct ST7789_param *st7789);
void ST7789_setAddrWindow(struct ST7789_param *st7789,uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1);
uint16_t ST7789_color565(struct ST7789_param *st7789,uint8_t r, uint8_t g, uint8_t b);

#endif /* ST7789_H_ */