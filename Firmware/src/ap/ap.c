/*
 * ap.c
 *
 *  Created on: 2019. 6. 3.
 *      Author: Baram
 */


#include "ap.h"



typedef struct
{
  uint8_t version_str[32];
  uint8_t board_str[32];
} fw_info_t;

const __attribute__((section(".version"))) fw_info_t fw_info = {"V190603R1", "STM32F407"};


void apInit(void)
{
}

void apMain(void)
{
  uint32_t pre_time;

  pre_time = millis();
  while(1)
  {
    if (millis()-pre_time >= 500)
    {
      pre_time = millis();
      ledToggle(_DEF_LED1);
    }
  }
}
