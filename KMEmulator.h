
// KMEmulator.h: PROJECT_NAME 应用程序的主头文件
//

#pragma once

#include "resource.h"		// 主符号

//Windows视觉样式6
#pragma comment(linker,"\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

// CKMEmulatorApp:

class CKMEmulatorApp : public CWinApp
{
public:
	CKMEmulatorApp();

public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()

private:
	CWinThread ContinousClicksThread;
};

extern CKMEmulatorApp theApp;
