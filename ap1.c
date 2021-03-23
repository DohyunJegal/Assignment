#include <stdio.h>
#include <stdlib.h> 

void main(){
    int list[5];
    int *plist[5] = {NULL,}; // 정수형 배열과 포인터형 배열 생성

    plist[0] = (int *)malloc(sizeof(int)); // heap에 공간 할당

    list[0] = 1;
    list[1] = 100; 

    *plist[0] = 200; // plist[0]이 가리키는 곳에 200 저장

    printf("[----- [Jegal Dohyun] [2018038018] -----] \n\n");

    printf("value of list[0] = %d\n", list[0]); // list[0]의 값 출력
    printf("address of list[0] = %p\n", &list[0]); // list[0]의 주소 출력
    printf("value of list  = %p\n", list); // 배열의 이름은 0번째 주소를 가리키므로 list[0]의 주소 출력
    printf("address of list (&list) = %p\n", &list); // list[0]의 주소 출력

    printf("---------------------\n\n");
    printf("value of list[1] = %d\n", list[1]); // list[1]의 값 출력
    printf("address of list[1] = %p\n", &list[1]); // list[1]의 주소 출력
    printf("value of *(list + 1) = %p\n", *(list + 1)); // list가 int형이므로 list[0]의 주소에 4바이트를 더한 주소인 list[1]의 값 출력
    printf("address of list + 1 = %p\n", list + 1);  // list[1]의 주소 출력

    printf("---------------------\n\n");
    printf("value of *plist[0] = %d\n", *plist[0]); // plist[0]이 가리키는 200 출력
    printf("&plist[0] = %p\n", &plist[0]); // plist[0]의주소 출력
    printf("&plist = %p\n", &plist); // 배열의 이름은 0번째 주소를 가리키므로 list[0]의 주소 출력
    printf("plist = %p\n", plist); // plist[0]의 주소 출력
    printf("plist[0] = %p\n", plist[0]); // plist[0]에 저장된 주소 출력
    printf("plist[1] = %p\n", plist[1]);
    printf("plist[2] = %p\n", plist[2]);
    printf("plist[3] = %p\n", plist[3]);
    printf("plist[4] = %p\n", plist[4]); // NULL로 초기화된 값 출력

    free(plist[0]); // heap에 할당된 공간 해제
}