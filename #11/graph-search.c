#include <stdio.h>
#include <stdlib.h>
#define MAX_VERTEX 10

typedef struct Node {
	int vertex;	// ������ ��ȣ
	struct Node *link;	// ���� ��带 ����ų ������
}Node;	// ������ ǥ���� ��� ����ü

typedef struct Graph {
	int vertexNum;	// ������ ���� ��Ÿ���� ����
	Node *adjLists[MAX_VERTEX];	// ��������Ʈ�� ǥ���� �迭
}Graph; 

short int visited[MAX_VERTEX] = { 0 };	// �湮������ ����� �迭

typedef struct QueueNode {
	int vertex;	// ť�� ���� ������ ����
	struct QueueNode *link;	// ���� ť�� ����ų ������
}QueueNode;
QueueNode *front, *rear;
void addq(int);	// ť�� ���� �߰��ϴ� �Լ�
int deleteq();	// ť�� ���� �����ϴ� �Լ�

void initializeGraph(Graph *);	// �׷����� �ʱ�ȭ�ϴ� �Լ�
void insertVertex(Graph *);	// ������ �߰��ϴ� �Լ�
void insertEdge(Graph *, int, int);	// ������ �߰��ϴ� �Լ�
void dfs(Graph *, int);	// ���̿켱Ž������ �׷����� ����ϴ� �Լ�
void bfs(Graph *, int);	// �ʺ�켱Ž������ �׷����� ����ϴ� �Լ�
void printGraph(Graph *);	// �׷����� ��������Ʈ�� ����ϴ� �Լ�
void freeGraph(Graph *);	// �׷����� �Ҵ������ϴ� �Լ�
void initVisited();	// �湮���θ� üũ�ϴ� visited �迭�� �ʱ�ȭ�ϴ� �Լ�

