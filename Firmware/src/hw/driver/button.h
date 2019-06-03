/*
 * button.h
 *
 *  Created on: 2019. 6. 3.
 *      Author: Baram
 */

#ifndef SRC_HW_DRIVER_BUTTON_H_
#define SRC_HW_DRIVER_BUTTON_H_

#include "hw_def.h"


#define BUTTON_MAX_CH       1


void buttonInit(void);
bool buttonGetPressed(uint8_t ch);

#endif /* SRC_HW_DRIVER_BUTTON_H_ */
