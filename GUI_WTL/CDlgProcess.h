#pragma once
#include <atlddx.h>
#include <atlctrls.h>

// CDlgProcess 对话框

class CDlgProcess : public CDialogImpl<CDlgProcess>, public	CWinDataExchange<CDlgProcess>
{
public:
	CDlgProcess(HWND Parent, int Show = SW_HIDE)
	{
		this->Create(Parent, NULL);
		this->ShowWindow(Show);
	}
private:
	CListViewCtrl	m_ListProc;
public:
	enum { IDD = IDD_PROCESS };

	BEGIN_DDX_MAP(CMainDlg)
		DDX_CONTROL_HANDLE(IDC_LIST_PROCESS, m_ListProc)
	END_DDX_MAP();

	BEGIN_MSG_MAP(CDlgProcess)
		NOTIFY_HANDLER(IDC_LIST_PROCESS, NM_DBLCLK, OnNMDblclkListProcess)
		MESSAGE_HANDLER(WM_SIZE, OnSize)
		MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
		MESSAGE_HANDLER(WM_ERASEBKGND, OnEraseBknd);
	END_MSG_MAP()
	LRESULT OnEraseBknd(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled)
	{
		bHandled = true;
		return	0;
	}


	CDlgProcess();
	virtual ~CDlgProcess();


	
public:
	LRESULT OnNMDblclkListProcess(int /*idCtrl*/, LPNMHDR pNMHDR, BOOL& /*bHandled*/);
	LRESULT OnTcnSelchangingTabMain(int /*idCtrl*/, LPNMHDR pNMHDR, BOOL& /*bHandled*/);
	LRESULT OnSize(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
};
