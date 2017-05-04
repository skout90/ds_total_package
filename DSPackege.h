/*
################################
	Data Structure Packege
	자료구조 종류
	- List
		1) ArrayList
		2) Linked List
		3) Circular Linked List
		4) Double Linked List
	- Stack
		5) Array Stack
		6) List Stack
	- Queue
		7) Circular Queue
		8) List Queue
		9) Deque(Double Ended Queue)
	- Tree
		10) Binary Tree
		11) Binary Search Tree
		12) AVL Tree
	- Heap & Priority Queue
		13) Heap & Priority Queue

	- Hash Table
		14) Hash Table
		15) Chaining(추가 헤더 파일을 사용)
	- Graph
		16) List Base Graph
	- Minimum cost Spanning Tree
		17) Kruskal algorithm(추가헤더 파일을 사용)

	Language : C
	제작자 : 홍익대학교 남준호
	참고 : 윤성우의 열혈 자료구조
################################
*/


#pragma once

#define TRUE 1
#define FALSE 0

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//#include "Slot.h"
//#include "WEdge.h"


// 원하는 자료구조 유형을 include 하세요.
//#include "Point.h"  

// 전체 기본 자료유형 설정
typedef int Data;
//typedef Point * Data;


//////////////////////////////////////////////////////////

// 1. ArrayList

#define LENGTH 100 //선형자료구조일 경우 길이 설정
typedef Data ALData; //전체 기본 자료유형과 다를 경우 추가설정

typedef struct __ArrayList
{
	ALData arr[LENGTH];
	int numOfData;     //자료 총 개수
	int curPosition;   //인덱스
} ArrayList;



//<초기화함수>
void AListInit(ArrayList *plist); 
//인자 : 초기화할 리스트 주소값
//리스트 생성시 최초 1회 호출

//<맨뒤 삽입함수>
void ALInsert(ArrayList *plist, ALData data); // 맨 뒤 삽입
//인자 : 리스트 주소값, 삽입할 데이터값

//<첫번째 값 확인>
int ALFirst(ArrayList *plist, ALData *pdata);
//인자 : //인자 : 리스트 주소값, 첫번째 값을 받아올 공간
//리턴 : 참조 성공시 1, 실패시 0 반환

//<다음 값 확인> :: ALFirst 호출이후 실행한다.
int ALNext(ArrayList *plist, ALData * pdata); // 
//인자 : 리스트 주소값, 값을 받아올 공간
//리턴 : 참조 성공시 1, 실패시 0 반환

//<현재 위치값 삭제> :: ALFirst와 ALNext로 삭제할 위치 찾은뒤 사용
ALData ALRemove(ArrayList *plist);
//인자 : 리스트 주소값
//리턴 : 삭제된 데이터값

//<저장된 자료 개수>
int ALCount(ArrayList *plist);
//인자 : 리스트 주소값






//////////////////////////////////////////////////////

// 2. LinkedList

typedef Data LData; //전체 기본 자료유형과 다를 경우 추가설정
//typedef CSlot LData;	//Chaning 사용시 사용.

typedef struct _node
{
	LData data;				//데이터 저장
	struct _node *next;		//다음 링크 주소
} SL_Node;

typedef struct _linkedList
{
	SL_Node * head;					// 맨 앞 주소
	SL_Node * tail;					// 맨 뒤 주소
	SL_Node * cur;					// 현재 노드 위치
	SL_Node * before;				// 현재 바로 이전 노드
	int numOfData;					
	int (*comp)(LData d1, LData d2);  //정렬 함수
} LinkedList;

//<초기화함수>
void ListInit(LinkedList *plist); 
//인자 : 초기화할 리스트 주소값
//더미노드 생성(head)
//리스트 생성시 최초 1회 호출

