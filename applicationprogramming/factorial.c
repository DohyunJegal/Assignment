#include <stdio.h>
 
int factorial(int n);
double dfactorial(int n);
 
void main() {
	int n, ifact = 1;
	double dfact = 1;
 
	printf(" n\t\t정수 팩토리얼\t\t실수 팩토리얼\n\n");
	for (n = 1; n <= 20; n++) {
		ifact = factorial(n);
		dfact = dfactorial(n);
 
		printf("%d:\t%20d\t%20.0lf\n", n, ifact, dfact);
	}
}
 
int factorial(int n) {
	if (n <= 1)
		return 1;
	else
		return n * factorial(n - 1);
}
 
double dfactorial(int n) {
	if (n <= 1)
		return 1;
	else
		return n * dfactorial(n - 1);
}
