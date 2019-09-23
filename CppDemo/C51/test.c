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
File����ƽ��С��
Author��aosini    Version:1.0     Data:2014/07/02
Description: �õ���������Ƶ����ת�ټ�ת��ͨ��mpu6050���С���ĽǶȼ����ٶȣ��ò�õ����ݾ����㷨��
             ������ʵ�MPW,ʹС���ܹ�վ����������������ʵ���ֻ�����С����
History:
**********************************************************/

/**********************ʵ���ߣ���׿�ֻ���Ӧ�ÿ���С��**************************/
/*		�ֻ���ͨ��������С��������Ϣ��С��ֻ���ڽ��յ���w������x������a������d������s����С
    ���Ż�����Ӧ�Ķ������ڰ�װ�򿪡�Robot-M���󣬵�������á������÷��͵��ַ���

ʵ������:�������Ӻ�ͨ���ֻ�����С����ǰ�������ˡ��������ң�Ҳ���Ե���������
        �ǰ�ť����������Ӧģʽ��ͨ���ֻ��Ƕȵı仯��������С����	
*/
#define PI 3.14159
//�ǶȲ���
float Angle, Angle_dot;   //С��������б�Ƕȡ����ٶ�
float Angle_aYZ;          //��Y��Z���ϵļ��ٶȴ�������õ���ֵ���������б�Ƕ�
float Angle_gX;           //��X��������Ǵ�������õ���ֵ����������ٶ�
//����������		
float  Q_angle=0.002;            
float  Q_gyro=0.01;              
float  R_angle=0.003;	//�ǶȲ����ٶȿ죬�ӳٵ�

//float  Q_angle=0.001;            
//float  Q_gyro=0.003;              
//float  R_angle=0.5;	


float  dt=0.005;	       //dtΪkalman�˲�������ʱ��;
char   C_0 = 1;
float  Q_bias, Angle_err;
float  PCt_0, PCt_1, E;
float  K_0, K_1, t_0, t_1;
float  Pdot[4] ={0,0,0,0};
float  PP[2][2] = { { 1, 0 },{ 0, 1 } };
// �������˲�
void Kalman_Filter(float Accel,float Gyro)		
{
	Angle+=(Gyro - Q_bias) * dt; //�������

	Pdot[0]=Q_angle - PP[0][1] - PP[1][0]; // Pk-����������Э�����΢��

	Pdot[1]=- PP[1][1];
	Pdot[2]=- PP[1][1];
	Pdot[3]=Q_gyro;
	
	PP[0][0] += Pdot[0] * dt;   // Pk-����������Э����΢�ֵĻ���
	PP[0][1] += Pdot[1] * dt;   // =����������Э����
	PP[1][0] += Pdot[2] * dt;
	PP[1][1] += Pdot[3] * dt;
		
	Angle_err = Accel - Angle;	//zk-�������
	
	PCt_0 = C_0 * PP[0][0];
	PCt_1 = C_0 * PP[1][0];
	
	E = R_angle + C_0 * PCt_0;
	
	K_0 = PCt_0 / E;
	K_1 = PCt_1 / E;
	
	t_0 = PCt_0;
	t_1 = C_0 * PP[0][1];

	PP[0][0] -= K_0 * t_0;		 //����������Э����
	PP[0][1] -= K_0 * t_1;
	PP[1][0] -= K_1 * t_0;
	PP[1][1] -= K_1 * t_1;
		
	Angle	+= K_0 * Angle_err;	 //�������
	Q_bias	+= K_1 * Angle_err;	 //�������
	Angle_dot = Gyro - Q_bias; //���ֵ(�������)��΢��=���ٶ�
}
//��Ǽ��㣨�������ںϣ�
void Angle_Calcu(void)	 
{
	//------���ݼ��ٶȷ�����ý��ٶ�--------------------------
    //���Բ⣬���ٶȴ�������Χ����  0  ��2g	 16384 LSB/g
	Angle_aYZ = atan2((Out_Data(ACCEL_YOUT_H) - 300), (Out_Data(ACCEL_ZOUT_H)-(16384-16450))) *180/PI ;   //ȥ�����ƫ��,����õ��Ƕȣ����ȣ�
	//����ת��Ϊ��,

    //-------�Ǽ��ٶ�-------------------------
//	//���Բ⣬�����ǲ�����Χ����	 0  ��250��/s  131LSB/(��/s)	0.00763358 (��/s)/LSB
//  Angle_gX = (Out_Data(GYRO_XOUT_H)-0) * 0.00763358 ;//0Ϊ���������ھ�ֹ�ǲ�õĽ��ٶ�Ϊ120LSB��

	//���Բ⣬�����ǲ�����Χ����	 1  ��500��/s  65.5LSB/(��/s)	0.01526 (��/s)/LSB
    Angle_gX = (Out_Data(GYRO_XOUT_H)-0) * 0.01526  ;//0Ϊ���������ھ�ֹ�ǲ�õĽ��ٶ�Ϊ120LSB��	
													  

	//-------�������˲��ں�-----------------------
	Kalman_Filter(Angle_aYZ - 0, Angle_gX - 0);       //�������˲��������,��ȥ���ƫ�ƣ�
}

