// ToolView.cpp : CToolView Ŭ������ ����
//

#include "stdafx.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
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
	// ǥ�� �μ� ����Դϴ�.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_DESTROY()
END_MESSAGE_MAP()

// CToolView ����/�Ҹ�

CToolView::CToolView()
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.
	m_pGameInstance = CGameInstance::GetInstance();
	Safe_AddRef(m_pGameInstance);
}

CToolView::~CToolView()
{
}

BOOL CToolView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

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

// CToolView �׸���
void CToolView::OnDraw(CDC* /*pDC*/)
{
	CToolDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: ���⿡ ���� �����Ϳ� ���� �׸��� �ڵ带 �߰��մϴ�.
}


// CToolView �μ�

BOOL CToolView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// �⺻���� �غ�
	return DoPreparePrinting(pInfo);
}

void CToolView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{

	// TODO: �μ��ϱ� ���� �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
}

void CToolView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ� �� ���� �۾��� �߰��մϴ�.
}


// CToolView ����

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
	if (FAILED(SetUp_DefaultRenderState()))  //ī�޶� ����
		return E_FAIL;

	if (FAILED(Ready_Prototype_Component()))  //������Ÿ�� ������Ʈ
		return E_FAIL;
	
	if (FAILED(Ready_Prototype_GameObject()))  //���ӿ�����Ʈ ������Ʈ
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

	/* For.Prototype_Component_VIBuffer_������Ʈ ���� */
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

	/* ���� �� ���ӿ� �ʿ��� �⺻ ������ ���¸� �����Ѵ�. */
	m_pGraphic_Device->SetRenderState(D3DRS_LIGHTING, FALSE);
	//m_pGraphic_Device->SetRenderState(D3DRS_SHADEMODE, D3DSHADE_FLAT);
	/* ���� �� ���ӿ� �ʿ��� �⺻ ������ ���¸� �����Ѵ�. */
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

CToolDoc* CToolView::GetDocument() const // ����׵��� ���� ������ �ζ������� �����˴ϴ�.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CToolDoc)));
	return (CToolDoc*)m_pDocument;
}
#endif //_DEBUG


// CToolView �޽��� ó����


void CToolView::OnDestroy()
{
	CView::OnDestroy();

	CKeyMgr::Get_Instance()->Destroy_Instance();
	Safe_Release(m_pRenderer);
	Safe_Release(m_pGraphic_Device);
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
	Safe_Release(m_pGameInstance);
	Safe_Release(m_Scene);
	CGameInstance::Release_Engine();
}