//<삽입함수>
void LInsert(LinkedList *plist, LData data);
//인자 : 리스트 주소값, 삽입할 데이터값
//- 정렬기준 존재시 : SInsert(정렬기준에 따라 삽입)호출 
//- 정렬기준 존재하지 않을 시 : FInsert(맨 앞 삽입)호출

//<LInsert에 의해 호출 되는 삽입함수>
void FInsert(LinkedList *plist, LData data); //head에 추가
void SInsert(LinkedList *plist, LData data); //정렬하여 추가
//정렬 기준 : SetSortRule 함수를 통해 등록.
//주어진 함수를 통해 값을 비교하여
//리턴값이 0일시에 해당위치에 값을 삽입한다.

//<tail에 삽입>
void TInsert(LinkedList * plist, LData data);
//인자 : 리스트 주소값, 삽입할 데이터값

//<첫번째 값 확인>
int LFirst(LinkedList *plist, LData *pdata);
//인자 : 리스트 주소값, 값을 받아올 공간
//리턴 : 참조 성공시 1, 실패시 0 반환

//<다음 값 확인> :: LFirst 호출이후 실행한다.
int LNext(LinkedList *plist, LData * pdata); // 
//인자 : 리스트 주소값, 값을 받아올 공간
//리턴 : 참조 성공시 1, 실패시 0 반환

//<현재 위치값 삭제> :: LFirst와 LNext로 삭제할 위치 찾은뒤 사용
LData LRemove(LinkedList *plist);
//인자 : 리스트 주소값
//리턴 : 삭제된 데이터값

//<저장된 자료 개수>
int LCount(LinkedList *plist);
//인자 : 리스트 주소값

//<정렬 기준 설정> 
void SetSortRule(LinkedList *plist, int (*comp)(LData d1, LData d2));
//인자 : 리스트 주소값, 정렬기준 함수

//정렬 기준을 설정하기 위해서
//main 상단에 다음의 형식을 가진 함수를 작성해야 한다.
//WhoIsPrecede 함수는 오름차순으로 Point를 정렬하는 함수
//리턴값이 0일시에, 위치를 찾음.
/*
int WhoIsPrecede(Point * d1, Point * d2)
{
	if(d1->xpos < d2->xpos)
	{
		return 0;
	}
	else if(d1->xpos == d2->xpos)
	{ 
		if(d1->ypos < d2->ypos)
			return 0;
		else
			return 1;
	}
	else
		return 1;
}
*/

////////////////////////////////////////////////

//3. Circular Linked List



typedef Data CLData;

typedef struct _cnode
{
	CLData data;
	struct _cnode *next;
} CL_Node;

typedef struct _CLL
{
	CL_Node *tail;   //head 대신 꼬리만 존재, head = tail->next
	CL_Node *cur;    //현재 위치
	CL_Node *before; //현재 이전 위치
	int (*comp)(CLData d1, CLData d2);  //정렬 함수
	int numOfData;  //저장된 자료의 수
} CircularList;

//<초기화함수>
void CListInit(CircularList *plist); 
//인자 : 초기화할 리스트 주소값
//리스트 생성시 최초 1회 호출

//<삽입함수>
void CLInsert(CircularList *plist, CLData data);
//인자 : 리스트 주소값, 삽입할 데이터값
//- 정렬기준 존재시 : SInsert(정렬기준에 따라 삽입)호출 
//- 정렬기준 존재하지 않을 시 : FInsert(맨 앞 삽입)호출

//<LInsert에 의해 호출 되는 삽입함수>
void CFInsert(CircularList *plist, CLData data); //head에 추가
void CSInsert(CircularList *plist, CLData data); //정렬하여 추가
//정렬 기준 : CSetSortRule 함수를 통해 등록.
//주어진 함수를 통해 값을 비교하여
//리턴값이 0일시에 해당위치에 값을 삽입한다.

//<tail에 삽입>
void CTInsert(CircularList *plist, CLData data);
//인자 : 리스트 주소값, 삽입할 데이터값

