#include<stdio.h>
#include<stdlib.h>

typedef struct Node {
	int key;				// ���� ������ ���� 
	struct Node* llink;		// ���� ��带 ����Ű�� ������ 
	struct Node* rlink;		// ���� ��带 ����Ű�� ������ 
} listNode;

typedef struct Head {
	struct Node* first;		// ���Ḯ��Ʈ�� ù ��带 ����Ű�� ����� 
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
	char command;				// �޴� �Է� �� ���� 
	int key;					// ��忡 ������ �� ���� 
	headNode* headnode=NULL;	// ����� �ʱ�ȭ 

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
			initialize(&headnode);	// ���Ḯ��Ʈ�� �ʱ�ȭ 
			break;
		case 'p': case 'P':
			printList(headnode);	// ���Ḯ��Ʈ ��� 
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insertNode(headnode, key);	// ��忡 ���� ���� �� ����Ʈ�� �߰� 
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(headnode, key);	// �Է¹��� ���� ���� ��� ���� 
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insertLast(headnode, key);	// ��忡 ���� ���� �� ����Ʈ �������� �߰� 
			break;
		case 'e': case 'E':
			deleteLast(headnode);		// ����Ʈ �������� ��� ���� 
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			insertFirst(headnode, key);	// ��忡 ���� ���� �� ����Ʈ ó���� �߰� 
			break;
		case 't': case 'T':
			deleteFirst(headnode);		// ����Ʈ ó���� ��� ���� 
			break;
		case 'r': case 'R':
			invertList(headnode);		// ����Ʈ�� �������� ���� 
			break;
		case 'q': case 'Q':
			freeList(headnode);			// ����Ʈ�� �Ҵ� ���� �� ���α׷� ���� 
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
		freeList(*h);	// h�� ������� �ʴٸ� �Ҵ� ���� 

	headNode* temp = (headNode*)malloc(sizeof(headNode));
	temp->first = NULL;	// ����� temp ���� �� NULL�� �ʱ�ȭ 
	*h = temp;			// h�� temp�� ���� 

	return 1;
}

int freeList(headNode* h) {
	listNode* p = h->first;	// ����Ʈ��� p�� ���� �� ����Ʈ�� ù ��带 ����Ŵ 
	listNode* prev = NULL;	// ���� ��带 ����ų ����Ʈ��� prev ���� �� NULL�� �ʱ�ȭ 

	while (p != NULL) {		// p�� ����Ű�� ��尡 ���� �� ���� �ݺ� 
		prev = p;			// p�� ����Ű�� ��带 prev�� ����Ŵ 
		p = p->rlink;		// p�� ���� ��带 p�� ��ü 
		free(prev);			// prev�� ����Ű�� ��� �Ҵ� ���� 
	}
	free(h);				// h�� ����Ű�� ��� �Ҵ� ���� 

	return 0;
}

void printList(headNode* h) {
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if (h == NULL) {		// h�� ����ִٸ� �����޼��� ��� 
		printf("Nothing to print....\n");
		return;
	}

	p = h->first;			// �����尡 ����Ű�� ��带 p�� ���� 

	while (p != NULL) {
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->rlink;
		i++;
	}

	printf("  items = %d\n", i);
}

int insertLast(headNode* h, int key) {	
	listNode* temp = (listNode*)malloc(sizeof(listNode)); 
	temp->key = key;		// �ӽ� ����Ʈ��� temp ���� �� �Է¹��� ���� temp�� key�� ���� 

	if (h->first) {			// �����尡 ����Ű�� ��尡 �ִ� ��� 
		listNode* current = (listNode*)malloc(sizeof(listNode));
		current = h->first;	// �ӽ� ����Ʈ��� current ���� �� ����Ʈ�� ù ��带 ����Ŵ 

		while (current->rlink != NULL) {	// current�� ����ų ���� ��尡 ���� �� ���� 
			current = current->rlink;		// ���� ��带 current�� ���� 
		}

		temp->rlink = NULL;			// temp�� ����Ű�� ������带 NULL�� ���� 
		temp->llink = current;		// temp�� ����Ű�� ������带 current�� ���� 
		current->rlink = temp;		// current�� ����Ű�� ������带 temp�� ���� 

	}

	else {		// �����尡 ����Ű�� ��尡 ���� ��� 
		temp->rlink = NULL; 
		temp->llink = NULL;			// temp�� ����Ű�� ����, ������带 NULL�� ���� 
		h->first = temp;			// �����尡 ����Ű�� ù ��带 temp�� ���� 
	}

	return 0;
}

