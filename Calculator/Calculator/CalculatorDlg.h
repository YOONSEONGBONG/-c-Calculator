
// CalculatorDlg.h : ��� ����
//

#pragma once
#include "afxwin.h"
#include<memory>
#include "Calculator.h"

// CCalculatorDlg ��ȭ ����
class CCalculatorDlg : public CDialogEx
{
public:
	char m_operater_flag = 0; //plus:0/minus:1/multiply:2/division
	char m_step = 0;	 //������ ��ư Ȯ�κ���
	long int m_count = 0; //������ ī��Ʈ����
	long double m_value = 0; //���� ���� �����ϱ����� ����
	long double m_flant = 0; //���ڸ� �ӽ� �����ϱ� ���� ����(%����)
	bool boonsoo_twice = false;
public:
	void M_Operate(double m_value_two); //��Ģ���� �߰� �Լ�

// �����Դϴ�.
public:
	CCalculatorDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_CALCULATOR_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �����Դϴ�.


// �����Դϴ�.
protected:
	HICON m_hIcon;

	// ������ �޽��� �� �Լ�
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:

	afx_msg void OnBnClickedButtonPlus();
	afx_msg void OnBnClickedButtonMinus();
	afx_msg void OnBnClickedButtonMultiply();
	afx_msg void OnBnClickedButtonDivision();
	afx_msg void OnBnClickedButtonEqual();
	afx_msg void OnBnClickedButtonCe();
	afx_msg void OnBnClickedButtonComma();
	afx_msg void OnBnClickedButtonBackspace();
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	afx_msg void OnBnClickedButtonSqrt();
	afx_msg void OnBnClickedButtonZegop();
	afx_msg void OnBnClickedButtonBoonsoo();
	afx_msg void OnBnClickedButtonC();
	afx_msg void OnBnClickedButtonPm();
	afx_msg void OnBnClickedButtonPercent();
	afx_msg void OnBnClickedButtonHistory();
	

public:
	CString history;
	CString result;
	bool bChange = false;
};
