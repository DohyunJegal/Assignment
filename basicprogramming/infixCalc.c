	#include <stdio.h>
 
void num_add(int a, int b);
void num_sub(int a, int b);
void num_mul(int a, int b);
void num_div(int a, int b);
 
int a, b;
char op; 
 
void main() {
	for (;;) {
		printf("연산을 입력하세요 : "); 
		scanf("%d %c %d", &a, &op, &b); 
 
		if (op == '+') {
			num_add(a, b);
		}
		else if (op == '-') {
			num_sub(a, b);
		}
		else if (op == '*') {
			num_mul(a, b);
		}
		else if (op == '/')  {
			num_div(a, b);
		}
	}
}
 
void num_add(int a, int b) {
	static int add = 0; 
	add++;
	printf("덧셈은 총 %d번 실행되었습니다. \n", add);
	printf("연산 결과 : %d \n\n", a + b);
}
 
void num_sub(int a, int b) {
	static int sub = 0; 
	sub++; 	
	printf("뺄셈은 총 %d번 실행되었습니다. \n", sub); 
	printf("연산 결과 : %d \n\n", a - b);
}
 
void num_mul(int a, int b) {
	static int mul = 0; 	
	mul++;
	printf("곱셈은 총 %d번 실행되었습니다. \n", mul); 
	printf("연산 결과 : %d \n\n", a * b);
}
 
void num_div(int a, int b) {
	static int div = 0; 
	div++;
	printf("나눗셈은 총 %d번 실행되었습니다. \n", div); 
	printf("연산 결과 : %d \n\n", a / b); 
}
