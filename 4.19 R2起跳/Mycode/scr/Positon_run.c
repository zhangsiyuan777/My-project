//#include "Positon_run.h"
//#include "arm_math.h"
//#include "RC_Remote.h"
//#include "FastCal.h"
//#include "stdio.h"
//#include "PID.h"
//#include "Chassis.h"
//#include "PID_task.h"

//Positon_Typedef Positon_t,Position_offest={.X = 0,.Y = 0,.Angle = 0};
//PositionPack_Typedef positon;
//LASER_Typedef Laser;
//uint16_t laser_speed=200,laser_angle=100,angle_spd = 900;//ԭ300 200 �ٶ�Сһ�� ���뼤���λ��һ�� ������Ծ�ʱ��



//PID RUN_seft= {35,0,5,0};
//PID RUN_x_left={.Kp=8,.Ki=0,.Kd=5,.limit=0},RUN_y_left={8,0,0,0},RUN_z_left={30,0,5,0};
//PID RUN_x_right={.Kp=8,.Ki=0,.Kd=0,.limit=0},RUN_y_right={8,0,0,0},RUN_z_right={30,0,5,0};

//static inline uint8_t Count_laseroffest(int16_t True,int16_t expect, uint16_t error) {
//    return abs((int)True - (int)expect) < error ? 0 : 1;
//}

//void Run_self(float EX) { //ԭ���Դ�EX��
//     static uint8_t a = 0  ;
//    if(Count_laseroffest(Positon_t.Angle,EX,1)){
//        PID_Control(Positon_t.Angle, EX, &RUN_seft);
//        limit(RUN_seft.pid_out, angle_spd, -angle_spd);
//        Run_Speed(&expect_wheel,0,0,RUN_seft.pid_out);
//    }
//    else
//    {
//    a++;
//        if(a >10)
//        {
//            Run_Speed(&expect_wheel,0,0,0);
//            MODE = CHOOSE;
//            Bit++; 
//            xEventGroupSetBits(pxSTEP_t,Bit); 
//        }
//            
//    }
//        
//    
//}
//void clip_pid_left(Laser_measure_Typedef *laser_t) {  
//    static uint8_t init = 0;
//    /*�������������10��λ��Ƕ�������1����ô���е���������ͣ�£�֤������ָ��λ�ã���ͬ*/
//     if(Count_laseroffest(Laser.X_left,laser_t->Ex,10) || Count_laseroffest(Laser.behind,laser_t->Ey,10)|| Count_laseroffest(Positon_t.Angle,laser_t->Ez,1)) {
//        init = 0;
//        PID_Control(Laser.X_left,laser_t->Ex,&RUN_x_left);
//        PID_Control(Laser.behind,laser_t->Ey,&RUN_y_left);
//        PID_Control(Positon_t.Angle,laser_t->Ez,&RUN_z_left);
//        limit(RUN_x_left.pid_out,laser_speed,-laser_speed);
//        limit(RUN_y_left.pid_out,700,-700);
//        limit(RUN_z_left.pid_out,laser_angle,-laser_angle);
//        Run_Speed(&expect_wheel,-RUN_x_left.pid_out,-RUN_y_left.pid_out,RUN_z_left.pid_out);
//     }    else {
////        init++;
////        if(init == 10){
//            Run_Speed(&expect_wheel,0,0,0);
//            MODE = CHOOSE;
//            Bit++; 
//            xEventGroupSetBits(pxSTEP_t,Bit); //�Զ�������һ��ָ��
//        //}
//    }
//    
//}
//void clip_pid_right(Laser_measure_Typedef * laser_t) {  
//    static uint8_t init = 0;
//     if(Count_laseroffest(Laser.X_right,laser_t->Ex,10) || Count_laseroffest(Laser.behind,laser_t->Ey,10)|| Count_laseroffest(Positon_t.Angle,laser_t->Ez,1)) {
//        init = 0;
//        PID_Control(Laser.X_right,laser_t->Ex,&RUN_x_right);
//        PID_Control(Laser.behind,laser_t->Ey,&RUN_y_right);
//        PID_Control(Positon_t.Angle,laser_t->Ez,&RUN_z_right);
//        limit(RUN_x_right.pid_out,800,-800);
//        limit(RUN_y_right.pid_out,800,-800);
//        limit(RUN_z_right.pid_out,500,-500);
//        Run_Speed(&expect_wheel,-RUN_x_right.pid_out,-RUN_y_right.pid_out,RUN_z_right.pid_out);
//     } else {
//        init++;
//        if(init == 10){
//            Run_Speed(&expect_wheel,0,0,0);
//            MODE = STP;
//            Bit++; 
//            xEventGroupSetBits(pxSTEP_t,Bit);
//        }
//    }
//}

