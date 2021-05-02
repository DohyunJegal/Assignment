#include <stdio.h>
 
int main(void) {
	char i;
 
	printf("문자를 입력하세요 : ");
	scanf_s("%c", &i);
 
	if (i == 'R')
		printf("Rectangle\n");
	else if (i=='T')
		printf("Triangle\n");
	else if (i=='C')
		printf("Circle\n");
	else
		printf("Unknown\n");
 
	return 0;
}
