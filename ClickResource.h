#pragma once
#include"framework.h"
enum Button :char{ Left, Middle, Right } ;

struct InfoClicks
{
	bool Running;

	Button WhatButton;
	UINT IntervalTime;			//���ʱ��
	UINT  MouseUpInterval;		//���̧����ʱ��

	bool RandomIntervalTime;	//����������ʱ��
	bool RandomJitter;			//����������궶��

	bool OnlyForWindow;			//��Ե����Ĵ���
};

