#include <stdio.h>
 
int main(void)
{
	int x, y;	
 
	printf("x와 y의 값을 입력하세요 : ");
	scanf_s("%d %d", &x, &y);
 
	(x > 0 && y > 0) ? printf("1사분면입니다.\n") : ((x < 0 && y>0) ? printf("2사분면입니다.\n") : ((x < 0 && y < 0) ? printf("3사분면입니다.\n") : ((x > 0 && y < 0) ? printf("4사분면입니다.\n") : printf("오류입니다.\n")))); 
 
	return 0;
}
