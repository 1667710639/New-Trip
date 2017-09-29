#include"CardCtrl.h"
#include<Windows.h>
#include"resource.h"
#include"DownCards.h"


//设置成员值
void CCardCtrl::SetDataValue(HWND hWnd ,HINSTANCE hInstance)
{
	m_hWnd = hWnd;
	m_hInstance = hInstance;

}//加载牌
void CCardCtrl::LoadCards()
{
	for(int i = 0;i<13;i++)//黑花
	{
		m_cardsArr[i].m_nCardsNum = i+1;
		m_cardsArr[i].m_nCardsColor = enum_cards_flower;
		m_cardsArr[i].m_hCardsBitmap = LoadBitmap(m_hInstance,MAKEINTRESOURCE(IDB_BITMAP1+i));
	}
	for(int i = 13;i<26;i++)//方块
	{
		m_cardsArr[i].m_nCardsNum = i-13+1;
		m_cardsArr[i].m_nCardsColor = enum_cards_square;
		m_cardsArr[i].m_hCardsBitmap = LoadBitmap(m_hInstance,MAKEINTRESOURCE(IDB_BITMAP1+i));
	}
	for(int i = 26;i<39;i++)//红心
	{
		m_cardsArr[i].m_nCardsNum = i-26+1;
		m_cardsArr[i].m_nCardsColor = enum_cards_heart;
		m_cardsArr[i].m_hCardsBitmap = LoadBitmap(m_hInstance,MAKEINTRESOURCE(IDB_BITMAP1+i));
	}
	for(int i = 39;i<52;i++)//黑
	{
		m_cardsArr[i].m_nCardsNum = i-39+1;
		m_cardsArr[i].m_nCardsColor = enum_cards_black;
		m_cardsArr[i].m_hCardsBitmap = LoadBitmap(m_hInstance,MAKEINTRESOURCE(IDB_BITMAP1+i));
	}

}
//初始化游戏数据
void CCardCtrl::InitGameData()
{
	m_hBackGroundBitmap = LoadBitmap(m_hInstance,MAKEINTRESOURCE(IDB_BITMAP57));
	//加载五十二张位图
	LoadCards();
	//下方链表绑定牌
	m_oDownCards.LoadDownCards(m_cardsArr,m_vtr,m_hInstance);
	//链接上方空位背景
	m_oUpCards.InitUpCards(m_hInstance);
	//左上方链表链接牌
	m_oLeftCards.InitLeftCards(m_cardsArr,m_vtr,m_hInstance);


}
//处理paint消息
void CCardCtrl::OnPaintWnd()
{
	//创建背景DC
	HDC hDc = GetDC(m_hWnd);
	//创建牌DC
	HDC hMenDC = CreateCompatibleDC(hDc);
	//绑定位图
	HBITMAP BackGroundBitmap = LoadBitmap(m_hInstance,MAKEINTRESOURCE(IDB_BITMAP57));
	SelectObject(hMenDC,BackGroundBitmap);
	
	//显示下方牌
	m_oDownCards.ShowDownCards(hMenDC);
	//显示上方牌
	m_oUpCards.ShowCards(hMenDC);
	//显示左上方牌
	m_oLeftCards.ShowLeftCards(hMenDC);
	//显示鼠标上的牌
	ShowMouseCards(hMenDC);
	//显示背景
	BitBlt(hDc,0,0,750,700,hMenDC,0,0,SRCCOPY);
	
	
	//释放DC
	DeleteDC(hMenDC);
	
	DeleteDC(hDc);

	DeleteObject(BackGroundBitmap);

}
//处理timer消息
void CCardCtrl::OnTimer(UINT nTimerID)
{

}
//键盘消息
	void CCardCtrl::OnKeyDown(UINT nKeyID)
{
	
}

