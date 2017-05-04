#include "DSPackege.h"

///////////////////////////////////////////////////////
///////////////////////////////////////////////////////
//���� �Լ� ����
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






//1. ArrayList
void AListInit(ArrayList *plist)
{ 
	plist->numOfData = 0;     //���� �ڷ� ���� 0 ���� �ʱ�ȭ
	plist->curPosition = -1;  //�ڷ� �����Ƿ� �ε��� = -1
}
void ALInsert(ArrayList *plist, ALData data)
{
	if(plist->numOfData > LENGTH) // �ڷ� ������ ���밡��ġ �ʰ���
	{
		puts("�ڷ� ������ ���밡��ġ�� �ʰ��Ͽ����ϴ�.");
		return;
	}

	plist->arr[plist->numOfData] = data; //�� �ڿ� �ڷ� ����
	(plist->numOfData)++;				 //�ڷᰳ���� ++
}

int ALFirst(ArrayList *plist, ALData *pdata)
{
	if(plist->numOfData == 0)	//�ڷ� ������ ���� 0
		return FALSE;
	
	plist->curPosition = 0;     //�ε��� 0���� ����
	*pdata = plist->arr[0];     //pdata�� ù��° �� ����.
	return TRUE;
}
int ALNext(ArrayList *plist, ALData * pdata)
{
	if(plist->curPosition >= (plist->numOfData)-1) 
		return FALSE;	//���̻� ������ �����Ͱ� ����

	(plist->curPosition)++; //�ε����� ++
	*pdata = plist->arr[plist->curPosition]; //pdata�� ���� ����
	return TRUE;
}

ALData ALRemove(ArrayList *plist)
{
	int rpos = plist->curPosition; //���� �ε��� ����
	int num = plist->numOfData;    //���� �ڷᰳ�� ����
	int i;
	ALData rdata = plist->arr[rpos]; //������ ���� �����صд�.

	for(i=rpos; i<num-1; i++)
		plist->arr[i] = plist->arr[i+1]; //�� ��ġ(rpos)���� ��ĭ�� ����.
	
	(plist->numOfData)--;
	(plist->curPosition)--;
	return rdata;//������ �� ����
}

int ALCount(ArrayList *plist)
{
	return plist->numOfData;
}




























////////////////////////////////////////////////////
//2.LinkedList

void ListInit(LinkedList *plist) 
{
	plist->head = (SL_Node*)malloc(sizeof(SL_Node));
	//���̳�� ����:����? ���� �� ��ȸ ���� �ϰ��ǰ� ����
	//���̳�� ���ٸ� ���� ��� ������ ���� �ٸ��� ó���ؾ�
	plist->head->next = NULL;
	plist->tail = plist->head;
	plist->comp = NULL;
	plist->numOfData = 0;
}

void LInsert(LinkedList *plist, LData data)
{
	if(plist->comp == NULL) //���� ������ ���ٸ�
		FInsert(plist, data); //�Ӹ��� ��� �߰�.
	else	//���� ������ ���õǾ��ٸ�
		SInsert(plist, data);	//���� ���ؿ� �ٰ� ����߰�
}

void FInsert(LinkedList *plist, LData data)
{
	SL_Node * newNode = (SL_Node *)malloc(sizeof(SL_Node));
	//�ܹ��� ��ũ����Ʈ�� ��带 ���� ����
	newNode->data = data; // ���� ����

	if(plist->head->next == NULL) //���ʻ����̶��
		plist->tail = newNode;	  //������ newNode
	
	newNode->next = plist->head->next;
	plist->head->next = newNode; //��带 ����
	(plist->numOfData)++; // ���� ���� ��Ŵ
}

void SInsert(LinkedList *plist, LData data)
{
	SL_Node *newNode = (SL_Node *)malloc(sizeof(SL_Node));
	//�ܹ��� ��ũ����Ʈ�� ��带 ���� ����
	SL_Node *pred = plist->head;
	newNode->data = data;

	while(pred->next != NULL && plist->comp(data, pred->next->data) != 0)
	{
		pred = pred->next;
	}

	newNode->next = pred->next;
	pred->next = newNode;

	if(newNode->next == NULL)	//��带 �������� ���������� tail�� ����
		plist->tail = newNode;

	(plist->numOfData)++;
}

void TInsert(LinkedList *plist, LData data)
{
	SL_Node * newNode = (SL_Node *)malloc(sizeof(SL_Node));
	//�ܹ��� ��ũ����Ʈ�� ��带 ���� ����
	newNode->data = data; // ���� ����
	newNode->next = NULL;

	plist->tail->next = newNode; //tail�� next�� newNode
	plist->tail = newNode;		 //tail�� newNode�� ����.
	
	(plist->numOfData)++; // ���� ���� ��Ŵ
}

int LFirst(LinkedList *plist, LData *pdata)
{
	if(plist->head->next == NULL) //��尡 �������� ������
		return FALSE;
	
	plist->before = plist->head;  //before�� head���
	plist->cur = plist->head->next;//cur�� head�� �������

	*pdata = plist->cur->data; //cur�� data�� ������
	return TRUE;
}

int LNext(LinkedList *plist, LData * pdata)
{
	if(plist->cur->next == NULL) //������尡 ���ٸ� false����
		return FALSE;
	
	plist->before = plist->cur;
	plist->cur = plist->cur->next; //��� ����

	*pdata = plist->cur->data; //�����Ͱ� ������
	return TRUE; //TRUE ����
}

LData LRemove(LinkedList *plist)
{
	SL_Node * rpos = plist->cur;
	LData rdata = rpos->data;	//�ӽ÷� ����

	plist->before->next = plist->cur->next;
	plist->cur = plist->before; //��� ���� ����

	free(rpos); //������ ��� �����Ҵ� ����
	(plist->numOfData)--; //������ �� ����
	return rdata; //������ ������ ����
}

int LCount(LinkedList *plist)
{
	return plist->numOfData;
}

void SetSortRule(LinkedList *plist, int (*comp)(LData d1, LData d2))
{
	plist->comp = comp; //�Լ� ���
}
































//////////////////////////////////////////////////////
//3. Circular Linked List

void CListInit(CircularList *plist)
{
	plist->tail = NULL;
	plist->cur = NULL;
	plist->before = NULL;
	plist->numOfData = 0;
	plist->comp = NULL;
}

