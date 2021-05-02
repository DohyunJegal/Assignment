#include <stdio.h>
 
int main(void) {
    double base, height, area;
    
    printf("삼각형의 밑변 : ");
    scanf_s("%lf", &base);
 
    printf("삼각형의 높이 : ");
    scanf_s("%lf", &height);
 
    area = 0.5 * base * height;
 
    printf("삼각형의 넓이 : %lf\n", area);
 
    return 0;
}
