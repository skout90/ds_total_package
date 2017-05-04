/*
################################
	Data Structure Packege
	�ڷᱸ�� ����
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
		15) Chaining(�߰� ��� ������ ���)
	- Graph
		16) List Base Graph
	- Minimum cost Spanning Tree
		17) Kruskal algorithm(�߰���� ������ ���)

	Language : C
	������ : ȫ�ʹ��б� ����ȣ
	���� : �������� ���� �ڷᱸ��
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


// ���ϴ� �ڷᱸ�� ������ include �ϼ���.
//#include "Point.h"  

// ��ü �⺻ �ڷ����� ����
typedef int Data;
//typedef Point * Data;


//////////////////////////////////////////////////////////

// 1. ArrayList

#define LENGTH 100 //�����ڷᱸ���� ��� ���� ����
typedef Data ALData; //��ü �⺻ �ڷ������� �ٸ� ��� �߰�����

typedef struct __ArrayList
{
	ALData arr[LENGTH];
	int numOfData;     //�ڷ� �� ����
	int curPosition;   //�ε���
} ArrayList;



//<�ʱ�ȭ�Լ�>
void AListInit(ArrayList *plist); 
//���� : �ʱ�ȭ�� ����Ʈ �ּҰ�
//����Ʈ ������ ���� 1ȸ ȣ��

//<�ǵ� �����Լ�>
void ALInsert(ArrayList *plist, ALData data); // �� �� ����
//���� : ����Ʈ �ּҰ�, ������ �����Ͱ�

//<ù��° �� Ȯ��>
int ALFirst(ArrayList *plist, ALData *pdata);
//���� : //���� : ����Ʈ �ּҰ�, ù��° ���� �޾ƿ� ����
//���� : ���� ������ 1, ���н� 0 ��ȯ

//<���� �� Ȯ��> :: ALFirst ȣ������ �����Ѵ�.
int ALNext(ArrayList *plist, ALData * pdata); // 
//���� : ����Ʈ �ּҰ�, ���� �޾ƿ� ����
//���� : ���� ������ 1, ���н� 0 ��ȯ

//<���� ��ġ�� ����> :: ALFirst�� ALNext�� ������ ��ġ ã���� ���
ALData ALRemove(ArrayList *plist);
//���� : ����Ʈ �ּҰ�
//���� : ������ �����Ͱ�

//<����� �ڷ� ����>
int ALCount(ArrayList *plist);
//���� : ����Ʈ �ּҰ�






//////////////////////////////////////////////////////

// 2. LinkedList

typedef Data LData; //��ü �⺻ �ڷ������� �ٸ� ��� �߰�����
//typedef CSlot LData;	//Chaning ���� ���.

typedef struct _node
{
	LData data;				//������ ����
	struct _node *next;		//���� ��ũ �ּ�
} SL_Node;

typedef struct _linkedList
{
	SL_Node * head;					// �� �� �ּ�
	SL_Node * tail;					// �� �� �ּ�
	SL_Node * cur;					// ���� ��� ��ġ
	SL_Node * before;				// ���� �ٷ� ���� ���
	int numOfData;					
	int (*comp)(LData d1, LData d2);  //���� �Լ�
} LinkedList;

//<�ʱ�ȭ�Լ�>
void ListInit(LinkedList *plist); 
//���� : �ʱ�ȭ�� ����Ʈ �ּҰ�
//���̳�� ����(head)
//����Ʈ ������ ���� 1ȸ ȣ��

//<�����Լ�>
void LInsert(LinkedList *plist, LData data);
//���� : ����Ʈ �ּҰ�, ������ �����Ͱ�
//- ���ı��� ����� : SInsert(���ı��ؿ� ���� ����)ȣ�� 
//- ���ı��� �������� ���� �� : FInsert(�� �� ����)ȣ��

//<LInsert�� ���� ȣ�� �Ǵ� �����Լ�>
void FInsert(LinkedList *plist, LData data); //head�� �߰�
void SInsert(LinkedList *plist, LData data); //�����Ͽ� �߰�
//���� ���� : SetSortRule �Լ��� ���� ���.
//�־��� �Լ��� ���� ���� ���Ͽ�
//���ϰ��� 0�Ͻÿ� �ش���ġ�� ���� �����Ѵ�.

//<tail�� ����>
void TInsert(LinkedList * plist, LData data);
//���� : ����Ʈ �ּҰ�, ������ �����Ͱ�

//<ù��° �� Ȯ��>
int LFirst(LinkedList *plist, LData *pdata);
//���� : ����Ʈ �ּҰ�, ���� �޾ƿ� ����
//���� : ���� ������ 1, ���н� 0 ��ȯ

//<���� �� Ȯ��> :: LFirst ȣ������ �����Ѵ�.
int LNext(LinkedList *plist, LData * pdata); // 
//���� : ����Ʈ �ּҰ�, ���� �޾ƿ� ����
//���� : ���� ������ 1, ���н� 0 ��ȯ

//<���� ��ġ�� ����> :: LFirst�� LNext�� ������ ��ġ ã���� ���
LData LRemove(LinkedList *plist);
//���� : ����Ʈ �ּҰ�
//���� : ������ �����Ͱ�

//<����� �ڷ� ����>
int LCount(LinkedList *plist);
//���� : ����Ʈ �ּҰ�

//<���� ���� ����> 
void SetSortRule(LinkedList *plist, int (*comp)(LData d1, LData d2));
//���� : ����Ʈ �ּҰ�, ���ı��� �Լ�

//���� ������ �����ϱ� ���ؼ�
//main ��ܿ� ������ ������ ���� �Լ��� �ۼ��ؾ� �Ѵ�.
//WhoIsPrecede �Լ��� ������������ Point�� �����ϴ� �Լ�
//���ϰ��� 0�Ͻÿ�, ��ġ�� ã��.
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
	CL_Node *tail;   //head ��� ������ ����, head = tail->next
	CL_Node *cur;    //���� ��ġ
	CL_Node *before; //���� ���� ��ġ
	int (*comp)(CLData d1, CLData d2);  //���� �Լ�
	int numOfData;  //����� �ڷ��� ��
} CircularList;

//<�ʱ�ȭ�Լ�>
void CListInit(CircularList *plist); 
//���� : �ʱ�ȭ�� ����Ʈ �ּҰ�
//����Ʈ ������ ���� 1ȸ ȣ��

//<�����Լ�>
void CLInsert(CircularList *plist, CLData data);
//���� : ����Ʈ �ּҰ�, ������ �����Ͱ�
//- ���ı��� ����� : SInsert(���ı��ؿ� ���� ����)ȣ�� 
//- ���ı��� �������� ���� �� : FInsert(�� �� ����)ȣ��

//<LInsert�� ���� ȣ�� �Ǵ� �����Լ�>
void CFInsert(CircularList *plist, CLData data); //head�� �߰�
void CSInsert(CircularList *plist, CLData data); //�����Ͽ� �߰�
//���� ���� : CSetSortRule �Լ��� ���� ���.
//�־��� �Լ��� ���� ���� ���Ͽ�
//���ϰ��� 0�Ͻÿ� �ش���ġ�� ���� �����Ѵ�.

//<tail�� ����>
void CTInsert(CircularList *plist, CLData data);
//���� : ����Ʈ �ּҰ�, ������ �����Ͱ�

//<ù��° �� Ȯ��>
int CLFirst(CircularList *plist, CLData *pdata);
//���� : ����Ʈ �ּҰ�, ���� �޾ƿ� ����
//���� : ���� ������ 1, ���н� 0 ��ȯ

//<���� �� Ȯ��> :: LFirst ȣ������ �����Ѵ�.
int CLNext(CircularList *plist, CLData * pdata); // 
//���� : ����Ʈ �ּҰ�, ���� �޾ƿ� ����
//���� : ���� ������ 1, ���н� 0 ��ȯ

//<���� ��ġ�� ����> :: LFirst�� LNext�� ������ ��ġ ã���� ���
CLData CLRemove(CircularList *plist);
//���� : ����Ʈ �ּҰ�
//���� : ������ �����Ͱ�

//<����� �ڷ� ����>
int CLCount(CircularList *plist);
//���� : ����Ʈ �ּҰ�

//<���� ���� ����> 
void CSetSortRule(CircularList *plist, int (*comp)(CLData d1, CLData d2));
//���� : ����Ʈ �ּҰ�, ���ı��� �Լ�

//���� ������ �����ϱ� ���ؼ�
//main ��ܿ� ������ ������ ���� �Լ��� �ۼ��ؾ� �Ѵ�.
//WhoIsPrecede �Լ��� ������������ Point�� �����ϴ� �Լ�
//���ϰ��� 0�Ͻÿ�, ��ġ�� ã��.



















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
	int (*comp)(DLData d1, DLData d2);  //���� �Լ�
	int numOfData;
} DBLinkedList;


//<�ʱ�ȭ�Լ�>
void DListInit(DBLinkedList *plist); 
//���� : �ʱ�ȭ�� ����Ʈ �ּҰ�
//����Ʈ ������ ���� 1ȸ ȣ��

//<�����Լ�>
void DLInsert(DBLinkedList *plist, DLData data);
//���� : ����Ʈ �ּҰ�, ������ �����Ͱ�
//- ���ı��� ����� : SInsert(���ı��ؿ� ���� ����)ȣ�� 
//- ���ı��� �������� ���� �� : FInsert(�� �� ����)ȣ��

//<LInsert�� ���� ȣ�� �Ǵ� �����Լ�>
void DFInsert(DBLinkedList *plist, DLData data); //head�� �߰�
void DSInsert(DBLinkedList *plist, DLData data); //�����Ͽ� �߰�
//���� ���� : DSetSortRule �Լ��� ���� ���.
//�־��� �Լ��� ���� ���� ���Ͽ�
//���ϰ��� 0�Ͻÿ� �ش���ġ�� ���� �����Ѵ�.

//<tail�� ����>
void DTInsert(DBLinkedList *plist, DLData data);
//���� : ����Ʈ �ּҰ�, ������ �����Ͱ�

//<ù��° �� Ȯ��>
int DLFirst(DBLinkedList *plist, DLData *pdata);
//���� : ����Ʈ �ּҰ�, ���� �޾ƿ� ����
//���� : ���� ������ 1, ���н� 0 ��ȯ

//<���� �� Ȯ��> :: LFirst ȣ������ �����Ѵ�.
int DLNext(DBLinkedList *plist, DLData * pdata);
//���� : ����Ʈ �ּҰ�, ���� �޾ƿ� ����
//���� : ���� ������ 1, ���н� 0 ��ȯ

//<���� �� Ȯ��>
int DLPrevious(DBLinkedList * plist, DLData * pdata);
//���� : ����Ʈ �ּҰ�, ���� �޾ƿ� ����
//���� : ���� ������ 1, ���н� 0 ��ȯ

//<���� ��ġ�� ����> :: LFirst�� LNext�� ������ ��ġ ã���� ���
DLData DLRemove(DBLinkedList *plist);
//���� : ����Ʈ �ּҰ�
//���� : ������ �����Ͱ�

//<����� �ڷ� ����>
int DLCount(DBLinkedList *plist);
//���� : ����Ʈ �ּҰ�

//<���� ���� ����> 
void DSetSortRule(DBLinkedList *plist, int (*comp)(DLData d1, DLData d2));
//���� : ����Ʈ �ּҰ�, ���ı��� �Լ�

//���� ������ �����ϱ� ���ؼ�
//main ��ܿ� ������ ������ ���� �Լ��� �ۼ��ؾ� �Ѵ�.
//WhoIsPrecede �Լ��� ������������ Point�� �����ϴ� �Լ�
//���ϰ��� 0�Ͻÿ�, ��ġ�� ã��.



















///////////////////////////////////////////////////////////
//5. Array Stack


#define STACK_LEN	100			//������ ũ�� ����

typedef Data ASData;				//���� �ڷ��� ����

typedef struct _arrayStack
{
	ASData stackArr[STACK_LEN];		//���� ����
	int topIndex;					//���� top�� �ε���
} ArrayStack;

//<���� �ʱ�ȭ>
void AStackInit(ArrayStack * pstack);
//���� : ���� �ּ�

//<���� EMPTY Ȯ��>
int ASIsEmpty(ArrayStack * pstack);
//������ ���� TRUE(1) ��ȯ, �׷��� ���� ��� FALSE(0) ��ȯ

//<���� ����>
void ASPush(ArrayStack * pstack, ASData data);
//���� : �����ּ�, ������ ��
//�ش� ���� ���ÿ� ����.

//<���� ����>
ASData ASPop(ArrayStack * pstack);
//������ ����� ��� ����.
//���� : ������ ������

//<Top�ε����� ������ Ȯ��>
ASData ASPeek(ArrayStack * pstack);
//���� : ����� ��� ��ȯ



















///////////////////////////////////////////////////////////
//6. List Stack

typedef Data LSData;				//���� �ڷ��� ����

typedef struct _lsnode
{
	LSData data;					//�ڷ��������
	struct _lsnode *next;			//������带 �մ� ������
} LS_Node;

typedef struct _listStack
{
	LS_Node *top;					//���� top�� �ε���
} ListStack;

//<���� �ʱ�ȭ>
void LStackInit(ListStack * pstack);
//���� : ���� �ּ�

//<���� EMPTY Ȯ��>
int LSIsEmpty(ListStack * pstack);
//������ ���� TRUE(1) ��ȯ, �׷��� ���� ��� FALSE(0) ��ȯ

//<���� ����>
void LSPush(ListStack * pstack, LSData data);
//���� : �����ּ�, ������ ��
//�ش� ���� ���ÿ� ����.

//<���� ����>
LSData LSPop(ListStack * pstack);
//������ ����� ��� ����.
//���� : ������ ������

//<Top�ε����� ������ Ȯ��>
LSData LSPeek(ListStack * pstack);
//���� : ����� ��� ��ȯ















///////////////////////////////////////////////////////////
//7. Circular Queue
//

#define QUE_LEN	100
typedef Data CQData;

typedef struct _cQueue
{
	int front;				//front�� �ε���, ���� ����Ű�� ��=���� �ƴ� ����
	int rear;				//rear�� �ε���
	CQData queArr[QUE_LEN];	//ť ����
} CQueue;

//<����ť �ʱ�ȭ>
void CQueueInit(CQueue * pq);
//���� : ����ť�� ������ ��
//front����, rear ���� 0���� �ʱ�ȭ.

//<����ť Empty���� Ȯ��>
int CQIsEmpty(CQueue * pq);
//���� : ����ť�� ������ ��
//���� : ��������� == TRUE / �ƴҽ� FALSE

//<����ť ����>
void CEnqueue(CQueue * pq, CQData data);
//���� : ����ť ������, ������ �����Ͱ�

//<����ť ����>
CQData CDequeue(CQueue * pq);
//���� : ����ť ������
//���� : ������ �� ��ȯ
//���� �Ǿ�  ������ ����

//<����ť front�� ����Ȯ��>
CQData CQPeek(CQueue * pq);
//���� : ����ť ������
//���� : front�� ������ Ȯ��























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


//<����Ʈ ť �ʱ�ȭ>
void LQueueInit(LQueue * pq);
//front����, rear ���� NULL�� �ʱ�ȭ.

//<����Ʈ ť Empty���� Ȯ��>
int LQIsEmpty(LQueue * pq);
//���� : ��������� == TRUE / �ƴҽ� FALSE

//<������ ����>
void LEnqueue(LQueue * pq, LQData data);
//���� : ����ť ������, ������ �����Ͱ�

//<������ ����>
LQData LDequeue(LQueue * pq);
//���� : ������ �� ��ȯ
//���� �Ǿ�  ������(front) ����

//<front�� ����Ȯ��>
LQData LQPeek(LQueue * pq);
//���� : front�� ������ Ȯ��














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

//<�ʱ�ȭ �Լ�>
void DequeInit(Deque * pdeq);

//<Empty Ȯ��>
int DQIsEmpty(Deque * pdeq);

//<�տ� ����>
void DQAddFirst(Deque * pdeq, DQData data);
//���� : ���� �ּ�, ������ ������

//<�ڿ� ����>
void DQAddLast(Deque * pdeq, DQData data);
//���� : ���� �ּ�, ������ ������

//<�� ����>
DQData DQRemoveFirst(Deque * pdeq);
//���� : ������ ������

//<�� ����>
DQData DQRemoveLast(Deque * pdeq);
//���� : ������ ������

//<front�� Ȯ��>
DQData DQGetFirst(Deque * pdeq);
//���� : Ȯ���� ������

//<rear�� Ȯ��>
DQData DQGetLast(Deque * pdeq);
//���� : Ȯ���� ������























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

//<����Ʈ�� ��� �����Լ�>
BT_Node * MakeBTreeNode(void);
//���� : ������ ����Ʈ���� �ּҰ�
//BT_Node * bt1 = MakeBTreeNode(); ������ ����

//<������ ���>
BTData GetData(BT_Node * bt);
//���� : �ش� ��忡 ����� ������ ��ȯ

//<������ ����>
void SetData(BT_Node * bt, BTData data);
//���� : ����� �ּҰ�, ������ ������

//<���� ����Ʈ���� �ּҰ� ��ȯ>
BT_Node * GetLeftSubTree(BT_Node * bt);

//<������ ����Ʈ���� �ּҰ� ��ȯ>
BT_Node * GetRightSubTree(BT_Node * bt);

//<���� ����Ʈ���� ����>
void MakeLeftSubTree(BT_Node * main, BT_Node * sub);
//���� : ���� ���, ����Ʈ�� ���

//<������ ����Ʈ���� ����>
void MakeRightSubTree(BT_Node * main, BT_Node * sub);
//���� : ���� ���, ����Ʈ�� ���

//�Լ� ������ ����
typedef void VisitFuncPtr(BTData   data);

//<���� Ž��>
void PreorderTraverse(BT_Node * bt, VisitFuncPtr action);
//���� : Ž�� ���� ���, �湮�� ��忡�� ������ �Լ�
//���� �Ʒ��� ���� ������ �Լ� main�� �������ְ�, ���ڿ� ����
/*
void ShowIntData(int data)
{
	printf("%d ", data);
}
*/

