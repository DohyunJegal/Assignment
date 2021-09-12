#include <stdio.h> 

struct student{
    char lastName[13]; // 13바이트
    int studentId; // 4바이트
    short grade; // 2바이트
};

void main(){
    struct student pst;

    printf("[----- [Jegal Dohyun] [2018038018] -----] \n\n");

    printf("size of student = %ld\n", sizeof(struct student)); // 구조체의 크기를 출력. 구조체에서 생성한 변수들의 크기를 더하면 19바이트여야 하나 채워넣기로 인해 24바이트가 출력된다.
    printf("size of int = %ld\n", sizeof(int)); 
    printf("size of short = %ld\n", sizeof(short));
}
