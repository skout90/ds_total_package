#pragma once

typedef struct __edge
{
	int v1;			// 간선이 연결하는 첫 번째 정점
	int v2;			// 간선이 연결하는 두 번째 정점
	int weight;		// 간선의 가중치
} WEdge;