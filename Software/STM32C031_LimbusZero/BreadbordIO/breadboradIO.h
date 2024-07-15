/*
 * breadboradIO.h
 *
 *  Created on: Jul 7, 2024
 *      Author: lukas
 */

#ifndef BREADBORADIO_H_
#define BREADBORADIO_H_

#include <stdint.h>

/* public variables */
extern uint8_t g_main_increment_counter;
extern uint32_t g_adc_raw_values[5];

typedef enum __op_modes{
	eINCREMENT = 0, eGAUGE, eKNIGHTRIDER, eSNAKE, eLASTBLINK, eNEOPIXEL,

	eOP_MODE_MAX,
} op_modes_t;

typedef enum __neopixel_states {
	eRED, eGREEN, eBLUE, eMIXED,
} neopixel_states_t;

typedef enum __increment_direction {
	eUP, eDOWN,
} increment_direction_t;

/* houskeeping */
void breadboardIO_init(void);
void breadboarIO_set_neopixel_increment_counter(increment_direction_t direction);
void breadboarIO_set_global_increment_counter(increment_direction_t direction);

/* FSM sub routines */
void breadbordIO_set_leds(uint8_t led_code);
void breadboardIO_poti_gauge_action(uint32_t poti);
void breadbordIO_knightrider(void);
void breadbordIO_snake(void);
void breadbordIO_last_blink(void);
void bradbordIO_neopixel(void);


/* interrupt callbacks */
void breadbordIO_button_interrupt_callback(uint16_t GPIO_Pin);
void breadboardIO_FSM(void);

#endif /* BREADBORADIO_H_ */