void CLInsert(CircularList *plist, CLData data)
{
	if(plist->comp != NULL && CLCount(plist) != 0) //���� ������ �ְų�, ù��° ������ �ƴ϶��
		CSInsert(plist, data); //���� ���ؿ� �ٰ� ����߰�
	else	//���� ������ ���ų�, ù��° �����̶��
		CFInsert(plist, data); //�Ӹ��� ��� �߰�
}

void CFInsert(CircularList *plist, CLData data)
{
	CL_Node *newNode = (CL_Node*)malloc(sizeof(CL_Node));//�����Ҵ�
	newNode->data = data;

	if(plist->tail == NULL)			//���� ��� ���Խ�
	{
		plist->tail = newNode;      //tail ��� ����
		newNode->next = newNode;    //next�� �ڱ� �ڽ��� ����Ŵ.
	}
	else
	{
		newNode->next = plist->tail->next; //newNode�� next����
		plist->tail->next = newNode;		   //���� tail next�� ����
	}
	(plist->numOfData)++;
}

void CSInsert(CircularList *plist, CLData data)
{
	int count = 0;
	CL_Node *pred = plist->tail;
	
	CL_Node *newNode = (CL_Node *)malloc(sizeof(CL_Node));
	//���� ��ũ����Ʈ�� ��带 ���� ����
	newNode->data = data;	//������ ����

	while(count < (plist->numOfData) && plist->comp(data, pred->next->data) != 0)
	{
		//(�ڷ��� ������ŭ && �񱳱��ؿ� ������ �� ����) �ݺ�
		pred = pred->next;
		count++;
	}

	//pred->next�� newNode�� ����
	newNode->next = pred->next; 
	pred->next = newNode;

	if(pred == plist->tail) //pred�� �������ٸ�
		plist->tail = newNode; //������ ���� newNode�� ����.

	(plist->numOfData)++;
}

void CTInsert(CircularList *plist, CLData data)
{
	CL_Node *newNode = (CL_Node*)malloc(sizeof(CL_Node));//�����Ҵ�
	newNode->data = data;

	if(plist->tail == NULL)			//���� ��� ���Խ�
	{
		plist->tail = newNode;      //tail ��� ����
		newNode->next = newNode;    //next�� �ڱ� �ڽ��� ����Ŵ.
	}
	else
	{
		newNode->next = plist->tail->next; //newNode�� next����
		plist->tail->next = newNode;		   //���� tail next�� ����
		plist->tail = newNode;			   //���� ����.
	}
	
	(plist->numOfData)++;
}

int CLFirst(CircularList *plist, CLData *pdata)
{
	if(plist->tail == NULL) //����� ��尡 ���ٸ�
		return FALSE;

	plist->before = plist->tail;		//before = tail
	plist->cur = plist->tail->next;		//cur = tail->next

	*pdata = plist->cur->data;
	return TRUE;
}

int CLNext(CircularList *plist, CLData * pdata)
{
	if(plist->tail == NULL) //����� ��尡 ���ٸ�
		return FALSE;

	plist->before = plist->cur;		//before = cur
	plist->cur = plist->cur->next;	//cur = cur->next

	*pdata = plist->cur->data;
	return TRUE;
}


CLData CLRemove(CircularList *plist)
{
	CL_Node * rpos = plist->cur;
	CLData rdata = rpos->data;

	if(rpos == plist->tail)	//���� ����� ������ ���
	{
		if(plist->tail == plist->tail->next) // �׸��� ������ ���� �����
			plist->tail = NULL;
		else
			plist->tail = plist->before;
	}

	plist->before->next = plist->cur->next;	
	plist->cur = plist->before;				//������ ��忡�� ���� ����

	free(rpos);
	(plist->numOfData)--;
	return rdata;
}

int CLCount(CircularList *plist)
{
	return plist->numOfData;
}

void CSetSortRule(CircularList *plist, int (*comp)(CLData d1, CLData d2))
{
	plist->comp = comp;
}































////////////////////////////////////////////
// 4. DBLinked List

void DListInit(DBLinkedList *plist)
{
	plist->head = (DL_Node*)malloc(sizeof(DL_Node));
	plist->tail = (DL_Node*)malloc(sizeof(DL_Node)); //���̳�����

	plist->head->prev = NULL;
	plist->head->next = plist->tail;

	plist->tail->next = NULL;
	plist->tail->prev = plist->head;

	plist->numOfData = 0;
	plist->comp = NULL;
}

void DLInsert(DBLinkedList *plist, DLData data)
{
	if(plist->comp != NULL) //���� ������ �ִٸ�
		DSInsert(plist, data); //���� ���ؿ� �ٰ� ����߰�
	else	//���� ������ ���ٸ�
		DFInsert(plist, data); //�Ӹ��� ��� �߰�
}


void DFInsert(DBLinkedList *plist, DLData data)
{
	DL_Node *old = plist->head->next; //�������(���� �� �� ���)

	DL_Node *newNode = (DL_Node*)malloc(sizeof(DL_Node));//�����Ҵ�
	newNode->data = data;

	newNode->next = old;				//(�����next)-�������
	newNode->prev = plist->head;		//head-(prev�����)

	old->prev = newNode;				//�����-(prev�������)
	plist->head->next = newNode;		//(head->next) - �����


	(plist->numOfData)++;
}

void DTInsert(DBLinkedList *plist, DLData data)
{
	DL_Node *old = plist->tail->prev; //�������(���� �� �� ���)
	DL_Node *newNode = (DL_Node*)malloc(sizeof(DL_Node));//�����Ҵ�
	newNode->data = data;

	newNode->next = plist->tail;		// (�����->next) - tail
	newNode->prev = old;				// �������-(prev�����) ���� 
	
	old->next = newNode;				// (�������next)-����� ����
	plist->tail->prev = newNode;		//	����� - (prevTail)

	(plist->numOfData)++;
}

