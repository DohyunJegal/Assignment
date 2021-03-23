#include <stdio.h>
#include <stdlib.h> 

void main(){
    int list[5];
    int *plist[5] = {NULL,}; // ������ �迭�� �������� �迭 ����

    plist[0] = (int *)malloc(sizeof(int)); // heap�� ���� �Ҵ�

    list[0] = 1;
    list[1] = 100; 

    *plist[0] = 200; // plist[0]�� ����Ű�� ���� 200 ����

    printf("[----- [Jegal Dohyun] [2018038018] -----] \n\n");

    printf("value of list[0] = %d\n", list[0]); // list[0]�� �� ���
    printf("address of list[0] = %p\n", &list[0]); // list[0]�� �ּ� ���
    printf("value of list  = %p\n", list); // �迭�� �̸��� 0��° �ּҸ� ����Ű�Ƿ� list[0]�� �ּ� ���
    printf("address of list (&list) = %p\n", &list); // list[0]�� �ּ� ���

    printf("---------------------\n\n");
    printf("value of list[1] = %d\n", list[1]); // list[1]�� �� ���
    printf("address of list[1] = %p\n", &list[1]); // list[1]�� �ּ� ���
    printf("value of *(list + 1) = %p\n", *(list + 1)); // list�� int���̹Ƿ� list[0]�� �ּҿ� 4����Ʈ�� ���� �ּ��� list[1]�� �� ���
    printf("address of list + 1 = %p\n", list + 1);  // list[1]�� �ּ� ���

    printf("---------------------\n\n");
    printf("value of *plist[0] = %d\n", *plist[0]); // plist[0]�� ����Ű�� 200 ���
    printf("&plist[0] = %p\n", &plist[0]); // plist[0]���ּ� ���
    printf("&plist = %p\n", &plist); // �迭�� �̸��� 0��° �ּҸ� ����Ű�Ƿ� list[0]�� �ּ� ���
    printf("plist = %p\n", plist); // plist[0]�� �ּ� ���
    printf("plist[0] = %p\n", plist[0]); // plist[0]�� ����� �ּ� ���
    printf("plist[1] = %p\n", plist[1]);
    printf("plist[2] = %p\n", plist[2]);
    printf("plist[3] = %p\n", plist[3]);
    printf("plist[4] = %p\n", plist[4]); // NULL�� �ʱ�ȭ�� �� ���

    free(plist[0]); // heap�� �Ҵ�� ���� ����
}