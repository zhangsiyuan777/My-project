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
float stop_speedX = -6; //ֻ�������ʱ�����̨�ٶ�
float runing_speedX = -6;  //���̺���̨һ��ת��ʱ�����̨�ٶ�
float tran_speedY = 0.1;
float limit_visionX = 5;  //X�������
float limit_speed = 0.1;
float Ex_Y = -80;//������ͷ�ϵ�ȡ��λ��
float limit_visionY = 10;  //Y�������
float Gimbal_rate = 19 * 4.0213 * 8192;
float Gimbal_Angle = 0;

float VisonY_speed=0; 
	
float dipan_speed=1;
Vision_Status vision_status=Adjusting_head;

Vision_control My_Vison_control={0};
//3508��������Ǽ�С��ô����˳ʱ��ת
//ʵ����֪��̨˳ʱ����ת�Ǹ�ֵ��������Ҫ��������ĽǶȼ��ϸ���
void Visual_control()
{		
	limit(expect_angle_3508.expect_1,70000,-70000);			
	limit(expect_angle_2006.expect_1,90000,1000);
	
//	if(expect_angle_3508.expect_1 == 70000 || expect_angle_3508.expect_1 == -70000)//���3508������λ��ô����ת����
//	{
//		My_Vison_control.Z=(expect_angle_3508.expect_1 / 70000) * 100; //�����ת���ٶ���Ҫ�޸�֮���ٸĿ��Ըĳ�һֱ���ɳ���ֱ��������
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
			if(Vision_t.X > limit_visionX||Vision_t.X < -limit_visionX||expect_angle_3508.expect_1>=40000||expect_angle_3508.expect_1<=-40000)	//��ת��̨������ȡ���λ�ò��������ת�Ƕ�,�����û������������Կ��ٵ���̨���˾����ٵ���̨�͵��̽ӽ�
			{    //����ӽ�x�����Ļ�û�ж�׼�����3508̫������߻���̫�����ұ�
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
			if(Vision_t.Y > Ex_Y+limit_visionY||Vision_t.Y < Ex_Y-limit_visionY) //������λ�ò���ȡ��λ�õ���������֮��
			{
				VisonY_speed=Vision_t.Y-Ex_Y; //Ex_Y-Vision_t.Y
				My_Vison_control.Z=0;
				//��������д������̨˳ʱ��ת����������
				if(VisonY_speed>0)
				{
					My_Vison_control.X = Fastsin(Gimbal_Angle)*(VisonY_speed/240*500*dipan_speed+standard_speed);//300�Ǵ�Լ������ٶ�
				  My_Vison_control.Y = Fastcos(Gimbal_Angle)*(VisonY_speed/240*500*dipan_speed+standard_speed);//240����Ļ����ֱ��ʵ�һ��
				}
				else if(VisonY_speed<0)
				{
					My_Vison_control.X = Fastsin(Gimbal_Angle)*(VisonY_speed/240*500*dipan_speed-standard_speed);//300�Ǵ�Լ������ٶ�
					My_Vison_control.Y = Fastcos(Gimbal_Angle)*(VisonY_speed/240*500*dipan_speed-standard_speed);//240����Ļ����ֱ��ʵ�һ��
				}
				else
				{
					My_Vison_control.X = 0;
					My_Vison_control.Y = 0;
				}
			}
			else //����ҵ������λ�ò���
			{
				//���������������ôX��ķֱ��ʺ�Y��ķֱ��ʶ��������˺��ʵ�λ��
				//��ô����ִ��ȡ��Ĳ���
				xSemaphoreGive(GetBall_Binary); 
				vision_status=Adjusting_head;
				MODE=REMOTE;
			}
			break;
		default:
			break;
	}
	
//	if(Vision_t.X > limit_visionX||Vis0ion_t.X < -limit_visionX||expect_angle_3508.expect_1>=40000||expect_angle_3508.expect_1<=-40000)	//��ת��̨������ȡ���λ�ò��������ת�Ƕ�,�����û������������Կ��ٵ���̨���˾����ٵ���̨�͵��̽ӽ�
//	{    //����ӽ�x�����Ļ�û�ж�׼�����3508̫������߻���̫�����ұ�
//		expect_angle_3508.expect_1 += stop_speedX*Vision_t.X;	
//		Gimbal_Angle = -(expect_angle_3508.expect_1/Gimbal_rate)*360; 
//		
//		My_Vison_control.Z=(-expect_angle_3508.expect_1 / 70000) * 300;
//	}
//	else
//	{
//		expect_angle_3508.expect_1 += runing_speedX*Vision_t.X;	
//		Gimbal_Angle = -(expect_angle_3508.expect_1/Gimbal_rate)*360; 
//		if(Vision_t.Y > Ex_Y+limit_visionY||Vision_t.Y < Ex_Y-limit_visionY) //������λ�ñ�ȡ��λ�õ���������֮��
//		{
//			VisonY_speed=Vision_t.Y-Ex_Y; //Ex_Y-Vision_t.Y
//			//��������д������̨˳ʱ��ת����������
//			My_Vison_control.X = Fastsin(Gimbal_Angle)*VisonY_speed/240*800 * dipan_speed;//300�Ǵ�Լ������ٶ�
//			My_Vison_control.Y = Fastcos(Gimbal_Angle)*VisonY_speed/240*800 * dipan_speed;//240����Ļ����ֱ��ʵ�һ��
//		}
//		else //����ҵ������λ�ò���
//		{
//			//���������������ôX��ķֱ��ʺ�Y��ķֱ��ʶ��������˺��ʵ�λ��
//			//��ô����ִ��ȡ��Ĳ���
//			xSemaphoreGive(GetBall_Binary);  
//			MODE=REMOTE;
//		}
//	}
}