//<첫번째 값 확인>
int CLFirst(CircularList *plist, CLData *pdata);
//인자 : 리스트 주소값, 값을 받아올 공간
//리턴 : 참조 성공시 1, 실패시 0 반환

//<다음 값 확인> :: LFirst 호출이후 실행한다.
int CLNext(CircularList *plist, CLData * pdata); // 
//인자 : 리스트 주소값, 값을 받아올 공간
//리턴 : 참조 성공시 1, 실패시 0 반환

//<현재 위치값 삭제> :: LFirst와 LNext로 삭제할 위치 찾은뒤 사용
CLData CLRemove(CircularList *plist);
//인자 : 리스트 주소값
//리턴 : 삭제된 데이터값

//<저장된 자료 개수>
int CLCount(CircularList *plist);
//인자 : 리스트 주소값

//<정렬 기준 설정> 
void CSetSortRule(CircularList *plist, int (*comp)(CLData d1, CLData d2));
//인자 : 리스트 주소값, 정렬기준 함수

//정렬 기준을 설정하기 위해서
//main 상단에 다음의 형식을 가진 함수를 작성해야 한다.
//WhoIsPrecede 함수는 오름차순으로 Point를 정렬하는 함수
//리턴값이 0일시에, 위치를 찾음.



















///////////////////////////////////////////////////////////
//4. Double Linked List

typedef Data DLData;

typedef struct _dnode
{
	DLData data;
	struct _dnode *next;
	struct _dnode *prev;
} DL_Node;

typedef struct _dbLinkedList
{
	DL_Node *head;
	DL_Node *tail;
	DL_Node *cur;
	int (*comp)(DLData d1, DLData d2);  //정렬 함수
	int numOfData;
} DBLinkedList;


//<초기화함수>
void DListInit(DBLinkedList *plist); 
//인자 : 초기화할 리스트 주소값
//리스트 생성시 최초 1회 호출

//<삽입함수>
void DLInsert(DBLinkedList *plist, DLData data);
//인자 : 리스트 주소값, 삽입할 데이터값
//- 정렬기준 존재시 : SInsert(정렬기준에 따라 삽입)호출 
//- 정렬기준 존재하지 않을 시 : FInsert(맨 앞 삽입)호출

//<LInsert에 의해 호출 되는 삽입함수>
void DFInsert(DBLinkedList *plist, DLData data); //head에 추가
void DSInsert(DBLinkedList *plist, DLData data); //정렬하여 추가
//정렬 기준 : DSetSortRule 함수를 통해 등록.
//주어진 함수를 통해 값을 비교하여
//리턴값이 0일시에 해당위치에 값을 삽입한다.

//<tail에 삽입>
void DTInsert(DBLinkedList *plist, DLData data);
//인자 : 리스트 주소값, 삽입할 데이터값

//<첫번째 값 확인>
int DLFirst(DBLinkedList *plist, DLData *pdata);
//인자 : 리스트 주소값, 값을 받아올 공간
//리턴 : 참조 성공시 1, 실패시 0 반환

//<다음 값 확인> :: LFirst 호출이후 실행한다.
int DLNext(DBLinkedList *plist, DLData * pdata);
//인자 : 리스트 주소값, 값을 받아올 공간
//리턴 : 참조 성공시 1, 실패시 0 반환

//<이전 값 확인>
int DLPrevious(DBLinkedList * plist, DLData * pdata);
//인자 : 리스트 주소값, 값을 받아올 공간
//리턴 : 참조 성공시 1, 실패시 0 반환

//<현재 위치값 삭제> :: LFirst와 LNext로 삭제할 위치 찾은뒤 사용
DLData DLRemove(DBLinkedList *plist);
//인자 : 리스트 주소값
//리턴 : 삭제된 데이터값

//<저장된 자료 개수>
int DLCount(DBLinkedList *plist);
//인자 : 리스트 주소값

