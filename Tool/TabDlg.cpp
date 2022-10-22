// TabDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Tool.h"
#include "TabDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#include "Tab1.h"
#include "Tab2.h"
#include "Tab3.h"
#include "Tab4.h"

// CTabDlg dialog

IMPLEMENT_DYNAMIC(CTabDlg, CDialog)

CTabDlg::CTabDlg(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_TABDLG, pParent)
{

}

CTabDlg::~CTabDlg()
{
}

void CTabDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB1, m_Tab);
}


BEGIN_MESSAGE_MAP(CTabDlg, CDialog)

	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, &CTabDlg::OnTcnSelchangeTab1)
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CTabDlg message handlers



void CTabDlg::OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: Add your control notification handler code here
	int sel = m_Tab.GetCurSel();
	m_iSelectTab = sel + 1;

	switch (sel) {

	case 0:
		pDlg1->ShowWindow(SW_SHOW);
		pDlg2->ShowWindow(SW_HIDE);
		pDlg3->ShowWindow(SW_HIDE);
		pDlg4->ShowWindow(SW_HIDE);
		break;

	case 1:
		pDlg1->ShowWindow(SW_HIDE);
		pDlg2->ShowWindow(SW_SHOW);
		pDlg3->ShowWindow(SW_HIDE);
		pDlg4->ShowWindow(SW_HIDE);
		break;

	case 2:
		pDlg1->ShowWindow(SW_HIDE);
		pDlg2->ShowWindow(SW_HIDE);
		pDlg3->ShowWindow(SW_SHOW);
		pDlg4->ShowWindow(SW_HIDE);
		break;

	case 3:
		pDlg1->ShowWindow(SW_HIDE);
		pDlg2->ShowWindow(SW_HIDE);
		pDlg3->ShowWindow(SW_HIDE);
		pDlg4->ShowWindow(SW_SHOW);
		break;
	}
}


BOOL CTabDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_Tab.InsertItem(0, _T("Tile"));
	m_Tab.InsertItem(1, _T("Object"));
	m_Tab.InsertItem(2, _T("Temp"));
	m_Tab.InsertItem(3, _T("Effect"));

	m_Tab.SetCurSel(0);

	CRect rect;
	m_Tab.GetWindowRect(&rect);

	pDlg1 = new CTab1;
	pDlg1->Create(IDD_DIALOG1, &m_Tab);
	pDlg1->MoveWindow(0, 25, rect.Width(), rect.Height());
	pDlg1->ShowWindow(SW_SHOW);


	pDlg2 = new CTab2;
	pDlg2->Create(IDD_DIALOG2, &m_Tab);
	pDlg2->MoveWindow(0, 25, rect.Width(), rect.Height());
	pDlg2->ShowWindow(SW_HIDE);

	pDlg3 = new CTab3;
	pDlg3->Create(IDD_DIALOG3, &m_Tab);
	pDlg3->MoveWindow(0, 25, rect.Width(), rect.Height());
	pDlg3->ShowWindow(SW_HIDE);

	pDlg4 = new CTab4;
	pDlg4->Create(IDD_DIALOG4, &m_Tab);
	pDlg4->MoveWindow(0, 25, rect.Width(), rect.Height());
	pDlg4->ShowWindow(SW_HIDE);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}


void CTabDlg::OnDestroy()
{
	CDialog::OnDestroy();

	delete pDlg1;
	delete pDlg2;
	delete pDlg3;
	delete pDlg4;
}
