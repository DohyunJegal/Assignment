#include<stdio.h>
#include<stdlib.h>

typedef struct Node {
	int key;			// ��忡 ���� ���� 
	struct Node* link;	// ���� ��带 ����Ŵ 
} listNode;

typedef struct Head {
	struct Node* first;	// ���Ḯ��Ʈ�� ó���� ����Ű�� ��� 
} headNode;

headNode* initialize(headNode* h);
int freeList(headNode* h);

int insertFirst(headNode* h, int key);
int insertNode(headNode* h, int key);
int insertLast(headNode* h, int key);

int deleteFirst(headNode* h);
int deleteNode(headNode* h, int key);
int deleteLast(headNode* h);
int invertList(headNode* h);

void printList(headNode* h);

int main(){
	char command;				// �޴� �Է� �� ����  
	int key;					// ��忡 �Է��� ���� ���� 
	headNode* headnode = NULL;	// ����Ʈ�� �ʱ�ȭ 

	printf("[----- [Jegal Dohyun] [2018038018] -----]\n");

	do{
		printf("\n----------------------------------------------------------------\n");
		printf("                     Singly Linked List                         \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			headnode = initialize(headnode);	// ���Ḯ��Ʈ ��ü�� �Ҵ������ϰ� �ʱ�ȭ
			break;
		case 'p': case 'P':
			printList(headnode);	// ���Ḯ��Ʈ ��ü ��� 
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insertNode(headnode, key);	// ���� �Է¹ް� ��带 ����Ʈ�� �߰� 
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(headnode, key);	// �Է¹��� ���� ���� ��带 ���� 
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insertLast(headnode, key);	// ���� �Է¹ް� ��带 ����Ʈ�� �������� �߰� 
			break;
		case 'e': case 'E':
			deleteLast(headnode);	// ����Ʈ �������� ��带 ���� 
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			insertFirst(headnode, key);	// �Է¹��� ���� ����Ʈ�� ó���� �߰� 
			break;
		case 't': case 'T':
			deleteFirst(headnode);	// ����Ʈ ó���� ��带 ���� 
			break;
		case 'r': case 'R':
			invertList(headnode);	//  ����Ʈ�� �������� ���� 
			break;
		case 'q': case 'Q':
			freeList(headnode);	// ���Ḯ��Ʈ�� �Ҵ������ϰ� ���α׷� ���� 
			break;
		default:								
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;	// �̿��� �Է°��� �����޼��� ��� 
		}

	}while(command != 'q' && command != 'Q');	// ���ᰪ �Է� �� ���� �ݺ� 

	return 1;
}

headNode* initialize(headNode* h){
	if(h != NULL)
		freeList(h);	// h�� �پ����� �ʴٸ� �Ҵ� ���� 

	headNode* temp = (headNode*)malloc(sizeof(headNode));	 
	temp->first = NULL;	// �ӽ� ����� �Ҵ� �� NULL�� �ʱ�ȭ
	return temp;	// �ӽ� ����� ��ȯ 
}

int freeList(headNode* h){
	listNode* p = h->first;	// ����Ʈ��� p�� ���� �� h�� ù ����Ʈ��带 ����Ŵ 

	listNode* prev = NULL;	// ����Ʈ��� prev�� ���� �� NULL�� �ʱ�ȭ 
	while(p != NULL) {	// p ��尡 ���� �� ���� �ݺ�  
		prev = p;	// prev�� p�� ����Ŵ 
		p = p->link; // p ���� �ּҸ� p�� ����Ű�� �� 
		free(prev);	// prev �Ҵ� ���� 
	}
	free(h); // h �Ҵ����� 
	return 0;
}

int insertFirst(headNode* h, int key){	// ����Ʈ�� ù �κп� ��带 �߰� 
	listNode* node = (listNode*)malloc(sizeof(listNode));	// ����Ʈ��� node ���� 
	node->key = key;	// node�� Ű ���� �Է¹��� key ���� 

	node->link = h->first;	// ����尡 ����Ű�� ��带 node�� ����Ű�� ���� 
	h->first = node;	// ����尡 node�� ����Ű�� ���� 

	return 0;
}

