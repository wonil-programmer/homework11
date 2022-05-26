#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTEX 10 // 최대 정점수
#define FALSE 0
#define TRUE 1

/* Graph Structure Declaration */
typedef struct graphNode {
	int vertex;	// 정점 (데이터 존재)
	struct graphNode* link;	// 그래프 구조체 포인터
} graphNode;

/* Sturcture Declaration to express graph as an adjacentList */
typedef struct graphType {
	int n;	// 그래프의 정점수
	graphNode* adjacentList[MAX_VERTEX]; // 그래프 정점에 대한 헤드 포인터 배열
    int visited[MAX_VERTEX]; // 그래프 정점에 대한 방문 표시를 위한 배열
} graphType;


/* 함수 원형 선언 */
void initializeGraph(graphType* g);
void insertVertex(graphType* g, int v);
void insertEdge(graphType* g, int u, int v);
void DFS_searchGraph(graphType* g, int v);
void BFS_searchGraph(graphType* g, int v);
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
            for (int data = 0; data <= MAX_VERTEX; data++) 
                // for문을 MAX_VERTEX만큼 돌며 해당 데이터의 정점을 삽입
			    insertVertex(G, data);
			break;

		case 'e': case 'E':
			/* Graph에 간선 삽입 */
			int edgeNum;
	        printf("삽입할 간선의 개수를 입력하세요 : \n");
	        scanf("%d", &edgeNum);
	        for (int i = 0; i < edgeNum; i++) {
                // for문을 edgeNum만큼 돌며 무방향 그래프의 간선을 해당 정점에 부속시킴
		        int x, y; // 꼬리정점 x, 머리정점 y
		        printf("정점 u와 v를 입력하세요 : \n");
		        scanf("%d", &x);
                scanf("%d", &y);
                // 무방향 그래프 간선 삽입
		        insert_edge(g, x, y);
                insert_edge(g, y, x);
	        }
			break;

		case 'd': case 'D':
			/* Graph를 DFS로 탐색 */
            int x; // 탐색을 시작할 정점
			void DFS_searchGraph(G, x);
			break;

		case 'b': case 'B':
			/* Graph를 BFS로 탐색 */
            int x; // 탐색을 시작할 정점
			void BFS_searchGraph(G, x);
			break;

		case 'p': case 'P':
            /* Graph 출력 */
			void printGraph(G);
			break;

		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}





/* 

