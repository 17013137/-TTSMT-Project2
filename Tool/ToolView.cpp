// ToolView.cpp : CToolView 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "Tool.h"
#endif
#include "ToolDoc.h"
#include "ToolView.h"
#include "MainFrm.h"

#include "GameInstance.h"
#include "Camera_Default.h"
#include "Input_Device.h"
#include "KeyMgr.h"

#include "Tool_Object.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

HWND	g_hWnd;


// CToolView

IMPLEMENT_DYNCREATE(CToolView, CView)

BEGIN_MESSAGE_MAP(CToolView, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_DESTROY()
END_MESSAGE_MAP()

// CToolView 생성/소멸

CToolView::CToolView()
{
	// TODO: 여기에 생성 코드를 추가합니다.
	m_pGameInstance = CGameInstance::GetInstance();
	Safe_AddRef(m_pGameInstance);
}

CToolView::~CToolView()
{
}

BOOL CToolView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

void CToolView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	CMainFrame*		pMainFrm = (CMainFrame*)AfxGetMainWnd();

	RECT	rcWnd{};
	
	pMainFrm->GetWindowRect(&rcWnd);
	SetRect(&rcWnd, 0, 0, rcWnd.right - rcWnd.left, rcWnd.bottom - rcWnd.top);
	
	RECT	rcMainView{};
	GetClientRect(&rcMainView);
	
	float	fRowFrm = float(rcWnd.right - rcMainView.right);
	float	fColFrm = float(rcWnd.bottom - rcMainView.bottom);
	
	pMainFrm->SetWindowPos(nullptr, 300, 100, int(WINCX + fRowFrm), int(WINCY + fColFrm), SWP_NOZORDER);
	
	g_hWnd = m_hWnd;
	
	CGraphic_Device::GRAPHICDESC		GraphicDesc;
	ZeroMemory(&GraphicDesc, sizeof(CGraphic_Device::GRAPHICDESC));
	
	GraphicDesc.hWnd = g_hWnd;
	GraphicDesc.iWinCX = WINCX;
	GraphicDesc.iWinCY = WINCY;
	
	
	if (FAILED(m_pGameInstance->Initialize_Engine(AfxGetInstanceHandle(), STAGE_END, GraphicDesc, &m_pGraphic_Device)))
		AfxMessageBox(L"Device Create Failed");
	
	if (FAILED(Ready_SetUp()))
		AfxMessageBox(L"Ready_SetUp Failed");

	m_Scene = CScene::Create(m_pGraphic_Device);
	
	if (FAILED(m_pGameInstance->Open_Level(STAGE_SCENE, m_Scene)))
		AfxMessageBox(L"Failed to Create Scene");

	
}

// CToolView 그리기
void CToolView::OnDraw(CDC* /*pDC*/)
{
	CToolDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
}


// CToolView 인쇄

