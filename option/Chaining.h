#pragma once

#include <stdio.h>
#include <stdlib.h>
#include "C:\Users\june\Desktop\������Ʈ\�ڷᱸ��\DSPackege.h"
#include "Slot.h"

////////////////////////////////////////////////////
//15. Chaining
///

//**** Linked List ������Ͽ��� LData�� ���������� �����ؾ��Ѵ�.
//typedef CSlot LData;



///// ���� TABLE
#define MAX_CTBL	100			//TABLE �ִ� �ڷ� ����
typedef int HashFunc(Key k);	//1�� �ؽ��Լ� ������

typedef struct __table
{
	LinkedList tb[MAX_CTBL];  
	HashFunc *hf;
}CTable;

//<���̺� �ʱ�ȭ>
void CTBInit(CTable *pt, HashFunc *f);
//main�� �ؽ� �Լ� ������ ����, CTBInit(&myTbl, MyHashFunc)�� ���.
/*ex
int MyHashFunc(int k)
{
	return k % 100;    // Ű�� �κ������θ� ����� ���� ���� ���� �ؽ��� ��!!!
}
*/

//<���̺� Ű�� ���� ����>
void CTBInsert(CTable *pt, Key k, Value v);

//<������ ����>
Value CTBDelete(CTable *pt, Key k);
//���� : ���� ������-������ ��/ ������ �������� ������ NULL

//<������ Ž��>
Value CTBSearch(CTable *pt, Key k);
//���� : Ž�� ������-ã�� ��/ ������ �������� ������ NULL
