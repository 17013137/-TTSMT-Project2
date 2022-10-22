#pragma once
#include "afxcmn.h"

class CTab1;
class CTab2;
class CTab3;
class CTab4;

// CTabDlg dialog

class CTabDlg : public CDialog
{
	DECLARE_DYNAMIC(CTabDlg)

public:
	CTabDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CTabDlg();

public:

	CTab1 *pDlg1 = nullptr;
	CTab2 *pDlg2 = nullptr;
	CTab3 *pDlg3 = nullptr;
	CTab4 *pDlg4 = nullptr;

	CTabCtrl m_Tab;
// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TABDLG };
#endif
public:
	int m_iSelectTab = 0;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	
	afx_msg void OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult);
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
};
