#include<stm32f10x_lib.h>
#include "sys.h"
#include "usart.h"		
#include "delay.h"
#include "motor.h"
#include "speed_cap.h"
#include "mpu6050.h"
#include "math.h"
#include "usart2.h"
#include "string.h"
/*********************************************************
Copyright (C), 2013-2023, YFRobot.
www.yfrobot.com
File：自平衡小车
Author：aosini    Version:1.0     Data:2014/07/02
Description: 用电机驱动控制电机的转速及转向，通过mpu6050测得小车的角度及角速度，用测得的数据经过算法，
             输出合适的MPW,使小车能够站立，再利用蓝牙，实现手机控制小车。
History:
**********************************************************/

/**********************实验七：安卓手机端应用控制小车**************************/
/*		手机端通过蓝牙向小车发送信息，小车只有在接收到“w”、“x”、“a”、“d”、“s”后小
    车才会有相应的动作。在安装打开“Robot-M”后，点击“设置”，设置发送的字符。

实验现象:蓝牙连接后，通过手机控制小车的前进、后退、向左、向右，也可以点击软件右上
        角按钮，打开重力感应模式，通过手机角度的变化，来控制小车。	
*/
#define PI 3.14159
//角度参数
float Angle, Angle_dot;   //小车最终倾斜角度、角速度
float Angle_aYZ;          //由Y轴Z轴上的加速度传感器测得的数值，计算出倾斜角度
float Angle_gX;           //由X轴的陀螺仪传感器测得的数值，计算出角速度
//卡尔曼参数		
float  Q_angle=0.002;            
float  Q_gyro=0.01;              
float  R_angle=0.003;	//角度测量速度快，延迟低

//float  Q_angle=0.001;            
//float  Q_gyro=0.003;              
//float  R_angle=0.5;	


float  dt=0.005;	       //dt为kalman滤波器采样时间;
char   C_0 = 1;
float  Q_bias, Angle_err;
float  PCt_0, PCt_1, E;
float  K_0, K_1, t_0, t_1;
float  Pdot[4] ={0,0,0,0};
float  PP[2][2] = { { 1, 0 },{ 0, 1 } };
// 卡尔曼滤波
void Kalman_Filter(float Accel,float Gyro)		
{
	Angle+=(Gyro - Q_bias) * dt; //先验估计

	Pdot[0]=Q_angle - PP[0][1] - PP[1][0]; // Pk-先验估计误差协方差的微分

	Pdot[1]=- PP[1][1];
	Pdot[2]=- PP[1][1];
	Pdot[3]=Q_gyro;
	
	PP[0][0] += Pdot[0] * dt;   // Pk-先验估计误差协方差微分的积分
	PP[0][1] += Pdot[1] * dt;   // =先验估计误差协方差
	PP[1][0] += Pdot[2] * dt;
	PP[1][1] += Pdot[3] * dt;
		
	Angle_err = Accel - Angle;	//zk-先验估计
	
	PCt_0 = C_0 * PP[0][0];
	PCt_1 = C_0 * PP[1][0];
	
	E = R_angle + C_0 * PCt_0;
	
	K_0 = PCt_0 / E;
	K_1 = PCt_1 / E;
	
	t_0 = PCt_0;
	t_1 = C_0 * PP[0][1];

	PP[0][0] -= K_0 * t_0;		 //后验估计误差协方差
	PP[0][1] -= K_0 * t_1;
	PP[1][0] -= K_1 * t_0;
	PP[1][1] -= K_1 * t_1;
		
	Angle	+= K_0 * Angle_err;	 //后验估计
	Q_bias	+= K_1 * Angle_err;	 //后验估计
	Angle_dot = Gyro - Q_bias; //输出值(后验估计)的微分=角速度
}
//倾角计算（卡尔曼融合）
void Angle_Calcu(void)	 
{
	//------根据加速度分量测得角速度--------------------------
    //不自测，加速度传感器范围设置  0  ±2g	 16384 LSB/g
	Angle_aYZ = atan2((Out_Data(ACCEL_YOUT_H) - 300), (Out_Data(ACCEL_ZOUT_H)-(16384-16450))) *180/PI ;   //去除零点偏移,计算得到角度（弧度）
	//弧度转换为度,

    //-------角加速度-------------------------
//	//不自测，陀螺仪测量范围设置	 0  ±250°/s  131LSB/(°/s)	0.00763358 (°/s)/LSB
//  Angle_gX = (Out_Data(GYRO_XOUT_H)-0) * 0.00763358 ;//0为补偿量，在静止是测得的角速度为120LSB；

	//不自测，陀螺仪测量范围设置	 1  ±500°/s  65.5LSB/(°/s)	0.01526 (°/s)/LSB
    Angle_gX = (Out_Data(GYRO_XOUT_H)-0) * 0.01526  ;//0为补偿量，在静止是测得的角速度为120LSB；	
													  

	//-------卡尔曼滤波融合-----------------------
	Kalman_Filter(Angle_aYZ - 0, Angle_gX - 0);       //卡尔曼滤波计算倾角,减去零点偏移，
}