int insertNode(headNode* h, int key){	// ����Ʈ ��ü �� �� ���� ��� �߰� 
	listNode* temp = (listNode*)malloc(sizeof(listNode));	// ����Ʈ��� temp ���� 
	temp->key = key;	// �Է¹��� ���� temp key�� ���� 
	
	if(h->first){	// �����尡 ����Ű�� ���� �ִ� ��� 
		listNode* current = (listNode*)malloc(sizeof(listNode));	// ����Ʈ��� current ���� 
		current = h->first;	// current�� ����尡 ����Ű�� ��带 ����Ű�� ���� 
		
		if(temp->key <= h->first->key){	// temp key�� ����Ʈ�� ù ����� ������ �۰ų� ���� ��� 
			temp->link =  h->first;	// ����尡 ����Ű�� ��带 temp�� ����Ű�� ���� 
			h->first = temp;	// ����尡 temp�� ����Ű�� ���� 
		}
		
		else{
			while(current->link != NULL){	// current�� ����Ű�� ��尡 ���� �� ���� �ݺ� 
				if(temp->key < current->link->key){	// �Է¹��� ���� ���� ����� ������ ���� ��� 
					temp->link = current->link;	// current�� ����Ű�� ��带 temp�� ����Ű�� ���� 
					current->link = temp;	// current�� temp�� ����Ű�� ���� 
					break;
				}
			current = current->link; // current�� ���� ���� �̵� 
			}
			
			if(current->link == NULL){	// curren�� ����Ű�� ��尡 ���� ��� 
				temp->link = NULL;	// temp�� ����Ű�°��� NULL�� ���� 
				current->link = temp;	// current�� ����Ű�� ���� temp�� ���� 		
			}
		}
	}
	
	else { // �����尡 ����Ű�� ���� ���� ��� 
		temp->link = NULL;	// temp�� ����Ű�� ���� NULL�� ���� 
		h->first = temp;	// �����尡 ����Ű�� ���� temp�� ���� 
	}
	
	return 0;
}

int insertLast(headNode* h, int key){	// ����Ʈ�� ������ �κп� ��带 �߰� 
	listNode* temp = (listNode*)malloc(sizeof(listNode));	// ����Ʈ��� temp ���� 
	temp->key = key;	// �Է¹��� ���� temp key�� ���� 
	
	if(h->first){	// �����尡 ����Ű�� ���� �ִ� ��� 
		listNode* current = (listNode*)malloc(sizeof(listNode));	// ����Ʈ��� current ���� 
		current = h->first;	// current�� ����尡 ����Ű�� ��带 ����Ű�� ���� 

		while(current->link != NULL){	
			current = current->link;	// current�� ����Ű�� ��尡 ���� �� ���� ���� ���� �̵� 
		}
		
		temp->link = NULL;	// temp�� ����Ű�� ���� NULL�� ���� 
		current->link = temp;	// current�� ����Ű�� ���� temp�� ����
	}
	
	else {	// �����尡 ����Ű�� ���� ���� ��� 
		temp->link = NULL;	// temp�� ����Ű�� ���� NULL�� ���� 
		h->first = temp;	// �����尡 ����Ű�� ���� temp�� ���� 
	}
	
	return 0;
}

int deleteFirst(headNode* h){	// ����Ʈ�� ù ��带 ���� 
	if(h->first){	// �����尡 ����Ű�� ���� �ִ� ��� 
		listNode* temp = (listNode*)malloc(sizeof(listNode));	// ����Ʈ��� temp ����
		temp = h->first;	// ����尡 ����Ű�� ��带 temp�� ���� 
		h->first = temp->link;	// temp�� ����Ű�� ��带 �����尡 ����Ű�� ���� 
		free(temp);	// temp �Ҵ� ���� 
	}
	
	return 0;
}

