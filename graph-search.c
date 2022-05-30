#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTEX 10 // 최대 정점수
#define FALSE 0
#define TRUE 1

/* Graph Structure Declaration */
typedef struct graphNode {
   	int vertex;   // 정점 (데이터 존재)
   	struct graphNode* link;   // 그래프 구조체 포인터
} graphNode;

/* Sturcture Declaration to express graph as an adjacentList */
typedef struct graphType {
   	int n;   // 그래프의 정점수
   	graphNode* adjacentList[MAX_VERTEX]; // 그래프 정점에 대한 헤드 포인터 배열
    int visited[MAX_VERTEX]; // 그래프 정점에 대한 방문 플래그 표시를 위한 배열
} graphType;

/* Declaration of Stack used in DFS */
typedef struct stackNode {
   	int data; // 노드 값
   	struct stackNode* link; // 다음 노드 가리키는 스택노드 구조체 포인터 
} stackNode;

stackNode* top; // 스택의 top 노드 지정하는 스택 구조체 포인터

/* Declaration of Queue used in BFS */
typedef struct QNode {
   	int data; // 큐노드 값
   	struct QNode* link; // 다음 노드 가리키는 큐노드 구조체 포인터
} QNode;

typedef struct QueueType {
   	struct QNode * front, *rear; // 큐의 처음과 마지막을 가리키는 큐노드 구조체 포인터
} QueueType;


/* 함수 원형 선언 */
void initializeGraph(graphType* g);
void insertVertex(graphType* g, int v);
void insertEdge(graphType* g, int u, int v);
void DFS_searchGraph(graphType* g, int v);
int isStackEmpty();
void push(int item);
int pop();
void BFS_searchGraph(graphType* g, int v);
QueueType* initQueue();
int isQueueEmpty();
void enQueue(QueueType* q, int item);
int deQueue(QueueType* q);

void printGraph(graphType* g);
void freeGraph(graphType* g);

int main()
{
   printf("------ [2019036068] [허원일] ------\n");

   char command;
   graphType* G = (graphType*)malloc(sizeof(graphType)); // 생성할 graph G에 대한 동적 메모리 할당

   do{
      printf("\n");
      printf("----------------------------------------------------------------\n");
      printf("                        Graph Searches                          \n");
      printf("----------------------------------------------------------------\n");
      printf(" Initialize Graph = z                                           \n");
      printf(" Insert Vertex = v             Insert Edge = e                  \n");
      printf(" Depth First Search = d        Breath First Search = b          \n");
      printf(" Print Graph = p               Quit = q                         \n");
      printf("----------------------------------------------------------------\n");

      printf("Command = ");
      scanf(" %c", &command);

      switch(command) {
      case 'z': case 'Z':
         /* Graph 초기화 */
         initializeGraph(G);
         break;

      case 'q': case 'Q':
         /* Graph에 할당된 메모리 반납 */
         freeGraph(G);
         break;

      case 'v': case 'V':
         /* Graph에 정점 삽입 */
            for (int data = 0; data < MAX_VERTEX; data++) 
            // for문을 MAX_VERTEX만큼 돌며 해당 데이터의 정점을 삽입
            	insertVertex(G, data);
         break;

      case 'e': case 'E':
         /* Graph에 간선 삽입 */
         	int edgeNum;
           	printf("삽입할 간선의 개수를 입력하세요 : \n");
           	scanf("%d", &edgeNum);
         /* 간선의 개수가 최대간선수보다 큰 경우 실행종료 (무방향그래프) */
         if (edgeNum > MAX_VERTEX*(MAX_VERTEX-1)/2) 
			break;
           	for (int i = 0; i < edgeNum; i++) {
                // for문을 edgeNum만큼 돌며 무방향 그래프의 간선을 해당 정점에 부속시킴
              	int x, y; // 꼬리정점 x, 머리정점 y
              	printf("정점 u와 v를 입력하세요 : \n");
              	scanf("%d", &x);
              	scanf("%d", &y);

                // 무방향 그래프 간선 삽입
              	insertEdge(G, x, y);
              	insertEdge(G, y, x);
           }
         break;

      case 'd': case 'D':
         /* Graph를 DFS로 탐색 */
         int DFS_vertex; // 탐색을 시작할 정점
         printf("탐색을 시작할 정점을 입력하세요: \n");
         scanf("%d", &DFS_vertex);
         DFS_searchGraph(G, DFS_vertex);
         break;

      case 'b': case 'B':
         /* Graph를 BFS로 탐색 */
         int BFS_vertex; // 탐색을 시작할 정점
         printf("탐색을 시작할 정점을 입력하세요: \n");
         scanf("%d", &BFS_vertex);
         BFS_searchGraph(G, BFS_vertex);
         break;

      case 'p': case 'P':
		 /* Graph 출력 */
         printGraph(G);
         break;

      default:
         printf("\n       >>>>>   Concentration!!   <<<<<     \n");
         break;
      }

   } while(command != 'q' && command != 'Q');

   return 1;
}