/*************PID控制调节*********************************************************************/
float PWM, PWM_L, PWM_R;
float Kp = 61, Ki = 7.5, Kd = 2.3, Kk = 0.005;	   // //如果只要平衡，可以不要position * Kk 
float err, speed_need = 0,turn_need = 0;	 //speed_need = 300,turn_need = 20
float position_dot, position_dot_filter, position;
void PID(float setPoint)
{
    position_dot = (TIM2_Encoder_Read_1() + TIM4_Encoder_Read_2())*0.5;//编码器值读出
	position_dot_filter	*= 0.85;
	position_dot_filter += position_dot*0.15; 
	position +=	position_dot_filter;  //电机行驶距离由position_dot_filter累加而来 
	position += speed_need; //给小车一定速度
	if(position > 90000)   
	{
	    position = 90000; 
	}
	else if(position < -90000)
	{
	    position = -90000;
	}
	err = Angle - setPoint;		//得到实际偏差角度
	if(err<-30 || err>30)   //角度过大，关闭电机 
	{  
	    M1_1 = 1;
		M1_2 = 1; //电机1刹车
		M2_1 = 1;
		M2_2 = 1; //电机2刹车
	    return;
	}    
	PWM = - err*Kp 
	      - Angle_dot*Ki 
	      + position_dot_filter*Kd 	  
		  + position*Kk;	//如果只要平衡，可以不要position * Kk 
	PWM_L = PWM + turn_need ;
	PWM_R = PWM - turn_need ;
	Motor_Speed_Control(PWM_L, PWM_R);   //电机输出
}																						  
	
int main(void)
{
	u8 reclen=0;//数据长度
	Stm32_Clock_Init(9); //系统时钟设置
	delay_init(72);	     //延时初始化
	uart_init(72,9600);  //串口1初始化
	USART2_Init(36,9600);//串口2初始化
	M_Init();		  	 //初始化与TB6612连接的硬件接口
	TIM3_PWM_Init(900,0);//不分频。PWM频率=72000/900=80Khz
	TIM2_Encoder_Init_1(0xffff, 0);
	TIM4_Encoder_Init_2(0xffff, 0);
	delay_ms(200);
	MPU6050_Init();	
    while(1)
	{
    	if(USART2_RX_STA&0X8000)			//接收到一次数据了
		{	
			LED =! LED;
 			reclen = USART2_RX_STA&0X7FFF;	//得到数据长度
		  	USART2_RX_BUF[reclen] = 0;	 	//加入结束符
			u2_printf("C%s\r\n",USART2_RX_BUF);	//判断接收的数据，并做出相应动作
			if(USART2_RX_BUF[0] == 'w')  {speed_need = -800; turn_need = 0;}	
			else if(USART2_RX_BUF[0] == 'x')  {speed_need = 800; turn_need = 0;}
			else if(USART2_RX_BUF[0] == 'a')  {turn_need = -160; speed_need = 0;}
			else if(USART2_RX_BUF[0] == 'd')  {turn_need = 160; speed_need = 0;}
			else if(USART2_RX_BUF[0] == 's')  {speed_need = 0; turn_need = 0;}
 			USART2_RX_STA=0;	 
		}
		TIM2_Encoder_Write_1(0);   //计数器清零
		TIM4_Encoder_Write_2(0);   //计数器清零
	    delay_ms(5);
		Angle_Calcu();			  //角度与角速度运算
		PID(-0.5);				  //修正角度 -1.3
	//	printf("角度：%f 角速度：%f\n",Angle,Angle_dot); //输出小车倾斜角度与旋转速度
	}
}




