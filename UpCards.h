#pragma once
#include"Card.h"

class CUpCards
{
public:
	CUpCards(void);
public:
	~CUpCards(void);
private:
	HBITMAP m_hbackBitmap;
public:
	List *m_pUpHead[4];
	List *m_pUpEnd[4];
	int m_nLinkID;
	int m_nUpLinkID;
public:
	void InitUpCards(HINSTANCE hInstance);
	void ShowCards(HDC hMemDC);
	bool CanWin();
public:
	bool CanUpRecieveCards(POINT pt,List* pMouseLinkHead);
	void UpRecieveCards(List* &pMouseLinkHead,List* &pMouseLinkEnd);
	bool CanMouseGetUpCards(POINT pt);
	void MouseGetUpCards(List* &pMouseLinkHead,List* &pMouseLinkEnd);
	void RevcertUpCards(List* &pMouseLinkHead,List* &pMouseLinkEnd);
};