//volatile int16_t Rotation = 100; 
////���ٶ�ƫתϵ��

//float Alpha;

//static float Rectify(float num)
//{
//    if(num < -1.0f) return (-1.0f);
//    else if(num > 1.0f) return (1.0f);
//    else return num;
//}
//static  float reform(float X) { //ǯ�ƽǶ���-180��180
//    while(X > 180.f)
//        X -= 360.f;
//    while(X <-180.f)
//        X += 360.f;
//	if((X < 0.1f) && (X > -0.1f))//ǯ����0�Ƕȷ�Χ�ĽǶ�Ϊ0
//		return 0;
//    return (X);
//}

//float Quick_square(Positon_Typedef * begin,Positon_Typedef *end) {
//    
////    float A[2] = {begin->X,begin->Y},//0.002MS
////          B[2] = {-end->X,-end->Y};
////       float add[2],mul[2],add12,squr;
////    arm_add_f32(A,B,add,2);
////    arm_mult_f32(add,add,mul,2);
////    arm_add_f32(&mul[0],&mul[1],&add12,1);
////    arm_sqrt_f32(add12,&squr);
////    return squr;
//    
//    float xx,a;//0.001MS
//    a = (begin->X - end->X) * (begin->X - end->X) + (begin->Y - end->Y) * (begin->Y - end->Y);
//    arm_sqrt_f32(a,&xx);
//    
//    return xx;
//    
//}

////static inline uint8_t Count_laseroffest(int16_t True,int16_t expect, uint16_t error) {
////    return abs((int)True - (int)expect) < error ? 0 : 1;
////}


//void Deal_Run_Strgight_Data(Straight_InitTypeDef *Run)
//{
//    /*Replace the start field  to current filed positon.*/		//��ʼ�����滻Ϊ��ǰ����
////    Run->Begin.X = Positon_t.X;
////    Run->Begin.Y = Positon_t.Y;
////    Run->Begin_Angle = Current_Angle;
//    Run->Begin = Positon_t;
//      
//    Run->Delta_Angle = Run->End.Angle - Run->Begin.Angle;
//    
//    /*Calculate the route length.*/		//���������˶�����
//    Run->Length = (int16_t)Quick_square(&Run->End,&Run->Begin);
////    sqrt((Run->End.X - Run->Begin.X) * (Run->End.X - Run->Begin.X)
////                            + (Run->End.Y - Run->Begin.Y) * (Run->End.Y - Run->Begin.Y));
//    
//    /*Calculate the difference between the start/end speed and the expected speed, then get the the acceleration and deceleration distance.*/
//    Run->B_Rotation = Run->Max_Rotation - ABS(Rotation);	//�����/ĩ����Ԥ�ڸ�ֵ�ٶȵĲ�ֵ���õ��Ӽ��پ���
//    Run->B_Length = Run->B_Rotation / Run->B_Proportion;	//���پ���
//    Run->L_Length = Run->L_Rotation / Run->L_Proportion;    //���پ���
//    Run->Angle_Length = ABS(Run->Delta_Angle) * Run->Angle_Proportion;

//    /*transform the route into a linear equation based on coodinate system, and calculate the coefficient of the linear.*/
//    Run->A = 0.01 * (Run->End.Y - Run->Begin.Y);	//����AX + BY + C = 0��ϵ�����˸�С����ϵ������һ�㣨��·�̹�����ϵ�����ޣ�
//    Run->B = 0.01 * (Run->Begin.X - Run->End.X);
//    Run->C = 0.01 * (Run->End.X * Run->Begin.Y - Run->Begin.X * Run->End.Y);	//y = kx + b��k = -A/B�� b = -C/B

//    /*Determine the direction of the MR1, 1 is the forward, -1 is the backward.*/	//MR1�˶�����1ǰ����-1����
//    if(Run->A > 0 || (Run->A == 0 && Run->B < 0))	//��y������ || ��x������
//        Run->Forward_Back = 1;
//    else Run->Forward_Back = -1;
//    
//    if(  Run->A / Run->B <= 0) Run->Slope = 1;	// б�� >= 0�Ķ� = 1
//    
//    else Run->Slope = -1;
////    printf("Run->Length = %d,Run->B_Length = %d ,Run->L_Length = %d,Run->Angle_Length = %f \r\n" ,Run->Length,Run->B_Length,Run->L_Length,Run->Angle_Length);
//}
//void Run_Strgight(Straight_InitTypeDef *Run) 
//{
//    float d,
//          Distance,
//          End,
//          Wanted_Angle,
//          Wanted_Alpha,
//          Angle,
//          V_Angle,
//          A_Proportion;
//    int16_t Vx,Vy;

