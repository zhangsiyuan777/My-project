#include "RC_Remote.h"
#include "stdio.h"
#include "FastCal.h"
#include "Bluetooth_phone.h"
#include "PID_task.h"
#include "Positon_run.h"
#include "Vision_task.h"
#include "PID.h"

int flag3=9;

int16_t Ex;
int16_t Ey;
int16_t Eomega;
UART_DataPack Tem_RemoteData={.head=0x5A};
UART_DataPack Tx_RemoteData;
UART_DataPack RemoteData;  //将串口接收的数据存到这里
UART_DataPack VisionData = {.head=0x5A};
uint8_t usart4_dma_buff[21]; //串口接收数据
Remote_Handle_t Remote_Control = {.Key_Control = &RemoteData.Key}; //取出遥控器数据
float gimbal_speed = 0.5f;

Positon_label MODE = REMOTE;

void Updatakey(Remote_Handle_t * xx) { //遥控器数据更新
    xx->Second = xx->First;
    xx->First = *xx->Key_Control;
}

uint16_t a = 0,c = 0,high = 400;
uint16_t tiao_time = 230,chu_time=144,sc_time = 65,hc_time = 167;
TaskHandle_t Remote_deal_Handler;
TaskHandle_t vPositon_deal_Handler;
void vRemote_deal(void * parameters) {
    
    for(;;) {
        
        Updatakey(&Remote_Control);
		if (Remote_Control.First.Left_Key_Down== 1 && Remote_Control.Second.Left_Key_Down == 0) {//											
			MODE = STP;				
		}
		else if(Remote_Control.First.Left_Key_Left== 1 && Remote_Control.Second.Left_Key_Left == 0)
		{
			MODE = RADER;
		}
		else if(Remote_Control.First.Left_Key_Right== 1 && Remote_Control.Second.Left_Key_Right == 0)
		{
			MODE = GIMBAL;
		}
		else if(Remote_Control.First.Left_Switch_Up== 1 && Remote_Control.Second.Left_Switch_Up == 0)
		{
			MODE = VISION;
		}
		else if (Remote_Control.First.Left_Key_Up== 1 && Remote_Control.Second.Left_Key_Up == 0) {//										
			MODE=REMOTE;			
		}
      if(MODE == REMOTE||MODE == VISION||MODE == GIMBAL){
			Servo_control();
			if(MODE == GIMBAL)
			{
				limit(expect_angle_3508.expect_1,70000,-70000);	
				expect_angle_3508.expect_1 += Remote_Control.Eangle * gimbal_speed;
			}
			if(MODE == VISION)
			{
				Visual_control();
			}
			if (Remote_Control.First.Right_Key_Left == 1 && Remote_Control.Second.Right_Key_Left == 0) {//取球
				MODE=REMOTE;
				for(h = 350;h>170;h--){	
					Get_angle(arm.l3+h-arm.d,x);					
					expect_angle_2006.expect_1 = (int)(8192 * 36 * 2.2 * ((jiao_a - arm.a) / 360)); 
					expect_angle_3508.expect_3 = (int)(8192 * 19 * 2.86 * ((jiao_b - arm.a - arm.b) / 360));
					servo_1 = 290 + (int)(arm.b / 186 * 2000);   
					Servo_control();
					vTaskDelay(10);
				}	
			}   
			else if (Remote_Control.First.Right_Key_Up == 1 && Remote_Control.Second.Right_Key_Up == 0) {
				HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_0);
				
			}
			else if (Remote_Control.First.Right_Key_Right == 1 && Remote_Control.Second.Right_Key_Right == 0) {
				MODE=REMOTE;
				if(expect_angle_2006.expect_1 == 90000)
					expect_angle_2006.expect_1 = 0;  // 10000
				else if(expect_angle_2006.expect_1 != 90000)
					expect_angle_2006.expect_1 = 90000;  // 10000
				expect_angle_3508.expect_3 = -110000; // -60000
				servo_1 = 540;
			}
			else if (Remote_Control.First.Right_Key_Down == 1 && Remote_Control.Second.Right_Key_Down == 0) {//视觉初始位置
				expect_angle_2006.expect_1 = 0;  // 10000
				expect_angle_3508.expect_3 = -40000; // -60000
				servo_1 = 0;
			}
			else if (Remote_Control.First.Right_Switch_Up == 1 && Remote_Control.Second.Right_Switch_Up == 0) {
				//Ex_Y+=10;
				expect_angle_2006.expect_1 =  200000;  // 10000
				expect_angle_3508.expect_3 = -200000; // -60000	
				servo_1 = 0;
			}
			else if (Remote_Control.First.Right_Switch_Down == 1 && Remote_Control.Second.Right_Switch_Down == 0) {
				//Ex_Y-=10;
				switch(flag3)
				{
						case 1: HAL_GPIO_WritePin(GPIOA, Valve1_Left_Pin|Valve1_Right_Pin, GPIO_PIN_RESET);//伸出
						HAL_GPIO_WritePin(GPIOC, Valve2_Left_Pin|Valve2_Right_Pin, GPIO_PIN_RESET);break;
						case 2: HAL_GPIO_WritePin(GPIOA, Valve1_Left_Pin|Valve1_Right_Pin, GPIO_PIN_SET);
						HAL_GPIO_WritePin(GPIOC, Valve2_Left_Pin|Valve2_Right_Pin, GPIO_PIN_SET);break;
						case 3: HAL_GPIO_WritePin(GPIOA, Valve1_Left_Pin, GPIO_PIN_SET);HAL_GPIO_WritePin(GPIOA,Valve1_Right_Pin, GPIO_PIN_RESET);//缓冲
						HAL_GPIO_WritePin(GPIOC, Valve2_Left_Pin, GPIO_PIN_SET);HAL_GPIO_WritePin(GPIOC,Valve2_Right_Pin, GPIO_PIN_RESET);break;
						case 4: HAL_GPIO_WritePin(GPIOA, Valve1_Left_Pin, GPIO_PIN_RESET);HAL_GPIO_WritePin(GPIOA,Valve1_Right_Pin, GPIO_PIN_SET);//收回
						HAL_GPIO_WritePin(GPIOC, Valve2_Left_Pin, GPIO_PIN_RESET);HAL_GPIO_WritePin(GPIOC,Valve2_Right_Pin, GPIO_PIN_SET);break;
						
						case 5: HAL_GPIO_WritePin(GPIOC, Valve2_Left_Pin|Valve2_Right_Pin, GPIO_PIN_RESET);break;
						case 6: HAL_GPIO_WritePin(GPIOC, Valve2_Left_Pin|Valve2_Right_Pin, GPIO_PIN_SET);break;
						case 7: HAL_GPIO_WritePin(GPIOC, Valve2_Left_Pin, GPIO_PIN_SET);HAL_GPIO_WritePin(GPIOC,Valve2_Right_Pin, GPIO_PIN_RESET);break;
						case 8: HAL_GPIO_WritePin(GPIOC, Valve2_Left_Pin, GPIO_PIN_RESET);HAL_GPIO_WritePin(GPIOC,Valve2_Right_Pin, GPIO_PIN_SET);break;
						case 9: 
							HAL_GPIO_WritePin(GPIOA, Valve1_Left_Pin, GPIO_PIN_RESET);HAL_GPIO_WritePin(GPIOA,Valve1_Right_Pin, GPIO_PIN_SET);//收回
							HAL_GPIO_WritePin(GPIOC, Valve2_Left_Pin, GPIO_PIN_RESET);HAL_GPIO_WritePin(GPIOC,Valve2_Right_Pin, GPIO_PIN_SET);
							osDelay(300);
							HAL_GPIO_WritePin(GPIOA, Valve1_Left_Pin|Valve1_Right_Pin, GPIO_PIN_RESET);//伸出
							HAL_GPIO_WritePin(GPIOC, Valve2_Left_Pin|Valve2_Right_Pin, GPIO_PIN_RESET);
							osDelay(tiao_time);
							HAL_GPIO_WritePin(GPIOA, Valve1_Left_Pin, GPIO_PIN_RESET);HAL_GPIO_WritePin(GPIOA,Valve1_Right_Pin, GPIO_PIN_SET);//收回
							HAL_GPIO_WritePin(GPIOC, Valve2_Left_Pin, GPIO_PIN_RESET);HAL_GPIO_WritePin(GPIOC,Valve2_Right_Pin, GPIO_PIN_SET);
							osDelay(chu_time);
							HAL_GPIO_WritePin(GPIOA, Valve1_Left_Pin|Valve1_Right_Pin, GPIO_PIN_RESET);//伸出
							HAL_GPIO_WritePin(GPIOC, Valve2_Left_Pin|Valve2_Right_Pin, GPIO_PIN_RESET);
							osDelay(sc_time);
							HAL_GPIO_WritePin(GPIOA, Valve1_Left_Pin, GPIO_PIN_SET);HAL_GPIO_WritePin(GPIOA,Valve1_Right_Pin, GPIO_PIN_RESET);//缓冲
							HAL_GPIO_WritePin(GPIOC, Valve2_Left_Pin, GPIO_PIN_SET);HAL_GPIO_WritePin(GPIOC,Valve2_Right_Pin, GPIO_PIN_RESET);
							
							osDelay(hc_time);
							HAL_GPIO_WritePin(GPIOA, Valve1_Left_Pin, GPIO_PIN_RESET);HAL_GPIO_WritePin(GPIOA,Valve1_Right_Pin, GPIO_PIN_SET);//收回
							HAL_GPIO_WritePin(GPIOC, Valve2_Left_Pin, GPIO_PIN_RESET);HAL_GPIO_WritePin(GPIOC,Valve2_Right_Pin, GPIO_PIN_SET);
							break;
				}
			}

			
		}

       osDelay(10);
   }                                                                                                                                
      
}

