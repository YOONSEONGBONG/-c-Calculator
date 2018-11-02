
// CalculatorDlg.h : 헤더 파일
//

#pragma once
#include "afxwin.h"
#include<memory>
#include "Calculator.h"

// CCalculatorDlg 대화 상자
class CCalculatorDlg : public CDialogEx
{
public:
	char m_operater_flag = 0; //plus:0/minus:1/multiply:2/division
	char m_step = 0;	 //연산자 버튼 확인변수
	long int m_count = 0; //연산자 카운트변수
	long double m_value = 0; //숫자 값을 저장하기위한 변수
	long double m_flant = 0; //숫자를 임시 저장하기 위한 변수(%연산)
	bool boonsoo_twice = false;
public:
	void M_Operate(double m_value_two); //사칙연산 추가 함수

// 생성입니다.
public:
	CCalculatorDlg(CWnd* pParent = NULL);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
	enum { IDD = IDD_CALCULATOR_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
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
