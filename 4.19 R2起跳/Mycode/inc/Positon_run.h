#ifndef _POSITON_RUN_H_
#define _POSITON_RUN_H_
#include "main.h"
#include "FreeRTOS.h"
#include "event_groups.h" 


/*ȡ����ֵ*/
#define ABS(x)	((x)>0 ? (x):(-(x)))
/*�Ƕ���ת��Ϊ������*/
#define ANGLE2RAD(x) (x/180.0f*PI)
/*������ת��Ϊ�Ƕ���*/
#define RAD2ANGLE(x) (x/PI*180.0f)

#pragma pack(1)
typedef struct {
   int16_t X;
   int16_t Y;
   int16_t Angle;
   int16_t rand;
} CAN_Pack_Typedef;
typedef struct {
    uint16_t adc;
    uint16_t spi1;
    uint16_t spi2;
    uint16_t spi3;
} LASER_SEND_Typedef;
#pragma pack()


typedef struct {
   int16_t X;
   int16_t Y;
   float Angle;
} Positon_Typedef;
#pragma pack(1)
typedef struct {
    uint8_t head;
    int16_t X;
    int16_t Y;
    int16_t Angle;
} PositionPack_Typedef;
#pragma pack()
typedef struct {
    uint16_t X_left;
    uint16_t X_right;
    uint16_t behind;
} LASER_Typedef;

typedef struct{
    Positon_Typedef Begin,End;
    
    int16_t B_Rotation;   //��ʼ�ٶȣ�Delta��
    uint16_t B_Length;  //��ʼ����/���پ���
    float B_Proportion;  //�ȼ��ٱ�����ԽС���ٶ�ԽС
    
    int16_t L_Rotation;   //Ҫ�����ٶ�
    uint16_t L_Length;  //ʻ������/���پ���
    float L_Proportion;  //�ȼ��ٱ�����ԽС���ٶ�ԽС
    
    
    int16_t Max_Rotation; //�����ٶ� 
    
    float Runout;  //������һ��
    float Alpha;  //�˶�·����x��ļн�
    float Slope;  //·��б��
    uint16_t Length; //·�߳���
    
    int16_t Delta_Angle;    //ƫת�Ƕ�
    float Angle_Proportion; // �Ƕ�ת������ϵ��

float Angle_Length;
    float V_Proportion;  //d��ƫϵ��
    
    float B_Gain;  //�����ٱ���
    float L_Gain;  //�����ٱ���
    
    float A;
    float B;
    float C;
    int8_t Forward_Back;  //ǰ��Ϊ1������Ϊ-1

}Straight_InitTypeDef;

typedef struct {
     float Ex;
     float Ey;   
     float Ez;
}Laser_measure_Typedef;

typedef struct {
    uint16_t wwgj;
    uint8_t step_left;
    uint8_t step_right;
    
    Laser_measure_Typedef *left[4];
    Laser_measure_Typedef *right[4];
    Straight_InitTypeDef * run[3];
}RUN_movement_Typedef;

extern volatile int16_t Rotation; 

void Run_self(float EX);
void clip_pid_left(Laser_measure_Typedef * laser_t);
void clip_pid_right(Laser_measure_Typedef *laser_t);
extern LASER_Typedef Laser;
extern Positon_Typedef Positon_t,Position_offest;
extern PositionPack_Typedef positon;

void Deal_Run_Strgight_Data(Straight_InitTypeDef *Run);
void Run_Strgight(Straight_InitTypeDef *Run);
float Quick_square(Positon_Typedef * begin,Positon_Typedef *end);

#endif
