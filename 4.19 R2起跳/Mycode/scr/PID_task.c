#include "PID_task.h"
#include "motor.h"
#include "tim.h"        
#include "ramp.h"
#include "math.h"             
#include "VCOMCOMM.h"
#define MY_debug 0
/*
SPEED_MODE下，速度环单环控制3510和3508，Ex_v1,Ex_v2,Ex_v3,Ex_v4分别控制电机速度  注意id
RM3150_MODE下，位置环双环控制3508和2006，
		3508位置控制 expect_angle_3508.expect_1-4分别控制四个电机的位置，    expect_wheel_ramp_3508：斜坡
		2006位置控制 expect_angle_2006.expect_1-4分别控制四个电机的位置，    expect_wheel_ramp_2006：斜坡
*/

int16_t CAN1_txdata[4];
int16_t CAN2_txdata[4];
Expect_Speed_Typedef Expect_Speed; //数据接收

Chassis_Motor_expect expect_wheel_3508;
Chassis_Motor_expect expect_angle_3508;
Chassis_Motor_expect expect_wheel_2006;
Chassis_Motor_expect expect_angle_2006;
int32_t expect_wheel_ramp_3508[4]={200,200,300,200};   //电机斜坡
int32_t expect_wheel_ramp_2006[4]={367,367,367,367};   //电机斜坡    机械臂 367
RM3510_TypeDef motor_wheel_3510[2];      
RM3508_TypeDef motor_wheel_3508[4];
M2006_TypeDef motor_wheel_2006[4];

Robotic_arm_t arm = {.l1=290.0f,.l2=150.0f,.l3=100.0f,.d=280.0f};

float x=400,  //臂到球的距离
	  h=190;  //吸盘到地面的距离
int jiao_a = 91;
int jiao_b = 88;

int32_t wheel_offset[4];
int32_t M2006_offset[4];

PID PID_wheel_speed[4]={{.Kp=2, .Ki=0, .Kd=2,.limit=5000},
						{.Kp=2, .Ki=0, .Kd=2,.limit=5000},
                        {.Kp=2, .Ki=0, .Kd=2,.limit=5000},
						{.Kp=2, .Ki=0, .Kd=2,.limit=5000},};


PID_Smis PID_wheel_position[4]={{.Kp=3, .Ki=0, .Kd=-4, .limit=5000},   //5 0 -6
								{.Kp=3, .Ki=0, .Kd=-4, .limit=5000},    //3 0 -5
                                {.Kp=3, .Ki=0, .Kd=-4, .limit=2000},    //1 0 -2
                                {.Kp=3, .Ki=0, .Kd=-4, .limit=2000}};

PID M2006_Speed[4]={{.Kp=2,.Ki=0,.Kd=2,.limit = 5000},
					{.Kp=2,.Ki=0,.Kd=2,.limit = 5000},
					{.Kp=2,.Ki=0,.Kd=2,.limit = 5000},
					{.Kp=2,.Ki=0,.Kd=2,.limit = 5000}};

PID_Smis M2006_Angle[4]={{.Kp=3,.Ki=0,.Kd=-2.7,.limit = 5000},
						 {.Kp=3,.Ki=0,.Kd=-2.7,.limit = 5000},
						 {.Kp=3,.Ki=0,.Kd=-2.7,.limit = 5000},
						 {.Kp=3,.Ki=0,.Kd=-2.7,.limit = 5000}};							
								
TaskHandle_t PID_Handler;	
								

