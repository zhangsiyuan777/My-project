#ifndef _MY_REMOTE_H_
#define _MY_REMOTE_H_

#include "main.h"
#include "cmsis_os.h"
#include "can.h"
#include "dma.h"
#include "usart.h"
#include "usb_device.h"
#include "gpio.h"

#include "WatchDog.h"
#include "RoboModule_DRV.h"
#include "CANDrive.h"



#pragma pack(1)
typedef struct
{
  uint16_t Left_Key_Up : 1;
  uint16_t Left_Key_Down : 1;
  uint16_t Left_Key_Left : 1;
  uint16_t Left_Key_Right : 1;
  uint16_t Left_Rocker : 1;
  uint16_t Left_Encoder : 1;
  uint16_t Left_Switch_Up : 1;
  uint16_t Left_Switch_Down : 1;  
  uint16_t Right_Key_Up : 1;
  uint16_t Right_Key_Down : 1;
  uint16_t Right_Key_Left : 1;
  uint16_t Right_Key_Right : 1;
  uint16_t Right_Rocker : 1;
  uint16_t Right_Encoder : 1;
  uint16_t Right_Switch_Up : 1;
  uint16_t Right_Switch_Down : 1;  
  } hw_key_t;

typedef struct {
	uint8_t head;
	uint16_t rocker[4];
	hw_key_t Key;
	uint32_t Left_Encoder;
	uint32_t Right_Encoder;
  uint16_t crc;
} UART_DataPack;

#pragma pack()

typedef struct {
    int16_t Ex;
    int16_t Ey;
    int16_t Eangle;
    hw_key_t *Key_Control;
    hw_key_t First,Second;
} Remote_Handle_t;

typedef struct
{
 double Expect_Speed_X;
 double Expect_Speed_Y;
 double Expect_Speed_Yaw;
} Expect_Speed_Typedef;



extern uint8_t usart4_dma_buff[21];
extern UART_DataPack RemoteData;
extern Remote_Handle_t Remote_Control;
extern RoboModule_Typedef MI,MII,MIII;



#endif
