#ifndef __WATCH_DOG_H
#define __WATCH_DOG_H

#include "WatchDog.h"
#include "Task_Init.h"
#include "RC_Remote.h"
#include "Vision_task.h"

void WatchDog_Task(void * pvParameters);
extern WatchDog_TypeDef Remote_dog;
extern uint8_t Remote_Flag;

extern WatchDog_TypeDef Vision_dog;
#endif
