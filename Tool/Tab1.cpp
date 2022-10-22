// Tab1.cpp : 구현 파일입니다.
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

// CTab1 대화 상자입니다.

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


// CTab1 메시지 처리기입니다.


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

	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	CString tpath = TEXT("./Bin/Resources/ToolTextures/CartoonTile/*.*");

	// 검색 클래스
	CFileFind finder;

	BOOL bWorking = finder.FindFile(tpath); //

	CString fileName;
	CString DirName;

	while (bWorking)
	{
		//다음 파일 or 폴더 가 존재하면다면 TRUE 반환
		bWorking = finder.FindNextFile();

		// folder 일 경우는 continue
		if (finder.IsDirectory() || finder.IsDots())
			continue;

		//파일의 이름
		CString _fileName = finder.GetFileName();

		//문자 추출
		fileName = finder.GetFileTitle();
		int _size = fileName.GetLength();

		//읽어온 파일 이름을 리스트박스와 map에 넣음
		m_Tile_Listbox.AddString(fileName);
	}


	//--블렌더오브젝트

	tpath = TEXT("./BlendObj/*.*");

	bWorking = finder.FindFile(tpath); //

	while (bWorking)
	{
		//다음 파일 or 폴더 가 존재하면다면 TRUE 반환
		bWorking = finder.FindNextFile();

		// folder 일 경우는 continue
		if (finder.IsDirectory() || finder.IsDots())
			continue;

		//파일의 이름
		CString _fileName = finder.GetFileName();

		//문자 추출
		fileName = finder.GetFileTitle();
		int _size = fileName.GetLength();

		//읽어온 파일 이름을 리스트박스와 map에 넣음
		m_Blend_ListBox.AddString(fileName);
	}


	tpath = TEXT("./Bin/Resources/ToolTextures/BlendObject/*.*");

	// 검색 클래스

	bWorking = finder.FindFile(tpath); //

	while (bWorking)
	{
		//다음 파일 or 폴더 가 존재하면다면 TRUE 반환
		bWorking = finder.FindNextFile();

		// folder 일 경우는 continue
		if (finder.IsDirectory() || finder.IsDots())
			continue;

		//파일의 이름
		CString _fileName = finder.GetFileName();

		//문자 추출
		fileName = finder.GetFileTitle();
		int _size = fileName.GetLength();

		//읽어온 파일 이름을 리스트박스와 map에 넣음
		m_Blend_Texture_ListBox.AddString(fileName);
	}

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CTab1::Tile_ListBox()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CTab1::OnLbnSelchangeList2() // sel_chgange;
{
	// TODO: Add your control notification handler code here
}


void CTab1::Tile_Delete_Button()
{
	UpdateData(TRUE);

	if (m_Scene_ListBox.GetCurSel() >= 0) {
		//원래 했던거 삭제모드
		CMainFrame*      pMain = dynamic_cast<CMainFrame*>(AfxGetMainWnd());
		CToolView*      pToolView = dynamic_cast<CToolView*>(pMain->m_MainSplitter.GetPane(0, 1));

		int _sel = m_Scene_ListBox.GetCurSel();


		pToolView->v_TileList.erase(pToolView->v_TileList.begin() + _sel);

		CLayer* temp = CGameInstance::GetInstance()->Get_GameObejct_Layer(STAGE_SCENE, L"TILE");

		if (FAILED(CGameInstance::GetInstance()->Remove_Layer_Object(temp, _sel))) {
			AfxMessageBox(L"삭제 실패!!");

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


void CTab1::Load_Save_Button()
{

	vector<OBJDATA*> _load;
	CMainFrame*      pMain = dynamic_cast<CMainFrame*>(AfxGetMainWnd());
	CToolView*      pToolView = dynamic_cast<CToolView*>(pMain->m_MainSplitter.GetPane(0, 1));


	if (!pToolView->v_TileList.empty()) {
		pToolView->v_TileList.clear();
		pToolView->v_TileList.shrink_to_fit();
	}

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

			//툴안에 데이터갱신

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

			CString itochar;																//숫자 문자변환
			itochar.Format(_T("%d"), pObjData->ObjID);
			m_Scene_ListBox.AddString(itochar);
		}
		CloseHandle(hFile);
	}
	
}