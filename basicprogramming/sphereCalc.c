include <stdio.h>
#define Pi 3.14
 
int main(void)	
{
	double A, V, r;
 
	printf("구의 반지름을 입력하세요 : ");
	scanf_s("%lf", &r);
 
	A = 4 * Pi*r*r;	
	V = (4 / 3)*Pi*r*r*r;
 
	printf("구의 표면적은 %lf, 체적은 %lf 입니다. \n", A, V);
 
	return 0;
}