/**********************实验六：PID参数设定求出合适的PWM**************************/
/*实验现象:	此实验的结果不会轻松实现，需要我们耐心的调试。
       1、给下面变量赋值Kp = 65, Ki = 6.5, Kd = 2.5, Kk = 0; 
	   2、垂直校正，在垂直时测得角度为“-1.3”，PID(-1.3);	
	   因为每个人使用的模块也都不同，每辆小车的各个参数都是有区别的，所以上面给出的只是
	   参考数值，参数需要根据自己小车的实际状态进行修改。在相同参数的情况下，因为电量的
	   不同，小车的站立效果都会不一样。
	   祝大家小车快点站起来！！！
*/
//#define PI 3.14159
////角度参数
//float Angle, Angle_dot;   //小车最终倾斜角度、角速度
//float Angle_aYZ;          //由Y轴Z轴上的加速度传感器测得的数值，计算出倾斜角度
//float Angle_gX;           //由X轴的陀螺仪传感器测得的数值，计算出角速度
////卡尔曼参数		
//float  Q_angle=0.002;            
//float  Q_gyro=0.01;              
//float  R_angle=0.003;	//角度测量速度快，延迟低
//
////float  Q_angle=0.001;            
////float  Q_gyro=0.003;              
////float  R_angle=0.5;	
//
//
//float  dt=0.005;	       //dt为kalman滤波器采样时间;
//char   C_0 = 1;
//float  Q_bias, Angle_err;
//float  PCt_0, PCt_1, E;
//float  K_0, K_1, t_0, t_1;
//float  Pdot[4] ={0,0,0,0};
//float  PP[2][2] = { { 1, 0 },{ 0, 1 } };
//// 卡尔曼滤波
//void Kalman_Filter(float Accel,float Gyro)		
//{
//	Angle+=(Gyro - Q_bias) * dt; //先验估计
//
//	Pdot[0]=Q_angle - PP[0][1] - PP[1][0]; // Pk-先验估计误差协方差的微分
//
//	Pdot[1]=- PP[1][1];
//	Pdot[2]=- PP[1][1];
//	Pdot[3]=Q_gyro;
//	
//	PP[0][0] += Pdot[0] * dt;   // Pk-先验估计误差协方差微分的积分
//	PP[0][1] += Pdot[1] * dt;   // =先验估计误差协方差
//	PP[1][0] += Pdot[2] * dt;
//	PP[1][1] += Pdot[3] * dt;
//		
//	Angle_err = Accel - Angle;	//zk-先验估计
//	
//	PCt_0 = C_0 * PP[0][0];
//	PCt_1 = C_0 * PP[1][0];
//	
//	E = R_angle + C_0 * PCt_0;
//	
//	K_0 = PCt_0 / E;
//	K_1 = PCt_1 / E;
//	
//	t_0 = PCt_0;
//	t_1 = C_0 * PP[0][1];
//
//	PP[0][0] -= K_0 * t_0;		 //后验估计误差协方差
//	PP[0][1] -= K_0 * t_1;
//	PP[1][0] -= K_1 * t_0;
//	PP[1][1] -= K_1 * t_1;
//		
//	Angle	+= K_0 * Angle_err;	 //后验估计
//	Q_bias	+= K_1 * Angle_err;	 //后验估计
//	Angle_dot = Gyro - Q_bias; //输出值(后验估计)的微分=角速度
//}
////倾角计算（卡尔曼融合）
//void Angle_Calcu(void)	 
//{
//	//------根据加速度分量测得角速度--------------------------
//    //不自测，加速度传感器范围设置  0  ±2g	 16384 LSB/g
//	Angle_aYZ = atan2((Out_Data(ACCEL_YOUT_H) - 300), (Out_Data(ACCEL_ZOUT_H)-(16384-16450))) *180/PI ;   //去除零点偏移,计算得到角度（弧度）
//	//弧度转换为度,
//
//    //-------角加速度-------------------------
////	//不自测，陀螺仪测量范围设置	 0  ±250°/s  131LSB/(°/s)	0.00763358 (°/s)/LSB
////  Angle_gX = (Out_Data(GYRO_XOUT_H)-0) * 0.00763358 ;//0为补偿量，在静止是测得的角速度为120LSB；
//
//	//不自测，陀螺仪测量范围设置	 1  ±500°/s  65.5LSB/(°/s)	0.01526 (°/s)/LSB
//    Angle_gX = (Out_Data(GYRO_XOUT_H)-0) * 0.01526  ;//0为补偿量，在静止是测得的角速度为120LSB；	
//													  
//
//	//-------卡尔曼滤波融合-----------------------
//	Kalman_Filter(Angle_aYZ - 0, Angle_gX - 0);       //卡尔曼滤波计算倾角,减去零点偏移，
//}
//
///*************PID控制调节*********************************************************************/
//float PWM, PWM_L, PWM_R;
//float Kp = 65, Ki = 6.5, Kd = 2.1, Kk = 0.005;	   // //如果只要平衡，可以不要position * Kk 
//float err, speed_need = 0,turn_need = 0;	 //speed_need = 300,turn_need = 20
//float position_dot, position_dot_filter, position;
//void PID(float setPoint)
//{
//    position_dot = (TIM2_Encoder_Read_1() + TIM4_Encoder_Read_2())*0.5;//编码器值读出
//	position_dot_filter	*= 0.85;
//	position_dot_filter += position_dot*0.15; 
//	position +=	position_dot_filter;  //电机行驶距离由position_dot_filter累加而来 
//	position += speed_need; //给小车一定速度
//	if(position > 90000)   
//	{
//	    position = 90000; 
//	}
//	else if(position < -90000)
//	{
//	    position = -90000;
//	}
//	if(Angle<-40 || Angle>40)               //角度过大，关闭电机 
//	{  
//	    M1_1 = 1;
//		M1_2 = 1; //电机1刹车
//		M2_1 = 1;
//		M2_2 = 1; //电机2刹车
//	    return;
//	}
//    err = Angle - setPoint;		//得到实际偏差角度
//	PWM = - err*Kp 
//	      - Angle_dot*Ki 
//	      + position_dot_filter*Kd 	  
//		  + position*Kk;	//如果只要平衡，可以不要position * Kk 
//	PWM_L = PWM + turn_need ;
//	PWM_R = PWM - turn_need ;
//	Motor_Speed_Control(PWM_L, PWM_R);   //电机输出
//}																						  
//	
//int main(void)
//{
//	Stm32_Clock_Init(9); //系统时钟设置
//	delay_init(72);	     //延时初始化
//	uart_init(72,9600);  //串口1初始化
//    LED_Init();
//	M_Init();		  	 //初始化与TB6612连接的硬件接口
//	TIM3_PWM_Init(900,0);//不分频。PWM频率=72000/900=80Khz
//	TIM2_Encoder_Init_1(0xffff, 0);
//	TIM4_Encoder_Init_2(0xffff, 0);
//	delay_ms(200);
//	MPU6050_Init();	
//    while(1)
//	{
//		TIM2_Encoder_Write_1(0);   //计数器清零
//		TIM4_Encoder_Write_2(0);   //计数器清零
//	    delay_ms(5);
//		Angle_Calcu();			  //角度与角速度运算
//		PID(-1.3);				  //修正角度 -1.3
//	}
//}
																					  




