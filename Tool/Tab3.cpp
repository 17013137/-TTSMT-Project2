// Tab3.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "Tool.h"
#include "Tab3.h"
#include "afxdialogex.h"

#include "GameInstance.h"
#include "GameObject.h"

#include "MainFrm.h"
#include "ToolView.h"

#include "Layer.h"
// CTab3 ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CTab3, CDialogEx)

CTab3::CTab3(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG3, pParent)
	, m_Collison_CB(FALSE)
{

}

CTab3::~CTab3()
{
}

void CTab3::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_Cube_List);
	DDX_Control(pDX, IDC_LIST2, m_Tex_ListBox);
	DDX_Control(pDX, IDC_LIST3, m_Scene_ListBox);
	DDX_Check(pDX, IDC_CHECK1, m_Collison_CB);
}


BEGIN_MESSAGE_MAP(CTab3, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CTab3::Delete_Button)
	ON_BN_CLICKED(IDC_BUTTON2, &CTab3::Save_Button)
	ON_BN_CLICKED(IDC_BUTTON12, &CTab3::Load_Button)
	ON_BN_CLICKED(IDC_CHECK1, &CTab3::Collison_CheckBox)
END_MESSAGE_MAP()


// CTab3 �޽��� ó�����Դϴ�.

BOOL CTab3::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	CString tpath = TEXT("./CubeObject/*.*");

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
		m_Cube_List.AddString(fileName);
	}

	CString tpath2 = TEXT("./Bin/Resources/ToolTextures/Cube/*.*");

	CFileFind finder2;

	BOOL bWorking2 = finder2.FindFile(tpath2); //

	CString fileName2;
	CString DirName2;

	while (bWorking2)
	{
		//���� ���� or ���� �� �����ϸ�ٸ� TRUE ��ȯ
		bWorking2 = finder2.FindNextFile();

		// folder �� ���� continue
		if (finder2.IsDirectory() || finder2.IsDots())
			continue;

		CString _fileName = finder2.GetFileName();
		CString _file;

		fileName2 = finder2.GetFileTitle();
		
		m_Tex_ListBox.AddString(fileName2);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
				  // ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}


void CTab3::Delete_Button()
{
	UpdateData(TRUE);

	if (m_Scene_ListBox.GetCurSel() >= 0) {
		//���� �ߴ��� �������
		CMainFrame*      pMain = dynamic_cast<CMainFrame*>(AfxGetMainWnd());
		CToolView*      pToolView = dynamic_cast<CToolView*>(pMain->m_MainSplitter.GetPane(0, 1));

		int _sel = m_Scene_ListBox.GetCurSel();

		CUBEDATA* _cube = pToolView->v_CubeList[_sel];
		_uint _ID = _cube->CubeID;
		pToolView->v_CubeList.erase(pToolView->v_CubeList.begin() + _sel);

		CLayer* temp = CGameInstance::GetInstance()->Get_GameObejct_Layer(STAGE_SCENE, L"Cube");

		if (FAILED(CGameInstance::GetInstance()->Remove_Layer_Object(temp, _sel))) {
			AfxMessageBox(L"���� ����!!");

		}

		m_Scene_ListBox.DeleteString(m_Scene_ListBox.GetCurSel());

	}

	UpdateData(FALSE);
}


void CTab3::Save_Button()
{
	UpdateData(TRUE);
	vector<WALLDATA*> _data;
	CMainFrame*      pMain = dynamic_cast<CMainFrame*>(AfxGetMainWnd());
	CToolView*      pToolView = dynamic_cast<CToolView*>(pMain->m_MainSplitter.GetPane(0, 1));
	vector<CUBEDATA*> v_WallList = pToolView->v_CubeList;

	for (auto& iter : v_WallList) {
		WALLDATA* _copy = new WALLDATA;
		_copy->isBlock= iter->CubeID;
		_copy->TexID = iter->TexID;
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
			WriteFile(hFile, &iter->isBlock, sizeof(_uint), &dwByte, NULL);
			WriteFile(hFile, &iter->TexID, sizeof(_uint), &dwByte, NULL);
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


void CTab3::Load_Button()
{
	vector<WALLDATA*> _load;
	CMainFrame*      pMain = dynamic_cast<CMainFrame*>(AfxGetMainWnd());
	CToolView*      pToolView = dynamic_cast<CToolView*>(pMain->m_MainSplitter.GetPane(0, 1));


	if (!pToolView->v_CubeList.empty()) {
		pToolView->v_CubeList.clear();
		pToolView->v_CubeList.shrink_to_fit();
	}

	m_Scene_ListBox.ResetContent();

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
		WALLDATA* pObjData = nullptr;

		while (true) {
			pObjData = new WALLDATA;
			ReadFile(hFile, &pObjData->isBlock, sizeof(_uint), &dwByte, nullptr);
			ReadFile(hFile, &pObjData->TexID, sizeof(_uint), &dwByte, nullptr);
			ReadFile(hFile, &pObjData->WorldMTX, sizeof(_float4x4), &dwByte, nullptr);

			if (0 == dwByte)
			{
				Safe_Delete(pObjData);
				break;
			}

			_tchar _proto[MAX_PATH] = TEXT("Prototype_GameObject_Cube");
			CGameInstance* m_Gameinstance = CGameInstance::GetInstance();

			pObjData->WorldMTX.m[0][3] = pObjData->isBlock;
			pObjData->WorldMTX.m[1][3] = pObjData->TexID;

			m_Gameinstance->Add_GameObjectToLayer(STAGE_SCENE, L"Cube", _proto, pObjData->WorldMTX);
			CLayer* obj_layer = m_Gameinstance->Get_GameObejct_Layer(STAGE_SCENE, L"Cube");
			size_t cnt = obj_layer->m_ObjectList.size();
			CGameObject* _obj = m_Gameinstance->Get_Obj_in_Layer(obj_layer, int(cnt - 1));
			CTransform* _trans = (CTransform*)_obj->Get_Component(L"Com_Transform");

			CUBEDATA* _tooldata = new CUBEDATA;
			_tooldata->CubeID = pObjData->isBlock;
			_tooldata->TexID = pObjData->TexID;
			_tooldata->Transform = _trans;
			_tooldata->Object = _obj;
			pToolView->v_CubeList.push_back(_tooldata);
			m_Scene_ListBox.AddString(L"Cube");
		}
		CloseHandle(hFile);
	}
}


void CTab3::Collison_CheckBox()
{
	UpdateData(TRUE);

	if (m_Collison_CB)
		m_Collison_CB = false;
	else
		m_Collison_CB = true;

	UpdateData(FALSE);

}
