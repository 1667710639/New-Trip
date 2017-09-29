#include"CardCtrl.h"
#include<Windows.h>
#include"resource.h"
#include"DownCards.h"


//���ó�Աֵ
void CCardCtrl::SetDataValue(HWND hWnd ,HINSTANCE hInstance)
{
	m_hWnd = hWnd;
	m_hInstance = hInstance;

}//������
void CCardCtrl::LoadCards()
{
	for(int i = 0;i<13;i++)//�ڻ�
	{
		m_cardsArr[i].m_nCardsNum = i+1;
		m_cardsArr[i].m_nCardsColor = enum_cards_flower;
		m_cardsArr[i].m_hCardsBitmap = LoadBitmap(m_hInstance,MAKEINTRESOURCE(IDB_BITMAP1+i));
	}
	for(int i = 13;i<26;i++)//����
	{
		m_cardsArr[i].m_nCardsNum = i-13+1;
		m_cardsArr[i].m_nCardsColor = enum_cards_square;
		m_cardsArr[i].m_hCardsBitmap = LoadBitmap(m_hInstance,MAKEINTRESOURCE(IDB_BITMAP1+i));
	}
	for(int i = 26;i<39;i++)//����
	{
		m_cardsArr[i].m_nCardsNum = i-26+1;
		m_cardsArr[i].m_nCardsColor = enum_cards_heart;
		m_cardsArr[i].m_hCardsBitmap = LoadBitmap(m_hInstance,MAKEINTRESOURCE(IDB_BITMAP1+i));
	}
	for(int i = 39;i<52;i++)//��
	{
		m_cardsArr[i].m_nCardsNum = i-39+1;
		m_cardsArr[i].m_nCardsColor = enum_cards_black;
		m_cardsArr[i].m_hCardsBitmap = LoadBitmap(m_hInstance,MAKEINTRESOURCE(IDB_BITMAP1+i));
	}

}
//��ʼ����Ϸ����
void CCardCtrl::InitGameData()
{
	m_hBackGroundBitmap = LoadBitmap(m_hInstance,MAKEINTRESOURCE(IDB_BITMAP57));
	//������ʮ����λͼ
	LoadCards();
	//�·��������
	m_oDownCards.LoadDownCards(m_cardsArr,m_vtr,m_hInstance);
	//�����Ϸ���λ����
	m_oUpCards.InitUpCards(m_hInstance);
	//���Ϸ�����������
	m_oLeftCards.InitLeftCards(m_cardsArr,m_vtr,m_hInstance);


}
//����paint��Ϣ
void CCardCtrl::OnPaintWnd()
{
	//��������DC
	HDC hDc = GetDC(m_hWnd);
	//������DC
	HDC hMenDC = CreateCompatibleDC(hDc);
	//��λͼ
	HBITMAP BackGroundBitmap = LoadBitmap(m_hInstance,MAKEINTRESOURCE(IDB_BITMAP57));
	SelectObject(hMenDC,BackGroundBitmap);
	
	//��ʾ�·���
	m_oDownCards.ShowDownCards(hMenDC);
	//��ʾ�Ϸ���
	m_oUpCards.ShowCards(hMenDC);
	//��ʾ���Ϸ���
	m_oLeftCards.ShowLeftCards(hMenDC);
	//��ʾ����ϵ���
	ShowMouseCards(hMenDC);
	//��ʾ����
	BitBlt(hDc,0,0,750,700,hMenDC,0,0,SRCCOPY);
	
	
	//�ͷ�DC
	DeleteDC(hMenDC);
	
	DeleteDC(hDc);

	DeleteObject(BackGroundBitmap);

}
//����timer��Ϣ
void CCardCtrl::OnTimer(UINT nTimerID)
{

}
//������Ϣ
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
//�������
void CCardCtrl::OnLButtonDown(POINT pt)
{
	//��¼����
	m_LeftMouseDownPos = pt;
	//�·�����
	if(pt.y >= 156)
	{	
		if(true == m_oDownCards.CanMouseGetDownCards(pt))
		{
			//����
			m_oDownCards.MouseGetDownCards(m_pMouseLinkHead,m_pMouseLinkEnd);
			this->OnPaintWnd();
			return ;

		}
	}
	//�Ϸ�����
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
	//�ܲ��ܿ���
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
//�Ҽ�����
void CCardCtrl::OnRButtonDown(POINT pt)
{

}
//���̧��
void CCardCtrl::OnLButtonUp(POINT pt)
{
	if(m_pMouseLinkHead != NULL)
	{
		
			//�·�����
			if(true == m_oDownCards.CanDownRecieveCards(pt,m_pMouseLinkHead))
			{
				m_oDownCards.DownRecieveCards(m_pMouseLinkHead ,m_pMouseLinkEnd);
				ClearValue();
				this->OnPaintWnd();
				return ;
			}
			
		
			//�Ϸ�����
			if(true == m_oUpCards.CanUpRecieveCards(pt,m_pMouseLinkHead))
			{
				m_oUpCards.UpRecieveCards(m_pMouseLinkHead ,m_pMouseLinkEnd);
				//����
				if(m_oDownCards.m_nLinkID != -1 && m_oDownCards.m_pCardsEnd[m_oDownCards.m_nLinkID] != NULL)
				{
					m_oDownCards.m_pCardsEnd[m_oDownCards.m_nLinkID]->bFlag = true;
				}
				//�Ƿ�Ӯ��
				if(true == m_oUpCards.CanWin())
				{
					MessageBox(m_hWnd,"��ϲ��Ӯ������Ϸ","��ʾ",MB_OK);
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
//�Ҽ�̧��
void CCardCtrl::OnRButtonUp(POINT pt)
{

}
//����ƶ�
void CCardCtrl::OnMouseMove(POINT pt)
{
	m_LeftMouseMovePos = pt;
	
	if(NULL != m_pMouseLinkHead)
	{
		this->OnPaintWnd();
	}
	
}
