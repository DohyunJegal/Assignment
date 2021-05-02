#include <stdio.h>
#include <math.h>
 
void main() {
	int n = 1;
	double nexp, fact, newexp, oldexp;
 
	nexp = exp(1.0);
	
	printf(" n  자연대수\t\t수열 계산\t\t오차 \n\n");
 
	n = 1;
	fact = 1;
	newexp = 0.0; 
	oldexp = -1.0;
 
	while (oldexp != newexp) {
		oldexp = newexp;
		newexp = newexp + 1.0 / fact;
		printf("%2d: %20.18lf %20.18lf %20.18lf \n", n, nexp, newexp, fabs(nexp - newexp));
		fact = fact * n;
		n = n + 1;
	}
}
