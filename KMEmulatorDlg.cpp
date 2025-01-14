
// KMEmulatorDlg.cpp: 实现文件
//
#include "framework.h"
#include "KMEmulator.h"
#include "KMEmulatorDlg.h"
#include "afxdialogex.h"
#include<strsafe.h>

// CKMEmulatorDlg 对话框

BEGIN_MESSAGE_MAP(CKMEmulatorDlg, CDialogEx)
	ON_BN_CLICKED(IDC_MouseUpInterval, CKMEmulatorDlg::IDC_MouseIntervalChecked)
	ON_BN_CLICKED(IDC_TopMostWindow, CKMEmulatorDlg::TopMostChecked)
	ON_BN_CLICKED(IDC_OnlyForWindow,CKMEmulatorDlg::OnlyForWindowChecked)
	ON_BN_CLICKED(IDC_BUTTONSTART, CKMEmulatorDlg::ButtonStart)
	ON_BN_CLICKED(IDC_SetHotKey, CKMEmulatorDlg::SetHotKey)
	ON_WM_HOTKEY()

	ON_COMMAND(ID_HELP, OnHelp)		//屏蔽f1 onhelp
	//ON_WM_MOUSEMOVE()
	//ON_WM_ACTIVATEAPP()
END_MESSAGE_MAP()



BOOL CKMEmulatorDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	((CStatic*)GetDlgItem(IDC_SELECTWINDOW))->SetIcon(m_hMove);
	((CButton*)GetDlgItem(IDC_LEFTBUTTON))->SetCheck(BST_CHECKED);

	((CButton*)GetDlgItem(IDC_TopMostWindow))->SetCheck(BST_CHECKED);
	SetWindowPos(&wndTopMost, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);

	return TRUE;  
}

void CKMEmulatorDlg::OnCancel() 
{
	UnregisterHotKey(*this, 0);
	CDialog::OnCancel();
};

//窗口消息函数
afx_msg void CKMEmulatorDlg::IDC_MouseIntervalChecked() 
{
	if (((CButton*)GetDlgItem(IDC_MouseUpInterval))->GetCheck() == BST_CHECKED)
		((CEdit*)GetDlgItem(IDC_EMouseInterval))->EnableWindow(true);
	else
		((CEdit*)GetDlgItem(IDC_EMouseInterval))->EnableWindow(false);;
	((CEdit*)GetDlgItem(IDC_EMouseInterval))->SetWindowText(L"");;
}

