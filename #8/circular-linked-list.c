#include<stdio.h>
#include<stdlib.h>

typedef struct Node {
	int key;	// ����� ���� ������ ���� 
	struct Node* llink;	// ������带 ����Ű�� ������ 
	struct Node* rlink;	// ������带 ����Ű�� ������ 
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
	char command;	// �޴� ���� ���� �����ϴ� ���� 
	int key;	// ��忡 ������ ���� �����ϴ� ���� 
	listNode* headnode=NULL;	// ����� �ʱ�ȭ 
	
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
			initialize(&headnode);	// ����Ʈ�� �ʱ�ȭ �� �Ҵ� 
			break;
		case 'p': case 'P':
			printList(headnode);	// ����Ʈ�� ��� �ּҿ� ���� �� ��� 
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insertNode(headnode, key);	// �Է¹��� ���� ��忡 ���� �� ����Ʈ�� �߰� 
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(headnode, key);	// �Է¹��� ���� ���� ��带 ����Ʈ���� ���� 
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insertLast(headnode, key);	// ����Ʈ�� �������� �Է¹��� ���� ������ ��� �߰� 
			break;
		case 'e': case 'E':
			deleteLast(headnode);	// ����Ʈ�� �������� ��带 ���� 
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			insertFirst(headnode, key);	// ����Ʈ�� ó���� �Է¹��� ���� ������ ��� �߰�
			break;
		case 't': case 'T':
			deleteFirst(headnode);	// ����Ʈ�� ó���� ��带 ���� 
			break;
		case 'r': case 'R':
			invertList(headnode);	// ����Ʈ�� �������� ���� 
			break;
		case 'q': case 'Q':
			freeList(headnode);	// ����Ʈ ��ü �Ҵ� ���� 
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');	// q�� �Է¹����� ���α׷� ���� 

	return 1;
}


int initialize(listNode** h) {
	if(*h != NULL)	// h�� ������� �ʴٸ� ����Ʈ �Ҵ� ���� 
		freeList(*h);

	*h = (listNode*)malloc(sizeof(listNode));
	(*h)->rlink = *h;
	(*h)->llink = *h;
	(*h)->key = -9999;	// ����, ������尡 ��� �ڽ��� ����Ű�� ������ ���� 
	return 1;
}

int freeList(listNode* h) {
	listNode* p = h->rlink;	// ����Ʈ�� ù ��� �ּҸ� �޴� ����Ʈ��� p �Ҵ�
	listNode* prev = NULL; // ������带 ����ų ����Ʈ��� prev �Ҵ�

	while (p->rlink != h){	// p�� ����Ű�� ��尡 ������� �� ���� �ݺ�
		prev = p;	// p�� ����Ű�� ��带 prev�� ����Ŵ 
		p = p->rlink;	// p�� �������� �̵�
		free(prev);	// prev�� ����Ű�� ��� �Ҵ� ���� 
	}
	free(p);	// p �Ҵ� ���� 

	return 0;
}

