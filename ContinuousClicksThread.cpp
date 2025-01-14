#include "ContinuousClicksThread.h"

UINT FunContinousClicksThread(LPVOID pParam) 
{
	srand(time(NULL));
	InfoClicks* ClickInfo = (InfoClicks*) pParam;

	while (1)										//来了就别走了
	{
		switch (ClickInfo->WhatButton)
		{
		case Left:
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			Sleep(ClickInfo->MouseUpInterval);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			break;
		case Middle:
			mouse_event(MOUSEEVENTF_MIDDLEDOWN, 0, 0, 0, 0);
			Sleep(ClickInfo->MouseUpInterval);
			mouse_event(MOUSEEVENTF_MIDDLEDOWN, 0, 0, 0, 0);
			break;
		case Right:
			mouse_event( MOUSEEVENTF_RIGHTDOWN, 0, 0, 0, 0);
			Sleep(ClickInfo->MouseUpInterval);
			mouse_event( MOUSEEVENTF_RIGHTDOWN, 0, 0, 0, 0);
			break;
		}
		if (ClickInfo->RandomIntervalTime)		//暂时这样用着先把
		{
			if (rand()%2)
			{
				Sleep((ClickInfo->IntervalTime)+ ((ClickInfo->IntervalTime)/15));
			}
			else
			{
				Sleep((ClickInfo->IntervalTime) - ((ClickInfo->IntervalTime) / 15));
			}
			continue;
		}
		Sleep(ClickInfo->IntervalTime);
	
	}
}

UINT FunRandomJitter(LPVOID pParam) 
{
	srand(time(NULL));

	POINT lpPoint{ 0 };
	GetCursorPos(&lpPoint);

	int way = rand();
	while (1)
	{
		static int randomPosX = rand() % ((lpPoint.x) / 30);
		static int randomPosY = rand() % ((lpPoint.y) / 10);

		way %= 5;
		switch (way)
		{
		case 1:
			SetCursorPos((lpPoint.x) + randomPosX, lpPoint.y + randomPosY);
			break;
		case 2:
			SetCursorPos((lpPoint.x) - randomPosX, lpPoint.y - randomPosY);
			break;
		case 3:
			SetCursorPos((lpPoint.x) + randomPosX, lpPoint.y - randomPosY);
			break;
		case 4:
			SetCursorPos((lpPoint.x) - randomPosX, lpPoint.y + randomPosY);
			break;
		}

		way = rand();
		Sleep(100);
		SetCursorPos(lpPoint.x, lpPoint.y);
	}

};