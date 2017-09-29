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
	//������
	void InitLeftCards(Cards *cardsArr,vector<int>& vtr,HINSTANCE hInstance);
	//��ʾ����
	void ShowLeftCards(HDC hMemDC);
public:
	//�ܷ����
	bool CanOpenCards(POINT pt);

	//����
	void OpenCards();
	//�ر���
	void CloseCards();
	//�ܲ���������
	bool CanMouseGetLeftCards(POINT pt);
	//����
	void MouseGetLeftCards(List* &pMouseLinkHead,List* &pMouseLinkEnd);
	//����
	void ResertLeftCards(List* &pMouseLinkHead,List* &pMouseLinkEnd);
};
