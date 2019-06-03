/*
 * reset.h
 *
 *  Created on: 2019. 6. 4.
 *      Author: Baram
 */

#ifndef SRC_HW_DRIVER_RESET_H_
#define SRC_HW_DRIVER_RESET_H_

#include "hw_def.h"


void resetInit(void);
void resetRunSoftReset(void);
void resetClearFlag(void);
uint8_t resetGetStatus(void);

#endif /* SRC_HW_DRIVER_RESET_H_ */
