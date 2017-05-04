#include "DSPackege.h"

///////////////////////////////////////////////////////
///////////////////////////////////////////////////////
//실제 함수 구현
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






//1. ArrayList
void AListInit(ArrayList *plist)
{ 
	plist->numOfData = 0;     //현재 자료 개수 0 으로 초기화
	plist->curPosition = -1;  //자료 없으므로 인덱스 = -1
}
void ALInsert(ArrayList *plist, ALData data)
{
	if(plist->numOfData > LENGTH) // 자료 개수가 수용가능치 초과시
	{
		puts("자료 개수가 수용가능치를 초과하였습니다.");
		return;
	}

	plist->arr[plist->numOfData] = data; //맨 뒤에 자료 저장
	(plist->numOfData)++;				 //자료개수를 ++
}

int ALFirst(ArrayList *plist, ALData *pdata)
{
	if(plist->numOfData == 0)	//자료 없을시 리턴 0
		return FALSE;
	
	plist->curPosition = 0;     //인덱스 0으로 설정
	*pdata = plist->arr[0];     //pdata에 첫번째 값 저장.
	return TRUE;
}
int ALNext(ArrayList *plist, ALData * pdata)
{
	if(plist->curPosition >= (plist->numOfData)-1) 
		return FALSE;	//더이상 참조할 데이터가 없음

	(plist->curPosition)++; //인덱스를 ++
	*pdata = plist->arr[plist->curPosition]; //pdata에 값을 저장
	return TRUE;
}

ALData ALRemove(ArrayList *plist)
{
	int rpos = plist->curPosition; //현재 인덱스 저장
	int num = plist->numOfData;    //현재 자료개수 저장
	int i;
	ALData rdata = plist->arr[rpos]; //삭제할 값을 저장해둔다.

	for(i=rpos; i<num-1; i++)
		plist->arr[i] = plist->arr[i+1]; //현 위치(rpos)부터 한칸씩 당긴다.
	
	(plist->numOfData)--;
	(plist->curPosition)--;
	return rdata;//삭제할 값 리턴
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
	//더미노드 생성:이유? 삭제 및 조회 과정 일관되게 가능
	//더미노드 없다면 남은 노드 개수에 따라 다르게 처리해야
	plist->head->next = NULL;
	plist->tail = plist->head;
	plist->comp = NULL;
	plist->numOfData = 0;
}

void LInsert(LinkedList *plist, LData data)
{
	if(plist->comp == NULL) //정렬 기준이 없다면
		FInsert(plist, data); //머리에 노드 추가.
	else	//정렬 기준이 마련되었다면
		SInsert(plist, data);	//정렬 기준에 근거 노드추가
}

void FInsert(LinkedList *plist, LData data)
{
	SL_Node * newNode = (SL_Node *)malloc(sizeof(SL_Node));
	//단방향 링크리스트의 노드를 동적 생성
	newNode->data = data; // 값을 삽입

	if(plist->head->next == NULL) //최초삽입이라면
		plist->tail = newNode;	  //꼬리는 newNode
	
	newNode->next = plist->head->next;
	plist->head->next = newNode; //노드를 연결
	(plist->numOfData)++; // 값을 증가 시킴
}

void SInsert(LinkedList *plist, LData data)
{
	SL_Node *newNode = (SL_Node *)malloc(sizeof(SL_Node));
	//단방향 링크리스트의 노드를 동적 생성
	SL_Node *pred = plist->head;
	newNode->data = data;

	while(pred->next != NULL && plist->comp(data, pred->next->data) != 0)
	{
		pred = pred->next;
	}

	newNode->next = pred->next;
	pred->next = newNode;

	if(newNode->next == NULL)	//노드를 마지막에 연결했을시 tail값 변경
		plist->tail = newNode;

	(plist->numOfData)++;
}

void TInsert(LinkedList *plist, LData data)
{
	SL_Node * newNode = (SL_Node *)malloc(sizeof(SL_Node));
	//단방향 링크리스트의 노드를 동적 생성
	newNode->data = data; // 값을 삽입
	newNode->next = NULL;

	plist->tail->next = newNode; //tail의 next가 newNode
	plist->tail = newNode;		 //tail을 newNode로 설정.
	
	(plist->numOfData)++; // 값을 증가 시킴
}

int LFirst(LinkedList *plist, LData *pdata)
{
	if(plist->head->next == NULL) //노드가 존재하지 않을시
		return FALSE;
	
	plist->before = plist->head;  //before에 head노드
	plist->cur = plist->head->next;//cur에 head의 다음노드

	*pdata = plist->cur->data; //cur의 data를 가져옴
	return TRUE;
}

int LNext(LinkedList *plist, LData * pdata)
{
	if(plist->cur->next == NULL) //다음노드가 없다면 false리턴
		return FALSE;
	
	plist->before = plist->cur;
	plist->cur = plist->cur->next; //노드 연결

	*pdata = plist->cur->data; //데이터값 가져옴
	return TRUE; //TRUE 리턴
}

