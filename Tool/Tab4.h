#pragma once
#include "afxwin.h"


// CTab4 대화 상자입니다.

class CTab4 : public CDialogEx
{
	DECLARE_DYNAMIC(CTab4)

public:
	CTab4(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CTab4();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG4 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

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
