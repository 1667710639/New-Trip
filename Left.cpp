#include "Left.h"

using namespace std;
CLeft::CLeft(void)
{
	 m_pCloseCardsHead =NULL;
	 m_pOpenCardsHead = NULL;
	 m_pCloseCardsEnd = NULL;
	 m_pOpenCardsEnd =NULL;
	 m_hBackBitmap = NULL;
	 m_bFalg = false;

}

CLeft::~CLeft(void)
{
	//�ͷ�����
	List* temp = m_pCloseCardsHead;
	while(NULL!=m_pCloseCardsHead)
	{
		temp = m_pCloseCardsHead;
		m_pCloseCardsHead = m_pCloseCardsHead->m_pNext;
		delete temp;
	}
	
	
	while(NULL!=m_pOpenCardsHead)
	{
		temp = m_pOpenCardsHead;
		m_pOpenCardsHead = m_pOpenCardsHead->m_pNext;
		delete temp;
	}
}
void CLeft::InitLeftCards(Cards *cardsArr,vector<int>& vtr,HINSTANCE hInstance)
{
		m_hBackBitmap = LoadBitmap(hInstance,MAKEINTRESOURCE(IDB_BITMAP54));
		int nIndex = 28;
		for(int i =0;i<24;i++)
		{
			//����ռ�
			List *temp = new List;
			//��Ա��ֵ
			temp->m_Cards = cardsArr[vtr[nIndex++]];
			temp->bFlag = true;
			temp->m_x = 30+3*i;
			temp->m_y = 30;
			temp->m_pNext = NULL;
			temp->m_pPre = NULL;
			//�������� 
			if(NULL == m_pCloseCardsHead)
			{
				m_pCloseCardsHead = temp;
				
			}
			else
			{
				m_pCloseCardsEnd->m_pNext = temp;
				temp->m_pPre = m_pCloseCardsEnd;
			}
			m_pCloseCardsEnd = temp;
	}
		
		
}
void CLeft::ShowLeftCards(HDC hMenDC)
{
	List* temp = m_pCloseCardsHead;
	//��ʾ�ر��б�
	while(NULL!=temp)
	{
		HDC hDc = CreateCompatibleDC(hMenDC);
			
		SelectObject(hDc,m_hBackBitmap);
			
		BitBlt(hMenDC,temp->m_x,temp->m_y,71,96,hDc,0,0,SRCCOPY);
			
		DeleteDC(hDc);
			
		
		temp = temp->m_pNext;
		
	
	}
	//��ʾ�Ǵ�����
	temp = m_pOpenCardsHead;
	while(NULL!=temp)
	{
		HDC hDc = CreateCompatibleDC(hMenDC);
			
		SelectObject(hDc,temp->m_Cards.m_hCardsBitmap);
			
		BitBlt(hMenDC,temp->m_x,temp->m_y,71,96,hDc,0,0,SRCCOPY);
			
		DeleteDC(hDc);
			
		temp = temp->m_pNext;
		
	

}
	
	
}
bool CLeft::CanOpenCards(POINT pt)
{
	if(m_pCloseCardsHead == NULL)
	{
		if((pt.x >= 30 && pt.x <= 101)&& pt.y >= 30 && pt.y <= 126)
		{
			m_bFalg = true;
			return false;
		}
	}
	else
	{
		if((pt.x >= m_pCloseCardsEnd->m_x && pt.x <= m_pCloseCardsEnd->m_x + 71) && 
			(pt.y >=m_pCloseCardsEnd->m_y && pt.y <= m_pCloseCardsEnd->m_y + 96))
		{
			return true;
		}
		
	}
	return false ;

}
void CLeft::OpenCards()
{
	//�Ѿ��򿪵��Ƶ���һ��
	List* temp = m_pOpenCardsHead;
	while(temp != NULL)
	{
		temp->m_x = 190;
		temp->m_y = 30;
		temp = temp->m_pNext;
	}
	for(int i = 0; i < 3 ; i++)
	{	
		//��סβ,�Ͽ��ڵ�
		temp = m_pCloseCardsEnd ;
		if(temp == NULL)
		{
			return;
		}
		else if(m_pCloseCardsHead == temp)
		{
			m_pCloseCardsHead = NULL;
			m_pCloseCardsEnd = NULL;
		}
		else
		{
			//
			m_pCloseCardsEnd = m_pCloseCardsEnd->m_pPre;
			m_pCloseCardsEnd->m_pNext = NULL;

			temp->m_pPre = NULL;
		}
		//���ӽڵ�
		if(m_pOpenCardsHead == NULL)
		{
			m_pOpenCardsHead = temp ;
			m_pOpenCardsEnd = temp;
		}
		else
		{
			m_pOpenCardsEnd->m_pNext = temp;
			temp->m_pPre = m_pOpenCardsEnd;
			
		}
		m_pOpenCardsEnd = temp ;
		//�޸�����
		m_pOpenCardsEnd->m_x = 190 +20 * i ;
		m_pOpenCardsEnd->m_y = 30 ;
	} 
}
void CLeft::CloseCards()
{
	int i = 0 ;
	//��Ǵ������β
	List* temp = NULL;
	while( m_pOpenCardsHead!= NULL)
	{
		temp = m_pOpenCardsEnd;
		if(m_pOpenCardsHead == m_pOpenCardsEnd)
		{
			m_pOpenCardsHead = NULL;
			m_pOpenCardsEnd = NULL;

		}
		else
		{
			m_pOpenCardsEnd = m_pOpenCardsEnd->m_pPre;
			m_pOpenCardsEnd->m_pNext = NULL;
			temp->m_pPre = NULL;
		}
		//���ر������β���
		if(m_pCloseCardsHead == NULL)
		{
			m_pCloseCardsHead = temp ;
			m_pCloseCardsEnd = temp;
		}
		else
		{
			m_pCloseCardsEnd->m_pNext = temp ;
			temp->m_pPre = m_pCloseCardsEnd;
		}
		m_pCloseCardsEnd = temp ;
		//�޸�����
		m_pCloseCardsEnd->m_x = 30 + 3*i;
		i++;
		m_pCloseCardsEnd->m_y = 30 ;
	}
}
bool CLeft::CanMouseGetLeftCards(POINT pt)
{
	if(m_pOpenCardsHead != NULL)
	{
		if((pt.x >= m_pOpenCardsEnd->m_x && pt.x <= m_pOpenCardsEnd->m_x + 71) 
			&&(pt.y >= 30 && pt.y <= 30+96))
		{
			return true;
		}
		return false;
	}
	return false;
	


}
void CLeft::MouseGetLeftCards(List* &pMouseLinkHead,List* &pMouseLinkEnd)
{
	if(m_pOpenCardsHead == m_pOpenCardsEnd)
	{
		pMouseLinkHead = m_pOpenCardsHead;
		pMouseLinkEnd = m_pOpenCardsEnd;
		m_pOpenCardsHead = NULL;
		m_pOpenCardsEnd = NULL;
	}
	else
	{
		pMouseLinkHead = m_pOpenCardsEnd;
		pMouseLinkEnd = m_pOpenCardsEnd;
		
		m_pOpenCardsEnd = m_pOpenCardsEnd->m_pPre;
		m_pOpenCardsEnd->m_pNext = NULL;
		
		pMouseLinkHead->m_pPre = NULL;
		
	}


}
void CLeft::ResertLeftCards(List* &pMouseLinkHead,List* &pMouseLinkEnd)
{
	if(m_pOpenCardsHead == NULL)
	{
		m_pOpenCardsHead = pMouseLinkHead;
		m_pOpenCardsEnd = pMouseLinkEnd;
		
		
	}
	else
	{
		m_pOpenCardsEnd->m_pNext = pMouseLinkHead;
		pMouseLinkHead->m_pPre = m_pOpenCardsEnd;
		m_pOpenCardsEnd = pMouseLinkHead;
	}
	pMouseLinkHead = NULL;
	pMouseLinkEnd = NULL;

}