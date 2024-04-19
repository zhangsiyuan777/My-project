#ifndef _MYTASK_H_
#define _MYTASK_H_

#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"


#include <WatchDog.h>
#include "CANDrive.H"
#include "CRC.H"
#include "PID.h"

#include "MyRemote.h"
#include "MyDog.h"


void Task_Creat(void);
void Motor_Task(void const *argument);
void Dog_Task(void const *argument);

typedef enum {
	STOP,
	REMOTE,
	VISION,
	DEATH
}MODE;

int32_t RAMP_self( int32_t final, int32_t now, int32_t ramp );


extern WatchDog_TypeDef Remote_dog;
extern RoboModule_Typedef MI,MII,MIII;
extern MODE mode;

extern WatchDog_TypeDef Remote_dog;//定义一个狗
extern  uint8_t Remote_Flag;

extern WatchDog_TypeDef PC_dog;
extern uint8_t PC_dog_Flag;

extern WatchDog_TypeDef dog_1;
extern uint8_t dog_1_Flag;

extern WatchDog_TypeDef dog_2;
extern uint8_t dog_2_Flag;

extern WatchDog_TypeDef dog_3;
extern uint8_t dog_3_Flag;

extern int16_t outcoming_1;
extern int16_t outcoming_2;
extern int16_t outcoming_3;




#endif
