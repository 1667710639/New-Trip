#pragma once
#include<Windows.h>
#include<iostream>
#include"resource.h"
#include<vector>


using namespace std;


//��ɫö��
enum {enum_cards_heart,enum_cards_black,enum_cards_square,enum_cards_flower};
//���忨Ƭ�ṹ��
struct Cards
{
	int m_nCardsNum; //����
	int m_nCardsColor; //��ɫ
	HBITMAP m_hCardsBitmap; //λͼ

};
//����ڵ�
struct List
{
	Cards m_Cards; //һ����
	bool bFlag; //����
	int m_x;//
	int m_y;//
	List *m_pNext;//��һ��
	List *m_pPre;//��һ��

};