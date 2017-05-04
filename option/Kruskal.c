#include "Kruskal.h"

///////////////////////////////////////////////////////////////////////
//17. Minimum cost Spanning Tree : Kruskal algorithm

//정렬 순서
int WhoPrecede(int data1, int data2)
{
	if(data1 < data2)
		return 0;
	else
		return 1;
}


//우선순위 큐를 위한 가중치 비교 함수
int PQWeightComp(WEdge d1, WEdge d2)
{
	return d1.weight - d2.weight;
}


// 그래프의 초기화
void LWGraphInit(LWGraph *pg, int nv)
{
	int i;

	pg->adjList = (LinkedList*)malloc(sizeof(LinkedList)*nv);//정점(nv) 개수만큼 동적할당
	pg->numV = nv;
	pg->numE = 0;		//초기의 간선 수 0개

	for(i=0; i<nv; i++) //nv : 전달받은 정점의 개수
	{
		ListInit(&(pg->adjList[i])); //정점마다 리스트 초기화.
		SetSortRule(&(pg->adjList[i]), WhoPrecede); //리스트의 정렬기준 설정->출력의 형태를 보기 좋게 하기 위함. 없어도 무관
	}

	//탐색 정보 등록을 위한 공간의 할당 및 초기화
	pg->visitInfo = (int *)malloc(sizeof(int)*pg->numV);
	memset(pg->visitInfo, 0, sizeof(int) * pg->numV);

	// 우선순위 큐 초기화
	PQueueInit(&(pg->pqueue), PQWeightComp);
}


//그래프의 리소스를 해제
void LWGraphDestroy(LWGraph *pg)
{
	if(pg->adjList != NULL)
		free(pg->adjList);

	if(pg->visitInfo != NULL)
		free(pg->visitInfo);
}

//간선의 추가
void AddWEdge(LWGraph *pg, int fromV, int toV, int weight)
{
	WEdge edge = {fromV, toV, weight};

	LInsert(&(pg->adjList[fromV]), toV);	//정점 fromV의 연결 리스트에 정점 toV의 정보 추가.
	LInsert(&(pg->adjList[toV]), fromV);	
	pg->numE += 1;	//간선 수 +1

	//간선의 가중치 정보를 우선순위 큐에 저장
	PEnqueue(&(pg->pqueue), edge);
}


//유틸리티 함수 : 간선의 정보 출력
void ShowLWGraphEdgeInfo(LWGraph *pg)
{
	int i;
	int vx;

	for(i=0; i<pg->numV; i++)
	{
		printf("%c와 연결된 정점 : ", i+65);

		if(LFirst(&(pg->adjList[i]), &vx))
		{
			printf("%c ", vx + 65);

			while(LNext(&(pg->adjList[i]), &vx))
				printf("%c ", vx + 65);
		}
		puts("");
	}
}

//정점 방문
int LWGVisitVertex(LWGraph *pg, int visitV)
{
	if(pg->visitInfo[visitV] == 0)
	{
		pg->visitInfo[visitV] = 1;	//방문한 곳은 1로 초기화
		//printf("%c ", visitV + 65);
		return TRUE;
	}

	return FALSE;
}

// Depth First Search : 정점의 정보 출력
void DFShowLWGraphVertex(LWGraph *pg, int startV)
{
	ArrayStack stack;
	int visitV = startV;
	int nextV;

	//DFS를 위한 스택의 초기화
	AStackInit(&stack);

	LWGVisitVertex(pg, visitV);	// 시작 정점 방문
	ASPush(&stack, visitV);		// 방문한 정점 스택에 삽입

	while(LFirst(&(pg->adjList[visitV]), &nextV) == TRUE) //참조성공시
	{
		int visitFlag = FALSE;

		if(LWGVisitVertex(pg, nextV) == TRUE)	//정점을 아직 방문하지않았다면
		{
			ASPush(&stack, visitV);	//방문한 정점 스택에 삽입
			visitV = nextV;			
			visitFlag = TRUE;		//방분했다고 표시
		}
		else
		{
			while(LNext(&(pg->adjList[visitV]), &nextV) == TRUE)
			{
				if(LWGVisitVertex(pg, nextV) == TRUE)
				{
					ASPush(&stack, visitV);
					visitV = nextV;
					visitFlag = TRUE;
					break;
				}
			}
		}

		if(visitFlag == FALSE)
		{
			if(ASIsEmpty(&stack) == TRUE)	//스택이 비면 DFS종료
				break;
			else
				visitV = ASPop(&stack);
		}
	}

	//탐색 정보 초기화
	memset(pg->visitInfo, 0, sizeof(int) * pg->numV);
}

// Breadth First Search : 정점의 정보 출력
void BFShowLWGraphVertex(LWGraph *pg, int startV)
{
	CQueue queue;
	int visitV = startV;
	int nextV;

	// DFS를 위한 큐의 초기화
	CQueueInit(&queue);

	//시작 정점 탐색
	LWGVisitVertex(pg, visitV);

	while(LFirst(&(pg->adjList[visitV]), &nextV) == TRUE)
	{
		if(LWGVisitVertex(pg, nextV) == TRUE)	//방문에 성공했다면
			CEnqueue(&queue, nextV);

		while(LNext(&(pg->adjList[visitV]), &nextV) == TRUE)
		{
			if(LWGVisitVertex(pg, nextV) == TRUE)	//방문성공시 큐에 삽입
				CEnqueue(&queue, nextV);
		}

		if(CQIsEmpty(&queue) == TRUE)	//큐가 비면 BFS 종료
			break;
		else
			visitV = CDequeue(&queue);
	}

	//탐색 정보 초기화
	memset(pg->visitInfo, 0, sizeof(int) * pg->numV);
}


