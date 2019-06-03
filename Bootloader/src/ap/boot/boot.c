/*
 * boot.c
 *
 *  Created on: 2019. 6. 4.
 *      Author: Baram
 */


#include "boot.h"



#define BOOT_CMD_READ_VERSION           0x00
#define BOOT_CMD_READ_BOARD_NAME        0x01
#define BOOT_CMD_FLASH_ERASE            0x02
#define BOOT_CMD_FLASH_WRITE            0x03
#define BOOT_CMD_JUMP_TO_FW             0x08



static void bootCmdReadVersion(cmd_t *p_cmd);
static void bootCmdReadBoardName(cmd_t *p_cmd);
static void bootCmdFlashErase(cmd_t *p_cmd);
static void bootCmdFlashWrite(cmd_t *p_cmd);
static void bootCmdJumpToFw(cmd_t *p_cmd);



bool bootCheckFw(void);
void bootJumpToFw(void);






void bootInit(void)
{
}


void bootJumpToFw(void)
{
  void (**jump_func)(void) = (void (**)(void))(FLASH_ADDR_FW + 4);

  bspDeInit();
  (*jump_func)();
}

bool bootVerifyFw(void)
{
  void (**jump_func)(void) = (void (**)(void))(FLASH_ADDR_FW + 4);


  if ((uint32_t)(*jump_func) != 0xFFFFFFFF)
  {
    return true;
  }
  else
  {
    return false;
  }
}

void bootCmdReadVersion(cmd_t *p_cmd)
{
  uint8_t *fw_version_str = (uint8_t *)FLASH_ADDR_FW_VER;

  cmdSendResp(p_cmd, OK, fw_version_str, 9);
}

void bootCmdReadBoardName(cmd_t *p_cmd)
{
  uint8_t *data = (uint8_t *)(FLASH_ADDR_FW_VER + 32);


  cmdSendResp(p_cmd, OK, data, 32);
}

void bootCmdFlashErase(cmd_t *p_cmd)
{
  uint8_t err_code = OK;
  uint32_t addr_begin;
  uint32_t addr_end;
  uint32_t length;


  addr_begin  = p_cmd->rx_packet.data[0]<<0;
  addr_begin |= p_cmd->rx_packet.data[1]<<8;
  addr_begin |= p_cmd->rx_packet.data[2]<<16;
  addr_begin |= p_cmd->rx_packet.data[3]<<24;

  length      = p_cmd->rx_packet.data[4]<<0;
  length     |= p_cmd->rx_packet.data[5]<<8;
  length     |= p_cmd->rx_packet.data[6]<<16;
  length     |= p_cmd->rx_packet.data[7]<<24;

  addr_end    = addr_begin + length - 1;


  if ((addr_begin >= FLASH_ADDR_START) && (addr_begin < FLASH_ADDR_END) &&
      (addr_end   >= FLASH_ADDR_START) && (addr_end   < FLASH_ADDR_END))
  {
    if (flashErase(addr_begin, length) == false)
    {
      err_code = ERR_FLASH_ERASE;
    }
  }
  else
  {
    err_code = ERR_FLASH_INVALID_ADDR;
  }

  cmdSendResp(p_cmd, err_code, NULL, 0);

}

void bootCmdFlashWrite(cmd_t *p_cmd)
{
  uint8_t err_code = OK;
  uint32_t addr_begin;
  uint32_t addr_end;
  uint32_t length;


  addr_begin  = p_cmd->rx_packet.data[0]<<0;
  addr_begin |= p_cmd->rx_packet.data[1]<<8;
  addr_begin |= p_cmd->rx_packet.data[2]<<16;
  addr_begin |= p_cmd->rx_packet.data[3]<<24;

  length      = p_cmd->rx_packet.data[4]<<0;
  length     |= p_cmd->rx_packet.data[5]<<8;
  length     |= p_cmd->rx_packet.data[6]<<16;
  length     |= p_cmd->rx_packet.data[7]<<24;

  addr_end    = addr_begin + length - 1;


  if ((addr_begin >= FLASH_ADDR_START) && (addr_begin < FLASH_ADDR_END) &&
      (addr_end   >= FLASH_ADDR_START) && (addr_end   < FLASH_ADDR_END))
  {
    if (flashWrite(addr_begin, &p_cmd->rx_packet.data[8], length) == false)
    {
      err_code = ERR_FLASH_WRITE;
    }
  }
  else
  {
    err_code = ERR_FLASH_INVALID_ADDR;
  }

  cmdSendResp(p_cmd, err_code, NULL, 0);
}

void bootCmdJumpToFw(cmd_t *p_cmd)
{
  if (bootVerifyFw() == true)
  {
    cmdSendResp(p_cmd, OK, NULL, 0);
    delay(100);
    bootJumpToFw();
  }
  else
  {
    cmdSendResp(p_cmd, ERR_INVALID_FW, NULL, 0);
  }
}

void bootProcessCmd(cmd_t *p_cmd)
{
  switch(p_cmd->rx_packet.cmd)
  {
    case BOOT_CMD_READ_VERSION:
      bootCmdReadVersion(p_cmd);
      break;

    case BOOT_CMD_READ_BOARD_NAME:
      bootCmdReadBoardName(p_cmd);
      break;

    case BOOT_CMD_FLASH_ERASE:
      bootCmdFlashErase(p_cmd);
      break;

    case BOOT_CMD_FLASH_WRITE:
      bootCmdFlashWrite(p_cmd);
      break;

    case BOOT_CMD_JUMP_TO_FW:
      bootCmdJumpToFw(p_cmd);
      break;


    default:
      cmdSendResp(p_cmd, ERR_INVALID_CMD, NULL, 0);
      break;
  }
}
