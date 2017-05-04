#pragma once

#include <stdio.h>
#include <stdlib.h>
#include "C:\Users\june\Desktop\프로젝트\자료구조\DSPackege.h"
#include "Slot.h"

////////////////////////////////////////////////////
//15. Chaining
///

//**** Linked List 헤더파일에서 LData를 다음값으로 수정해야한다.
//typedef CSlot LData;



///// 실제 TABLE
#define MAX_CTBL	100			//TABLE 최대 자료 갯수
typedef int HashFunc(Key k);	//1차 해쉬함수 포인터

typedef struct __table
{
	LinkedList tb[MAX_CTBL];  
	HashFunc *hf;
}CTable;

//<테이블 초기화>
void CTBInit(CTable *pt, HashFunc *f);
//main에 해쉬 함수 구현해 놓고, CTBInit(&myTbl, MyHashFunc)로 등록.
/*ex
int MyHashFunc(int k)
{
	return k % 100;    // 키를 부분적으로만 사용한 별로 좋지 않은 해쉬의 예!!!
}
*/

//<테이블에 키와 값을 저장>
void CTBInsert(CTable *pt, Key k, Value v);

//<데이터 삭제>
Value CTBDelete(CTable *pt, Key k);
//리턴 : 삭제 성공시-삭제한 값/ 데이터 존재하지 않을시 NULL

//<데이터 탐색>
Value CTBSearch(CTable *pt, Key k);
//리턴 : 탐색 성공시-찾은 값/ 데이터 존재하지 않을시 NULL
