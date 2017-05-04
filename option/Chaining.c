#include "Chaining.h"


///////////////////////////////////////////////////////////
//15. Chaining

//<���̺� �ʱ�ȭ>
void CTBInit(CTable *pt, HashFunc *f)
{
	int i;

	for(i=0; i<MAX_CTBL; i++)
		ListInit(&(pt->tb[i]));	//i�� ��ŭ�� ����Ʈ�� �ʱ�ȭ

	pt->hf = f;	//�ؽ� �Լ� ��� 
}


//<���̺� Ű�� ���� ����>
void CTBInsert(CTable *pt, Key k, Value v)
{
	int hv = pt->hf(k);	// �ؽ��Լ��� ����� Ű�� �����ѵ� Ű�� ����
	CSlot ns = {k, v};	// Ű�� ���� ����
	//LData ns;


	if(CTBSearch(pt, k) != NULL) // Ű�� �ߺ��Ǿ��ٸ�(�ƿ� ������ ��)
	{
		puts("Key overlap!");
		return;
	}
	else						//Ű�� �ߺ����� �ʾҴٸ� ����.
	{
		LInsert(&(pt->tb[hv]), ns);
	}
}

//<������ ����>
Value CTBDelete(CTable *pt, Key k)
{
	int hv = pt->hf(k); // �ؽ��Լ��� ����� Ű�� �����ѵ� Ű�� ����
	CSlot cSlot;		// Ž�� �� ���� �޾ƿ� ���� ����

	if(LFirst(&(pt->tb[hv]), &cSlot))	//ù��°�� ����
	{
		if(cSlot.key == k)		//�ش� Ű�� �����
		{
			 LRemove(&(pt->tb[hv]));
			 return cSlot.val;	//������ �� ����
		}
		else
		{
			while(LNext(&(pt->tb[hv]), &cSlot)) //�ε��� hv ����Ʈ�� ������ ����
			{
				if(cSlot.key == k)	//�ش�Ű �����
				{
					LRemove(&(pt->tb[hv]));
					return cSlot.val;
				}
			}
		
		}
	}
	return NULL;
}

//<������ Ž��>
Value CTBSearch(CTable *pt, Key k)
{
	int hv = pt->hf(k); // �ؽ��Լ��� ����� Ű�� �����ѵ� Ű�� ����
	CSlot cSlot;		// Ž�� �� ���� �޾ƿ� ���� ����

	if(LFirst(&(pt->tb[hv]), &cSlot))	//hv�ε��� ����Ʈ�� ù��° ���� Ž��
	{
		if(cSlot.key == k)				//ù��° ������ Ű���� ��ġ�ϸ�
		{
			return cSlot.val;			//�ش罽���� ���� ��ȯ
		}
		else
		{
			while(LNext(&(pt->tb[hv]), &cSlot))	//���� ������ ����
			{
				if(cSlot.key == k)
					return cSlot.val;
			}
		}
	}

	return NULL;			//ã�� ���� ����.
}