void DSInsert(DBLinkedList *plist, DLData data)
{
	DL_Node *pred = plist->head;		//pred;������ ��ġ
	DL_Node *predNext;
	
	DL_Node *newNode = (DL_Node *)malloc(sizeof(DL_Node));
	newNode->data = data;	//���� ���� �� ������ ����

	while(pred->next != NULL && plist->comp(data, pred->next->data) != 0)
	{
		//�񱳱��ؿ� ������ �� ���� �ݺ�-���� �ƴҶ�d
		pred = pred->next;
	}

	if(pred->next == NULL)  //tail(���̳��)�� ���
		pred = pred->prev;	//tail ����ġ�� ��������


	predNext = pred->next;			//pred �������

	//newNode �翷�� ����
	newNode->next = predNext; //(�����next) - (predNext)
	newNode->prev = pred;	  //pred - (prev�����)			 

	//�翷 ���� ����带 ����
	pred->next = newNode;
	predNext->prev = newNode;

	(plist->numOfData)++;
}

int DLFirst(DBLinkedList *plist, DLData *pdata)
{
	if(plist->head->next == plist->tail)	//��尡 �ϳ��� ������
		return FALSE;

	plist->cur = plist->head->next;	//���簪�� ù��° ����
	*pdata = plist->cur->data;		//������ �޾ƿ�.
	
	return TRUE;
}

int DLNext(DBLinkedList *plist, DLData * pdata)
{
	if(plist->cur->next == plist->tail) //������ ���̹Ƿ� false����
		return FALSE;
	
	plist->cur = plist->cur->next;	//���� ��ġ�� ��ĭ �Ű� ��������
	*pdata = plist->cur->data;		//������ �޾ƿ�.
	return TRUE;
}

int DLPrevious(DBLinkedList * plist, DLData * pdata)
{
	if(plist->cur->prev == plist->head) //���� ó���̹Ƿ� false����
		return FALSE;

	plist->cur = plist->cur->prev;	//������ġ���� �������� ��ĭ �ű�
	*pdata = plist->cur->data;		//������ �޾ƿ�.
	return TRUE;
}

DLData DLRemove(DBLinkedList *plist)
{
	DL_Node * rpos = plist->cur;
	DLData remv = rpos->data;

	rpos->prev->next = rpos->next;//(����������next) - ���������
	rpos->next->prev = rpos->prev;//���������� - (prev���������)

	plist->cur = plist->cur->prev; // cur��ġ ������.

	free(rpos);
	(plist->numOfData)--;
	return remv;
}

int DLCount(DBLinkedList *plist)
{
	return plist->numOfData;
}

void DSetSortRule(DBLinkedList *plist, int (*comp)(DLData d1, DLData d2))
{
	plist->comp = comp;
}






























////////////////////////////////////////////
// 5. Array Stack

void AStackInit(ArrayStack * pstack)
{
	pstack->topIndex = -1; //�ʱ� ���̹Ƿ� top�ε����� -1
}

int ASIsEmpty(ArrayStack * pstack)
{
	if(pstack->topIndex == -1)	//��� ������ TRUE ����
		return TRUE;
	else						//�׷��� ������ FALSE ����
		return FALSE;
}

void ASPush(ArrayStack * pstack, ASData data)
{
	pstack->topIndex += 1;						//top�� ����Ų��
	pstack->stackArr[pstack->topIndex] = data;	//�ش� �ε����� ������
}

ASData ASPop(ArrayStack * pstack)
{
	int rldx;

	if(ASIsEmpty(pstack))				//������ ����ִµ� popȣ���
	{
		puts("Can't pop : Stack is empty!");
		exit(-1);
	}

	rldx = pstack->topIndex;		//rldx�� ���� �ε��� ���� ����
	pstack->topIndex -= 1;		//top���� 1 ����

	return pstack->stackArr[rldx];
}

ASData ASPeek(ArrayStack * pstack)
{
	if(ASIsEmpty(pstack))				//������ ����ִµ� peekȣ���
	{
		puts("Can't peek : Stack is empty!");
		exit(-1);
	}

	return pstack->stackArr[pstack->topIndex];	//�ش� ���� ��ȯ
}































////////////////////////////////////////////
// 6. List Stack

void LStackInit(ListStack * pstack)
{
	pstack->top = NULL;		//head(top)�� null�� �ʱ�ȭ
}

int LSIsEmpty(ListStack * pstack)
{
	if(pstack->top == NULL)	//top�� null�϶�
		return TRUE;
	else
		return FALSE;
}

void LSPush(ListStack * pstack, LSData data)
{
	LS_Node * newNode = (LS_Node*)malloc(sizeof(LS_Node));

	newNode->data = data;
	newNode->next = pstack->top;

	pstack->top = newNode;
}

LSData LSPop(ListStack * pstack)
{
	LSData rdata;
	LS_Node * rnode;

	if(LSIsEmpty(pstack)) {
		puts("Can't Pop : empty!!");
		exit(-1);
	}

	rdata = pstack->top->data;
	rnode = pstack->top;

	pstack->top = pstack->top->next;
	free(rnode);

	return rdata;
}

LSData LSPeek(ListStack * pstack)
{
	if(LSIsEmpty(pstack)) {
		puts("Can't Peek : empty!!");
		exit(-1);
	}

	return pstack->top->data;
}


































////////////////////////////////////////////
// 7. Circular Queue


//<����ť �ʱ�ȭ>
void CQueueInit(CQueue * pq)
{
	pq->front = 0;
	pq->rear = 0;		//front�� rear���� 0���� �ʱ�ȭ
}

//<����ť Empty���� Ȯ��>
int CQIsEmpty(CQueue * pq)
{
	if(pq->front == pq->rear) //front�� rear���� ������ �������
		return TRUE;
	else					  //�װԾƴ϶�� ������� ����.
		return FALSE;
}

int NextPosIdx(int pos)		  //���� �ε��� ����
{
	if(pos == QUE_LEN-1)	  //��üũ��-1�� ������ġ�� ����
		return 0;		  //���� �ε��� = 0 (�迭�ε����� ��ȯ������)
	else				  
		return pos+1;	  //���� �ε��� = +1
}

//<����ť ����> : rear�� ����
void CEnqueue(CQueue * pq, CQData data)
{
	if(NextPosIdx(pq->rear) == pq->front) //rear�� ���� �ε����� front�� ���ٸ�
	{
		puts("Queue is full!!");		  //���� ���̹Ƿ� �����޽���
		exit(-1);
	}
	pq->rear = NextPosIdx(pq->rear);		//rear���� +1
	pq->queArr[pq->rear] = data;			//data ����
}

