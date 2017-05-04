#include "Chaining.h"


///////////////////////////////////////////////////////////
//15. Chaining

//<테이블 초기화>
void CTBInit(CTable *pt, HashFunc *f)
{
	int i;

	for(i=0; i<MAX_CTBL; i++)
		ListInit(&(pt->tb[i]));	//i개 만큼의 리스트를 초기화

	pt->hf = f;	//해쉬 함수 등록 
}


//<테이블에 키와 값을 저장>
void CTBInsert(CTable *pt, Key k, Value v)
{
	int hv = pt->hf(k);	// 해쉬함수를 사용해 키를 생성한뒤 키를 저장
	CSlot ns = {k, v};	// 키와 값을 저장
	//LData ns;


	if(CTBSearch(pt, k) != NULL) // 키가 중복되었다면(아예 동일한 값)
	{
		puts("Key overlap!");
		return;
	}
	else						//키가 중복되지 않았다면 삽입.
	{
		LInsert(&(pt->tb[hv]), ns);
	}
}

//<데이터 삭제>
Value CTBDelete(CTable *pt, Key k)
{
	int hv = pt->hf(k); // 해쉬함수를 사용해 키를 생성한뒤 키를 저장
	CSlot cSlot;		// 탐색 후 값을 받아올 슬롯 생성

	if(LFirst(&(pt->tb[hv]), &cSlot))	//첫번째값 참조
	{
		if(cSlot.key == k)		//해당 키가 존재시
		{
			 LRemove(&(pt->tb[hv]));
			 return cSlot.val;	//삭제한 값 리턴
		}
		else
		{
			while(LNext(&(pt->tb[hv]), &cSlot)) //인덱스 hv 리스트의 다음값 참조
			{
				if(cSlot.key == k)	//해당키 존재시
				{
					LRemove(&(pt->tb[hv]));
					return cSlot.val;
				}
			}
		
		}
	}
	return NULL;
}

//<데이터 탐색>
Value CTBSearch(CTable *pt, Key k)
{
	int hv = pt->hf(k); // 해쉬함수를 사용해 키를 생성한뒤 키를 저장
	CSlot cSlot;		// 탐색 후 값을 받아올 슬롯 생성

	if(LFirst(&(pt->tb[hv]), &cSlot))	//hv인덱스 리스트의 첫번째 슬롯 탐색
	{
		if(cSlot.key == k)				//첫번째 슬롯의 키값이 일치하면
		{
			return cSlot.val;			//해당슬롯의 값을 반환
		}
		else
		{
			while(LNext(&(pt->tb[hv]), &cSlot))	//다음 슬롯을 참조
			{
				if(cSlot.key == k)
					return cSlot.val;
			}
		}
	}

	return NULL;			//찾는 값이 없음.
}