LData LRemove(LinkedList *plist)
{
	SL_Node * rpos = plist->cur;
	LData rdata = rpos->data;	//임시로 저장

	plist->before->next = plist->cur->next;
	plist->cur = plist->before; //노드 연결 수정

	free(rpos); //삭제한 노드 동적할당 해제
	(plist->numOfData)--; //데이터 수 감소
	return rdata; //삭제한 데이터 리턴
}

int LCount(LinkedList *plist)
{
	return plist->numOfData;
}

void SetSortRule(LinkedList *plist, int (*comp)(LData d1, LData d2))
{
	plist->comp = comp; //함수 등록
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
	if(plist->comp != NULL && CLCount(plist) != 0) //정렬 기준이 있거나, 첫번째 삽입이 아니라면
		CSInsert(plist, data); //정렬 기준에 근거 노드추가
	else	//정렬 기준이 없거나, 첫번째 삽입이라면
		CFInsert(plist, data); //머리에 노드 추가
}

void CFInsert(CircularList *plist, CLData data)
{
	CL_Node *newNode = (CL_Node*)malloc(sizeof(CL_Node));//동적할당
	newNode->data = data;

	if(plist->tail == NULL)			//최초 노드 삽입시
	{
		plist->tail = newNode;      //tail 노드 설정
		newNode->next = newNode;    //next가 자기 자신을 가리킴.
	}
	else
	{
		newNode->next = plist->tail->next; //newNode의 next연결
		plist->tail->next = newNode;		   //기존 tail next의 연결
	}
	(plist->numOfData)++;
}

void CSInsert(CircularList *plist, CLData data)
{
	int count = 0;
	CL_Node *pred = plist->tail;
	
	CL_Node *newNode = (CL_Node *)malloc(sizeof(CL_Node));
	//원형 링크리스트의 노드를 동적 생성
	newNode->data = data;	//데이터 삽입

	while(count < (plist->numOfData) && plist->comp(data, pred->next->data) != 0)
	{
		//(자료의 갯수만큼 && 비교기준에 충족할 때 까지) 반복
		pred = pred->next;
		count++;
	}

	//pred->next에 newNode를 연결
	newNode->next = pred->next; 
	pred->next = newNode;

	if(pred == plist->tail) //pred가 꼬리였다면
		plist->tail = newNode; //꼬리는 이제 newNode가 차지.

	(plist->numOfData)++;
}

void CTInsert(CircularList *plist, CLData data)
{
	CL_Node *newNode = (CL_Node*)malloc(sizeof(CL_Node));//동적할당
	newNode->data = data;

	if(plist->tail == NULL)			//최초 노드 삽입시
	{
		plist->tail = newNode;      //tail 노드 설정
		newNode->next = newNode;    //next가 자기 자신을 가리킴.
	}
	else
	{
		newNode->next = plist->tail->next; //newNode의 next연결
		plist->tail->next = newNode;		   //기존 tail next의 연결
		plist->tail = newNode;			   //테일 변경.
	}
	
	(plist->numOfData)++;
}

int CLFirst(CircularList *plist, CLData *pdata)
{
	if(plist->tail == NULL) //저장된 노드가 없다면
		return FALSE;

	plist->before = plist->tail;		//before = tail
	plist->cur = plist->tail->next;		//cur = tail->next

	*pdata = plist->cur->data;
	return TRUE;
}

int CLNext(CircularList *plist, CLData * pdata)
{
	if(plist->tail == NULL) //저장된 노드가 없다면
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

	if(rpos == plist->tail)	//삭제 대상이 꼬리일 경우
	{
		if(plist->tail == plist->tail->next) // 그리고 마지막 남은 노드라면
			plist->tail = NULL;
		else
			plist->tail = plist->before;
	}

	plist->before->next = plist->cur->next;	
	plist->cur = plist->before;				//삭제할 노드에서 연결 끊음

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
	plist->tail = (DL_Node*)malloc(sizeof(DL_Node)); //더미노드생성

	plist->head->prev = NULL;
	plist->head->next = plist->tail;

	plist->tail->next = NULL;
	plist->tail->prev = plist->head;

	plist->numOfData = 0;
	plist->comp = NULL;
}

void DLInsert(DBLinkedList *plist, DLData data)
{
	if(plist->comp != NULL) //정렬 기준이 있다면
		DSInsert(plist, data); //정렬 기준에 근거 노드추가
	else	//정렬 기준이 없다면
		DFInsert(plist, data); //머리에 노드 추가
}


void DFInsert(DBLinkedList *plist, DLData data)
{
	DL_Node *old = plist->head->next; //이전노드(이전 맨 앞 노드)

	DL_Node *newNode = (DL_Node*)malloc(sizeof(DL_Node));//동적할당
	newNode->data = data;

	newNode->next = old;				//(새노드next)-이전노드
	newNode->prev = plist->head;		//head-(prev새노드)

	old->prev = newNode;				//새노드-(prev이전노드)
	plist->head->next = newNode;		//(head->next) - 새노드


	(plist->numOfData)++;
}

void DTInsert(DBLinkedList *plist, DLData data)
{
	DL_Node *old = plist->tail->prev; //이전노드(이전 맨 뒤 노드)
	DL_Node *newNode = (DL_Node*)malloc(sizeof(DL_Node));//동적할당
	newNode->data = data;

	newNode->next = plist->tail;		// (새노드->next) - tail
	newNode->prev = old;				// 이전노드-(prev새노드) 연결 
	
	old->next = newNode;				// (이전노드next)-새노드 연결
	plist->tail->prev = newNode;		//	새노드 - (prevTail)

	(plist->numOfData)++;
}

