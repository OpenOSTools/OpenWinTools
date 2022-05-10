// MainDlg.cpp : implementation of the CMainDlg class
//
/////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "resource.h"
#include "MainDlg.h"

CString	LDS(int ids)
{
	TCHAR	buf[512] = { 0 };
	LoadString(NULL, ids, buf, _countof(buf) - 1);
	return	buf;
}

LRESULT CMainDlg::OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	// center the dialog on the screen
	CenterWindow();

	// set icons
	HICON hIcon = AtlLoadIconImage(IDR_MAINFRAME, LR_DEFAULTCOLOR, ::GetSystemMetrics(SM_CXICON), ::GetSystemMetrics(SM_CYICON));
	SetIcon(hIcon, TRUE);
	HICON hIconSmall = AtlLoadIconImage(IDR_MAINFRAME, LR_DEFAULTCOLOR, ::GetSystemMetrics(SM_CXSMICON), ::GetSystemMetrics(SM_CYSMICON));
	SetIcon(hIconSmall, FALSE);

	DoDataExchange(FALSE);

	m_StatusBar.Create(this->m_hWnd, NULL, NULL, WS_CHILD | WS_VISIBLE | SBARS_SIZEGRIP);
	int w[] = { 100,200,300,-1 };
	m_StatusBar.SetParts(_countof(w), &w[0]);    
	m_StatusBar.SetText(0, _T("1"));
	m_StatusBar.SetText(1, _T("2"));

    m_Tabs =
	{ 
		std::make_pair(LDS(IDS_TAB_SYSINFO),        (CWindow*)new CDlgSysInfo(this->m_hWnd)),
		std::make_pair(LDS(IDS_TAB_PROC),		    (CWindow*)new CDlgProcess(this->m_hWnd)),
		std::make_pair(_T("内核"),                  (CWindow*)new CDlgKernel(this->m_hWnd)),
		std::make_pair(_T("钩子"),                  (CWindow*)new CDlgHook(this->m_hWnd)),
		std::make_pair(LDS(IDS_TAB_NET),            (CWindow*)new CDlgNetwork(this->m_hWnd)),
		std::make_pair(LDS(IDS_TAB_FILE),            (CWindow*)new CDlgFile(this->m_hWnd)),
		std::make_pair(_T("注册表"),	              (CWindow*)new CDlgRegistry(this->m_hWnd)),
		std::make_pair(_T("自启动"),              (CWindow*)new CDlgStartup(this->m_hWnd)),
		std::make_pair(_T("硬件"),                (CWindow*)new CDlgHardWare(this->m_hWnd)),
		std::make_pair(_T("调试"),                (CWindow*)new CDlgDebug(this->m_hWnd)),
		std::make_pair(_T("行为"),                (CWindow*)new CDlgBehavior(this->m_hWnd))
	};

	
    m_TabMain.ModifyStyleEx(0, WS_EX_COMPOSITED);

	for (auto it = m_Tabs.begin(); it != m_Tabs.end(); it++)
	{
		m_TabMain.AddItem(it->first);
	}

	m_TabMain.SetCurSel(0);

	return TRUE;
}

LRESULT CMainDlg::OnAppAbout(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	CSimpleDialog<IDD_ABOUTBOX, FALSE> dlg;
	dlg.DoModal();
	return 0;
}

LRESULT CMainDlg::OnOK(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	// TODO: Add validation code 
	//EndDialog(wID);
	return 0;
}

LRESULT CMainDlg::OnCancel(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	if (MessageBox(LDS(IDS_EXIT_CONFIRM), _T(""), MB_OKCANCEL|MB_DEFBUTTON2) == IDOK)
	{
		EndDialog(wID);
	}
	
	return 0;
}


LRESULT CMainDlg::OnBnClickedOk(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	// TODO: 在此添加控件通知处理程序代码

	return 0;
}


LRESULT CMainDlg::OnTcnSelchangeTabMain(int /*idCtrl*/, LPNMHDR pNMHDR, BOOL& /*bHandled*/)
{
    PAINTSTRUCT ps;

	ResizeChildDlg();

	return 0;
}


LRESULT CMainDlg::OnTcnKeydownTabMain(int /*idCtrl*/, LPNMHDR pNMHDR, BOOL& /*bHandled*/)
{
	NMTCKEYDOWN* pTCKeyDown = reinterpret_cast<NMTCKEYDOWN*>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码

	return 0;
}


LRESULT CMainDlg::OnTcnSelchangingTabMain(int /*idCtrl*/, LPNMHDR pNMHDR, BOOL& /*bHandled*/)
{
    
	m_Tabs[m_TabMain.GetCurSel()].second->ShowWindow(SW_HIDE);
	return 0;
}


LRESULT CMainDlg::OnSize(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	RECT thisRect;
	GetClientRect(&thisRect);
	
	m_TabMain.MoveWindow(&thisRect);
	
	ResizeChildDlg();
	return 0;
}
