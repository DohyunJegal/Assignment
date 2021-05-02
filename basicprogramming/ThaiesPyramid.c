#include <stdio.h>
 
int main(void) {
	double AC, AE, BC, DE;	
 
	printf("AC와 AE, BC의 값을 입력하세요 : "); 
	scanf_s("%lf %lf %lf", &AC, &AE, &BC);	
 
	DE = (AE*BC) / AC;
 
	printf("DE의 값은 %lf입니다.\n", DE);	
 
	return 0;
}