void DSInsert(DBLinkedList *plist, DLData data)
{
	DL_Node *pred = plist->head;		//pred;저장할 위치
	DL_Node *predNext;
	
	DL_Node *newNode = (DL_Node *)malloc(sizeof(DL_Node));
	newNode->data = data;	//동적 생성 후 데이터 삽입

	while(pred->next != NULL && plist->comp(data, pred->next->data) != 0)
	{
		//비교기준에 충족할 때 까지 반복-끝이 아닐때d
		pred = pred->next;
	}

	if(pred->next == NULL)  //tail(더미노드)일 경우
		pred = pred->prev;	//tail 전위치로 돌려놓음


	predNext = pred->next;			//pred 다음노드

	//newNode 양옆을 연결
	newNode->next = predNext; //(새노드next) - (predNext)
	newNode->prev = pred;	  //pred - (prev새노드)			 

	//양옆 노드와 뉴노드를 연결
	pred->next = newNode;
	predNext->prev = newNode;

	(plist->numOfData)++;
}

int DLFirst(DBLinkedList *plist, DLData *pdata)
{
	if(plist->head->next == plist->tail)	//노드가 하나도 없을시
		return FALSE;

	plist->cur = plist->head->next;	//현재값을 첫번째 노드로
	*pdata = plist->cur->data;		//데이터 받아옴.
	
	return TRUE;
}

int DLNext(DBLinkedList *plist, DLData * pdata)
{
	if(plist->cur->next == plist->tail) //꼬리면 끝이므로 false리턴
		return FALSE;
	
	plist->cur = plist->cur->next;	//현재 위치를 한칸 옮겨 다음노드로
	*pdata = plist->cur->data;		//데이터 받아옴.
	return TRUE;
}

int DLPrevious(DBLinkedList * plist, DLData * pdata)
{
	if(plist->cur->prev == plist->head) //헤드면 처음이므로 false리턴
		return FALSE;

	plist->cur = plist->cur->prev;	//현재위치에서 왼쪽으로 한칸 옮김
	*pdata = plist->cur->data;		//데이터 받아옴.
	return TRUE;
}

DLData DLRemove(DBLinkedList *plist)
{
	DL_Node * rpos = plist->cur;
	DLData remv = rpos->data;

	rpos->prev->next = rpos->next;//(현재노드이전next) - 현재노드다음
	rpos->next->prev = rpos->prev;//현재노드이전 - (prev현재노드다음)

	plist->cur = plist->cur->prev; // cur위치 재조정.

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
	pstack->topIndex = -1; //초기 값이므로 top인덱스는 -1
}

int ASIsEmpty(ArrayStack * pstack)
{
	if(pstack->topIndex == -1)	//비어 있으면 TRUE 리턴
		return TRUE;
	else						//그렇지 않으면 FALSE 리턴
		return FALSE;
}

void ASPush(ArrayStack * pstack, ASData data)
{
	pstack->topIndex += 1;						//top을 증가킨뒤
	pstack->stackArr[pstack->topIndex] = data;	//해당 인덱스에 값삽입
}

ASData ASPop(ArrayStack * pstack)
{
	int rldx;

	if(ASIsEmpty(pstack))				//스택이 비어있는데 pop호출시
	{
		puts("Can't pop : Stack is empty!");
		exit(-1);
	}

	rldx = pstack->topIndex;		//rldx에 지울 인덱스 값을 넣음
	pstack->topIndex -= 1;		//top값을 1 감소

	return pstack->stackArr[rldx];
}

ASData ASPeek(ArrayStack * pstack)
{
	if(ASIsEmpty(pstack))				//스택이 비어있는데 peek호출시
	{
		puts("Can't peek : Stack is empty!");
		exit(-1);
	}

	return pstack->stackArr[pstack->topIndex];	//해당 값을 반환
}































////////////////////////////////////////////
// 6. List Stack

void LStackInit(ListStack * pstack)
{
	pstack->top = NULL;		//head(top)을 null로 초기화
}

