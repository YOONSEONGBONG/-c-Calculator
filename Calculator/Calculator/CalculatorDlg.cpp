
// CalculatorDlg.cpp : 구현 파일
//

#include "stdafx.h"
#include "Calculator.h"
#include "CalculatorDlg.h"
#include "afxdialogex.h"
#include <math.h>
#include "CalculatorHistoryDlg.h"
#include <fstream>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CString history;
	CString result;
	bool bChange = false;
	char m_operater_flag = 0; //NONE:0/plus:1/minus:2/multiply:3/division:4
	char m_step = 0;	 //연산자 버튼 확인변수
	long int m_count = 0; //연산자 카운트변수
	long double m_value = 0; //숫자 값을 저장하기위한 변수
	long double m_flant = 0; //숫자를 임시 저장하기 위한 변수(%연산)
	bool boonsoo_twice = false;
public:
	CAboutDlg();

	// 대화 상자 데이터입니다.
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()

};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CCalculatorDlg 대화 상자



CCalculatorDlg::CCalculatorDlg(CWnd* pParent /*=NULL*/)
: CDialogEx(CCalculatorDlg::IDD, pParent)

{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCalculatorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	

}

BEGIN_MESSAGE_MAP(CCalculatorDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_PLUS, &CCalculatorDlg::OnBnClickedButtonPlus)
	ON_BN_CLICKED(IDC_BUTTON_MINUS, &CCalculatorDlg::OnBnClickedButtonMinus)
	ON_BN_CLICKED(IDC_BUTTON_MULTIPLY, &CCalculatorDlg::OnBnClickedButtonMultiply)
	ON_BN_CLICKED(IDC_BUTTON_DIVISION, &CCalculatorDlg::OnBnClickedButtonDivision)
	ON_BN_CLICKED(IDC_BUTTON_EQUAL, &CCalculatorDlg::OnBnClickedButtonEqual)
	ON_BN_CLICKED(IDC_BUTTON_CE, &CCalculatorDlg::OnBnClickedButtonCe)
	ON_BN_CLICKED(IDC_BUTTON_COMMA, &CCalculatorDlg::OnBnClickedButtonComma)
	ON_BN_CLICKED(IDC_BUTTON_BACKSPACE, &CCalculatorDlg::OnBnClickedButtonBackspace)
	ON_BN_CLICKED(IDC_BUTTON_SQRT, &CCalculatorDlg::OnBnClickedButtonSqrt)
	ON_BN_CLICKED(IDC_BUTTON_ZEGOP, &CCalculatorDlg::OnBnClickedButtonZegop)
	ON_BN_CLICKED(IDC_BUTTON_BOONSOO, &CCalculatorDlg::OnBnClickedButtonBoonsoo)
	ON_BN_CLICKED(IDC_BUTTON_C, &CCalculatorDlg::OnBnClickedButtonC)
	ON_BN_CLICKED(IDC_BUTTON_PM, &CCalculatorDlg::OnBnClickedButtonPm)
	ON_BN_CLICKED(IDC_BUTTON_PERCENT, &CCalculatorDlg::OnBnClickedButtonPercent)
	ON_BN_CLICKED(IDC_BUTTON_HISTORY, &CCalculatorDlg::OnBnClickedButtonHistory)
END_MESSAGE_MAP()


// CCalculatorDlg 메시지 처리기

BOOL CCalculatorDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CCalculatorDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CCalculatorDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CCalculatorDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

BOOL CCalculatorDlg::OnCommand(WPARAM wParam, LPARAM lParam)
{
	if (IDC_BUTTON_0 <= wParam&&wParam <= IDC_BUTTON_9) //솔루션탐색기 → Resource.h → 숫자버튼 매크로 확인
	{
		CString str, number_str, str2; //문자열
		number_str.Format(L"%d", wParam - IDC_BUTTON_0); //숫자'0'을 기준으로 잡는다

		if (m_step == 0) //연산자가 눌리지 않았을경우
		{
			GetDlgItemText(IDC_EDIT_RESULT, str2); //에디트에 입력된값을 str변수에 저장
		}
		else if (m_step == 1)
		{
			GetDlgItemText(IDC_EDIT_RESULT, str);
			m_step = 0;
			m_value = _wtof(str);
		}
		else if (m_step == 2)
		{
			CEdit* pHistory = (CEdit*)GetDlgItem(IDC_EDIT_HISTORY);
			pHistory->SetWindowTextW(L" ");

			m_value = 0;
			m_step = 0;
			m_count = 0;
			m_operater_flag = 0;

			UpdateData(FALSE);
		}

		SetDlgItemText(IDC_EDIT_RESULT, str2 + number_str); //str에 저장된 값에 숫자값을 더해 출력
	
	}
	m_flant = m_value;
	return CDialogEx::OnCommand(wParam, lParam);
}

