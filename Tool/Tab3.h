#pragma once
#include "afxwin.h"


// CTab3 대화 상자입니다.

class CTab3 : public CDialogEx
{
	DECLARE_DYNAMIC(CTab3)

public:
	CTab3(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CTab3();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG3 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CListBox m_Cube_List;
	CListBox m_Tex_ListBox;
	CListBox m_Scene_ListBox;
	virtual BOOL OnInitDialog();
	afx_msg void Delete_Button();
	afx_msg void Save_Button();
	afx_msg void Load_Button();
	BOOL m_Collison_CB;
	afx_msg void Collison_CheckBox();
};
