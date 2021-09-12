#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int key;	// ���� ������ ���� 
	struct node *left;	// ����� ���� �ڽĳ�带 ����Ű�� ������ 
	struct node *right;	// ����� ������ �ڽĳ�带 ����Ű�� ������ 
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
	char command;	// �޴� �Է��� ������ ���� 
	int key;	// �Է°��� �����ϴ� ���� 
	Node* head = NULL;	// ����� ���� 

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
			initializeBST(&head);	// Ʈ�� ��ü�� �ʱ�ȭ �� ����� ���Ҵ� 
			break;
		case 'q': case 'Q':
			freeBST(head);	// Ʈ�� ��ü�� �Ҵ� ����
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insert(head, key);	// �Է¹��� ���� ���� ��带 Ʈ���� �߰� 
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(head, key);	// �Է¹��� ���� ���� ��� ���� 
			break;
		case 'r': case 'R':
			recursiveInorder(head->left);	// ��ȯ������� Ʈ�� ��� 
			break;
		case 't': case 'T':
			iterativeInorder(head->left);	// ����������� Ʈ�� ��� 
			break;
		case 'l': case 'L':
			levelOrder(head->left);	// ������ȸ ������� Ʈ�� ��� 
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
	if (ptr) {	// Ʈ���� �����ϴ� ���
		recursiveInorder(ptr->left);	// ���� �ڽĳ�� ���ȣ�� 
		printf(" [%d] ", ptr->key);	// ���� ����� ���� ��� 
		recursiveInorder(ptr->right);	// ������ �ڽĳ�� ���ȣ�� 
	}
}

void iterativeInorder(Node* node) {
	top = -1;	// ������ top�� -1�� �ʱ�ȭ 
	for (;;) {
		for (; node; node = node->left)	// Ʈ���� �� ���� �ڽĳ�忡 ������ ������ �ݺ� 
			push(node);	// ���� ��带 ���ÿ� push 
		node = pop();	// ���ÿ��� pop�� ��带 node�� ���� 
		if (!node) break;	// node�� NULL�̸� break 
		printf(" [%d] ", node->key);	// ���� ����� ���� ��� 
		node = node->right;	// node�� �����ڽ��� node�� ���� 
	}
}