afx_msg void CKMEmulatorDlg::TopMostChecked() 
{
	if (((CButton*)GetDlgItem(IDC_TopMostWindow))->GetCheck() == BST_CHECKED)
		SetWindowPos(&wndTopMost,0,0,0,0, SWP_NOMOVE| SWP_NOSIZE);
	else
		SetWindowPos(&wndNoTopMost, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
}

afx_msg void CKMEmulatorDlg::OnlyForWindowChecked() 
{
	if (((CButton*)GetDlgItem(IDC_OnlyForWindow))->GetCheck() == BST_CHECKED)
	{
		((CStatic*)GetDlgItem(IDC_SELECTWINDOW))->ShowWindow(SW_SHOW);
		((CStatic*)GetDlgItem(IDC_STATIC1))->ShowWindow(SW_SHOW);	//提示语
	}
	else
	{
		((CStatic*)GetDlgItem(IDC_SELECTWINDOW))->ShowWindow(SW_HIDE);
		(GetDlgItem(IDC_STATIC1))->ShowWindow(SW_HIDE);
	}
}

afx_msg void CKMEmulatorDlg::ButtonStart() 
{
	static InfoClicks ClickInfo;		//声明为static防止内存泄漏
	ZeroMemory(&ClickInfo, sizeof(InfoClicks));
	

	if (ClicksThread)
	{
		TerminateThread(*ClicksThread,0);		//可能会访问到不可访问的内存
		//ClicksThread->SuspendThread();
		if (GetLastError() != ERROR_INVALID_HANDLE)
			delete ClicksThread;
			//RaiseException(0,0,0,0);		//直接崩溃得了
		ClicksThread = nullptr;

		TerminateThread(*RandomJitter, 0);
		if (GetLastError() != ERROR_INVALID_HANDLE)
			delete RandomJitter;
		RandomJitter = nullptr;

		(GetDlgItem(IDC_BUTTONSTART))->SetWindowTextW(L"开始连点");
	}
	else
	{
		CButton* buttonCheck = nullptr;
		buttonCheck = (CButton*)(GetDlgItem(IDC_LEFTBUTTON));		//这里不用循环了，控件id给vs管的，保险点
		if (buttonCheck->GetCheck() == BST_CHECKED)
			ClickInfo.WhatButton = Left;
		buttonCheck = (CButton*)(GetDlgItem(IDC_MIDDLEBUTTON));
		if (buttonCheck->GetCheck() == BST_CHECKED)
			ClickInfo.WhatButton = Middle;
		buttonCheck = (CButton*)(GetDlgItem(IDC_RIGHTBUTTON));
		if (buttonCheck->GetCheck() == BST_CHECKED)
			ClickInfo.WhatButton = Right;

		BOOL lpTranslated;
		ClickInfo.IntervalTime = GetDlgItemInt(IDC_EDITInterval, &lpTranslated, false);
		if (!lpTranslated)
		{
			MessageBox(L"间隔时间不能为空", L"错误", MB_OK | MB_ICONERROR);
			return;
		}
		ClickInfo.MouseUpInterval = GetDlgItemInt(IDC_EMouseInterval, nullptr, false);

		buttonCheck = (CButton*)(GetDlgItem(IDC_RandomIntervalTime));
		ClickInfo.RandomIntervalTime = (buttonCheck->GetCheck() == BST_CHECKED);

		buttonCheck = (CButton*)(GetDlgItem(IDC_RandomJitter));
		ClickInfo.RandomJitter = (buttonCheck->GetCheck() == BST_CHECKED);

		buttonCheck = (CButton*)(GetDlgItem(IDC_OnlyForWindow));
		ClickInfo.OnlyForWindow = (buttonCheck->GetCheck() == BST_CHECKED);

		if (!ClicksThread)
		ClicksThread = AfxBeginThread(FunContinousClicksThread, &ClickInfo);
		if (ClicksThread == nullptr)
		{
			DWORD ErrorCode = GetLastError();
			WCHAR srting[20]{ 0 };
			StringCchPrintfW(srting, 20, L"连点启动失败，错误码:%d", ErrorCode);
			MessageBox(srting, L"错误", IDOK | MB_ICONERROR);
			return;
		}

		if ((!RandomJitter)&& ClickInfo.RandomJitter)
			RandomJitter = AfxBeginThread(FunRandomJitter, &ClickInfo);
		if (ClicksThread == nullptr)
		{
			DWORD ErrorCode = GetLastError();
			WCHAR srting[20]{ 0 };
			StringCchPrintfW(srting, 20, L"连点启动失败，错误码:%d", ErrorCode);
			MessageBox(srting, L"错误", IDOK | MB_ICONERROR);
			return;
		}

		(GetDlgItem(IDC_BUTTONSTART))->SetWindowTextW(L"停止连点");
	}

}

afx_msg void CKMEmulatorDlg::SetHotKey()
{
	WORD wVirtualKeyCode, wModifiers;
	(((CHotKeyCtrl*)GetDlgItem(IDC_HOTKEY))->GetHotKey(wVirtualKeyCode, wModifiers));

	UnregisterHotKey(*this, 0);
	if (RegisterHotKey(*this, 0, wModifiers, wVirtualKeyCode))
	{
		MessageBox(L"快捷键设置成功", L"成功", MB_OK | MB_ICONINFORMATION);
	}
	else
		MessageBox(L"快捷键设置失败，请更换快捷键", L"失败", MB_OK | MB_ICONERROR);

	return;
}

afx_msg void CKMEmulatorDlg::OnHotKey(UINT, UINT, UINT)
{
	this->ButtonStart();
};

//野心不要太起先
//afx_msg void CKMEmulatorDlg::OnMouseMove(UINT wParam, CPoint mousePoint) 
//{
//	if ((ClicksThread && isThreadRunning))
//		ClicksThread->SuspendThread();
//	else if ((ClicksThread || isThreadRunning))
//	{
//		if (isThreadRunning)
//		{
//			ClicksThread->SuspendThread();
//			isThreadRunning = false;
//		}
//		else
//			return;
//	}
//};
//
//
//
//afx_msg void CKMEmulatorDlg::OnActivateApp(BOOL wParam, DWORD)
//{
//	if (wParam)
//		return;
//	if (!(ClicksThread && isThreadRunning))
//		return;
//	if (ClicksThread)
//	{
//
//			ClicksThread->ResumeThread();
//			isThreadRunning = true;
//		
//	}
//};