#include<stdio.h>
#include<stdlib.h>

typedef struct Node {
	int key;			// 노드에 값을 저장 
	struct Node* link;	// 다음 노드를 가리킴 
} listNode;

typedef struct Head {
	struct Node* first;	// 연결리스트의 처음을 가리키는 헤드 
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
	char command;				// 메뉴 입력 값 저장  
	int key;					// 노드에 입력할 숫자 저장 
	headNode* headnode = NULL;	// 리스트를 초기화 

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
			headnode = initialize(headnode);	// 연결리스트 전체를 할당해제하고 초기화
			break;
		case 'p': case 'P':
			printList(headnode);	// 연결리스트 전체 출력 
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insertNode(headnode, key);	// 값을 입력받고 노드를 리스트에 추가 
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(headnode, key);	// 입력받은 값을 가진 노드를 삭제 
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insertLast(headnode, key);	// 값을 입력받고 노드를 리스트의 마지막에 추가 
			break;
		case 'e': case 'E':
			deleteLast(headnode);	// 리스트 마지막의 노드를 삭제 
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			insertFirst(headnode, key);	// 입력받은 값을 리스트의 처음에 추가 
			break;
		case 't': case 'T':
			deleteFirst(headnode);	// 리스트 처음의 노드를 삭제 
			break;
		case 'r': case 'R':
			invertList(headnode);	//  리스트를 역순으로 연결 
			break;
		case 'q': case 'Q':
			freeList(headnode);	// 연결리스트를 할당해제하고 프로그램 종료 
			break;
		default:								
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;	// 이외의 입력값은 오류메세지 출력 
		}

	}while(command != 'q' && command != 'Q');	// 종료값 입력 전 까지 반복 

	return 1;
}

headNode* initialize(headNode* h){
	if(h != NULL)
		freeList(h);	// h가 바어있지 않다면 할당 해제 

	headNode* temp = (headNode*)malloc(sizeof(headNode));	 
	temp->first = NULL;	// 임시 헤드노드 할당 후 NULL로 초기화
	return temp;	// 임시 헤드노드 반환 
}

int freeList(headNode* h){
	listNode* p = h->first;	// 리스트노드 p를 생성 후 h의 첫 리스트노드를 가리킴 

	listNode* prev = NULL;	// 리스트노드 prev를 생성 후 NULL로 초기화 
	while(p != NULL) {	// p 노드가 없을 때 까지 반복  
		prev = p;	// prev가 p를 가리킴 
		p = p->link; // p 다음 주소를 p를 가리키게 함 
		free(prev);	// prev 할당 해제 
	}
	free(h); // h 할당해제 
	return 0;
}

int insertFirst(headNode* h, int key){	// 리스트의 첫 부분에 노드를 추가 
	listNode* node = (listNode*)malloc(sizeof(listNode));	// 리스트노드 node 생성 
	node->key = key;	// node의 키 값에 입력받은 key 대입 

	node->link = h->first;	// 헤드노드가 가리키던 노드를 node가 가리키게 변경 
	h->first = node;	// 헤드노드가 node를 가리키게 변경 

	return 0;
}

int insertNode(headNode* h, int key){	// 리스트 전체 중 한 곳에 노드 추가 
	listNode* temp = (listNode*)malloc(sizeof(listNode));	// 리스트노드 temp 생성 
	temp->key = key;	// 입력받은 값을 temp key에 저장 
	
	if(h->first){	// 헤더노드가 가리키는 값이 있는 경우 
		listNode* current = (listNode*)malloc(sizeof(listNode));	// 리스트노드 current 생성 
		current = h->first;	// current가 헤드노드가 가리키던 노드를 가리키게 설정 
		
		if(temp->key <= h->first->key){	// temp key가 리스트의 첫 노드의 값보다 작거나 같은 경우 
			temp->link =  h->first;	// 헤드노드가 가리키던 노드를 temp가 가리키게 변경 
			h->first = temp;	// 헤드노드가 temp를 가리키게 변경 
		}
		
		else{
			while(current->link != NULL){	// current가 가리키는 노드가 없을 때 까지 반복 
				if(temp->key < current->link->key){	// 입력받은 값이 다음 노드의 값보다 작은 경우 
					temp->link = current->link;	// current가 가리키단 노드를 temp가 가리키게 변경 
					current->link = temp;	// current가 temp를 가리키게 변경 
					break;
				}
			current = current->link; // current의 다음 노드로 이동 
			}
			
			if(current->link == NULL){	// curren가 가리키는 노드가 없는 경우 
				temp->link = NULL;	// temp가 가리키는값을 NULL로 변경 
				current->link = temp;	// current가 가리키는 값을 temp로 변경 		
			}
		}
	}
	
	else { // 헤더노드가 가리키는 값이 없는 경우 
		temp->link = NULL;	// temp가 가리키는 값을 NULL로 변경 
		h->first = temp;	// 헤더노드가 가리키는 값을 temp로 설정 
	}
	
	return 0;
}

