#include <stdio.h>
#include <stdlib.h>

#define MAX_QUEUE_SIZE 4 // 큐의 최대 크기를 정의 

typedef char element; // element라는 char형의 별칭 설정 
typedef struct {
	element queue[MAX_QUEUE_SIZE];
	int front, rear;
}QueueType; // 큐와 front, rear 값을 가지는 구조체 생성 


QueueType *createQueue();
int freeQueue(QueueType *cQ);
int isEmpty(QueueType *cQ);
int isFull(QueueType *cQ);
void enQueue(QueueType *cQ, element item);
void deQueue(QueueType *cQ, element* item);
void printQ(QueueType *cQ);
void debugQ(QueueType *cQ);
element getElement();

int main(void){
	QueueType *cQ = createQueue(); // createQueue()함수를 사용해 주소를 담는 자료형 cQ생성 
	element data; // 큐의 데이터를 받을 char형 변수 
	char command; // 메뉴 입력값을 저장할 char형 변수 

	printf("[----- [Jegal Dohyun] [2018038018] -----]\n\n");
	
	do{
		printf("\n-----------------------------------------------------\n");
		printf("                     Circular Q                   \n");
		printf("------------------------------------------------------\n");
		printf(" Insert=i,  Delete=d,   PrintQ=p,   Debug=b,   Quit=q \n");
		printf("------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'i': case 'I':
			data = getElement(); // getElement()로 받은 데이터 값을 data에 저장 
			enQueue(cQ, data); // data값과 사전 생성한 cQ의 주소를  enQueue()로 전달 
			break;
		case 'd': case 'D':
			deQueue(cQ, &data); // data값과 cQ의 주소를  deQueue()로 전달 
			break;
		case 'p': case 'P':
			printQ(cQ); // cQ의 주소를  printQ()로 전달 
			break;
		case 'b': case 'B':
			debugQ(cQ); // cQ의 주소를  debugQ()로 전달
			break;
		case 'q': case 'Q':
   	    	freeQueue(cQ); // cQ의 주소를  freeQueue()로 전달
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n"); // 이외의 값이 입력되면 오류메세지 출력 
			break;
		}

	}while(command != 'q' && command != 'Q'); // q 입력 전 까지 메뉴 반복 출력 


	return 1;
}

QueueType *createQueue(){
	QueueType *cQ; // 사전 정의한 QueueType 구조체의 주소를 담는 cQ 생성 
	cQ = (QueueType *)malloc(sizeof(QueueType)); // malloc()함수를 통해 메모리에 동적 구조체 할당 
	cQ->front = 0;
	cQ->rear = 0; // front와 rear의 값을 0으로 초기화 
	return cQ;
}

int freeQueue(QueueType *cQ){
    if(cQ == NULL) return 1; // cQ가 비어있는 경우 스킵 
    free(cQ); // free()함수를 통해 할당되어있는 cQ 할당 해제 
    return 1; 
}

element getElement(){
	element item; // 입력받을 char형 변수 선언 
	printf("Input element = ");
	scanf(" %c", &item);
	return item; // 큐에 들어갈 내용을 입력받고 리턴 
}

int isEmpty(QueueType *cQ){
	if (cQ->front == cQ->rear){ // cQ의 front와 rear이 같다면 비어있음 
    	printf("Queue is Empty");
    	return 1;
	}
    return 0;
}

int isFull(QueueType *cQ){
	if (((cQ->rear + 1) % MAX_QUEUE_SIZE) == cQ->front){ // cQ의 rear+1 값이 front와 값이 같다면 꽉참 
		printf("Queue is Full"); // 큐가 가득차 rear보다 한 칸 앞의 front와 만나게 된다. 
		return 1;	
	}	
	return 0;
}

void enQueue(QueueType *cQ, element item){
	if(isFull(cQ) == 0){ // 사전에 큐가 가득차있는지 확인 
	cQ->rear = (cQ->rear + 1) % MAX_QUEUE_SIZE; // rear값을 증가시킴 
	cQ->queue[cQ->rear] = item; // 비어있는 공간에 값 대입 
	}
}

void deQueue(QueueType *cQ, element *item){
	if(isEmpty(cQ) == 0){ // 사전에 큐가 비어있는지 확인 
		cQ->front = (cQ->front + 1) % MAX_QUEUE_SIZE; // front값을 증가시킴 
		cQ->queue[cQ->front] = '\0';  // 값이 차있는 공간에 널문자 대입 
	}
}


void printQ(QueueType *cQ){
	int i, first, last;

	first = (cQ->front + 1)%MAX_QUEUE_SIZE; // front + 1 값을 first라 지정 
	last = (cQ->rear + 1)%MAX_QUEUE_SIZE; // rear + 1 값을 last라 지정 

	printf("Circular Queue : [");

	i = first;
	while(i != last){ // front == rear까지 모든 값 출력시까지 반복 
		printf("%3c", cQ->queue[i]);
		i = (i+1)%MAX_QUEUE_SIZE; // front + 1 값 증가 
	}
	printf(" ]\n");
}


void debugQ(QueueType *cQ){
	int i;
	
	printf("\n---DEBUG\n");
	for(i = 0; i < MAX_QUEUE_SIZE; i++){
		if(i == cQ->front) { // front값이 위치한 큐로 이동해 'front' 메세지 출력 
			printf("  [%d] = front\n", i);
			continue;
		}
		printf("  [%d] = %c\n", i, cQ->queue[i]); // 0부터  MAX_QUEUE_SIZE까지 큐에 저장된 값 출력 

	}
	printf("front = %d, rear = %d\n", cQ->front, cQ->rear); // front와 rear값 출력 
}


