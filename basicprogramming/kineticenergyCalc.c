#include <stdio.h>		
 
int main(void) {
	double mass, speed, kenergy;		
   
	printf("질량 : ");	
	scanf_s("%lf", &mass);
	printf("속도 : ");
	scanf_s("%lf", &speed);
 
	kenergy = 0.5*mass*speed*speed;	
 
	printf("운동에너지 : %lf\n", kenergy);
 
	return 0;
}
