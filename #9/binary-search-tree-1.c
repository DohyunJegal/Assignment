#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int key;	// 노드에 저장할 값 
	struct node *left;	// 노드의 왼쪽 자식노드를 가리키는 포인터 
	struct node *right;	// 노드의 오른쪽 자식노드를 가리키는 포인터
} Node;

int initializeBST(Node** h);
void inorderTraversal(Node* ptr);	  /* recursive inorder traversal */
void preorderTraversal(Node* ptr);    /* recursive preorder traversal */
void postorderTraversal(Node* ptr);	  /* recursive postorder traversal */
int insert(Node* head, int key);  /* insert a node to the tree */
int deleteLeafNode(Node* head, int key);  /* delete the leaf node for the key */
Node* searchRecursive(Node* ptr, int key);  /* search the node for the key */
Node* searchIterative(Node* head, int key);  /* search the node for the key */
int freeBST(Node* head); /* free all memories allocated to the tree */

Node* modifiedSearch(Node* head, int key);	// 노드 삽입시 삽입 할 위치의 부모노드를 전달하는 함수 
Node* deleteSearch(Node* head, int key);	// 삭제할 리프노드를 검색하는 함수 
void freeHeadleft(Node* ptr);	// 헤드노드를 제외한 트리를 삭제하는 함수 

