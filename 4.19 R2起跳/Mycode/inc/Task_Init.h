#ifndef _TASK_INIT_H_
#define _TASK_INIT_H_

#include "main.h"
#include "FreeRTOS.h"
#include "task.h"
#include "stdio.h"
#include "math.h"
#include "queue.h"
#include "event_groups.h" 
#include "cmsis_os.h"

#include "usart.h"
#include "can.h"
#include "gpio.h"

#include "CANDrive.h"
#include "RoboModule_DRV.h"
#include "motor.h"
#include "CRC.h"
#include "RC_Remote.h"

void task_Init(void);    
extern uint8_t data1[17];
#endif
