#pragma once
#include "afxwin.h"

// CTab2 ��ȭ �����Դϴ�.

class CTab2 : public CDialogEx
{
	DECLARE_DYNAMIC(CTab2)

public:
	CTab2(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CTab2();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG2 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnLbnSelchangeList1();
	virtual BOOL OnInitDialog();
	// ���� ��ȯ�� ������Ʈ���� ����Ʈ
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
