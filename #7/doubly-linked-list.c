#include<stdio.h>
#include<stdlib.h>

typedef struct Node {
	int key;				// 값을 저장할 변수 
	struct Node* llink;		// 이전 노드를 가리키는 포인터 
	struct Node* rlink;		// 다음 노드를 가리키는 포인터 
} listNode;

typedef struct Head {
	struct Node* first;		// 연결리스트의 첫 노드를 가라키는 헤드노드 
}headNode;

int initialize(headNode** h);

int freeList(headNode* h);

int insertNode(headNode* h, int key);
int insertLast(headNode* h, int key);
int insertFirst(headNode* h, int key);
int deleteNode(headNode* h, int key);
int deleteLast(headNode* h);
int deleteFirst(headNode* h);
int invertList(headNode* h);

void printList(headNode* h);

int main()
{
	char command;				// 메뉴 입력 값 저장 
	int key;					// 노드에 저장할 값 저장 
	headNode* headnode=NULL;	// 헤드노드 초기화 

	printf("[----- [Jegal Dohyun] [2018038018] -----]\n");

	do{
		printf("----------------------------------------------------------------\n");
		printf("                     Doubly Linked  List                        \n");
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
			initialize(&headnode);	// 연결리스트를 초기화 
			break;
		case 'p': case 'P':
			printList(headnode);	// 연결리스트 출력 
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insertNode(headnode, key);	// 노드에 값을 담은 후 리스트에 추가 
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(headnode, key);	// 입력받은 값을 가진 노드 제거 
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insertLast(headnode, key);	// 노드에 값을 담은 후 리스트 마지막에 추가 
			break;
		case 'e': case 'E':
			deleteLast(headnode);		// 리스트 마지막의 노드 제거 
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			insertFirst(headnode, key);	// 노드에 값을 담은 후 리스트 처음에 추가 
			break;
		case 't': case 'T':
			deleteFirst(headnode);		// 리스트 처음의 노드 제거 
			break;
		case 'r': case 'R':
			invertList(headnode);		// 리스트를 역순으로 연결 
			break;
		case 'q': case 'Q':
			freeList(headnode);			// 리스트를 할당 해제 후 프로그램 종료 
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

int initialize(headNode** h) {
	if (*h != NULL)
		freeList(*h);	// h가 비어있지 않다면 할당 해제 

	headNode* temp = (headNode*)malloc(sizeof(headNode));
	temp->first = NULL;	// 헤드노드 temp 생성 후 NULL로 초기화 
	*h = temp;			// h를 temp로 설정 

	return 1;
}

int freeList(headNode* h) {
	listNode* p = h->first;	// 리스트노드 p를 생성 후 리스트의 첫 노드를 가리킴 
	listNode* prev = NULL;	// 이전 노드를 가리킬 리스트노드 prev 생성 후 NULL로 초기화 

	while (p != NULL) {		// p가 가리키는 노드가 없을 때 까지 반복 
		prev = p;			// p가 가리키는 노드를 prev가 가리킴 
		p = p->rlink;		// p의 다음 노드를 p로 교체 
		free(prev);			// prev가 가리키는 노드 할당 해제 
	}
	free(h);				// h가 가리키는 노드 할당 해제 

	return 0;
}

void printList(headNode* h) {
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if (h == NULL) {		// h가 비어있다면 오류메세지 출력 
		printf("Nothing to print....\n");
		return;
	}

	p = h->first;			// 헤더노드가 가리키는 노드를 p로 설정 

	while (p != NULL) {
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->rlink;
		i++;
	}

	printf("  items = %d\n", i);
}

int insertLast(headNode* h, int key) {	
	listNode* temp = (listNode*)malloc(sizeof(listNode)); 
	temp->key = key;		// 임시 리스트노드 temp 생성 후 입력받은 값을 temp의 key에 저장 

	if (h->first) {			// 헤더노드가 가리키는 노드가 있는 경우 
		listNode* current = (listNode*)malloc(sizeof(listNode));
		current = h->first;	// 임시 리스트노드 current 생성 후 리스트의 첫 노드를 가리킴 

		while (current->rlink != NULL) {	// current가 가리킬 다음 노드가 없을 때 까지 
			current = current->rlink;		// 다음 노드를 current로 설정 
		}

		temp->rlink = NULL;			// temp가 가리키는 다음노드를 NULL로 설정 
		temp->llink = current;		// temp가 가리키는 이전노드를 current로 설정 
		current->rlink = temp;		// current가 가리키는 다음노드를 temp로 설정 

	}

	else {		// 헤더노드가 가리키는 노드가 없는 경우 
		temp->rlink = NULL; 
		temp->llink = NULL;			// temp가 가리키는 이전, 다음노드를 NULL로 설정 
		h->first = temp;			// 헤더노드가 가리키는 첫 노드를 temp로 설정 
	}

	return 0;
}

int deleteLast(headNode* h) {
	if (h->first) {		// 헤더노드가 가리키는 노드가 있는 경우 
		listNode* temp = (listNode*)malloc(sizeof(listNode));
		listNode* current = (listNode*)malloc(sizeof(listNode));	// 임시 리스트노드 temp, current 생성
		current = h->first->rlink;	// current가 가리키는 노드를 리스트의 2번째 노드로 설정 
		temp = h->first;			// temp가 가리키는 노드를 리스츠의 첫 노드로 설정 

		while (current->rlink != NULL) {	// current가 가리키는 노드가 없을 때 까지 temp와 current를 다음노드로 이동 
			temp = temp->rlink;	
			current = current->rlink;
		}

		temp->rlink = NULL;	// temp가 가리키는 다음노드를 NULL로 설정 
		free(current);		// 마지막 노드를 가리키는 current 할당 해제 
	}

	return 0;
}

int insertFirst(headNode* h, int key) {
	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;	// 임시 리스트노드 node 생성 후 입력받은 값을 node의 key에 저장

	if (h->first) {		// 헤더노드가 가리키는 노드가 있는 경우 
		node->rlink = h->first;	// node가 가리키는 다음노드를 리스트의 첫 노드로 설정 
		node->llink = NULL;		// node가 가리키는 이전노드를 NULL로 설정 
		h->first->llink = node;	// 리스트의 2번째 노드가 가리키는 이전노드를 node로 변경 
		h->first = node;		// 헤드노드가 가리키는 노드를 node로 변경 
	}
	else {	// 헤더노드가 가리키는 노드가 없는 경우
		node->rlink = NULL;		
		node->llink = NULL;		// node가 가리키는 이전,다음노드를 NULL로 설정
		h->first = node;		// 헤드노드가 가리키는 노드를 node로 변경
	}

	return 0;
}

int deleteFirst(headNode* h) {
	if (h->first) {		// 헤더노드가 가리키는 노드가 있는 경우 
		listNode* temp = (listNode*)malloc(sizeof(listNode));
		temp = h->first;		// 임시 리스트노드 temp 생성 후 리스트의 첫 노드를 temp로 변경 
		h->first = temp->rlink;	// 리스트의 2번째 노드를 헤드노드가 가리키게 변경 
		free(temp);		// temp가 가리키는 노드 할당 해제 
	}
	return 0;
}

int invertList(headNode* h) {
	listNode* current = (listNode*)malloc(sizeof(listNode));	
	listNode* temp = (listNode*)malloc(sizeof(listNode));		// 임시 리스트노드 current, temp 생성
	
	current = h->first;	// current가 리스트의 첫 노드를 가리키게 설정 
	temp = NULL;		// temp는 NULL로 초기화 
	
	while (current != NULL){				// current가 가리키는 노드가 없을 때 까지 반복 
        temp = current->llink;				// temp가 current의 이전노드를 가리키게 설정 
        current->llink = current->rlink;	// current의 다음노드를 current의 이전노드로 변경 
        current->rlink = temp;				// temp를 current의 다음노드로 변경             
        current = current->llink;			// current의 이전노드를 current로 변경 
    }
    
    h->first = temp->llink;		// temp의 이전노드를 헤더노드가 가리키게 변경 
    
	return 0;
}

int insertNode(headNode* h, int key) {
	listNode* temp = (listNode*)malloc(sizeof(listNode));
	temp->key = key;	// 임시 리스트노드 temp 생성 후 입력받은 값을 temp의 key에 저장 

	if (h->first) {		// 헤더노드가 가리키는 노드가 있는 경우 
		listNode* current = (listNode*)malloc(sizeof(listNode));
		current = h->first;	// 임시 리스트노드 current 생성 후 리스트의 첫 노드를 가리키게 설정 

		if (temp->key <= h->first->key) {	// temp의 key가 리스트의 첫 노드의 값보다 작거나 같은 경우
			temp->rlink = h->first;			// temp의 다음노드를 리스트의 첫 노드로 설정 
			temp->llink = NULL;				// temp의 이전노드를 NULL로 설정 
			h->first->llink = temp;			// 리스트의 2번째 노드의 이전노드를 temp로 변경 
			h->first = temp;				// 헤드노드가 temp를 가리키게 변경 
		}

		else {
			while (current->rlink != NULL) {	// current의 다음노드가 없을 때 까지 변경 
				if (temp->key < current->rlink->key) {	// temp의 key가 다음노드의 값보다 작은 경우 
					temp->rlink = current->rlink;		// temp의 다음노드를 current의 다음노드로 설정 
					temp->llink = current;				// temp의 이전노드를 current로 설정 
					current->rlink->llink = temp;		// current의 다음노드의 이전노드를 temp로 변경 
					current->rlink = temp;				// current의 다음노드를 temp로 변경 
					break;
				}
				current = current->rlink;		// current의 다음노드로 이동 
			}

			if (current->rlink == NULL) {		// current가 가리키는 노드가 없을 경우 
				temp->rlink = NULL;				// temp의 다음노드를 NULL로 설정 
				temp->llink = current;			// temp의 이전노드를 current로 설정 
				current->rlink = temp;			// current의 다음노드를 temp로 설정 
			}
		}
	}

	else {	// 헤더노드가 가리키는 노드가 없는 경우
		temp->rlink = NULL; 
		temp->llink = NULL;	// temp의 이전,다음노드를 NULL로 설정
		h->first = temp;	// 헤드노드가 temp를 가리키게 변경 
	}
	return 0;
}

int deleteNode(headNode* h, int key) {
	if (h->first) {		// 헤더노드가 가리키는 노드가 있는 경우 
		listNode* temp = (listNode*)malloc(sizeof(listNode));	// 임시 리스트노드 temp 생성 

		if (key == h->first->key) {		// 입력받은 값이 리스트의 첫 노드 값과 같은 경우 
			temp = h->first;			// temp가 리스트의 첫 노드를 가리킴 
			h->first = temp->rlink;		// 헤드노드가 temp의 다음노드를 가리키게 변경 
			temp->rlink = NULL;			// temp의 다음노드를 NULL로 설정 
			free(temp);					// temp가 가리키는 노드 할당 해제 
		}

		else {
			listNode* current = (listNode*)malloc(sizeof(listNode));
			current = h->first->rlink;	// 임시 리스트노드 current 생성 후 리스트의 2번째 노드를 가리키게 설정 
			temp = h->first;			// temp가 리스트의 첫 노드를 가리키게 설정 

			while (current->key != key) {	// current의 key값이 입력된 값과 같을 때 까지 반복
				temp = temp->rlink;
				current = current->rlink;	// temp와 current를 다음노드로 이동 
			}

			if (current->rlink) {			// current의 다음노드가 존재하는 경우 
				temp->rlink = current->rlink;	// temp의 다음노드를 current의 다음노드로 변경 
				current->rlink->llink = temp;	// current의 다음노드의 이전노드를 temp로 변경 
				free(current);					// current가 가리키는 노드 할당 해제 
			}

			else {	// current가 가리키는 노드가 존재하지 않는 경우 
				temp->rlink = NULL;	// temp의 다음노드를 NULL로 설정 
				free(current);		// current가 가리키는 노드 할당 해제 
			}
		}
	}

	return 1;
}
