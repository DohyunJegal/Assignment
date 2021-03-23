#include <stdio.h> 

void print1 (int *ptr, int rows); 

void main(){
    int one[] = {0, 1, 2, 3, 4};

    printf("[----- [Jegal Dohyun] [2018038018] -----] \n\n");

    printf("one = %p\n", one); // �迭�� �̸��� 0��° �ּҸ� ����Ű�Ƿ� one[0]�� �ּ� ���
    printf("&one = %p\n", &one); // one[0]�� �ּ� ���
    printf("&one[0] = %p\n", &one[0]); // one[0]�� �ּ� ���
    printf("\n"); 

    print1(&one[0], 5);
} 

void print1 (int *ptr, int rows){
    int i; 

    printf("Address \t Contents \n");
    for(i = 0; i < rows; i++)
        printf("%p \t %5d \n", ptr + i, *(ptr + i)); // one[]�� int���̹Ƿ� one[]�� �ּҿ� 4����Ʈ�� ���ذ��鼭 ������ ���� ���
    printf("\n");
}