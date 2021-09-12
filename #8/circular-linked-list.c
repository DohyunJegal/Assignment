#include<stdio.h>
#include<stdlib.h>

typedef struct Node {
	int key;	// 노드의 값을 저장할 변수 
	struct Node* llink;	// 이전노드를 가리키는 포인터 
	struct Node* rlink;	// 다음노드를 가리키는 포인터 
} listNode;

int initialize(listNode** h);
int freeList(listNode* h);
int insertLast(listNode* h, int key);
int deleteLast(listNode* h);
int insertFirst(listNode* h, int key);
int deleteFirst(listNode* h);
int invertList(listNode* h);

int insertNode(listNode* h, int key);
int deleteNode(listNode* h, int key);

void printList(listNode* h);

int main()
{
	char command;	// 메뉴 조작 값을 저장하는 변수 
	int key;	// 노드에 저장할 값을 저장하는 변수 
	listNode* headnode=NULL;	// 헤드노드 초기화 
	
	printf("[----- [Jegal Dohyun] [2018038018] -----]\n");

	do{
		printf("----------------------------------------------------------------\n");
		printf("                  Doubly Circular Linked List                   \n");
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
			initialize(&headnode);	// 리스트를 초기화 후 할당 
			break;
		case 'p': case 'P':
			printList(headnode);	// 리스트의 노드 주소와 저장 값 출력 
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insertNode(headnode, key);	// 입력받은 값을 노드에 저장 후 리스트에 추가 
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(headnode, key);	// 입력받은 값을 가진 노드를 리스트에서 제거 
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insertLast(headnode, key);	// 리스트의 마지막에 입력받은 값을 저장한 노드 추가 
			break;
		case 'e': case 'E':
			deleteLast(headnode);	// 리스트의 마지막의 노드를 제거 
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			insertFirst(headnode, key);	// 리스트의 처음에 입력받은 값을 저장한 노드 추가
			break;
		case 't': case 'T':
			deleteFirst(headnode);	// 리스트의 처음으 노드를 제거 
			break;
		case 'r': case 'R':
			invertList(headnode);	// 리스트를 역순으로 저장 
			break;
		case 'q': case 'Q':
			freeList(headnode);	// 리스트 전체 할당 해제 
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');	// q를 입력받으면 프로그램 종료 

	return 1;
}


int initialize(listNode** h) {
	if(*h != NULL)	// h가 비어있지 않다면 리스트 할당 해제 
		freeList(*h);

	*h = (listNode*)malloc(sizeof(listNode));
	(*h)->rlink = *h;
	(*h)->llink = *h;
	(*h)->key = -9999;	// 이전, 다음노드가 모두 자신을 가리키는 헤더노드 생성 
	return 1;
}

int freeList(listNode* h) {
	listNode* p = h->rlink;	// 리스트의 첫 노드 주소를 받는 리스트노드 p 할당
	listNode* prev = NULL; // 이전노드를 가리킬 리스트노드 prev 할당

	while (p->rlink != h){	// p가 가리키는 노드가 헤드노드일 때 까지 반복
		prev = p;	// p가 가리키는 노드를 prev가 가리킴 
		p = p->rlink;	// p는 다음노드로 이동
		free(prev);	// prev가 가리키는 노드 할당 해제 
	}
	free(p);	// p 할당 해제 

	return 0;
}

void printList(listNode* h) {
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if(h == NULL) {	// 리스트가 비어있다면 오류메세지 출력 
		printf("Nothing to print....\n");
		return;
	}

	p = h->rlink;	// 리스트노드 p가 리스트의 첫 노드를 가리킴 

	while(p != NULL && p != h) {	// p가 헤더노드나 빈 노드를 가리킬 때 까지 반복 
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->rlink;	// p는 다음노드로 이동 
		i++;
	}
	printf("  items = %d\n", i);

	printf("\n---checking addresses of links\n");
	printf("-------------------------------\n");
	printf("head node: [llink]=%p, [head]=%p, [rlink]=%p\n", h->llink, h, h->rlink);

	i = 0;
	p = h->rlink;  
	while(p != NULL && p != h) {
		printf("[ [%d]=%d ] [llink]=%p, [node]=%p, [rlink]=%p\n", i, p->key, p->llink, p, p->rlink);
		p = p->rlink;
		i++;
	}

}

int insertLast(listNode* h, int key) {
	listNode* temp = (listNode*)malloc(sizeof(listNode)); 
	temp->key = key;	// 임시 리스트노드 temp 생성 후 입력받은 값을 temp의 key에 저장

	if (h) {	// 헤더노드가 존재하는 경우 
		listNode* current = (listNode*)malloc(sizeof(listNode));
		current = h;	// 임시 리스트노드 current 생성 후 헤더노드를 가리킴 

		while (current->rlink != h) {	// current의 다음노드가 헤더노드일 때 까지 반복 
			current = current->rlink;	// current의 다음노드로 이동 
		}

		temp->rlink = h;	// temp의 다음노드를 헤더노드로 설정 
		temp->llink = current;	// temp의 이전노드를 current로 설정 
		current->rlink = temp;	// current의 다음노드를 temp로 변경 
		h->llink = temp;	// 헤더노드의 이전노드를 temp로 변경 
	}

	else {	// 헤더노드가 존재하지 않는 경우 
		temp->rlink = temp;
		temp->llink = temp;
		h = temp;	// 이전, 다음노드가 자신을 가리키는 헤더노드 생성
	}
	
	return 1;
}

int deleteLast(listNode* h) {
	if (h) {	// 헤더노드가 존재하는 경우	
		listNode* temp = (listNode*)malloc(sizeof(listNode));
		listNode* current = (listNode*)malloc(sizeof(listNode));
		current = h->rlink;	// 리스트의 첫 노드를 가리키는 리스트노드 current 할당 
		temp = h;	// 헤더노드를 가리키는 리스트노드 temp 할당 

		while (current->rlink != h) {	// current의 다음노드가 헤더노드일 때 까지 반복 
			temp = temp->rlink;	
			current = current->rlink;	// temp와 current의 각각 다음노드로 이동 
		}

		temp->rlink = h;	// temp의 다음노드를 헤더노드로 설정 
		h->llink = temp;	// 헤더노드의 이전노드를 temp로 변경 
		current->llink = current; 
		current->rlink = current;
		free(current);	// current의 이전, 다음노드를 자신으로 변경 후 할당 해제 
	}

	return 1;
}

int insertFirst(listNode* h, int key) {
	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;

	if (h) {	// 헤더노드가 존재하는 경우
		node->rlink = h->rlink;	// node의 다음링크를 리스트의 첫 노드로 설정 
		node->llink = h;	// node의 이전링크를 헤더노드로 설정 
		h->rlink->llink = node;	// 리스트의 첫 노드의 이전노드를 node로 변경 
		h->rlink = node;	// 헤더노드의 다음노드를 node로 변경 
	}
	else {	// 헤더노드가 존재하지 않는 경우
		node->rlink = node;		
		node->llink = node;	
		h = node;	// 이전, 다음노드가 자신을 가리키는 헤더노드 생성
	}

	return 1;
}

int deleteFirst(listNode* h) {
	if (h) {	// 헤더노드가 존재하는 경우
		listNode* temp = (listNode*)malloc(sizeof(listNode));
		temp = h->rlink;	// 리스트의 첫 노드를 가리키는 리스트노드 temp 할당 
		
		temp->rlink->llink = h;	// 리스트의 두번 째 노드의 이전노드를 헤더노드로 변경 
		h->rlink = temp->rlink;	// 헤더노드의 다음노드를 리스트의 두번 째 노드로 변경 
		temp->llink = temp;
		temp->rlink = temp;
		free(temp);	// temp의 이전, 다음노드를 자신으로 변경 후 할당 해제
	}
	
	return 1;

}

int invertList(listNode* h) {
	listNode* post = (listNode*)malloc(sizeof(listNode));
	listNode* current = (listNode*)malloc(sizeof(listNode));
    current = h;	// 헤더노드를 가리키는 리스트노드 h와 h의 다음노드를 가리킬 post 할당 
    
    while(post != h){	// post가 헤더노드를 가리킬 때 까지 반복 
    	post = current->rlink;	// post를 current의 다음노드를 가리키게 설정 
        current->rlink = current->llink;	// current의 다음노드를 반대방향인 이전노드로 변경 
        current->llink = post;	// current의 이전노드를 반대방향인 post로 변경 
        current = post;	// post가 가리키는 노드로 current 이동 
	}
    
	return 0;
}

int insertNode(listNode* h, int key) {
	listNode* temp = (listNode*)malloc(sizeof(listNode));
	temp->key = key;	// 리스트노드 temp 할당 후 입력받은 값을 저장 

	if (h) {	// 헤더노드가 존재하는 경우	
		listNode* current = (listNode*)malloc(sizeof(listNode));
		current = h;	// 헤더노드를 가리킬 리스트노드 current 할당 

		if (temp->key <= h->key) {	// temp의 key가 리스트의 첫 노드의 값보다 작거나 같은 경우	
			temp->rlink = h->rlink;	// temp의 다음노드를 리스트의 첫 노드로 설정 
			temp->llink = h;	// temp의 이전노드를 헤더노드로 설정 
			h->rlink->llink = temp;	// 리스트의 첫 노드의 이전노드를 temp로 변경 
			h->rlink = temp;	// 헤더노드의 다음노드를 temp로 변경 
		}

		else {	// temp의 key가 리스트의 첫 노드의 값과 다른 경우 
			while (current->rlink != h) {	// current의 다음노드가 헤더노드일 때 까지 반복 
				if (temp->key < current->rlink->key) {	// temp의 key가 다음노드의 값보다 작은 경우  
					temp->rlink = current->rlink;	// temp의 다음노드를 current의 다음노드로 설정 
					temp->llink = current;	// temp의 이전노드를 current로 설정 
					current->rlink->llink = temp;	// current의 다음노드의 이전노드를 temp로 변경
					current->rlink = temp;	// current의 다음노드를 temp로 변경
					break;
				}
				current = current->rlink;	// current가 다음노드로 이동 
			}

			if (current->rlink == h) {	// current가 가리키는 노드 헤더노드일 경우 
				temp->rlink = h;	// temp의 다음노드를 헤더노드로 설정 
				temp->llink = current;	// temp의 이전노드를 current로 설정 
				current->rlink = temp;	// current의 다음노드를 temp로 변경 
				h->llink = temp;	// 헤더노드의 이전노드를 temp로 변경 
			}
		}
	}

	else {	// 헤더노드가 존재하지 않는 경우
		temp->rlink = temp;		
		temp->llink = temp;	
		h = temp;	// 이전, 다음노드가 자신을 가리키는 헤더노드 생성
	}

	return 0;
}

int deleteNode(listNode* h, int key) {
	if (h) {	// 헤더노드가 존재하는 경우	
		listNode* temp = (listNode*)malloc(sizeof(listNode));	// 리스트노드 temp 할당 
		
		if (key == h->key) {	// 입력받은 값이 리스트의 첫 노드 값과 같은 경우
			temp = h->rlink;	// temp가 리스트의 첫 노드를 가리키게 설정 
			
			temp->rlink->llink = h;	// 리스트의 두번 째 노드의 이전노드를 헤더노드로 변경 
			h->rlink = temp->rlink;	// 헤더노드의 다음노드를 리스트의 두번 째 노드로 변경 
			temp->llink = temp;
			temp->rlink = temp;
			free(temp);	// temp의 이전, 다음노드를 자신으로 변경 후 할당 해제
		}

		else {	// 입력받은 값이 리스트의 첫 노드 값과 다른 경우 
			listNode* current = (listNode*)malloc(sizeof(listNode));
			current = h->rlink;	// 리스트노드의 첫 노드를 가리키는 리스트노드 currnet 할당 
			temp = h;	// temp가 헤더노드를 가리키게 설정 

			while (current->key != key) {	// current의 key값이 입력된 값과 같을 때 까지 반복
				temp = temp->rlink;
				current = current->rlink;	// temp와 current의 각각 다음노드로 이동
			}

			if (current->rlink) {	// current의 다음노드가 존재하는 경우
				current->rlink->llink = temp;	// current 다음노드의 이전노드를 temp로 변경 
				temp->rlink = current->rlink;	// temp의 다음노드를 current의 다음노드로 변경 
				current->llink = current;
				current->rlink = current;
				free(current);	// current의 이전, 다음노드를 자신으로 변경 후 할당 해제
			}

			else {	// current의 다음노드가 존재하지 않는 경우
				temp->rlink = h;	// temp의 다음노드를 헤더노드로 변경 
				h->llink = temp;	// 헤더노드의 이전노드를 temp로 변경 
				current->llink = current;
				current->rlink = current;
				free(current);	// current의 이전, 다음노드를 자신으로 변경 후 할당 해제
			}
		}
	}

	return 0;
}
