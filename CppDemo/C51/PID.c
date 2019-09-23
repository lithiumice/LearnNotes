#include <stdio.h>

struct _PID{
    float set_speed;
    float real_speed;
    float error;
    float last_error;
    float Kp,Ki,Kd;
    float integral;
}PID;

void PID_init(float set,float real){
    PID.set_speed=set;
    PID.real_speed=real;
    PID.error=0;
    PID.last_error=0;
    PID.integral=0;
    PID.Kp=0.1;
    PID.Ki=0.15;
    PID.Kd=0.1;
}


float PID_realize(float speed)
{
    PID.set_speed=speed;
    PID.error=PID.set_speed-PID.real_speed;
    PID.integral+=PID.error;
    PID.real_speed=PID.Kp*PID.error+PID.Ki*PID.integral+PID.Kd*(PID.error-PID.last_error);
    PID.last_error=PID.error;
    return PID.real_speed;
}

int main(){
	
int count=0;
float set=250.0;
float real=0;
PID_init(set,real);
while(count<200){

        real=PID_realize(set);
        printf("%f\n",real);
        count++;
    }
}