////    FieldPosition();	//ȫ����λ���꼰�Ƕ�

//    Distance =  (int16_t)Quick_square(&Positon_t,&Run->Begin);
////    sqrt((Positon_t.X - Run->Begin.X) * (Positon_t.X  - Run->Begin.X)
////                     + (Positon_t.Y - Run->Begin.Y) * (Positon_t.Y - Run->Begin.Y));	//����ʵ���˶�����
//    
//    End = (int16_t)Quick_square(&Positon_t,&Run->End);
////    sqrt((Positon_t.X - Run->End.X) * (Positon_t.X - Run->End.X)
////                     + (Positon_t.Y - Run->End.Y) * (Positon_t.Y - Run->End.Y));	//�����End��ĳ���
//    float sqr;
//    arm_sqrt_f32(Run->A * Run->A + Run->B * Run->B,&sqr);
////     sqrt(Run->A * Run->A + Run->B * Run->B)
//    d = (-1)*Run->Slope*Run->Forward_Back *((Run->A * Positon_t.X + Run->B * Positon_t.Y + Run->C) / sqr ) * Run->V_Proportion; //����ƫ��Ӧ�ߵ�ֱ��ʱ����һ���������ٶȣ������d�ǳ���ֱ�ߵľ���
//    //��������λ����ֱ�ߵĴ��߳��ȣ���ʵ�ʳ���һ���ٶȱ�������Ϊ�����ٶ�ʹ�ã�
//    
//    Run->Alpha = Run->Forward_Back * FastAsin((Run->End.X - Positon_t.X) / (float)End);	//�˶�·����x��ļн�
//    
//    
//    
//    if(Distance <= Run->B_Length)	//������
//    {  
//        Run->B_Gain = (Distance / Run->B_Length);         
//        Rotation = Run->Forward_Back * (Run->Max_Rotation - Run->B_Rotation * Rectify(1 - Run->B_Gain));
//    }
//    else if(End <= Run->L_Length)	//�ȼ���
//    {
//        Run->L_Gain = (End / Run->L_Length);
//        Rotation = Run->Forward_Back * (Run->Max_Rotation - Run->L_Rotation * Rectify(1 - Run->L_Gain));
//    }
//    else Rotation = Run->Forward_Back * Run->Max_Rotation;    //�м�����
//    
//    if((Positon_t.Y < Run->End.Y && Run->Forward_Back == -1) || (Positon_t.Y > Run->End.Y && Run->Forward_Back == 1))	//��λ
//    {  
//        Run->Alpha = - Run->Alpha;	//ֱ��ʻ���Ƕ�
//        Rotation = -Rotation; 
//    }
//    
//    Wanted_Angle = Run->Begin.Angle + Rectify(Distance / Run->Angle_Length) * Run->Delta_Angle;//����ת���ĽǶ�
//    Wanted_Alpha = Run->Alpha + Wanted_Angle;//�����Դ���ƫת�Ƕ�
//    float _cos,_sin;
//    arm_sin_cos_f32(reform(Wanted_Alpha),&_sin,&_cos);
//    
//    Vx = (Rotation + d) * _sin;
//    Vy = (Rotation - d) * _cos;
//    
//    Angle = (Wanted_Angle - Positon_t.Angle); //����ƫ��ת���Ƕ�
//    
//    arm_sqrt_f32(Vx * Vx + Vy * Vy , &sqr);
//    A_Proportion = Run->Max_Rotation / 10.f;
//    V_Angle = Angle * sqr / A_Proportion; 
//    Run_Speed(&expect_wheel,Vx, Vy, V_Angle);
////    printf("Vx = %d  Vy = %d   V_Angle = %f  d = %f  Wanted_Alpha = %f  _cos = %f  _sin = %f  \r\n",Vx,Vy,V_Angle,d,Wanted_Alpha,_cos,_sin);
//    
//    End -= Run->Runout; //End-80<=0֤������ָ��λ������Χ��
//    
//    if(End <= 0) 
//    {
//        Alpha = Wanted_Alpha;
////        Run_Speed(&expect_wheel,0,0,0);
////        MODE = CHOOSE;
//        if(Bit > 0x0E)
//        {
//                MODE = REMOTE;
//                if(Remote_speed_limit == 1.f)
//                LED_F = 2;
//                if(Remote_speed_limit == 0.2f)
//                LED_F = 3;
//            
//        }
//        Bit++;
//        xEventGroupSetBits(pxSTEP_t,Bit);
//        
////        TurnFlag = 0;
//        
//    }
//}