//<���� Ž��>
void InorderTraverse(BT_Node * bt, VisitFuncPtr action);
//���� : Ž�� ���� ���, �湮�� ��忡�� ������ �Լ�

//<���� Ž��>
void PostorderTraverse(BT_Node * bt, VisitFuncPtr action);
//���� : Ž�� ���� ���, �湮�� ��忡�� ������ �Լ�

//<����Ʈ�� �Ҹ� �Լ�>
void DeleteTree(BT_Node * bt);

//<���� �ڽ� ��� ����>
BT_Node * RemoveLeftSubTree(BT_Node *bt);
//���� : ���ŵ� ����� �ּ� ���� ��ȯ

//<������ �ڽ� ��� ����>
BT_Node* RemoveRightSubTree(BT_Node *bt);
//���� : ���ŵ� ����� �ּ� ���� ��ȯ

//<���� �ڽ� ��� ����>
void ChangeLeftSubTree(BT_Node* main, BT_Node *sub);
//���� : ����� ���, ������ ��

//<������ �ڽ� ��� ����>
void ChangeRightSubTree(BT_Node* main, BT_Node *sub);
//���� : ����� ���, ������ ��
























//////////////////////////////////////////////////
// 11. Binary Search Tree

typedef BTData BSTData;

//<���� Ž��Ʈ�� ���� �� �ʱ�ȭ>
void BSTMakeAndInit(BT_Node ** pRoot);