int insertLast(headNode* h, int key){	// 리스트의 마지막 부분에 노드를 추가 
	listNode* temp = (listNode*)malloc(sizeof(listNode));	// 리스트노드 temp 생성 
	temp->key = key;	// 입력받은 값을 temp key에 저장 
	
	if(h->first){	// 헤더노드가 가리키는 값이 있는 경우 
		listNode* current = (listNode*)malloc(sizeof(listNode));	// 리스트노드 current 생성 
		current = h->first;	// current가 헤드노드가 가리키던 노드를 가리키게 설정 

		while(current->link != NULL){	
			current = current->link;	// current가 가리키는 노드가 없을 때 까지 다음 노드로 이동 
		}
		
		temp->link = NULL;	// temp가 가리키는 값을 NULL로 변경 
		current->link = temp;	// current가 가리키는 값을 temp로 설정
	}
	
	else {	// 헤더노드가 가리키는 값이 없는 경우 
		temp->link = NULL;	// temp가 가리키는 값을 NULL로 변경 
		h->first = temp;	// 헤더노드가 가리키는 값을 temp로 설정 
	}
	
	return 0;
}

int deleteFirst(headNode* h){	// 리스트의 첫 노드를 제거 
	if(h->first){	// 헤더노드가 가리키는 값이 있는 경우 
		listNode* temp = (listNode*)malloc(sizeof(listNode));	// 리스트노드 temp 생성
		temp = h->first;	// 헤드노드가 가리키던 노드를 temp로 설정 
		h->first = temp->link;	// temp가 가리키는 노드를 헤더노드가 가리키게 변경 
		free(temp);	// temp 할당 해제 
	}
	
	return 0;
}

int deleteNode(headNode* h, int key){	// 리스트 전체 중 한 곳의 노드 제거 
	if(h->first){	// 헤더노드가 가리키는 값이 있는 경우 
		listNode* temp = (listNode*)malloc(sizeof(listNode));	// 리스트노드 temp 생성 
		
		if(key == h->first->key){ // 입력받은 값이 리스트의 첫 노드 값과 같은 경우 
			temp = h->first;	// 헤더노드가 가리키는 노드를 temp로 설정 
			h->first = temp->link;	// temp가 가리키던 노드를 헤더노드가 가리키게 변경 
			free(temp);	// temp 할당 해제 
		}
		
		else{	// 입력받은 값이 첫 노드 값과 다른 경우
			listNode* current = (listNode*)malloc(sizeof(listNode));	// 리스트노드 current 생성
			current = h->first->link;	// 헤드노드가 가리키는 다음 노드를 current로 설정 
			temp = h->first;	// 헤드노드가 가리키는 노드를 temp로 설정 
			
			while(current->key != key){	// current key값이 입력값과 같을 때 까지 반복 
				temp = temp->link;
				current = current->link;	// current와 temp 다음 노드로 이동
			}
			
			if(current->link){	// current가 가리키는 노드가 존재하는 경우 
				temp->link = current->link;	// current가 가리키던 노드를 temp가 가리키게 변경 
				free(current);	// current 할당 해제 
			}
		
			else{	// current가 가리키는 노드가 존재하지 않는 경우
				temp->link = NULL;	// temp가 가리키는 값을 NULL로 설정 
				free(current);	// current 할당 해제 
			}
		}
	}

	return 0;

}

int deleteLast(headNode* h) {	// 리스트의 마지막 노드를 제거 
	if(h->first){	// 헤더노드가 가리키는 값이 있는 경우 
		listNode* temp = (listNode*)malloc(sizeof(listNode));
		listNode* current = (listNode*)malloc(sizeof(listNode));	// 리스트노드 temp, current 생성 
		current = h->first->link;	// 헤드노드가 가리키는 다음 노드를 current로 설정 
		temp = h->first;	// 헤드노드가 가리키는 노드를 temp로 설정 

		while(current->link != NULL){	// current가 가리키는 노드가 없을 때 까지 반복 
			temp = temp->link;
			current = current->link;	// temp와 current 다음 노드로 이동
		}
		
		temp->link = NULL;	// temp가 가리키는 값을 NULL로 변경 
		free(current);	// current 할당 해제 
	}
	
	return 0;
}

int invertList(headNode* h) {	// 연결리스트의 연결을 반대로 연결 
	listNode* current = (listNode*)malloc(sizeof(listNode));	
	listNode* previous = (listNode*)malloc(sizeof(listNode));
	listNode* post = (listNode*)malloc(sizeof(listNode));	// 리스트노드 생성
	
	current = h->first;	// 헤더노드가 가리키는 노드를 current로 설정 
	previous = NULL;
	post = NULL;	// previous와 post는 NULL로 초기화 
	
	while (current != NULL){	// current가 NULL일 때까지 반복 
        post = current->link;	// current가 가리키는 노드를 post로 설정 
        current->link = previous;	//	current가 가리키는 노드를 previous로 변경 
        previous = current;	// previous 노드를 current로 설정 
        current = post;	// current 노드를 post로 설정 
    }
    h->first = previous; // previous를 헤더노드가 가리키게 변경 

	return 0;
}

void printList(headNode* h) {
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if(h == NULL) {
		printf("Nothing to print....\n");
		return;	// h가 비어있다면 오류메세지 출력 
	}

	p = h->first;	// 헤더노드가 가리키는 노드를 p로 설정 

	while(p != NULL) {
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->link;
		i++;
	}

	printf("  items = %d\n", i);
}

