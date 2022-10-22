// Tab2.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "Tool.h"
#include "Tab2.h"
#include "afxdialogex.h"
#include "GameInstance.h"
#include "GameObject.h"

#include "MainFrm.h"
#include "ToolView.h"

#include "Layer.h"
// CTab2 ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CTab2, CDialogEx)




CTab2::CTab2(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG2, pParent)
	, m_Camera_Set(FALSE)
	, Tile_PickingMode_Box(FALSE)
	, m_Rotation_90(FALSE)
{

}

CTab2::~CTab2()
{
}

void CTab2::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_Obj_list);
	DDX_Control(pDX, IDC_LIST2, m_SObj_List);
	DDX_Check(pDX, IDC_CHECK1, m_Camera_Set);
	DDX_Check(pDX, IDC_CHECK2, Tile_PickingMode_Box);
	DDX_Check(pDX, IDC_CHECK3, m_Rotation_90);
	DDX_Control(pDX, IDC_LIST3, m_CubeTex__ListBox);
}




BEGIN_MESSAGE_MAP(CTab2, CDialogEx)
	ON_LBN_SELCHANGE(IDC_LIST1, &CTab2::OnLbnSelchangeList1)
	ON_BN_CLICKED(IDC_CHECK1, &CTab2::Camera_Set_Button)
	ON_BN_CLICKED(IDC_BUTTON1, &CTab2::Save_Button)
	ON_BN_CLICKED(IDC_BUTTON8, &CTab2::Load_Button)
	ON_BN_CLICKED(IDC_BUTTON2, &CTab2::Scene_Delete_Button)
	ON_BN_CLICKED(IDC_CHECK2, &CTab2::Tile_Picking_CheckBox)
	ON_BN_CLICKED(IDC_CHECK3, &CTab2::Rotation_90_CheckBox)
END_MESSAGE_MAP()


// CTab2 �޽��� ó�����Դϴ�.


void CTab2::OnLbnSelchangeList1()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}


