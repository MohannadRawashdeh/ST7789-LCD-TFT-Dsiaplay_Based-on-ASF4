/************************************************************************/
/*					ST7789 Display Example
			this example will show you how to control a 240*240 pixel display
			using ASF4 and SAMD21/L21-22 xplained pro  board
			using DFLL 48MHz Clock for the CPU & SPI (11MHz)GLCK for the fastest performance
			Code written By: Mohannad Rawashdeh March 2020
			
			Connection :
			Display							SAMD21
			GND								  GND
			VCC									+5V(or +3.3 based on your module)
			SDA								  PA06
			SCL								  PA07
			RST								  PB06
			DC								  PB07
			CS								  PB03(for port control ,or PA05 as standard SPI CS)
			https://mb-raw.blogspot.com/
			*/
/************************************************************************/

#include "atmel_start.h"
#include <hal_gpio.h>
#include <hal_delay.h>
#include "Graphics_Lib/Display_ST7789/ST7789.h"
#include "Graphics_Lib/Raw_GFX/Raw_GFX_ST7789.h"
#include "Graphics_Lib/Font/fonts.h"
#include "Graphics_Lib/Font/bitmap_logo.h"

#define display_Height    240
#define display_Width     240

struct ST7789_param ST7789_t;
void Start_Graphic_Lib(void);
void Port_test();
void Test_Graphic_line();
void Test_Graphic_HLine();
void Test_Graphic_VLine();
void Test_Graphic_Rect();
void Test_Graphic_Cir();
void Test_draw_bitmap();
void Test_Graphic_FillRect();
void Test_Text_char();
	void Start_Graphic_Lib(void)
	{
		/*must be Called once to select the LCD and SPI parameters*/
		ST7789_Init(&ST7789_t,display_Height,display_Width,
					SPI_display_CS,Display_DC_pin,Display_RST_pin);
	}

