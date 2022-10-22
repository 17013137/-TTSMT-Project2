#pragma once

#include "Base.h"

BEGIN(Engine)

class CPicking final : public CBase
{
	DECLARE_SINGLETON(CPicking)
public:
	CPicking();
	virtual ~CPicking() = default;

public:
	HRESULT NativeConstruct(HWND hWnd, LPDIRECT3DDEVICE9 pGraphic_Device);

	/* 매 프레임마다 호출을 하여, 월드 스페이스 상의 m_vRay, m_vRayPos 구해놓는다. */
	void Update_ToTransform();
	void Transform_ToLocalSpace(_float4x4* pWorldMatrixInverse);

	_bool Picking_OnLocalSpace(_float3* pLocalPoints, _float3* pPickingPointOut);

private:
	HWND				m_hWnd;
	LPDIRECT3DDEVICE9	m_pGraphic_Device = nullptr;
	_float3				m_vWorldRay, m_vWorldRayPos;
	_float3				m_vLocalRay, m_vLocalRayPos;



public:
	virtual void Free() override;
};

END