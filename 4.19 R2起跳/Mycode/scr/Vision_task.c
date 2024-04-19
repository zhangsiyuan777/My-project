#include "Vision_task.h"
#include "PID_task.h"
#include "RC_Remote.h"
#include "FastCal.h"
VisionBack_Typedef vision_t;
Vision_Typedef Vision_t;
Vision_Typedef vision_offest;

#define standard_speed 60

extern SemaphoreHandle_t GetBall_Binary;
int flag = 0;
float stop_speedX = -6; //只在找球的时候的云台速度
float runing_speedX = -6;  //地盘和云台一起转的时候的云台速度
float tran_speedY = 0.1;
float limit_visionX = 5;  //X轴的死驱
float limit_speed = 0.1;
float Ex_Y = -80;//在摄像头上的取球位置
float limit_visionY = 10;  //Y轴的死驱
float Gimbal_rate = 19 * 4.0213 * 8192;
float Gimbal_Angle = 0;

float VisonY_speed=0; 
	
float dipan_speed=1;
Vision_Status vision_status=Adjusting_head;

Vision_control My_Vison_control={0};
//3508期望如果是减小那么就是顺时针转
//实践得知云台顺时针旋转是负值，所以需要给算出来的角度加上负号
void Visual_control()
{		
	limit(expect_angle_3508.expect_1,70000,-70000);			
	limit(expect_angle_2006.expect_1,90000,1000);
	
//	if(expect_angle_3508.expect_1 == 70000 || expect_angle_3508.expect_1 == -70000)//如果3508到了限位那么就旋转车身
//	{
//		My_Vison_control.Z=(expect_angle_3508.expect_1 / 70000) * 100; //这个旋转的速度需要修改之后再改可以改成一直调成车身直到球到中心
//		//My_Vison_control.Z=(expect_angle_3508.expect_1 / 320) * 100;
//		
//		//VisionData.rocker[2]=2047- (Vision_t.X/ 70000) * 100;
//	}
//	else 
//	{
//		My_Vison_control.Z=(expect_angle_3508.expect_1 / 70000) * 100;
//		//VisionData.rocker[2] = 2047;
//	}
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	switch(vision_status)
	{
		case Adjusting_head:
			if(Vision_t.X > limit_visionX||Vision_t.X < -limit_visionX||expect_angle_3508.expect_1>=40000||expect_angle_3508.expect_1<=-40000)	//旋转云台调整的取球的位置并且算出旋转角度,如果球没到接受区间就以快速调云台到了就慢速调云台和地盘接近
			{    //如果视角x的中心还没有对准球或者3508太靠近左边或者太靠近右边
				expect_angle_3508.expect_1 += stop_speedX*Vision_t.X;	
				Gimbal_Angle = -(expect_angle_3508.expect_1/Gimbal_rate)*360; 
				
				My_Vison_control.Z=(-expect_angle_3508.expect_1 / 70000.0) * 500;
			}
			else
			{
				vision_status=Adjusting_baseplate;
				osDelay(500);
			}
			break;
		case Adjusting_baseplate:
			expect_angle_3508.expect_1 += runing_speedX*Vision_t.X;	
			Gimbal_Angle = -(expect_angle_3508.expect_1/Gimbal_rate)*360; 
			if(Vision_t.Y > Ex_Y+limit_visionY||Vision_t.Y < Ex_Y-limit_visionY) //如果球的位置不在取球位置的上下死区之间
			{
				VisonY_speed=Vision_t.Y-Ex_Y; //Ex_Y-Vision_t.Y
				My_Vison_control.Z=0;
				//现在这样写假设云台顺时针转期望是正的
				if(VisonY_speed>0)
				{
					My_Vison_control.X = Fastsin(Gimbal_Angle)*(VisonY_speed/240*500*dipan_speed+standard_speed);//300是大约的最大速度
				  My_Vison_control.Y = Fastcos(Gimbal_Angle)*(VisonY_speed/240*500*dipan_speed+standard_speed);//240是屏幕纵轴分辨率的一半
				}
				else if(VisonY_speed<0)
				{
					My_Vison_control.X = Fastsin(Gimbal_Angle)*(VisonY_speed/240*500*dipan_speed-standard_speed);//300是大约的最大速度
					My_Vison_control.Y = Fastcos(Gimbal_Angle)*(VisonY_speed/240*500*dipan_speed-standard_speed);//240是屏幕纵轴分辨率的一半
				}
				else
				{
					My_Vison_control.X = 0;
					My_Vison_control.Y = 0;
				}
			}
			else //如果找到了球的位置并且
			{
				//如果进入这个情况那么X轴的分辨率和Y轴的分辨率都调整到了合适的位置
				//那么可以执行取球的操作
				xSemaphoreGive(GetBall_Binary); 
				vision_status=Adjusting_head;
				MODE=REMOTE;
			}
			break;
		default:
			break;
	}
	
//	if(Vision_t.X > limit_visionX||Vis0ion_t.X < -limit_visionX||expect_angle_3508.expect_1>=40000||expect_angle_3508.expect_1<=-40000)	//旋转云台调整的取球的位置并且算出旋转角度,如果球没到接受区间就以快速调云台到了就慢速调云台和地盘接近
//	{    //如果视角x的中心还没有对准球或者3508太靠近左边或者太靠近右边
//		expect_angle_3508.expect_1 += stop_speedX*Vision_t.X;	
//		Gimbal_Angle = -(expect_angle_3508.expect_1/Gimbal_rate)*360; 
//		
//		My_Vison_control.Z=(-expect_angle_3508.expect_1 / 70000) * 300;
//	}
//	else
//	{
//		expect_angle_3508.expect_1 += runing_speedX*Vision_t.X;	
//		Gimbal_Angle = -(expect_angle_3508.expect_1/Gimbal_rate)*360; 
//		if(Vision_t.Y > Ex_Y+limit_visionY||Vision_t.Y < Ex_Y-limit_visionY) //如果球的位置比取球位置的上下死区之间
//		{
//			VisonY_speed=Vision_t.Y-Ex_Y; //Ex_Y-Vision_t.Y
//			//现在这样写假设云台顺时针转期望是正的
//			My_Vison_control.X = Fastsin(Gimbal_Angle)*VisonY_speed/240*800 * dipan_speed;//300是大约的最大速度
//			My_Vison_control.Y = Fastcos(Gimbal_Angle)*VisonY_speed/240*800 * dipan_speed;//240是屏幕纵轴分辨率的一半
//		}
//		else //如果找到了球的位置并且
//		{
//			//如果进入这个情况那么X轴的分辨率和Y轴的分辨率都调整到了合适的位置
//			//那么可以执行取球的操作
//			xSemaphoreGive(GetBall_Binary);  
//			MODE=REMOTE;
//		}
//	}
}