int LSIsEmpty(ListStack * pstack)
{
	if(pstack->top == NULL)	//top이 null일때
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


//<원형큐 초기화>
void CQueueInit(CQueue * pq)
{
	pq->front = 0;
	pq->rear = 0;		//front와 rear값을 0으로 초기화
}

//<원형큐 Empty여부 확인>
int CQIsEmpty(CQueue * pq)
{
	if(pq->front == pq->rear) //front와 rear값이 같으면 비어있음
		return TRUE;
	else					  //그게아니라면 비어있지 않음.
		return FALSE;
}

int NextPosIdx(int pos)		  //다음 인덱스 참조
{
	if(pos == QUE_LEN-1)	  //전체크기-1과 현재위치가 같음
		return 0;		  //다음 인덱스 = 0 (배열인덱스를 순환시켜줌)
	else				  
		return pos+1;	  //다음 인덱스 = +1
}

//<원형큐 삽입> : rear로 삽입
void CEnqueue(CQueue * pq, CQData data)
{
	if(NextPosIdx(pq->rear) == pq->front) //rear의 다음 인덱스가 front와 같다면
	{
		puts("Queue is full!!");		  //꽉찬 것이므로 오류메시지
		exit(-1);
	}
	pq->rear = NextPosIdx(pq->rear);		//rear값을 +1
	pq->queArr[pq->rear] = data;			//data 삽입
}

//<원형큐 삭제> : front로 삭제
CQData CDequeue(CQueue * pq)
{
	if(CQIsEmpty(pq))
	{
		puts("Queue is empty!!");	//비어 있으므로 오류메시지
		exit(-1);
	}

	pq->front = NextPosIdx(pq->front);		//front를 다음 인덱스로
	return pq->queArr[pq->front];					//삭제 된 값 반환
}

//<원형큐 front의 내용확인>
CQData CQPeek(CQueue * pq)
{
	if(CQIsEmpty(pq))
	{
		puts("Queue is empty!!");	//비어 있으므로 오류메시지
		exit(-1);
	}
	return pq->queArr[NextPosIdx(pq->front)];
}





























////////////////////////////////////////////////////////////////
// 8. List Queue

//<리스트 큐 초기화>
void LQueueInit(LQueue * pq)
{
	pq->front = NULL;
	pq->rear = NULL;
}

//<리스트 큐 Empty여부 확인>
int LQIsEmpty(LQueue * pq)
{
	if(pq->front == NULL)	//front가 NULL이면 비어있는것이므로
		return TRUE;
	else
		return FALSE;
}

//<데이터 삽입>
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

//<데이터 삭제> : 가장 맨앞  데이터(front) 삭제
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

//<front의 내용확인> 
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

//<초기화 함수>
void DequeInit(Deque * pdeq)
{
	pdeq->head = NULL;
	pdeq->tail = NULL;
}

//<Empty 확인>
int DQIsEmpty(Deque * pdeq)
{
	if(pdeq->head == NULL)		//head가 NULL이면 비어있으므로
		return TRUE;
	else
		return FALSE;
}

//<앞에 삽입>
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

//<뒤에 삽입>
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

//<앞 삭제>
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

//<뒤 삭제>
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

//<front값 확인>
DQData DQGetFirst(Deque * pdeq)
{
	if(DQIsEmpty(pdeq))
	{
		printf("Deque Memory is empty!");
		exit(-1);
	}

	return pdeq->head->data;
}

//<rear값 확인>
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

//<이진트리노드 생성함수>
BT_Node * MakeBTreeNode(void)
{
	BT_Node *nd = (BT_Node*)malloc(sizeof(BT_Node)); //동적생성

	nd->left = NULL;
	nd->right = NULL;

	return nd;
}

//<데이터 얻기>
BTData GetData(BT_Node * bt)
{
	return bt->data;
}

//<데이터 저장>
void SetData(BT_Node * bt, BTData data)
{
	bt->data = data;
}

//<왼쪽 서브트리의 주소값 반환>
BT_Node * GetLeftSubTree(BT_Node * bt)
{
	return bt->left;
}

//<오른쪽 서브트리의 주소값 반환>
BT_Node * GetRightSubTree(BT_Node * bt)
{
	return bt->right;
}

//<왼쪽 서브트리를 연결>
void MakeLeftSubTree(BT_Node * main, BT_Node * sub)
{
	if(main->left != NULL)
	{
		puts("delete old node");
		free(main->left);
	}
	
	main->left = sub;
}

//<오른쪽 서브트리를 연결>
void MakeRightSubTree(BT_Node * main, BT_Node * sub)
{
	if(main->right != NULL)
	{
		puts("delete old node");
		free(main->right);
	}

	main->right = sub;
}

//<전위 탐색>
void PreorderTraverse(BT_Node * bt, VisitFuncPtr action)
{
	if(bt == NULL)
		return;

	action(bt->data);
	PreorderTraverse(bt->left, action);
	PreorderTraverse(bt->right, action);
}

//<중위 탐색>
void InorderTraverse(BT_Node * bt, VisitFuncPtr action)
{
	if(bt == NULL)
		return;

	InorderTraverse(bt->left, action);
	action(bt->data);
	InorderTraverse(bt->right, action);
}

//<후위 탐색>
void PostorderTraverse(BT_Node * bt, VisitFuncPtr action)
{
	if(bt == NULL)
		return;

	PostorderTraverse(bt->left, action);
	PostorderTraverse(bt->right, action);
	action(bt->data);
}

//<이진트리 소멸 함수>
void DeleteTree(BT_Node * bt)
{
	if(bt == NULL)
		return;

	DeleteTree(bt->left);
	DeleteTree(bt->right);

	printf("del tree data: %d \n", bt->data);
	free(bt);
}

//<왼쪽 자식 노드 제거>
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

//<오른쪽 자식 노드 제거>
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

//<왼쪽 자식 노드 변경>
void ChangeLeftSubTree(BT_Node* main, BT_Node *sub)
{
	main->left = sub;
}

//<오른쪽 자식 노드 변경>
void ChangeRightSubTree(BT_Node* main, BT_Node *sub)
{
	main->right = sub;
}





























////////////////////////////////////////////////////
// 11. 이진 탐색 트리 
//<이진 탐색트리 생성 및 초기화>
void BSTMakeAndInit(BT_Node ** pRoot)
{
	*pRoot = NULL;
}

//<노드에 저장된 데이터 반환>
BSTData BSTGetNodeData(BT_Node *bst)
{
	return GetData(bst);
}

//<데이터 삽입> : 밸런싱을 끄려면 해당함수 아래부분 리밸런싱을 주석처리
void BSTInsert(BT_Node **pRoot, BSTData data)
{
	BT_Node *pNode = NULL;	//부모 노드
	BT_Node *cNode = *pRoot;//현재 노드
	BT_Node *nNode = NULL;	//새 노드

	// 새로운 노드가 추가될 위치를 찾는다.
	while(cNode != NULL)
	{
		if(data == GetData(cNode))
			return;	//키 중복 불허

		pNode = cNode; //부모노드를 한단계 내림.

		//값 비교 : cNode의 데이터, 왼쪽 오른쪽 자식
		if(GetData(cNode) > data)
			cNode = GetLeftSubTree(cNode);
		else
			cNode = GetRightSubTree(cNode);
	}

	// pNode의 서브 노드에 추가할 새 노드의 생성
	nNode = MakeBTreeNode();	//새 노드 생성
	SetData(nNode, data);	//새 노드에 데이터 저장

	// pNode의 서브 노드에 새 노드를 추가
	if(pNode != NULL)	// 새 노드가  루트 노드가 아니라면
	{
		 if(data < GetData(pNode))
			 MakeLeftSubTree(pNode, nNode);//부모노드의 왼쪽에 새노드생성
		 else
			MakeRightSubTree(pNode, nNode);
	}
	else	// 새 노드가 루트 노드라면,
	{
		*pRoot = nNode;	//루트가 뉴노드
	}

	//////////////////////////////////////////
	*pRoot = Rebalance(pRoot);	//노드 삽입 후 리밸런싱
	//////////////////////////////////////////
}

//<데이터 탐색>
BT_Node *BSTSearch(BT_Node *bst, BSTData target)
{
	BT_Node *cNode = bst;	//현재 노드
	BSTData cd;				//현재 데이터

	//노드 탐색
	while(cNode != NULL)
	{
		cd = GetData(cNode);	//현재 노드의 데이터 얻음

		if(target == cd)		//찾으려는 데이터 비교
			return cNode;
		else if(target < cd)	//찾으려는 데이터가 현재 노드 값에 비해 작다면
			cNode = GetLeftSubTree(cNode);	//왼쪽을 검색하기 위해 왼쪽노드로 이동
		else
			cNode = GetRightSubTree(cNode);
	}

	return NULL;
}

//<데이터 삭제> : 밸런싱을 끄려면 해당함수 아래부분 리밸런싱을 주석처리
BT_Node *BSTRemove(BT_Node **pRoot, BSTData target)
{
	//삭제 대상이 루트 노드인 경우를 별도로 고려.
	//상황1 : 삭제할 노드가 단말 노드인경우
	//상황2 : 삭제할 노드가 하나의 자식 노드를 갖는경우
	//상황3 : 삭제할 노드가 두개의 자식 노드를 갖는경우
	
	BT_Node *pVRoot = MakeBTreeNode();
	//가상 루트 더미노드: 삭제노드가 루트노드일 경우도 코드를 똑같이 적용하기 위해

	BT_Node *pNode = pVRoot;	//부모 노드< 가상루트값
	BT_Node *cNode = *pRoot;	//현재 노드< 루트값
	BT_Node *dNode;				//지울 노드

	//루트 노드를 pVRoot가 가리키는 노드의 오른쪽 서브 노드가 되게 함
	ChangeRightSubTree(pVRoot, *pRoot);

	//삭제 대상을 저장한 노드 탐색
	while(cNode != NULL && GetData(cNode) != target)
	{
		pNode = cNode;

		if(target <GetData(cNode))
			cNode = GetLeftSubTree(cNode);
		else
			cNode = GetRightSubTree(cNode);
	}

	if(cNode == NULL)	// 삭제 대상이 존재하지 않는다면
		return NULL;

	dNode = cNode;		//삭제 대상을 dNode가 가리키게 함

	//상황 1 : 삭제할 노드가 단말 노드인 경우
	if(GetLeftSubTree(dNode) == NULL && GetRightSubTree(dNode) == NULL)
	{
		if(GetLeftSubTree(pNode) == dNode)
			RemoveLeftSubTree(pNode);
		else
			RemoveRightSubTree(pNode);
	}

	//상황 2 ; 하나의 자식 노드를 갖는경우
	else if(GetLeftSubTree(dNode) == NULL || GetRightSubTree(dNode) == NULL)
	{
		BT_Node *dcNode;		//delete node의 자식노드

		if(GetLeftSubTree(dNode) != NULL)//왼쪽노드존재할때
			dcNode = GetLeftSubTree(dNode);
		else
			dcNode = GetRightSubTree(dNode);

		if(GetLeftSubTree(pNode) == dNode)	//지울노드가 부모노드의 왼쪽에 달려있으면
			ChangeLeftSubTree(pNode, dcNode);
		else
			ChangeRightSubTree(pNode, dcNode);
	}

	//상황 3 : 두개의 자식 노드를 갖는 경우
	else
	{
		BT_Node *mNode;				// 제일 작은 노드
		BT_Node *mpNode;			//최소 노드의 부모노드
		BTData delData;

		//단계1
		//삭제할 노드를 대체할 노드를 찾는다.
		//삭제할 노드 : 삭제할 노드의 오른쪽 서브 트리에서 가장 작은 값
		
		mNode = GetRightSubTree(dNode);//삭제할 노드의 오른쪽 노드
		mpNode = dNode;	   //위의 부모노드

		while(GetLeftSubTree(mNode) != NULL)
		{
			mpNode = mNode;
			mNode = GetLeftSubTree(mNode);
			//삭제할 노드의 오른쪽 서브 트리에서 가장 왼쪽 = 가장작은값
		}

		//단계2
		//대체할 노드에 저장된 값을 삭제할 노드에 대입
		delData = GetData(dNode);	//대입전 데이터 백업
		SetData(dNode, GetData(mNode));//대입

		//단계3
		//대체할 노드의 부모 노드와 자식 노드를 연결
		if(GetLeftSubTree(mpNode) == mNode) //대체할 노드가 왼쪽 자식노드라면
			ChangeLeftSubTree(mpNode, GetRightSubTree(mNode));
			//대체할 노드의 자식 노드를 부모노드의 왼쪽에 연결
		else
			ChangeRightSubTree(mpNode, GetRightSubTree(mNode));
		
		//삭제한 노드를 리턴하기 위해 mNode 재활용
		dNode = mNode;				//대입
		SetData(dNode, delData);	//백업 데이터 복원
	}

	//삭제된 노드가 루트 노드인 경우에 대한 처리
	if(GetRightSubTree(pVRoot) != *pRoot)
		*pRoot = GetRightSubTree(pVRoot);

	free(pVRoot);
	//////////////////////////////////////////
	*pRoot = Rebalance(pRoot); //노드 제거후 리밸런싱
	//////////////////////////////////////////
	return dNode;
}

void ShowIntData(int data)
{
	printf("%d ", data);
}

//<데이터 출력>
void BSTShowAll(BT_Node *bst)
{
	InorderTraverse(bst, ShowIntData);
}
































////////////////////////////////////////////////////
//12. AVL트리

//LL회전
BT_Node * RotateLL(BT_Node * bst)
{
	BT_Node *pNode = bst; //이전노드
	BT_Node *cNode = GetLeftSubTree(pNode);  //현재노드

	ChangeLeftSubTree(pNode, GetRightSubTree(cNode)); //CNode의 오른쪽 자식을 pNode왼쪽으로 이동
	ChangeRightSubTree(cNode, pNode); //pNode를 cNode의 오른쪽에 연결
	return cNode;	//현재노드 리턴.
}

//RR회전
BT_Node * RotateRR(BT_Node * bst)
{
	BT_Node *pNode = bst; //이전 노드
	BT_Node *cNode = GetRightSubTree(pNode); //현재 노드

	ChangeRightSubTree(pNode, GetLeftSubTree(cNode)); //cNode의 왼쪽자식을 pNode의 오른쪽에 연결
	ChangeLeftSubTree(cNode, pNode); //cNode의 왼쪽에 pNode 에 연결. 
	return cNode;
}

//RL 회전: LL회전으로 RR상태로 만든뒤 RR회전을 사용.
BT_Node *RotateRL(BT_Node *bst)
{
	BT_Node *pNode = bst;
	BT_Node *cNode = GetRightSubTree(pNode);

	//부분적 LL 회전
	ChangeRightSubTree(pNode, RotateLL(cNode));
	//pNode의 오른쪽에 cNode-LL회전한 것을 붙여 RR상태를 만듬

	return RotateRR(pNode); // RR회전
}

//LR 회전 : RR회전으로 LL상태로 만든뒤 LL회전을 사용
BT_Node *RotateLR(BT_Node *bst)
{
	BT_Node *pNode;
	BT_Node *cNode;

	pNode = bst;
	cNode = GetLeftSubTree(pNode);

	//부분적 RR회전
	ChangeLeftSubTree(pNode, RotateRR(cNode));
	//pNode의 왼쪽에 cNode-RR회전 한 것을 붙여 LL상태로 만듬

	return RotateLL(pNode); // LL회전
}

//재귀적으로 트리의 높이를 계산화여 반환한다.
int GetHeight(BT_Node *bst)
{
	int leftH;		//left 높이
	int rightH;		//right 높이

	if(bst == NULL)
		return 0;

	//왼쪽 서브트리 높이 계산
	leftH = GetHeight(GetLeftSubTree(bst));

	//오른쪽 서브트리 높이 계산
	rightH = GetHeight(GetRightSubTree(bst));

	// 큰 값의 높이를 반환한다.
	if(leftH > rightH)
		return leftH + 1;
	else
		return rightH + 1;
}

// 두 서브 트리의 높이의 차를 반환
int GetHeightDiff(BT_Node *bst)
{
	int lsh;	// 왼쪽 서브트리 높이
	int rsh;	// 오른쪽 서브트리 높이

	if(bst == NULL)	// 노드가 하나도 없으면 0 반환
		return 0;

	lsh = GetHeight(GetLeftSubTree(bst));  //왼쪽 서브트리 높이
	rsh = GetHeight(GetRightSubTree(bst)); //오른쪽 서브트리 높이

	return lsh - rsh; //높이 차를 반환
}


// 트리의 균형을 잡는다.
BT_Node * Rebalance(BT_Node ** pRoot)
{
	int hDiff = GetHeightDiff(*pRoot);

	if(hDiff > 1)	// 왼쪽 서브 트리 방향으로 높이가 2이상 크다면
	{
		if(GetHeightDiff(GetLeftSubTree(*pRoot)) > 0) //LL상태라면
			*pRoot = RotateLL(*pRoot);				  //LL회전
		else
			*pRoot = RotateLR(*pRoot);				  //LR회전
	}
	if(hDiff < -1) // 오른쪽 서브 트리 방향으로 즉 -2 이하면
	{
		if(GetHeightDiff(GetRightSubTree(*pRoot)) < 0) //RR상태라면
			*pRoot = RotateRR(*pRoot);				   //RR회전
		else
			*pRoot = RotateRL(*pRoot);				   //RL회전
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
	if(ph->numOfData == 0)	//힙 안의 데이터 개수확인
		return TRUE;
	else
		return FALSE;
}

int GetParentIDX(int idx)
{
	return idx/2;
}

//왼쪽 자식 노드의 인덱스 값 반환
int GetLChildIDX(int idx)
{
	return idx*2;
}

//오른쪽 자식 노드의 인덱스 값 반환
int GetRChildIDX(int idx)
{
	return GetLChildIDX(idx)+1;
}

//두 개의 자식 노드 중 높은 우선순위가 높은 자식 노드 인덱스 값 반환
//자식 노드가 없으면 0을 반환, 자식 노드가 하나인 경우 그 노드의 인덱스값 반환
int GetHiPriChildIDX(Heap *ph, int idx)
{
	if(GetLChildIDX(idx) > ph->numOfData) //자식 노드가 존재하지 않으면
		return 0;
	
	else if(GetLChildIDX(idx) == ph->numOfData) //자식노드가 하나면
		return GetLChildIDX(idx);
	else //자식 노드가 둘다 존재한다면
	{
		//오른쪽 자식 노드의 우선순위가 높다면
		if(ph->comp(ph->heapArr[GetLChildIDX(idx)], ph->heapArr[GetRChildIDX(idx)]) < 0 )
			return GetRChildIDX(idx); //오른쪽 자식 노드의 인덱스값 반환
		else
			return GetLChildIDX(idx);
	}
}


void HInsert(Heap * ph, HData data)
{
	int idx = ph->numOfData+1; //힙 내의 인덱스

	while(idx != 1) //idx가 루트노드 일때까지
	{
		//data와 마지막 노드의 부모노드를 비교
		if(ph->comp(data, ph->heapArr[GetParentIDX(idx)]) > 0)
		{
			ph->heapArr[idx] = ph->heapArr[GetParentIDX(idx)];
			//idx위치와 부모노드의 위치 바꿈
			idx = GetParentIDX(idx); //idx값은 기존 부모의 idx값
		}
		else //현재 상태가 조건에 만족.
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

	HData retData = ph->heapArr[1]; //지울 데이터 임시저장
	HData lastElem = ph->heapArr[ph->numOfData];//마지막 위치노드 데이터값 저장

	

	//원리 : 마지막 노드를 루트노드의 자리로 옮긴 다음에,
	//자식 노드와의 비교를 통해 제자리를 찾아가게 한다.

	//GetHiPriChildIDX(ph, parentIdx)
	//>두 자식 노드 중 우선순위가 높은 것의 인덱스
	//>자식노드가 없으면 0, 하나 있으면 그 노드의 인덱스
	//chilIdx 에 GetHiPriChildIdx의 결과를 넣고 반복문시작
	while(childIdx = GetHiPriChildIDX(ph, parentIdx))
	{
		//마지막 노드와 GetHiPriChildIdx의 결과의 우선순위 비교
		if(ph->comp(lastElem, ph->heapArr[childIdx]) >= 0)
			break; // 마지막 노드의 우선순위가 높으면 반복문 탈출

		//마지막 노드보다 우선순위 높으니, 비교대상 노드의 위치를  한 레벨 올림
		ph->heapArr[parentIdx] = ph->heapArr[childIdx];
		//부모노드와 위치 바꿈.
		parentIdx = childIdx; //위치 바꿨으니 idx값도 자식idx값으로
	} //반복문 탈출하면 parentIdx에는 마지막 노드의 위치정보 저장

	ph->heapArr[parentIdx] = lastElem;	//마지막 노드 최종 저장
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
//<테이블 초기화>
void TBInit(Table *pt, HashFunc *f)
{
	int i;

	for(i=0; i<MAX_TBL; i++)		//테이블 상태를 EMPTY로 초기화
		(pt->tb[i]).status = EMPTY;

	pt->hf = f;					    //해쉬 함수 등록
}

//<테이블에 키와 값을 저장>
void TBInsert(Table *pt, Key k, Value v)
{
	int hv = pt->hf(k);			//해쉬함수로 키값 생성
	pt->tb[hv].val = v;			//해당 키값에 Value 저장
	pt->tb[hv].key = k;			//실제 키값(변환전) 저장
	pt->tb[hv].status = INUSE;
}

//<데이터 삭제>
Value TBDelete(Table *pt, Key k)
{
	int hv = pt->hf(k);			//해쉬함수로 키값 생성
	
	if((pt->tb[hv]).status != INUSE)	//사용중이 아니라면
	{
		return NULL;				//데이터가 존재하지 않음
	}
	else
	{
		(pt->tb[hv]).status = DELETED;	//status 를 DELETED로 변경
		return (pt->tb[hv]).val;			//삭제한 값 반환
	}
}

//<데이터 탐색>
Value TBSearch(Table *pt, Key k)
{
	int hv = pt->hf(k);			//해쉬함수로 키값 생성

	if((pt->tb[hv]).status != INUSE)//사용중이 아니라면
		return NULL;				//데이터가 존재하지 않음
	else
		return (pt->tb[hv]).val;		//해당 인덱스값 반환
}















////////////////////////////////////////////////////////
//15. Chaining : 별도 파일 구현






















///////////////////////////////////////////////////////
//16. List Base Graph

int WhoIsPrecede(int data1, int data2);

// 그래프의 초기화
void LGraphInit(LGraph *pg, int nv)
{
	int i;

	pg->adjList = (LinkedList*)malloc(sizeof(LinkedList)*nv);//정점(nv) 개수만큼 동적할당
	pg->numV = nv;
	pg->numE = 0;		//초기의 간선 수 0개

	for(i=0; i<nv; i++) //nv : 전달받은 정점의 개수
	{
		ListInit(&(pg->adjList[i])); //정점마다 리스트 초기화.
		SetSortRule(&(pg->adjList[i]), WhoIsPrecede); //리스트의 정렬기준 설정->출력의 형태를 보기 좋게 하기 위함. 없어도 무관
	}

	//탐색 정보 등록을 위한 공간의 할당 및 초기화
	pg->visitInfo = (int *)malloc(sizeof(int)*pg->numV);
	memset(pg->visitInfo, 0, sizeof(int) * pg->numV);
}


//그래프의 리소스를 해제
void LGraphDestroy(LGraph *pg)
{
	if(pg->adjList != NULL)
		free(pg->adjList);

	if(pg->visitInfo != NULL)
		free(pg->visitInfo);
}

//간선의 추가
void LAddEdge(LGraph *pg, int fromV, int toV)
{
	LInsert(&(pg->adjList[fromV]), toV);	//정점 fromV의 연결 리스트에 정점 toV의 정보 추가.
	LInsert(&(pg->adjList[toV]), fromV);	
	pg->numE += 1;	//간선 수 +1
}

//유틸리티 함수 : 간선의 정보 출력
void ShowLGraphEdgeInfo(LGraph *pg)
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

int WhoIsPrecede(int data1, int data2)
{
	if(data1 < data2)
		return 0;
	else
		return 1;
}

//정점 방문
int VisitVertex(LGraph *pg, int visitV)
{
	if(pg->visitInfo[visitV] == 0)
	{
		pg->visitInfo[visitV] = 1;	//방문한 곳은 1로 초기화
		printf("%c ", visitV + 65);
		return TRUE;
	}

	return FALSE;
}

// Depth First Search : 정점의 정보 출력
void DFShowGraphVertex(LGraph *pg, int startV)
{
	ArrayStack stack;
	int visitV = startV;
	int nextV;

	//DFS를 위한 스택의 초기화
	AStackInit(&stack);

	VisitVertex(pg, visitV);	// 시작 정점 방문
	ASPush(&stack, visitV);		// 방문한 정점 스택에 삽입

	while(LFirst(&(pg->adjList[visitV]), &nextV) == TRUE) //참조성공시
	{
		int visitFlag = FALSE;

		if(VisitVertex(pg, nextV) == TRUE)	//정점을 아직 방문하지않았다면
		{
			ASPush(&stack, visitV);	//방문한 정점 스택에 삽입
			visitV = nextV;			
			visitFlag = TRUE;		//방분했다고 표시
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
void BFShowGraphVertex(LGraph *pg, int startV)
{
	CQueue queue;
	int visitV = startV;
	int nextV;

	// DFS를 위한 큐의 초기화
	CQueueInit(&queue);

	//시작 정점 탐색
	VisitVertex(pg, visitV);

	while(LFirst(&(pg->adjList[visitV]), &nextV) == TRUE)
	{
		if(VisitVertex(pg, nextV) == TRUE)	//방문에 성공했다면
			CEnqueue(&queue, nextV);

		while(LNext(&(pg->adjList[visitV]), &nextV) == TRUE)
		{
			if(VisitVertex(pg, nextV) == TRUE)	//방문성공시 큐에 삽입
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
















///////////////////////////////////////////////////////////////////////
//17. Minimum cost Spanning Tree : Kruskal algorithm
//추가파일에 별도 구현