void CCardCtrl::ShowMouseCards(HDC hMemDC)
{
	int nPos_X = m_LeftMouseMovePos.x - m_LeftMouseDownPos.x;
	
	int nPos_Y = m_LeftMouseMovePos.y - m_LeftMouseDownPos.y;
	
	List* temp = m_pMouseLinkHead;
	
	while(temp!=NULL )
	{
		HDC hDc =CreateCompatibleDC(hMemDC);
		
		SelectObject(hDc,temp->m_Cards.m_hCardsBitmap);
		
		BitBlt(hMemDC,temp->m_x + nPos_X,temp->m_y + nPos_Y,71,96,hDc,0,0,SRCCOPY);
		
		DeleteDC(hDc);
		
		temp = temp->m_pNext;
	}
}
void CCardCtrl::ClearValue()
{
	m_oDownCards.m_pTemp = NULL;
	m_oDownCards.m_nLinkID = -1;
	m_oDownCards.m_nRecieveID = -1;

	m_oUpCards.m_nLinkID = -1;
	m_oUpCards.m_nUpLinkID = -1;


}
//左键按下
void CCardCtrl::OnLButtonDown(POINT pt)
{
	//记录鼠标点
	m_LeftMouseDownPos = pt;
	//下方拿牌
	if(pt.y >= 156)
	{	
		if(true == m_oDownCards.CanMouseGetDownCards(pt))
		{
			//拿牌
			m_oDownCards.MouseGetDownCards(m_pMouseLinkHead,m_pMouseLinkEnd);
			this->OnPaintWnd();
			return ;

		}
	}
	//上方拿牌
	if(pt.y <= 126 && pt.x >= 330)
	{	
		if(true == m_oUpCards.CanMouseGetUpCards(pt))
		{
			//
			m_oUpCards.MouseGetUpCards(m_pMouseLinkHead,m_pMouseLinkEnd);
			this->OnPaintWnd();
			return ;
		}
	}
	if(true == m_oLeftCards.CanMouseGetLeftCards(pt))
	{
		m_oLeftCards.MouseGetLeftCards(m_pMouseLinkHead,m_pMouseLinkEnd);
		this->OnPaintWnd();
		return;
	}
	//能不能开牌
	if(true == m_oLeftCards.CanOpenCards(pt))
	{
		m_oLeftCards.OpenCards();
	}
	else
	{
		if(m_oLeftCards.m_bFalg == true)
		{
			m_oLeftCards.m_bFalg = false;
			m_oLeftCards.CloseCards();
		}
	}
	this->OnPaintWnd();
	return;
}
//右键按下
void CCardCtrl::OnRButtonDown(POINT pt)
{

}
//左键抬起
void CCardCtrl::OnLButtonUp(POINT pt)
{
	if(m_pMouseLinkHead != NULL)
	{
		
			//下方接收
			if(true == m_oDownCards.CanDownRecieveCards(pt,m_pMouseLinkHead))
			{
				m_oDownCards.DownRecieveCards(m_pMouseLinkHead ,m_pMouseLinkEnd);
				ClearValue();
				this->OnPaintWnd();
				return ;
			}
			
		
			//上方接收
			if(true == m_oUpCards.CanUpRecieveCards(pt,m_pMouseLinkHead))
			{
				m_oUpCards.UpRecieveCards(m_pMouseLinkHead ,m_pMouseLinkEnd);
				//翻牌
				if(m_oDownCards.m_nLinkID != -1 && m_oDownCards.m_pCardsEnd[m_oDownCards.m_nLinkID] != NULL)
				{
					m_oDownCards.m_pCardsEnd[m_oDownCards.m_nLinkID]->bFlag = true;
				}
				//是否赢了
				if(true == m_oUpCards.CanWin())
				{
					MessageBox(m_hWnd,"恭喜您赢得了游戏","提示",MB_OK);
				}
				ClearValue();
				this->OnPaintWnd();
				return ; 
			}
			
			if(m_oUpCards.m_nUpLinkID != -1)
			{	
				m_oUpCards.RevcertUpCards(m_pMouseLinkHead ,m_pMouseLinkEnd);
				
				ClearValue();

				this->OnPaintWnd();

				return ;
			}

			 
			if(m_oDownCards.m_nLinkID != -1)
			{	
				m_oDownCards.RevertCards(m_pMouseLinkHead ,m_pMouseLinkEnd);
				
				ClearValue();

				this->OnPaintWnd();
				
				return ; 
			}
			m_oLeftCards.ResertLeftCards(m_pMouseLinkHead ,m_pMouseLinkEnd);
			
				ClearValue();

				this->OnPaintWnd();
				
				return ; 
		}

}
//右键抬起
void CCardCtrl::OnRButtonUp(POINT pt)
{

}
//鼠标移动
void CCardCtrl::OnMouseMove(POINT pt)
{
	m_LeftMouseMovePos = pt;
	
	if(NULL != m_pMouseLinkHead)
	{
		this->OnPaintWnd();
	}
	
}
