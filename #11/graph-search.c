#include <stdio.h>
#include <stdlib.h>
#define MAX_VERTEX 10

typedef struct Node {
	int vertex;	// 정점의 번호
	struct Node *link;	// 다음 노드를 가리킬 포인터
}Node;	// 정점을 표현할 노드 구조체

typedef struct Graph {
	int vertexNum;	// 정점의 수를 나타내는 변수
	Node *adjLists[MAX_VERTEX];	// 인접리스트를 표현할 배열
}Graph; 

short int visited[MAX_VERTEX] = { 0 };	// 방문유무를 기록할 배열

typedef struct QueueNode {
	int vertex;	// 큐에 값을 저장할 변수
	struct QueueNode *link;	// 다음 큐를 가리킬 포인터
}QueueNode;
QueueNode *front, *rear;
void addq(int);	// 큐에 값을 추가하는 함수
int deleteq();	// 큐의 값을 제거하는 함수

void initializeGraph(Graph *);	// 그래프를 초기화하는 함수
void insertVertex(Graph *);	// 정점을 추가하는 함수
void insertEdge(Graph *, int, int);	// 간선을 추가하는 함수
void dfs(Graph *, int);	// 깊이우선탐색으로 그래프를 출력하는 함수
void bfs(Graph *, int);	// 너비우선탐색으로 그래프를 출력하는 함수
void printGraph(Graph *);	// 그래프의 인접리스트를 출력하는 함수
void freeGraph(Graph *);	// 그래프를 할당해제하는 함수
void initVisited();	// 방문여부를 체크하는 visited 배열을 초기화하는 함수

int main()
{
	char command;
	int key = 0, v1 = 0, v2 = 0;
	Graph *graph = (Graph *)malloc(sizeof(Graph));	// 그래프를 표현하는 graph 생성

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
			initializeGraph(graph);	// 그래프 초기화
			printf("\n > Graph Initialized. \n");
			break;
		case 'q': case 'Q':
			freeGraph(graph);	// 그래프의 내부 연결 할당해제
			free(graph);	// graph 할당해제
			break;
		case 'v': case 'V':
			insertVertex(graph);	// 정점 추가
			break;
		case 'e': case 'E':
			printf("\n > Type two vertices number (v1 v2) : ");
			scanf("%d %d", &v1, &v2);
			insertEdge(graph, v1, v2);	// 두 정점 사이의 간선 추가
			insertEdge(graph, v2, v1);	// 무방향 그래프를 표현하기 위해 한번 더 추가
			break;
		case 'd': case 'D':
			printf("\n > Depth First Search \n");
			dfs(graph, 0);	// 깊이우선탐색
			initVisited();	// visited[] 초기화
			break;
		case 'b': case 'B':
			printf("\n > Breath First Search \n");
			bfs(graph, 0);	// 너비우선탐색
			initVisited();	// visited[] 초기화
			break;
		case 'p': case 'P':
			printf("\n > Print Graph \n");
			printGraph(graph);	// 그래프의 인접리스트 출력
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	} while (command != 'q' && command != 'Q');	// q 입력전 까지 반복 

	return 1;
}

void initializeGraph(Graph * g) {
	int i;

	g->vertexNum = 0;	// 정점의 수를 0으로 설정
	for (i = 0; i < MAX_VERTEX; i++)
		g->adjLists[i] = NULL;	// adjLists가 가리키는 노드들을 NULL로 설정
}

void insertVertex(Graph * g) {
	if ((g->vertexNum + 1) > MAX_VERTEX)	// 정점을 추가했을 때 최대 정점의 수를 초과하는 경우
		printf("\n > Maximum number of vertex has reached.");	// 오류메세지 출력
	else {
		printf("\n > Vertex[%d] Inserted. \n", g->vertexNum);
		g->vertexNum++;	// 정점의 수 추가
	}
}

