#pragma once
#include <atlddx.h>
#include <atlstr.h>


// CDlgSysInfo 对话框

class CDlgSysInfo : public CDialogImpl<CDlgSysInfo>, public	CWinDataExchange<CDlgSysInfo>
{
public:
	CDlgSysInfo(HWND Parent, int Show = SW_HIDE)
	{
		this->Create(Parent, NULL);
		this->ShowWindow(Show);
	}
	
public:
	enum { IDD = IDD_SYSINFO };

	BEGIN_DDX_MAP(CDlgSysInfo)
		
	END_DDX_MAP();

	BEGIN_MSG_MAP(CDlgSysInfo)
		MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
		MESSAGE_HANDLER(WM_SIZE, OnSize)
		NOTIFY_HANDLER(IDC_LIST_SYSINFO, NM_RCLICK, OnNMRclickListSysinfo)
		MESSAGE_HANDLER(WM_TIMER, OnTimer)
		COMMAND_HANDLER(IDOK, BN_CLICKED, OnBnClickedOk)
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
	LRESULT OnSize(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnNMRclickListSysinfo(int /*idCtrl*/, LPNMHDR pNMHDR, BOOL& /*bHandled*/);
	LRESULT OnTimer(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnBnClickedOk(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
};