//<정렬 기준 설정> 
void DSetSortRule(DBLinkedList *plist, int (*comp)(DLData d1, DLData d2));
//인자 : 리스트 주소값, 정렬기준 함수

//정렬 기준을 설정하기 위해서
//main 상단에 다음의 형식을 가진 함수를 작성해야 한다.
//WhoIsPrecede 함수는 오름차순으로 Point를 정렬하는 함수
//리턴값이 0일시에, 위치를 찾음.



















///////////////////////////////////////////////////////////
//5. Array Stack


#define STACK_LEN	100			//스택의 크기 설정

typedef Data ASData;				//개별 자료형 설정

typedef struct _arrayStack
{
	ASData stackArr[STACK_LEN];		//스택 생성
	int topIndex;					//스택 top의 인덱스
} ArrayStack;

//<스택 초기화>
void AStackInit(ArrayStack * pstack);
//인자 : 스택 주소

//<스택 EMPTY 확인>
int ASIsEmpty(ArrayStack * pstack);
//스택이 빈경우 TRUE(1) 반환, 그렇지 않은 경우 FALSE(0) 반환

//<스택 삽입>
void ASPush(ArrayStack * pstack, ASData data);
//인자 : 스택주소, 저장할 값
//해당 값을 스택에 삽입.

//<스택 삭제>
ASData ASPop(ArrayStack * pstack);
//마지막 저장된 요소 삭제.
//리턴 : 삭제된 데이터

//<Top인덱스의 데이터 확인>
ASData ASPeek(ArrayStack * pstack);
//리턴 : 저장된 요소 반환



















///////////////////////////////////////////////////////////
//6. List Stack

typedef Data LSData;				//개별 자료형 설정

typedef struct _lsnode
{
	LSData data;					//자료저장공간
	struct _lsnode *next;			//다음노드를 잇는 포인터
} LS_Node;

typedef struct _listStack
{
	LS_Node *top;					//스택 top의 인덱스
} ListStack;

//<스택 초기화>
void LStackInit(ListStack * pstack);
//인자 : 스택 주소

//<스택 EMPTY 확인>
int LSIsEmpty(ListStack * pstack);
//스택이 빈경우 TRUE(1) 반환, 그렇지 않은 경우 FALSE(0) 반환

//<스택 삽입>
void LSPush(ListStack * pstack, LSData data);
//인자 : 스택주소, 저장할 값
//해당 값을 스택에 삽입.

//<스택 삭제>
LSData LSPop(ListStack * pstack);
//마지막 저장된 요소 삭제.
//리턴 : 삭제된 데이터

//<Top인덱스의 데이터 확인>
LSData LSPeek(ListStack * pstack);
//리턴 : 저장된 요소 반환















///////////////////////////////////////////////////////////
//7. Circular Queue
//

#define QUE_LEN	100
typedef Data CQData;

typedef struct _cQueue
{
	int front;				//front의 인덱스, 현재 가리키는 것=삭제 됐다 가정
	int rear;				//rear의 인덱스
	CQData queArr[QUE_LEN];	//큐 생성
} CQueue;

//<원형큐 초기화>
void CQueueInit(CQueue * pq);
//인자 : 원형큐의 포인터 값
//front값과, rear 값을 0으로 초기화.

//<원형큐 Empty여부 확인>
int CQIsEmpty(CQueue * pq);
//인자 : 원형큐의 포인터 값
//리턴 : 비어있을시 == TRUE / 아닐시 FALSE

//<원형큐 삽입>
void CEnqueue(CQueue * pq, CQData data);
//인자 : 원형큐 포인터, 삽입할 데이터값

//<원형큐 삭제>
CQData CDequeue(CQueue * pq);
//인자 : 원형큐 포인터
//리턴 : 삭제한 값 반환
//가장 맨앞  데이터 삭제

