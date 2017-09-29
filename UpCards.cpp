#include "UpCards.h"

CUpCards::CUpCards(void)
{
	//ָ�����
	memset(m_pUpHead,0,4*4);
	memset(m_pUpEnd,0,4*4);
	m_hbackBitmap = NULL; 
	m_nLinkID = -1;
	m_nUpLinkID = -1;
	
}

CUpCards::~CUpCards(void)
{	
	//�����ͷſռ�
	List* temp = NULL;
	for(int i=0;i<4;i++)
	{
		while(NULL!=m_pUpHead[i])
		{
			temp = m_pUpHead[i];
			m_pUpHead[i] = m_pUpHead[i]->m_pNext;
			delete temp;
		
		}
	
	
	}
}
//��ʼ��
void CUpCards::InitUpCards(HINSTANCE hInstance)
{
	m_hbackBitmap = LoadBitmap(hInstance,MAKEINTRESOURCE(IDB_BITMAP58));
	
}
//������
void CUpCards::ShowCards(HDC hMemDC)
{
	//����������DC
	HDC hDc = CreateCompatibleDC(hMemDC);
	
	for(int i = 0; i<4;i++)
	{
		
		if(NULL!=m_pUpHead[i])
		{
			SelectObject(hDc,m_pUpEnd[i]->m_Cards.m_hCardsBitmap);
			
		}
		else{
		//��һ��λͼ
		SelectObject(hDc,m_hbackBitmap);
		
		}
		BitBlt(hMemDC,330+100*i,30,71,96,hDc,0,0,SRCCOPY);
	}
	DeleteDC(hDc);
}
bool CUpCards::CanUpRecieveCards(POINT pt,List* pMouseLinkHead)
{
	
	//�ж��Ƿ���һ����
	if(pMouseLinkHead->m_pNext != NULL)
	{
		return false;
	}
	//���¶�λ����ID
	int nLinkID = (pt.x -330)/100;
	
	
	if((pt.x >= 330 + nLinkID * 100 && pt.x <= 401 + nLinkID * 100) &&
		(pt.y >= 30 && pt.y <= 30 + 96))
	{	
		//�ж������Ƿ�Ϊ��
		if(m_pUpHead[nLinkID] == NULL)
		{
			if(pMouseLinkHead->m_Cards.m_nCardsNum == 1)
			{
				m_nLinkID = nLinkID;
				return true;
			}
			return false;
		}
		else
		{
			if((m_pUpEnd[nLinkID]->m_Cards.m_nCardsNum + 1 == pMouseLinkHead->m_Cards.m_nCardsNum) 
				&& (m_pUpEnd[nLinkID]->m_Cards.m_nCardsColor == pMouseLinkHead->m_Cards.m_nCardsColor))
			{
				m_nLinkID = nLinkID;
				return true;
			}
			return false;
		}
	}
	return false;
}
void CUpCards::UpRecieveCards(List* &pMouseLinkHead,List* &pMouseLinkEnd)
{
	if(m_pUpHead[m_nLinkID] == NULL)
	{
		m_pUpHead[m_nLinkID] = pMouseLinkHead;
		m_pUpEnd[m_nLinkID] = pMouseLinkEnd;
	}
	else
	{
		m_pUpEnd[m_nLinkID]->m_pNext = pMouseLinkHead;
		pMouseLinkHead->m_pPre = m_pUpEnd[m_nLinkID];
		m_pUpEnd[m_nLinkID] = pMouseLinkEnd;

	
	}
	pMouseLinkHead = NULL;
	pMouseLinkEnd = NULL;

	//�޸�����
	m_pUpEnd[m_nLinkID]->m_x = 330 + m_nLinkID * 100;
	m_pUpEnd[m_nLinkID]->m_y = 30;
}
bool CUpCards::CanMouseGetUpCards(POINT pt)
{
	//������
	int nLinkID = (pt.x -330)/100;
	if((pt.x >= 330 + nLinkID * 100 && pt.x <= 401 + nLinkID * 100) &&
		(pt.y >= 30 && pt.y <= 30 + 96))
	{	
		//�ж������Ƿ�Ϊ��
		if(m_pUpHead[nLinkID] != NULL)
		{
			m_nUpLinkID = nLinkID;
			return true;	
		}
		return false;
	}
	return false;
}
void CUpCards::MouseGetUpCards(List* &pMouseLinkHead,List* &pMouseLinkEnd)
{
	if(m_pUpHead[m_nUpLinkID] == m_pUpEnd[m_nUpLinkID])
	{
		pMouseLinkHead = m_pUpHead[m_nUpLinkID];
		pMouseLinkEnd = m_pUpEnd[m_nUpLinkID];
		m_pUpHead[m_nUpLinkID] = NULL;
		m_pUpEnd[m_nUpLinkID] = NULL;
	}
	else
	{
		pMouseLinkHead = m_pUpEnd[m_nUpLinkID];
		pMouseLinkEnd = m_pUpEnd[m_nUpLinkID];
		
		m_pUpEnd[m_nUpLinkID] = m_pUpEnd[m_nUpLinkID]->m_pPre;
		m_pUpEnd[m_nUpLinkID]->m_pNext = NULL;
		pMouseLinkHead->m_pPre = NULL;
	}

}
void CUpCards::RevcertUpCards(List* &pMouseLinkHead,List* &pMouseLinkEnd)
{
	if(m_pUpHead[m_nUpLinkID] == NULL)
	{
		m_pUpHead[m_nUpLinkID] = pMouseLinkHead;
		m_pUpEnd[m_nUpLinkID] = pMouseLinkEnd;
	}
	else
	{
		m_pUpEnd[m_nUpLinkID]->m_pNext = pMouseLinkHead;
		pMouseLinkHead->m_pPre = m_pUpEnd[m_nUpLinkID];
		m_pUpEnd[m_nUpLinkID] = pMouseLinkHead;
	}
		pMouseLinkHead = NULL;
		pMouseLinkEnd = NULL;
}
bool CUpCards::CanWin()
{
	for(int i = 0; i < 4;i++)
	{
		if(m_pUpEnd[i] == NULL || m_pUpEnd[i]->m_Cards.m_nCardsNum != 13)
		{
			return false;
		}
	
	}
	return true;


}