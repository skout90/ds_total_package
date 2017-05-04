#pragma once
#include "C:\Users\june\Desktop\������Ʈ\�ڷᱸ��\DSPackege.h"

///////////////////////////////////////////////////////////////////////
//17. Minimum cost Spanning Tree : Kruskal algorithm


//DSPackege.h 16�� List Base Graph���� �̹� ����.
//enum {A, B, C, D, E, F, G, H, I, J};	//������ �̸��� ���ȭ
//enum {SEOUL, INCHEON, DAEGU, BUSAN, KWANGJU };

typedef struct __ual
{
	int numV;				//������ ��
	int numE;				//������ ��
	LinkedList *adjList;	//������ ����
	int *visitInfo;			//�湮 ���� üũ
	PQueue pqueue;			//������ ����ġ ���� ����
} LWGraph; // ����Ʈ ����ġ �׷���


// �׷����� �ʱ�ȭ
void LWGraphInit(LWGraph *pg, int nv);
//���� : �׷����� �ּ�, nv = "������ ��" ����

//�׷����� ���ҽ��� ����
void LWGraphDestroy(LWGraph *pg);

//������ �߰�
void AddWEdge(LWGraph *pg, int fromV, int toV, int weight);
//���� : �׷��� �ּ�, fromV�� toV�� ���޵� ������ �����ϴ� ���� �߰�

//��ƿ��Ƽ �Լ� : ������ ���� ���
void ShowLWGraphEdgeInfo(LWGraph *pg);

// Depth First Search : ������ ���� ���
void DFShowLWGraphVertex(LWGraph *pg, int startV);
//���� : �׷����ּ�, Ž���� ������ ����

// Breadth First Search : ������ ���� ���
void BFShowLWGraphVertex(LWGraph *pg, int startV);
//���� : �׷����ּ�, Ž���� ������ ����

// �ּҺ�� ���� Ʈ�� ����
void ConKruskalMST(LWGraph *pg);

// ����ġ ���� ���
void ShowGraphEdgeWeightInfo(LWGraph *pg);