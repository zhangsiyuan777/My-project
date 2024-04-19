#ifndef _Bluetooth_phone_H
#define _Bluetooth_phone_H
#include "main.h"


#pragma pack(1)
typedef struct {
    uint8_t hand;
    uint8_t mode;
    int16_t right;
    int16_t down;
    int16_t left;
    int16_t upputter;
    uint8_t sum;
    uint8_t al;
}BluetoothRx_Typedef;
#pragma pack()
void Bluetooth_Rx(void);
extern uint8_t usart2_dma_buff[12],flash_flag;
void operate_flash(void * parameters);


#endif
