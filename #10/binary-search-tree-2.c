#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int key;	// 값을 저장할 변수 
	struct node *left;	// 노드의 왼쪽 자식노드를 가리키는 포인터 
	struct node *right;	// 노드의 오른쪽 자식노드를 가리키는 포인터 
} Node;

/* for stack */
#define MAX_STACK_SIZE 20
Node* stack[MAX_STACK_SIZE];
int top = -1;

Node* pop();
void push(Node* aNode);

/* for queue */
#define MAX_QUEUE_SIZE 20
Node* queue[MAX_QUEUE_SIZE];
int front = 0;
int rear = 0;

Node* deQueue();
void enQueue(Node* aNode);
int initializeBST(Node** h);

/* functions that you have to implement */
void recursiveInorder(Node* ptr);	  /* recursive inorder traversal */
void iterativeInorder(Node* ptr);     /* iterative inorder traversal */
void levelOrder(Node* ptr);	          /* level order traversal */
int insert(Node* head, int key);      /* insert a node to the tree */
int deleteNode(Node* head, int key);  /* delete the node for the key */
int freeBST(Node* head); /* free all memories allocated to the tree */

/* you may add your own defined functions if necessary */

int main()
{
	char command;	// 메뉴 입력을 저장할 변수 
	int key;	// 입력값을 저장하는 변수 
	Node* head = NULL;	// 헤드노드 생성 

	printf("[----- [Jegal Dohyun] [2018038018] -----]");

	do {
		printf("\n\n");
		printf("----------------------------------------------------------------\n");
		printf("                   Binary Search Tree #2                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize BST       = z                                       \n");
		printf(" Insert Node          = i      Delete Node                  = d \n");
		printf(" Recursive Inorder    = r      Iterative Inorder (Stack)    = t \n");
		printf(" Level Order (Queue)  = l      Quit                         = q \n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch (command) {
		case 'z': case 'Z':
			initializeBST(&head);	// 트리 전체를 초기화 후 헤드노드 재할당 
			break;
		case 'q': case 'Q':
			freeBST(head);	// 트리 전체를 할당 해제
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insert(head, key);	// 입력받은 값을 가진 노드를 트리에 추가 
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(head, key);	// 입력받은 값을 가진 노드 삭제 
			break;
		case 'r': case 'R':
			recursiveInorder(head->left);	// 순환방식으로 트리 출력 
			break;
		case 't': case 'T':
			iterativeInorder(head->left);	// 순차방식으로 트리 출력 
			break;
		case 'l': case 'L':
			levelOrder(head->left);	// 레벨순회 방식으로 트리 출력 
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}
	} while (command != 'q' && command != 'Q');

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

	top = -1;
	front = rear = 0;

	return 1;
}

void recursiveInorder(Node* ptr) {
	if (ptr) {	// 트리가 존재하는 경우
		recursiveInorder(ptr->left);	// 왼쪽 자식노드 재귀호출 
		printf(" [%d] ", ptr->key);	// 현재 노드의 값을 출력 
		recursiveInorder(ptr->right);	// 오른쪽 자식노드 재귀호출 
	}
}

void iterativeInorder(Node* node) {
	top = -1;	// 스택의 top을 -1로 초기화 
	for (;;) {
		for (; node; node = node->left)	// 트리의 맨 왼쪽 자식노드에 도달할 때까지 반복 
			push(node);	// 현재 노드를 스택에 push 
		node = pop();	// 스택에서 pop한 노드를 node로 변경 
		if (!node) break;	// node가 NULL이면 break 
		printf(" [%d] ", node->key);	// 현재 노드의 값을 출력 
		node = node->right;	// node의 우측자식을 node로 변경 
	}
}

void levelOrder(Node* ptr) {
	front = rear = 0;	// 큐의 front, rear을 0으로 초기화 
	if (!ptr) return;	// ptr이 NULL이면 break 
	enQueue(ptr);	// ptr의 노드를 큐에 추가 
	for (;;) {
		ptr = deQueue();	// 큐에서 deQueue한 노드를 ptr로 변경 
		if (ptr) {	// ptr이 존재하는 경우 
			printf(" [%d] ", ptr->key);	// 현재 노드의 값을 출력 
			if (ptr->left)	// ptr의 왼쪽 자식이 있는 경우 
				enQueue(ptr->left);	// 왼쪽 자식을 enQueue 
			if (ptr->right)	// ptr의 오른쪽 자식이 있는경우 
				enQueue(ptr->right);	// 오른쪽 자식을 enQueue 
		}
		else break;	// ptr이 존재하지 않는 경우 break 
	}
}

int insert(Node* head, int key) {
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->key = key;
	newNode->left = NULL;
	newNode->right = NULL;

	if (head->left == NULL) {
		head->left = newNode;
		return 1;
	}

	/* head->left is the root */
	Node* ptr = head->left;

	Node* parentNode = NULL;
	while (ptr != NULL) {

		/* if there is a node for the key, then just return */
		if (ptr->key == key) return 1;

		/* we have to move onto children nodes,
		* keep tracking the parent using parentNode */
		parentNode = ptr;

		/* key comparison, if current node's key is greater than input key
		* then the new node has to be inserted into the right subtree;
		* otherwise the left subtree.
		*/
		if (ptr->key < key)
			ptr = ptr->right;
		else
			ptr = ptr->left;
	}

	/* linking the new node to the parent */
	if (parentNode->key > key)
		parentNode->left = newNode;
	else
		parentNode->right = newNode;
	return 1;
}

