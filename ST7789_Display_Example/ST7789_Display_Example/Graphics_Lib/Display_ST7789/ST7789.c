/*
 * ST7789.c
 *
 * Created: 3/21/2020 11:48:28 PM
 *  Author: Mohannad Rawashdeh
 */ 
#include "atmel_start.h"
#include "Graphics_Lib/Display_ST7789/ST7789.h"
#include "Graphics_Lib/Raw_GFX/Raw_GFX_ST7789.h"

static void Font_init(void)
{
	Font8.Height=8;
	Font8.Width =5;
	Font12.Height=12;
	Font12.Width=8;
	Font16.Height=16;
	Font16.Width=11;
	Font20.Height=20;
	Font20.Width=14;
	
}
int  ST7789_Init(struct ST7789_param *st7789,uint16_t Disp_Height,
		uint16_t Disp_Width,uint8_t CS_pin,uint8_t DC_pin,uint8_t RST_pin)
{
	/*init the GPIO , SPI driver*/
	st7789->cs_pin=CS_pin;
	st7789->rst_pin=RST_pin;
	st7789->dc_pin=DC_pin;
	st7789->busy_pin=0;/*no busy pin available here*/
	st7789->height=Disp_Height;
	st7789->width =Disp_Width;
	st7789->data_size=1;
	st7789->buf_size=2;
	Font_init();
	/*init the SPI driver here*/
	ST7789_SPI_driver_init(st7789);
	ST7789_Reset(st7789);
		 //************* Start Initial Sequence **********//
		 ST7789_SendCommand(st7789,0x36);
		 ST7789_SendData(st7789,0x00);
		 //writedata(0x70);
		 
		 ST7789_SendCommand(st7789,0x3A);
		 ST7789_SendData(st7789,0x05);
		 
		 ST7789_SendCommand(st7789,0xB2);
		 ST7789_SendData(st7789,0x0C);
		 ST7789_SendData(st7789,0x0C);
		 ST7789_SendData(st7789,0x00);
		 ST7789_SendData(st7789,0x33);
		 ST7789_SendData(st7789,0x33);
		 
		 ST7789_SendCommand(st7789,0xB7);
		 ST7789_SendData(st7789,0x35);
		 
		 ST7789_SendCommand(st7789,0xBB);
		 ST7789_SendData(st7789,0x19);
		 
		 ST7789_SendCommand(st7789,0xC0);
		 ST7789_SendData(st7789,0x2C);
		 
		 ST7789_SendCommand(st7789,0xC2);
		 ST7789_SendData(st7789,0x01);
		 
		 ST7789_SendCommand(st7789,0xC3);
		 ST7789_SendData(st7789,0x12);
		 
		 ST7789_SendCommand(st7789,0xC4);
		 ST7789_SendData(st7789,0x20);
		 
		 ST7789_SendCommand(st7789,0xC6);
		 ST7789_SendData(st7789,0x0F);
		 
		 ST7789_SendCommand(st7789,0xD0);
		 ST7789_SendData(st7789,0xA4);
		 ST7789_SendData(st7789,0xA1);
		 
		 ST7789_SendCommand(st7789,0xE0);
		 ST7789_SendData(st7789,0xD0);
		 ST7789_SendData(st7789,0x04);
		 ST7789_SendData(st7789,0x0D);
		 ST7789_SendData(st7789,0x11);
		 ST7789_SendData(st7789,0x13);
		 ST7789_SendData(st7789,0x2B);
		 ST7789_SendData(st7789,0x3F);
		 ST7789_SendData(st7789,0x54);
		 ST7789_SendData(st7789,0x4C);
		 ST7789_SendData(st7789,0x18);
		 ST7789_SendData(st7789,0x0D);
		 ST7789_SendData(st7789,0x0B);
		 ST7789_SendData(st7789,0x1F);
		 ST7789_SendData(st7789,0x23);
		 
		 ST7789_SendCommand(st7789,0xE1);
		 ST7789_SendData(st7789,0xD0);
		 ST7789_SendData(st7789,0x04);
		 ST7789_SendData(st7789,0x0C);
		 ST7789_SendData(st7789,0x11);
		 ST7789_SendData(st7789,0x13);
		 ST7789_SendData(st7789,0x2C);
		 ST7789_SendData(st7789,0x3F);
		 ST7789_SendData(st7789,0x44);
		 ST7789_SendData(st7789,0x51);
		 ST7789_SendData(st7789,0x2F);
		 ST7789_SendData(st7789,0x1F);
		 ST7789_SendData(st7789,0x1F);
		 ST7789_SendData(st7789,0x20);
		 ST7789_SendData(st7789,0x23);
		 
		 ST7789_SendCommand(st7789,0x21);
		 set_ST7789_SPI_driver_pin(st7789->cs_pin,true);
		 set_ST7789_SPI_driver_pin(st7789->cs_pin,false);

		 ST7789_SendCommand(st7789,0x11);    //Exit Sleep
		 ST7789_dtime_delay_ms(120);
		 ST7789_SendCommand(st7789,0x29);    //Display on
	return 0;
}
void ST7789_SendCommand(struct ST7789_param *st7789,uint8_t command)
{
	/*set DC pin to low  */
	st7789->data[0]=command;
	set_ST7789_SPI_driver_pin(st7789->dc_pin,false);
	spi_send_cmd_ST7789(st7789);
}
void ST7789_SendData(struct ST7789_param *st7789,uint8_t data)
{
	/*set DC pin to high  */
	st7789->data[0]=data;
	set_ST7789_SPI_driver_pin(st7789->dc_pin,true);
	spi_send_cmd_ST7789(st7789);
}
void ST7789_Sendspiburst(struct ST7789_param *st7789,uint8_t dc_status)
{
	set_ST7789_SPI_driver_pin(st7789->dc_pin,dc_status);
	spi_transfer_ST7789(st7789);
}
void ST7789_Reset(struct ST7789_param *st7789)
{
	set_ST7789_SPI_driver_pin(st7789->rst_pin,true);
	ST7789_dtime_delay_ms(10);
	set_ST7789_SPI_driver_pin(st7789->rst_pin,false);
	ST7789_dtime_delay_ms(25);
	set_ST7789_SPI_driver_pin(st7789->rst_pin,true);
	ST7789_dtime_delay_ms(100);
}
void ST7789_setAddrWindow(struct ST7789_param *st7789,uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1)
{
	ST7789_SendCommand(st7789,ST7789_CASET); // Column addr set
	ST7789_SendData(st7789,x0 >> 8);
	ST7789_SendData(st7789,x0 & 0xFF);     // XSTART
	ST7789_SendData(st7789,x1 >> 8);
	ST7789_SendData(st7789,x1 & 0xFF);     // XEND

	ST7789_SendCommand(st7789,ST7789_PASET); // Row addr set
	ST7789_SendData(st7789,y0>>8);
	ST7789_SendData(st7789,y0);     // YSTART
	ST7789_SendData(st7789,y1>>8);
	ST7789_SendData(st7789,y1);     // YEND

	ST7789_SendCommand(st7789,ST7789_RAMWR); // write to RAM
}

uint16_t ST7789_color565(struct ST7789_param *st7789,uint8_t r, uint8_t g, uint8_t b)
{
	return ((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3);
}

