#pragma once
#include "afxwin.h"


// CalculatorHistoryDlg ��ȭ �����Դϴ�.

class CalculatorHistoryDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CalculatorHistoryDlg)

public:
	CalculatorHistoryDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CalculatorHistoryDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_DIALOG_LISTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonInsert();
	afx_msg void OnBnClickedButtonRemove();
public:
	CListBox historyList;
	char m_step=0;
	char m_operater_flag = 0;
};
