#ifndef _RC_REMOTE_H_
#define _RC_REMOTE_H_

#include "Task_Init.h"
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

typedef enum {
     START,
     LASER_SELF,
     LASER_left,
     LASER_right,
     STP,
     STOP,
     REMOTE,
     NEXT,
     CHOOSE,
	 RADER,
	 GIMBAL,
	 VISION,
}Positon_label;
									
extern UART_DataPack Tx_RemoteData;
extern UART_DataPack RemoteData;
extern UART_DataPack VisionData; 
extern uint8_t usart4_dma_buff[21];
extern Remote_Handle_t Remote_Control;

extern Positon_label MODE;
void Updatakey(Remote_Handle_t * xx);
extern TaskHandle_t Remote_deal_Handler;
extern TaskHandle_t vPositon_deal_Handler;

void vRemote_deal(void * parameters);
void vPositon_deal(void * parameters);

#endif
