#include <stdio.h> 

void print1 (int *ptr, int rows); 

void main(){
    int one[] = {0, 1, 2, 3, 4};

    printf("[----- [Jegal Dohyun] [2018038018] -----] \n\n");

    printf("one = %p\n", one); // 배열의 이름은 0번째 주소를 가리키므로 one[0]의 주소 출력
    printf("&one = %p\n", &one); // one[0]의 주소 출력
    printf("&one[0] = %p\n", &one[0]); // one[0]의 주소 출력
    printf("\n"); 

    print1(&one[0], 5);
} 

void print1 (int *ptr, int rows){
    int i; 

    printf("Address \t Contents \n");
    for(i = 0; i < rows; i++)
        printf("%p \t %5d \n", ptr + i, *(ptr + i)); // one[]이 int형이므로 one[]의 주소에 4바이트씩 더해가면서 내부의 값을 출력
    printf("\n");
}