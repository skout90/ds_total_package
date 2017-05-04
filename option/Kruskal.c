#include "Kruskal.h"

///////////////////////////////////////////////////////////////////////
//17. Minimum cost Spanning Tree : Kruskal algorithm

//���� ����
int WhoPrecede(int data1, int data2)
{
	if(data1 < data2)
		return 0;
	else
		return 1;
}


//�켱���� ť�� ���� ����ġ �� �Լ�
int PQWeightComp(WEdge d1, WEdge d2)
{
	return d1.weight - d2.weight;
}


// �׷����� �ʱ�ȭ
void LWGraphInit(LWGraph *pg, int nv)
{
	int i;

	pg->adjList = (LinkedList*)malloc(sizeof(LinkedList)*nv);//����(nv) ������ŭ �����Ҵ�
	pg->numV = nv;
	pg->numE = 0;		//�ʱ��� ���� �� 0��

	for(i=0; i<nv; i++) //nv : ���޹��� ������ ����
	{
		ListInit(&(pg->adjList[i])); //�������� ����Ʈ �ʱ�ȭ.
		SetSortRule(&(pg->adjList[i]), WhoPrecede); //����Ʈ�� ���ı��� ����->����� ���¸� ���� ���� �ϱ� ����. ��� ����
	}

	//Ž�� ���� ����� ���� ������ �Ҵ� �� �ʱ�ȭ
	pg->visitInfo = (int *)malloc(sizeof(int)*pg->numV);
	memset(pg->visitInfo, 0, sizeof(int) * pg->numV);

	// �켱���� ť �ʱ�ȭ
	PQueueInit(&(pg->pqueue), PQWeightComp);
}


//�׷����� ���ҽ��� ����
void LWGraphDestroy(LWGraph *pg)
{
	if(pg->adjList != NULL)
		free(pg->adjList);

	if(pg->visitInfo != NULL)
		free(pg->visitInfo);
}

//������ �߰�
void AddWEdge(LWGraph *pg, int fromV, int toV, int weight)
{
	WEdge edge = {fromV, toV, weight};

	LInsert(&(pg->adjList[fromV]), toV);	//���� fromV�� ���� ����Ʈ�� ���� toV�� ���� �߰�.
	LInsert(&(pg->adjList[toV]), fromV);	
	pg->numE += 1;	//���� �� +1

	//������ ����ġ ������ �켱���� ť�� ����
	PEnqueue(&(pg->pqueue), edge);
}


//��ƿ��Ƽ �Լ� : ������ ���� ���
void ShowLWGraphEdgeInfo(LWGraph *pg)
{
	int i;
	int vx;

	for(i=0; i<pg->numV; i++)
	{
		printf("%c�� ����� ���� : ", i+65);

		if(LFirst(&(pg->adjList[i]), &vx))
		{
			printf("%c ", vx + 65);

			while(LNext(&(pg->adjList[i]), &vx))
				printf("%c ", vx + 65);
		}
		puts("");
	}
}

//���� �湮
int LWGVisitVertex(LWGraph *pg, int visitV)
{
	if(pg->visitInfo[visitV] == 0)
	{
		pg->visitInfo[visitV] = 1;	//�湮�� ���� 1�� �ʱ�ȭ
		//printf("%c ", visitV + 65);
		return TRUE;
	}

	return FALSE;
}

// Depth First Search : ������ ���� ���
void DFShowLWGraphVertex(LWGraph *pg, int startV)
{
	ArrayStack stack;
	int visitV = startV;
	int nextV;

	//DFS�� ���� ������ �ʱ�ȭ
	AStackInit(&stack);

	LWGVisitVertex(pg, visitV);	// ���� ���� �湮
	ASPush(&stack, visitV);		// �湮�� ���� ���ÿ� ����

	while(LFirst(&(pg->adjList[visitV]), &nextV) == TRUE) //����������
	{
		int visitFlag = FALSE;

		if(LWGVisitVertex(pg, nextV) == TRUE)	//������ ���� �湮�����ʾҴٸ�
		{
			ASPush(&stack, visitV);	//�湮�� ���� ���ÿ� ����
			visitV = nextV;			
			visitFlag = TRUE;		//����ߴٰ� ǥ��
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
			if(ASIsEmpty(&stack) == TRUE)	//������ ��� DFS����
				break;
			else
				visitV = ASPop(&stack);
		}
	}

	//Ž�� ���� �ʱ�ȭ
	memset(pg->visitInfo, 0, sizeof(int) * pg->numV);
}

