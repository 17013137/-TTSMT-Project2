// Tab4.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "Tool.h"
#include "Tab4.h"
#include "afxdialogex.h"
#include "GameInstance.h"
#include "GameObject.h"

#include "MainFrm.h"
#include "ToolView.h"

#include "Layer.h"


// CTab4 ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CTab4, CDialogEx)

CTab4::CTab4(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG4, pParent)
{

}

CTab4::~CTab4()
{
}

void CTab4::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_Type_ListBox);
	DDX_Control(pDX, IDC_LIST3, m_Scene_ListBox);
	DDX_Control(pDX, IDC_LIST2, m_Tex_ListBox);
}


BEGIN_MESSAGE_MAP(CTab4, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON2, &CTab4::Save_Button)
	ON_BN_CLICKED(IDC_BUTTON12, &CTab4::Load_Button)
	ON_BN_CLICKED(IDC_BUTTON1, &CTab4::Delete_Button)
END_MESSAGE_MAP()


// CTab4 �޽��� ó�����Դϴ�.


BOOL CTab4::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	CString tpath = TEXT("./BlendObj/*.*");

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
		m_Type_ListBox.AddString(fileName);
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
		m_Tex_ListBox.AddString(fileName);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
				  // ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}


void CTab4::Save_Button()
{
	UpdateData(TRUE);

	vector<OBJDATA*> _data;
	CMainFrame*      pMain = dynamic_cast<CMainFrame*>(AfxGetMainWnd());
	CToolView*      pToolView = dynamic_cast<CToolView*>(pMain->m_MainSplitter.GetPane(0, 1));
	vector<TILEDATA*> v_BlendList = pToolView->v_BlendList;

	for (auto& iter : v_BlendList) {
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


void CTab4::Load_Button()
{
	vector<OBJDATA*> _load;
	CMainFrame*      pMain = dynamic_cast<CMainFrame*>(AfxGetMainWnd());
	CToolView*      pToolView = dynamic_cast<CToolView*>(pMain->m_MainSplitter.GetPane(0, 1));


	if (!pToolView->v_BlendList.empty()) {
		pToolView->v_BlendList.clear();
		pToolView->v_BlendList.shrink_to_fit();
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

			_tchar _proto[MAX_PATH] = TEXT("Prototype_GameObject_XRect");
			CGameInstance* m_Gameinstance = CGameInstance::GetInstance();

			pObjData->WorldMTX.m[0][3] = (_float)pObjData->ObjID;

			m_Gameinstance->Add_GameObjectToLayer(STAGE_SCENE, L"BLEND", _proto, (_float4x4)pObjData->WorldMTX);
			CLayer* obj_layer = m_Gameinstance->Get_GameObejct_Layer(STAGE_SCENE, L"BLEND");
			size_t cnt = obj_layer->m_ObjectList.size();
			CGameObject* _obj = m_Gameinstance->Get_Obj_in_Layer(obj_layer, int(cnt - 1));
			CTransform* _trans = (CTransform*)_obj->Get_Component(L"Com_Transform");

			TILEDATA* _tooldata = new TILEDATA;
			_tooldata->TileID = pObjData->ObjID;
			_tooldata->Transform = _trans;
			_tooldata->Object = _obj;
			pToolView->v_BlendList.push_back(_tooldata);

			CString itochar;																//���� ���ں�ȯ
			itochar.Format(_T("%d"), pObjData->ObjID);
			m_Scene_ListBox.AddString(itochar);
		}
		CloseHandle(hFile);
	}
}


void CTab4::Delete_Button()
{
	UpdateData(TRUE);

	if (m_Scene_ListBox.GetCurSel() >= 0) {
		//���� �ߴ��� �������
		CMainFrame*      pMain = dynamic_cast<CMainFrame*>(AfxGetMainWnd());
		CToolView*      pToolView = dynamic_cast<CToolView*>(pMain->m_MainSplitter.GetPane(0, 1));

		int _sel = m_Scene_ListBox.GetCurSel();


		pToolView->v_BlendList.erase(pToolView->v_BlendList.begin() + _sel);

		CLayer* temp = CGameInstance::GetInstance()->Get_GameObejct_Layer(STAGE_SCENE, L"BLEND");

		if (FAILED(CGameInstance::GetInstance()->Remove_Layer_Object(temp, _sel))) {
			AfxMessageBox(L"���� ����!!");

		}
		m_Scene_ListBox.DeleteString(m_Scene_ListBox.GetCurSel());

	}

	UpdateData(FALSE);
}
