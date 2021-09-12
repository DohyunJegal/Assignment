#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int key;	// ��忡 ������ �� 
	struct node *left;	// ����� ���� �ڽĳ�带 ����Ű�� ������ 
	struct node *right;	// ����� ������ �ڽĳ�带 ����Ű�� ������
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

Node* modifiedSearch(Node* head, int key);	// ��� ���Խ� ���� �� ��ġ�� �θ��带 �����ϴ� �Լ� 
Node* deleteSearch(Node* head, int key);	// ������ ������带 �˻��ϴ� �Լ� 
void freeHeadleft(Node* ptr);	// ����带 ������ Ʈ���� �����ϴ� �Լ� 

int main()
{
	char command;
	int key;
	Node* head = NULL;	// ����带 ����ų ������ 
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
			initializeBST(&head);	// Ʈ�� ��ü�� �ʱ�ȭ �� ����� ���Ҵ� 
			break;
		case 'q': case 'Q':
			freeBST(head);	// Ʈ�� ��ü�� �Ҵ� ���� 
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insert(head, key);	// �Է¹��� ���� ���� ��带 Ʈ���� �߰� 
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteLeafNode(head, key);	// �Է¹��� ���� ���� ������� ���� 
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			ptr = searchIterative(head, key);	// �Է¹��� ���� ���� ��带 �ݺ������� �˻� 
			if(ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else
				printf("\n Cannot find the node [%d]\n", key);
			break;
		case 's': case 'S':
			printf("Your Key = ");
			scanf("%d", &key);
			ptr = searchRecursive(head->left, key);	// �Է¹��� ���� ���� ��带 ��ͱ����� �˻� 
			if(ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else
				printf("\n Cannot find the node [%d]\n", key);
			break;

		case 'i': case 'I':
			inorderTraversal(head->left);	// ������ȸ ������� Ʈ�� ��� 
			break;
		case 'p': case 'P':
			preorderTraversal(head->left);	// ������ȸ ������� Ʈ�� ��� 
			break;
		case 't': case 'T':
			postorderTraversal(head->left);	// ������ȸ ������� Ʈ�� ��� 
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
	if (ptr){	// Ʈ���� �����ϴ� ���
		inorderTraversal(ptr->left);	// ���� �ڽĳ��� ���ȣ��
		printf("%d ", ptr->key);	// ���� ����� ���� ���
		inorderTraversal(ptr->right);	// ������ �ڽĳ��� ���ȣ��
	}
}

void preorderTraversal(Node* ptr) {
	if (ptr){	// Ʈ���� �����ϴ� ���
		printf("%d ", ptr->key);	// ���� ����� ���� ���
		preorderTraversal(ptr->left);	// ���� �ڽĳ��� ���ȣ��
		preorderTraversal(ptr->right);	// ������ �ڽĳ��� ���ȣ��
	}
}

void postorderTraversal(Node* ptr) {
	if (ptr){	// Ʈ���� �����ϴ� ���
		preorderTraversal(ptr->left);	// ���� �ڽĳ��� ���ȣ��
		preorderTraversal(ptr->right);	// ������ �ڽĳ��� ���ȣ��
		printf("%d ", ptr->key);	// ���� ����� ���� ���
	}

}

int insert(Node* head, int key) {
	Node *ptr = (Node*)malloc(sizeof(Node));
	Node *temp = (Node*)malloc(sizeof(Node));
	temp = modifiedSearch(head, key);	// ��带 ������ ��ġ�� �θ��� �ּҸ� temp�� ���� 

	if(temp || head) {	// temp�� head�� ������� �ʴ� ��� 
		ptr->key = key;	 
		ptr->left = NULL;
		ptr->right = NULL; // �Է¹��� ���� ptr�� ���� �� �������� ����

		if (!head->left)	// Ʈ���� ����ִ� ��� 
			head->left = ptr;	// ptr�� Ʈ���� root�� ���� 
		else if (key < temp->key)	// temp�� ���� �Է¹��� ������ ū ��� 
			temp->left = ptr;	// ptr�� temp�� ���� �ڽĳ��� ���� 
		else	// �Է¹��� ���� temp�� ������ ū ���  
			temp->right = ptr;	// ptr�� temp�� ������ �ڽĳ��� ���� 
	}
	return 0;
}

int deleteLeafNode(Node* head, int key) {
	Node *temp = (Node*)malloc(sizeof(Node));
	Node *prev = (Node*)malloc(sizeof(Node));
	temp = deleteSearch(head, key);	// ������ ���� ������ �ִ� ����� �ּҸ� temp�� ���� 
	prev = head->left;	// Ʈ���� root �ּҸ� prev�� ���� 

	if (temp) {	// �������� ���� ������尡 �����ϴ� ��� 
		while (prev) {	// prev�� NULL�� �� ���� �ݺ� 
			if (prev->left == temp || prev->right == temp)	// prev�� �ڽĳ�尡 temp�� ��� 
				break;
			if (key < prev->key)	// prev�� ���� �Է°����� ���� ��� 
				prev = prev->left;	// prev�� ���� �ڽĳ��� �̵� 
			else	// prev�� ���� �Է°����� ū ��� 
				prev = prev->right;	// prev�� ������ �ڽĳ��� �̵� 
		}

		if (prev == NULL) {	// ��Ʈ��带 �����ϴ� ���
			free(temp);	// temp �Ҵ� ���� 
			head->left = NULL;	// ������� ���� �ڽĳ�带 NULL�� ���� 
		}
		else if (prev->left == temp) {	// �θ����� ���� �ڽĳ�尡 ���� ����� ���
			prev->left = NULL;	// �θ����� ���� �ڽĳ�带 NULL�� ���� 
			free(temp);	// temp �Ҵ� ���� 
		}
		else if (prev->right == temp) {	// �θ����� ������ �ڽĳ�尡 ���� ����� ���
			prev->right = NULL;	// �θ����� ������ �ڽĳ�带 NULL�� ���� 
			free(temp);	// temp �Ҵ� ���� 
		}
	}
	else	// �������� ���� ������尡 ���ٸ� �����޼��� ��� 
		printf("������忡 �ش� ���� �������� �ʽ��ϴ�. \n");

	return 0;
}

Node* searchRecursive(Node* ptr, int key) {
	if (!ptr)	// Ʈ���� ����ִ� ���, ã�� ���� ���� ��� NULL ��ȯ  
		return NULL;
	if (ptr->key == key)	// �Է°��� �ش� ����� ���� ���� ��� ��� �ּ� ��ȯ 
		return ptr;
	if (key < ptr->key)	// �Է°��� �������� ������ ������� 
		return searchRecursive(ptr->left, key);	// ���� �ڽĳ���� �ּҷ� ���ȣ�� 
	return searchRecursive(ptr->right, key);	// �Է°��� �������� ������ ������� ������ �ڽĳ���� �ּҷ� ���ȣ�� 
}

Node* searchIterative(Node* head, int key) {
	Node *temp = (Node*)malloc(sizeof(Node));
	temp = head->left;	// Ʈ���� root �ּҸ� temp�� ���� 

	while (temp) {	// temp�� NULL�� �� ���� �ݺ� 
		if (temp->key == key)	// �Է°��� �������� ���� ���� ��� 
			return temp;	// �������� �ּ� ��ȯ 
		if (key < temp->key)	// �Է°��� �������� ������ ���� ��� 
			temp = temp->left;	// temp�� �������� ���� �ڽĳ��� ���� 
		else	// �Է°��� �������� ������ ū ���
			temp = temp->right;	// temp�� �������� ������ �ڽĳ��� ���� 
	}
	return NULL;
}

int freeBST(Node* head) {
	if (head) {	// ����尡 ������� �ʴ� ��� 
		freeHeadleft(head->left);	// Ʈ���� root���� ��ü�� �����ϴ� �Լ� ȣ�� 
		free(head);	// ����� �Ҵ� ���� 
	}
	return 0;
}

Node* modifiedSearch(Node* head, int key) {
	Node *temp = (Node*)malloc(sizeof(Node));
	Node *prev = (Node*)malloc(sizeof(Node));
	temp = head->left;	// Ʈ���� root �ּҸ� temp�� ���� 

	if (!temp)	// temp�� NULL�� ��� NULL ��ȯ 
		return NULL;

	while (temp) {	// temp�� NULL�� �� ���� �ݺ� 
		prev = temp;	// ���� ����� �θ��� ǥ���� ���� prev �Ҵ�  

		if (temp->key == key)	// �߰��� ���� ���� ��尡 �̹� �����ϴ� ��� NULL ��ȯ 
			return NULL;
		if (key < temp->key)	// �Է°��� �������� ������ ���� ���  
			temp = temp->left;	// temp�� �������� ���� �ڽĳ��� ���� 
		else	// �Է°��� �������� ������ ū ���
			temp = temp->right;	// temp�� �������� ������ �ڽĳ��� ���� 
	}
	return prev;	// ���� ����� �θ��� �ּ� ��ȯ 
}

Node* deleteSearch(Node* head, int key) {
	Node *temp = (Node*)malloc(sizeof(Node));
	temp = head->left;	// Ʈ���� root �ּҸ� temp�� ���� 

	while (temp) {	// temp�� NULL�� �� ���� �ݺ�
		if (temp->key == key) {	// temp�� ���� �Է°��� ���� ��� 
			if (temp->left == NULL && temp->right == NULL)	// ��尡 ��������� ��� temp�� �ּ� ��ȯ 
				return temp; 
			else	// ��尡 ����尡 �ƴ� ��� NULL ��ȯ 
				return NULL;
		}

		if (key < temp->key)	// �Է°��� �������� ������ ���� ���  
			temp = temp->left;	// temp�� �������� ���� �ڽĳ��� ���� 
		else	// �Է°��� �������� ������ ū ���
			temp = temp->right;	// temp�� �������� ������ �ڽĳ��� ���� 
	}
	return NULL; 
}

void freeHeadleft(Node* ptr) {
	if (ptr) {	// ptr�� NULL�� �ƴ� ��� 
		freeHeadleft(ptr->left);	// ���� �ڽĳ���� �ּҷ� ���ȣ�� 
		freeHeadleft(ptr->right);	// ������ �ڽĳ���� �ּҷ� ���ȣ�� 
		free(ptr);	// ptr �Ҵ� ���� 
	}
}