//<원형큐 front의 내용확인>
CQData CQPeek(CQueue * pq);
//인자 : 원형큐 포인터
//리턴 : front의 데이터 확인























///////////////////////////////////////////////////////////
//8. List Queue
//

typedef Data LQData;

typedef struct _lsqnode
{
	LQData data;
	struct _lsqnode *next;
} LQ_Node;

typedef struct _lQueue
{
	LQ_Node *front;
	LQ_Node *rear;
} LQueue;


//<리스트 큐 초기화>
void LQueueInit(LQueue * pq);
//front값과, rear 값을 NULL로 초기화.

//<리스트 큐 Empty여부 확인>
int LQIsEmpty(LQueue * pq);
//리턴 : 비어있을시 == TRUE / 아닐시 FALSE

//<데이터 삽입>
void LEnqueue(LQueue * pq, LQData data);
//인자 : 원형큐 포인터, 삽입할 데이터값

//<데이터 삭제>
LQData LDequeue(LQueue * pq);
//리턴 : 삭제한 값 반환
//가장 맨앞  데이터(front) 삭제

//<front의 내용확인>
LQData LQPeek(LQueue * pq);
//리턴 : front의 데이터 확인














///////////////////////////////////////////////////////////
//9. Deque (Double-ended queue)
//

typedef Data DQData;

typedef struct _dqnode
{
	DQData data;
	struct _dqnode *next;
	struct _dqnode *prev;
} DQ_Node;

typedef struct _dDeque
{
	DQ_Node *head;
	DQ_Node *tail;
} Deque;

//<초기화 함수>
void DequeInit(Deque * pdeq);

//<Empty 확인>
int DQIsEmpty(Deque * pdeq);

//<앞에 삽입>
void DQAddFirst(Deque * pdeq, DQData data);
//인자 : 덱의 주소, 삽입할 데이터

//<뒤에 삽입>
void DQAddLast(Deque * pdeq, DQData data);
//인자 : 덱의 주소, 삽입할 데이터

//<앞 삭제>
DQData DQRemoveFirst(Deque * pdeq);
//리턴 : 삭제한 데이터

//<뒤 삭제>
DQData DQRemoveLast(Deque * pdeq);
//리턴 : 삭제한 데이터

//<front값 확인>
DQData DQGetFirst(Deque * pdeq);
//리턴 : 확인할 데이터

//<rear값 확인>
DQData DQGetLast(Deque * pdeq);
//리턴 : 확인할 데이터























///////////////////////////////////////////////////////////
//10. Binary Tree
//

typedef Data BTData;

typedef struct _bTreeNode
{
	BTData data;
	struct _bTreeNode *left;
	struct _bTreeNode *right;
} BT_Node;

//<이진트리 노드 생성함수>
BT_Node * MakeBTreeNode(void);
//리턴 : 생성된 이진트리의 주소값
//BT_Node * bt1 = MakeBTreeNode(); 식으로 생성

//<데이터 얻기>
BTData GetData(BT_Node * bt);
//리턴 : 해당 노드에 저장된 데이터 반환

//<데이터 저장>
void SetData(BT_Node * bt, BTData data);
//인자 : 노드의 주소값, 저장할 데이터

//<왼쪽 서브트리의 주소값 반환>
BT_Node * GetLeftSubTree(BT_Node * bt);

//<오른쪽 서브트리의 주소값 반환>
BT_Node * GetRightSubTree(BT_Node * bt);

//<왼쪽 서브트리를 연결>
void MakeLeftSubTree(BT_Node * main, BT_Node * sub);
//인자 : 메인 노드, 서브트리 노드

//<오른쪽 서브트리를 연결>
void MakeRightSubTree(BT_Node * main, BT_Node * sub);
//인자 : 메인 노드, 서브트리 노드

//함수 포인터 선언
typedef void VisitFuncPtr(BTData   data);