void PID_Task(void *pvParameters){ //电机pid控制任务 
	
    wheel_offset[0] = motor_wheel_3508[0].Angle;//   纠偏
    wheel_offset[1] = motor_wheel_3508[1].Angle;
    wheel_offset[2] = motor_wheel_3508[2].Angle;
	wheel_offset[3] = motor_wheel_3508[3].Angle;
    
	M2006_offset[0] = motor_wheel_2006[0].Angle;//   纠偏
    M2006_offset[1] = motor_wheel_2006[1].Angle;
	M2006_offset[2] = motor_wheel_2006[2].Angle;
	M2006_offset[3] = motor_wheel_2006[3].Angle;
    
	portTickType xLastWakeTime = xTaskGetTickCount();
	
	for(;;){
		//3508位置控制
		expect_wheel_3508.expect_1 = RAMP_self(expect_angle_3508.expect_1,expect_wheel_3508.expect_1,expect_wheel_ramp_3508[0]);
		PID_Control_Smis(motor_wheel_3508[0].Angle - wheel_offset[0],expect_wheel_3508.expect_1,&PID_wheel_position[0],motor_wheel_3508[0].Speed);
		PID_Control(motor_wheel_3508[0].Speed,PID_wheel_position[0].pid_out,&PID_wheel_speed[0]);
		limit(PID_wheel_speed[0].pid_out,RM3508_LIMIT,-RM3508_LIMIT);
		CAN1_txdata[0]=PID_wheel_speed[0].pid_out;
		
		expect_wheel_3508.expect_2 = RAMP_self(expect_angle_3508.expect_2,expect_wheel_3508.expect_2,expect_wheel_ramp_3508[1]);
		PID_Control_Smis(motor_wheel_3508[1].Angle - wheel_offset[1],expect_wheel_3508.expect_2,&PID_wheel_position[1],motor_wheel_3508[1].Speed);
		PID_Control(motor_wheel_3508[1].Speed,PID_wheel_position[1].pid_out,&PID_wheel_speed[1]);
		limit(PID_wheel_speed[1].pid_out,RM3508_LIMIT,-RM3508_LIMIT);
		CAN1_txdata[1]=PID_wheel_speed[1].pid_out;
		
		expect_wheel_3508.expect_3 = RAMP_self(expect_angle_3508.expect_3,expect_wheel_3508.expect_3,expect_wheel_ramp_3508[2]);
		PID_Control_Smis(motor_wheel_3508[2].Angle - wheel_offset[2],expect_wheel_3508.expect_3,&PID_wheel_position[2],motor_wheel_3508[2].Speed);
		PID_Control(motor_wheel_3508[2].Speed,PID_wheel_position[2].pid_out,&PID_wheel_speed[2]);
		limit(PID_wheel_speed[2].pid_out,RM3508_LIMIT,-RM3508_LIMIT);
		CAN1_txdata[2]=PID_wheel_speed[2].pid_out;
		
		expect_wheel_3508.expect_4 = RAMP_self(expect_angle_3508.expect_4,expect_wheel_3508.expect_4,expect_wheel_ramp_3508[3]);
		PID_Control_Smis(motor_wheel_3508[3].Angle - wheel_offset[3],expect_wheel_3508.expect_4,&PID_wheel_position[3],motor_wheel_3508[3].Speed);
		PID_Control(motor_wheel_3508[3].Speed,PID_wheel_position[3].pid_out,&PID_wheel_speed[3]);
		limit(PID_wheel_speed[3].pid_out,RM3508_LIMIT,-RM3508_LIMIT);
		CAN1_txdata[3]=PID_wheel_speed[3].pid_out;
		#if !MY_debug
		MotorSend(&hcan1,0x200,CAN1_txdata);
		#endif
		//2006位置控制
		expect_wheel_2006.expect_1 = RAMP_self(expect_angle_2006.expect_1,expect_wheel_2006.expect_1,expect_wheel_ramp_2006[0]);
		PID_Control_Smis(motor_wheel_2006[0].Angle - M2006_offset[0],expect_wheel_2006.expect_1,&M2006_Angle[0],motor_wheel_2006[0].Speed);
 		limit(M2006_Angle[0].pid_out,M2006_LIMIT,-M2006_LIMIT);		
		PID_Control(motor_wheel_2006[0].Speed,M2006_Angle[0].pid_out,&M2006_Speed[0]);
		limit(M2006_Speed[0].pid_out,M2006_LIMIT,-M2006_LIMIT);
		CAN2_txdata[0]=M2006_Speed[0].pid_out;
		
		expect_wheel_2006.expect_2 = RAMP_self(expect_angle_2006.expect_2,expect_wheel_2006.expect_2,expect_wheel_ramp_2006[1]);
		PID_Control_Smis(motor_wheel_2006[1].Angle - M2006_offset[1],expect_wheel_2006.expect_2,&M2006_Angle[1],motor_wheel_2006[1].Speed);
 		limit(M2006_Angle[1].pid_out,M2006_LIMIT,-M2006_LIMIT);		
		PID_Control(motor_wheel_2006[1].Speed,M2006_Angle[0].pid_out,&M2006_Speed[1]);
		limit(M2006_Speed[1].pid_out,M2006_LIMIT,-M2006_LIMIT);
		CAN2_txdata[1]=M2006_Speed[1].pid_out;
		
		expect_wheel_2006.expect_3 = RAMP_self(expect_angle_2006.expect_3,expect_wheel_2006.expect_3,expect_wheel_ramp_2006[2]);
		PID_Control_Smis(motor_wheel_2006[2].Angle - M2006_offset[2],expect_wheel_2006.expect_3,&M2006_Angle[2],motor_wheel_2006[2].Speed);
 		limit(M2006_Angle[2].pid_out,M2006_LIMIT,-M2006_LIMIT);		
		PID_Control(motor_wheel_2006[2].Speed,M2006_Angle[2].pid_out,&M2006_Speed[2]);
		limit(M2006_Speed[2].pid_out,M2006_LIMIT,-M2006_LIMIT);
		CAN2_txdata[2]=M2006_Speed[2].pid_out;
		
		expect_wheel_2006.expect_4 = RAMP_self(expect_angle_2006.expect_4,expect_wheel_2006.expect_4,expect_wheel_ramp_2006[3]);
		PID_Control_Smis(motor_wheel_2006[3].Angle - M2006_offset[3],expect_wheel_2006.expect_4,&M2006_Angle[3],motor_wheel_2006[3].Speed);
 		limit(M2006_Angle[3].pid_out,M2006_LIMIT,-M2006_LIMIT);		
		PID_Control(motor_wheel_2006[3].Speed,M2006_Angle[3].pid_out,&M2006_Speed[3]);
		limit(M2006_Speed[3].pid_out,M2006_LIMIT,-M2006_LIMIT);
		CAN2_txdata[3]=M2006_Speed[3].pid_out;
		#if !MY_debug
		MotorSend(&hcan2, 0x200, CAN2_txdata);// ID:201~204
		#endif
		vTaskDelay(1);
		vTaskDelayUntil(&xLastWakeTime,2);
  }
}
						
