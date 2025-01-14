
// KMEmulator.cpp: 定义应用程序的类行为。
//

#include "framework.h"
#include "KMEmulator.h"
#include "KMEmulatorDlg.h"

// CKMEmulatorApp

BEGIN_MESSAGE_MAP(CKMEmulatorApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CKMEmulatorApp 构造

CKMEmulatorApp::CKMEmulatorApp()
{
	// TODO: 在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
}


// 唯一的 CKMEmulatorApp 对象

CKMEmulatorApp theApp;


// CKMEmulatorApp 初始化

BOOL CKMEmulatorApp::InitInstance()
{
	HWND window = FindWindow(_T("KMEmulator"), nullptr);
	if (window) 
	{
		ShowWindow(window, SW_SHOW);
		return false;
	}

	CWinApp::InitInstance();

	//这里开始真正开始
	WNDCLASS wc = { 0 };
	GetClassInfo(AfxGetInstanceHandle(), _T("#32770"), &wc);
	wc.lpszClassName = _T("KMEmulator");
	AfxRegisterClass(&wc);

	CKMEmulatorDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();

	return FALSE;
}

