// MainDlg.h : interface of the CMainDlg class
//
/////////////////////////////////////////////////////////////////////////////

#pragma once
#include <atlddx.h>
#include <atlstr.h>

#include "CDlgProcess.h"
#include "CDlgSysInfo.h"
#include "CDlgBehavior.h"
#include "CDlgDebug.h"
#include "CDlgFile.h"
#include "CDlgHardware.h"
#include "CDlgHook.h"
#include "CDlgNetwork.h"
#include "CDlgRegistry.h"
#include "CDlgStartup.h"
#include "CDlgKernel.h"

class CMainDlg : public CDialogImpl<CMainDlg>,public	CWinDataExchange<CMainDlg>
{
private:
	VOID ResizeChildDlg()
	{
		RECT ClientRect, ItemRect, ChildDlgRect;
		RECT StatusBarRect;

		m_StatusBar.GetClientRect(&StatusBarRect);
		
		m_TabMain.GetClientRect(&ClientRect);
		m_TabMain.GetItemRect(0, &ItemRect);

		ChildDlgRect.left = ClientRect.left;
		ChildDlgRect.right = ClientRect.right;
		ChildDlgRect.top = ItemRect.bottom + 4;
		ChildDlgRect.bottom = ClientRect.bottom - (StatusBarRect.bottom - StatusBarRect.top);

		m_Tabs[m_TabMain.GetCurSel()].second->MoveWindow(&ChildDlgRect, FALSE);
		m_Tabs[m_TabMain.GetCurSel()].second->ShowWindow(SW_SHOW);

		
		StatusBarRect.left = ClientRect.left;
		StatusBarRect.top = ChildDlgRect.bottom;
		StatusBarRect.right = ClientRect.right;
		StatusBarRect.bottom = ClientRect.bottom;
		m_StatusBar.MoveWindow(&StatusBarRect);
	}
	
private:
	std::vector<std::pair<CString, CWindow*>> m_Tabs;
	CStatusBarCtrl	m_StatusBar;

private:
	CTabCtrl	m_TabMain;
public:
	enum { IDD = IDD_MAINDLG };

	BEGIN_DDX_MAP(CMainDlg)
		DDX_CONTROL_HANDLE(IDC_TAB_MAIN, m_TabMain)
	END_DDX_MAP();

	BEGIN_MSG_MAP(CMainDlg)
		MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
		COMMAND_ID_HANDLER(ID_APP_ABOUT, OnAppAbout)
		COMMAND_ID_HANDLER(IDOK, OnOK)
		COMMAND_ID_HANDLER(IDCANCEL, OnCancel)
		COMMAND_HANDLER(IDOK, BN_CLICKED, OnBnClickedOk)
		NOTIFY_HANDLER(IDC_TAB_MAIN, TCN_SELCHANGE, OnTcnSelchangeTabMain)
		NOTIFY_HANDLER(IDC_TAB_MAIN, TCN_KEYDOWN, OnTcnKeydownTabMain)
		NOTIFY_HANDLER(IDC_TAB_MAIN, TCN_SELCHANGING, OnTcnSelchangingTabMain)
		MESSAGE_HANDLER(WM_SIZE, OnSize)
		MESSAGE_HANDLER(WM_ERASEBKGND, OnEraseBknd);
	END_MSG_MAP()
	LRESULT OnEraseBknd(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled)
	{
		bHandled = true;
		return	0;
	}
// Handler prototypes (uncomment arguments if needed):
//	LRESULT MessageHandler(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
//	LRESULT CommandHandler(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
//	LRESULT NotifyHandler(int /*idCtrl*/, LPNMHDR /*pnmh*/, BOOL& /*bHandled*/)

	LRESULT OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnAppAbout(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnOK(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnCancel(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnBnClickedOk(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnTcnSelchangeTabMain(int /*idCtrl*/, LPNMHDR pNMHDR, BOOL& /*bHandled*/);
	LRESULT OnTcnKeydownTabMain(int /*idCtrl*/, LPNMHDR pNMHDR, BOOL& /*bHandled*/);
	LRESULT OnTcnSelchangingTabMain(int /*idCtrl*/, LPNMHDR pNMHDR, BOOL& /*bHandled*/);
	LRESULT OnSize(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
};