int deleteNode(headNode* h, int key){	// ����Ʈ ��ü �� �� ���� ��� ���� 
	if(h->first){	// �����尡 ����Ű�� ���� �ִ� ��� 
		listNode* temp = (listNode*)malloc(sizeof(listNode));	// ����Ʈ��� temp ���� 
		
		if(key == h->first->key){ // �Է¹��� ���� ����Ʈ�� ù ��� ���� ���� ��� 
			temp = h->first;	// �����尡 ����Ű�� ��带 temp�� ���� 
			h->first = temp->link;	// temp�� ����Ű�� ��带 �����尡 ����Ű�� ���� 
			free(temp);	// temp �Ҵ� ���� 
		}
		
		else{	// �Է¹��� ���� ù ��� ���� �ٸ� ���
			listNode* current = (listNode*)malloc(sizeof(listNode));	// ����Ʈ��� current ����
			current = h->first->link;	// ����尡 ����Ű�� ���� ��带 current�� ���� 
			temp = h->first;	// ����尡 ����Ű�� ��带 temp�� ���� 
			
			while(current->key != key){	// current key���� �Է°��� ���� �� ���� �ݺ� 
				temp = temp->link;
				current = current->link;	// current�� temp ���� ���� �̵�
			}
			
			if(current->link){	// current�� ����Ű�� ��尡 �����ϴ� ��� 
				temp->link = current->link;	// current�� ����Ű�� ��带 temp�� ����Ű�� ���� 
				free(current);	// current �Ҵ� ���� 
			}
		
			else{	// current�� ����Ű�� ��尡 �������� �ʴ� ���
				temp->link = NULL;	// temp�� ����Ű�� ���� NULL�� ���� 
				free(current);	// current �Ҵ� ���� 
			}
		}
	}

	return 0;

}

int deleteLast(headNode* h) {	// ����Ʈ�� ������ ��带 ���� 
	if(h->first){	// �����尡 ����Ű�� ���� �ִ� ��� 
		listNode* temp = (listNode*)malloc(sizeof(listNode));
		listNode* current = (listNode*)malloc(sizeof(listNode));	// ����Ʈ��� temp, current ���� 
		current = h->first->link;	// ����尡 ����Ű�� ���� ��带 current�� ���� 
		temp = h->first;	// ����尡 ����Ű�� ��带 temp�� ���� 

		while(current->link != NULL){	// current�� ����Ű�� ��尡 ���� �� ���� �ݺ� 
			temp = temp->link;
			current = current->link;	// temp�� current ���� ���� �̵�
		}
		
		temp->link = NULL;	// temp�� ����Ű�� ���� NULL�� ���� 
		free(current);	// current �Ҵ� ���� 
	}
	
	return 0;
}

int invertList(headNode* h) {	// ���Ḯ��Ʈ�� ������ �ݴ�� ���� 
	listNode* current = (listNode*)malloc(sizeof(listNode));	
	listNode* previous = (listNode*)malloc(sizeof(listNode));
	listNode* post = (listNode*)malloc(sizeof(listNode));	// ����Ʈ��� ����
	
	current = h->first;	// �����尡 ����Ű�� ��带 current�� ���� 
	previous = NULL;
	post = NULL;	// previous�� post�� NULL�� �ʱ�ȭ 
	
	while (current != NULL){	// current�� NULL�� ������ �ݺ� 
        post = current->link;	// current�� ����Ű�� ��带 post�� ���� 
        current->link = previous;	//	current�� ����Ű�� ��带 previous�� ���� 
        previous = current;	// previous ��带 current�� ���� 
        current = post;	// current ��带 post�� ���� 
    }
    h->first = previous; // previous�� �����尡 ����Ű�� ���� 

	return 0;
}

void printList(headNode* h) {
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if(h == NULL) {
		printf("Nothing to print....\n");
		return;	// h�� ����ִٸ� �����޼��� ��� 
	}

	p = h->first;	// �����尡 ����Ű�� ��带 p�� ���� 

	while(p != NULL) {
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->link;
		i++;
	}

	printf("  items = %d\n", i);
}

