// Tab1.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "Tool.h"
#include "Tab1.h"
#include "afxdialogex.h"
#include "GameInstance.h"
#include "GameObject.h"

#include "MainFrm.h"
#include "ToolView.h"

#include "Layer.h"

// CTab1 ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CTab1, CDialogEx)

CTab1::CTab1(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG1, pParent)
	, m_VertexX(0)
	, m_VertexZ(0)
{

}

CTab1::~CTab1()
{
}

void CTab1::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_VertexX);
	DDX_Text(pDX, IDC_EDIT3, m_VertexZ);
	DDX_Control(pDX, IDC_LIST1, m_Tile_Listbox);
	DDX_Control(pDX, IDC_LIST2, m_Scene_ListBox);
	DDX_Control(pDX, IDC_LIST3, m_Blend_ListBox);
	DDX_Control(pDX, IDC_LIST5, m_Scene_Blend);
	DDX_Control(pDX, IDC_LIST4, m_Blend_Texture_ListBox);
}


BEGIN_MESSAGE_MAP(CTab1, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CTab1::VertexCnt_Button)
	ON_LBN_SELCHANGE(IDC_LIST1, &CTab1::Tile_ListBox)
	ON_LBN_SELCHANGE(IDC_LIST2, &CTab1::OnLbnSelchangeList2)
	ON_BN_CLICKED(IDC_BUTTON4, &CTab1::Tile_Delete_Button)
	ON_BN_CLICKED(IDC_BUTTON11, &CTab1::Tile_Save_Button)
	ON_BN_CLICKED(IDC_BUTTON5, &CTab1::Load_Save_Button)
END_MESSAGE_MAP()


// CTab1 �޽��� ó�����Դϴ�.


void CTab1::VertexCnt_Button()
{
	UpdateData(TRUE);

	CMainFrame*		pMain = dynamic_cast<CMainFrame*>(AfxGetMainWnd());
	CToolView*		pToolView = dynamic_cast<CToolView*>(pMain->m_MainSplitter.GetPane(0, 1));

	pToolView->Ready_Prototype_Terrain(m_VertexX, m_VertexZ);

	UpdateData(FALSE);
}


BOOL CTab1::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	UpdateData(TRUE);

	m_VertexX = 80;
	m_VertexZ = 80;

	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

	CString tpath = TEXT("./Bin/Resources/ToolTextures/CartoonTile/*.*");

	// �˻� Ŭ����
	CFileFind finder;

	BOOL bWorking = finder.FindFile(tpath); //

	CString fileName;
	CString DirName;

	while (bWorking)
	{
		//���� ���� or ���� �� �����ϸ�ٸ� TRUE ��ȯ
		bWorking = finder.FindNextFile();

		// folder �� ���� continue
		if (finder.IsDirectory() || finder.IsDots())
			continue;

		//������ �̸�
		CString _fileName = finder.GetFileName();

		//���� ����
		fileName = finder.GetFileTitle();
		int _size = fileName.GetLength();

		//�о�� ���� �̸��� ����Ʈ�ڽ��� map�� ����
		m_Tile_Listbox.AddString(fileName);
	}


	//--����������Ʈ

	tpath = TEXT("./BlendObj/*.*");

	bWorking = finder.FindFile(tpath); //

	while (bWorking)
	{
		//���� ���� or ���� �� �����ϸ�ٸ� TRUE ��ȯ
		bWorking = finder.FindNextFile();

		// folder �� ���� continue
		if (finder.IsDirectory() || finder.IsDots())
			continue;

		//������ �̸�
		CString _fileName = finder.GetFileName();

		//���� ����
		fileName = finder.GetFileTitle();
		int _size = fileName.GetLength();

		//�о�� ���� �̸��� ����Ʈ�ڽ��� map�� ����
		m_Blend_ListBox.AddString(fileName);
	}


	tpath = TEXT("./Bin/Resources/ToolTextures/BlendObject/*.*");

	// �˻� Ŭ����

	bWorking = finder.FindFile(tpath); //

	while (bWorking)
	{
		//���� ���� or ���� �� �����ϸ�ٸ� TRUE ��ȯ
		bWorking = finder.FindNextFile();

		// folder �� ���� continue
		if (finder.IsDirectory() || finder.IsDots())
			continue;

		//������ �̸�
		CString _fileName = finder.GetFileName();

		//���� ����
		fileName = finder.GetFileTitle();
		int _size = fileName.GetLength();

		//�о�� ���� �̸��� ����Ʈ�ڽ��� map�� ����
		m_Blend_Texture_ListBox.AddString(fileName);
	}

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}


