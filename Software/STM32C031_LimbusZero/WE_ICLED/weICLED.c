#include "weICLED.h"
#include <string.h>

uint16_t dma_buffer[LENGTH * NO_OF_LEDS + 1] = { 0 };

// convert RGB Color code expressed as uint8 number to bit-stream zero and ones
void neopixel_convert_RGB_to_bit_code(NEOPIXEL_t neopixe, uint16_t *bit_buffer) {
	// swap bits since we need MSB....LSB
	// Separating color green
	for (uint32_t i = 0; i < 8; i++) {
		if (neopixe.color_code_green & (1 << i)) {
			bit_buffer[7 - i] = 1;
		} else {
			bit_buffer[7 - i] = 0;
		}
	}
	// Separating color red
	for (uint32_t i = 0; i < 8; i++) {
		if (neopixe.color_code_red & (1 << i)) {
			bit_buffer[7 - i + 8] = 1;
		} else {
			bit_buffer[7 - i + 8] = 0;
		}
	}
	// Separating color blue
	for (uint32_t i = 0; i < 8; i++) {
		if (neopixe.color_code_blue & (1 << i)) {
			bit_buffer[7 - i + 16] = 1;
		} else {
			bit_buffer[7 - i + 16] = 0;
		}
	}
}

void neopixel_convert_bool_to_spi_frame(uint16_t *bit_buffer, uint32_t length) {
	for (uint32_t i = 0; i < length; i++) {
		if (bit_buffer[i] == 1)
			bit_buffer[i] = HIGH;
		else {
			bit_buffer[i] = LOW;
		}
	}
}

void neopixel_duplicate_bit_pattern(uint16_t *bit_buffer_single_neopixel, uint16_t *bit_buffer_target, uint32_t no_of_copies) {
	const uint16_t neopixel_bit_frame_size = 24;
	for (uint32_t i = 0; i < no_of_copies; ++i) {
		memcpy(&bit_buffer_target[i * neopixel_bit_frame_size], bit_buffer_single_neopixel, neopixel_bit_frame_size * 2);
	}
}

void neopixel_set_color(NEOPIXEL_t* pixel, RGB8_t rgb)
{
	pixel->color_code_red = rgb.color_code_red;
	pixel->color_code_green = rgb.color_code_green;
	pixel->color_code_blue = rgb.color_code_blue;

}

uint16_t neopixel_buffer_all_green[LENGTH] = {
//    MSB................................LSB
HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH,
LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW,
LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, };

uint16_t neopixel_buffer_all_red[LENGTH] = {
LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW,
HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH,
LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, };

uint16_t neopixel_buffer_all_blue[LENGTH] = {
LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW,
LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW,
HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, };

uint16_t neopixel_buffer_all_white[LENGTH] = {
HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH,
HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH,
HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, };

uint16_t neopixel_buffer_all_off[LENGTH] = {
LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW,
LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW,
LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, };

uint16_t neopixel_spi_buffer[LENGTH] = {NEO_RESET};

/* very easy straight forward routine to test all colors
 * offset of 3 is becaus neopixel LED's need a reset frame, here the lib sends three reset frames to make sure
 * since some neopix of different vendors behave little different */
void neopixel_demo(void) {
	neopixel_duplicate_bit_pattern(neopixel_buffer_all_white, &neopixel_spi_buffer[3], NO_OF_LEDS);
	NEOPIXEL_SNED_BUFFER((uint8_t*)neopixel_spi_buffer, LENGTH);
	NEOPIXEL_DELAY(2000);

	neopixel_duplicate_bit_pattern(neopixel_buffer_all_blue, &neopixel_spi_buffer[3], NO_OF_LEDS);
	NEOPIXEL_SNED_BUFFER((uint8_t*)neopixel_spi_buffer, LENGTH);
	NEOPIXEL_DELAY(2000);

	neopixel_duplicate_bit_pattern(neopixel_buffer_all_green, &neopixel_spi_buffer[3], NO_OF_LEDS);
	NEOPIXEL_SNED_BUFFER((uint8_t*)neopixel_spi_buffer, LENGTH);
	NEOPIXEL_DELAY(2000);

	neopixel_duplicate_bit_pattern(neopixel_buffer_all_red, &neopixel_spi_buffer[3], NO_OF_LEDS);
	NEOPIXEL_SNED_BUFFER((uint8_t*)neopixel_spi_buffer, LENGTH);
	NEOPIXEL_DELAY(2000);

	neopixel_duplicate_bit_pattern(neopixel_buffer_all_off, &neopixel_spi_buffer[3], NO_OF_LEDS);
	NEOPIXEL_SNED_BUFFER((uint8_t*)neopixel_spi_buffer, LENGTH);
	NEOPIXEL_DELAY(2000);
}
