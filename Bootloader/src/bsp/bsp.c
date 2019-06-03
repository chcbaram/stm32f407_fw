/*
 * bsp.c
 *
 *  Created on: 2019. 6. 3.
 *      Author: Baram
 */


#include "bsp.h"


extern void cubeInit(void);
extern void uartPutch(uint8_t ch, uint8_t data);
extern void usbDeInit(void);


void bspInit(void)
{
  cubeInit();
}

void bspDeInit(void)
{
  usbDeInit();
  HAL_RCC_DeInit();
  HAL_DeInit();
}

void delay(uint32_t ms)
{
  HAL_Delay(ms);
}

uint32_t millis(void)
{
  return HAL_GetTick();
}

int __io_putchar(int ch)
{
  uartPutch(_DEF_UART1, ch);

  return 1;
}