int deleteNode(Node* head, int key) {
	Node *temp = (Node*)malloc(sizeof(Node));
	Node *prev = (Node*)malloc(sizeof(Node));
	Node *post = (Node*)malloc(sizeof(Node));
	Node *p_temp = (Node*)malloc(sizeof(Node));
	temp = head->left;	// temp가 root노드를 가리키게 설정 
	prev = post = p_temp = NULL;

	while (temp) {	// temp가 NULL이 아닐 때 까지 반복 
		if (temp->key == key)	
			break;	// temp가 가리키는 노드의 값이 입력 값과 같은 경우 break 
		prev = temp; 
		if (key < temp->key)	// temp가 가리키는 노드 값보다 입력 값이 작은 경우 
			temp = temp->left;	// temp의 왼쪽 자식노드를 temp로 설정 
		else	// temp가 가리키는 노드 값보다 입력 값이 큰 경우 
			temp = temp->right;	// temp의 오른쪽 자식노드를 temp로 설정 
	}

	if (!temp->left && !temp->right) {	// 삭제할 노드의 자식노드가 없는 경우
		if (prev) {	// 삭제 대상이 루트노드가 아닌경우
			if (prev->left == temp) {	// 삭제 노드가 부모노드의 왼쪽 자식일 경우 
				prev->left = NULL;
				free(temp);
			}
			else {	// 삭제 노드가 부모노드의 오른쪽 자식일 경우 
				prev->right = NULL;
				free(temp);
			}
		}
		else {	// 삭제 대상이 루트노드인 경우 
			head->left = NULL;
			free(temp);
		}
	}
	else if (!temp->left || !temp->right) {	// 삭제할 노드의 자식노드가 하나인 경우
		if (prev) {	// 삭제 대상이 루트노드가 아닌경우
			if (prev->left == temp) {	// 삭제 노드가 부모노드의 왼쪽 자식일 경우 
				if (temp->left)	// 삭제 노드의 왼쪽 자식노드가 존재하는 경우 
					prev->left = temp->left;
				else	// 삭제 노드의 오른쪽 자식노드가 존재하는 경우 
					prev->left = temp->right;
				free(temp);
			}
			else {	// 삭제 노드가 부모노드의 오른쪽 자식일 경우 
				if (temp->left)	// 삭제 노드의 왼쪽 자식노드가 존재하는 경우
					prev->right = temp->left;
				else	// 삭제 노드의 오른쪽 자식노드가 존재하는 경우 
					prev->right = temp->right;
				free(temp);
			}
		}
		else {	// 삭제 대상이 루트노드인 경우 
			if (temp->left)// 삭제 노드의 왼쪽 자식노드가 존재하는 경우
				head->left = temp->left;
			else	// 삭제 노드의 오른쪽 자식노드가 존재하는 경우 
				head->left = temp->right;
			free(temp);
		}
	}
	else {	// 삭제할 노드의 자식노드가 두 개인 경우
		post = temp->right;	// 삭제할 노드의 오른쪽 자식노드를 post로 설정 
		while (post->left) {	// post의 왼쪽 자식노드가 없을 때 까지 반복 
			p_temp = post;	// p_temp를 post의 부모노드로 설정 
			post = post->left;	// post를 왼쪽 자식노드로 변경 
		}
		temp->key = post->key;	// post의 값을 temp에 이동 

		if (p_temp) {	// p_temp가 존재하는 경우 
			if (post->right)	// post의 우측 자식노드가 존재하는 경우 
				p_temp->left = post->right;	// post의 부모노드가 post의 자식노드를 가리키게 변경 
			else
				p_temp->left = NULL;
			free(post);
		}
		else {	// p_temp가 존재하지 않는 경우 
			if (post->right)	// post의 우측 자식노드가 존재하는 경우 
				temp->right = post->right;	// temp의 우측 자식노드를  post의 자식노드를 가리키게 변경 
			else
				temp->right = NULL;
			free(post);
		}
	}
	return 0;
}


void freeNode(Node* ptr) {
	if (ptr) {
		freeNode(ptr->left);
		freeNode(ptr->right);
		free(ptr);	// 재귀호출을 통한 트리 할당해제 
	}
}

int freeBST(Node* head) {
	if (head->left == head) {	// root 노드가 존재하지 않는 경우 
		free(head);
		return 1;
	}

	Node* p = head->left;
	freeNode(p);
	free(head);
	return 1;
}

Node* pop() {
	if (top == -1)	// 스택이 비어있는 경우 
		return NULL;
	return stack[top--];	// 현재 stack[top]을 반환하고 top-- 
}

void push(Node* aNode) {
	if (top < MAX_STACK_SIZE - 1)	// 스택이 꽉 차지 않은 경우 
		stack[++top] = aNode;	// 노드를 스택에 top 
}

Node* deQueue() {
	if (front == rear)	// 큐가 비어있는 경우 
		return NULL;
	front = (front + 1) % MAX_QUEUE_SIZE;
	return queue[front];	// 현재 queue[front]를 반환 
}

void enQueue(Node* aNode) {
	rear = (rear + 1) % MAX_QUEUE_SIZE;
	if (front != rear)	// 큐가 꽉 차지 않은 경우 
		queue[rear] = aNode;	// 노드를 큐에 enque 
}