void CTab1::Tile_ListBox()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}


void CTab1::OnLbnSelchangeList2() // sel_chgange;
{
	// TODO: Add your control notification handler code here
}


void CTab1::Tile_Delete_Button()
{
	UpdateData(TRUE);

	if (m_Scene_ListBox.GetCurSel() >= 0) {
		//���� �ߴ��� �������
		CMainFrame*      pMain = dynamic_cast<CMainFrame*>(AfxGetMainWnd());
		CToolView*      pToolView = dynamic_cast<CToolView*>(pMain->m_MainSplitter.GetPane(0, 1));

		int _sel = m_Scene_ListBox.GetCurSel();


		pToolView->v_TileList.erase(pToolView->v_TileList.begin() + _sel);

		CLayer* temp = CGameInstance::GetInstance()->Get_GameObejct_Layer(STAGE_SCENE, L"TILE");

		if (FAILED(CGameInstance::GetInstance()->Remove_Layer_Object(temp, _sel))) {
			AfxMessageBox(L"���� ����!!");

		}
		m_Scene_ListBox.DeleteString(m_Scene_ListBox.GetCurSel());

	}

	UpdateData(FALSE);
}


void CTab1::Tile_Save_Button()
{

	UpdateData(TRUE);

	vector<OBJDATA*> _data;
	CMainFrame*      pMain = dynamic_cast<CMainFrame*>(AfxGetMainWnd());
	CToolView*      pToolView = dynamic_cast<CToolView*>(pMain->m_MainSplitter.GetPane(0, 1));
	vector<TILEDATA*> v_TileList = pToolView->v_TileList;

	for (auto& iter : v_TileList) {
		OBJDATA* _copy = new OBJDATA;
		_copy->ObjID = iter->TileID;
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


void CTab1::Load_Save_Button()
{

	vector<OBJDATA*> _load;
	CMainFrame*      pMain = dynamic_cast<CMainFrame*>(AfxGetMainWnd());
	CToolView*      pToolView = dynamic_cast<CToolView*>(pMain->m_MainSplitter.GetPane(0, 1));


	if (!pToolView->v_TileList.empty()) {
		pToolView->v_TileList.clear();
		pToolView->v_TileList.shrink_to_fit();
	}

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

	m_Scene_ListBox.ResetContent();


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

			_tchar _proto[MAX_PATH] = TEXT("Prototype_GameObject_Tile");
			CGameInstance* m_Gameinstance = CGameInstance::GetInstance();

			pObjData->WorldMTX.m[0][3] = (_float)pObjData->ObjID;

			m_Gameinstance->Add_GameObjectToLayer(STAGE_SCENE, L"TILE", _proto, (_float4x4)pObjData->WorldMTX);
			CLayer* obj_layer = m_Gameinstance->Get_GameObejct_Layer(STAGE_SCENE, L"TILE");
			size_t cnt = obj_layer->m_ObjectList.size();
			CGameObject* _obj = m_Gameinstance->Get_Obj_in_Layer(obj_layer, int(cnt - 1));
			CTransform* _trans = (CTransform*)_obj->Get_Component(L"Com_Transform");

			TILEDATA* _tooldata = new TILEDATA;
			_tooldata->TileID = pObjData->ObjID;
			_tooldata->Transform = _trans;
			_tooldata->Object = _obj;
			pToolView->v_TileList.push_back(_tooldata);

			CString itochar;																//���� ���ں�ȯ
			itochar.Format(_T("%d"), pObjData->ObjID);
			m_Scene_ListBox.AddString(itochar);
		}
		CloseHandle(hFile);
	}
	
}