//<전위 탐색>
void PreorderTraverse(BT_Node * bt, VisitFuncPtr action);
//인자 : 탐색 시작 노드, 방문한 노드에서 실행할 함수
//사용법 아래와 같은 형태의 함수 main에 선언해주고, 인자에 넣음
/*
void ShowIntData(int data)
{
	printf("%d ", data);
}
*/

//<중위 탐색>
void InorderTraverse(BT_Node * bt, VisitFuncPtr action);
//인자 : 탐색 시작 노드, 방문한 노드에서 실행할 함수

//<후위 탐색>
void PostorderTraverse(BT_Node * bt, VisitFuncPtr action);
//인자 : 탐색 시작 노드, 방문한 노드에서 실행할 함수

//<이진트리 소멸 함수>
void DeleteTree(BT_Node * bt);

//<왼쪽 자식 노드 제거>
BT_Node * RemoveLeftSubTree(BT_Node *bt);
//리턴 : 제거된 노드의 주소 값이 반환

//<오른쪽 자식 노드 제거>
BT_Node* RemoveRightSubTree(BT_Node *bt);
//리턴 : 제거된 노드의 주소 값이 반환

//<왼쪽 자식 노드 변경>
void ChangeLeftSubTree(BT_Node* main, BT_Node *sub);
//인자 : 변경될 대상, 변경할 값

//<오른쪽 자식 노드 변경>
void ChangeRightSubTree(BT_Node* main, BT_Node *sub);
//인자 : 변경될 대상, 변경할 값
























//////////////////////////////////////////////////
// 11. Binary Search Tree

typedef BTData BSTData;

//<이진 탐색트리 생성 및 초기화>
void BSTMakeAndInit(BT_Node ** pRoot);

//<노드에 저장된 데이터 반환>
BSTData BSTGetNodeData(BT_Node *bst);

//<데이터 삽입>
void BSTInsert(BT_Node **pRoot, BSTData data);

//<데이터 탐색>
BT_Node *BSTSearch(BT_Node *bst, BSTData target);
//리턴 : 찾았을 시, 노드의 주소 못찾았을 시 NULL 리턴

//<데이터 삭제>
BT_Node *BSTRemove(BT_Node **pRoot, BSTData target);
//리턴 : 삭제할 노드 존재시, 삭제한 노드 리턴, 없을시 NULL 리턴

//<데이터 출력>
void BSTShowAll(BT_Node *bst);























////////////////////////////////////////////////////
//12. AVL Tree

// 트리의 균형을 잡는다.
BT_Node * Rebalance(BT_Node ** pRoot);



















///////////////////////////////////////////////////////////
//13. Priority Queue
//

////////// heap
#define HEAP_LEN	100

typedef int HData;		//힙에 저장할 자료형 설정
typedef int PriorityComp(HData d1, HData d2); //힙의 우선순위 비교함수

typedef struct _heap
{
	PriorityComp *comp;
	int numOfData;
	HData heapArr[HEAP_LEN];
} Heap;

//<우선순위 비교함수 등록>
void HeapInit(Heap *ph, PriorityComp pc);
/*
int DataPriorityComp(char ch1, char ch2)
{
	return ch2-ch1; //사전식배열
//	return ch1-ch2;/
}
*/

//<힙의 Empty 여부 확인>
int HIsEmpty(Heap *ph);
//리턴 : 비어있을 경우 TRUE

//<삽입 함수>
void HInsert(Heap *ph, HData data);

//<삭제 함수>
HData HDelete(Heap *ph);
//리턴 : 삭제한 함수

///////////Priority Queue

typedef Heap PQueue;
typedef HData PQData;

//<초기화 함수>
void PQueueInit(PQueue * ppq, PriorityComp pc);
//인자 : 우선순위 큐의 주소, 비교함수

//<empty여부 확인>
int PQIsEmpty(PQueue * ppq);
//리턴 : 비어있을 시 1

