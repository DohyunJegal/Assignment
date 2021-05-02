#include <stdio.h>
 
int find_max(int data[]);
 
void main() {
	int data[10] = { 3,2,9,7,1,4,8,0,6,5 };
	int n, maxindex;
 
	maxindex = find_max(data);
 
	printf("배열의 값 \n");
 
	for (n = 0; n < 10; n++) {
		printf("data[%d]=%d ", n, data[n]);
		if ((n + 1) % 5 == 0)
			printf("\n");
	}
 
	printf("최대값 : data[%d] = %d", maxindex, data[maxindex]);
}
 
int find_max(int data[]) {
	int max, n;
 
	max = data[0];
 
	for (n = 0; n < 10; n++) {
		if (data[max] < data[n])
			max = n;
 
	}
 
	return max;
}
