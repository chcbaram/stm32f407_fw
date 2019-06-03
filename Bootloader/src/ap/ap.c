/*
 * ap.c
 *
 *  Created on: 2019. 6. 3.
 *      Author: Baram
 */


#include "ap.h"
#include "boot/boot.h"


cmd_t cmd_boot;


void apInit(void)
{
  if (buttonGetPressed(_DEF_BUTTON1) != true)
  {
    if (resetGetStatus() != _DEF_RESET_SOFT)
    {
      bootJumpToFw();
    }
  }

  cmdInit(&cmd_boot);
  cmdBegin(&cmd_boot, _DEF_UART1, 115200);
}

void apMain(void)
{
  uint32_t pre_time;

  pre_time = millis();
  while(1)
  {
    if (millis()-pre_time >= 100)
    {
      pre_time = millis();
      ledToggle(_DEF_LED1);
    }

    if (cmdReceivePacket(&cmd_boot) == true)
    {
      bootProcessCmd(&cmd_boot);
    }
  }
}
