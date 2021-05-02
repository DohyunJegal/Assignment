#include <stdio.h>	
 
int main(void)	
{
	double x, result;		
 
	printf("x의 값을 입력하시오 : ");	
	scanf_s("%lf", &x);		
 
	if (x <= 0)
		result = x * x*x - 9 * x + 2;
	else		
		result = 7 * x + 2;
 
	printf("f(x)의 값은 %lf 입니다. \n", result);	
 
	return 0;
}

// f(x) = x^3-9x+2 (x<=0), 7x+2 (x>0)
