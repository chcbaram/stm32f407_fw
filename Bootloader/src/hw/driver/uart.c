/*
 * uart.c
 *
 *  Created on: 2019. 6. 3.
 *      Author: Baram
 */


#include "uart.h"


extern uint32_t cdcAvailable(void);
extern uint32_t cdcGetBaud(void);
extern uint8_t  cdcRead(void);
extern uint32_t cdcWrite(uint8_t *p_data, uint32_t length);



void uartInit(void)
{

}

bool uartOpen(uint8_t ch, uint32_t baud)
{
  return true;
}

uint32_t uartAvailable(uint8_t ch)
{
  return cdcAvailable();
}

uint32_t uartGetBaud(uint8_t ch)
{
  return cdcGetBaud();
}

uint8_t uartRead(uint8_t ch)
{
  return cdcRead();
}

uint32_t uartWrite(uint8_t ch, uint8_t *p_data, uint32_t length)
{
  return cdcWrite(p_data, length);
}

void uartPutch(uint8_t ch, uint8_t data)
{
  uartWrite(ch, &data, 1);
}

uint8_t uartGetch(uint8_t ch)
{
  while(uartAvailable(ch) <= 0);

  return uartRead(ch);
}

void uartPrintf(uint8_t ch, char *fmt, ...)
{
  char buf[256];
  va_list args;
  int len;

  va_start(args, fmt);
  len = vsnprintf(buf, 256, fmt, args);

  uartWrite(ch, (uint8_t *)buf, len);

  va_end(args);
}

