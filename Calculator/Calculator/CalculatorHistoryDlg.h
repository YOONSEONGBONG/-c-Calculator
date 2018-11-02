#pragma once
#include "afxwin.h"


// CalculatorHistoryDlg 대화 상자입니다.

class CalculatorHistoryDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CalculatorHistoryDlg)

public:
	CalculatorHistoryDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CalculatorHistoryDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_DIALOG_LISTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonInsert();
	afx_msg void OnBnClickedButtonRemove();
public:
	CListBox historyList;
	char m_step=0;
	char m_operater_flag = 0;
};