/**********************实验五：卡尔曼与角度角速度计算**************************/
/*实验现象:倾角：指的是小车的中心线与垂线之间的角度；
		   角速度：指的是小车倾倒的角速度。
           小车垂直静止于桌面时，倾斜角Angle与角速度Angle_dot为“零”，这里的“零”
           指的是在一定范围内。
	Angle：过了垂直角度，向右倾倒时（右视图），Angle的角度小于0（负数），与垂直方向之间的角度越大，
		   Angle值越小；向左倾倒时（右视图），Angle的角度大于0（正数），与垂直方向之间的角度越大，
		   Angle值越大；
Angle_dot：小车顺时针速旋转时（右视图），Angle_dot小于0（负数），速度越大，值越小
		   小车逆时针速旋转时（右视图），Angle_dot大于0（正数），速度越大，值越大
*/
//#define PI 3.14159
////角度参数
//float Angle, Angle_dot;   //小车最终倾斜角度、角速度
//float Angle_aYZ;          //由Y轴Z轴上的加速度传感器测得的数值，计算出倾斜角度
//float Angle_gX;           //由X轴的陀螺仪传感器测得的数值，计算出角速度
////卡尔曼参数		
//float  Q_angle=0.01;            
//float  Q_gyro=0.01;              
//float  R_angle=0.003;	
//float  dt=0.005;	       //dt为kalman滤波器采样时间;
//char   C_0 = 1;
//float  Q_bias, Angle_err;
//float  PCt_0, PCt_1, E;
//float  K_0, K_1, t_0, t_1;
//float  Pdot[4] ={0,0,0,0};
//float  PP[2][2] = { { 1, 0 },{ 0, 1 } };
//// 卡尔曼滤波
//void Kalman_Filter(float Accel,float Gyro)		
//{
//	Angle+=(Gyro - Q_bias) * dt; //先验估计
//
//	Pdot[0]=Q_angle - PP[0][1] - PP[1][0]; // Pk-先验估计误差协方差的微分
//
//	Pdot[1]=- PP[1][1];
//	Pdot[2]=- PP[1][1];
//	Pdot[3]=Q_gyro;
//	
//	PP[0][0] += Pdot[0] * dt;   // Pk-先验估计误差协方差微分的积分
//	PP[0][1] += Pdot[1] * dt;   // =先验估计误差协方差
//	PP[1][0] += Pdot[2] * dt;
//	PP[1][1] += Pdot[3] * dt;
//		
//	Angle_err = Accel - Angle;	//zk-先验估计
//	
//	PCt_0 = C_0 * PP[0][0];
//	PCt_1 = C_0 * PP[1][0];
//	
//	E = R_angle + C_0 * PCt_0;
//	
//	K_0 = PCt_0 / E;
//	K_1 = PCt_1 / E;
//	
//	t_0 = PCt_0;
//	t_1 = C_0 * PP[0][1];
//
//	PP[0][0] -= K_0 * t_0;		 //后验估计误差协方差
//	PP[0][1] -= K_0 * t_1;
//	PP[1][0] -= K_1 * t_0;
//	PP[1][1] -= K_1 * t_1;
//		
//	Angle	+= K_0 * Angle_err;	 //后验估计
//	Q_bias	+= K_1 * Angle_err;	 //后验估计
//	Angle_dot = Gyro - Q_bias; //输出值(后验估计)的微分=角速度
//}
////倾角计算（卡尔曼融合）
//void Angle_Calcu(void)	 
//{
//	//------根据加速度分量测得角速度--------------------------
//    //不自测，加速度传感器范围设置  0  ±2g	 16384 LSB/g
//	Angle_aYZ = atan2((Out_Data(ACCEL_YOUT_H) - 300), (Out_Data(ACCEL_ZOUT_H)-(16384-16450))) *180/PI ;   //去除零点偏移,计算得到角度（弧度）
//	//弧度转换为度,
//
//    //-------角速度-------------------------
//	//不自测，陀螺仪测量范围设置	 0  ±250°/s  131LSB/(°/s)	0.00763358 (°/s)/LSB
//    Angle_gX = (Out_Data(GYRO_XOUT_H)-0) *0.00763358 ;//0为补偿量，在静止是测得的角速度为0LSB；
//		
//	//-------卡尔曼滤波融合-----------------------
//	Kalman_Filter(Angle_aYZ - 0, Angle_gX - 0);       //卡尔曼滤波计算倾角,减去零点偏移，
//}
//int main(void)
//{
//	Stm32_Clock_Init(9); //系统时钟设置
//	delay_init(72);	     //延时初始化
//	uart_init(72,9600);  //串口1初始化
//    delay_ms(200);
//	MPU6050_Init();	
//    while(1)
//	{
//	    delay_ms(5);
//		Angle_Calcu();
//		printf("角度：%f 角速度：%f\n",Angle,Angle_dot); //输出小车倾斜角度与旋转速度
//	}
//}


