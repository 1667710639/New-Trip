#pragma once
#include"Card.h"
#include<algorithm>
#include<iostream>
#include "DownCards.h"
#include"UpCards.h"
#include"Left.h"
#include<time.h>
using namespace std;

class CCardCtrl
{
private:
	HWND m_hWnd;
	HINSTANCE m_hInstance;
	CDownCards m_oDownCards;
	CUpCards m_oUpCards;
	CLeft m_oLeftCards;
public:
	Cards m_cardsArr[52];
	vector<int> m_vtr;
	HBITMAP m_hBackGroundBitmap;
	//�������
	List* m_pMouseLinkHead;
	List* m_pMouseLinkEnd;

public:
	CCardCtrl():m_vtr(52)
	{
		m_hWnd = NULL;
		m_hInstance = NULL;
		//������ʼ��
		for(int i = 0 ; i<52;i++)
		{
			m_vtr[i] = i;
		}
		//�������
		srand((unsigned int)time(NULL));
		//�����������
		random_shuffle(m_vtr.begin(),m_vtr.end());
		//����
		m_hBackGroundBitmap = NULL;
		//�������
		m_pMouseLinkHead = NULL;
		m_pMouseLinkEnd = NULL;
	}
~CCardCtrl()
	{
		
	}
public:
	//���ó�Աֵ
	void SetDataValue(HWND hWnd ,HINSTANCE hInstance);
	
	HWND GethWnd(){return m_hWnd;}
	
	HINSTANCE GethInstance(){return m_hInstance;}

	void ClearValue();
	
private:
//������
void LoadCards();
// 
void ShowMouseCards(HDC hMemDC);

POINT m_LeftMouseDownPos;

POINT m_LeftMouseMovePos;
public:
	//��ʼ����Ϸ����
	void InitGameData();
	//����paint��Ϣ
	void OnPaintWnd();
	//����timer��Ϣ
	void OnTimer(UINT nTimerID);
	//������Ϣ
	void OnKeyDown(UINT nKeyID);
	//���
	void OnLButtonDown(POINT pt);
	//�Ҽ�
	void OnRButtonDown(POINT pt);
	//���
	void OnLButtonUp(POINT pt);
	//�Ҽ�
	void OnRButtonUp(POINT pt);
	//����ƶ�
	void OnMouseMove(POINT pt);
};