void CCalculatorDlg::M_Operate(double m_value_two)
{
	switch (m_operater_flag)

	{
	case 0: //NONE
		m_value = m_value_two;
		break;
	case 1: //더하기
		m_value += m_value_two;
		break;

	case 2: //뺴기
		m_value -= m_value_two;
		break;

	case 3: //곱하기
		m_value *= m_value_two;
		break;

	case 4: //나누기
		if (m_value_two != 0)
		{
			m_value /= m_value_two;
		}
		else
		{
			m_value = 0;
		}
		break;

	}
}

void CCalculatorDlg::OnBnClickedButtonPlus()
{
	CString str, str2, omg;
	double m_value_two = GetDlgItemInt(IDC_EDIT_RESULT);
	GetDlgItemText(IDC_EDIT_RESULT, omg);
	m_value_two = _wtof(omg);

	m_count++;
	GetDlgItemText(IDC_EDIT_RESULT, str2);
	GetDlgItemText(IDC_EDIT_HISTORY, str);
	if (m_count == 1)
	{
		m_value = m_value_two;
	}

	if (m_step == 1){
		str.Delete(str.GetLength() - 1, 1);
		str2 = "";
	}
	else if (m_step == 2){
		str.Delete(str.GetLength(), 1);
		str2 = "";
		M_Operate(m_value_two);
	}
	else{
		M_Operate(m_value_two);
	}


	m_operater_flag = 1;
	m_step = 1;


	SetDlgItemText(IDC_EDIT_HISTORY, str + str2 + '+');

	omg.Format(L"%f", m_value);
	omg.TrimRight(L"0");
	omg.TrimRight(L".");
	SetDlgItemText(IDC_EDIT_RESULT, omg);
}

void CCalculatorDlg::OnBnClickedButtonMinus()
{
	CString str, str2, omg;
	double m_value_two = GetDlgItemInt(IDC_EDIT_RESULT);
	GetDlgItemText(IDC_EDIT_RESULT, omg);
	m_value_two = _wtof(omg);

	m_count++;
	GetDlgItemText(IDC_EDIT_RESULT, str2);
	GetDlgItemText(IDC_EDIT_HISTORY, str);
	if (m_count == 1)
	{
		m_value = m_value_two;
	}


	if (m_step == 1){
		str.Delete(str.GetLength() - 1, 1);
		str2 = "";
	}
	else if (m_step == 2){
		str.Delete(str.GetLength(), 1);
		str2 = "";
		M_Operate(m_value_two);
	}
	else{
		M_Operate(m_value_two);
	}


	m_operater_flag = 2;
	m_step = 1;


	SetDlgItemText(IDC_EDIT_HISTORY, str + str2 + '-');

	omg.Format(L"%f", m_value);
	omg.TrimRight(L"0");
	omg.TrimRight(L".");
	SetDlgItemText(IDC_EDIT_RESULT, omg);
}

void CCalculatorDlg::OnBnClickedButtonMultiply()
{
	CString str, str2, omg;
	double m_value_two = GetDlgItemInt(IDC_EDIT_RESULT);
	GetDlgItemText(IDC_EDIT_RESULT, omg);
	m_value_two = _wtof(omg);

	m_count++;
	GetDlgItemText(IDC_EDIT_RESULT, str2);
	GetDlgItemText(IDC_EDIT_HISTORY, str);

	if (m_count == 1)
	{
		m_value = m_value_two;
	}

	if (m_step == 1){
		str.Delete(str.GetLength() - 1, 1);
		str2 = "";
	}
	else if (m_step == 2){
		str.Delete(str.GetLength(), 1);
		str2 = "";
		M_Operate(m_value_two);
	}
	else{
		M_Operate(m_value_two);
	}

	m_operater_flag = 3;
	m_step = 1;

	SetDlgItemText(IDC_EDIT_HISTORY, str + str2 + '*');

	omg.Format(L"%f", m_value);
	omg.TrimRight(L"0");
	omg.TrimRight(L".");
	SetDlgItemText(IDC_EDIT_RESULT, omg);

}