int deleteLast(headNode* h) {
	if (h->first) {		// �����尡 ����Ű�� ��尡 �ִ� ��� 
		listNode* temp = (listNode*)malloc(sizeof(listNode));
		listNode* current = (listNode*)malloc(sizeof(listNode));	// �ӽ� ����Ʈ��� temp, current ����
		current = h->first->rlink;	// current�� ����Ű�� ��带 ����Ʈ�� 2��° ���� ���� 
		temp = h->first;			// temp�� ����Ű�� ��带 �������� ù ���� ���� 

		while (current->rlink != NULL) {	// current�� ����Ű�� ��尡 ���� �� ���� temp�� current�� �������� �̵� 
			temp = temp->rlink;	
			current = current->rlink;
		}

		temp->rlink = NULL;	// temp�� ����Ű�� ������带 NULL�� ���� 
		free(current);		// ������ ��带 ����Ű�� current �Ҵ� ���� 
	}

	return 0;
}

int insertFirst(headNode* h, int key) {
	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;	// �ӽ� ����Ʈ��� node ���� �� �Է¹��� ���� node�� key�� ����

	if (h->first) {		// �����尡 ����Ű�� ��尡 �ִ� ��� 
		node->rlink = h->first;	// node�� ����Ű�� ������带 ����Ʈ�� ù ���� ���� 
		node->llink = NULL;		// node�� ����Ű�� ������带 NULL�� ���� 
		h->first->llink = node;	// ����Ʈ�� 2��° ��尡 ����Ű�� ������带 node�� ���� 
		h->first = node;		// ����尡 ����Ű�� ��带 node�� ���� 
	}
	else {	// �����尡 ����Ű�� ��尡 ���� ���
		node->rlink = NULL;		
		node->llink = NULL;		// node�� ����Ű�� ����,������带 NULL�� ����
		h->first = node;		// ����尡 ����Ű�� ��带 node�� ����
	}

	return 0;
}

int deleteFirst(headNode* h) {
	if (h->first) {		// �����尡 ����Ű�� ��尡 �ִ� ��� 
		listNode* temp = (listNode*)malloc(sizeof(listNode));
		temp = h->first;		// �ӽ� ����Ʈ��� temp ���� �� ����Ʈ�� ù ��带 temp�� ���� 
		h->first = temp->rlink;	// ����Ʈ�� 2��° ��带 ����尡 ����Ű�� ���� 
		free(temp);		// temp�� ����Ű�� ��� �Ҵ� ���� 
	}
	return 0;
}

int invertList(headNode* h) {
	listNode* current = (listNode*)malloc(sizeof(listNode));	
	listNode* temp = (listNode*)malloc(sizeof(listNode));		// �ӽ� ����Ʈ��� current, temp ����
	
	current = h->first;	// current�� ����Ʈ�� ù ��带 ����Ű�� ���� 
	temp = NULL;		// temp�� NULL�� �ʱ�ȭ 
	
	while (current != NULL){				// current�� ����Ű�� ��尡 ���� �� ���� �ݺ� 
        temp = current->llink;				// temp�� current�� ������带 ����Ű�� ���� 
        current->llink = current->rlink;	// current�� ������带 current�� �������� ���� 
        current->rlink = temp;				// temp�� current�� �������� ����             
        current = current->llink;			// current�� ������带 current�� ���� 
    }
    
    h->first = temp->llink;		// temp�� ������带 �����尡 ����Ű�� ���� 
    
	return 0;
}