//<��忡 ����� ������ ��ȯ>
BSTData BSTGetNodeData(BT_Node *bst);

//<������ ����>
void BSTInsert(BT_Node **pRoot, BSTData data);

//<������ Ž��>
BT_Node *BSTSearch(BT_Node *bst, BSTData target);
//���� : ã���� ��, ����� �ּ� ��ã���� �� NULL ����

//<������ ����>
BT_Node *BSTRemove(BT_Node **pRoot, BSTData target);
//���� : ������ ��� �����, ������ ��� ����, ������ NULL ����

//<������ ���>
void BSTShowAll(BT_Node *bst);























////////////////////////////////////////////////////
//12. AVL Tree

// Ʈ���� ������ ��´�.
BT_Node * Rebalance(BT_Node ** pRoot);



















///////////////////////////////////////////////////////////
//13. Priority Queue
//

////////// heap
#define HEAP_LEN	100

typedef int HData;		//���� ������ �ڷ��� ����
typedef int PriorityComp(HData d1, HData d2); //���� �켱���� ���Լ�

typedef struct _heap
{
	PriorityComp *comp;
	int numOfData;
	HData heapArr[HEAP_LEN];
} Heap;

//<�켱���� ���Լ� ���>
void HeapInit(Heap *ph, PriorityComp pc);
/*
int DataPriorityComp(char ch1, char ch2)
{
	return ch2-ch1; //�����Ĺ迭
//	return ch1-ch2;/
}
*/

