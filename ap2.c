#include <stdio.h>
#include <stdlib.h> 

void main(){
    int list[5];
    int *plist[5]; // 정수형 배열과 포인터형 배열 생성

    list[0] = 10;
    list[1] = 11;

    plist[0] = (int *)malloc(sizeof(int)); // heap에 공간 할당

    printf("[----- [Jegal Dohyun] [2018038018] -----] \n\n");
    
    printf("list[0] \t = %d\n", list[0]); // list[0]의 값 출력
    printf("address of list \t = %p\n", list); // 배열의 이름은 0번째 주소를 가리키므로 list[0]의 주소 출력
    printf("address of list[0] \t = %p\n", &list[0]); // list[0]의 주소 출력
    printf("address of list + 0 \t = %p\n", list + 0); 
    printf("address of list + 1 \t = %p\n", list + 1);
    printf("address of list + 2 \t = %p\n", list + 2);
    printf("address of list + 3 \t = %p\n", list + 3);
    printf("address of list + 4 \t = %p\n", list + 4); // list가 int형이므로 list[0]의 주소에 (4바이트*수)를 더한 주소인 list[n]의 값 출력
    printf("address of list[4] \t = %p\n", &list[4]); // list[4]의 주소 출력

    free(plist[0]); // heap에 할당된 공간 해제
}