//<우선순위 큐에 데이터 저장>
void PEnqueue(PQueue * ppq, PQData data);
//인자 : 우선순위 큐의 주소, 저장할 데이터

//<데이터 삭제>
PQData PDequeue(PQueue * ppq);
//인자 : 우선순위 큐의 주소
//리턴 : 삭제한 데이터 반환



























//////////////////////////////////////////////////
//14. Hash Table


//// TABLE에 들어가는 자료형 선언
typedef int Key;		//key값을 int로 설정
typedef char* Value;	//value값을 문자열(char*)로 설정

enum SlotStatus { EMPTY, DELETED, INUSE };

typedef struct __slot
{
	Key key;
	Value val;
	enum SlotStatus status;
}Slot;	//Table에 들어가는 자료유형

//*패키지 째로 이용하려면 주석을 풀지 말것!!!!
//*단독 사용시에만 주석을 풀것
//*패키지 째로 이용하려면 주석을 풀지 말것!!!!




/// 실제 TABLE
#define MAX_TBL	100		//TABLE 최대 자료 갯수
typedef int HashFunc(Key k);	//1차 해쉬함수 포인터

typedef struct _table
{
	Slot tb[MAX_TBL];  
	HashFunc *hf;
}Table;

//<테이블 초기화>
void TBInit(Table *pt, HashFunc *f);
//main에 해쉬 함수 구현해 놓고, TBInit(&myTbl, MyHashFunc)로 등록.
/*ex
int MyHashFunc(int k)
{
	return k % 100;    // 키를 부분적으로만 사용한 별로 좋지 않은 해쉬의 예!!!
}
*/

//<테이블에 키와 값을 저장>
void TBInsert(Table *pt, Key k, Value v);

//<데이터 삭제>
Value TBDelete(Table *pt, Key k);
//리턴 : 삭제 성공시-삭제한 값/ 데이터 존재하지 않을시 NULL

//<데이터 탐색>
Value TBSearch(Table *pt, Key k);
//리턴 : 탐색 성공시-찾은 값/ 데이터 존재하지 않을시 NULL
























/////////////////////////////////////////////
//15. Chaining


//별도의 헤더파일 사용
//Chinag.h Chaing.c Slot.h Slot.c + DSPackege를 모두 사용.

////////////////////////////////////////////






















///////////////////////////////////////////////
//16. ListBaseGraph

enum {A, B, C, D, E, F, G, H, I, J};	//정점의 이름을 상수화
//enum {SEOUL, INCHEON, DAEGU, BUSAN, KWANGJU };

typedef struct _ual
{
	int numV;				//정점의 수
	int numE;				//간선의 수
	LinkedList *adjList;	//간선의 정보
	int *visitInfo;			//방문 여부 확인
} LGraph;

// 그래프의 초기화
void LGraphInit(LGraph *pg, int nv);
//인자 : 그래프의 주소, nv = "정점의 수" 전달

//그래프의 리소스를 해제
void LGraphDestroy(LGraph *pg);

//간선의 추가
void LAddEdge(LGraph *pg, int fromV, int toV);
//인자 : 그래프 주소, fromV와 toV로 전달된 정점을 연결하는 간선 추가

//유틸리티 함수 : 간선의 정보 출력
void ShowLGraphEdgeInfo(LGraph *pg);

// Depth First Search : 정점의 정보 출력
void DFShowGraphVertex(LGraph *pg, int startV);
//인자 : 그래프주소, 탐색을 시작할 정점

// Breadth First Search : 정점의 정보 출력
void BFShowGraphVertex(LGraph *pg, int startV);
//인자 : 그래프주소, 탐색을 시작할 정점

























///////////////////////////////////////////////////////////////////////
//17. Minimum cost Spanning Tree : Kruskal algorithm

//별도의 헤더파일 사용
//WEdge.h Kruskal.h Kruskal.c + DSPackege를 모두 사용.

///////////////////////////////////////////////////////////////////////