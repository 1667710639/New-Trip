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
	//鼠标链表
	List* m_pMouseLinkHead;
	List* m_pMouseLinkEnd;

public:
	CCardCtrl():m_vtr(52)
	{
		m_hWnd = NULL;
		m_hInstance = NULL;
		//向量初始化
		for(int i = 0 ; i<52;i++)
		{
			m_vtr[i] = i;
		}
		//随机种子
		srand((unsigned int)time(NULL));
		//向量随机排列
		random_shuffle(m_vtr.begin(),m_vtr.end());
		//背景
		m_hBackGroundBitmap = NULL;
		//鼠标链表
		m_pMouseLinkHead = NULL;
		m_pMouseLinkEnd = NULL;
	}
~CCardCtrl()
	{
		
	}
public:
	//设置成员值
	void SetDataValue(HWND hWnd ,HINSTANCE hInstance);
	
	HWND GethWnd(){return m_hWnd;}
	
	HINSTANCE GethInstance(){return m_hInstance;}

	void ClearValue();
	
private:
//加载牌
void LoadCards();
// 
void ShowMouseCards(HDC hMemDC);

POINT m_LeftMouseDownPos;

POINT m_LeftMouseMovePos;
public:
	//初始化游戏数据
	void InitGameData();
	//处理paint消息
	void OnPaintWnd();
	//处理timer消息
	void OnTimer(UINT nTimerID);
	//键盘消息
	void OnKeyDown(UINT nKeyID);
	//左键
	void OnLButtonDown(POINT pt);
	//右键
	void OnRButtonDown(POINT pt);
	//左键
	void OnLButtonUp(POINT pt);
	//右键
	void OnRButtonUp(POINT pt);
	//鼠标移动
	void OnMouseMove(POINT pt);
};