/*********************实验四：MPU6050***************************/
/*实验现象；将传感器水平放置时，ACC: X=0  Y=0  Z=16384  GYRO:X=0  Y=0  Z=0  TEMP_OUT: 30.59 
		   当然这只是一个理想状况下绝对水平，测量无误差的状况下才会有的结果。在实际的测量时，
		   结果是在不停的变化的，当然在传感器不动的状态下，输出的变化保持在一定的范围之内。
		   试着改变传感器的状态，看串口输出值变化特点。请参考图：传感器轴的方向与旋转的极性。
		   TEMP_OUT:的值没有太大的变化，当您用手放在MPU6050上面时输出的值渐渐的变大。
*/
//int main(void)
//{
//	Stm32_Clock_Init(9); //系统时钟设置
//	delay_init(72);	     //延时初始化
//	uart_init(72,9600);  //串口1初始化
//	MPU6050_Init();
//	while(1)
//	{
//		delay_ms(500);
//		printf("ACC: X=%6d  Y=%6d  Z=%6d   ", 
//				Out_Data(ACCEL_XOUT_H), Out_Data(ACCEL_YOUT_H), Out_Data(ACCEL_ZOUT_H) );
//		printf("GYRO:X=%6d  Y=%6d  Z=%6d   ", 
//				Out_Data(GYRO_XOUT_H), Out_Data(GYRO_YOUT_H), Out_Data(GYRO_ZOUT_H) );
//		printf("TEMP_OUT: %.2f \n", (float)(Out_Data(TEMP_OUT_H)/(float)340)+36.53	);
//	}
//}