/*************PID���Ƶ���*********************************************************************/
float PWM, PWM_L, PWM_R;
float Kp = 61, Ki = 7.5, Kd = 2.3, Kk = 0.005;	   // //���ֻҪƽ�⣬���Բ�Ҫposition * Kk 
float err, speed_need = 0,turn_need = 0;	 //speed_need = 300,turn_need = 20
float position_dot, position_dot_filter, position;
void PID(float setPoint)
{
    position_dot = (TIM2_Encoder_Read_1() + TIM4_Encoder_Read_2())*0.5;//������ֵ����
	position_dot_filter	*= 0.85;
	position_dot_filter += position_dot*0.15; 
	position +=	position_dot_filter;  //�����ʻ������position_dot_filter�ۼӶ��� 
	position += speed_need; //��С��һ���ٶ�
	if(position > 90000)   
	{
	    position = 90000; 
	}
	else if(position < -90000)
	{
	    position = -90000;
	}
	err = Angle - setPoint;		//�õ�ʵ��ƫ��Ƕ�
	if(err<-30 || err>30)   //�Ƕȹ��󣬹رյ�� 
	{  
	    M1_1 = 1;
		M1_2 = 1; //���1ɲ��
		M2_1 = 1;
		M2_2 = 1; //���2ɲ��
	    return;
	}    
	PWM = - err*Kp 
	      - Angle_dot*Ki 
	      + position_dot_filter*Kd 	  
		  + position*Kk;	//���ֻҪƽ�⣬���Բ�Ҫposition * Kk 
	PWM_L = PWM + turn_need ;
	PWM_R = PWM - turn_need ;
	Motor_Speed_Control(PWM_L, PWM_R);   //������
}																						  
	
int main(void)
{
	u8 reclen=0;//���ݳ���
	Stm32_Clock_Init(9); //ϵͳʱ������
	delay_init(72);	     //��ʱ��ʼ��
	uart_init(72,9600);  //����1��ʼ��
	USART2_Init(36,9600);//����2��ʼ��
	M_Init();		  	 //��ʼ����TB6612���ӵ�Ӳ���ӿ�
	TIM3_PWM_Init(900,0);//����Ƶ��PWMƵ��=72000/900=80Khz
	TIM2_Encoder_Init_1(0xffff, 0);
	TIM4_Encoder_Init_2(0xffff, 0);
	delay_ms(200);
	MPU6050_Init();	
    while(1)
	{
    	if(USART2_RX_STA&0X8000)			//���յ�һ��������
		{	
			LED =! LED;
 			reclen = USART2_RX_STA&0X7FFF;	//�õ����ݳ���
		  	USART2_RX_BUF[reclen] = 0;	 	//���������
			u2_printf("C%s\r\n",USART2_RX_BUF);	//�жϽ��յ����ݣ���������Ӧ����
			if(USART2_RX_BUF[0] == 'w')  {speed_need = -800; turn_need = 0;}	
			else if(USART2_RX_BUF[0] == 'x')  {speed_need = 800; turn_need = 0;}
			else if(USART2_RX_BUF[0] == 'a')  {turn_need = -160; speed_need = 0;}
			else if(USART2_RX_BUF[0] == 'd')  {turn_need = 160; speed_need = 0;}
			else if(USART2_RX_BUF[0] == 's')  {speed_need = 0; turn_need = 0;}
 			USART2_RX_STA=0;	 
		}
		TIM2_Encoder_Write_1(0);   //����������
		TIM4_Encoder_Write_2(0);   //����������
	    delay_ms(5);
		Angle_Calcu();			  //�Ƕ�����ٶ�����
		PID(-0.5);				  //�����Ƕ� -1.3
	//	printf("�Ƕȣ�%f ���ٶȣ�%f\n",Angle,Angle_dot); //���С����б�Ƕ�����ת�ٶ�
	}
}




