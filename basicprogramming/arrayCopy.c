	#include <stdio.h>
#define SIZE 5
 
void array_copy(int *A, int *B, int size);
 
void main() {
	int A[SIZE] = { 24,16,85,24,2 };
	int B[SIZE] = { 0 };
	int i;
 
	array_copy(A, B, SIZE);
	
	printf("A[ ] : ");
	for (i = 0; i < SIZE; i++) {
		printf("%d ", A[i]);
	}
	printf("\nB[ ] : ");
	for (i = 0; i < SIZE; i++) {
		printf("%d ", B[i]);
	}
	printf("\n");
}
 
void array_copy(int *A, int *B, int size) {	
	int i;
	for (i = 0; i < size; i++) {
		B[i] = A[i];
	}
}