void CCalculatorDlg::OnBnClickedButtonDivision()
{
	CString str, str2, omg;
	double m_value_two = GetDlgItemInt(IDC_EDIT_RESULT);
	GetDlgItemText(IDC_EDIT_RESULT, omg);
	m_value_two = _wtof(omg);

	m_count++;


	m_operater_flag = 4;
	m_step = 1;

	GetDlgItemText(IDC_EDIT_RESULT, str2);
	GetDlgItemText(IDC_EDIT_HISTORY, str);
	if (m_count == 1)
	{
		m_value = m_value_two;
	}

	if (m_step == 1){
		str.Delete(str.GetLength() - 1, 1);
		str2 = "";
	}
	else if (m_step == 2){
		str.Delete(str.GetLength(), 1);
		str2 = "";
		M_Operate(m_value_two);
	}
	else{
		M_Operate(m_value_two);
	}

	SetDlgItemText(IDC_EDIT_HISTORY, str + str2 + '/');

	omg.Format(L"%f", m_value);
	omg.TrimRight(L"0");
	omg.TrimRight(L".");
	SetDlgItemText(IDC_EDIT_RESULT, omg);
}

void CCalculatorDlg::OnBnClickedButtonEqual()
{
	CString str,str2,str3;

 	double m_value_two = GetDlgItemInt(IDC_EDIT_RESULT);
	GetDlgItemText(IDC_EDIT_HISTORY, str);
	GetDlgItemText(IDC_EDIT_RESULT, str2);
	m_value_two = _wtof(str2);

	CEdit* pHistory = (CEdit*)GetDlgItem(IDC_EDIT_HISTORY);
	pHistory->SetWindowTextW(L" ");

	M_Operate(m_value_two);
	m_operater_flag = 0;
	m_count = 0;
	m_step;
	str3.Format(L"%f", m_value);
	str3.TrimRight(L"0");
	str3.TrimRight(L".");
	SetDlgItemText(IDC_EDIT_RESULT, str3);
	std::ofstream file;
	file.open("save.dat", std::fstream::app);
	if (m_step == 0)
	{
		file << (CT2A)str << (CT2A)str2 << "=" << (CT2A)str3 << "\n";
	}
	if (m_step == 2)
	{
		file << (CT2A)str<< "=" << (CT2A)str3 << "\n";
	}
	
	file.close();
	//SetDlgItemInt(IDC_EDIT_RESULT, m_value);//연산된 값을 화면에 출력

}

void CCalculatorDlg::OnBnClickedButtonCe()
{
	SetDlgItemText(IDC_EDIT_RESULT, L" ");

	CString str;
	GetDlgItemText(IDC_EDIT_RESULT, str);
	str.Delete(str.GetLength() - 1, 1);
	SetDlgItemText(IDC_EDIT_RESULT, str);
}

void CCalculatorDlg::OnBnClickedButtonC()
{
	UpdateData(TRUE);

	CEdit* pResult = (CEdit*)GetDlgItem(IDC_EDIT_RESULT);
	CEdit* pHistory = (CEdit*)GetDlgItem(IDC_EDIT_HISTORY);
	pHistory->SetWindowTextW(L" ");
	pResult->SetWindowTextW(L" ");
	
	m_value = 0;
	m_step = 0;
	m_count = 0;
	m_operater_flag = 0;

	UpdateData(FALSE);
}

void CCalculatorDlg::OnBnClickedButtonComma()
{
	CString str;
	GetDlgItemText(IDC_EDIT_RESULT, str);
	SetDlgItemText(IDC_EDIT_RESULT, str + '.');
}

void CCalculatorDlg::OnBnClickedButtonBackspace()
{
	CString str;
	GetDlgItemText(IDC_EDIT_RESULT, str);
	str.Delete(str.GetLength() - 1, 1);
	SetDlgItemText(IDC_EDIT_RESULT, str);
}