/**********************ʵ������PID�����趨������ʵ�PWM**************************/
/*ʵ������:	��ʵ��Ľ����������ʵ�֣���Ҫ�������ĵĵ��ԡ�
       1�������������ֵKp = 65, Ki = 6.5, Kd = 2.5, Kk = 0; 
	   2����ֱУ�����ڴ�ֱʱ��ýǶ�Ϊ��-1.3����PID(-1.3);	
	   ��Ϊÿ����ʹ�õ�ģ��Ҳ����ͬ��ÿ��С���ĸ�����������������ģ��������������ֻ��
	   �ο���ֵ��������Ҫ�����Լ�С����ʵ��״̬�����޸ġ�����ͬ����������£���Ϊ������
	   ��ͬ��С����վ��Ч�����᲻һ����
	   ף���С�����վ����������
*/
//#define PI 3.14159
////�ǶȲ���
//float Angle, Angle_dot;   //С��������б�Ƕȡ����ٶ�
//float Angle_aYZ;          //��Y��Z���ϵļ��ٶȴ�������õ���ֵ���������б�Ƕ�
//float Angle_gX;           //��X��������Ǵ�������õ���ֵ����������ٶ�
////����������		
//float  Q_angle=0.002;            
//float  Q_gyro=0.01;              
//float  R_angle=0.003;	//�ǶȲ����ٶȿ죬�ӳٵ�
//
////float  Q_angle=0.001;            
////float  Q_gyro=0.003;              
////float  R_angle=0.5;	
//
//
//float  dt=0.005;	       //dtΪkalman�˲�������ʱ��;
//char   C_0 = 1;
//float  Q_bias, Angle_err;
//float  PCt_0, PCt_1, E;
//float  K_0, K_1, t_0, t_1;
//float  Pdot[4] ={0,0,0,0};
//float  PP[2][2] = { { 1, 0 },{ 0, 1 } };
//// �������˲�
//void Kalman_Filter(float Accel,float Gyro)		
//{
//	Angle+=(Gyro - Q_bias) * dt; //�������
//
//	Pdot[0]=Q_angle - PP[0][1] - PP[1][0]; // Pk-����������Э�����΢��
//
//	Pdot[1]=- PP[1][1];
//	Pdot[2]=- PP[1][1];
//	Pdot[3]=Q_gyro;
//	
//	PP[0][0] += Pdot[0] * dt;   // Pk-����������Э����΢�ֵĻ���
//	PP[0][1] += Pdot[1] * dt;   // =����������Э����
//	PP[1][0] += Pdot[2] * dt;
//	PP[1][1] += Pdot[3] * dt;
//		
//	Angle_err = Accel - Angle;	//zk-�������
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
//	PP[0][0] -= K_0 * t_0;		 //����������Э����
//	PP[0][1] -= K_0 * t_1;
//	PP[1][0] -= K_1 * t_0;
//	PP[1][1] -= K_1 * t_1;
//		
//	Angle	+= K_0 * Angle_err;	 //�������
//	Q_bias	+= K_1 * Angle_err;	 //�������
//	Angle_dot = Gyro - Q_bias; //���ֵ(�������)��΢��=���ٶ�
//}
////��Ǽ��㣨�������ںϣ�
//void Angle_Calcu(void)	 
//{
//	//------���ݼ��ٶȷ�����ý��ٶ�--------------------------
//    //���Բ⣬���ٶȴ�������Χ����  0  ��2g	 16384 LSB/g
//	Angle_aYZ = atan2((Out_Data(ACCEL_YOUT_H) - 300), (Out_Data(ACCEL_ZOUT_H)-(16384-16450))) *180/PI ;   //ȥ�����ƫ��,����õ��Ƕȣ����ȣ�
//	//����ת��Ϊ��,
//
//    //-------�Ǽ��ٶ�-------------------------
////	//���Բ⣬�����ǲ�����Χ����	 0  ��250��/s  131LSB/(��/s)	0.00763358 (��/s)/LSB
////  Angle_gX = (Out_Data(GYRO_XOUT_H)-0) * 0.00763358 ;//0Ϊ���������ھ�ֹ�ǲ�õĽ��ٶ�Ϊ120LSB��
//
//	//���Բ⣬�����ǲ�����Χ����	 1  ��500��/s  65.5LSB/(��/s)	0.01526 (��/s)/LSB
//    Angle_gX = (Out_Data(GYRO_XOUT_H)-0) * 0.01526  ;//0Ϊ���������ھ�ֹ�ǲ�õĽ��ٶ�Ϊ120LSB��	
//													  
//
//	//-------�������˲��ں�-----------------------
//	Kalman_Filter(Angle_aYZ - 0, Angle_gX - 0);       //�������˲��������,��ȥ���ƫ�ƣ�
//}
//
///*************PID���Ƶ���*********************************************************************/
//float PWM, PWM_L, PWM_R;
//float Kp = 65, Ki = 6.5, Kd = 2.1, Kk = 0.005;	   // //���ֻҪƽ�⣬���Բ�Ҫposition * Kk 
//float err, speed_need = 0,turn_need = 0;	 //speed_need = 300,turn_need = 20
//float position_dot, position_dot_filter, position;
//void PID(float setPoint)
//{
//    position_dot = (TIM2_Encoder_Read_1() + TIM4_Encoder_Read_2())*0.5;//������ֵ����
//	position_dot_filter	*= 0.85;
//	position_dot_filter += position_dot*0.15; 
//	position +=	position_dot_filter;  //�����ʻ������position_dot_filter�ۼӶ��� 
//	position += speed_need; //��С��һ���ٶ�
//	if(position > 90000)   
//	{
//	    position = 90000; 
//	}
//	else if(position < -90000)
//	{
//	    position = -90000;
//	}
//	if(Angle<-40 || Angle>40)               //�Ƕȹ��󣬹رյ�� 
//	{  
//	    M1_1 = 1;
//		M1_2 = 1; //���1ɲ��
//		M2_1 = 1;
//		M2_2 = 1; //���2ɲ��
//	    return;
//	}
//    err = Angle - setPoint;		//�õ�ʵ��ƫ��Ƕ�
//	PWM = - err*Kp 
//	      - Angle_dot*Ki 
//	      + position_dot_filter*Kd 	  
//		  + position*Kk;	//���ֻҪƽ�⣬���Բ�Ҫposition * Kk 
//	PWM_L = PWM + turn_need ;
//	PWM_R = PWM - turn_need ;
//	Motor_Speed_Control(PWM_L, PWM_R);   //������
//}																						  
//	
//int main(void)
//{
//	Stm32_Clock_Init(9); //ϵͳʱ������
//	delay_init(72);	     //��ʱ��ʼ��
//	uart_init(72,9600);  //����1��ʼ��
//    LED_Init();
//	M_Init();		  	 //��ʼ����TB6612���ӵ�Ӳ���ӿ�
//	TIM3_PWM_Init(900,0);//����Ƶ��PWMƵ��=72000/900=80Khz
//	TIM2_Encoder_Init_1(0xffff, 0);
//	TIM4_Encoder_Init_2(0xffff, 0);
//	delay_ms(200);
//	MPU6050_Init();	
//    while(1)
//	{
//		TIM2_Encoder_Write_1(0);   //����������
//		TIM4_Encoder_Write_2(0);   //����������
//	    delay_ms(5);
//		Angle_Calcu();			  //�Ƕ�����ٶ�����
//		PID(-1.3);				  //�����Ƕ� -1.3
//	}
//}
																					  




