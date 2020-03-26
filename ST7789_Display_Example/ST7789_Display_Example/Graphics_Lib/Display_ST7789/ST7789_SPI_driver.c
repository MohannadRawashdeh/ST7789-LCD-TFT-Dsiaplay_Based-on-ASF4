/*
 * ST7789_SPI_driver.c
 *
 * Created: 3/21/2020 11:50:12 PM
 *  Author: Mohannad Rawashdeh
 */ 
#include "atmel_start.h"
#include "Graphics_Lib/Display_ST7789/ST7789_SPI_driver.h"
#include "hal_spi_m_sync.h"
#include "hpl_spi.h"
#include "utils.h"
#include "driver_init.h"
#include <hal_io.h>
#include <hal_gpio.h>
//const uint32_t UC8151_spi_baudrate  = 1000000;
#define ASF4_spi_driver  driver_spi_m_sync_ST7789
struct io_descriptor *io_ST7789_spi;
 struct spi_xfer xfer;
void    ST7789_SPI_driver_init(struct ST7789_param *driver)
{
	st7789_spi.busy_pin=driver->busy_pin;
	st7789_spi.cs_pin  =driver->cs_pin;
	st7789_spi.dc_pin  =driver->dc_pin;
	st7789_spi.rst_pin =driver->rst_pin;
	st7789_spi.height  =driver->height;
	st7789_spi.width   =driver->width;
	st7789_spi.spi_driver_type=ASF4_spi_driver;
	//spi_m_sync_set_baudrate(&SPI_Display,UC8151_spi_baudrate);
	/*in default the driver is sync spi*/
	/*don't forget to set the height and width of the display*/
	//driver->spi_driver_type = driver_spi_m_sync_ST7789;
	spi_m_sync_get_io_descriptor(&SPI_Display, &io_ST7789_spi);
	spi_m_sync_enable(&SPI_Display);	
}
void    set_ST7789_SPI_driver_pin(uint8_t pin,uint8_t status)
{
	//gpio_set_pin_level(pin,status);
	gpio_set_port_level(GPIO_PORTB,1U << GPIO_PIN(pin),status);
}
uint8_t get_ST7789_SPI_driver_pin(uint8_t pin)
{
	return gpio_get_pin_level(pin);
}
void    ST7789_dtime_delay_ms(uint16_t dtime)
{
	delay_ms(dtime);
}
void    spi_send_cmd_ST7789(struct ST7789_param *driver)
{
		#if ASF4_spi_driver == driver_spi_m_sync_ST7789
			/*xfer.rxbuf=NULL;
			//xfer.txbuf=driver->data;
			//xfer.size =driver->data_size;			
			//spi_m_sync_transfer(&SPI_Display,&xfer);
			*/
			set_ST7789_SPI_driver_pin(driver->cs_pin, false);
			io_write(io_ST7789_spi,driver->data, driver->data_size);
			set_ST7789_SPI_driver_pin(driver->cs_pin, true);
		#endif
}
void    spi_transfer_ST7789(struct ST7789_param *driver)
{
	#if ASF4_spi_driver == driver_spi_m_sync_ST7789
		io_write(io_ST7789_spi,driver->buf_data, driver->buf_size);
	#endif
}

