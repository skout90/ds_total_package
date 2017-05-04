#pragma once
#include "C:\Users\june\Desktop\프로젝트\자료구조\DSPackege.h"

///////////////////////////////////////////////////////////////////////
//17. Minimum cost Spanning Tree : Kruskal algorithm


//DSPackege.h 16번 List Base Graph에서 이미 정의.
//enum {A, B, C, D, E, F, G, H, I, J};	//정점의 이름을 상수화
//enum {SEOUL, INCHEON, DAEGU, BUSAN, KWANGJU };

typedef struct __ual
{
	int numV;				//정점의 수
	int numE;				//간선의 수
	LinkedList *adjList;	//간선의 정보
	int *visitInfo;			//방문 여부 체크
	PQueue pqueue;			//간선의 가중치 정보 저장
} LWGraph; // 리스트 가중치 그래프


// 그래프의 초기화
void LWGraphInit(LWGraph *pg, int nv);
//인자 : 그래프의 주소, nv = "정점의 수" 전달

//그래프의 리소스를 해제
void LWGraphDestroy(LWGraph *pg);

//간선의 추가
void AddWEdge(LWGraph *pg, int fromV, int toV, int weight);
//인자 : 그래프 주소, fromV와 toV로 전달된 정점을 연결하는 간선 추가

//유틸리티 함수 : 간선의 정보 출력
void ShowLWGraphEdgeInfo(LWGraph *pg);

// Depth First Search : 정점의 정보 출력
void DFShowLWGraphVertex(LWGraph *pg, int startV);
//인자 : 그래프주소, 탐색을 시작할 정점

// Breadth First Search : 정점의 정보 출력
void BFShowLWGraphVertex(LWGraph *pg, int startV);
//인자 : 그래프주소, 탐색을 시작할 정점

// 최소비용 신장 트리 구성
void ConKruskalMST(LWGraph *pg);

// 가중치 정보 출력
void ShowGraphEdgeWeightInfo(LWGraph *pg);