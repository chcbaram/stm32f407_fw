/*
 * reset.c
 *
 *  Created on: 2019. 6. 4.
 *      Author: Baram
 */


#include "reset.h"


static uint8_t reset_status = 0x00;


void resetInit(void)
{
  uint8_t ret = 0;

  if (__HAL_RCC_GET_FLAG(RCC_FLAG_PINRST) != RESET)
  {
    ret |= (1<<_DEF_RESET_PIN);
  }
  if (__HAL_RCC_GET_FLAG(RCC_FLAG_BORRST) != RESET)
  {
    ret |= (1<<_DEF_RESET_POWER);
  }
  if (__HAL_RCC_GET_FLAG(RCC_FLAG_PORRST) != RESET)
  {
    ret |= (1<<_DEF_RESET_POWER);
  }
  if (__HAL_RCC_GET_FLAG(RCC_FLAG_IWDGRST) != RESET)
  {
    ret |= (1<<_DEF_RESET_WDG);
  }
  if (__HAL_RCC_GET_FLAG(RCC_FLAG_WWDGRST) != RESET)
  {
    ret |= (1<<_DEF_RESET_WDG);
  }
  if (__HAL_RCC_GET_FLAG(RCC_FLAG_SFTRST) != RESET)
  {
    ret |= (1<<_DEF_RESET_SOFT);
  }

  __HAL_RCC_CLEAR_RESET_FLAGS();



  if (ret & (1<<_DEF_RESET_WDG))
  {
    reset_status = _DEF_RESET_WDG;
  }
  else if (ret & (1<<_DEF_RESET_SOFT))
  {
    reset_status = _DEF_RESET_SOFT;
  }
  else if (ret & (1<<_DEF_RESET_PIN))
  {
    reset_status = _DEF_RESET_PIN;
  }
  else
  {
    reset_status = _DEF_RESET_POWER;
  }
}

void resetRunSoftReset(void)
{
  HAL_NVIC_SystemReset();
}

void resetClearFlag(void)
{
  __HAL_RCC_CLEAR_RESET_FLAGS();
}

uint8_t resetGetStatus(void)
{
  return reset_status;
}
