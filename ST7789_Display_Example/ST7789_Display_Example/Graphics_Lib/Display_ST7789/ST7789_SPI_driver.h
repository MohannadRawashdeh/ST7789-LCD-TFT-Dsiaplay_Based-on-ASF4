/*
 * ST7789_SPI_driver.h
 *
 * Created: 3/21/2020 11:49:56 PM
 *  Author: Mohannad Rawashdeh
 */ 


#ifndef ST7789_SPI_DRIVER_H_
#define ST7789_SPI_DRIVER_H_

#include "utils.h"
#ifndef driver_spi_m_sync_ST7789
#define driver_spi_m_sync_ST7789    1 /*using sync driver for ASF4*/
#endif
#ifndef driver_spi_m_async_ST7789
#define driver_spi_m_async_ST7789   2 /*using async driver for ASF4 , 0:disabled , 2: enabled*/
#endif
#ifndef driver_spi_m_RTOS_ST7789
#define driver_spi_m_RTOS_ST7789    3 /*using RTOS driver for ASF4,0:disabled , 3: enabled*/
#endif
#ifndef driver_spi_m_DMA_ST7789
#define driver_spi_m_DMA_ST7789     4 /*using DMA driver for ASF4,0:disabled , 4: enabled*/
#endif

struct ST7789_param
{
	uint8_t cs_pin;
	uint8_t busy_pin;
	uint8_t dc_pin;
	uint8_t rst_pin;
	uint8_t spi_driver_type;
	uint16_t width;
	uint16_t height;
	uint8_t data[1];
	uint8_t buf_data[512];
	uint16_t buf_size;
	uint16_t data_size;
};
struct ST7789_param  st7789_spi;

void    ST7789_SPI_driver_init(struct ST7789_param *driver);
void    set_ST7789_SPI_driver_pin(uint8_t pin,uint8_t status);
uint8_t get_ST7789_SPI_driver_pin(uint8_t pin);
void    ST7789_dtime_delay_ms(uint16_t dtime);
void    spi_send_cmd_ST7789(struct ST7789_param *driver);
void    spi_transfer_ST7789(struct ST7789_param *driver);

#endif /* ST7789_SPI_DRIVER_H_ */