void CCalculatorDlg::OnBnClickedButtonSqrt()
{
	UpdateData(TRUE);

	CString str, omg;
	double m_value_two = GetDlgItemInt(IDC_EDIT_RESULT);
	GetDlgItemText(IDC_EDIT_RESULT, omg);
	GetDlgItemText(IDC_EDIT_HISTORY, str);

	m_value_two = _wtof(omg);
	/*if (str == L" " || str == "")
	{
	str = omg;
	str.Trim(L" ");
	}*/
	SetDlgItemText(IDC_EDIT_HISTORY, str + L"sqrt(" + omg + ')');
	omg.Format(L"%f", sqrt(m_value_two));
	omg.TrimRight(L"0");
	omg.TrimRight(L".");

	SetDlgItemText(IDC_EDIT_RESULT, omg);

	m_step = 2;
	UpdateData(FALSE);
}

void CCalculatorDlg::OnBnClickedButtonZegop()
{
	CString str, omg;
	double m_value_two = GetDlgItemInt(IDC_EDIT_RESULT);
	GetDlgItemText(IDC_EDIT_RESULT, omg);
	GetDlgItemText(IDC_EDIT_HISTORY, str);
	m_value_two = _wtof(omg);
	/*if (str == L" " || str == "")
	{
	str = omg;
	str.Trim(L" ");
	}*/
	SetDlgItemText(IDC_EDIT_HISTORY, str + L"Square(" + omg + ')');
	omg.Format(L"%f", m_value_two * m_value_two);
	omg.TrimRight(L"0");
	omg.TrimRight(L".");

	SetDlgItemText(IDC_EDIT_RESULT, omg);

	m_step = 2;

	UpdateData(FALSE);
}

void CCalculatorDlg::OnBnClickedButtonBoonsoo()
{
	CString str, omg;
	double m_value_two = GetDlgItemInt(IDC_EDIT_RESULT);
	GetDlgItemText(IDC_EDIT_RESULT, omg);
	GetDlgItemText(IDC_EDIT_HISTORY, str);
	m_value_two = _wtof(omg);
	if (str == L" " || str == "")
	{
		str = omg;
		str.Trim(L" ");
	}
	SetDlgItemText(IDC_EDIT_HISTORY, L"Reciproc(" + str + ')');
	if (boonsoo_twice == false)
	{
		omg.Format(L"%f", 1 / m_value_two);
		omg.TrimRight(L"0");
		omg.TrimRight(L".");
		boonsoo_twice = true;
	}
	else
	{
		omg.Format(L"%d",(int)(1 / m_value_two));
		boonsoo_twice = false;
	}
	

	SetDlgItemText(IDC_EDIT_RESULT, omg);

	m_step = 2;

	UpdateData(FALSE);
}

void CCalculatorDlg::OnBnClickedButtonPm()
{
	UpdateData(TRUE);

	CString  omg;
	double m_value_two = GetDlgItemInt(IDC_EDIT_RESULT);
	GetDlgItemText(IDC_EDIT_RESULT, omg);
	m_value_two = _wtof(omg);

	omg.Format(L"%f", -1 * m_value_two);
	omg.TrimRight(L"0");
	omg.TrimRight(L".");

	SetDlgItemText(IDC_EDIT_RESULT, omg);
	m_step = 2;

	UpdateData(FALSE);
}

void CCalculatorDlg::OnBnClickedButtonPercent()
{
	UpdateData(TRUE);

	CString  omg;
	double m_value_two = GetDlgItemInt(IDC_EDIT_RESULT);
	double m_flant2;
	GetDlgItemText(IDC_EDIT_RESULT, omg);
	m_value_two = _wtof(omg);

	m_flant2 = m_flant * (m_value_two / 100.0);
	omg.Format(L"%f", m_flant2);
	omg.TrimRight(L"0");
	omg.TrimRight(L".");

	SetDlgItemText(IDC_EDIT_RESULT, omg);
	m_step = 2;

	UpdateData(FALSE);
}

void CCalculatorDlg::OnBnClickedButtonHistory()
{
	
	CalculatorHistoryDlg dlg=new CalculatorHistoryDlg;
	std::ifstream file("save.dat");
	if (file.fail())
	{
		std::ofstream file2("save.dat");
		file2.close();
	}
	file.close();
	dlg.DoModal();
	
	if (bChange)
	{
		bChange = false;
		SetDlgItemText(IDC_EDIT_RESULT, result);
		SetDlgItemText(IDC_EDIT_HISTORY, history);
	}
	
}

