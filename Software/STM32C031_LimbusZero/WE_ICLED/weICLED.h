#ifndef WEICLED_H_
#define WEICLED_H_

#include <stdint.h>

#define LOW			0xC000
#define HIGH		0xFF00
#define NEO_RESET	0x0000
#define NO_OF_LEDS			12
#define BIT_PER_LED			24
#define NO_OF_RESET_FRAMES	3
#define LENGTH				(NO_OF_LEDS*BIT_PER_LED+NO_OF_RESET_FRAMES) // 12*24 + 6

#include "stm32c0xx_hal.h"
#include "spi.h"
#define NEOPIXEL_DELAY(ms)							HAL_Delay(ms)
#define NEOPIXEL_SNED_BUFFER(bit_buffer, length)	HAL_SPI_Transmit_DMA(&hspi1, bit_buffer, length)

extern uint16_t neopixel_spi_buffer[LENGTH];

typedef struct __NEOPIXEL_t {
	uint8_t color_code_green;
	uint8_t color_code_red;
	uint8_t color_code_blue;
} NEOPIXEL_t;

typedef struct __RGB8_t {
	uint8_t color_code_green;
	uint8_t color_code_red;
	uint8_t color_code_blue;
} RGB8_t;

void neopixel_demo(void);
void neopixel_set_color(NEOPIXEL_t* pixel, RGB8_t rgb);
void neopixel_convert_RGB_to_bit_code(NEOPIXEL_t neopixe, uint16_t *bit_buffer);
void neopixel_convert_bool_to_spi_frame(uint16_t *bit_buffer, uint32_t length);
void neopixel_duplicate_bit_pattern(uint16_t *bit_buffer_single_neopixel, uint16_t *bit_buffer_target, uint32_t no_of_copies);
void neopixel_send_bit_stream(uint32_t *data_array, uint16_t length);


#endif /* WEICLED_H_ */