BOOL CTab2::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	CString tpath = TEXT("./Object/*.*");

	// �˻� Ŭ����
	CFileFind finder;

	BOOL bWorking = finder.FindFile(tpath); //

	CString fileName;
	CString DirName;

	while (bWorking)
	{
		bWorking = finder.FindNextFile();
		if (finder.IsDirectory() || finder.IsDots())
			continue;

		CString _fileName = finder.GetFileName();
		CString _file;

		fileName = finder.GetFileTitle(); 
		m_Obj_list.AddString(fileName);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
				  // ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}

void CTab2::Camera_Set_Button()
{
	UpdateData(TRUE);

	if (m_Camera_Set) {
		m_SObj_List.SetCurSel(-1);
		m_Camera_Set = false;
	}
	else {
		m_Camera_Set = true;
	}
	UpdateData(FALSE);
}

void CTab2::Save_Button()
{
	UpdateData(TRUE);
	vector<OBJDATA*> _data;
	CMainFrame*      pMain = dynamic_cast<CMainFrame*>(AfxGetMainWnd());
	CToolView*      pToolView = dynamic_cast<CToolView*>(pMain->m_MainSplitter.GetPane(0, 1));
	vector<TOOLDATA*> v_ObjList = pToolView->v_ObjList;

	for (auto& iter : v_ObjList) {
		OBJDATA* _copy = new OBJDATA;
		_copy->ObjID = iter->ObjID;
		_copy->WorldMTX = iter->Transform->Get_WorldMatrix();
		_data.push_back(_copy);
	}

	CFileDialog	Dlg(FALSE,	// true�� ��� ���� ���, false �� ��� �ٸ� �̸����� ���� ���
		L"dat", // default ���� Ȯ���, ���� �� Ȯ���ڸ��� ��������� ������ ���� ������ Ȯ���ڸ��� ����ϰ� ������
		L"*.dat", // ��ȭ���ڿ� ǥ�õ� ���� ���ϸ�
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, // OFN_HIDEREADONLY(�б����� üũ�ڽ� ����), OFN_OVERWRITEPROMPT(�ߺ� ���� ���� �� ���޽��� ���� �ɼ�)
		L"Data File(*.dat)|*.dat||",	// ��ȭ ���ڿ� ǥ�õ� ���� ����, �޺��ڽ��� ��µ� ���ڿ� | ���� ����� ���͸� ���ڿ� ||
		this); // �θ� ������ �ּ�

	TCHAR	szPath[MAX_PATH] = L"";
	GetCurrentDirectory(MAX_PATH, szPath);
	PathRemoveFileSpec(szPath);
	lstrcat(szPath, L"\\Data");
	Dlg.m_ofn.lpstrInitialDir = szPath;

	if (IDOK == Dlg.DoModal())
	{
		CString	strFind = Dlg.GetPathName();
		const TCHAR*	pGetPath = strFind.GetString();
		HANDLE      hFile = CreateFile(pGetPath, GENERIC_WRITE, 0, 0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

		if (INVALID_HANDLE_VALUE == hFile) {
			AfxMessageBox(L"Device Create Failed");
			return;
		}

		DWORD dwByte = 0;
		for (auto iter : _data) {
			WriteFile(hFile, &iter->ObjID, sizeof(_uint), &dwByte, NULL);
			WriteFile(hFile, &iter->WorldMTX, sizeof(_float4x4), &dwByte, NULL);

		}
		CloseHandle(hFile);
		AfxMessageBox(L"���� ����!");

		for (auto& iter : _data) {
			Safe_Delete(iter);
			iter = nullptr;
			iter++;
		}
		_data.clear();

		CloseHandle(hFile);
	}

	
	UpdateData(FALSE);
}


void CTab2::Load_Button()
{
	vector<OBJDATA*> _load;
	CMainFrame*      pMain = dynamic_cast<CMainFrame*>(AfxGetMainWnd());
	CToolView*      pToolView = dynamic_cast<CToolView*>(pMain->m_MainSplitter.GetPane(0, 1));
	

	if (!pToolView->v_ObjList.empty()) {
		pToolView->v_ObjList.clear();
		pToolView->v_ObjList.shrink_to_fit();
	}

	m_SObj_List.ResetContent();

	CFileDialog	Dlg(TRUE,	// true�� ��� ���� ���, false �� ��� �ٸ� �̸����� ���� ���
		L"dat", // default ���� Ȯ���, ���� �� Ȯ���ڸ��� ��������� ������ ���� ������ Ȯ���ڸ��� ����ϰ� ������
		L"*.dat", // ��ȭ���ڿ� ǥ�õ� ���� ���ϸ�
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, // OFN_HIDEREADONLY(�б����� üũ�ڽ� ����), OFN_OVERWRITEPROMPT(�ߺ� ���� ���� �� ���޽��� ���� �ɼ�)
		L"Data File(*.dat)|*.dat||",	// ��ȭ ���ڿ� ǥ�õ� ���� ����, �޺��ڽ��� ��µ� ���ڿ� | ���� ����� ���͸� ���ڿ� ||
		this); // �θ� ������ �ּ�

	TCHAR	szPath[MAX_PATH] = L"";
	GetCurrentDirectory(MAX_PATH, szPath);
	PathRemoveFileSpec(szPath);
	lstrcat(szPath, L"\\Data");
	Dlg.m_ofn.lpstrInitialDir = szPath;


	// --

	if (IDOK == Dlg.DoModal())
	{
		CString	strFind = Dlg.GetPathName();
		const TCHAR*	pGetPath = strFind.GetString();

		HANDLE		hFile = CreateFile(pGetPath, GENERIC_READ, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
		if (INVALID_HANDLE_VALUE == hFile)
			return;

		DWORD	dwByte = 0;
		OBJDATA* pObjData = nullptr;

		while (true) {
			pObjData = new OBJDATA;
			ReadFile(hFile, &pObjData->ObjID, sizeof(_uint), &dwByte, nullptr);
			ReadFile(hFile, &pObjData->WorldMTX, sizeof(_float4x4), &dwByte, nullptr);
			if (0 == dwByte)
			{
				Safe_Delete(pObjData);
				break;
			}

			//���ȿ� �����Ͱ���

			_tchar _proto[MAX_PATH] = TEXT("Prototype_GameObject_");
			lstrcat(_proto, enum_str[pObjData->ObjID]);
			CGameInstance* m_Gameinstance = CGameInstance::GetInstance();

			m_Gameinstance->Add_GameObjectToLayer(STAGE_SCENE, L"OBJECT", _proto, _float4x4(pObjData->WorldMTX));
			CLayer* obj_layer = m_Gameinstance->Get_GameObejct_Layer(STAGE_SCENE, L"OBJECT");
			size_t cnt = obj_layer->m_ObjectList.size();
			CGameObject* _obj = m_Gameinstance->Get_Obj_in_Layer(obj_layer, int(cnt - 1));
			CTransform* _trans = (CTransform*)_obj->Get_Component(L"Com_Transform");

			TOOLDATA* _tooldata = new TOOLDATA;
			_tooldata->ObjID = pObjData->ObjID;
			_tooldata->Transform = _trans;
			_tooldata->Object = _obj;
			pToolView->v_ObjList.push_back(_tooldata);
			m_SObj_List.AddString(enum_str[pObjData->ObjID]);
		}
		CloseHandle(hFile);
	}

	// --
	
}


void CTab2::Scene_Delete_Button()
{

	if (m_SObj_List.GetCurSel() >= 0) {
		//���� �ߴ��� �������
		CMainFrame*      pMain = dynamic_cast<CMainFrame*>(AfxGetMainWnd());
		CToolView*      pToolView = dynamic_cast<CToolView*>(pMain->m_MainSplitter.GetPane(0, 1));

		int _sel = m_SObj_List.GetCurSel();

		TOOLDATA* _data = pToolView->v_ObjList[_sel];
		pToolView->v_ObjList.erase(pToolView->v_ObjList.begin() + _sel);
		
		CLayer* temp = CGameInstance::GetInstance()->Get_GameObejct_Layer(STAGE_SCENE, L"OBJECT");
		
		if (FAILED(CGameInstance::GetInstance()->Remove_Layer_Object(temp, _sel))) {
			AfxMessageBox(L"���� ����!!");
		}
		delete _data;

		m_SObj_List.DeleteString(m_SObj_List.GetCurSel());
		
	}
}


void CTab2::Tile_Picking_CheckBox()
{
	UpdateData(TRUE);

	if (Tile_PickingMode_Box == TRUE) {
		Tile_PickingMode_Box = FALSE;
	}
	else {
		Tile_PickingMode_Box = TRUE;
	}

	UpdateData(FALSE);
}


void CTab2::Rotation_90_CheckBox()
{
	UpdateData(TRUE);

	if (m_Rotation_90) {
		m_Rotation_90 = false;
	}
	else {
		m_Rotation_90 = true;
	}
	UpdateData(FALSE); 
}
