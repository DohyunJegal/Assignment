#include <stdio.h>
 
void get_sum_diff(int x, int y, int *p_sum, int *p_diff);	
 
void main() {
	int a, b;
 
	printf("두 정수를 입력하세요 : ");
	scanf("%d %d", &a, &b);	
 
	get_sum_diff(a, b, &a, &b);
 
	printf("두 정수의 합 : %d \n", a); 
	printf("두 정수의 차 : %d \n", b);
}
 
void get_sum_diff(int x, int y, int *p_sum, int *p_diff) {	
	*p_sum = x + y;	
 
	if (x <= y)	
		*p_diff = y - x;
	else 
		*p_diff = x - y;
}