int servo_1 = 0;
int servo_2 = 0;
int servo_3 = 0;
int servo_4 = 0;

TaskHandle_t vN5055_Handle;
int myflag = 0;
float speed_n5055_1 = 5,speed_n5055_2 = 5;//5055速度

void Get_angle(float h,float x)       // 三自由度机械臂角度解算
{
	//printf("%.2f ",h);
	float r_lc=sqrt(h*h+x*x); 
	float c_ac = acos((arm.l1*arm.l1+arm.l2*arm.l2-r_lc*r_lc)/(2*arm.l1*arm.l2))/PI * 180; 
	float r_ab = asin(x/r_lc)/PI*180;
	if(h < 0) r_ab = 180 - r_ab;
	float c_ab = acos((r_lc*r_lc+arm.l2*arm.l2-arm.l1*arm.l1)/(2*r_lc*arm.l2))/PI * 180;

	arm.a = 180 - r_ab - c_ab;
	arm.b = c_ac - arm.a;
	//return arm;
}

/*   机械臂运行
int jiao_a = 91;
int jiao_b = 88;
if(put_flag == 4)
		{
			
			if(pos_flag == 0)
			{
				duoji_1 = 0;
				expect_angle_2006.expect_1 = 0;
				expect_angle_3508.expect_3 = 0;
			}
			if(pos_flag == 1)
			{
				expect_angle_2006.expect_1 = 120000;  // 10000
				expect_angle_3508.expect_3 = -70000; // -60000
				duoji_1 = 400;
			}
			if(pos_flag == 2)
			{                        
				expect_angle_2006.expect_1 = (int)(8192 * 36 * 2.2 * ((jiao_a - arm.a) / 360)); 
				expect_angle_3508.expect_3 = (int)(8192 * 19 * 2.27 * ((jiao_b - arm.a - arm.b) / 360));
				duoji_1 = 224 + (int)(arm.b / 300 * 2000);		
			}
			
			vTaskDelay(10);
			jiaqu();
			Get_angle(arm.l3+h-arm.d,x);
//			vTaskDelay(1000);
//			h = 150;
		}
*/

