#include <stdio.h>
 
int main(void) {
    double x, y, z, sum, avg;  
    
    printf("실수를 입력하시오 : "); 
    scanf_s("%lf", &x);  
 
    printf("실수를 입력하시오 : "); 
    scanf_s("%lf", &y);
 
    printf("실수를 입력하시오 : ");
    scanf_s("%lf", &z); 
 
    sum = x + y + z;
    avg = sum / 3.0;
 
    printf("합계는 %lf이고 평균값은 %lf입니다.\n", sum, avg);
    
    return 0; 
} 
