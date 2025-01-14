
// KMEmulatorDlg.h: 头文件
//

#pragma once
#include "ClickResource.h"
#include"ContinuousClicksThread.h"

// CKMEmulatorDlg 对话框
class CKMEmulatorDlg : public CDialogEx
{
// 构造
public:
	CKMEmulatorDlg(CWnd* pParent = nullptr)
		: CDialogEx(IDD_KMEMULATOR_DIALOG, pParent)
	{
		m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
		m_hMove = AfxGetApp()->LoadIcon(IDI_MOVE);
		m_hMoving = AfxGetApp()->LoadIconW(IDI_MOVING);
	}	// 标准构造函数

// 实现
protected:
	HICON m_hIcon;
	HICON m_hMove = nullptr,m_hMoving = nullptr;
	//令Esc同关闭按键有效
	virtual void OnOK() {};  
	virtual void OnCancel();
	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	//启用抬起间隔按钮
	afx_msg void IDC_MouseIntervalChecked();
	//保持窗口指定按钮
	afx_msg void TopMostChecked();
	//针对单独窗口按钮
	afx_msg void OnlyForWindowChecked();
	//开始连点按钮
	afx_msg void ButtonStart();
	//热键
	afx_msg void OnHotKey(UINT, UINT, UINT);

	//获取在鼠标移动的消息：防止误点到连点器
	//afx_msg void OnMouseMove(UINT wParam, CPoint mousePoint);
	//afx_msg void OnActivateApp(BOOL, DWORD);
	afx_msg void SetHotKey();

	afx_msg void OnHelp() {};
	DECLARE_MESSAGE_MAP()
private:
	CWinThread * ClicksThread = nullptr;	//连点器线程
	CWinThread * RandomJitter = nullptr;	//抖动器线程
};