int insertNode(headNode* h, int key) {
	listNode* temp = (listNode*)malloc(sizeof(listNode));
	temp->key = key;	// �ӽ� ����Ʈ��� temp ���� �� �Է¹��� ���� temp�� key�� ���� 

	if (h->first) {		// �����尡 ����Ű�� ��尡 �ִ� ��� 
		listNode* current = (listNode*)malloc(sizeof(listNode));
		current = h->first;	// �ӽ� ����Ʈ��� current ���� �� ����Ʈ�� ù ��带 ����Ű�� ���� 

		if (temp->key <= h->first->key) {	// temp�� key�� ����Ʈ�� ù ����� ������ �۰ų� ���� ���
			temp->rlink = h->first;			// temp�� ������带 ����Ʈ�� ù ���� ���� 
			temp->llink = NULL;				// temp�� ������带 NULL�� ���� 
			h->first->llink = temp;			// ����Ʈ�� 2��° ����� ������带 temp�� ���� 
			h->first = temp;				// ����尡 temp�� ����Ű�� ���� 
		}

		else {
			while (current->rlink != NULL) {	// current�� ������尡 ���� �� ���� ���� 
				if (temp->key < current->rlink->key) {	// temp�� key�� ��������� ������ ���� ��� 
					temp->rlink = current->rlink;		// temp�� ������带 current�� �������� ���� 
					temp->llink = current;				// temp�� ������带 current�� ���� 
					current->rlink->llink = temp;		// current�� ��������� ������带 temp�� ���� 
					current->rlink = temp;				// current�� ������带 temp�� ���� 
					break;
				}
				current = current->rlink;		// current�� �������� �̵� 
			}

			if (current->rlink == NULL) {		// current�� ����Ű�� ��尡 ���� ��� 
				temp->rlink = NULL;				// temp�� ������带 NULL�� ���� 
				temp->llink = current;			// temp�� ������带 current�� ���� 
				current->rlink = temp;			// current�� ������带 temp�� ���� 
			}
		}
	}

	else {	// �����尡 ����Ű�� ��尡 ���� ���
		temp->rlink = NULL; 
		temp->llink = NULL;	// temp�� ����,������带 NULL�� ����
		h->first = temp;	// ����尡 temp�� ����Ű�� ���� 
	}
	return 0;
}

int deleteNode(headNode* h, int key) {
	if (h->first) {		// �����尡 ����Ű�� ��尡 �ִ� ��� 
		listNode* temp = (listNode*)malloc(sizeof(listNode));	// �ӽ� ����Ʈ��� temp ���� 

		if (key == h->first->key) {		// �Է¹��� ���� ����Ʈ�� ù ��� ���� ���� ��� 
			temp = h->first;			// temp�� ����Ʈ�� ù ��带 ����Ŵ 
			h->first = temp->rlink;		// ����尡 temp�� ������带 ����Ű�� ���� 
			temp->rlink = NULL;			// temp�� ������带 NULL�� ���� 
			free(temp);					// temp�� ����Ű�� ��� �Ҵ� ���� 
		}

		else {
			listNode* current = (listNode*)malloc(sizeof(listNode));
			current = h->first->rlink;	// �ӽ� ����Ʈ��� current ���� �� ����Ʈ�� 2��° ��带 ����Ű�� ���� 
			temp = h->first;			// temp�� ����Ʈ�� ù ��带 ����Ű�� ���� 

			while (current->key != key) {	// current�� key���� �Էµ� ���� ���� �� ���� �ݺ�
				temp = temp->rlink;
				current = current->rlink;	// temp�� current�� �������� �̵� 
			}

			if (current->rlink) {			// current�� ������尡 �����ϴ� ��� 
				temp->rlink = current->rlink;	// temp�� ������带 current�� �������� ���� 
				current->rlink->llink = temp;	// current�� ��������� ������带 temp�� ���� 
				free(current);					// current�� ����Ű�� ��� �Ҵ� ���� 
			}

			else {	// current�� ����Ű�� ��尡 �������� �ʴ� ��� 
				temp->rlink = NULL;	// temp�� ������带 NULL�� ���� 
				free(current);		// current�� ����Ű�� ��� �Ҵ� ���� 
			}
		}
	}

	return 1;
}
