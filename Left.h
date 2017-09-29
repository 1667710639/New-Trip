#pragma once
#include"Card.h"


class CLeft
{
public:
	CLeft(void);
public:
	~CLeft(void);
private:
	List* m_pCloseCardsHead;
	List* m_pCloseCardsEnd;
	
	List* m_pOpenCardsHead;
	List* m_pOpenCardsEnd;
	
	HBITMAP m_hBackBitmap;
public:
	bool m_bFalg;
public:
	//加载牌
	void InitLeftCards(Cards *cardsArr,vector<int>& vtr,HINSTANCE hInstance);
	//显示函数
	void ShowLeftCards(HDC hMemDC);
public:
	//能否打开牌
	bool CanOpenCards(POINT pt);

	//打开牌
	void OpenCards();
	//关闭牌
	void CloseCards();
	//能不能拿起牌
	bool CanMouseGetLeftCards(POINT pt);
	//拿牌
	void MouseGetLeftCards(List* &pMouseLinkHead,List* &pMouseLinkEnd);
	//返回
	void ResertLeftCards(List* &pMouseLinkHead,List* &pMouseLinkEnd);
};