void levelOrder(Node* ptr) {
	front = rear = 0;	// ť�� front, rear�� 0���� �ʱ�ȭ 
	if (!ptr) return;	// ptr�� NULL�̸� break 
	enQueue(ptr);	// ptr�� ��带 ť�� �߰� 
	for (;;) {
		ptr = deQueue();	// ť���� deQueue�� ��带 ptr�� ���� 
		if (ptr) {	// ptr�� �����ϴ� ��� 
			printf(" [%d] ", ptr->key);	// ���� ����� ���� ��� 
			if (ptr->left)	// ptr�� ���� �ڽ��� �ִ� ��� 
				enQueue(ptr->left);	// ���� �ڽ��� enQueue 
			if (ptr->right)	// ptr�� ������ �ڽ��� �ִ°�� 
				enQueue(ptr->right);	// ������ �ڽ��� enQueue 
		}
		else break;	// ptr�� �������� �ʴ� ��� break 
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
	temp = head->left;	// temp�� root��带 ����Ű�� ���� 
	prev = post = p_temp = NULL;

	while (temp) {	// temp�� NULL�� �ƴ� �� ���� �ݺ� 
		if (temp->key == key)	
			break;	// temp�� ����Ű�� ����� ���� �Է� ���� ���� ��� break 
		prev = temp; 
		if (key < temp->key)	// temp�� ����Ű�� ��� ������ �Է� ���� ���� ��� 
			temp = temp->left;	// temp�� ���� �ڽĳ�带 temp�� ���� 
		else	// temp�� ����Ű�� ��� ������ �Է� ���� ū ��� 
			temp = temp->right;	// temp�� ������ �ڽĳ�带 temp�� ���� 
	}

	if (!temp->left && !temp->right) {	// ������ ����� �ڽĳ�尡 ���� ���
		if (prev) {	// ���� ����� ��Ʈ��尡 �ƴѰ��
			if (prev->left == temp) {	// ���� ��尡 �θ����� ���� �ڽ��� ��� 
				prev->left = NULL;
				free(temp);
			}
			else {	// ���� ��尡 �θ����� ������ �ڽ��� ��� 
				prev->right = NULL;
				free(temp);
			}
		}
		else {	// ���� ����� ��Ʈ����� ��� 
			head->left = NULL;
			free(temp);
		}
	}
	else if (!temp->left || !temp->right) {	// ������ ����� �ڽĳ�尡 �ϳ��� ���
		if (prev) {	// ���� ����� ��Ʈ��尡 �ƴѰ��
			if (prev->left == temp) {	// ���� ��尡 �θ����� ���� �ڽ��� ��� 
				if (temp->left)	// ���� ����� ���� �ڽĳ�尡 �����ϴ� ��� 
					prev->left = temp->left;
				else	// ���� ����� ������ �ڽĳ�尡 �����ϴ� ��� 
					prev->left = temp->right;
				free(temp);
			}
			else {	// ���� ��尡 �θ����� ������ �ڽ��� ��� 
				if (temp->left)	// ���� ����� ���� �ڽĳ�尡 �����ϴ� ���
					prev->right = temp->left;
				else	// ���� ����� ������ �ڽĳ�尡 �����ϴ� ��� 
					prev->right = temp->right;
				free(temp);
			}
		}
		else {	// ���� ����� ��Ʈ����� ��� 
			if (temp->left)// ���� ����� ���� �ڽĳ�尡 �����ϴ� ���
				head->left = temp->left;
			else	// ���� ����� ������ �ڽĳ�尡 �����ϴ� ��� 
				head->left = temp->right;
			free(temp);
		}
	}
	else {	// ������ ����� �ڽĳ�尡 �� ���� ���
		post = temp->right;	// ������ ����� ������ �ڽĳ�带 post�� ���� 
		while (post->left) {	// post�� ���� �ڽĳ�尡 ���� �� ���� �ݺ� 
			p_temp = post;	// p_temp�� post�� �θ���� ���� 
			post = post->left;	// post�� ���� �ڽĳ��� ���� 
		}
		temp->key = post->key;	// post�� ���� temp�� �̵� 

		if (p_temp) {	// p_temp�� �����ϴ� ��� 
			if (post->right)	// post�� ���� �ڽĳ�尡 �����ϴ� ��� 
				p_temp->left = post->right;	// post�� �θ��尡 post�� �ڽĳ�带 ����Ű�� ���� 
			else
				p_temp->left = NULL;
			free(post);
		}
		else {	// p_temp�� �������� �ʴ� ��� 
			if (post->right)	// post�� ���� �ڽĳ�尡 �����ϴ� ��� 
				temp->right = post->right;	// temp�� ���� �ڽĳ�带  post�� �ڽĳ�带 ����Ű�� ���� 
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
		free(ptr);	// ���ȣ���� ���� Ʈ�� �Ҵ����� 
	}
}

int freeBST(Node* head) {
	if (head->left == head) {	// root ��尡 �������� �ʴ� ��� 
		free(head);
		return 1;
	}

	Node* p = head->left;
	freeNode(p);
	free(head);
	return 1;
}

Node* pop() {
	if (top == -1)	// ������ ����ִ� ��� 
		return NULL;
	return stack[top--];	// ���� stack[top]�� ��ȯ�ϰ� top-- 
}

void push(Node* aNode) {
	if (top < MAX_STACK_SIZE - 1)	// ������ �� ���� ���� ��� 
		stack[++top] = aNode;	// ��带 ���ÿ� top 
}

Node* deQueue() {
	if (front == rear)	// ť�� ����ִ� ��� 
		return NULL;
	front = (front + 1) % MAX_QUEUE_SIZE;
	return queue[front];	// ���� queue[front]�� ��ȯ 
}

void enQueue(Node* aNode) {
	rear = (rear + 1) % MAX_QUEUE_SIZE;
	if (front != rear)	// ť�� �� ���� ���� ��� 
		queue[rear] = aNode;	// ��带 ť�� enque 
}