void Port_test()
{
	gpio_set_port_level(GPIO_PORTB,1U << GPIO_PIN(LED0),true);
	delay_ms(100);
	gpio_set_port_level(GPIO_PORTB,1U << GPIO_PIN(LED0),false);
	delay_ms(100);
}	

	void Test_Graphic_VLine()
	{
			for (uint16_t col=0;col<ST7789_t.width;col+=8)
			{
				ST7789_drawFastVLine(&ST7789_t,col,0,ST7789_t.height,ST7789_GREEN);
				delay_ms(50);
			}
			for (uint16_t col=4;col<ST7789_t.width;col+=8)
			{
				ST7789_drawFastVLine(&ST7789_t,col,0,ST7789_t.height,ST7789_BLUE);
				delay_ms(50);
			}
			
	}

	void Test_Graphic_HLine()
	{
		for (uint16_t row=0;row<ST7789_t.height;row+=8)
		{
			ST7789_drawFastHLine(&ST7789_t,0,row,ST7789_t.width,ST7789_RED);
			delay_ms(50);
		}
		for (uint16_t row=4;row<ST7789_t.height;row+=8)
		{
			ST7789_drawFastHLine(&ST7789_t,0,row,ST7789_t.width,ST7789_CYAN);
			delay_ms(50);
		}
	
	}
	
	void Test_Graphic_Rect()
	{
			ST7789_drawRect(&ST7789_t,32,32,64,32,ST7789_CYAN);
			ST7789_drawRect(&ST7789_t,16,16,96,64,ST7789_RED);
			ST7789_drawRect(&ST7789_t,16,128,72,16,ST7789_YELLOW);
			ST7789_fillRect(&ST7789_t,168,128,16,48,ST7789_GREEN);
			ST7789_fillRect(&ST7789_t,16,216,24,16,ST7789_YELLOW);
			ST7789_fillRect(&ST7789_t,64,216,32,24,ST7789_RED);
			delay_ms(1000);
		
	}	
	
	void Test_Graphic_Cir()
	{
		for (uint16_t i=(ST7789_t.width/6)-1 ; i>4 ;i-=2)
		{
		ST7789_drawCircle(&ST7789_t,ST7789_t.width/2,ST7789_t.height/2,i,ST7789_BLUE);	
		delay_ms(50);
		}
		delay_ms(2000);
		ST7789_fillScreen(&ST7789_t,ST7789_WHITE);	
		ST7789_fillCircle(&ST7789_t,ST7789_t.width/2,ST7789_t.height/2,(ST7789_t.width/6)-1,ST7789_RED);
		delay_ms(500);
	}
	
	void Test_Text_char()
	{
		ST7789_DrawCharAt(&ST7789_t,5,5,'A',&Font24,1,ST7789_BLACK);
		ST7789_DrawCharAt(&ST7789_t,64,5,'X',&Font16,1,ST7789_BLACK);
		ST7789_DrawStringAt(&ST7789_t,5,24,"Hello World",&Font24,1,ST7789_BLACK);
		ST7789_DrawStringAt(&ST7789_t,5,48,"ST7789 Display",&Font16,1,ST7789_BLACK);
		ST7789_DrawStringAt(&ST7789_t,5,68,"With SAMD21J18",&Font16,1,ST7789_RED);
		ST7789_DrawStringAt(&ST7789_t,5,88,"& SAML22J18",&Font16,1,ST7789_RED);
		ST7789_DrawStringAt(&ST7789_t,5,108,"With SPI Bus",&Font16,1,ST7789_BLUE);
		ST7789_DrawStringAt(&ST7789_t,5,128,"Programmed by",&Font16,1,ST7789_BLUE);
		ST7789_DrawStringAt(&ST7789_t,5,150,"M.Rawashdeh",&Font24,1,ST7789_BLUE);
		ST7789_DrawStringAt(&ST7789_t,5,190,"March 2020",&Font16,2,ST7789_BLUE);
	}
	void Test_draw_bitmap()
	{
		ST7789_drawBitmap(&ST7789_t,0,0,MR_Logo_240x135,240,240,ST7789_BLACK);
		delay_ms(50);
		 for (int16_t c=255;c>0;c-=25)
		 {
			 ST7789_drawBitmap(&ST7789_t,0,0,MR_Logo_240x135,240,240,ST7789_color565(&ST7789_t,c,255-c,8));		 			 
		 }
		 delay_ms(50);
		ST7789_fillScreen(&ST7789_t,ST7789_BLACK);
		ST7789_drawBitmap(&ST7789_t,0,0,MR_Logo_240x135,240,240,ST7789_WHITE);
		delay_ms(50);
		for (int16_t c=255;c>0;c-=25)
		{
			ST7789_drawBitmap(&ST7789_t,0,0,USB_ICON,240,240,ST7789_color565(&ST7789_t,c,255-c,8));
		}
	}
	
	void Test_Graphic_FillRect()
	{
		ST7789_fillScreen(&ST7789_t,ST7789_RED);
		gpio_toggle_pin_level(LED0);
		ST7789_fillScreen(&ST7789_t,ST7789_BLACK);
		gpio_toggle_pin_level(LED0);
		ST7789_fillScreen(&ST7789_t,ST7789_BLUE);
		gpio_toggle_pin_level(LED0);
		ST7789_fillScreen(&ST7789_t,ST7789_CYAN);
		gpio_toggle_pin_level(LED0);
		ST7789_fillScreen(&ST7789_t,ST7789_WHITE);
		gpio_toggle_pin_level(LED0);
		ST7789_fillScreen(&ST7789_t,ST7789_YELLOW);
		gpio_toggle_pin_level(LED0);
		ST7789_fillScreen(&ST7789_t,ST7789_BLUE);
		
	}
int main(void)
{
	atmel_start_init();
	Port_test();
	Start_Graphic_Lib();
	uint16_t time_delay=1000;
	ST7789_fillScreen(&ST7789_t,ST7789_BLACK);
	while (1)
	{
		Test_Graphic_FillRect();
		ST7789_fillScreen(&ST7789_t,ST7789_WHITE);
		Test_Text_char();
		delay_ms(time_delay);
		ST7789_fillScreen(&ST7789_t,ST7789_WHITE);
		Test_Graphic_HLine();
		delay_ms(time_delay);
		ST7789_fillScreen(&ST7789_t,ST7789_WHITE);
		Test_Graphic_VLine();
		delay_ms(time_delay);
		ST7789_fillScreen(&ST7789_t,ST7789_BLACK);
		Test_Graphic_Rect();
		delay_ms(time_delay);
		ST7789_fillScreen(&ST7789_t,ST7789_WHITE);
		Test_Graphic_Cir();
		delay_ms(time_delay);
		ST7789_fillScreen(&ST7789_t,ST7789_WHITE);
		while (1)
		{
			Test_draw_bitmap();
		}
		
		delay_ms(time_delay);
		ST7789_fillScreen(&ST7789_t,ST7789_WHITE);
	}
}
