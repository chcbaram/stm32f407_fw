/*
 * ap.c
 *
 *  Created on: 2018. 8. 25.
 *      Author: Baram
 */




#include "ap.h"





char file_version[32];
char file_board[32];


int32_t getFileSize(char *file_name);



void apInit(void)
{

}

void apMain(int argc, char *argv[])
{
  bool ret;
  char *port_name;
  char *file_name;
  int baud;
  int fw_size;
  uint8_t  block_buf[FLASH_TX_BLOCK_LENGTH];
  uint8_t  version_str[128];
  uint8_t  board_str[128
                     ];
  static FILE *fp;
  uint8_t errcode;
  uint32_t time_pre;
  bool flash_write_done;
  uint32_t addr;
  size_t readbytes;
  uint32_t percent;
  uint32_t len;


  if (argc != 4)
  {
    printf("downloader.exe com1 115200 firmware.binary\n");
    return;
  }

  port_name = (char *)argv[ 1 ];
  baud      = strtol( argv[ 2 ], NULL, 10 );
  file_name = (char *)argv[ 3 ];


  fw_size = getFileSize(file_name);

  printf("downloader...\n\n");

  printf("file open\n");
  printf("  file name \t: %s \n", file_name);
  printf("  file size \t: %d KB\n", fw_size/1024);
  printf("  file ver  \t: %s\n", file_version);
  printf("  file board\t: %s\n", file_board);


  printf("port open \t: %s\n", port_name);

  ret = bootInit(_DEF_UART2, port_name, baud);
  if (ret == true)
  {
    printf("bootInit \t: OK\n");
  }
  else
  {
    printf("bootInit  Fail\n");
    return;
  }


  while(1)
  {
    //-- 버전 확인
    //
    errcode = bootCmdReadVersion(version_str);
    if (errcode == OK)
    {
      printf("version \t: %s\n", &version_str[0]);
    }
    else
    {
      printf("bootCmdReadVersion faild \n");
      break;
    }

    //-- 보드 이름 확인
    //
    errcode = bootCmdReadBoardName(board_str);
    if (errcode == OK)
    {
      printf("board name \t: %s\n", board_str);
    }
    else
    {
      printf("bootCmdReadBoardName faild \n");
      break;
    }


    //-- Flash Erase
    //
    printf("erase fw...\n");
    time_pre = millis();
    errcode = bootCmdFlashErase(FLASH_FW_ADDR_START, fw_size);
    if (errcode == OK)
    {
      printf("erase fw ret \t: OK (%d ms)\n", millis()-time_pre);
    }
    else
    {
      printf("bootCmdFlashEraseFw faild : %d\n", errcode);
      break;
    }


    //-- Flash Write
    //
    if( ( fp = fopen( file_name, "rb" ) ) == NULL )
    {
      fprintf( stderr, "Unable to open %s\n", file_name );
      exit( 1 );
    }


    flash_write_done = false;
    addr = FLASH_FW_ADDR_START;
    time_pre = millis();
    while(1)
    {
      if( !feof( fp ) )
      {
        readbytes = fread( block_buf, 1, FLASH_TX_BLOCK_LENGTH, fp );
        percent = (addr+readbytes-FLASH_FW_ADDR_START)*100/fw_size;
        printf("flash fw \t: %d %%\r", percent);
      }
      else
      {
        break;
      }

      if( readbytes == 0 )
      {
        break;
      }
      else
      {
        len = readbytes;
      }


      for (int retry=0; retry<3; retry++)
      {
        errcode = bootCmdFlashWrite(addr, block_buf, len);
        if( errcode == OK )
        {
          break;
        }
        else
        {
          printf("err_code \t: %d \n", errcode);
        }
      }
      if( errcode != OK )
      {
        break;
      }

      addr += len;

      if ((addr-FLASH_FW_ADDR_START) == fw_size)
      {
        flash_write_done = true;
        break;
      }
    }
    fclose(fp);

    printf("\r\n");

    if( errcode != OK || flash_write_done == false )
    {
      printf("flash fw fail \t: %d\r\n", errcode);
      break;
    }
    else
    {
      printf("flash fw ret \t: OK (%d ms) \r\n", millis()-time_pre);
    }


    if( errcode != OK || flash_write_done == false )
    {
      printf("Download \t: Fail\r\n");
      return;
    }
    else
    {
      printf("Download \t: OK\r\n");
    }


    errcode = bootCmdJumpToFw();
    if (errcode == OK)
    {
        printf("jump to fw \t: OK\n");
    }
    else
    {
      printf("jump to fw fail : %d\n", errcode);
    }

    break;
  }


  uartClose(_DEF_UART2);
}

int32_t getFileSize(char *file_name)
{
  int32_t ret = -1;
  static FILE *fp;
  uint8_t block_buf[1024];

  if( ( fp = fopen( file_name, "rb" ) ) == NULL )
  {
    fprintf( stderr, "Unable to open %s\n", file_name );
    exit( 1 );
  }
  else
  {
    fread( block_buf, 1, 1024, fp );
    fread( block_buf, 1, 1024, fp );

    for (int i=0; i<32; i++)
    {
      file_version[i] = block_buf[i];
      file_board[i]   = block_buf[i+32];
    }

    fseek( fp, 0, SEEK_END );
    ret = ftell( fp );
    fseek( fp, 0, SEEK_SET );
    fclose(fp);
  }

  return ret;
}
