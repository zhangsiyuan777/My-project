#ifndef _PID_TASK_H_
#define _PID_TASK_H_

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

#define PI                3.1415926f

typedef struct
{
 double Expect_Speed_X;
 double Expect_Speed_Y;
 double Expect_Speed_Yaw;
} Expect_Speed_Typedef;
extern Expect_Speed_Typedef Expect_Speed;

typedef struct {
	float l1;//机械臂关节一长度
	float l2;//机械臂关节二长度
	float l3;//机械臂关节三长度
	float l4;//机械臂关节四长度
	float d;//底盘高度
	
	float a;//电机角度
	float b;//舵机角度
}Robotic_arm_t;    //机械臂角度

extern Chassis_Motor_expect expect_wheel_3508;
extern Chassis_Motor_expect expect_wheel_2006;
extern TaskHandle_t PID_Handler;
extern TaskHandle_t vN5055_Handle;
extern Chassis_Motor_expect expect_angle_3508;
extern Chassis_Motor_expect expect_angle_2006;
extern int servo_1;
extern int servo_2;
extern int servo_3;
extern int servo_4;
extern Robotic_arm_t arm;
extern float x,h;
extern int jiao_a;
extern int jiao_b;

int32_t RAMP_self( int32_t final, int32_t now, int32_t ramp );
void Servo_control(void);
void Robotic_Arm_take(void);
void PID_Task(void *pvParameters);
void vN5055_task(void *parameters);
void Get_angle(float h,float x);

//void jiaqu();

#endif
