/*
 * button.c
 *
 *  Created on: 2019. 6. 3.
 *      Author: Baram
 */


#include "button.h"



typedef struct
{
  GPIO_TypeDef *GPIOx;
  uint16_t      GPIO_Pin;
  GPIO_PinState on_state;
} button_tbl_t;


button_tbl_t button_tbl[BUTTON_MAX_CH] =
    {
        {GPIOA, GPIO_PIN_0,  GPIO_PIN_SET},
    };


void buttonInit(void)
{

}

bool buttonGetPressed(uint8_t ch)
{
  GPIO_PinState button_state;

  button_state = HAL_GPIO_ReadPin(button_tbl[ch].GPIOx, button_tbl[ch].GPIO_Pin);

  if (button_state == button_tbl[ch].on_state)
  {
    return true;
  }
  else
  {
    return false;
  }
}