// 한쪽 방향의 간선 소멸: ConKruskalMST Helper function
void RemoveWayEdge(LWGraph *pg, int fromV, int toV)
{
	int edge;

	if(LFirst(&(pg->adjList[fromV]), &edge))
	{
		if(edge == toV)
		{
			LRemove(&(pg->adjList[fromV]));
			return;
		}

		while(LNext(&(pg->adjList[fromV]), &edge))
		{
			if(edge == toV)
			{
				LRemove(&(pg->adjList[fromV]));
				return;
			}
		}
	}
}

// 간선의 소멸: ConKruskalMST Helper function
void RemoveEdge(LWGraph * pg, int fromV, int toV)
{
	RemoveWayEdge(pg, fromV, toV);
	RemoveWayEdge(pg, toV, fromV);
	(pg->numE)--;
}

//간선 회복
void RecoverEdge(LWGraph *pg, int fromV, int toV, int weight)
{
	LInsert(&(pg->adjList[fromV]), toV);
	LInsert(&(pg->adjList[toV]), fromV);
	(pg->numE)++;
}


// 두 정점이 연결되어 있다면 TRUE, 그렇지 않다면 FALSE 반환
int IsConnVertex(LWGraph * pg, int v1, int v2)
{
	ArrayStack stack;
	int visitV = v1;
	int nextV;

	//DFS를 위한 스택의 초기화
	AStackInit(&stack);
	LWGVisitVertex(pg, visitV);	// 시작 정점 방문
	ASPush(&stack, visitV);		// 방문한 정점 스택에 삽입

	while(LFirst(&(pg->adjList[visitV]), &nextV) == TRUE) //참조성공시
	{
		int visitFlag = FALSE;

		//정점을 돌아다니는 도중에 목표를 찾는다면 TRUE를 반환.
		if(nextV == v2) 
		{

			//함수 반환전 초기화 진행
			memset(pg->visitInfo, 0, sizeof(int) * pg->numV);
			return TRUE;
		}

		if(LWGVisitVertex(pg, nextV) == TRUE)	//정점을 아직 방문하지않았다면
		{
			ASPush(&stack, visitV);	//방문한 정점 스택에 삽입
			visitV = nextV;			
			visitFlag = TRUE;		//방분했다고 표시
		}
		else
		{
			while(LNext(&(pg->adjList[visitV]), &nextV) == TRUE)
			{
				//정점을 돌아다니는 도중에 목표를 찾는다면 TRUE를 반환.
				if(nextV == v2) 
				{
					//함수 반환전 초기화 진행
					memset(pg->visitInfo, 0, sizeof(int) * pg->numV);
					return TRUE;
				}
				if(LWGVisitVertex(pg, nextV) == TRUE)
				{
					ASPush(&stack, visitV);
					visitV = nextV;
					visitFlag = TRUE;
					break;
				}
			}
		}

		if(visitFlag == FALSE)
		{
			if(ASIsEmpty(&stack) == TRUE)	//스택이 비면 DFS종료
				break;
			else
				visitV = ASPop(&stack);
		}
	}

	//탐색 정보 초기화
	memset(pg->visitInfo, 0, sizeof(int) * pg->numV);
	return FALSE;	//목표를 찾지 못하였음.
}


// 최소비용 신장 트리 구성
void ConKruskalMST(LWGraph *pg)
{
	WEdge recvEdge[20];	//복원할 간선의 정보 저장
	WEdge edge;
	int eidx = 0;
	int i;

	//최소비용신장트리를 완성할 때 까지 아래의 while문 반복
	while(pg->numE+1 > pg->numV)	// MST간선의 수 + 1 == 정점의수
	{
		//우선순위 큐에서 가중치가 제일 높은 간선의 정보를 꺼냄
		edge = PDequeue(&(pg->pqueue));

		//우선순위 큐에서 꺼낸 간선을 실제로 그래프에서 삭제
		RemoveEdge(pg, edge.v1, edge.v2);

		//간선을 삭제하고 나서도 두 정점을 연결하는 경로가 있는지 확인
		if(!IsConnVertex(pg, edge.v1, edge.v2))
		{
			//경로가 없다면 삭제한 간선을 복원
			RecoverEdge(pg, edge.v1, edge.v2, edge.weight);

			//복원한 간선의 정보를 별도로 저장
			//별도로 저장하는 이유 : 한 번 검토가 이뤄진 간선은 재검토하지 않음
			//하지만 삭제하면 해당 간선의 정보를 잃게 되기 때문에 따로 저장.
			recvEdge[eidx++] = edge;
		}
	}

	//우선순위 큐에서 삭제된 간선의 정보를 회복
	for(i=0; i<eidx; i++)
		PEnqueue(&(pg->pqueue), recvEdge[i]);
}

// 가중치 정보 출력
void ShowGraphEdgeWeightInfo(LWGraph *pg)
{
	PQueue copyPQ = pg->pqueue;
	WEdge edge;

	while(!PQIsEmpty(&copyPQ))
	{
		edge = PDequeue(&copyPQ);
		printf("(%c-%c), w:%d \n", edge.v1+65, edge.v2+65, edge.weight);
	}
}
