#include <stdio.h>
#include <stdlib.h>

#define MAX_QUEUE_SIZE 4 // ť�� �ִ� ũ�⸦ ���� 

typedef char element; // element��� char���� ��Ī ���� 
typedef struct {
	element queue[MAX_QUEUE_SIZE];
	int front, rear;
}QueueType; // ť�� front, rear ���� ������ ����ü ���� 


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
	QueueType *cQ = createQueue(); // createQueue()�Լ��� ����� �ּҸ� ��� �ڷ��� cQ���� 
	element data; // ť�� �����͸� ���� char�� ���� 
	char command; // �޴� �Է°��� ������ char�� ���� 

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
			data = getElement(); // getElement()�� ���� ������ ���� data�� ���� 
			enQueue(cQ, data); // data���� ���� ������ cQ�� �ּҸ�  enQueue()�� ���� 
			break;
		case 'd': case 'D':
			deQueue(cQ, &data); // data���� cQ�� �ּҸ�  deQueue()�� ���� 
			break;
		case 'p': case 'P':
			printQ(cQ); // cQ�� �ּҸ�  printQ()�� ���� 
			break;
		case 'b': case 'B':
			debugQ(cQ); // cQ�� �ּҸ�  debugQ()�� ����
			break;
		case 'q': case 'Q':
   	    	freeQueue(cQ); // cQ�� �ּҸ�  freeQueue()�� ����
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n"); // �̿��� ���� �ԷµǸ� �����޼��� ��� 
			break;
		}

	}while(command != 'q' && command != 'Q'); // q �Է� �� ���� �޴� �ݺ� ��� 


	return 1;
}

QueueType *createQueue(){
	QueueType *cQ; // ���� ������ QueueType ����ü�� �ּҸ� ��� cQ ���� 
	cQ = (QueueType *)malloc(sizeof(QueueType)); // malloc()�Լ��� ���� �޸𸮿� ���� ����ü �Ҵ� 
	cQ->front = 0;
	cQ->rear = 0; // front�� rear�� ���� 0���� �ʱ�ȭ 
	return cQ;
}

int freeQueue(QueueType *cQ){
    if(cQ == NULL) return 1; // cQ�� ����ִ� ��� ��ŵ 
    free(cQ); // free()�Լ��� ���� �Ҵ�Ǿ��ִ� cQ �Ҵ� ���� 
    return 1; 
}

element getElement(){
	element item; // �Է¹��� char�� ���� ���� 
	printf("Input element = ");
	scanf(" %c", &item);
	return item; // ť�� �� ������ �Է¹ް� ���� 
}

int isEmpty(QueueType *cQ){
	if (cQ->front == cQ->rear){ // cQ�� front�� rear�� ���ٸ� ������� 
    	printf("Queue is Empty");
    	return 1;
	}
    return 0;
}

int isFull(QueueType *cQ){
	if (((cQ->rear + 1) % MAX_QUEUE_SIZE) == cQ->front){ // cQ�� rear+1 ���� front�� ���� ���ٸ� ���� 
		printf("Queue is Full"); // ť�� ������ rear���� �� ĭ ���� front�� ������ �ȴ�. 
		return 1;	
	}	
	return 0;
}

void enQueue(QueueType *cQ, element item){
	if(isFull(cQ) == 0){ // ������ ť�� �������ִ��� Ȯ�� 
	cQ->rear = (cQ->rear + 1) % MAX_QUEUE_SIZE; // rear���� ������Ŵ 
	cQ->queue[cQ->rear] = item; // ����ִ� ������ �� ���� 
	}
}

void deQueue(QueueType *cQ, element *item){
	if(isEmpty(cQ) == 0){ // ������ ť�� ����ִ��� Ȯ�� 
		cQ->front = (cQ->front + 1) % MAX_QUEUE_SIZE; // front���� ������Ŵ 
		cQ->queue[cQ->front] = '\0';  // ���� ���ִ� ������ �ι��� ���� 
	}
}


void printQ(QueueType *cQ){
	int i, first, last;

	first = (cQ->front + 1)%MAX_QUEUE_SIZE; // front + 1 ���� first�� ���� 
	last = (cQ->rear + 1)%MAX_QUEUE_SIZE; // rear + 1 ���� last�� ���� 

	printf("Circular Queue : [");

	i = first;
	while(i != last){ // front == rear���� ��� �� ��½ñ��� �ݺ� 
		printf("%3c", cQ->queue[i]);
		i = (i+1)%MAX_QUEUE_SIZE; // front + 1 �� ���� 
	}
	printf(" ]\n");
}


void debugQ(QueueType *cQ){
	int i;
	
	printf("\n---DEBUG\n");
	for(i = 0; i < MAX_QUEUE_SIZE; i++){
		if(i == cQ->front) { // front���� ��ġ�� ť�� �̵��� 'front' �޼��� ��� 
			printf("  [%d] = front\n", i);
			continue;
		}
		printf("  [%d] = %c\n", i, cQ->queue[i]); // 0����  MAX_QUEUE_SIZE���� ť�� ����� �� ��� 

	}
	printf("front = %d, rear = %d\n", cQ->front, cQ->rear); // front�� rear�� ��� 
}


