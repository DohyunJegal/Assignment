#include <stdio.h> 

struct student{
    char lastName[13]; // 13����Ʈ
    int studentId; // 4����Ʈ
    short grade; // 2����Ʈ
};

void main(){
    struct student pst;

    printf("[----- [Jegal Dohyun] [2018038018] -----] \n\n");

    printf("size of student = %ld\n", sizeof(struct student)); // ����ü�� ũ�⸦ ���. ����ü���� ������ �������� ũ�⸦ ���ϸ� 19����Ʈ���� �ϳ� ä���ֱ�� ���� 24����Ʈ�� ��µȴ�.
    printf("size of int = %ld\n", sizeof(int)); 
    printf("size of short = %ld\n", sizeof(short));
}