//<����ť ����> : front�� ����
CQData CDequeue(CQueue * pq)
{
	if(CQIsEmpty(pq))
	{
		puts("Queue is empty!!");	//��� �����Ƿ� �����޽���
		exit(-1);
	}

	pq->front = NextPosIdx(pq->front);		//front�� ���� �ε�����
	return pq->queArr[pq->front];					//���� �� �� ��ȯ
}

//<����ť front�� ����Ȯ��>
CQData CQPeek(CQueue * pq)
{
	if(CQIsEmpty(pq))
	{
		puts("Queue is empty!!");	//��� �����Ƿ� �����޽���
		exit(-1);
	}
	return pq->queArr[NextPosIdx(pq->front)];
}





























////////////////////////////////////////////////////////////////
// 8. List Queue

//<����Ʈ ť �ʱ�ȭ>
void LQueueInit(LQueue * pq)
{
	pq->front = NULL;
	pq->rear = NULL;
}

//<����Ʈ ť Empty���� Ȯ��>
int LQIsEmpty(LQueue * pq)
{
	if(pq->front == NULL)	//front�� NULL�̸� ����ִ°��̹Ƿ�
		return TRUE;
	else
		return FALSE;
}

//<������ ����>
void LEnqueue(LQueue * pq, LQData data)
{
	LQ_Node *newNode = (LQ_Node*)malloc(sizeof(LQ_Node));
	newNode->next = NULL;
	newNode->data = data;

	if(LQIsEmpty(pq))
	{
		pq->front = newNode;
		pq->rear = newNode;
	}
	else
	{
		pq->rear->next = newNode;
		pq->rear = newNode;
	}
}

//<������ ����> : ���� �Ǿ�  ������(front) ����
LQData LDequeue(LQueue * pq)
{
	LQ_Node * delNode;
	LQData retData;

	if(LQIsEmpty(pq))
	{
		puts("Queue is empty!");
		exit(-1);
	}

	delNode = pq->front;
	retData = delNode->data;
	pq->front = pq->front->next;

	free(delNode);
	return retData;
}

//<front�� ����Ȯ��> 
LQData LQPeek(LQueue * pq)
{
	if(LQIsEmpty(pq))
	{
		puts("Queue is empty");
		exit(-1);
	}

	return pq->front->data;
}



































////////////////////////////////////////////////////////////////
// 9. Deque (Double_ended queue)

//<�ʱ�ȭ �Լ�>
void DequeInit(Deque * pdeq)
{
	pdeq->head = NULL;
	pdeq->tail = NULL;
}

//<Empty Ȯ��>
int DQIsEmpty(Deque * pdeq)
{
	if(pdeq->head == NULL)		//head�� NULL�̸� ��������Ƿ�
		return TRUE;
	else
		return FALSE;
}

//<�տ� ����>
void DQAddFirst(Deque * pdeq, DQData data)
{
	DQ_Node *newNode = (DQ_Node*)malloc(sizeof(DQ_Node));
	newNode->data = data;

	newNode->next = pdeq->head;
	newNode->prev = NULL;

	if(DQIsEmpty(pdeq))
		pdeq->tail = newNode;
	else
		pdeq->head->prev = newNode;

	pdeq->head = newNode;
}

//<�ڿ� ����>
void DQAddLast(Deque * pdeq, DQData data)
{
	DQ_Node *newNode = (DQ_Node*)malloc(sizeof(DQ_Node));
	newNode->data = data;

	newNode->next = NULL;
	newNode->prev = pdeq->tail;

	if(DQIsEmpty(pdeq))
		pdeq->head = newNode;
	else
		pdeq->tail->next = newNode;

	pdeq->tail = newNode;
}

//<�� ����>
DQData DQRemoveFirst(Deque * pdeq)
{
	DQ_Node* rnode = pdeq->head;
	DQData rdata = pdeq->head->data;

	if(DQIsEmpty(pdeq))
	{
		puts("Deque Memory is empty!");
		exit(-1);
	}

	pdeq->head = pdeq->head->next;
	free(rnode);

	if(pdeq->head == NULL)
		pdeq->tail = NULL;
	else
		pdeq->head->prev = NULL;

	return rdata;
}

//<�� ����>
DQData DQRemoveLast(Deque * pdeq)
{
	DQ_Node* rnode = pdeq->tail;
	DQData rdata = pdeq->tail->data;

	if(DQIsEmpty(pdeq))
	{
		puts("Deque Memory is empty!");
		exit(-1);
	}

	pdeq->tail = pdeq->tail->prev;
	free(rnode);

	if(pdeq->tail == NULL)
		pdeq->head = NULL;
	else
		pdeq->tail->next = NULL;

	return rdata;
}

//<front�� Ȯ��>
DQData DQGetFirst(Deque * pdeq)
{
	if(DQIsEmpty(pdeq))
	{
		printf("Deque Memory is empty!");
		exit(-1);
	}

	return pdeq->head->data;
}

//<rear�� Ȯ��>
DQData DQGetLast(Deque * pdeq)
{
	if(DQIsEmpty(pdeq))
	{
		puts("Deque Memory is empty!");
		exit(-1);
	}

	return pdeq->tail->data;
}


































////////////////////////////////////////////////////////////////
// 10. Binary Tree

//<����Ʈ����� �����Լ�>
BT_Node * MakeBTreeNode(void)
{
	BT_Node *nd = (BT_Node*)malloc(sizeof(BT_Node)); //��������

	nd->left = NULL;
	nd->right = NULL;

	return nd;
}

//<������ ���>
BTData GetData(BT_Node * bt)
{
	return bt->data;
}

//<������ ����>
void SetData(BT_Node * bt, BTData data)
{
	bt->data = data;
}

//<���� ����Ʈ���� �ּҰ� ��ȯ>
BT_Node * GetLeftSubTree(BT_Node * bt)
{
	return bt->left;
}

//<������ ����Ʈ���� �ּҰ� ��ȯ>
BT_Node * GetRightSubTree(BT_Node * bt)
{
	return bt->right;
}

//<���� ����Ʈ���� ����>
void MakeLeftSubTree(BT_Node * main, BT_Node * sub)
{
	if(main->left != NULL)
	{
		puts("delete old node");
		free(main->left);
	}
	
	main->left = sub;
}