/**********************ʵ���壺��������ǶȽ��ٶȼ���**************************/
/*ʵ������:��ǣ�ָ����С�����������봹��֮��ĽǶȣ�
		   ���ٶȣ�ָ����С���㵹�Ľ��ٶȡ�
           С����ֱ��ֹ������ʱ����б��Angle����ٶ�Angle_dotΪ���㡱������ġ��㡱
           ָ������һ����Χ�ڡ�
	Angle�����˴�ֱ�Ƕȣ������㵹ʱ������ͼ����Angle�ĽǶ�С��0�����������봹ֱ����֮��ĽǶ�Խ��
		   AngleֵԽС�������㵹ʱ������ͼ����Angle�ĽǶȴ���0�����������봹ֱ����֮��ĽǶ�Խ��
		   AngleֵԽ��
Angle_dot��С��˳ʱ������תʱ������ͼ����Angle_dotС��0�����������ٶ�Խ��ֵԽС
		   С����ʱ������תʱ������ͼ����Angle_dot����0�����������ٶ�Խ��ֵԽ��
*/
//#define PI 3.14159
////�ǶȲ���
//float Angle, Angle_dot;   //С��������б�Ƕȡ����ٶ�
//float Angle_aYZ;          //��Y��Z���ϵļ��ٶȴ�������õ���ֵ���������б�Ƕ�
//float Angle_gX;           //��X��������Ǵ�������õ���ֵ����������ٶ�
////����������		
//float  Q_angle=0.01;            
//float  Q_gyro=0.01;              
//float  R_angle=0.003;	
//float  dt=0.005;	       //dtΪkalman�˲�������ʱ��;
//char   C_0 = 1;
//float  Q_bias, Angle_err;
//float  PCt_0, PCt_1, E;
//float  K_0, K_1, t_0, t_1;
//float  Pdot[4] ={0,0,0,0};
//float  PP[2][2] = { { 1, 0 },{ 0, 1 } };
//// �������˲�
//void Kalman_Filter(float Accel,float Gyro)		
//{
//	Angle+=(Gyro - Q_bias) * dt; //�������
//
//	Pdot[0]=Q_angle - PP[0][1] - PP[1][0]; // Pk-����������Э�����΢��
//
//	Pdot[1]=- PP[1][1];
//	Pdot[2]=- PP[1][1];
//	Pdot[3]=Q_gyro;
//	
//	PP[0][0] += Pdot[0] * dt;   // Pk-����������Э����΢�ֵĻ���
//	PP[0][1] += Pdot[1] * dt;   // =����������Э����
//	PP[1][0] += Pdot[2] * dt;
//	PP[1][1] += Pdot[3] * dt;
//		
//	Angle_err = Accel - Angle;	//zk-�������
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
//	PP[0][0] -= K_0 * t_0;		 //����������Э����
//	PP[0][1] -= K_0 * t_1;
//	PP[1][0] -= K_1 * t_0;
//	PP[1][1] -= K_1 * t_1;
//		
//	Angle	+= K_0 * Angle_err;	 //�������
//	Q_bias	+= K_1 * Angle_err;	 //�������
//	Angle_dot = Gyro - Q_bias; //���ֵ(�������)��΢��=���ٶ�
//}
////��Ǽ��㣨�������ںϣ�
//void Angle_Calcu(void)	 
//{
//	//------���ݼ��ٶȷ�����ý��ٶ�--------------------------
//    //���Բ⣬���ٶȴ�������Χ����  0  ��2g	 16384 LSB/g
//	Angle_aYZ = atan2((Out_Data(ACCEL_YOUT_H) - 300), (Out_Data(ACCEL_ZOUT_H)-(16384-16450))) *180/PI ;   //ȥ�����ƫ��,����õ��Ƕȣ����ȣ�
//	//����ת��Ϊ��,
//
//    //-------���ٶ�-------------------------
//	//���Բ⣬�����ǲ�����Χ����	 0  ��250��/s  131LSB/(��/s)	0.00763358 (��/s)/LSB
//    Angle_gX = (Out_Data(GYRO_XOUT_H)-0) *0.00763358 ;//0Ϊ���������ھ�ֹ�ǲ�õĽ��ٶ�Ϊ0LSB��
//		
//	//-------�������˲��ں�-----------------------
//	Kalman_Filter(Angle_aYZ - 0, Angle_gX - 0);       //�������˲��������,��ȥ���ƫ�ƣ�
//}
//int main(void)
//{
//	Stm32_Clock_Init(9); //ϵͳʱ������
//	delay_init(72);	     //��ʱ��ʼ��
//	uart_init(72,9600);  //����1��ʼ��
//    delay_ms(200);
//	MPU6050_Init();	
//    while(1)
//	{
//	    delay_ms(5);
//		Angle_Calcu();
//		printf("�Ƕȣ�%f ���ٶȣ�%f\n",Angle,Angle_dot); //���С����б�Ƕ�����ת�ٶ�
//	}
//}


