#include <stdio.h> 
#include <stdlib.h>

void main(){
    int **x; // 이중 포인터

    printf("[----- [Jegal Dohyun] [2018038018] -----] \n\n");

    printf("sizeof(x) = %lu\n", sizeof(x)); // 주소를 저장, 4바이트가 출력된다. (32비트)
    printf("sizeof(*x) = %lu\n", sizeof(*x)); // 주소를 저장, 4바이트가 출력된다. (32비트)
    printf("sizeof(**x) = %lu\n", sizeof(**x)); // int형을 저장, 4바이트가 출력된다.
}