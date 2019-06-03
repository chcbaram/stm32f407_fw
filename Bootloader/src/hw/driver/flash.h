/*
 * flash.h
 *
 *  Created on: 2019. 6. 3.
 *      Author: Baram
 */

#ifndef SRC_HW_DRIVER_FLASH_H_
#define SRC_HW_DRIVER_FLASH_H_

#include "hw_def.h"


void flashInit(void);
bool flashErase(uint32_t addr, uint32_t length);
bool flashWrite(uint32_t addr, uint8_t *p_data, uint32_t length);
bool flashRead(uint32_t addr, uint8_t *p_data, uint32_t length);

#endif /* SRC_HW_DRIVER_FLASH_H_ */
