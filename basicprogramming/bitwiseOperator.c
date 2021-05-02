#include <stdio.h>		
 
int main(void) {
	int x, y;
 
	printf("정수를 입력하세요 : ");
	scanf_s("%d", &x);
	
	printf("2를 곱하고 싶은 횟수 : ");	
	scanf_s("%d", &y);	
 
	printf("%d<<%d의 값 : %d \n", x,y,x<<y);	
 
	return 0;
}
