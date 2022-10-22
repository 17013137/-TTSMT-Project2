// Tab3.cpp : 구현 파일입니다.
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
// CTab3 대화 상자입니다.

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


// CTab3 메시지 처리기입니다.

BOOL CTab3::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	CString tpath = TEXT("./CubeObject/*.*");

	// 검색 클래스
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
		//다음 파일 or 폴더 가 존재하면다면 TRUE 반환
		bWorking2 = finder2.FindNextFile();

		// folder 일 경우는 continue
		if (finder2.IsDirectory() || finder2.IsDots())
			continue;

		CString _fileName = finder2.GetFileName();
		CString _file;

		fileName2 = finder2.GetFileTitle();
		
		m_Tex_ListBox.AddString(fileName2);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CTab3::Delete_Button()
{
	UpdateData(TRUE);

	if (m_Scene_ListBox.GetCurSel() >= 0) {
		//원래 했던거 삭제모드
		CMainFrame*      pMain = dynamic_cast<CMainFrame*>(AfxGetMainWnd());
		CToolView*      pToolView = dynamic_cast<CToolView*>(pMain->m_MainSplitter.GetPane(0, 1));

		int _sel = m_Scene_ListBox.GetCurSel();

		CUBEDATA* _cube = pToolView->v_CubeList[_sel];
		_uint _ID = _cube->CubeID;
		pToolView->v_CubeList.erase(pToolView->v_CubeList.begin() + _sel);

		CLayer* temp = CGameInstance::GetInstance()->Get_GameObejct_Layer(STAGE_SCENE, L"Cube");

		if (FAILED(CGameInstance::GetInstance()->Remove_Layer_Object(temp, _sel))) {
			AfxMessageBox(L"삭제 실패!!");

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

	CFileDialog	Dlg(FALSE,	// true인 경우 열기 모드, false 인 경우 다른 이름으로 저장 모드
		L"dat", // default 파일 확장명, 저장 시 확장자명을 명시해주지 않으면 현재 기입한 확장자명을 사용하게 설정됨
		L"*.dat", // 대화상자에 표시될 최초 파일명
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, // OFN_HIDEREADONLY(읽기전용 체크박스 숨김), OFN_OVERWRITEPROMPT(중복 파일 저장 시 경고메시지 띄우기 옵션)
		L"Data File(*.dat)|*.dat||",	// 대화 상자에 표시될 파일 형식, 콤보박스에 출력될 문자열 | 실제 사용할 필터링 문자열 ||
		this); // 부모 윈도우 주소

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
		AfxMessageBox(L"저장 성공!");

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

	CFileDialog	Dlg(TRUE,	// true인 경우 열기 모드, false 인 경우 다른 이름으로 저장 모드
		L"dat", // default 파일 확장명, 저장 시 확장자명을 명시해주지 않으면 현재 기입한 확장자명을 사용하게 설정됨
		L"*.dat", // 대화상자에 표시될 최초 파일명
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, // OFN_HIDEREADONLY(읽기전용 체크박스 숨김), OFN_OVERWRITEPROMPT(중복 파일 저장 시 경고메시지 띄우기 옵션)
		L"Data File(*.dat)|*.dat||",	// 대화 상자에 표시될 파일 형식, 콤보박스에 출력될 문자열 | 실제 사용할 필터링 문자열 ||
		this); // 부모 윈도우 주소

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