void insertEdge(Graph * g, int v1, int v2) {
	Node *node, *temp, *prev;
	int error = 0;

	temp = g->adjLists[v1];	// temp를 adjLists[v1]이 가리키는 노드로 설정
	while (temp) {	// temp가 존재할 때 까지 반복
		if (temp->vertex == v2) {	// temp의 정점 넘버가 v2와 같은 경우
			error = 1;
			break;	// error을 1로 설정 후 while문 break
		}
		temp = temp->link;	// temp를 temp의 다음노드로 설정
	}

	if (!error) {	// error가 0인 경우
		if (v1 >= g->vertexNum || v2 >= g->vertexNum) {	// v1이나 v2가 현재 정점의 수보다 큰 경우
			printf("\n Vertex number is not correct.");	// 오류메세지 출력
		}
		else {
			node = (Node *)malloc(sizeof(Node)); 
			node->vertex = v2;	// node의 정점 넘버를 v2로 설정

			if (!g->adjLists[v1]) {	// adjLists[v1]가 가리키는 노드가 없는 경우
				node->link = NULL;	// node의 다음 노드를 NULL로 설정
				g->adjLists[v1] = node;	// adjLists[v1]가 node를 가리키게 설정
			}
			else {	// adjLists[v1]가 가리키는 노드가 있는 경우
				if (v2 < g->adjLists[v1]->vertex) {	// v2가 adjLists[v1]가 가리키는 노드의 정점 넘버보다 작은 경우
					node->link = g->adjLists[v1];	// adjLists[v1]가 가리키는 노드를 node가 가리키게 설정
					g->adjLists[v1] = node;	// adjLists[v1]가 node를 가리키게 변경
				}
				else {	// v2가 adjLists[v1]가 가리키는 노드의 정점 넘버보다 큰 경우
					temp = g->adjLists[v1];	// temp가 adjLists[v1]가 가리키는 노드를 가리키게 설정
					prev = temp;	// prev가 temp를 가리키게 설정

					while (v2 > temp->vertex) {	// v2가 temp에 저장된 정점 노드보다 클 때 까지 반복
						prev = temp;	// temp를 prev가 가리키게 설정
						temp = temp->link;	// temp는 다음 노드로 변경
						if (!temp)
							break;	// temp가 NULL인 경우 break
					}

					if (!temp) {	// temp가 비어있는 경우
						node->link = NULL;	// node의 다음 노드를 NULL로 설정
						prev->link = node;	// prev의 다음 노드를 node로 변경
					}
					else {	// temp가 비어있지 않은 경우
						node->link = temp;	// node의 다음 노드를 temp로 변경
						prev->link = node;	// prev의 다음 노드를 node로 변경
					}
				}
			}
			printf("\n (%d > %d) Edge Inserted.", v1, v2);
		}
	}
	else	// error가 0인 경우 에러메세지 출력
		printf("\n (%d > %d) Edge already exists. ", v1, v2);
}

void dfs(Graph *g, int v) {
	Node *w;
	visited[v] = 1;	// 방문기록 추가
	printf("%5d", v);
	for (w = g->adjLists[v]; w; w = w->link)	// w가 adjLists[v]를 가리키게 설정 후 for문 반복 시 다음 노드로 이동
		if (!visited[w->vertex])	// 다음 정점 방문 기록이 없는 경우
			dfs(g, w->vertex);	// 재귀호출
}

void bfs(Graph *g, int v) {
	Node *w;
	front = rear = NULL;	// front와 rear을 NULL로 초기화
	printf("%5d", v);
	visited[v] = 1;	// 방문기록 추가
	addq(v);	// 정점 넘버 v를 큐에 추가
	while (front) {	// front가 NULL이 될 때 까지 반복
		v = deleteq();	// 큐에서 제거한 값을 v에 대입
		for (w = g->adjLists[v]; w; w = w->link)	// w가 adjLists[v]를 가리키게 설정 후 for문 반복 시 다음 노드로 이동
			if (!visited[w->vertex]) {	// 다음 정점 방문 기록이 없는 경우
				printf("%5d", w->vertex);
				addq(w->vertex);	// 다음 정점 큐에 추가
				visited[w->vertex] = 1;	// 다음 노드 방문기록 추가
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
			printf("\t %d", temp->vertex);	// 연결된 노드 리스트를 출력
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
			free(prev);	// adjLists[i]에 연결된 노드들을 할당해제
		}
		g->adjLists[i] = NULL;	// adjLists[i]값을 NULL로 변경
	}
}

void addq(int i) {
	QueueNode *temp = (QueueNode *)malloc(sizeof(QueueNode));

	if (temp) {
		temp->vertex = i;	// 큐에 저장할 값을 대입
		temp->link = NULL;	// 큐의 다음을 NULL로 설정
		if (!front) {	// front가 NULL인 경우
			front = temp;
			rear = temp;	// front와 rear을 temp로 설정
		}
		else {	// front가 값이 있는 경우
			rear->link = temp;	// rear이 temp를 가리키게 변경
			rear = temp;
		}
	}
}

int deleteq() {
	QueueNode *temp = front;
	int item;
	if (front) {	// front가 값이 있는 경우
		item = temp->vertex;	// item에 temp가 가지고 있는 값 저장
		front = front->link;	// front 이동
		if (!front)	// front가 NULL인 경우
			rear = NULL;	// rear도 NULL로 설정
		free(temp);	// temp 할당해제
		return item;
	}
}

void initVisited() {
	int i;

	for (i = 0; i < MAX_VERTEX; i++)
		visited[i] = 0;	// 방문기록을 모두 초기화
}
