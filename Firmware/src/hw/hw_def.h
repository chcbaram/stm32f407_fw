/*
 * hw_def.h
 *
 *  Created on: 2019. 6. 3.
 *      Author: Baram
 */

#ifndef SRC_HW_HW_DEF_H_
#define SRC_HW_HW_DEF_H_

#include "def.h"
#include "bsp.h"

#define logPrintf(...)    printf(__VA_ARGS__)


#define FLASH_ADDR_TAG      0x08020000
#define FLASH_ADDR_FW       0x08020400
#define FLASH_ADDR_FW_VER   0x08020800

#define FLASH_ADDR_START    0x08020000
#define FLASH_ADDR_END      0x08100000


#endif /* SRC_HW_HW_DEF_H_ */
