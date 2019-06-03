/*
 * hw.c
 *
 *  Created on: 2019. 6. 3.
 *      Author: Baram
 */


#include "hw.h"





void hwInit(void)
{
  bspInit();

  ledInit();
  uartInit();
  buttonInit();
  flashInit();
  resetInit();
}