BOOL CToolView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CToolView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{

	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CToolView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CToolView 진단

#ifdef _DEBUG
void CToolView::AssertValid() const
{
	CView::AssertValid();
}

void CToolView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

void CToolView::Tick(float fTimeDelta)
{
	if (nullptr == m_pGameInstance)
		return;

	m_pGameInstance->Tick_Engine(fTimeDelta);
}

HRESULT CToolView::Render()
{
	if (nullptr == m_pGameInstance)
		return E_FAIL;

	m_pGameInstance->Render_Begin();

	if (FAILED(m_pRenderer->Render_GameObjects()))
		return E_FAIL;

	if (FAILED(m_pGameInstance->Render_Engine()))
		return E_FAIL;

	m_pGameInstance->Render_End();

	return S_OK;
}

HRESULT CToolView::Ready_SetUp()
{
	if (FAILED(SetUp_DefaultRenderState()))  //카메라 셋팅
		return E_FAIL;

	if (FAILED(Ready_Prototype_Component()))  //포로토타입 컴포넌트
		return E_FAIL;
	
	if (FAILED(Ready_Prototype_GameObject()))  //게임오브젝트 컴포넌트
		return E_FAIL;

	return S_OK;
}

HRESULT CToolView::Ready_Prototype_GameObject()
{
	/* For.Prototype_GameObject_Monster */
	if (FAILED(m_pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Camera_Default"),
		CCamera_Default::Create(m_pGraphic_Device))))
		return E_FAIL;

	if (FAILED(m_pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Terrain"), CTerrain::Create(m_pGraphic_Device))))
		return E_FAIL;

	if (FAILED(m_pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Cube"), CCube::Create(m_pGraphic_Device))))
		return E_FAIL;

	if (FAILED(m_pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Tile"), CTile::Create(m_pGraphic_Device))))
		return E_FAIL;

	if (FAILED(m_pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Door"), CDoor::Create(m_pGraphic_Device))))
		return E_FAIL;

	if (FAILED(m_pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Drawer"), CDrawer::Create(m_pGraphic_Device))))
		return E_FAIL;

	if (FAILED(m_pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Cone"), CCone::Create(m_pGraphic_Device))))
		return E_FAIL;

	if (FAILED(m_pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Barricade2"), CBarricade2::Create(m_pGraphic_Device))))
		return E_FAIL;

	if (FAILED(m_pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Wall"), CWall::Create(m_pGraphic_Device))))
		return E_FAIL;

	if (FAILED(m_pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Window"), CWindow::Create(m_pGraphic_Device))))
		return E_FAIL;

	if (FAILED(m_pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Tree"), CTree::Create(m_pGraphic_Device))))
		return E_FAIL;


	if (FAILED(m_pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_NormalZombie"), CNormalZombie::Create(m_pGraphic_Device))))
		return E_FAIL;

	if (FAILED(m_pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_ZombieSpitter"), CZombieSpitter::Create(m_pGraphic_Device))))
		return E_FAIL;

	if (FAILED(m_pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_BlueSkeleton"), CBlueSkeleton::Create(m_pGraphic_Device))))
		return E_FAIL;
	if (FAILED(m_pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Fanatic"), CFanatic::Create(m_pGraphic_Device))))
		return E_FAIL;
	if (FAILED(m_pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_GrandfaSkeleton"), CGrandfaSkeleton::Create(m_pGraphic_Device))))
		return E_FAIL;

	if (FAILED(m_pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Wither_Skeleton"), CWither_Skeleton::Create(m_pGraphic_Device))))
		return E_FAIL;




	if (FAILED(m_pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_XRect"), CXRect::Create(m_pGraphic_Device))))
		return E_FAIL;

	if (FAILED(m_pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Wood"), CWood::Create(m_pGraphic_Device))))
		return E_FAIL;

	if (FAILED(m_pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_GateCube"), CGateCube::Create(m_pGraphic_Device))))
		return E_FAIL;

	if (FAILED(m_pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_PurpleGate"), CPurpleGate::Create(m_pGraphic_Device))))
		return E_FAIL;

	if (FAILED(m_pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_SoulFire"), CSoulFire::Create(m_pGraphic_Device))))
		return E_FAIL;

	return S_OK;
}

HRESULT CToolView::Ready_Prototype_Component()
{
	if (FAILED(m_pGameInstance->Add_Component_Prototype(STAGE_STATIC, TEXT("Prototype_Component_Renderer"), m_pRenderer = CRenderer::Create(m_pGraphic_Device))))
		return E_FAIL;
	if (FAILED(m_pGameInstance->Add_Component_Prototype(STAGE_STATIC, TEXT("Prototype_Component_Transform"), CTransform::Create(m_pGraphic_Device))))
		return E_FAIL;
	if (FAILED(m_pGameInstance->Add_Component_Prototype(STAGE_STATIC, TEXT("Prototype_Component_SubTransform"), CSubTransform::Create(m_pGraphic_Device))))
		return E_FAIL;

	Safe_AddRef(m_pRenderer);

	/* For.Prototype_Component_Texture_Default */
	if (FAILED(m_pGameInstance->Add_Component_Prototype(STAGE_SCENE, TEXT("Prototype_Component_Texture_Terrain"), CTexture::Create(m_pGraphic_Device, CTexture::TYPE_DEFAULT, TEXT("./Bin/Resources/ToolTextures/CartoonTile/%d.png"), 71))))
		return E_FAIL;
	if (FAILED(m_pGameInstance->Add_Component_Prototype(STAGE_SCENE, TEXT("Prototype_Component_Texture_Cube"),
		CTexture::Create(m_pGraphic_Device, CTexture::TYPE_CUBE, TEXT("./Bin/Resources/ToolTextures/Cube/%d.dds"), 41))))
		return E_FAIL;
	if (FAILED(m_pGameInstance->Add_Component_Prototype(STAGE_SCENE, TEXT("Prototype_Component_Texture_Blend"), CTexture::Create(m_pGraphic_Device, CTexture::TYPE_DEFAULT, TEXT("./Bin/Resources/ToolTextures/BlendObject/%d.png"), 47))))
		return E_FAIL;

	if (FAILED(m_pGameInstance->Add_Component_Prototype(STAGE_SCENE, TEXT("Prototype_Component_Texture_Gate"), CTexture::Create(m_pGraphic_Device, CTexture::TYPE_DEFAULT, TEXT("./Bin/Resources/ToolTextures/Gate/Type1/Purple/purple_(%d).png"), 32))))
		return E_FAIL;

	if (FAILED(m_pGameInstance->Add_Component_Prototype(STAGE_SCENE, TEXT("Prototype_Component_Texture_SoulFire"), CTexture::Create(m_pGraphic_Device, CTexture::TYPE_DEFAULT, TEXT("./Bin/Resources/ToolTextures/Effect/SoulFire/soul_fire(%d).png"), 32))))
		return E_FAIL;
	if (FAILED(m_pGameInstance->Add_Component_Prototype(STAGE_SCENE, TEXT("Prototype_Component_Texture_Fire"), CTexture::Create(m_pGraphic_Device, CTexture::TYPE_DEFAULT, TEXT("./Bin/Resources/ToolTextures/Effect/Fire/fire_%d.png"), 32))))
		return E_FAIL;

	/* For.Prototype_Component_VIBuffer_오브젝트 ㅇㅇ */
	if (FAILED(m_pGameInstance->Add_Component_Prototype(STAGE_SCENE, TEXT("Prototype_Component_VIBuffer_Terrain"), CVIBuffer_Terrain::Create(m_pGraphic_Device, 80, 80))))
		return E_FAIL;
	if (FAILED(m_pGameInstance->Add_Component_Prototype(STAGE_SCENE, TEXT("Prototype_Component_VIBuffer_Rect"), CVIBuffer_Rect::Create(m_pGraphic_Device))))
		return E_FAIL;
	if (FAILED(m_pGameInstance->Add_Component_Prototype(STAGE_SCENE, TEXT("Prototype_Component_VIBuffer_Cube"), CVIBuffer_Cube::Create(m_pGraphic_Device))))
		return E_FAIL;
	if (FAILED(m_pGameInstance->Add_Component_Prototype(STAGE_SCENE, TEXT("Prototype_Component_VIBuffer_Tile"), CVIBuffer_Tile::Create(m_pGraphic_Device))))
		return E_FAIL;
	if (FAILED(m_pGameInstance->Add_Component_Prototype(STAGE_SCENE, TEXT("Prototype_Component_VIBuffer_Door"), CVIBuffer_Door::Create(m_pGraphic_Device))))
		return E_FAIL;
	if (FAILED(m_pGameInstance->Add_Component_Prototype(STAGE_SCENE, TEXT("Prototype_Component_VIBuffer_Window"), CVIBuffer_Window::Create(m_pGraphic_Device))))
		return E_FAIL;
	if (FAILED(m_pGameInstance->Add_Component_Prototype(STAGE_SCENE, TEXT("Prototype_Component_VIBuffer_Wall"), CVIBuffer_Wall::Create(m_pGraphic_Device))))
		return E_FAIL;
	if (FAILED(m_pGameInstance->Add_Component_Prototype(STAGE_SCENE, TEXT("Prototype_Component_VIBuffer_Drawer"), CVIBuffer_Drawer::Create(m_pGraphic_Device))))
		return E_FAIL;
	if (FAILED(m_pGameInstance->Add_Component_Prototype(STAGE_SCENE, TEXT("Prototype_Component_VIBuffer_Cone"), CVIBuffer_Cone::Create(m_pGraphic_Device))))
		return E_FAIL;
	if (FAILED(m_pGameInstance->Add_Component_Prototype(STAGE_SCENE, TEXT("Prototype_Component_VIBuffer_Tree"), CVIBuffer_Tree::Create(m_pGraphic_Device))))
		return E_FAIL;
	if (FAILED(m_pGameInstance->Add_Component_Prototype(STAGE_SCENE, TEXT("Prototype_Component_VIBuffer_Barricade2"), CVIBuffer_Barricade2::Create(m_pGraphic_Device))))
		return E_FAIL;
	if (FAILED(m_pGameInstance->Add_Component_Prototype(STAGE_SCENE, TEXT("Prototype_Component_VIBuffer_XRect"), CVIBuffer_XRect::Create(m_pGraphic_Device))))
		return E_FAIL;



	/* For.Prototype_Component_Transform */



	return S_OK;
}

HRESULT CToolView::SetUp_DefaultRenderState()
{
	if (nullptr == m_pGraphic_Device)
		return E_FAIL;

	/* 현재 내 게임에 필요한 기본 렌더링 상태를 설정한다. */
	m_pGraphic_Device->SetRenderState(D3DRS_LIGHTING, FALSE);
	//m_pGraphic_Device->SetRenderState(D3DRS_SHADEMODE, D3DSHADE_FLAT);
	/* 현재 내 게임에 필요한 기본 렌더링 상태를 설정한다. */
	m_pGraphic_Device->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	m_pGraphic_Device->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);

	return S_OK;
}

HRESULT CToolView::Ready_Prototype_Terrain(int _X, int _Z)
{
	m_pGameInstance->Remove_Prototype_Component(STAGE_SCENE, TEXT("Prototype_Component_VIBuffer_Terrain"));

	if (FAILED(m_pGameInstance->Add_Component_Prototype(STAGE_SCENE, TEXT("Prototype_Component_VIBuffer_Terrain"), CVIBuffer_Terrain::Create(m_pGraphic_Device, _X, _Z))))
		return E_FAIL;

	m_pGameInstance->Clear_Layer_list(STAGE_SCENE, TEXT("Layer_BackGround"));
	m_pGameInstance->Add_GameObjectToLayer(STAGE_SCENE, TEXT("Layer_BackGround"), TEXT("Prototype_GameObject_Terrain"));

	return S_OK;
}

CToolDoc* CToolView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CToolDoc)));
	return (CToolDoc*)m_pDocument;
}
#endif //_DEBUG


// CToolView 메시지 처리기


void CToolView::OnDestroy()
{
	CView::OnDestroy();

	CKeyMgr::Get_Instance()->Destroy_Instance();
	Safe_Release(m_pRenderer);
	Safe_Release(m_pGraphic_Device);
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	Safe_Release(m_pGameInstance);
	Safe_Release(m_Scene);
	CGameInstance::Release_Engine();
}
