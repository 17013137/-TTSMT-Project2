
// ToolView.h : CToolView Ŭ������ �������̽�
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
protected: // serialization������ ��������ϴ�.
	CToolView();
	DECLARE_DYNCREATE(CToolView)

// Ư���Դϴ�.
public:
	CToolDoc* GetDocument() const;

// �۾��Դϴ�.
public:

// �������Դϴ�.
public:
	virtual void OnDraw(CDC* pDC);  // �� �並 �׸��� ���� �����ǵǾ����ϴ�.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// �����Դϴ�.
public:
	virtual ~CToolView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

//3D���� ��
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
// ������ �޽��� �� �Լ�
protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();
	afx_msg void OnDestroy();
};

#ifndef _DEBUG  // ToolView.cpp�� ����� ����
inline CToolDoc* CToolView::GetDocument() const
   { return reinterpret_cast<CToolDoc*>(m_pDocument); }
#endif