//??pwm? servo_1 servo_2 servo_3 servo_4????tim1-4
void Servo_control()     //舵机控制
{
	__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1,500+servo_1); 
	__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2,500+servo_2);
	
	__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3,500+servo_3);  
	__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_4,500+servo_4);  
}

void Robotic_Arm_take()
{	
	if(h == 190) h = 150;
	else if(h == 150) h = 190;
	expect_angle_2006.expect_1 = (int)(8192 * 36 * 2.2 * ((jiao_a - arm.a) / 360)); 
	expect_angle_3508.expect_3 = (int)(8192 * 19 * 2.86 * ((jiao_b - arm.a - arm.b) / 360));
	servo_1 = 290 + (int)(arm.b / 186 * 2000);  

	vTaskDelay(10000);
	
	expect_angle_2006.expect_1 = 100000;  // 10000
	expect_angle_3508.expect_3 = -70000; // -60000
	servo_1 = 600;
	vTaskDelay(10000);
}

void Robotic_Arm_put()
{	
	if(h == 190) h = 150;
	else if(h == 150) h = 190;
	expect_angle_2006.expect_1 = (int)(8192 * 36 * 2.2 * ((jiao_a - arm.a) / 360)); 
	expect_angle_3508.expect_3 = (int)(8192 * 19 * 2.86 * ((jiao_b - arm.a - arm.b) / 360));
	servo_1 = 290 + (int)(arm.b / 186 * 2000);  

	vTaskDelay(10000);
	
	expect_angle_2006.expect_1 = 100000;  // 10000
	expect_angle_3508.expect_3 = -70000; // -60000
	servo_1 = 600;
	vTaskDelay(10000);
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


void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan){     //can回调
	
	if (hcan->Instance == CAN1) {
		uint16_t ID1 = CAN_Receive_DataFrame(&hcan1,CAN1_buff);     
		switch(ID1){		
			case 0x201: 
				RM3508_Receive(&motor_wheel_3508[0],CAN1_buff);
				break;
			case 0x202: 
				RM3508_Receive(&motor_wheel_3508[1],CAN1_buff);
				break;
			case 0x203: 
				RM3508_Receive(&motor_wheel_3508[2],CAN1_buff);
				break;
			case 0x204: 
				RM3508_Receive(&motor_wheel_3508[3],CAN1_buff);
				break;  
			default: break;
		}			
	}
}

void HAL_CAN_RxFifo1MsgPendingCallback(CAN_HandleTypeDef *hcan){
	
	uint16_t ID1 = CAN_Receive_DataFrame(&hcan2,CAN2_buff);     
	switch(ID1){             
		case 0x201: 
			M2006_Receive(&motor_wheel_2006[0], CAN2_buff);
			break;
		case 0x202: 
			M2006_Receive(&motor_wheel_2006[1], CAN2_buff);
			break;
		case 0x203: 
			M2006_Receive(&motor_wheel_2006[2], CAN2_buff);
			break;
		case 0x204: 
			M2006_Receive(&motor_wheel_2006[2], CAN2_buff);
			break;       
		default: break;
	}
	
				
}

void VCOMM_CallBack(uint8_t fun_code, uint16_t id, uint8_t *data, uint8_t len)        //接收pc端数据，详细见队库
{
	memcpy(&Expect_Speed, data, sizeof(Expect_Speed_Typedef));
	//VCOMM_Transmit(fun_code, id, data, len);
}

