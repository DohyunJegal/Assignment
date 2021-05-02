#include <stdio.h>
#include <stdlib.h>
#include <time.h>
 
void main() {
	int num[10] = { 0 };
	int i=0,a=0;
 
	srand((unsigned)time(NULL));
		
	for (i = 0; i < 100; i++) { 
		++num[rand() % 10];
	}
 
	for (i = 0; i<10 ; i++) {
		if (num[i] > num[a])
			a = i;
	}
 
	for (i = 0; i<10; i++) {
		printf("%d %d번 \n", i, num[i]);
	}
 
	printf("\n가장 많이 생성된 수 : %d \n", a);
}