//<������ ����Ʈ���� ����>
void MakeRightSubTree(BT_Node * main, BT_Node * sub)
{
	if(main->right != NULL)
	{
		puts("delete old node");
		free(main->right);
	}

	main->right = sub;
}

//<���� Ž��>
void PreorderTraverse(BT_Node * bt, VisitFuncPtr action)
{
	if(bt == NULL)
		return;

	action(bt->data);
	PreorderTraverse(bt->left, action);
	PreorderTraverse(bt->right, action);
}

//<���� Ž��>
void InorderTraverse(BT_Node * bt, VisitFuncPtr action)
{
	if(bt == NULL)
		return;

	InorderTraverse(bt->left, action);
	action(bt->data);
	InorderTraverse(bt->right, action);
}

//<���� Ž��>
void PostorderTraverse(BT_Node * bt, VisitFuncPtr action)
{
	if(bt == NULL)
		return;

	PostorderTraverse(bt->left, action);
	PostorderTraverse(bt->right, action);
	action(bt->data);
}

//<����Ʈ�� �Ҹ� �Լ�>
void DeleteTree(BT_Node * bt)
{
	if(bt == NULL)
		return;

	DeleteTree(bt->left);
	DeleteTree(bt->right);

	printf("del tree data: %d \n", bt->data);
	free(bt);
}

//<���� �ڽ� ��� ����>
BT_Node * RemoveLeftSubTree(BT_Node *bt)
{
	BT_Node *delNode;

	if(bt != NULL)
	{
		delNode = bt->left;
		bt->left = NULL;
	}

	return delNode;
}

//<������ �ڽ� ��� ����>
BT_Node* RemoveRightSubTree(BT_Node *bt)
{
	BT_Node *delNode;

	if(bt != NULL)
	{
		delNode = bt->right;
		bt->right = NULL;
	}

	return delNode;
}

//<���� �ڽ� ��� ����>
void ChangeLeftSubTree(BT_Node* main, BT_Node *sub)
{
	main->left = sub;
}

//<������ �ڽ� ��� ����>
void ChangeRightSubTree(BT_Node* main, BT_Node *sub)
{
	main->right = sub;
}





























////////////////////////////////////////////////////
// 11. ���� Ž�� Ʈ�� 
//<���� Ž��Ʈ�� ���� �� �ʱ�ȭ>
void BSTMakeAndInit(BT_Node ** pRoot)
{
	*pRoot = NULL;
}

//<��忡 ����� ������ ��ȯ>
BSTData BSTGetNodeData(BT_Node *bst)
{
	return GetData(bst);
}

//<������ ����> : �뷱���� ������ �ش��Լ� �Ʒ��κ� ���뷱���� �ּ�ó��
void BSTInsert(BT_Node **pRoot, BSTData data)
{
	BT_Node *pNode = NULL;	//�θ� ���
	BT_Node *cNode = *pRoot;//���� ���
	BT_Node *nNode = NULL;	//�� ���

	// ���ο� ��尡 �߰��� ��ġ�� ã�´�.
	while(cNode != NULL)
	{
		if(data == GetData(cNode))
			return;	//Ű �ߺ� ����

		pNode = cNode; //�θ��带 �Ѵܰ� ����.

		//�� �� : cNode�� ������, ���� ������ �ڽ�
		if(GetData(cNode) > data)
			cNode = GetLeftSubTree(cNode);
		else
			cNode = GetRightSubTree(cNode);
	}

	// pNode�� ���� ��忡 �߰��� �� ����� ����
	nNode = MakeBTreeNode();	//�� ��� ����
	SetData(nNode, data);	//�� ��忡 ������ ����

	// pNode�� ���� ��忡 �� ��带 �߰�
	if(pNode != NULL)	// �� ��尡  ��Ʈ ��尡 �ƴ϶��
	{
		 if(data < GetData(pNode))
			 MakeLeftSubTree(pNode, nNode);//�θ����� ���ʿ� ��������
		 else
			MakeRightSubTree(pNode, nNode);
	}
	else	// �� ��尡 ��Ʈ �����,
	{
		*pRoot = nNode;	//��Ʈ�� �����
	}

	//////////////////////////////////////////
	*pRoot = Rebalance(pRoot);	//��� ���� �� ���뷱��
	//////////////////////////////////////////
}

//<������ Ž��>
BT_Node *BSTSearch(BT_Node *bst, BSTData target)
{
	BT_Node *cNode = bst;	//���� ���
	BSTData cd;				//���� ������

	//��� Ž��
	while(cNode != NULL)
	{
		cd = GetData(cNode);	//���� ����� ������ ����

		if(target == cd)		//ã������ ������ ��
			return cNode;
		else if(target < cd)	//ã������ �����Ͱ� ���� ��� ���� ���� �۴ٸ�
			cNode = GetLeftSubTree(cNode);	//������ �˻��ϱ� ���� ���ʳ��� �̵�
		else
			cNode = GetRightSubTree(cNode);
	}

	return NULL;
}