/****************实验三；编码器与速度检测***********************/
/*实验现象：此实验与实验二类似，只是在原有基础上添加了编码器功能，
            在电机转动的同时，通过串口将测得的速度输出，在电机向前
			转动时，串口输出值为正；电机向后转动时，串口输出为负。
speed的范围（-900~+900）
*/
//int main(void)
//{
//	s16 speed = 900;
//	Stm32_Clock_Init(9); //系统时钟设置
//	delay_init(72);	     //延时初始化
//	uart_init(72,9600);  //串口1初始化
//	LED_Init();
//	M_Init();
//	TIM3_PWM_Init(900,0); 
//	TIM2_Encoder_Init_1(0xffff, 0);
//	TIM4_Encoder_Init_2(0xffff, 0);
//	
//	while(1)
//	{		
//		if(speed == -900)
//		{
//			speed = 900;
//			LED =! LED;
//			Motor_Speed_Control(0, 0);
//			delay_ms(500);
//		}
//		speed--;
//		TIM2_Encoder_Write_1(0);
//		TIM4_Encoder_Write_2(0);
//		Motor_Speed_Control(speed, speed);
//		delay_ms(5);
//		printf("编码器值1：%4d ;编码器值2：%4d \n",
//		     TIM2_Encoder_Read_1(),TIM4_Encoder_Read_2());
//	}
//}


/****************实验二；电机变速运行********************/
/*实验现象：电机以最快速度正转（右侧看，电机顺时针转动），
      		速度渐渐地减小，直到电机停止，渐渐地电机向后
			转动（右侧看，电机逆时针转动）速度不断加快，
 			直到转速最快后电机突然刹车，并静止0.5s，完成
			一个周期。并不断循环。
speed的范围（-900~+900）
*/
//int main(void)
//{
//    s16 speed = 900;
//    Stm32_Clock_Init(9); //系统时钟设置
//    delay_init(72);	     //延时初始化
//    uart_init(72,9600);  //串口1初始化
//    LED_Init();
//    M_Init();
//	  TIM3_PWM_Init(900,0); //设定自动装载值为900，不分频。PWM频率=72000/900=80Khz
//    while(1)
//    {
//	     if(speed == -900)
//    	 {
//		     speed = 900;
//			 LED =!LED;
//		     Motor_Speed_Control(0, 0);
//	         delay_ms(500 );
//	     }
//	     speed--;
//	     delay_ms(5 );
//	     Motor_Speed_Control(speed, speed);
//	}  
//}


/************实验一；点亮“STATE”***************/
/*实验现象：灯“STATE”每隔500ms改变一次点亮方式*/
//int main(void)
//{
//    Stm32_Clock_Init(9); //系统时钟设置
//    delay_init(72);	     //延时初始化
//    LED_Init();
//    while(1)
//    {
//        LED =!LED;
//        delay_ms(500);
//    }
//}
