/*
 * flash.c
 *
 *  Created on: 2019. 6. 3.
 *      Author: Baram
 */


#include "flash.h"


#define FLASH_MAX_SECTOR          12


typedef struct
{
  int16_t  index;
  uint32_t addr;
  uint32_t length;
} flash_tbl_t;


flash_tbl_t flash_tbl[FLASH_MAX_SECTOR] =
    {
        {0, 0x08000000, 16*1024},
        {1, 0x08004000, 16*1024},
        {2, 0x08008000, 16*1024},
        {3, 0x0800C000, 16*1024},
        {4, 0x08010000, 64*1024},
        {5, 0x08020000, 128*1024},
        {6, 0x08040000, 128*1024},
        {7, 0x08060000, 128*1024},
        {8, 0x08080000, 128*1024},
        {9, 0x080A0000, 128*1024},
        {10,0x080C0000, 128*1024},
        {11,0x080E0000, 128*1024},
    };


void flashInit(void)
{

}

bool flashErase(uint32_t addr, uint32_t length)
{
  bool ret = true;

  int32_t start_sector = -1;
  int32_t end_sector = -1;


  HAL_FLASH_Unlock();

  for (int i=0; i<FLASH_MAX_SECTOR; i++)
  {
    bool update = false;
    uint32_t start_addr;
    uint32_t end_addr;


    start_addr = flash_tbl[i].addr;
    end_addr   = flash_tbl[i].addr + flash_tbl[i].length - 1;

    if (start_addr >= addr && start_addr < (addr+length))
    {
      update = true;
    }
    if (end_addr >= addr && end_addr < (addr+length))
    {
      update = true;
    }

    if (addr >= start_addr && addr <= end_addr)
    {
      update = true;
    }
    if ((addr+length-1) >= start_addr && (addr+length-1) <= end_addr)
    {
      update = true;
    }


    if (update == true)
    {
      if (start_sector < 0)
      {
        start_sector = i;
      }
      end_sector = i;
    }
  }

  if (start_sector >= 0)
  {
    FLASH_EraseInitTypeDef EraseInit;
    uint32_t SectorError;
    HAL_StatusTypeDef status;


    EraseInit.Sector       = start_sector;
    EraseInit.NbSectors    = (end_sector - start_sector) + 1;
    EraseInit.TypeErase    = FLASH_TYPEERASE_SECTORS;
    EraseInit.VoltageRange = FLASH_VOLTAGE_RANGE_3;

    status = HAL_FLASHEx_Erase(&EraseInit, &SectorError);
    if (status != HAL_OK)
    {
      ret = false;
    }
  }
  else
  {
    ret = false;
  }

  HAL_FLASH_Lock();

  return ret;
}

bool flashWrite(uint32_t addr, uint8_t *p_data, uint32_t length)
{
  bool ret = true;


  HAL_FLASH_Unlock();

  for (int i=0; i<length; i++)
  {
    HAL_StatusTypeDef status;

    status = HAL_FLASH_Program(FLASH_TYPEPROGRAM_BYTE, addr + i, (uint64_t)p_data[i]);
    if (status != HAL_OK)
    {
      ret = false;
      break;
    }
  }

  HAL_FLASH_Lock();

  return ret;
}

bool flashRead(uint32_t addr, uint8_t *p_data, uint32_t length)
{
  bool ret = true;
  uint8_t *p_byte = (uint8_t *)addr;


  for (int i=0; i<length; i++)
  {
    p_data[i] = p_byte[i];
  }

  return ret;
}
