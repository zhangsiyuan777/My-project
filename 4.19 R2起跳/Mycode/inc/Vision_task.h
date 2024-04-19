#ifndef _VISION_TASK_H_
#define _VISION_TASK_H_

#include "FreeRTOS.h"
#include "cmsis_os.h"
#include "task.h"
#include "RMLibHead.h"
#include "RoboModule_DRV.h"
#include "stm32f4xx_hal.h"
#include "Odrive_Set.h"
#include "CANDrive.h"
#include "PID.h"
#include "motor.h"
#include "ramp.h"
#include "Chassis.h"

typedef struct {
	int32_t X;
	int32_t Y;
	int32_t Size;
	int32_t Distance;
} Vision_Typedef;

#pragma pack(1)
typedef struct {
    uint8_t head;
    int32_t X;
    int32_t Y;
    int32_t Size;
	int32_t Distance;
} VisionBack_Typedef;

typedef struct 
{
	int32_t X;
	int32_t Y;
	int32_t Z;
}Vision_control;

typedef enum
{
	Adjusting_head=0,
	Adjusting_baseplate,
}Vision_Status;

#pragma pack()
//extern Expect_Speed_Typedef Expect_Speed;

void Visual_control(void);

extern float Ex_Y;
extern VisionBack_Typedef vision_t;
extern Vision_Typedef Vision_t;
extern Vision_Typedef vision_offest;
extern Vision_control My_Vison_control;
#endif
