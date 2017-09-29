#include "DownCards.h"

using namespace std;
CDownCards::CDownCards(void)
{
	//赋值
	memset (m_pCardsHead,0,4*7);
	memset (m_pCardsEnd,0,4*7);
	m_hBackCardsBitmap = NULL;
	m_pTemp = NULL;
	m_nLinkID = -1;
	 m_nRecieveID = -1;
	

}

CDownCards::~CDownCards(void)
{
	//链表的释放
	List* temp = NULL;
	for(int i = 0;i<7;i++)
	{
		
		while(NULL!=m_pCardsHead[i])
		{
			temp = m_pCardsHead[i];
			m_pCardsHead[i] =  m_pCardsHead[i]->m_pNext; 
			delete temp;
		}
	}
}
void CDownCards::LoadDownCards(Cards *cardsArr,vector<int>& vtr,HINSTANCE hInstance)
{
	m_hBackCardsBitmap = LoadBitmap(hInstance,MAKEINTRESOURCE(IDB_BITMAP54));
	int nIndex = 0;
	for(int i = 0; i < 7 ;i++)
	{
		for(int j = 0 ; j <= i;j++)
		{
			//申请空间
			List *temp = new List;
			//成员赋值
			temp->m_Cards = cardsArr[vtr[nIndex++]];
			temp->bFlag = false;
			temp->m_x = 30+100*i;
			temp->m_y = 156+30*j;
			temp->m_pNext = NULL;
			temp->m_pPre = NULL;
			//链接链表 
			if(NULL == m_pCardsHead[i])
			{
				m_pCardsHead[i] = temp;
				
			}
			else
			{
				m_pCardsEnd[i]->m_pNext = temp;
				temp->m_pPre = m_pCardsEnd[i];
			}
			m_pCardsEnd[i] = temp;
		}
		
		m_pCardsEnd[i]->bFlag = true;
	}

}
//显示牌
void CDownCards::ShowDownCards(HDC hMenDC)
{
	List* temp =NULL;  
	for(int i = 0;i < 7;i++)
	{
		temp = m_pCardsHead[i];
		while(NULL!= temp)
		{
			HDC hDc =CreateCompatibleDC(hMenDC);
			if(temp->bFlag == true)
			{
				SelectObject(hDc,temp->m_Cards.m_hCardsBitmap);
			}
			else
			{
				SelectObject(hDc,m_hBackCardsBitmap);
			
			}
			BitBlt(hMenDC,temp->m_x,temp->m_y,71,96,hDc,0,0,SRCCOPY);
			DeleteDC(hDc);
			temp = temp->m_pNext;	
		}
	
	
	}
}
//拿牌判断
bool CDownCards::CanMouseGetDownCards(POINT pt)
{
	//确定链表
	int nLinkID = pt.x/100;
	List* temp = m_pCardsHead[nLinkID];
	while(NULL!=temp)
	{
		//拿牌是鼠标点在尾排上
		if(temp == m_pCardsEnd[nLinkID])
		{
			if((pt.x>temp->m_x && pt.x<=temp->m_x+71)&&(pt.y>temp->m_y && pt.y<=temp->m_y+96))
			{
				m_pTemp = temp; //记录被拿的牌
				m_nLinkID = nLinkID; //记录被拿牌的列数
				return true;
			}
			return false;
		}//拿牌鼠标在牌列中
		else
		{
			if((pt.x>temp->m_x && pt.x<=temp->m_x+71)&&(pt.y>=temp->m_y && pt.y<temp->m_y+30))
			{
				if(true==temp->bFlag) //判断牌是否是正面
				{
					m_pTemp = temp;//记录被拿的牌
					m_nLinkID = nLinkID;//记录被拿牌的列数
					return true;
				}
				return false;
			}
			
		}
		temp = temp->m_pNext;
	}
	return false;
}
//拿牌
void CDownCards::MouseGetDownCards(List* &pMouseLinkHead,List* &pMouseLinkEnd)
{

	if(m_pCardsHead[m_nLinkID] == m_pTemp) //判断被拿的牌是否是头牌
	{
		pMouseLinkHead = m_pCardsHead[m_nLinkID];
		pMouseLinkEnd = m_pCardsEnd[m_nLinkID];    //接收牌
		m_pCardsHead[m_nLinkID] = NULL;
		m_pCardsEnd[m_nLinkID] = NULL;
	}
	else
	{
		//先连接牌
		pMouseLinkHead = m_pTemp;
		pMouseLinkEnd = m_pCardsEnd[m_nLinkID];
		//后断
		m_pCardsEnd[m_nLinkID] = m_pTemp->m_pPre;
		m_pCardsEnd[m_nLinkID]->m_pNext = NULL;
		m_pTemp->m_pPre = NULL;
	}
	m_pTemp = NULL;
}
//放牌判断
bool CDownCards::CanDownRecieveCards(POINT pt,List* pMouseLinkHead)
{
	int nLinkID = pt.x/100; //判断鼠标大概在那列牌
	List* temp = m_pCardsHead[nLinkID];
	if(temp == NULL)
	{
		if((pt.x > nLinkID*100+30 && pt.x <= nLinkID*100+30+71)&&
		   (pt.y > 156 && pt.y <= 156+96))
		{
			if(pMouseLinkHead->m_Cards.m_nCardsNum == 13)
			{
				 m_nRecieveID = nLinkID; //记录放牌的列数
				return true;
			}
			return false;
		}
		return false;
	}
	else
	{
		//是不是尾的范围
		if((pt.x >= m_pCardsEnd[nLinkID]->m_x && pt.x <= m_pCardsEnd[nLinkID]->m_x+71)&&
		   (pt.y >= m_pCardsEnd[nLinkID]->m_y && pt.y <= m_pCardsEnd[nLinkID]->m_y+96))
		{
			if(m_pCardsEnd[nLinkID]->m_Cards.m_nCardsNum - 1 == pMouseLinkHead->m_Cards.m_nCardsNum)
			{
				if((m_pCardsEnd[nLinkID]->m_Cards.m_nCardsColor == enum_cards_black || m_pCardsEnd[nLinkID]->m_Cards.m_nCardsColor == enum_cards_flower)&&
				   (pMouseLinkHead->m_Cards.m_nCardsColor == enum_cards_square || pMouseLinkHead->m_Cards.m_nCardsColor == enum_cards_heart))
				{
					m_nRecieveID = nLinkID;
					return true;
				}
				if((m_pCardsEnd[nLinkID]->m_Cards.m_nCardsColor == enum_cards_square || m_pCardsEnd[nLinkID]->m_Cards.m_nCardsColor == enum_cards_heart)&&
				   (pMouseLinkHead->m_Cards.m_nCardsColor == enum_cards_black || pMouseLinkHead->m_Cards.m_nCardsColor == enum_cards_flower))
				{
					m_nRecieveID = nLinkID;
					return true;
				}
				return false;
			}
			return false;
		}
		return false ;
	}
	return false;
}
//放牌
void CDownCards::DownRecieveCards(List* &pMouseLinkHead,List* &pMouseLinkEnd)
{
	if(m_pCardsHead[m_nRecieveID] == NULL)
	{
		m_pCardsHead[m_nRecieveID] = pMouseLinkHead;
		m_pCardsEnd[m_nRecieveID] = pMouseLinkEnd;
		
	}
	else
	{
		m_pCardsEnd[m_nRecieveID]->m_pNext = pMouseLinkHead;
		pMouseLinkHead->m_pPre = m_pCardsEnd[m_nRecieveID];
		m_pCardsEnd[m_nRecieveID] = pMouseLinkHead;
	}
		pMouseLinkHead = NULL;
		pMouseLinkEnd = NULL; 
		List* temp = m_pCardsHead[m_nRecieveID];
		int j = 0;
		while(temp!=NULL)
		{
			temp->m_x = 30+100*m_nRecieveID;
			temp->m_y = 156+30*j;
			j++;
			temp = temp->m_pNext;
		}
		//翻牌
		if(m_pCardsHead[m_nLinkID] != NULL && m_nLinkID != -1)
			{
				m_pCardsEnd[m_nLinkID]->bFlag = true;
			}

}
void CDownCards::RevertCards(List* &pMouseLinkHead,List* &pMouseLinkEnd)
{
	//是不是NULL
	if(m_pCardsHead[m_nLinkID] == NULL)
	{
		m_pCardsHead[m_nLinkID] = pMouseLinkHead;
		m_pCardsEnd[m_nLinkID] = pMouseLinkEnd;
		pMouseLinkHead = NULL;
		pMouseLinkEnd = NULL;
	}
	else
	{
		m_pCardsEnd[m_nLinkID]->m_pNext = pMouseLinkHead;
		pMouseLinkHead->m_pPre = m_pCardsEnd[m_nLinkID];
		m_pCardsEnd[m_nLinkID] = pMouseLinkEnd;
		
	}
	pMouseLinkHead = NULL;
	pMouseLinkEnd = NULL;
}