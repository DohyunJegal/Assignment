#include <stdio.h> 
#include <stdlib.h>

void main(){
    int **x; // ���� ������

    printf("[----- [Jegal Dohyun] [2018038018] -----] \n\n");

    printf("sizeof(x) = %lu\n", sizeof(x)); // �ּҸ� ����, 4����Ʈ�� ��µȴ�. (32��Ʈ)
    printf("sizeof(*x) = %lu\n", sizeof(*x)); // �ּҸ� ����, 4����Ʈ�� ��µȴ�. (32��Ʈ)
    printf("sizeof(**x) = %lu\n", sizeof(**x)); // int���� ����, 4����Ʈ�� ��µȴ�.
}