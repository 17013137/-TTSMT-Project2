
// ToolView.h : CToolView 클래스의 인터페이스
//

#pragma once

#include "Base.h"
#include "Tool_Define.h"
#include "Scene.h"

BEGIN(Engine)
class CRenderer;
class CGameInstance;
END

class CToolDoc;
class CToolView : public CView
{
protected: // serialization에서만 만들어집니다.
	CToolView();
	DECLARE_DYNCREATE(CToolView)

// 특성입니다.
public:
	CToolDoc* GetDocument() const;

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 구현입니다.
public:
	virtual ~CToolView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

//3D공간 셋
public:
	void Tick(float fTimeDelta);
	HRESULT Render();

private:
	HRESULT Ready_SetUp();

private:
	HRESULT Ready_Prototype_GameObject();
	HRESULT Ready_Prototype_Component();
	HRESULT SetUp_DefaultRenderState();

public:
	HRESULT Ready_Prototype_Terrain(int _X, int _Z);
public:
	CGameInstance*		m_pGameInstance = nullptr;
	LPDIRECT3DDEVICE9	m_pGraphic_Device = nullptr;
	CRenderer*			m_pRenderer = nullptr;
	CScene* m_Scene = nullptr;

public:
	vector<TOOLDATA*> v_ObjList;
	vector<CUBEDATA*> v_CubeList;
	vector<TILEDATA*> v_TileList;
	vector<TILEDATA*> v_BlendList;
// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();
	afx_msg void OnDestroy();
};

#ifndef _DEBUG  // ToolView.cpp의 디버그 버전
inline CToolDoc* CToolView::GetDocument() const
   { return reinterpret_cast<CToolDoc*>(m_pDocument); }
#endif

