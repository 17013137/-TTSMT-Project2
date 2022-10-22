#pragma once

#include "GameObject.h"
#include "Tool_Define.h"

// input과 다른 현재 
class CTerrain;
class CMouse : public CBase {

	DECLARE_SINGLETON(CMouse)

private:
	explicit CMouse();
	explicit CMouse(LPDIRECT3DDEVICE9 _pGraphic_Device);
	virtual ~CMouse() = default;

public:
	static CMouse* Create(LPDIRECT3DDEVICE9 _pGraphic_Device);

public:
	void Tick();
	const D3DXVECTOR3&	GetLayVector(void) const { return m_RayVector; }
	const POINT& GetMousePos(void) const { return m_ptMouse; }
	_float3 Get_PeekPos(_float _dist);
	_float Pick_Dist(CTerrain* _Obj, const _tchar* pBuffTag, const _tchar* pTransComTag);
	_bool Picking(CGameObject* _Obj, const _tchar* pBuffTag, const _tchar* pTransComTag);
	_float Pick(D3DXVECTOR3& _p1, D3DXVECTOR3& _p2, D3DXVECTOR3& _p3, D3DXMATRIX _worldmat);

public:
	virtual void Free() override;

private:
	LPDIRECT3DDEVICE9	m_pGraphic_Device;
	D3DXVECTOR3			m_RayPos;
	D3DXVECTOR3			m_RayVector;
	POINT				m_ptMouse;
};
