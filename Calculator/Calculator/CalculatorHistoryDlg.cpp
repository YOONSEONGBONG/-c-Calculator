// CalculatorHistoryDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Calculator.h"
#include "CalculatorHistoryDlg.h"
#include "afxdialogex.h"
#include <fstream>
#include "CalculatorDlg.h"

// CalculatorHistoryDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CalculatorHistoryDlg, CDialogEx)

CalculatorHistoryDlg::CalculatorHistoryDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CalculatorHistoryDlg::IDD, pParent)
{

}

CalculatorHistoryDlg::~CalculatorHistoryDlg()
{
}

void CalculatorHistoryDlg::DoDataExchange(CDataExchange* pDX)
{	
	char tmp[1000];
	CString str;
	
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, historyList);
	std::ifstream file("save.dat");
	while (!file.eof()){
		file.getline(tmp, 1000);
		str = tmp;
		str.TrimLeft(L" ");	
		if (str != L""){
			historyList.AddString(str);
		}
		
	}
	file.close();
	

	
}


BEGIN_MESSAGE_MAP(CalculatorHistoryDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_INSERT, &CalculatorHistoryDlg::OnBnClickedButtonInsert)
	ON_BN_CLICKED(IDC_BUTTON_REMOVE, &CalculatorHistoryDlg::OnBnClickedButtonRemove)
	
END_MESSAGE_MAP()


// CalculatorHistoryDlg 메시지 처리기입니다.


void CalculatorHistoryDlg::OnBnClickedButtonInsert()
{
	CString str,str2,tmp;
	int index = historyList.GetCurSel();

	if (index != LB_ERR)
	{
		historyList.GetText(index, tmp);
		AfxExtractSubString(str, tmp, 0, '=');
		AfxExtractSubString(str2, tmp, 1, '=');
	}
	CCalculatorDlg *pDlg = (CCalculatorDlg*)AfxGetMainWnd();
	pDlg->history = str;
	pDlg->result = str2;
	pDlg->bChange = true;
	pDlg->m_step = 2;
	OnOK();
}


void CalculatorHistoryDlg::OnBnClickedButtonRemove()
{	
	
	CString str;
	int index = historyList.GetCurSel();

	if (index != LB_ERR)
	{
		historyList.DeleteString(index);
	}
	std::ofstream file;
	file.open("save.dat", std::ios::trunc);
	for (int i = 0; i < historyList.GetCount(); i++){
		historyList.GetText(i, str);
		file << (CT2A)str<< "\n";
	}
	file.close();
	

}