int main()
{
	char command;
	int key;
	Node* head = NULL;	// 헤드노드를 가리킬 포인터 
	Node* ptr = NULL;	/* temp */
	
	printf("[----- [Jegal Dohyun] [2018038018] -----]");

	do{
		printf("\n\n");
		printf("----------------------------------------------------------------\n");
		printf("                   Binary Search Tree #1                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize BST       = z                                       \n");
		printf(" Insert Node          = n      Delete Leaf Node             = d \n");
		printf(" Inorder Traversal    = i      Search Node Recursively      = s \n");
		printf(" Preorder Traversal   = p      Search Node Iteratively      = f\n");
		printf(" Postorder Traversal  = t      Quit                         = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initializeBST(&head);	// 트리 전체를 초기화 후 헤드노드 재할당 
			break;
		case 'q': case 'Q':
			freeBST(head);	// 트리 전체를 할당 해제 
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insert(head, key);	// 입력받은 값을 가진 노드를 트리에 추가 
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteLeafNode(head, key);	// 입력받은 값을 가진 리프노드 삭제 
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			ptr = searchIterative(head, key);	// 입력받은 값을 가진 노드를 반복구조로 검색 
			if(ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else
				printf("\n Cannot find the node [%d]\n", key);
			break;
		case 's': case 'S':
			printf("Your Key = ");
			scanf("%d", &key);
			ptr = searchRecursive(head->left, key);	// 입력받은 값을 가진 노드를 재귀구조로 검색 
			if(ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else
				printf("\n Cannot find the node [%d]\n", key);
			break;

		case 'i': case 'I':
			inorderTraversal(head->left);	// 중위순회 방식으로 트리 출력 
			break;
		case 'p': case 'P':
			preorderTraversal(head->left);	// 전위순회 방식으로 트리 출력 
			break;
		case 't': case 'T':
			postorderTraversal(head->left);	// 후위순회 방식으로 트리 출력 
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

int initializeBST(Node** h) {
	/* if the tree is not empty, then remove all allocated nodes from the tree*/
	if (*h != NULL)
		freeBST(*h);

	/* create a head node */
	*h = (Node*)malloc(sizeof(Node));
	(*h)->left = NULL;	/* root */
	(*h)->right = *h;
	(*h)->key = -9999;
	return 1;
}

void inorderTraversal(Node* ptr) {
	if (ptr){	// 트리가 존재하는 경우
		inorderTraversal(ptr->left);	// 왼쪽 자식노드로 재귀호출
		printf("%d ", ptr->key);	// 현재 노드의 값을 출력
		inorderTraversal(ptr->right);	// 오른쪽 자식노드로 재귀호출
	}
}

void preorderTraversal(Node* ptr) {
	if (ptr){	// 트리가 존재하는 경우
		printf("%d ", ptr->key);	// 현재 노드의 값을 출력
		preorderTraversal(ptr->left);	// 왼쪽 자식노드로 재귀호출
		preorderTraversal(ptr->right);	// 오른쪽 자식노드로 재귀호출
	}
}

void postorderTraversal(Node* ptr) {
	if (ptr){	// 트리가 존재하는 경우
		preorderTraversal(ptr->left);	// 왼쪽 자식노드로 재귀호출
		preorderTraversal(ptr->right);	// 오른쪽 자식노드로 재귀호출
		printf("%d ", ptr->key);	// 현재 노드의 값을 출력
	}

}

int insert(Node* head, int key) {
	Node *ptr = (Node*)malloc(sizeof(Node));
	Node *temp = (Node*)malloc(sizeof(Node));
	temp = modifiedSearch(head, key);	// 노드를 삽입할 위치의 부모노드 주소를 temp에 저장 

	if(temp || head) {	// temp나 head가 비어있지 않는 경우 
		ptr->key = key;	 
		ptr->left = NULL;
		ptr->right = NULL; // 입력받은 값을 ptr에 저장 후 리프노드로 만듦

		if (!head->left)	// 트리가 비어있는 경우 
			head->left = ptr;	// ptr을 트리의 root로 지정 
		else if (key < temp->key)	// temp의 값이 입력받은 값보다 큰 경우 
			temp->left = ptr;	// ptr을 temp의 왼쪽 자식노드로 연결 
		else	// 입력받은 값이 temp의 값보다 큰 경우  
			temp->right = ptr;	// ptr을 temp의 오른쪽 자식노드로 연결 
	}
	return 0;
}

int deleteLeafNode(Node* head, int key) {
	Node *temp = (Node*)malloc(sizeof(Node));
	Node *prev = (Node*)malloc(sizeof(Node));
	temp = deleteSearch(head, key);	// 삭제할 값을 가지고 있는 노드의 주소를 temp에 저장 
	prev = head->left;	// 트리의 root 주소를 prev에 저장 

	if (temp) {	// 삭제값을 가진 리프노드가 존재하는 경우 
		while (prev) {	// prev가 NULL일 때 까지 반복 
			if (prev->left == temp || prev->right == temp)	// prev의 자식노드가 temp일 경우 
				break;
			if (key < prev->key)	// prev의 값이 입력값보다 작은 경우 
				prev = prev->left;	// prev의 왼쪽 자식노드로 이동 
			else	// prev의 값이 입력값보다 큰 경우 
				prev = prev->right;	// prev의 오른쪽 자식노드로 이동 
		}

		if (prev == NULL) {	// 루트노드를 삭제하는 경우
			free(temp);	// temp 할당 해제 
			head->left = NULL;	// 헤드노드의 왼쪽 자식노드를 NULL로 변경 
		}
		else if (prev->left == temp) {	// 부모노드의 왼쪽 자식노드가 삭제 대상인 경우
			prev->left = NULL;	// 부모노드의 왼쪽 자식노드를 NULL로 변경 
			free(temp);	// temp 할당 해제 
		}
		else if (prev->right == temp) {	// 부모노드의 오른쪽 자식노드가 삭제 대상인 경우
			prev->right = NULL;	// 부모노드의 오른쪽 자식노드를 NULL로 변경 
			free(temp);	// temp 할당 해제 
		}
	}
	else	// 삭제값을 가진 리프노드가 없다면 오류메세지 출력 
		printf("리프노드에 해당 값이 존재하지 않습니다. \n");

	return 0;
}

Node* searchRecursive(Node* ptr, int key) {
	if (!ptr)	// 트리가 비어있는 경우, 찾는 값이 없는 경우 NULL 반환  
		return NULL;
	if (ptr->key == key)	// 입력값과 해당 노드의 값이 같은 경우 노드 주소 반환 
		return ptr;
	if (key < ptr->key)	// 입력값이 현재노드의 값보다 작은경우 
		return searchRecursive(ptr->left, key);	// 왼쪽 자식노드의 주소로 재귀호출 
	return searchRecursive(ptr->right, key);	// 입력값이 현재노드의 값보다 작은경우 오른쪽 자식노드의 주소로 재귀호출 
}

Node* searchIterative(Node* head, int key) {
	Node *temp = (Node*)malloc(sizeof(Node));
	temp = head->left;	// 트리의 root 주소를 temp에 저장 

	while (temp) {	// temp가 NULL일 때 까지 반복 
		if (temp->key == key)	// 입력값과 현재노드의 값과 같은 경우 
			return temp;	// 현재노드의 주소 반환 
		if (key < temp->key)	// 입력값이 현재노드의 값보다 작은 경우 
			temp = temp->left;	// temp를 현재노드의 왼쪽 자식노드로 변경 
		else	// 입력값이 현재노드의 값보다 큰 경우
			temp = temp->right;	// temp를 현재노드의 오른쪽 자식노드로 변경 
	}
	return NULL;
}

int freeBST(Node* head) {
	if (head) {	// 헤드노드가 비어있지 않는 경우 
		freeHeadleft(head->left);	// 트리의 root부터 전체를 삭제하는 함수 호출 
		free(head);	// 헤드노드 할당 해제 
	}
	return 0;
}

Node* modifiedSearch(Node* head, int key) {
	Node *temp = (Node*)malloc(sizeof(Node));
	Node *prev = (Node*)malloc(sizeof(Node));
	temp = head->left;	// 트리의 root 주소를 temp에 저장 

	if (!temp)	// temp가 NULL인 경우 NULL 반환 
		return NULL;

	while (temp) {	// temp가 NULL일 때 까지 반복 
		prev = temp;	// 현재 노드의 부모노드 표현을 위한 prev 할당  

		if (temp->key == key)	// 추가할 값을 가진 노드가 이미 존재하는 경우 NULL 반환 
			return NULL;
		if (key < temp->key)	// 입력값이 현재노드의 값보다 작은 경우  
			temp = temp->left;	// temp를 현재노드의 왼쪽 자식노드로 변경 
		else	// 입력값이 현재노드의 값보다 큰 경우
			temp = temp->right;	// temp를 현재노드의 오른쪽 자식노드로 변경 
	}
	return prev;	// 현재 노드의 부모노드 주소 반환 
}

Node* deleteSearch(Node* head, int key) {
	Node *temp = (Node*)malloc(sizeof(Node));
	temp = head->left;	// 트리의 root 주소를 temp에 저장 

	while (temp) {	// temp가 NULL일 때 까지 반복
		if (temp->key == key) {	// temp의 값이 입력값과 같은 경우 
			if (temp->left == NULL && temp->right == NULL)	// 노드가 리프노드인 경우 temp의 주소 반환 
				return temp; 
			else	// 노드가 리노드가 아닌 경우 NULL 반환 
				return NULL;
		}

		if (key < temp->key)	// 입력값이 현재노드의 값보다 작은 경우  
			temp = temp->left;	// temp를 현재노드의 왼쪽 자식노드로 변경 
		else	// 입력값이 현재노드의 값보다 큰 경우
			temp = temp->right;	// temp를 현재노드의 오른쪽 자식노드로 변경 
	}
	return NULL; 
}

void freeHeadleft(Node* ptr) {
	if (ptr) {	// ptr이 NULL이 아닌 경우 
		freeHeadleft(ptr->left);	// 왼쪽 자식노드의 주소로 재귀호출 
		freeHeadleft(ptr->right);	// 오른쪽 자식노드의 주소로 재귀호출 
		free(ptr);	// ptr 할당 해제 
	}
}
