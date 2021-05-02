#include <stdio.h>	
#include <stdlib.h>
#include <time.h>
 
void main() {
	int score[10][3] = { 0 };	
	int student = 0;	
	int a, b, min, max;	
 
	srand((unsigned)time(NULL)); 
 
	printf("학생의 수를 입력하세요 (최대 10명) : ");	
	scanf("%d", &student);
 
	for (a = 0; a < student; a++) {	
		for (b = 0; b < 3; b++) {
			score[a][b] = rand() % 100 + 1;
		}
	}
 
	printf("학번 시험#1 시험#2 시험#3 \n");	
    
	for (a = 0; a < student; a++) {
		printf("%d\t", a + 1);
 
		for (b = 0; b < 3; b++) {
			printf("%d\t", score[a][b]);
		}
		printf("\n");
	}
 
	for (a = 0; a<3 ; a++) {
		max = 0;
 
		for (b = 0; b < student; b++) {
			if (max < score[b][a])
				max = score[b][a];
		}
		printf("시험 #%d의 최대점수 : %d\n", a + 1, max);	
	}
 
	for (a = 0; a<3; a++) {
		min = 100;	
 
		for (b = 0; b < student; b++) {
			if (min > score[b][a])
				min = score[b][a];
		}
		printf("시험 #%d의 최소점수 : %d\n", a + 1, min);
	}
}
