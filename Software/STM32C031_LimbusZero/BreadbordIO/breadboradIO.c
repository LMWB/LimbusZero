/*
 * breadboradIO.c
 *
 *  Created on: Jul 7, 2024
 *      Author: lukas
 */

#include <main.h>
#include <stm32c0xx_hal_gpio.h>
#include "spi.h"
#include "weICLED.h"
#include "breadboradIO.h"

/* Platform specific driver functions -> in my case STM32 with HAL */
void bredboard_driver_neopixel_send_data(uint8_t* bit_buffer, uint16_t length){

	//HAL_SPI_Transmit(&hspi1, bit_buffer, length, 500); // without DMA
	HAL_SPI_Transmit_DMA(&hspi1, bit_buffer, length); // with DMA
}

void bredboard_driver_set_GPIO(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin, GPIO_PinState PinState){
	HAL_GPIO_WritePin(GPIOx, GPIO_Pin, PinState);
}

void bredboard_driver_toggle_GPIO(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin){
	HAL_GPIO_TogglePin(GPIOx, GPIO_Pin);
}

uint8_t bredboard_driver_read_GPIO(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin){
	return (uint8_t) HAL_GPIO_ReadPin(GPIOx, GPIO_Pin);
}

#define INCREMENT_COUNTER_INIT	(64-1)

/* public variables */
uint8_t g_main_increment_counter = INCREMENT_COUNTER_INIT;
uint32_t g_adc_raw_values[5] = { 0 };

/* private variables */
static neopixel_states_t neopixel_state;
static op_modes_t breadboardIO_operation_mode;
static uint8_t red_increment_counter;
static uint8_t green_increment_counter;
static uint8_t blue_increment_counter;


void breadboardIO_init(void)
{
	breadboardIO_operation_mode = eKNIGHTRIDER;
	neopixel_state 				= eGREEN;

	red_increment_counter 		= INCREMENT_COUNTER_INIT;
	green_increment_counter 	= INCREMENT_COUNTER_INIT;
	blue_increment_counter 		= INCREMENT_COUNTER_INIT;
}

void breadbordIO_set_leds(uint8_t led_code) {
	bredboard_driver_set_GPIO(Out1_GPIO_Port, Out1_Pin, led_code & 0x01);
	bredboard_driver_set_GPIO(Out2_GPIO_Port, Out2_Pin, led_code & 0x02);
	bredboard_driver_set_GPIO(Out3_GPIO_Port, Out3_Pin, led_code & 0x04);
	bredboard_driver_set_GPIO(Out4_GPIO_Port, Out4_Pin, led_code & 0x08);

	bredboard_driver_set_GPIO(Out5_GPIO_Port, Out5_Pin, led_code & 0x10);
	bredboard_driver_set_GPIO(Out6_GPIO_Port, Out6_Pin, led_code & 0x20);
	bredboard_driver_set_GPIO(Out7_GPIO_Port, Out7_Pin, led_code & 0x40);
	bredboard_driver_set_GPIO(Out8_GPIO_Port, Out8_Pin, led_code & 0x80);
}

static void bradbordIO_increment_encoder_action(void) {
	if( bredboard_driver_read_GPIO(IncB_GPIO_Port, IncB_Pin) == GPIO_PIN_RESET ) {
		/* counting up */
		/* the main increment counter is only supposed to count up/down when not NEOPIXEL-Mode*/
		if(breadboardIO_operation_mode == eNEOPIXEL){
			breadboarIO_set_neopixel_increment_counter(eDOWN);
		}else{
			breadboarIO_set_global_increment_counter(eDOWN);
		}
	} else {
		/* counting down */
		if(breadboardIO_operation_mode == eNEOPIXEL){
			breadboarIO_set_neopixel_increment_counter(eUP);
		}
		else{
			breadboarIO_set_global_increment_counter(eUP);
		}
	}
}

void breadboardIO_poti_gauge_action(uint32_t poti) {
	bredboard_driver_set_GPIO(Out1_GPIO_Port, Out1_Pin, 0);
	bredboard_driver_set_GPIO(Out2_GPIO_Port, Out2_Pin, 0);
	bredboard_driver_set_GPIO(Out3_GPIO_Port, Out3_Pin, 0);
	bredboard_driver_set_GPIO(Out4_GPIO_Port, Out4_Pin, 0);

	bredboard_driver_set_GPIO(Out5_GPIO_Port, Out5_Pin, 0);
	bredboard_driver_set_GPIO(Out6_GPIO_Port, Out6_Pin, 0);
	bredboard_driver_set_GPIO(Out7_GPIO_Port, Out7_Pin, 0);
	bredboard_driver_set_GPIO(Out8_GPIO_Port, Out8_Pin, 0);

	if (poti > 512) {
		bredboard_driver_set_GPIO(Out1_GPIO_Port, Out1_Pin, 1);
	}

	if (poti > 1024) {
		bredboard_driver_set_GPIO(Out2_GPIO_Port, Out2_Pin, 1);
	}

	if (poti > 1536) {
		bredboard_driver_set_GPIO(Out3_GPIO_Port, Out3_Pin, 1);
	}

	if (poti > 2048) {
		bredboard_driver_set_GPIO(Out4_GPIO_Port, Out4_Pin, 1);
	}

	if (poti > 2560) {
		bredboard_driver_set_GPIO(Out5_GPIO_Port, Out5_Pin, 1);
	}

	if (poti > 3072) {
		bredboard_driver_set_GPIO(Out6_GPIO_Port, Out6_Pin, 1);
	}

	if (poti > 3584) {
		bredboard_driver_set_GPIO(Out7_GPIO_Port, Out7_Pin, 1);
	}

	if (poti > 4096 - 30) {
		bredboard_driver_set_GPIO(Out8_GPIO_Port, Out8_Pin, 1);
	}
}

