#include "..\Public\BlendObject.h"

#include "GameInstance.h"
#include "Transform.h"



CBlendObject::CBlendObject(LPDIRECT3DDEVICE9 pGraphic_Device)
	: CGameObject(pGraphic_Device)
{
	
}

CBlendObject::CBlendObject(const CBlendObject & rhs)
	: CGameObject(rhs.m_pGraphic_Device)
{

}

HRESULT CBlendObject::NativeConstruct_Prototype()
{
	return S_OK;
}

HRESULT CBlendObject::NativeConstruct(void * pArg)
{
	return S_OK;
}

void CBlendObject::Tick(_float fTimeDelta)
{
	CGameObject::Tick(fTimeDelta);
}

void CBlendObject::LateTick(_float fTimeDelta)
{
	CGameObject::LateTick(fTimeDelta);

}

HRESULT CBlendObject::Render()
{
	return S_OK;
}

void CBlendObject::Compute_CamDistance(CTransform * pTransform)
{
	_float4x4			ViewMatrix;

	m_pGraphic_Device->GetTransform(D3DTS_VIEW, &ViewMatrix);
	D3DXMatrixInverse(&ViewMatrix, nullptr, &ViewMatrix);

	_float3		vDir = *(_float3*)&ViewMatrix.m[3][0] - pTransform->Get_State(CTransform::STATE_POSITION);

	m_fCamDistance = D3DXVec3Length(&vDir);
}

void CBlendObject::Free()
{
	__super::Free();


}