//<���� Empty ���� Ȯ��>
int HIsEmpty(Heap *ph);
//���� : ������� ��� TRUE

//<���� �Լ�>
void HInsert(Heap *ph, HData data);

//<���� �Լ�>
HData HDelete(Heap *ph);
//���� : ������ �Լ�

///////////Priority Queue

typedef Heap PQueue;
typedef HData PQData;

//<�ʱ�ȭ �Լ�>
void PQueueInit(PQueue * ppq, PriorityComp pc);
//���� : �켱���� ť�� �ּ�, ���Լ�

//<empty���� Ȯ��>
int PQIsEmpty(PQueue * ppq);
//���� : ������� �� 1

//<�켱���� ť�� ������ ����>
void PEnqueue(PQueue * ppq, PQData data);
//���� : �켱���� ť�� �ּ�, ������ ������

//<������ ����>
PQData PDequeue(PQueue * ppq);
//���� : �켱���� ť�� �ּ�
//���� : ������ ������ ��ȯ



























//////////////////////////////////////////////////
//14. Hash Table


//// TABLE�� ���� �ڷ��� ����
typedef int Key;		//key���� int�� ����
typedef char* Value;	//value���� ���ڿ�(char*)�� ����

enum SlotStatus { EMPTY, DELETED, INUSE };