/* 공백 graph를 생성하는 함수 */
void initializeGraph(graphType *g) {
    int v;
    g->n = 0; // 그래프 정점수를 0으로 초기화
    for (v = 0; v < MAX_VERTEX; v++) {
        g->adjacentList[v] = NULL; // 그래프 정점에 대한 헤드 포인터 배열을 NULL로 초기화
        g->visited[v] = FALSE; // 그래프 정점에 대한 배열 visited를 FALSE로 초기화
    }
}

/* graph에 정점 v를 삽입하는 함수 */
void insertVertex(graphType* g, int v) {
    /* 점점수가 최대정점수보다 커질 경우 경고문 출력후 함수 종료 */
   if ((g->n) + 1 > MAX_VERTEX) {
        printf("\n 그래프의 정점의 개수를 초과하였습니다\n");
      return;
   }
   g->n++; // 그래프 정점수 하나 증가
}

/* graph에 간선 (u,v)를 삽입하는 함수 */
void insertEdge(graphType* g, int u, int v) {
   /* 정점 u의 번호나 정점 v의 번호가 그래프 정점의 개수 이상일 때 경고문 출력 후 함수 종료 */
   if (u >= g->n || v >= g->n) {
      printf("그래프 정점 번호를 잘못 입력하였습니다!\n");
      return;
   }

   /* 삽입할 노드 생성 */
   graphNode* node = (graphNode*)malloc(sizeof(graphNode));  
   node->vertex = v;
   node->link = NULL;

   /* 헤드포인터가 가리키는 인접 연결리스트가 공백일 경우 생성한 노드를 헤드에 연결 */
   if (g->adjacentList[u] == NULL) {
      g->adjacentList[u] = node;

      return;
   }

   graphNode* cur = g->adjacentList[u]; // 인접 연결리스트를 가리키는 그래프노드 포인터 cur
   graphNode* prev = g->adjacentList[u]; // 인접 연결리스트를 가리키는 그래프노드 포인터 prev (cur을 따라감)

   /* vertex를 기준으로 삽입할 위치를 찾는다 */
   while (cur != NULL) {
      if (cur->vertex > v) {
         /* 첫 노드 앞쪽에 삽입해야할 경우 인지 검사 */
         if (cur == g->adjacentList[u]) {
            node->link = g->adjacentList[u]; // 새로운 노드가 연결리스트의 기존의 첫번째 노드를 가리키게 함
            g->adjacentList[u] = node; // 새로운 노드를 연결리스트의 첫번째 노드로 지정
         }
         /* 중간이거나 마지막인 경우 */
         else {
            node->link = cur; // 새로운 노드의 다음 노드를 cur로 지정
            prev->link = node; // 삽입할 위치 전의 노드를 새로운 노드와 연결
         }
         return;
      }
      prev = cur; // cur을 따라가는 prev 
      cur = cur->link; // cur을 cur 다음노드를 가리키게함 
   }

   /* 마지막 노드까지 찾지 못한 경우 , 마지막에 삽입 */
	prev->link = node;

	return;
}


/* 생성된 graph의 인접리스트 표현을 출력하는 함수 */
void printGraph(graphType* g) {
    for (int i = 0; i < g->n; i++) {
    // for문을 정점수만큼 돌며 인접리스트의 포인터배열의 첫번째 원소부터 하여 인접한 정점들을 출력
      graphNode* p = g->adjacentList[i]; 
        // 포인터배열의 i번째 헤드포인터가 가리키는 첫번째 정점을 가리키는 그래프구조체 포인터 p
      printf("정점 %d의 인접 리스트 ", i);
      while (p != NULL) {
         printf("-> %d ", p->vertex); // 해당 정점의 값을 출력
         p = p->link; // 인접 정점으로 이동
      }
      printf("\n");
   }
}

/* graph를 DFS(깊이우선탐색)하는 함수 */
void DFS_searchGraph(graphType* g, int v) {
   graphNode* w;  // 그래프노드 구조체 포인터 w
   top = NULL; // 스택의 top을 NULL로 지정
   push(v); // 정점을 스택에 삽입
   g->visited[v] = TRUE; // 정점 방문 배열 TRUE로 변경
   printf(" %d", v);
   
   /* 스택이 공백일 때까지 반복 */
   while(!isStackEmpty()) {
      w = g->adjacentList[v]; // 탐색 시작 노드의 인접리스트의 첫번째 원소를 가리키는 w
	  /* w가 NULL이 아닐 때까지 반복 */
      while(w) {
		/* w의 정점 인덱스의 방문기록배열이 FALSE면 스택에 w의 정점값 삽입 */
		if (!g->visited[w->vertex]) {
			push(w->vertex);
			g->visited[w->vertex] = TRUE; // w의 정점 인덱스의 방문기록배열 TRUE로 변경
			printf(" %d", w->vertex);
			v = w->vertex; // w의 정점값을 v에 대입
			w = g->adjacentList[v]; // 탐색노드를 v로 변경
		}
         else w = w->link; // 다음노드를 가리키게 함
      }
      v = pop(); // 스택의 값을 추출하여 v에 대입
   }

   	/* 탐색이 끝나면 방문기록배열 초기화 */
    for (int i = 0; i < MAX_VERTEX; i++) 
    g->visited[i] = FALSE;
}

