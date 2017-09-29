#pragma once
#include"Card.h"


using namespace std;
class CDownCards
{
public:
	CDownCards(void);
public:
	~CDownCards(void);
public:
	
	List* m_pCardsHead[7];
	List* m_pCardsEnd[7];
	HBITMAP m_hBackCardsBitmap;
public:
	List* m_pTemp;
	int m_nLinkID; //拿牌列数
	int m_nRecieveID;//放牌列数
public:
	void LoadDownCards(Cards *cardsArr,vector<int>& vtr,HINSTANCE hInstance);
	void ShowDownCards(HDC hMenDC);
public:
	bool CanMouseGetDownCards(POINT pt);
	void MouseGetDownCards(List* &pMouseLinkHead,List* &pMouseLinkEnd);
	
	bool CanDownRecieveCards(POINT pt,List* pMouseLinkHead);
	void DownRecieveCards(List* &pMouseLinkHead,List* &pMouseLinkEnd);
	
	void RevertCards(List* &pMouseLinkHead,List* &pMouseLinkEnd);
};
