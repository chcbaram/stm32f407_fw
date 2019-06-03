/*
 * led.h
 *
 *  Created on: 2019. 6. 3.
 *      Author: Baram
 */

#ifndef SRC_HW_DRIVER_LED_H_
#define SRC_HW_DRIVER_LED_H_


#include "hw_def.h"


#define LED_MAX_CH          1

void ledInit(void);
void ledOn(uint8_t ch);
void ledOff(uint8_t ch);
void ledToggle(uint8_t ch);


#endif /* SRC_HW_DRIVER_LED_H_ */
