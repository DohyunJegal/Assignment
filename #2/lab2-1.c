#include <stdio.h>

void main(){
    char charType;
    int integerType;
    float floatType;
    double doubleType;                                              // char, int, float, double형 변수 생성

    printf("[----- [Jegal Dohyun] [2018038018] -----] \n\n");

    printf("Size of char : %ld byte \n",sizeof(charType));
    printf("Size of int : %ld bytes \n",sizeof(integerType));
    printf("Size of float : %ld bytes \n",sizeof(floatType));
    printf("Size of double : %ld bytes \n",sizeof(doubleType));     // 생성한 변수들의 크기를 출력

    printf("-----------------------------------------\n");

    printf("Size of char : %ld byte \n",sizeof(char));
    printf("Size of int : %ld bytes \n",sizeof(int));
    printf("Size of float : %ld bytes \n",sizeof(float));
    printf("Size of double : %ld bytes \n",sizeof(double));         // char, int, float, double형의 크기를 출력

    printf("-----------------------------------------\n");

    printf("Size of char* : %ld byte \n",sizeof(char*));
    printf("Size of int* : %ld bytes \n",sizeof(int*));
    printf("Size of float* : %ld bytes \n",sizeof(float*));
    printf("Size of double* : %ld bytes \n",sizeof(double*));       // 32비트에서의 주소 저장 공간 크기 출력
}
