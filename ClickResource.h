#pragma once
#include"framework.h"
enum Button :char{ Left, Middle, Right } ;

struct InfoClicks
{
	bool Running;

	Button WhatButton;
	UINT IntervalTime;			//间隔时间
	UINT  MouseUpInterval;		//鼠标抬起间隔时间

	bool RandomIntervalTime;	//启用随机间隔时间
	bool RandomJitter;			//启用随机坐标抖动

	bool OnlyForWindow;			//针对单独的窗口
};

