#pragma once
#include "afxwin.h"

// CTab2 대화 상자입니다.

class CTab2 : public CDialogEx
{
	DECLARE_DYNAMIC(CTab2)

public:
	CTab2(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CTab2();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG2 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnLbnSelchangeList1();
	virtual BOOL OnInitDialog();
	// 씬에 소환된 오브젝트들의 리스트
	CListBox m_Obj_list;
	CListBox m_SObj_List;
	CListBox m_CubeTex__ListBox;
public:
	BOOL m_Camera_Set;
	afx_msg void Camera_Set_Button();
	afx_msg void Save_Button();
	afx_msg void Load_Button();
	afx_msg void Scene_Delete_Button();
	BOOL Tile_PickingMode_Box;
	afx_msg void Tile_Picking_CheckBox();
	BOOL m_Rotation_90;
	afx_msg void Rotation_90_CheckBox();
};
