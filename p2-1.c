#include <stdio.h> 

#define MAX_SIZE 100 

float sum(float [], int);
float input[MAX_SIZE], answer; // MAX_SIZE��ŭ �迭 ����
int i; 

void main(){
    for(i = 0; i < MAX_SIZE; i++) // ������ �迭�� 0���� ���� �������Ѱ��� ����
        input[i] = i; 

    printf("[----- [Jegal Dohyun] [2018038018] -----] \n\n");
    
    printf("address of input = %p\n", input); // �迭�� �̸��� 0��° �ּҸ� ����Ű�Ƿ� input[0]�� �ּ� ���
    
    answer = sum(input, MAX_SIZE);
    printf("The sum is : %f\n", answer);
} 

float sum(float list[], int n){
    printf("value of list = %p\n", list); // list[]�� ����Ű�� �ִ� input�� �ּ� ��� 
    printf("address of list = %p\n\n", &list); // list[]�� �ּ� ���

    int i;
    float tempsum = 0;

    for(i = 0; i < n; i++) // input[]�� ��� ���� ���� tempsum�� ����
        tempsum += list[i]; 

    return tempsum;
}