int main()
{
	char command;
	int key = 0, v1 = 0, v2 = 0;
	Graph *graph = (Graph *)malloc(sizeof(Graph));	// �׷����� ǥ���ϴ� graph ����

	printf("[----- [Jegal Dohyun] [2018038018] -----]");

	do {
		printf("\n\n");
		printf("----------------------------------------------------------------\n");
		printf("                       Graph Searches                           \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize Graph     = z                                       \n");
		printf(" Insert Vertex        = v      Insert Edge                  = e \n");
		printf(" Depth First Search   = d      Breath First Search          = b \n");
		printf(" Print Graph          = p      Quit                         = q \n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch (command) {
		case 'z': case 'Z':
			initializeGraph(graph);	// �׷��� �ʱ�ȭ
			printf("\n > Graph Initialized. \n");
			break;
		case 'q': case 'Q':
			freeGraph(graph);	// �׷����� ���� ���� �Ҵ�����
			free(graph);	// graph �Ҵ�����
			break;
		case 'v': case 'V':
			insertVertex(graph);	// ���� �߰�
			break;
		case 'e': case 'E':
			printf("\n > Type two vertices number (v1 v2) : ");
			scanf("%d %d", &v1, &v2);
			insertEdge(graph, v1, v2);	// �� ���� ������ ���� �߰�
			insertEdge(graph, v2, v1);	// ������ �׷����� ǥ���ϱ� ���� �ѹ� �� �߰�
			break;
		case 'd': case 'D':
			printf("\n > Depth First Search \n");
			dfs(graph, 0);	// ���̿켱Ž��
			initVisited();	// visited[] �ʱ�ȭ
			break;
		case 'b': case 'B':
			printf("\n > Breath First Search \n");
			bfs(graph, 0);	// �ʺ�켱Ž��
			initVisited();	// visited[] �ʱ�ȭ
			break;
		case 'p': case 'P':
			printf("\n > Print Graph \n");
			printGraph(graph);	// �׷����� ��������Ʈ ���
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	} while (command != 'q' && command != 'Q');	// q �Է��� ���� �ݺ� 

	return 1;
}

void initializeGraph(Graph * g) {
	int i;

	g->vertexNum = 0;	// ������ ���� 0���� ����
	for (i = 0; i < MAX_VERTEX; i++)
		g->adjLists[i] = NULL;	// adjLists�� ����Ű�� ������ NULL�� ����
}

void insertVertex(Graph * g) {
	if ((g->vertexNum + 1) > MAX_VERTEX)	// ������ �߰����� �� �ִ� ������ ���� �ʰ��ϴ� ���
		printf("\n > Maximum number of vertex has reached.");	// �����޼��� ���
	else {
		printf("\n > Vertex[%d] Inserted. \n", g->vertexNum);
		g->vertexNum++;	// ������ �� �߰�
	}
}

void insertEdge(Graph * g, int v1, int v2) {
	Node *node, *temp, *prev;
	int error = 0;

	temp = g->adjLists[v1];	// temp�� adjLists[v1]�� ����Ű�� ���� ����
	while (temp) {	// temp�� ������ �� ���� �ݺ�
		if (temp->vertex == v2) {	// temp�� ���� �ѹ��� v2�� ���� ���
			error = 1;
			break;	// error�� 1�� ���� �� while�� break
		}
		temp = temp->link;	// temp�� temp�� �������� ����
	}

	if (!error) {	// error�� 0�� ���
		if (v1 >= g->vertexNum || v2 >= g->vertexNum) {	// v1�̳� v2�� ���� ������ ������ ū ���
			printf("\n Vertex number is not correct.");	// �����޼��� ���
		}
		else {
			node = (Node *)malloc(sizeof(Node)); 
			node->vertex = v2;	// node�� ���� �ѹ��� v2�� ����

			if (!g->adjLists[v1]) {	// adjLists[v1]�� ����Ű�� ��尡 ���� ���
				node->link = NULL;	// node�� ���� ��带 NULL�� ����
				g->adjLists[v1] = node;	// adjLists[v1]�� node�� ����Ű�� ����
			}
			else {	// adjLists[v1]�� ����Ű�� ��尡 �ִ� ���
				if (v2 < g->adjLists[v1]->vertex) {	// v2�� adjLists[v1]�� ����Ű�� ����� ���� �ѹ����� ���� ���
					node->link = g->adjLists[v1];	// adjLists[v1]�� ����Ű�� ��带 node�� ����Ű�� ����
					g->adjLists[v1] = node;	// adjLists[v1]�� node�� ����Ű�� ����
				}
				else {	// v2�� adjLists[v1]�� ����Ű�� ����� ���� �ѹ����� ū ���
					temp = g->adjLists[v1];	// temp�� adjLists[v1]�� ����Ű�� ��带 ����Ű�� ����
					prev = temp;	// prev�� temp�� ����Ű�� ����

					while (v2 > temp->vertex) {	// v2�� temp�� ����� ���� ��庸�� Ŭ �� ���� �ݺ�
						prev = temp;	// temp�� prev�� ����Ű�� ����
						temp = temp->link;	// temp�� ���� ���� ����
						if (!temp)
							break;	// temp�� NULL�� ��� break
					}

					if (!temp) {	// temp�� ����ִ� ���
						node->link = NULL;	// node�� ���� ��带 NULL�� ����
						prev->link = node;	// prev�� ���� ��带 node�� ����
					}
					else {	// temp�� ������� ���� ���
						node->link = temp;	// node�� ���� ��带 temp�� ����
						prev->link = node;	// prev�� ���� ��带 node�� ����
					}
				}
			}
			printf("\n (%d > %d) Edge Inserted.", v1, v2);
		}
	}
	else	// error�� 0�� ��� �����޼��� ���
		printf("\n (%d > %d) Edge already exists. ", v1, v2);
}

void dfs(Graph *g, int v) {
	Node *w;
	visited[v] = 1;	// �湮��� �߰�
	printf("%5d", v);
	for (w = g->adjLists[v]; w; w = w->link)	// w�� adjLists[v]�� ����Ű�� ���� �� for�� �ݺ� �� ���� ���� �̵�
		if (!visited[w->vertex])	// ���� ���� �湮 ����� ���� ���
			dfs(g, w->vertex);	// ���ȣ��
}

void bfs(Graph *g, int v) {
	Node *w;
	front = rear = NULL;	// front�� rear�� NULL�� �ʱ�ȭ
	printf("%5d", v);
	visited[v] = 1;	// �湮��� �߰�
	addq(v);	// ���� �ѹ� v�� ť�� �߰�
	while (front) {	// front�� NULL�� �� �� ���� �ݺ�
		v = deleteq();	// ť���� ������ ���� v�� ����
		for (w = g->adjLists[v]; w; w = w->link)	// w�� adjLists[v]�� ����Ű�� ���� �� for�� �ݺ� �� ���� ���� �̵�
			if (!visited[w->vertex]) {	// ���� ���� �湮 ����� ���� ���
				printf("%5d", w->vertex);
				addq(w->vertex);	// ���� ���� ť�� �߰�
				visited[w->vertex] = 1;	// ���� ��� �湮��� �߰�
			}
	}
}

void printGraph(Graph *g) {
	Node *temp;
	int i;

	for (i = 0; i < g->vertexNum; i++) {
		temp = g->adjLists[i];
		printf("\n adjLists[%d] ", i);
		while (temp) {
			printf("\t %d", temp->vertex);	// ����� ��� ����Ʈ�� ���
			temp = temp->link;
		}
	}
}

void freeGraph(Graph *g) {
	Node *temp, *prev;
	int i;

	for (i = 0; i < MAX_VERTEX; i++) {
		temp = g->adjLists[i];
		while (temp) {
			prev = temp;
			temp = temp->link;
			free(prev);	// adjLists[i]�� ����� ������ �Ҵ�����
		}
		g->adjLists[i] = NULL;	// adjLists[i]���� NULL�� ����
	}
}

void addq(int i) {
	QueueNode *temp = (QueueNode *)malloc(sizeof(QueueNode));

	if (temp) {
		temp->vertex = i;	// ť�� ������ ���� ����
		temp->link = NULL;	// ť�� ������ NULL�� ����
		if (!front) {	// front�� NULL�� ���
			front = temp;
			rear = temp;	// front�� rear�� temp�� ����
		}
		else {	// front�� ���� �ִ� ���
			rear->link = temp;	// rear�� temp�� ����Ű�� ����
			rear = temp;
		}
	}
}

int deleteq() {
	QueueNode *temp = front;
	int item;
	if (front) {	// front�� ���� �ִ� ���
		item = temp->vertex;	// item�� temp�� ������ �ִ� �� ����
		front = front->link;	// front �̵�
		if (!front)	// front�� NULL�� ���
			rear = NULL;	// rear�� NULL�� ����
		free(temp);	// temp �Ҵ�����
		return item;
	}
}

void initVisited() {
	int i;

	for (i = 0; i < MAX_VERTEX; i++)
		visited[i] = 0;	// �湮����� ��� �ʱ�ȭ
}