void breadbordIO_snake(void) {
	static uint8_t count = 0;
	static uint16_t timer = 0;
	timer++;
	if (timer > g_main_increment_counter) {
		uint32_t snake = (0xff << count);

		snake = snake >> 8;
		bredboard_driver_set_GPIO(Out1_GPIO_Port, Out1_Pin, snake & 0x01);
		bredboard_driver_set_GPIO(Out2_GPIO_Port, Out2_Pin, snake & 0x02);
		bredboard_driver_set_GPIO(Out3_GPIO_Port, Out3_Pin, snake & 0x04);
		bredboard_driver_set_GPIO(Out4_GPIO_Port, Out4_Pin, snake & 0x08);

		bredboard_driver_set_GPIO(Out5_GPIO_Port, Out5_Pin, snake & 0x10);
		bredboard_driver_set_GPIO(Out6_GPIO_Port, Out6_Pin, snake & 0x20);
		bredboard_driver_set_GPIO(Out7_GPIO_Port, Out7_Pin, snake & 0x40);
		bredboard_driver_set_GPIO(Out8_GPIO_Port, Out8_Pin, snake & 0x80);
		timer = 0;
		count++;

		/* restart condition, snake has run through */
		if (count >= 16) {
			count = 0;
		}
	}
}

void breadbordIO_knightrider(void) {
	static int8_t count = 0;
	static uint16_t timer = 0;
	static uint8_t dir = 0;
	timer++;
	if (timer > g_main_increment_counter) {
		uint32_t knightrider = (0x01 << count);

		bredboard_driver_set_GPIO(Out1_GPIO_Port, Out1_Pin, knightrider & 0x01);
		bredboard_driver_set_GPIO(Out2_GPIO_Port, Out2_Pin, knightrider & 0x02);
		bredboard_driver_set_GPIO(Out3_GPIO_Port, Out3_Pin, knightrider & 0x04);
		bredboard_driver_set_GPIO(Out4_GPIO_Port, Out4_Pin, knightrider & 0x08);

		bredboard_driver_set_GPIO(Out5_GPIO_Port, Out5_Pin, knightrider & 0x10);
		bredboard_driver_set_GPIO(Out6_GPIO_Port, Out6_Pin, knightrider & 0x20);
		bredboard_driver_set_GPIO(Out7_GPIO_Port, Out7_Pin, knightrider & 0x40);
		bredboard_driver_set_GPIO(Out8_GPIO_Port, Out8_Pin, knightrider & 0x80);
		timer = 0;


		/* decision making on direction of LED */
		if(knightrider == 0x80){
			dir = 1;
		}

		if(knightrider == 0x01){
			dir = 0;
		}

		/* moving the LED up and down */
		if(dir == 0){
			count++;
		}else{
			count--;
		}
	}
}

void breadboardIO_set_neopixel_state(neopixel_states_t newState){

	if(neopixel_state == newState){
		neopixel_state = eMIXED;
	}else{
		neopixel_state = newState;
	}
}

void breadboarIO_set_global_increment_counter(increment_direction_t direction) {
	if (direction == eUP) {
		if (g_main_increment_counter < 0xff) {
			g_main_increment_counter++;
		}
	} else {
		if (g_main_increment_counter > 0) {
			g_main_increment_counter--;
		}
	}
}

void breadboarIO_set_neopixel_increment_counter(increment_direction_t direction){
	switch (neopixel_state) {
		case eRED:
			if(direction == eUP){
				red_increment_counter++;
			}else{
				red_increment_counter--;
			}
			break;
		case eGREEN:
			if(direction == eUP){
				green_increment_counter++;
			}else{
				green_increment_counter--;
			}
			break;
		case eBLUE:
			if(direction == eUP){
				blue_increment_counter++;
			}else
				blue_increment_counter--;
			break;
		default:
			break;
	}
}

