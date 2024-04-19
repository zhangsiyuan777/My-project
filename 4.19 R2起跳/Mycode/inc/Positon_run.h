#ifndef _POSITON_RUN_H_
#define _POSITON_RUN_H_
#include "main.h"
#include "FreeRTOS.h"
#include "event_groups.h" 


/*取绝对值*/
#define ABS(x)	((x)>0 ? (x):(-(x)))
/*角度制转化为弧度制*/
#define ANGLE2RAD(x) (x/180.0f*PI)
/*弧度制转换为角度制*/
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
    
    int16_t B_Rotation;   //起始速度（Delta）
    uint16_t B_Length;  //起始加速/减速距离
    float B_Proportion;  //匀加速比例，越小加速度越小
    
    int16_t L_Rotation;   //要减的速度
    uint16_t L_Length;  //驶出加速/减速距离
    float L_Proportion;  //匀减速比例，越小加速度越小
    
    
    int16_t Max_Rotation; //匀速速度 
    
    float Runout;  //进入下一段
    float Alpha;  //运动路线与x轴的夹角
    float Slope;  //路线斜率
    uint16_t Length; //路线长度
    
    int16_t Delta_Angle;    //偏转角度
    float Angle_Proportion; // 角度转换距离系数

float Angle_Length;
    float V_Proportion;  //d纠偏系数
    
    float B_Gain;  //缓加速比例
    float L_Gain;  //缓减速比例
    
    float A;
    float B;
    float C;
    int8_t Forward_Back;  //前进为1，后退为-1

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
