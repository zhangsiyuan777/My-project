#include "my_core.h"
#include "cmsis_os.h"
#include "main.h"
#include "ros.h"
#include "yolov5_ros_msgs/port_serial.h"
#include <stdio.h>
#include "Vision_task.h"
#include "WatchDog.h"
//#include "Watch_Dog.h"
//#include "Watch_Dog.h"

int light_flag=0;
extern WatchDog_TypeDef Vision_dog;;

Expect_Typedef Expect_Tx ={.Expect_Speed_X = 0,.Expect_Speed_Y = 0,.Expect_Speed_Yaw = 0};
TaskHandle_t loop_task_handle;
TaskHandle_t deal_task_handle;
void loop_task(void);
void deal_task(void);
//extern TIM_HandleTypeDef htim2;
// 创建节点句柄
ros::NodeHandle nh;
yolov5_ros_msgs::port_serial msg;
//ros::Publisher pub("custom_msg_chatter",&msg);
// 声明订阅话题消息回调函数(具体实现在下文)
void sub_callback(const yolov5_ros_msgs::port_serial& msg);
ros::Subscriber<yolov5_ros_msgs::port_serial> sub("basket_id",&sub_callback);
// 接收回调
void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size){
	// 由于在STM32Hardware.h中默认rosserial相关串口为huart2，因此这样进行判断
	if(huart->Instance == USART2){
		//接收完全回调
		if(huart->RxXferSize == Size){
			nh.getHardware()->reset_rbuf(nh.getHardware()->rbuflen);
			BaseType_t xHigherPriorityTaskWoken;
			// 任务通知
			vTaskNotifyGiveFromISR(deal_task_handle,&xHigherPriorityTaskWoken);
			portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
		}
		// 判断UART IDLE中断是否关闭，从而判断是否由IDLE引起的中断
		else if(!__HAL_UART_GET_IT_SOURCE(huart,UART_IT_IDLE))
		{
			nh.getHardware()->reset_rbuf(huart->RxXferSize - Size);
			BaseType_t xHigherPriorityTaskWoken;
			// 任务通知
			vTaskNotifyGiveFromISR(deal_task_handle,&xHigherPriorityTaskWoken);
			portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
		}
	}
}

//发送回调
void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart){
	// 由于在STM32Hardware.h中默认rosserial相关串口为huart2，因此这样进行判断
	if(huart->Instance == USART2){
		nh.getHardware()->flush();
	}
}

/* 初始化 */
void setup(){
	// 初始化节点
	nh.initNode();
	// 注册发布者
	//nh.advertise(pub);
	nh.subscribe(sub);
	// 创建任务
	xTaskCreate((TaskFunction_t)loop_task,"loop_task",127,NULL,0,&loop_task_handle);//21
	xTaskCreate((TaskFunction_t)deal_task,"deal_task",127,NULL,0,&deal_task_handle);//23
	//HAL_TIM_Base_Start_IT(&htim2);
}

// 同步任务，一段时间同步一次
void loop_task(){
	for(;;){
		nh.spinOnce();
		vTaskDelay(400);
		// 这里回旋用于同步时间，时间不短于1s，但不建议过短以免影响实际使用
	}
}

// 处理接收的ros数据任务
void deal_task(){
	for(;;){
		// 等待接收通知
		ulTaskNotifyTake(pdTRUE,portMAX_DELAY);
		// 接收到通知处理数据
		nh.spinOnce();
	}
}

//void pub_msg(){
//	if(nh.connected()){
//		// 载入数据
//		msg.x = 1.0;
//		msg.y = 2.0;
//		msg.z = 3.0;
//		pub.publish(&msg);
//	}
//}
void sub_callback(const yolov5_ros_msgs::port_serial& msg)
{
	 char p_buff[50];
//	Expect_Tx.Expect_Speed_X = msg.radar_x;
//	Expect_Tx.Expect_Speed_Y = msg.radar_y;
//	Expect_Tx.Expect_Speed_Yaw = msg.radar_z;
//	Expect_Tx.flag=msg.flag;
	light_flag++;
	if(light_flag==5)
	{
		light_flag=0;
		HAL_GPIO_TogglePin(GPIOC,GPIO_PIN_13);
	}
	Vision_t.X=msg.x;
	Vision_t.Y=msg.y;
	Vision_t.Distance=msg.distance;
	Feed_Dog(&Vision_dog);
	sprintf(p_buff,"[stm32]: sub data:%d,%d,%d,%d",msg.id,msg.x,msg.y,msg.distance);
	// 接收后打印，PC端会打印出来
	nh.loginfo(p_buff);
}