//<������ ����> : �뷱���� ������ �ش��Լ� �Ʒ��κ� ���뷱���� �ּ�ó��
BT_Node *BSTRemove(BT_Node **pRoot, BSTData target)
{
	//���� ����� ��Ʈ ����� ��츦 ������ ���.
	//��Ȳ1 : ������ ��尡 �ܸ� ����ΰ��
	//��Ȳ2 : ������ ��尡 �ϳ��� �ڽ� ��带 ���°��
	//��Ȳ3 : ������ ��尡 �ΰ��� �ڽ� ��带 ���°��
	
	BT_Node *pVRoot = MakeBTreeNode();
	//���� ��Ʈ ���̳��: ������尡 ��Ʈ����� ��쵵 �ڵ带 �Ȱ��� �����ϱ� ����

	BT_Node *pNode = pVRoot;	//�θ� ���< �����Ʈ��
	BT_Node *cNode = *pRoot;	//���� ���< ��Ʈ��
	BT_Node *dNode;				//���� ���

	//��Ʈ ��带 pVRoot�� ����Ű�� ����� ������ ���� ��尡 �ǰ� ��
	ChangeRightSubTree(pVRoot, *pRoot);

	//���� ����� ������ ��� Ž��
	while(cNode != NULL && GetData(cNode) != target)
	{
		pNode = cNode;

		if(target <GetData(cNode))
			cNode = GetLeftSubTree(cNode);
		else
			cNode = GetRightSubTree(cNode);
	}

	if(cNode == NULL)	// ���� ����� �������� �ʴ´ٸ�
		return NULL;

	dNode = cNode;		//���� ����� dNode�� ����Ű�� ��

	//��Ȳ 1 : ������ ��尡 �ܸ� ����� ���
	if(GetLeftSubTree(dNode) == NULL && GetRightSubTree(dNode) == NULL)
	{
		if(GetLeftSubTree(pNode) == dNode)
			RemoveLeftSubTree(pNode);
		else
			RemoveRightSubTree(pNode);
	}

	//��Ȳ 2 ; �ϳ��� �ڽ� ��带 ���°��
	else if(GetLeftSubTree(dNode) == NULL || GetRightSubTree(dNode) == NULL)
	{
		BT_Node *dcNode;		//delete node�� �ڽĳ��

		if(GetLeftSubTree(dNode) != NULL)//���ʳ�������Ҷ�
			dcNode = GetLeftSubTree(dNode);
		else
			dcNode = GetRightSubTree(dNode);

		if(GetLeftSubTree(pNode) == dNode)	//�����尡 �θ����� ���ʿ� �޷�������
			ChangeLeftSubTree(pNode, dcNode);
		else
			ChangeRightSubTree(pNode, dcNode);
	}

	//��Ȳ 3 : �ΰ��� �ڽ� ��带 ���� ���
	else
	{
		BT_Node *mNode;				// ���� ���� ���
		BT_Node *mpNode;			//�ּ� ����� �θ���
		BTData delData;

		//�ܰ�1
		//������ ��带 ��ü�� ��带 ã�´�.
		//������ ��� : ������ ����� ������ ���� Ʈ������ ���� ���� ��
		
		mNode = GetRightSubTree(dNode);//������ ����� ������ ���
		mpNode = dNode;	   //���� �θ���

		while(GetLeftSubTree(mNode) != NULL)
		{
			mpNode = mNode;
			mNode = GetLeftSubTree(mNode);
			//������ ����� ������ ���� Ʈ������ ���� ���� = ����������
		}

		//�ܰ�2
		//��ü�� ��忡 ����� ���� ������ ��忡 ����
		delData = GetData(dNode);	//������ ������ ���
		SetData(dNode, GetData(mNode));//����

		//�ܰ�3
		//��ü�� ����� �θ� ���� �ڽ� ��带 ����
		if(GetLeftSubTree(mpNode) == mNode) //��ü�� ��尡 ���� �ڽĳ����
			ChangeLeftSubTree(mpNode, GetRightSubTree(mNode));
			//��ü�� ����� �ڽ� ��带 �θ����� ���ʿ� ����
		else
			ChangeRightSubTree(mpNode, GetRightSubTree(mNode));
		
		//������ ��带 �����ϱ� ���� mNode ��Ȱ��
		dNode = mNode;				//����
		SetData(dNode, delData);	//��� ������ ����
	}

	//������ ��尡 ��Ʈ ����� ��쿡 ���� ó��
	if(GetRightSubTree(pVRoot) != *pRoot)
		*pRoot = GetRightSubTree(pVRoot);

	free(pVRoot);
	//////////////////////////////////////////
	*pRoot = Rebalance(pRoot); //��� ������ ���뷱��
	//////////////////////////////////////////
	return dNode;
}

void ShowIntData(int data)
{
	printf("%d ", data);
}

//<������ ���>
void BSTShowAll(BT_Node *bst)
{
	InorderTraverse(bst, ShowIntData);
}
































////////////////////////////////////////////////////
//12. AVLƮ��

//LLȸ��
BT_Node * RotateLL(BT_Node * bst)
{
	BT_Node *pNode = bst; //�������
	BT_Node *cNode = GetLeftSubTree(pNode);  //������

	ChangeLeftSubTree(pNode, GetRightSubTree(cNode)); //CNode�� ������ �ڽ��� pNode�������� �̵�
	ChangeRightSubTree(cNode, pNode); //pNode�� cNode�� �����ʿ� ����
	return cNode;	//������ ����.
}

//RRȸ��
BT_Node * RotateRR(BT_Node * bst)
{
	BT_Node *pNode = bst; //���� ���
	BT_Node *cNode = GetRightSubTree(pNode); //���� ���

	ChangeRightSubTree(pNode, GetLeftSubTree(cNode)); //cNode�� �����ڽ��� pNode�� �����ʿ� ����
	ChangeLeftSubTree(cNode, pNode); //cNode�� ���ʿ� pNode �� ����. 
	return cNode;
}

//RL ȸ��: LLȸ������ RR���·� ����� RRȸ���� ���.
BT_Node *RotateRL(BT_Node *bst)
{
	BT_Node *pNode = bst;
	BT_Node *cNode = GetRightSubTree(pNode);

	//�κ��� LL ȸ��
	ChangeRightSubTree(pNode, RotateLL(cNode));
	//pNode�� �����ʿ� cNode-LLȸ���� ���� �ٿ� RR���¸� ����

	return RotateRR(pNode); // RRȸ��
}

//LR ȸ�� : RRȸ������ LL���·� ����� LLȸ���� ���
BT_Node *RotateLR(BT_Node *bst)
{
	BT_Node *pNode;
	BT_Node *cNode;

	pNode = bst;
	cNode = GetLeftSubTree(pNode);

	//�κ��� RRȸ��
	ChangeLeftSubTree(pNode, RotateRR(cNode));
	//pNode�� ���ʿ� cNode-RRȸ�� �� ���� �ٿ� LL���·� ����

	return RotateLL(pNode); // LLȸ��
}

//��������� Ʈ���� ���̸� ���ȭ�� ��ȯ�Ѵ�.
int GetHeight(BT_Node *bst)
{
	int leftH;		//left ����
	int rightH;		//right ����

	if(bst == NULL)
		return 0;

	//���� ����Ʈ�� ���� ���
	leftH = GetHeight(GetLeftSubTree(bst));

	//������ ����Ʈ�� ���� ���
	rightH = GetHeight(GetRightSubTree(bst));

	// ū ���� ���̸� ��ȯ�Ѵ�.
	if(leftH > rightH)
		return leftH + 1;
	else
		return rightH + 1;
}