/*********************ʵ���ģ�MPU6050***************************/
/*ʵ�����󣻽�������ˮƽ����ʱ��ACC: X=0  Y=0  Z=16384  GYRO:X=0  Y=0  Z=0  TEMP_OUT: 30.59 
		   ��Ȼ��ֻ��һ������״���¾���ˮƽ������������״���²Ż��еĽ������ʵ�ʵĲ���ʱ��
		   ������ڲ�ͣ�ı仯�ģ���Ȼ�ڴ�����������״̬�£�����ı仯������һ���ķ�Χ֮�ڡ�
		   ���Ÿı䴫������״̬�����������ֵ�仯�ص㡣��ο�ͼ����������ķ�������ת�ļ��ԡ�
		   TEMP_OUT:��ֵû��̫��ı仯���������ַ���MPU6050����ʱ�����ֵ�����ı��
*/
//int main(void)
//{
//	Stm32_Clock_Init(9); //ϵͳʱ������
//	delay_init(72);	     //��ʱ��ʼ��
//	uart_init(72,9600);  //����1��ʼ��
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


/****************ʵ���������������ٶȼ��***********************/
/*ʵ�����󣺴�ʵ����ʵ������ƣ�ֻ����ԭ�л���������˱��������ܣ�
            �ڵ��ת����ͬʱ��ͨ�����ڽ���õ��ٶ�������ڵ����ǰ
			ת��ʱ���������ֵΪ����������ת��ʱ���������Ϊ����
speed�ķ�Χ��-900~+900��
*/
//int main(void)
//{
//	s16 speed = 900;
//	Stm32_Clock_Init(9); //ϵͳʱ������
//	delay_init(72);	     //��ʱ��ʼ��
//	uart_init(72,9600);  //����1��ʼ��
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
//		printf("������ֵ1��%4d ;������ֵ2��%4d \n",
//		     TIM2_Encoder_Read_1(),TIM4_Encoder_Read_2());
//	}
//}


