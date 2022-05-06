// CDlgProcess.cpp: 实现文件
//

#include "stdafx.h"
#include "resource.h"
#include "CDlgProcess.h"


CDlgProcess::CDlgProcess()
{

}

CDlgProcess::~CDlgProcess()
{
}


LRESULT CDlgProcess::OnNMDblclkListProcess(int /*idCtrl*/, LPNMHDR pNMHDR, BOOL& /*bHandled*/)
{
	// TODO: 在此添加控件通知处理程序代码

	return 0;
}


LRESULT CDlgProcess::OnSize(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	RECT R;
	GetClientRect(&R);
	m_ListProc.MoveWindow(&R);

	return 0;
}


struct PROC_LIST_COL
{
	LPCTSTR ColName;
	int		ColWidth;
};




LRESULT CDlgProcess::OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	DoDataExchange(FALSE);
	
	PROC_LIST_COL Col[] = {
		{_T("PID"),40},
		{_T("名称"),120},
		{_T("用户名"),120},
		{_T("CPU"),40},
		{_T("GPU"),40},
		{_T("启动时间"),80},
		{_T("CPU时间"),80},
		{_T("线程"),40},
		{_T("模块"),40},
		{_T("内存"),60},
		{_T("路径"),200},
		{_T("命令行"),200}
	};
	
	for (auto i = 0; i < _countof(Col); i++)
	{
		m_ListProc.InsertColumn(i, Col[i].ColName, 0, Col[i].ColWidth);
	}


	return TRUE;
}