// �� ���� Ʈ���� ������ ���� ��ȯ
int GetHeightDiff(BT_Node *bst)
{
	int lsh;	// ���� ����Ʈ�� ����
	int rsh;	// ������ ����Ʈ�� ����

	if(bst == NULL)	// ��尡 �ϳ��� ������ 0 ��ȯ
		return 0;

	lsh = GetHeight(GetLeftSubTree(bst));  //���� ����Ʈ�� ����
	rsh = GetHeight(GetRightSubTree(bst)); //������ ����Ʈ�� ����

	return lsh - rsh; //���� ���� ��ȯ
}


// Ʈ���� ������ ��´�.
BT_Node * Rebalance(BT_Node ** pRoot)
{
	int hDiff = GetHeightDiff(*pRoot);

	if(hDiff > 1)	// ���� ���� Ʈ�� �������� ���̰� 2�̻� ũ�ٸ�
	{
		if(GetHeightDiff(GetLeftSubTree(*pRoot)) > 0) //LL���¶��
			*pRoot = RotateLL(*pRoot);				  //LLȸ��
		else
			*pRoot = RotateLR(*pRoot);				  //LRȸ��
	}
	if(hDiff < -1) // ������ ���� Ʈ�� �������� �� -2 ���ϸ�
	{
		if(GetHeightDiff(GetRightSubTree(*pRoot)) < 0) //RR���¶��
			*pRoot = RotateRR(*pRoot);				   //RRȸ��
		else
			*pRoot = RotateRL(*pRoot);				   //RLȸ��
	}
	return *pRoot;
}






















///////////////////////////////////////////////////////////
//13. Priority Queue
//

////////// heap
void HeapInit(Heap * ph, PriorityComp pc)
{
	ph->numOfData = 0;
	ph->comp = pc;
}
int HIsEmpty(Heap * ph)
{
	if(ph->numOfData == 0)	//�� ���� ������ ����Ȯ��
		return TRUE;
	else
		return FALSE;
}

int GetParentIDX(int idx)
{
	return idx/2;
}

//���� �ڽ� ����� �ε��� �� ��ȯ
int GetLChildIDX(int idx)
{
	return idx*2;
}

//������ �ڽ� ����� �ε��� �� ��ȯ
int GetRChildIDX(int idx)
{
	return GetLChildIDX(idx)+1;
}

//�� ���� �ڽ� ��� �� ���� �켱������ ���� �ڽ� ��� �ε��� �� ��ȯ
//�ڽ� ��尡 ������ 0�� ��ȯ, �ڽ� ��尡 �ϳ��� ��� �� ����� �ε����� ��ȯ
int GetHiPriChildIDX(Heap *ph, int idx)
{
	if(GetLChildIDX(idx) > ph->numOfData) //�ڽ� ��尡 �������� ������
		return 0;
	
	else if(GetLChildIDX(idx) == ph->numOfData) //�ڽĳ�尡 �ϳ���
		return GetLChildIDX(idx);
	else //�ڽ� ��尡 �Ѵ� �����Ѵٸ�
	{
		//������ �ڽ� ����� �켱������ ���ٸ�
		if(ph->comp(ph->heapArr[GetLChildIDX(idx)], ph->heapArr[GetRChildIDX(idx)]) < 0 )
			return GetRChildIDX(idx); //������ �ڽ� ����� �ε����� ��ȯ
		else
			return GetLChildIDX(idx);
	}
}


void HInsert(Heap * ph, HData data)
{
	int idx = ph->numOfData+1; //�� ���� �ε���

	while(idx != 1) //idx�� ��Ʈ��� �϶�����
	{
		//data�� ������ ����� �θ��带 ��
		if(ph->comp(data, ph->heapArr[GetParentIDX(idx)]) > 0)
		{
			ph->heapArr[idx] = ph->heapArr[GetParentIDX(idx)];
			//idx��ġ�� �θ����� ��ġ �ٲ�
			idx = GetParentIDX(idx); //idx���� ���� �θ��� idx��
		}
		else //���� ���°� ���ǿ� ����.
		{
			break;
		}
	}

	ph->heapArr[idx] = data;
	ph->numOfData += 1;
}

HData HDelete(Heap * ph)
{
	int parentIdx = 1;
	int childIdx;

	HData retData = ph->heapArr[1]; //���� ������ �ӽ�����
	HData lastElem = ph->heapArr[ph->numOfData];//������ ��ġ��� �����Ͱ� ����

	

	//���� : ������ ��带 ��Ʈ����� �ڸ��� �ű� ������,
	//�ڽ� ������ �񱳸� ���� ���ڸ��� ã�ư��� �Ѵ�.

	//GetHiPriChildIDX(ph, parentIdx)
	//>�� �ڽ� ��� �� �켱������ ���� ���� �ε���
	//>�ڽĳ�尡 ������ 0, �ϳ� ������ �� ����� �ε���
	//chilIdx �� GetHiPriChildIdx�� ����� �ְ� �ݺ�������
	while(childIdx = GetHiPriChildIDX(ph, parentIdx))
	{
		//������ ���� GetHiPriChildIdx�� ����� �켱���� ��
		if(ph->comp(lastElem, ph->heapArr[childIdx]) >= 0)
			break; // ������ ����� �켱������ ������ �ݺ��� Ż��

		//������ ��庸�� �켱���� ������, �񱳴�� ����� ��ġ��  �� ���� �ø�
		ph->heapArr[parentIdx] = ph->heapArr[childIdx];
		//�θ���� ��ġ �ٲ�.
		parentIdx = childIdx; //��ġ �ٲ����� idx���� �ڽ�idx������
	} //�ݺ��� Ż���ϸ� parentIdx���� ������ ����� ��ġ���� ����

	ph->heapArr[parentIdx] = lastElem;	//������ ��� ���� ����
	ph->numOfData -= 1;	
	return retData;
}

////////Priority Queue
void PQueueInit(PQueue  *ppq, PriorityComp pc)
{
	HeapInit(ppq, pc);
}