/****************ʵ����������������********************/
/*ʵ�����󣺵��������ٶ���ת���Ҳ࿴�����˳ʱ��ת������
      		�ٶȽ����ؼ�С��ֱ�����ֹͣ�������ص�����
			ת�����Ҳ࿴�������ʱ��ת�����ٶȲ��ϼӿ죬
 			ֱ��ת��������ͻȻɲ��������ֹ0.5s�����
			һ�����ڡ�������ѭ����
speed�ķ�Χ��-900~+900��
*/
//int main(void)
//{
//    s16 speed = 900;
//    Stm32_Clock_Init(9); //ϵͳʱ������
//    delay_init(72);	     //��ʱ��ʼ��
//    uart_init(72,9600);  //����1��ʼ��
//    LED_Init();
//    M_Init();
//	  TIM3_PWM_Init(900,0); //�趨�Զ�װ��ֵΪ900������Ƶ��PWMƵ��=72000/900=80Khz
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


/************ʵ��һ��������STATE��***************/
/*ʵ�����󣺵ơ�STATE��ÿ��500ms�ı�һ�ε�����ʽ*/
//int main(void)
//{
//    Stm32_Clock_Init(9); //ϵͳʱ������
//    delay_init(72);	     //��ʱ��ʼ��
//    LED_Init();
//    while(1)
//    {
//        LED =!LED;
//        delay_ms(500);
//    }
//}
