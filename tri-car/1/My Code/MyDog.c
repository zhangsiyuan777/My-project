#include "MyDog.h"

TaskHandle_t MyDog_Handler;


void MyDog(void)
	
{
	    portTickType xLastWakeTime = xTaskGetTickCount();

	for(;;){
		
		
		
		if(Remote_Flag==0)
		{
			if(mode==REMOTE ){
				outcoming_1 =0;
				outcoming_2 =0;
				outcoming_3 =0;
			}
			HAL_GPIO_WritePin(GPIOC,GPIO_PIN_13,GPIO_PIN_SET);		

		}
		if(PC_dog_Flag==0){
			
				if(mode==VISION ){
				outcoming_1 =0;
				outcoming_2 =0;
				outcoming_3 =0;
			}
			HAL_GPIO_WritePin(GPIOC,GPIO_PIN_0,GPIO_PIN_SET);		

		}
//		if(dog_1_Flag==0||dog_2_Flag ==0||dog_3_Flag ==0){
//		outcoming_1 =0;
//		outcoming_2 =0;
//		outcoming_3 =0;
//		if(dog_1_Flag ==0)
//		HAL_GPIO_WritePin(GPIOC,GPIO_PIN_1,GPIO_PIN_RESET);		
//		if(dog_2_Flag ==0)
//		HAL_GPIO_WritePin(GPIOC,GPIO_PIN_2,GPIO_PIN_RESET);	
//		if(dog_3_Flag ==0)
//		HAL_GPIO_WritePin(GPIOC,GPIO_PIN_3,GPIO_PIN_RESET);	


//		}
		
		
		vTaskDelayUntil(&xLastWakeTime,( 10 / portTICK_RATE_MS ));

	}

}
