#include <stdio.h>	
 
int main(void)	{
	int a, b, number;
	
	printf("정수를 입력하세요 : ");   
	scanf_s("%d", &number);	
 
	for (a = 1; a <= number; a++) {
		for (b = 1; b <= a; b++) {
			printf("%d \t", b);	
		}
		printf("\n");
	}
 
	return 0;
}