typedef struct __slot
{
	Key key;
	Value val;
	enum SlotStatus status;
}Slot;	//Table�� ���� �ڷ�����

//*��Ű�� °�� �̿��Ϸ��� �ּ��� Ǯ�� ����!!!!
//*�ܵ� ���ÿ��� �ּ��� Ǯ��
//*��Ű�� °�� �̿��Ϸ��� �ּ��� Ǯ�� ����!!!!




/// ���� TABLE
#define MAX_TBL	100		//TABLE �ִ� �ڷ� ����
typedef int HashFunc(Key k);	//1�� �ؽ��Լ� ������

typedef struct _table
{
	Slot tb[MAX_TBL];  
	HashFunc *hf;
}Table;

//<���̺� �ʱ�ȭ>
void TBInit(Table *pt, HashFunc *f);
//main�� �ؽ� �Լ� ������ ����, TBInit(&myTbl, MyHashFunc)�� ���.
/*ex
int MyHashFunc(int k)
{
	return k % 100;    // Ű�� �κ������θ� ����� ���� ���� ���� �ؽ��� ��!!!
}
*/

//<���̺� Ű�� ���� ����>
void TBInsert(Table *pt, Key k, Value v);

//<������ ����>
Value TBDelete(Table *pt, Key k);
//���� : ���� ������-������ ��/ ������ �������� ������ NULL

