#include "Task_Init.h"
#include "PID_task.h"
#include "WatchDog.h"
#include "Watch_Dog.h"

TaskHandle_t WatchDogTask_Handler;
TaskHandle_t Get_Ball_Handler;
uint8_t data1[17];//定位板接收

void Get_Ball(void * parameters); //取球任务

SemaphoreHandle_t GetBall_Binary=NULL;

void task_Init() {
     /*CAN1_Init*/
    CanFilter_Init(&hcan1);
    HAL_CAN_Start(&hcan1);
    HAL_CAN_ActivateNotification(&hcan1, CAN_IT_RX_FIFO0_MSG_PENDING);
    
    /*CAN2_Init*/
    CanFilter_Init(&hcan2);
    HAL_CAN_Start(&hcan2);
    HAL_CAN_ActivateNotification(&hcan2, CAN_IT_RX_FIFO1_MSG_PENDING);
	
		HAL_NVIC_DisableIRQ(DMA1_Stream2_IRQn);
    __HAL_UART_ENABLE_IT(&huart4, UART_IT_IDLE);
    HAL_UART_Receive_DMA(&huart4, usart4_dma_buff, sizeof(usart4_dma_buff));
    
    WatchDog_Init(&Remote_dog, 60);
		WatchDog_Init(&Vision_dog, 100);
    
vPortEnterCritical();
 
    xTaskCreate(PID_Task,
         "PID_task",
          127,  //71
          NULL,
          2,
          &PID_Handler); 
	xTaskCreate(WatchDog_Task, 
          "WatchDog_task",
          32,  
          NULL, 
          4,
          &WatchDogTask_Handler);
	xTaskCreate(vRemote_deal,
          "vRemote_deal",
          127,  //57
          NULL,
          4,
          &Remote_deal_Handler);
	xTaskCreate(vPositon_deal,
          "vPositon_deal",
		  
          127,  //71
          NULL,
          4,
          &vPositon_deal_Handler);
	xTaskCreate(Get_Ball,
          "Get_Ball",
          127,  //71
          NULL,
          4,
          &Get_Ball_Handler);
					
vPortExitCritical();
}

void Get_Ball(void * parameters) {
    //TickType_t u32_wate = xTaskGetTickCount();
		GetBall_Binary=xSemaphoreCreateBinary();
		for(;;) {	
			if(xSemaphoreTake(GetBall_Binary,portMAX_DELAY))
			{
				for(h = 350;h>170;h--)
				{	
					Get_angle(arm.l3+h-arm.d,x);					
					expect_angle_2006.expect_1 = (int)(8192 * 36 * 2.2 * ((jiao_a - arm.a) / 360)); 
					expect_angle_3508.expect_3 = (int)(8192 * 19 * 2.86 * ((jiao_b - arm.a - arm.b) / 360));
					servo_1 = 290 + (int)(arm.b / 186 * 2000);   
					Servo_control();
					vTaskDelay(10);
				}	
				osDelay(300);
				HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_0);
				osDelay(300);
				expect_angle_2006.expect_1 = 0;  // 10000
				expect_angle_3508.expect_3 = -40000; // -60000
				servo_1 = 0;
				osDelay(2000);
				HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_0);
			}
			osDelay(5);
		}
}