void vPositon_deal(void * parameters) {
    TickType_t u32_wate = xTaskGetTickCount();
    for(;;) {
			
   	if(MODE == STP || MODE == STOP) //急停
		{
			Tem_RemoteData.rocker[1]=2047;
			Tem_RemoteData.rocker[0]=2047;
			Tem_RemoteData.rocker[2]=2047;	
			HAL_UART_Transmit_DMA(&huart3, (uint8_t*)(&Tem_RemoteData), sizeof(UART_DataPack));		
		}	
		else if(MODE == RADER)		
		{
//			Tx_RemoteData.rocker[0]=RemoteData.rocker[0]-Expect_Speed.Expect_Speed_X*655;  //x轴向速度
//			Tx_RemoteData.rocker[1]=RemoteData.rocker[1]+Expect_Speed.Expect_Speed_Y*655;  //y轴向速度
//			Tx_RemoteData.rocker[2]=RemoteData.rocker[2]+Expect_Speed.Expect_Speed_Yaw*400;  //z自传速度						
			Tem_RemoteData.rocker[0]=2047-Expect_Speed.Expect_Speed_Y*800;  //x轴向速度655			
			Tem_RemoteData.rocker[1]=2047-Expect_Speed.Expect_Speed_X*800;  //y轴向速度655		
			Tem_RemoteData.rocker[2]=2047-Expect_Speed.Expect_Speed_Yaw*400;  //z自传速度400							

			Ex =-(Tem_RemoteData.rocker[0] - 2047);
//          Remote_Control.Ey  =0;
			Ey = (Tem_RemoteData.rocker[1] - 2047);			
			Eomega = (Tem_RemoteData.rocker[2] - 2047)/2048.f*180;						
	
			HAL_UART_Transmit_DMA(&huart3, (uint8_t*)(&Tem_RemoteData), sizeof(UART_DataPack));
		}
		else if(MODE == GIMBAL)
		{
			//Tem_RemoteData.rocker[0] = RemoteData.rocker[0];  //x轴向速度655			
			//Tem_RemoteData.rocker[1] = RemoteData.rocker[1];  //y轴向速度655
			Tem_RemoteData = RemoteData;
			Tem_RemoteData.rocker[2] = 2047;
			HAL_UART_Transmit_DMA(&huart3, (uint8_t*)(&Tem_RemoteData), sizeof(UART_DataPack));
		}
		else if(MODE == VISION)
		{
//			Tem_RemoteData = VisionData;
//			Ex =-(Tem_RemoteData.rocker[0] - 2047);
//			Ey = (Tem_RemoteData.rocker[1] - 2047);			
//			Eomega = (Tem_RemoteData.rocker[2] - 2047)/2048.f*180;	
			limit(My_Vison_control.X,1000,-1000);
			limit(My_Vison_control.Y,1000,-1000);
			limit(My_Vison_control.Z,1000,-1000);
			
			Tem_RemoteData.rocker[0]=2047+My_Vison_control.X; //x是正数就往右走
			Tem_RemoteData.rocker[1]=2047-My_Vison_control.Y; //y是正数就往前走
			Tem_RemoteData.rocker[2]=2047+My_Vison_control.Z;
			
			HAL_UART_Transmit_DMA(&huart3, (uint8_t*)(&Tem_RemoteData), sizeof(UART_DataPack));
		}
		else if(MODE == REMOTE)  //遥控器                                     
		{
			HAL_UART_Transmit_DMA(&huart3, (uint8_t*)(&Tx_RemoteData), sizeof(UART_DataPack));
		}
   		vTaskDelayUntil(&u32_wate,4);
    }
}