/* 스택이 공백 상태인지 검사하는 함수 */
int isStackEmpty() {
   if (top == NULL) return 1;
   else return 0;
}

/* 스택에 값을 삽입하는 함수 */
void push(int item) {
	/* 새로운 스택 노드구조체 포인터 temp */
   	stackNode* temp = (stackNode*)malloc(sizeof(stackNode));
   	temp->data = item;
   	temp->link = top;

   	top = temp; // temp을 top로 지정
}

/* 스택의 값을 추출하는 함수 */
int pop() {
   	int item;
   	stackNode* temp = top; // 스택 노드구조체 포인터 temp이 스택의 top을 가리키게 함

	/* 공백스택인 경우 함수 종료, 아니면 */
   	if (isStackEmpty()) return 0;
   	else {
   	   item = temp->data; // temp의 값을 item에 대입
   	   top = temp->link; // top을 temp 다음으로 변경
   	   free(temp); // temp 메모리 해제
	
   	   return item;
   	}
}

/* 큐를 초기화하는 함수 */
QueueType* initQueue() {
   QueueType* q;
   q = (QueueType*)malloc(sizeof(QueueType));
   q->front = NULL;
   q->rear = NULL;

   return q;
}

/* 큐가 공백상태인지 검사하는 함수 */
int isQueueEmpty(QueueType* q) {
   if (q->front == NULL) return 1;
   else return 0;
}

/* 큐에 원소를 삽입하는 함수 */
void enQueue(QueueType* q, int item) {
	/* 새로운 큐 구조체 포인터 newNode */
   QNode* newNode = (QNode*)malloc(sizeof(QNode));
   newNode->data = item;
   newNode->link = NULL;

	/* 큐가 공백상태인 경우 */
   	if (q->front == NULL) {
   	   q->front = newNode; 
   	   q->rear = newNode;
   	}
	/* 큐가 공백상태가 아닌 경우 */
   	else {
   	   q->rear->link = newNode; // 큐의 마지막에 노드 삽입
   	   q->rear = newNode; // 큐의 마지막 초기화
   	}
}

/* 큐의 원소를 추출하는 함수 */
int deQueue(QueueType* q) {
   QNode* old = q->front; // 큐의 시작을 가리키는 큐노드 구조체 포인터 old
   int item;

   /* 큐가 공백상태이면 함수종료 */ 
   if (isQueueEmpty(q)) return 0;
   else {
		item = old->data; // 큐의 첫번째 원소를 item에 대입
		q->front = q->front->link; // 큐의 시작을 다음 노드로 변경
		/* 큐의 시작이 NULL인 경우 마지막도 NULL로 지정 */
		if (q->front == NULL)
			q->rear = NULL;
		free(old); // old 메모리 해제

		return item;
   }
}

/* graph를 BFS(너비우선탐색)하는 함수 */
void BFS_searchGraph(graphType* g, int v) {
   	graphNode* w; // 그래프 노드구조체 포인터 w
   	QueueType* q; // 큐 선언
   	q = initQueue(); // 큐 초기화
   	g->visited[v] =  TRUE; // 해당하는 정점의 방문기록 표시
   	printf("%d ", v);
   	enQueue(q, v); // 큐에 정점 삽입
	
	/* 큐가 공백상태일때까지 반복 */
   	while(!isQueueEmpty(q)) {
   	   	v = deQueue(q); // 큐의 원소 추출 후 v 초기화
   	   	for (w = g->adjacentList[v]; w; w = w->link) {
			/* 모든 정점을 방문할때까지 반복 */
   			if (!g->visited[w->vertex]) {
   			   g->visited[w->vertex] = TRUE; // 정점 방문기록 표시
   			   printf("%d ", w->vertex);
   			   enQueue(q, w->vertex); // 큐에 해당 정점 삽입
   			}
   	    }
   	}

   	/* 탐색이 끝나면 방문기록배열 초기화 */
   	for (int i = 0; i < MAX_VERTEX; i++) 
   	 g->visited[i] = FALSE;
}	


/* graph의 메모리를 해제하는 함수 */
void freeGraph(graphType* g) {
	/* 인접리스트 초기화 */
	for (int i = 0; i < MAX_VERTEX; i++) {
		graphNode* p = g->adjacentList[i];
		graphNode* prev = NULL;
		while(p != NULL) {
			prev = p;
			p = p->link;
			free(prev);
		}
	}
	free(g);
}