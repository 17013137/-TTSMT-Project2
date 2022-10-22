#pragma once
#include "Tool_Define.h"
#include "Level.h"

BEGIN(Engine)

class CGameInstance;
class CGameObject;
END
class CTabDlg;
class CToolView;
class CScene final : public CLevel
{
private:
	explicit CScene(LPDIRECT3DDEVICE9 pGraphic_Device);
	virtual ~CScene() = default;

public:
	virtual HRESULT NativeConstruct() override;
	virtual void Tick(_float fTimeDelta) override;
	virtual HRESULT Render() override;
	
public:
	void TabManaged(_float fTimeDelta);
	void Tab1(_float fTimeDelta);
	void Tab2(_float fTimeDelta);
	void Tab3(_float fTimeDelta);
	void Tab4(_float fTimeDelta);

public:
	HRESULT Ready_Layer_Camera(const _tchar* pLayerTag);
	HRESULT Ready_Layer_BackGround(const _tchar* pLayerTag);
	
private:
	CTabDlg* m_tabDlg;
	CToolView* m_toolView;

	CGameInstance* m_Gameinstance = nullptr;
	_float _speed = 2.f;
public:
	static CScene* Create(LPDIRECT3DDEVICE9 pGraphic_Device);
	virtual void Free() override;
};

