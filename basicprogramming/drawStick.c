#include <stdio.h>	 
 
int main(void) {
	int a, number;
 
	for (;;) {
		printf("막대의 높이 (종료 : -1) : ");	
		scanf_s("%d", &number);	
 
		if (number >= 1 && number <= 50) {
			for (a = 0; a < number; a++)
				printf("*\n");
		}
		else if (number == -1)	
			break;
	}
 
	return 0;
}
