/*
 * uart.h
 *
 *  Created on: 2019. 6. 3.
 *      Author: Baram
 */

#ifndef SRC_HW_DRIVER_UART_H_
#define SRC_HW_DRIVER_UART_H_

#include "hw_def.h"


#define UART_MAX_CH           1


void     uartInit(void);
bool     uartOpen(uint8_t ch, uint32_t baud);
uint32_t uartGetBaud(uint8_t ch);
uint32_t uartAvailable(uint8_t ch);
uint8_t  uartRead(uint8_t ch);
void     uartPutch(uint8_t ch, uint8_t data);
uint8_t  uartGetch(uint8_t ch);
uint32_t uartWrite(uint8_t ch, uint8_t *p_data, uint32_t length);
void     uartPrintf(uint8_t ch, char *fmt, ...);

#endif /* SRC_HW_DRIVER_UART_H_ */
