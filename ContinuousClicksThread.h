#pragma once
#include "framework.h"
#include "ClickResource.h"
//连点的主要实现线程函数
UINT FunContinousClicksThread(LPVOID pParam);
//鼠标抖动实现函数
UINT FunRandomJitter(LPVOID pParam);