//<������ Ž��>
Value TBSearch(Table *pt, Key k);
//���� : Ž�� ������-ã�� ��/ ������ �������� ������ NULL
























/////////////////////////////////////////////
//15. Chaining


//������ ������� ���
//Chinag.h Chaing.c Slot.h Slot.c + DSPackege�� ��� ���.

////////////////////////////////////////////






















///////////////////////////////////////////////
//16. ListBaseGraph

enum {A, B, C, D, E, F, G, H, I, J};	//������ �̸��� ���ȭ
//enum {SEOUL, INCHEON, DAEGU, BUSAN, KWANGJU };

typedef struct _ual
{
	int numV;				//������ ��
	int numE;				//������ ��
	LinkedList *adjList;	//������ ����
	int *visitInfo;			//�湮 ���� Ȯ��
} LGraph;

// �׷����� �ʱ�ȭ
void LGraphInit(LGraph *pg, int nv);
//���� : �׷����� �ּ�, nv = "������ ��" ����

//�׷����� ���ҽ��� ����
void LGraphDestroy(LGraph *pg);

//������ �߰�
void LAddEdge(LGraph *pg, int fromV, int toV);
//���� : �׷��� �ּ�, fromV�� toV�� ���޵� ������ �����ϴ� ���� �߰�

//��ƿ��Ƽ �Լ� : ������ ���� ���
void ShowLGraphEdgeInfo(LGraph *pg);

// Depth First Search : ������ ���� ���
void DFShowGraphVertex(LGraph *pg, int startV);
//���� : �׷����ּ�, Ž���� ������ ����

// Breadth First Search : ������ ���� ���
void BFShowGraphVertex(LGraph *pg, int startV);
//���� : �׷����ּ�, Ž���� ������ ����

























///////////////////////////////////////////////////////////////////////
//17. Minimum cost Spanning Tree : Kruskal algorithm

//������ ������� ���
//WEdge.h Kruskal.h Kruskal.c + DSPackege�� ��� ���.

///////////////////////////////////////////////////////////////////////