void bradbordIO_neopixel(void) {

	uint16_t bit_buffer[LENGTH] = { 0 };	// working buffer to convert RGB-Color to ICLED Bit Frame
	NEOPIXEL_t neopix = {0};				// working variable

	switch (neopixel_state) {
	case eRED:
		breadbordIO_set_leds(red_increment_counter);
		neopix.color_code_blue = 0;
		neopix.color_code_green = 0;
		neopix.color_code_red = red_increment_counter;

		neopixel_convert_RGB_to_bit_code(neopix, bit_buffer);
		neopixel_convert_bool_to_spi_frame(bit_buffer, LENGTH);
		neopixel_duplicate_bit_pattern(bit_buffer, &neopixel_spi_buffer[3], NO_OF_LEDS);

		bredboard_driver_neopixel_send_data( (uint8_t*)neopixel_spi_buffer, LENGTH);
		break;
	case eGREEN:
		breadbordIO_set_leds(green_increment_counter);
		neopix.color_code_blue = 0;
		neopix.color_code_green = green_increment_counter;
		neopix.color_code_red = 0;

		neopixel_convert_RGB_to_bit_code(neopix, bit_buffer);
		neopixel_convert_bool_to_spi_frame(bit_buffer, LENGTH);
		neopixel_duplicate_bit_pattern(bit_buffer, &neopixel_spi_buffer[3], NO_OF_LEDS);

		bredboard_driver_neopixel_send_data( (uint8_t*)neopixel_spi_buffer, LENGTH);
		break;
	case eBLUE:
		breadbordIO_set_leds(blue_increment_counter);

		neopix.color_code_blue = blue_increment_counter;
		neopix.color_code_green = 0;
		neopix.color_code_red = 0;

		neopixel_convert_RGB_to_bit_code(neopix, bit_buffer);
		neopixel_convert_bool_to_spi_frame(bit_buffer, LENGTH);
		neopixel_duplicate_bit_pattern(bit_buffer, &neopixel_spi_buffer[3], NO_OF_LEDS);

		bredboard_driver_neopixel_send_data( (uint8_t*)neopixel_spi_buffer, LENGTH);
		break;
	case eMIXED:
		breadbordIO_set_leds(0);

		neopix.color_code_blue = blue_increment_counter;
		neopix.color_code_green = green_increment_counter;
		neopix.color_code_red = red_increment_counter;

		neopixel_convert_RGB_to_bit_code(neopix, bit_buffer);
		neopixel_convert_bool_to_spi_frame(bit_buffer, LENGTH);
		neopixel_duplicate_bit_pattern(bit_buffer, &neopixel_spi_buffer[3], NO_OF_LEDS);

		bredboard_driver_neopixel_send_data( (uint8_t*)neopixel_spi_buffer, LENGTH);
		break;
	default:
		break;
	}

}

/* the last LED pattern which was shown, will blink from know on */
void breadbordIO_last_blink(void) {
	static uint16_t timer = 0;
	timer++;
	if (timer > g_main_increment_counter) {
		bredboard_driver_toggle_GPIO(Out1_GPIO_Port, Out1_Pin);
		bredboard_driver_toggle_GPIO(Out2_GPIO_Port, Out2_Pin);
		bredboard_driver_toggle_GPIO(Out3_GPIO_Port, Out3_Pin);
		bredboard_driver_toggle_GPIO(Out4_GPIO_Port, Out4_Pin);

		bredboard_driver_toggle_GPIO(Out5_GPIO_Port, Out5_Pin);
		bredboard_driver_toggle_GPIO(Out6_GPIO_Port, Out6_Pin);
		bredboard_driver_toggle_GPIO(Out7_GPIO_Port, Out7_Pin);
		bredboard_driver_toggle_GPIO(Out8_GPIO_Port, Out8_Pin);
		timer = 0;
	}
}

void breadboardIO_FSM(void) {
	/* execute always */
	__NOP();

	/* execute depending on mode */
	switch (breadboardIO_operation_mode) {
	case eINCREMENT:
		breadbordIO_set_leds(g_main_increment_counter);
		break;
	case eGAUGE:
		breadboardIO_poti_gauge_action(g_adc_raw_values[0]);
		break;
	case eKNIGHTRIDER:
		breadbordIO_knightrider();
		break;
	case eSNAKE:
		breadbordIO_snake();
		break;
	case eLASTBLINK:
		breadbordIO_last_blink();
		break;
	case eNEOPIXEL:
		bradbordIO_neopixel();
		break;
	default:
		break;
	}
}
void breadbordIO_button_interrupt_callback(uint16_t GPIO_Pin) {

	if (GPIO_Pin == B1_Pin) {
		breadboardIO_operation_mode++;
		if (breadboardIO_operation_mode == eOP_MODE_MAX) {
			breadboardIO_operation_mode = eINCREMENT;
		}

	} else if (GPIO_Pin == B2_Pin) {
		breadboardIO_set_neopixel_state(eRED);
	} else if (GPIO_Pin == B3_Pin) {
		breadboardIO_set_neopixel_state(eGREEN);
	} else if (GPIO_Pin == B4_Pin) {
		breadboardIO_set_neopixel_state(eBLUE);
	} else if (GPIO_Pin == IncA_Pin) {
		bradbordIO_increment_encoder_action();
	}
}
