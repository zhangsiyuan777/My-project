#include "Watch_Dog.h"
#include "PID_task.h"
//#include "RC_Chassis.h"
WatchDog_TypeDef Remote_dog;
WatchDog_TypeDef Vision_dog;
uint8_t Remote_Flag;

extern TaskHandle_t loop_task_handle;
extern TaskHandle_t deal_task_handle;

UBaseType_t uxHighWaterMark1,uxHighWaterMark2,uxHighWaterMark3,uxHighWaterMark4,uxHighWaterMark5,uxHighWaterMark6;
		

void WatchDog_Task(void * pvParameters)
{
	for(;;)
	{
		WatchDog_Polling();
		
//		uxHighWaterMark1=uxTaskGetStackHighWaterMark2( PID_Handler );
//		uxHighWaterMark2=uxTaskGetStackHighWaterMark2( deal_task_handle );
//		uxHighWaterMark3=uxTaskGetStackHighWaterMark2( Remote_deal_Handler );
//		uxHighWaterMark4=uxTaskGetStackHighWaterMark2( vPositon_deal_Handler );
//		uxHighWaterMark5=uxTaskGetStackHighWaterMark2( loop_task_handle );
		vTaskDelay(5);
	}
}

void WatchDog_CallBack(WatchDogp handle)
{
//	  if(IS_Dog(handle, Remote_dog))
//    {       
//			MODE = STOP;
//    }
		if(IS_Dog(handle, Vision_dog))
		{
			Vision_t.X=0;
			Vision_t.Y=0;
			Vision_t.Distance=0;
			My_Vison_control.X=0;
			My_Vison_control.Y=0;
			My_Vison_control.Z=0;
		}
}

void FeedDog_CallBack(WatchDogp handle)
{     	
	//MODE = REMOTE;
	if(IS_Dog(handle, Remote_dog))
	{
        if(MODE == STOP)
        {
					MODE = REMOTE;
        }
  }
}
