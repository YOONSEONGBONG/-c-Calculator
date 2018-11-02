
// CalculatorDlg.cpp : ���� ����
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


// ���� ���α׷� ������ ���Ǵ� CAboutDlg ��ȭ �����Դϴ�.

class CAboutDlg : public CDialogEx
{
public:
	CString history;
	CString result;
	bool bChange = false;
	char m_operater_flag = 0; //NONE:0/plus:1/minus:2/multiply:3/division:4
	char m_step = 0;	 //������ ��ư Ȯ�κ���
	long int m_count = 0; //������ ī��Ʈ����
	long double m_value = 0; //���� ���� �����ϱ����� ����
	long double m_flant = 0; //���ڸ� �ӽ� �����ϱ� ���� ����(%����)
	bool boonsoo_twice = false;
public:
	CAboutDlg();

	// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	// �����Դϴ�.
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


// CCalculatorDlg ��ȭ ����



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


// CCalculatorDlg �޽��� ó����

BOOL CCalculatorDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// �ý��� �޴��� "����..." �޴� �׸��� �߰��մϴ�.

	// IDM_ABOUTBOX�� �ý��� ��� ������ �־�� �մϴ�.
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

	// �� ��ȭ ������ �������� �����մϴ�.  ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	//  �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.

	// TODO: ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.

	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
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

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�.  ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void CCalculatorDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �׸��⸦ ���� ����̽� ���ؽ�Ʈ�Դϴ�.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Ŭ���̾�Ʈ �簢������ �������� ����� ����ϴ�.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �������� �׸��ϴ�.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// ����ڰ� �ּ�ȭ�� â�� ���� ���ȿ� Ŀ���� ǥ�õǵ��� �ý��ۿ���
//  �� �Լ��� ȣ���մϴ�.
HCURSOR CCalculatorDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

BOOL CCalculatorDlg::OnCommand(WPARAM wParam, LPARAM lParam)
{
	if (IDC_BUTTON_0 <= wParam&&wParam <= IDC_BUTTON_9) //�ַ��Ž���� �� Resource.h �� ���ڹ�ư ��ũ�� Ȯ��
	{
		CString str, number_str, str2; //���ڿ�
		number_str.Format(L"%d", wParam - IDC_BUTTON_0); //����'0'�� �������� ��´�

		if (m_step == 0) //�����ڰ� ������ �ʾ������
		{
			GetDlgItemText(IDC_EDIT_RESULT, str2); //����Ʈ�� �ԷµȰ��� str������ ����
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

		SetDlgItemText(IDC_EDIT_RESULT, str2 + number_str); //str�� ����� ���� ���ڰ��� ���� ���
	
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
	case 1: //���ϱ�
		m_value += m_value_two;
		break;

	case 2: //����
		m_value -= m_value_two;
		break;

	case 3: //���ϱ�
		m_value *= m_value_two;
		break;

	case 4: //������
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
	//SetDlgItemInt(IDC_EDIT_RESULT, m_value);//����� ���� ȭ�鿡 ���

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

