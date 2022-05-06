// CDlgSysInfo.cpp: 实现文件
//

#include "STDAfx.h"
#include "resource.h"
#include "CDlgSysInfo.h"



// CDlgSysInfo 消息处理程序

LRESULT CDlgSysInfo::OnInitDialog(UINT, WPARAM, LPARAM, BOOL&)
{
	return LRESULT();
}

LRESULT CDlgSysInfo::OnSize(UINT, WPARAM, LPARAM, BOOL&)
{
	return LRESULT();
}


LRESULT CDlgSysInfo::OnNMRclickListSysinfo(int /*idCtrl*/, LPNMHDR pNMHDR, BOOL& /*bHandled*/)
{
	// TODO: 在此添加控件通知处理程序代码
	MessageBox(_T("r"));
	return 0;
}


LRESULT CDlgSysInfo::OnTimer(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	return 0;
}


LRESULT CDlgSysInfo::OnBnClickedOk(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	// TODO: 在此添加控件通知处理程序代码

	return 0;
}
