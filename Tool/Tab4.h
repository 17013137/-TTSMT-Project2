#pragma once
#include "afxwin.h"


// CTab4 ��ȭ �����Դϴ�.

class CTab4 : public CDialogEx
{
	DECLARE_DYNAMIC(CTab4)

public:
	CTab4(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CTab4();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG4 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CListBox m_Type_ListBox;
	CListBox m_Scene_ListBox;
	CListBox m_Tex_ListBox;
	afx_msg void Save_Button();
	afx_msg void Load_Button();
	afx_msg void Delete_Button();
};
