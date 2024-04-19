#include "MyTask.H"

Expect_Speed_Typedef VCOMCOMM_Data;  

RoboModule_Typedef MI,MII,MIII;

MODE mode=REMOTE;

WatchDog_TypeDef Remote_dog;//定义一个狗
uint8_t Remote_Flag=0;

WatchDog_TypeDef PC_dog;
uint8_t PC_dog_Flag=0;

//WatchDog_TypeDef dog_1;
//uint8_t dog_1_Flag=0;

//WatchDog_TypeDef dog_2;
//uint8_t dog_2_Flag=0;

//WatchDog_TypeDef dog_3;
//uint8_t dog_3_Flag=0;

short outcoming_1 = 0,outcoming_2 = 0,outcoming_3 = 0;



void Task_Creat()
{
	
		WatchDog_Init(&Remote_dog, 60);//设置喂狗；
		WatchDog_Init(&PC_dog,60);
//		WatchDog_Init(&dog_1, 120);
//		WatchDog_Init(&dog_2, 120);
//		WatchDog_Init(&dog_3, 120);	
	
		
 xTaskCreate
	(
	(TaskFunction_t)Motor_Task,
	"MotorTask",
	128,
	NULL,
	5,
	NULL
	);
	
	xTaskCreate
	(
	(TaskFunction_t)Dog_Task,
	"FeedDog",
	64,
	NULL,
	5,
	NULL
	);
	xTaskCreate
	(
	(TaskFunction_t)MyDog,
	"My_Dog",
	64,
	NULL,
	5,
	NULL
	);
}


void Motor_Task(void const *argument)
{
		    portTickType xLastWakeTime = xTaskGetTickCount();
	
		
//		vTaskDelay(500 / portTICK_RATE_MS );

	for(;;)
 {

	 
	 if(RemoteData.Key.Left_Key_Up){
		
			mode=VISION;
				
		}
	 
	  if(RemoteData.Key.Left_Key_Left){
			
			mode=REMOTE;
				
		}
		
	 if(RemoteData.Key.Left_Key_Down){
		
			mode=STOP;
		 outcoming_1=0;
		 outcoming_2=0;
		 outcoming_3=0;
		}
	 
	 if(mode==REMOTE)
	 {
	  outcoming_1 = Remote_Control.Ey * 0.866025 + Remote_Control.Ex * 0.5+ Remote_Control.Eangle * 0.5;
		outcoming_2 = - Remote_Control.Ey* 0.866025 + Remote_Control.Ex * 0.5+ Remote_Control.Eangle * 0.5;
		outcoming_3 = 0 - Remote_Control.Ex + Remote_Control.Eangle * 0.5;
		 
	 }
		
		limit(outcoming_1  , 17000 , -17000);
		limit(outcoming_2  , 17000 , -17000);
		limit(outcoming_3  , 17000 , -17000);
	
		MI.ExpVelocity = RAMP_self(outcoming_1,MI.ExpVelocity,500);
		MII.ExpVelocity = RAMP_self(outcoming_2,MII.ExpVelocity,500); 
		MIII.ExpVelocity = RAMP_self(outcoming_3,MIII.ExpVelocity,500);

		CAN_RoboModule_DRV_Velocity_Mode(&hcan2,&MI);
	  CAN_RoboModule_DRV_Velocity_Mode(&hcan2,&MII);
	  CAN_RoboModule_DRV_Velocity_Mode(&hcan2,&MIII);
	 
	
	 vTaskDelayUntil( &xLastWakeTime, ( 10 / portTICK_RATE_MS ) );
	 
  }
}

void Dog_Task(void const *argument)
{
			portTickType xLastWakeTime = xTaskGetTickCount();

		for(;;)
	{

		WatchDog_Polling();
		
		vTaskDelayUntil( &xLastWakeTime, ( 10 / portTICK_RATE_MS ) );
	}
}

//void HAL_CAN_RxFifo1MsgPendingCallback(CAN_HandleTypeDef *hcan) {//接收蓝砖的数据
//    if (hcan->Instance == CAN2) {
//       
//        uint8_t data2[8];
//        switch(CAN_Receive_DataFrame (hcan, data2)) {
//          
//					case 010:Feed_Dog(&dog_1);break;
//					case 020:Feed_Dog(&dog_2);break;
//					case 030:Feed_Dog(&dog_3);break;
//						
//            default :break;
//        }
//    }
//}

void WatchDog_CallBack(WatchDogp handle)
{
	if(IS_Dog(handle, Remote_dog))
		Remote_Flag = 0;
	if(IS_Dog(handle,PC_dog))
		PC_dog_Flag = 0;
//	if(IS_Dog(handle, dog_1))
//		dog_1_Flag = 0;
//	if(IS_Dog(handle, dog_2))
//		dog_2_Flag = 0;
//	if(IS_Dog(handle, dog_3))
//		dog_3_Flag = 0;
//	
}

void FeedDog_CallBack(WatchDogp handle)
{
	if(IS_Dog(handle, Remote_dog)){
		
		Remote_Flag = 1;
		HAL_GPIO_WritePin(GPIOC,GPIO_PIN_13,GPIO_PIN_RESET);	
		
	}
	if(IS_Dog(handle,PC_dog)){
		
		PC_dog_Flag=1;
		HAL_GPIO_WritePin(GPIOC,GPIO_PIN_0,GPIO_PIN_RESET);	
		
	}
//	if(IS_Dog(handle, dog_1)){
//		
//		dog_1_Flag = 1;
//		HAL_GPIO_WritePin(GPIOC,GPIO_PIN_1,GPIO_PIN_SET);	
//		
//	}
//	if(IS_Dog(handle, dog_2)){
//		
//		dog_2_Flag = 1;
//		HAL_GPIO_WritePin(GPIOC,GPIO_PIN_2,GPIO_PIN_SET);	
//	}
//	if(IS_Dog(handle, dog_3)){
//		
//		dog_3_Flag = 1;
//		HAL_GPIO_WritePin(GPIOC,GPIO_PIN_3,GPIO_PIN_SET);	
//	}

}
void VCOMM_CallBack(uint8_t fun_code, uint16_t id, uint8_t *data, uint8_t len)       
{
	
	memcpy(&VCOMCOMM_Data, data, sizeof(Expect_Speed_Typedef));
	Feed_Dog(&PC_dog);

	if(mode==VISION){
	
		outcoming_1 = 1000 * (VCOMCOMM_Data.Expect_Speed_X * 0.866025 - VCOMCOMM_Data.Expect_Speed_Y * 0.5 - VCOMCOMM_Data.Expect_Speed_Yaw *0.25);
		outcoming_2 = 1000 * (- VCOMCOMM_Data.Expect_Speed_X * 0.866025 - VCOMCOMM_Data.Expect_Speed_Y * 0.5 - VCOMCOMM_Data.Expect_Speed_Yaw * 0.25);
		outcoming_3 = 1000 * (0 + VCOMCOMM_Data.Expect_Speed_Y * 0.5 - VCOMCOMM_Data.Expect_Speed_Yaw * 0.25);

	}
	
}

int32_t RAMP_self( int32_t final, int32_t now, int32_t ramp ) //斜坡函数
{
    float buffer = final - now;
    
    if (buffer > 0)
    {
        if (buffer > ramp)  
                now += ramp;  
        else
                now += buffer;
    }		
    else
    {
        if (buffer < -ramp)
                now += -ramp;
        else
                now += buffer;
    }
    return now;
}
