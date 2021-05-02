#include <stdio.h>
#include <math.h>
 
void main() {
	int n, sign;
	double PI, pi1, pi2, pi2sqr;
 
	PI = 4.0*atan(1.0);
	
	printf("원주율 = %10.8lf\n\n", PI);
	printf("항의 수\t공식 1\t\t오차\t\t공식 2\t\t오차\n\n");
 
	pi1 = 0.0;
	pi2sqr = 0.0; 
	sign = -1;
 
	for (n = 1; n <= 10000; n++) {
		sign *= -1;
		pi1 += (double)sign*4.0 / (2.0*(double)n - 1.0);
		pi2sqr += 6.0 / ((double)n*(double)n);
		pi2 = sqrt(pi2sqr);
 
		if ((n % 1000) == 0) 
		printf("%6d\t%10.8lf\t%10.8lf\t%10.8lf\t%10.8lf\n", n, pi1, fabs(PI - pi1), pi2, fabs(PI - pi2));
	}
}