int PQIsEmpty(PQueue *ppq)
{
	return HIsEmpty(ppq);
}

void PEnqueue(PQueue *ppq, PQData data)
{
	HInsert(ppq, data);
}

PQData PDequeue(PQueue *ppq)
{
	return HDelete(ppq);
}



























///////////////////////////////////////////////////
////14. Hash Table
//
//<���̺� �ʱ�ȭ>
void TBInit(Table *pt, HashFunc *f)
{
	int i;

	for(i=0; i<MAX_TBL; i++)		//���̺� ���¸� EMPTY�� �ʱ�ȭ
		(pt->tb[i]).status = EMPTY;

	pt->hf = f;					    //�ؽ� �Լ� ���
}

//<���̺� Ű�� ���� ����>
void TBInsert(Table *pt, Key k, Value v)
{
	int hv = pt->hf(k);			//�ؽ��Լ��� Ű�� ����
	pt->tb[hv].val = v;			//�ش� Ű���� Value ����
	pt->tb[hv].key = k;			//���� Ű��(��ȯ��) ����
	pt->tb[hv].status = INUSE;
}

//<������ ����>
Value TBDelete(Table *pt, Key k)
{
	int hv = pt->hf(k);			//�ؽ��Լ��� Ű�� ����
	
	if((pt->tb[hv]).status != INUSE)	//������� �ƴ϶��
	{
		return NULL;				//�����Ͱ� �������� ����
	}
	else
	{
		(pt->tb[hv]).status = DELETED;	//status �� DELETED�� ����
		return (pt->tb[hv]).val;			//������ �� ��ȯ
	}
}

//<������ Ž��>
Value TBSearch(Table *pt, Key k)
{
	int hv = pt->hf(k);			//�ؽ��Լ��� Ű�� ����

	if((pt->tb[hv]).status != INUSE)//������� �ƴ϶��
		return NULL;				//�����Ͱ� �������� ����
	else
		return (pt->tb[hv]).val;		//�ش� �ε����� ��ȯ
}















////////////////////////////////////////////////////////
//15. Chaining : ���� ���� ����






















///////////////////////////////////////////////////////
//16. List Base Graph

int WhoIsPrecede(int data1, int data2);

// �׷����� �ʱ�ȭ
void LGraphInit(LGraph *pg, int nv)
{
	int i;

	pg->adjList = (LinkedList*)malloc(sizeof(LinkedList)*nv);//����(nv) ������ŭ �����Ҵ�
	pg->numV = nv;
	pg->numE = 0;		//�ʱ��� ���� �� 0��

	for(i=0; i<nv; i++) //nv : ���޹��� ������ ����
	{
		ListInit(&(pg->adjList[i])); //�������� ����Ʈ �ʱ�ȭ.
		SetSortRule(&(pg->adjList[i]), WhoIsPrecede); //����Ʈ�� ���ı��� ����->����� ���¸� ���� ���� �ϱ� ����. ��� ����
	}

	//Ž�� ���� ����� ���� ������ �Ҵ� �� �ʱ�ȭ
	pg->visitInfo = (int *)malloc(sizeof(int)*pg->numV);
	memset(pg->visitInfo, 0, sizeof(int) * pg->numV);
}


//�׷����� ���ҽ��� ����
void LGraphDestroy(LGraph *pg)
{
	if(pg->adjList != NULL)
		free(pg->adjList);

	if(pg->visitInfo != NULL)
		free(pg->visitInfo);
}

//������ �߰�
void LAddEdge(LGraph *pg, int fromV, int toV)
{
	LInsert(&(pg->adjList[fromV]), toV);	//���� fromV�� ���� ����Ʈ�� ���� toV�� ���� �߰�.
	LInsert(&(pg->adjList[toV]), fromV);	
	pg->numE += 1;	//���� �� +1
}

//��ƿ��Ƽ �Լ� : ������ ���� ���
void ShowLGraphEdgeInfo(LGraph *pg)
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

int WhoIsPrecede(int data1, int data2)
{
	if(data1 < data2)
		return 0;
	else
		return 1;
}

//���� �湮
int VisitVertex(LGraph *pg, int visitV)
{
	if(pg->visitInfo[visitV] == 0)
	{
		pg->visitInfo[visitV] = 1;	//�湮�� ���� 1�� �ʱ�ȭ
		printf("%c ", visitV + 65);
		return TRUE;
	}

	return FALSE;
}

// Depth First Search : ������ ���� ���
void DFShowGraphVertex(LGraph *pg, int startV)
{
	ArrayStack stack;
	int visitV = startV;
	int nextV;

	//DFS�� ���� ������ �ʱ�ȭ
	AStackInit(&stack);

	VisitVertex(pg, visitV);	// ���� ���� �湮
	ASPush(&stack, visitV);		// �湮�� ���� ���ÿ� ����

	while(LFirst(&(pg->adjList[visitV]), &nextV) == TRUE) //����������
	{
		int visitFlag = FALSE;

		if(VisitVertex(pg, nextV) == TRUE)	//������ ���� �湮�����ʾҴٸ�
		{
			ASPush(&stack, visitV);	//�湮�� ���� ���ÿ� ����
			visitV = nextV;			
			visitFlag = TRUE;		//����ߴٰ� ǥ��
		}
		else
		{
			while(LNext(&(pg->adjList[visitV]), &nextV) == TRUE)
			{
				if(VisitVertex(pg, nextV) == TRUE)
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
void BFShowGraphVertex(LGraph *pg, int startV)
{
	CQueue queue;
	int visitV = startV;
	int nextV;

	// DFS�� ���� ť�� �ʱ�ȭ
	CQueueInit(&queue);

	//���� ���� Ž��
	VisitVertex(pg, visitV);

	while(LFirst(&(pg->adjList[visitV]), &nextV) == TRUE)
	{
		if(VisitVertex(pg, nextV) == TRUE)	//�湮�� �����ߴٸ�
			CEnqueue(&queue, nextV);

		while(LNext(&(pg->adjList[visitV]), &nextV) == TRUE)
		{
			if(VisitVertex(pg, nextV) == TRUE)	//�湮������ ť�� ����
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
















///////////////////////////////////////////////////////////////////////
//17. Minimum cost Spanning Tree : Kruskal algorithm
//�߰����Ͽ� ���� ����