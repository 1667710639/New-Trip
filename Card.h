#pragma once
#include<Windows.h>
#include<iostream>
#include"resource.h"
#include<vector>


using namespace std;


//花色枚举
enum {enum_cards_heart,enum_cards_black,enum_cards_square,enum_cards_flower};
//定义卡片结构体
struct Cards
{
	int m_nCardsNum; //牌数
	int m_nCardsColor; //花色
	HBITMAP m_hCardsBitmap; //位图

};
//链表节点
struct List
{
	Cards m_Cards; //一张牌
	bool bFlag; //正反
	int m_x;//
	int m_y;//
	List *m_pNext;//下一张
	List *m_pPre;//上一张

};