void printList(listNode* h) {
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if(h == NULL) {	// ����Ʈ�� ����ִٸ� �����޼��� ��� 
		printf("Nothing to print....\n");
		return;
	}

	p = h->rlink;	// ����Ʈ��� p�� ����Ʈ�� ù ��带 ����Ŵ 

	while(p != NULL && p != h) {	// p�� �����峪 �� ��带 ����ų �� ���� �ݺ� 
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->rlink;	// p�� �������� �̵� 
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
	temp->key = key;	// �ӽ� ����Ʈ��� temp ���� �� �Է¹��� ���� temp�� key�� ����

	if (h) {	// �����尡 �����ϴ� ��� 
		listNode* current = (listNode*)malloc(sizeof(listNode));
		current = h;	// �ӽ� ����Ʈ��� current ���� �� �����带 ����Ŵ 

		while (current->rlink != h) {	// current�� ������尡 �������� �� ���� �ݺ� 
			current = current->rlink;	// current�� �������� �̵� 
		}

		temp->rlink = h;	// temp�� ������带 ������� ���� 
		temp->llink = current;	// temp�� ������带 current�� ���� 
		current->rlink = temp;	// current�� ������带 temp�� ���� 
		h->llink = temp;	// �������� ������带 temp�� ���� 
	}

	else {	// �����尡 �������� �ʴ� ��� 
		temp->rlink = temp;
		temp->llink = temp;
		h = temp;	// ����, ������尡 �ڽ��� ����Ű�� ������ ����
	}
	
	return 1;
}

int deleteLast(listNode* h) {
	if (h) {	// �����尡 �����ϴ� ���	
		listNode* temp = (listNode*)malloc(sizeof(listNode));
		listNode* current = (listNode*)malloc(sizeof(listNode));
		current = h->rlink;	// ����Ʈ�� ù ��带 ����Ű�� ����Ʈ��� current �Ҵ� 
		temp = h;	// �����带 ����Ű�� ����Ʈ��� temp �Ҵ� 

		while (current->rlink != h) {	// current�� ������尡 �������� �� ���� �ݺ� 
			temp = temp->rlink;	
			current = current->rlink;	// temp�� current�� ���� �������� �̵� 
		}

		temp->rlink = h;	// temp�� ������带 ������� ���� 
		h->llink = temp;	// �������� ������带 temp�� ���� 
		current->llink = current; 
		current->rlink = current;
		free(current);	// current�� ����, ������带 �ڽ����� ���� �� �Ҵ� ���� 
	}

	return 1;
}

int insertFirst(listNode* h, int key) {
	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;

	if (h) {	// �����尡 �����ϴ� ���
		node->rlink = h->rlink;	// node�� ������ũ�� ����Ʈ�� ù ���� ���� 
		node->llink = h;	// node�� ������ũ�� ������� ���� 
		h->rlink->llink = node;	// ����Ʈ�� ù ����� ������带 node�� ���� 
		h->rlink = node;	// �������� ������带 node�� ���� 
	}
	else {	// �����尡 �������� �ʴ� ���
		node->rlink = node;		
		node->llink = node;	
		h = node;	// ����, ������尡 �ڽ��� ����Ű�� ������ ����
	}

	return 1;
}

int deleteFirst(listNode* h) {
	if (h) {	// �����尡 �����ϴ� ���
		listNode* temp = (listNode*)malloc(sizeof(listNode));
		temp = h->rlink;	// ����Ʈ�� ù ��带 ����Ű�� ����Ʈ��� temp �Ҵ� 
		
		temp->rlink->llink = h;	// ����Ʈ�� �ι� ° ����� ������带 ������� ���� 
		h->rlink = temp->rlink;	// �������� ������带 ����Ʈ�� �ι� ° ���� ���� 
		temp->llink = temp;
		temp->rlink = temp;
		free(temp);	// temp�� ����, ������带 �ڽ����� ���� �� �Ҵ� ����
	}
	
	return 1;

}

int invertList(listNode* h) {
	listNode* post = (listNode*)malloc(sizeof(listNode));
	listNode* current = (listNode*)malloc(sizeof(listNode));
    current = h;	// �����带 ����Ű�� ����Ʈ��� h�� h�� ������带 ����ų post �Ҵ� 
    
    while(post != h){	// post�� �����带 ����ų �� ���� �ݺ� 
    	post = current->rlink;	// post�� current�� ������带 ����Ű�� ���� 
        current->rlink = current->llink;	// current�� ������带 �ݴ������ �������� ���� 
        current->llink = post;	// current�� ������带 �ݴ������ post�� ���� 
        current = post;	// post�� ����Ű�� ���� current �̵� 
	}
    
	return 0;
}

int insertNode(listNode* h, int key) {
	listNode* temp = (listNode*)malloc(sizeof(listNode));
	temp->key = key;	// ����Ʈ��� temp �Ҵ� �� �Է¹��� ���� ���� 

	if (h) {	// �����尡 �����ϴ� ���	
		listNode* current = (listNode*)malloc(sizeof(listNode));
		current = h;	// �����带 ����ų ����Ʈ��� current �Ҵ� 

		if (temp->key <= h->key) {	// temp�� key�� ����Ʈ�� ù ����� ������ �۰ų� ���� ���	
			temp->rlink = h->rlink;	// temp�� ������带 ����Ʈ�� ù ���� ���� 
			temp->llink = h;	// temp�� ������带 ������� ���� 
			h->rlink->llink = temp;	// ����Ʈ�� ù ����� ������带 temp�� ���� 
			h->rlink = temp;	// �������� ������带 temp�� ���� 
		}

		else {	// temp�� key�� ����Ʈ�� ù ����� ���� �ٸ� ��� 
			while (current->rlink != h) {	// current�� ������尡 �������� �� ���� �ݺ� 
				if (temp->key < current->rlink->key) {	// temp�� key�� ��������� ������ ���� ���  
					temp->rlink = current->rlink;	// temp�� ������带 current�� �������� ���� 
					temp->llink = current;	// temp�� ������带 current�� ���� 
					current->rlink->llink = temp;	// current�� ��������� ������带 temp�� ����
					current->rlink = temp;	// current�� ������带 temp�� ����
					break;
				}
				current = current->rlink;	// current�� �������� �̵� 
			}

			if (current->rlink == h) {	// current�� ����Ű�� ��� �������� ��� 
				temp->rlink = h;	// temp�� ������带 ������� ���� 
				temp->llink = current;	// temp�� ������带 current�� ���� 
				current->rlink = temp;	// current�� ������带 temp�� ���� 
				h->llink = temp;	// �������� ������带 temp�� ���� 
			}
		}
	}

	else {	// �����尡 �������� �ʴ� ���
		temp->rlink = temp;		
		temp->llink = temp;	
		h = temp;	// ����, ������尡 �ڽ��� ����Ű�� ������ ����
	}

	return 0;
}

int deleteNode(listNode* h, int key) {
	if (h) {	// �����尡 �����ϴ� ���	
		listNode* temp = (listNode*)malloc(sizeof(listNode));	// ����Ʈ��� temp �Ҵ� 
		
		if (key == h->key) {	// �Է¹��� ���� ����Ʈ�� ù ��� ���� ���� ���
			temp = h->rlink;	// temp�� ����Ʈ�� ù ��带 ����Ű�� ���� 
			
			temp->rlink->llink = h;	// ����Ʈ�� �ι� ° ����� ������带 ������� ���� 
			h->rlink = temp->rlink;	// �������� ������带 ����Ʈ�� �ι� ° ���� ���� 
			temp->llink = temp;
			temp->rlink = temp;
			free(temp);	// temp�� ����, ������带 �ڽ����� ���� �� �Ҵ� ����
		}

		else {	// �Է¹��� ���� ����Ʈ�� ù ��� ���� �ٸ� ��� 
			listNode* current = (listNode*)malloc(sizeof(listNode));
			current = h->rlink;	// ����Ʈ����� ù ��带 ����Ű�� ����Ʈ��� currnet �Ҵ� 
			temp = h;	// temp�� �����带 ����Ű�� ���� 

			while (current->key != key) {	// current�� key���� �Էµ� ���� ���� �� ���� �ݺ�
				temp = temp->rlink;
				current = current->rlink;	// temp�� current�� ���� �������� �̵�
			}

			if (current->rlink) {	// current�� ������尡 �����ϴ� ���
				current->rlink->llink = temp;	// current ��������� ������带 temp�� ���� 
				temp->rlink = current->rlink;	// temp�� ������带 current�� �������� ���� 
				current->llink = current;
				current->rlink = current;
				free(current);	// current�� ����, ������带 �ڽ����� ���� �� �Ҵ� ����
			}

			else {	// current�� ������尡 �������� �ʴ� ���
				temp->rlink = h;	// temp�� ������带 ������� ���� 
				h->llink = temp;	// �������� ������带 temp�� ���� 
				current->llink = current;
				current->rlink = current;
				free(current);	// current�� ����, ������带 �ڽ����� ���� �� �Ҵ� ����
			}
		}
	}

	return 0;
}
