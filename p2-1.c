#include <stdio.h> 

#define MAX_SIZE 100 

float sum(float [], int);
float input[MAX_SIZE], answer; // MAX_SIZE만큼 배열 생성
int i; 

void main(){
    for(i = 0; i < MAX_SIZE; i++) // 생성한 배열에 0부터 값을 증가시켜가며 대입
        input[i] = i; 

    printf("[----- [Jegal Dohyun] [2018038018] -----] \n\n");
    
    printf("address of input = %p\n", input); // 배열의 이름은 0번째 주소를 가리키므로 input[0]의 주소 출력
    
    answer = sum(input, MAX_SIZE);
    printf("The sum is : %f\n", answer);
} 

float sum(float list[], int n){
    printf("value of list = %p\n", list); // list[]가 가리키고 있는 input의 주소 출력 
    printf("address of list = %p\n\n", &list); // list[]의 주소 출력

    int i;
    float tempsum = 0;

    for(i = 0; i < n; i++) // input[]의 모든 값을 더해 tempsum에 저장
        tempsum += list[i]; 

    return tempsum;
}