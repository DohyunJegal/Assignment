#include <stdio.h>

void main(){
    int i;
    int *ptr;   // 포인터 ptr 선언 
    int **dptr; // 더블포인터 dptr 선언

    printf("[----- [Jegal Dohyun] [2018038018] -----] \n\n");

    i = 1234;

    printf("[checking values before ptr = &i] \n");
    printf("value of i == %d \n", i);   // i의 값 출력
    printf("address of i == %p \n", &i);    // i의 주소 출력
    printf("value of ptr == %p \n", ptr);   // ptr의 값 출력
    printf("address of ptr == %p \n\n", &ptr);    // ptr의 주소 출력

    ptr = &i; // i의 주소를 ptr에 저장
    
    printf("[checking values after ptr = &i] \n");
    printf("value of i == %d \n", i);   
    printf("address of i == %p \n", &i);
    printf("value of ptr == %p \n", ptr); // ptr의 값인 i의 주소 출력
    printf("address of ptr == %p \n", &ptr); // ptr의 주소 출력
    printf("value of *ptr == %d \n\n", *ptr); // ptr이 가리키는 i의 값 출력

    dptr = &ptr; // dptr에 ptr의 주소 저장

    printf("[checking values after dptr = &ptr] \n");
    printf("value of i == %d \n", i);
    printf("address of i == %p \n", &i);
    printf("value of ptr == %p \n", ptr);
    printf("address of ptr == %p \n", &ptr);
    printf("value of *ptr == %d \n", *ptr);
    printf("value of dptr == %p \n", dptr); // dptr의 값인 ptr의 주소 출력
    printf("address of dptr == %p \n", &dptr); // dptr의 주소 출력
    printf("value of *dptr == %p \n", *dptr); // dptr이 가리키는 ptr의 i의 주소 출력
    printf("value of **dptr == %d \n", **dptr); // dptr이 가리키는 ptr이 가리키는 i의 값 출력

    *ptr = 7777; // ptr이 가리키는 i에 7777 저장

    printf("\n[after *ptr = 7777] \n");
    printf("value of i == %d \n", i);
    printf("value of *ptr == %d \n", *ptr);
    printf("value of **dptr == %d \n", **dptr); // i의 값 출력

    **dptr = 8888; // dptr이 가리키는 ptr이 가리키는 i에 8888 저장
    
    printf("\n[after **dptr = 8888] \n");
    printf("value of i == %d \n", i);
    printf("value of *ptr == %d \n", *ptr);
    printf("value of **dptr == %d \n", **dptr); // i의 값 출력
}