// Breadth First Search : ������ ���� ���
void BFShowLWGraphVertex(LWGraph *pg, int startV)
{
	CQueue queue;
	int visitV = startV;
	int nextV;

	// DFS�� ���� ť�� �ʱ�ȭ
	CQueueInit(&queue);

	//���� ���� Ž��
	LWGVisitVertex(pg, visitV);

	while(LFirst(&(pg->adjList[visitV]), &nextV) == TRUE)
	{
		if(LWGVisitVertex(pg, nextV) == TRUE)	//�湮�� �����ߴٸ�
			CEnqueue(&queue, nextV);

		while(LNext(&(pg->adjList[visitV]), &nextV) == TRUE)
		{
			if(LWGVisitVertex(pg, nextV) == TRUE)	//�湮������ ť�� ����
				CEnqueue(&queue, nextV);
		}

		if(CQIsEmpty(&queue) == TRUE)	//ť�� ��� BFS ����
			break;
		else
			visitV = CDequeue(&queue);
	}

	//Ž�� ���� �ʱ�ȭ
	memset(pg->visitInfo, 0, sizeof(int) * pg->numV);
}


// ���� ������ ���� �Ҹ�: ConKruskalMST Helper function
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

// ������ �Ҹ�: ConKruskalMST Helper function
void RemoveEdge(LWGraph * pg, int fromV, int toV)
{
	RemoveWayEdge(pg, fromV, toV);
	RemoveWayEdge(pg, toV, fromV);
	(pg->numE)--;
}

//���� ȸ��
void RecoverEdge(LWGraph *pg, int fromV, int toV, int weight)
{
	LInsert(&(pg->adjList[fromV]), toV);
	LInsert(&(pg->adjList[toV]), fromV);
	(pg->numE)++;
}


// �� ������ ����Ǿ� �ִٸ� TRUE, �׷��� �ʴٸ� FALSE ��ȯ
int IsConnVertex(LWGraph * pg, int v1, int v2)
{
	ArrayStack stack;
	int visitV = v1;
	int nextV;

	//DFS�� ���� ������ �ʱ�ȭ
	AStackInit(&stack);
	LWGVisitVertex(pg, visitV);	// ���� ���� �湮
	ASPush(&stack, visitV);		// �湮�� ���� ���ÿ� ����

	while(LFirst(&(pg->adjList[visitV]), &nextV) == TRUE) //����������
	{
		int visitFlag = FALSE;

		//������ ���ƴٴϴ� ���߿� ��ǥ�� ã�´ٸ� TRUE�� ��ȯ.
		if(nextV == v2) 
		{

			//�Լ� ��ȯ�� �ʱ�ȭ ����
			memset(pg->visitInfo, 0, sizeof(int) * pg->numV);
			return TRUE;
		}

		if(LWGVisitVertex(pg, nextV) == TRUE)	//������ ���� �湮�����ʾҴٸ�
		{
			ASPush(&stack, visitV);	//�湮�� ���� ���ÿ� ����
			visitV = nextV;			
			visitFlag = TRUE;		//����ߴٰ� ǥ��
		}
		else
		{
			while(LNext(&(pg->adjList[visitV]), &nextV) == TRUE)
			{
				//������ ���ƴٴϴ� ���߿� ��ǥ�� ã�´ٸ� TRUE�� ��ȯ.
				if(nextV == v2) 
				{
					//�Լ� ��ȯ�� �ʱ�ȭ ����
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
			if(ASIsEmpty(&stack) == TRUE)	//������ ��� DFS����
				break;
			else
				visitV = ASPop(&stack);
		}
	}

	//Ž�� ���� �ʱ�ȭ
	memset(pg->visitInfo, 0, sizeof(int) * pg->numV);
	return FALSE;	//��ǥ�� ã�� ���Ͽ���.
}


// �ּҺ�� ���� Ʈ�� ����
void ConKruskalMST(LWGraph *pg)
{
	WEdge recvEdge[20];	//������ ������ ���� ����
	WEdge edge;
	int eidx = 0;
	int i;

	//�ּҺ�����Ʈ���� �ϼ��� �� ���� �Ʒ��� while�� �ݺ�
	while(pg->numE+1 > pg->numV)	// MST������ �� + 1 == �����Ǽ�
	{
		//�켱���� ť���� ����ġ�� ���� ���� ������ ������ ����
		edge = PDequeue(&(pg->pqueue));

		//�켱���� ť���� ���� ������ ������ �׷������� ����
		RemoveEdge(pg, edge.v1, edge.v2);

		//������ �����ϰ� ������ �� ������ �����ϴ� ��ΰ� �ִ��� Ȯ��
		if(!IsConnVertex(pg, edge.v1, edge.v2))
		{
			//��ΰ� ���ٸ� ������ ������ ����
			RecoverEdge(pg, edge.v1, edge.v2, edge.weight);

			//������ ������ ������ ������ ����
			//������ �����ϴ� ���� : �� �� ���䰡 �̷��� ������ ��������� ����
			//������ �����ϸ� �ش� ������ ������ �Ұ� �Ǳ� ������ ���� ����.
			recvEdge[eidx++] = edge;
		}
	}

	//�켱���� ť���� ������ ������ ������ ȸ��
	for(i=0; i<eidx; i++)
		PEnqueue(&(pg->pqueue), recvEdge[i]);
}

// ����ġ ���� ���
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
