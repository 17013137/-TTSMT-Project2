#include "stdafx.h"
#include "Cube.h"
#include "GameInstance.h"

CCube::CCube(LPDIRECT3DDEVICE9 pGraphic_Device)
	: CGameObject(pGraphic_Device)
{
}

CCube::CCube(const CCube & rhs)
	: CGameObject(rhs)
{
}

HRESULT CCube::NativeConstruct_Prototype()
{
	if (FAILED(__super::NativeConstruct_Prototype()))	
		return E_FAIL;

	return S_OK;
}

HRESULT CCube::NativeConstruct(void * pArg)
{
	if (FAILED(__super::NativeConstruct(pArg)))
		return E_FAIL;

	if (FAILED(SetUp_Components()))
		return E_FAIL;
	_float4x4 temp;
	memcpy(temp, pArg, sizeof(_float4x4));
	isColison = (_uint)temp.m[0][3];
	ImgNum = (_uint)temp.m[1][3];
	temp.m[0][3] = 0.f;
	temp.m[1][3] = 0.f;
	m_pTransformCom->Set_State(CTransform::STATE_RIGHT, _float3(temp.m[0][0], temp.m[0][1], temp.m[0][2]));
	m_pTransformCom->Set_State(CTransform::STATE_UP, _float3(temp.m[1][0], temp.m[1][1], temp.m[1][2]));
	m_pTransformCom->Set_State(CTransform::STATE_LOOK, _float3(temp.m[2][0], temp.m[2][1], temp.m[2][2]));
	m_pTransformCom->Set_State(CTransform::STATE_POSITION, _float3(temp.m[3][0], temp.m[3][1], temp.m[3][2]));

	return S_OK;
}

void CCube::Tick(_float fTimeDelta)
{
	__super::Tick(fTimeDelta);


}

void CCube::LateTick(_float fTimeDelta)
{
	__super::LateTick(fTimeDelta);
	

	if (nullptr == m_pGraphic_Device)
		return;

	m_pRendererCom->Add_RenderGroup(CRenderer::GROUP_NONBLEND, this);
}

HRESULT CCube::Render()
{
	if (FAILED(__super::Render()))
		return E_FAIL;	

	if (FAILED(m_pTextureCom->Bind_OnGraphicDevice(ImgNum)))
		return E_FAIL;

	if (FAILED(m_pTransformCom->Bind_OnGraphicDevice()))
		return E_FAIL;

	m_pVIBufferCom->Render();
	


	return S_OK;
}

_bool CCube::Picking(_float3 * _pickpos)
{
	_float3	vOut;
	if (true == m_pVIBufferCom->Picking(m_pTransformCom, &vOut)) {
		D3DXVec3TransformCoord(&vOut, &vOut, &m_pTransformCom->Get_WorldMatrix());
		*_pickpos = vOut;
		return true;
	}

	return false;
}

_bool CCube::CubePicking(_float3 * _pickpos)
{
	_float3	vOut;
	if (true == m_pVIBufferCom->Cube_Picking(m_pTransformCom, &vOut)) {
		D3DXVec3TransformCoord(&vOut, &vOut, &m_pTransformCom->Get_WorldMatrix());
		*_pickpos = vOut;
		return true;
	}

	return false;
}



HRESULT CCube::SetUp_Components()
{
	/* For.Com_Transform */
	CTransform::TRANSFORMDESC		TransformDesc;
	ZeroMemory(&TransformDesc, sizeof(CTransform::TRANSFORMDESC));

	TransformDesc.fSpeedPerSec = 0.3f;
	TransformDesc.fRotationPerSec = D3DXToRadian(90.0f);
	TransformDesc.fScalePerSec = 1.f;

	if (FAILED(__super::SetUp_Components(TEXT("Com_Transform"), STAGE_STATIC, TEXT("Prototype_Component_Transform"), (CComponent**)&m_pTransformCom, &TransformDesc)))
		return E_FAIL;

	/* For.Com_Renderer */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Renderer"), STAGE_STATIC, TEXT("Prototype_Component_Renderer"), (CComponent**)&m_pRendererCom)))
		return E_FAIL;

	/* For.Com_VIBuffer */
	if (FAILED(__super::SetUp_Components(TEXT("Com_VIBuffer"), STAGE_SCENE, TEXT("Prototype_Component_VIBuffer_Cube"), (CComponent**)&m_pVIBufferCom)))
		return E_FAIL;

	/* For.Com_Texture */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Texture"), STAGE_SCENE, TEXT("Prototype_Component_Texture_Cube"), (CComponent**)&m_pTextureCom)))
		return E_FAIL;

	return S_OK;
}

CCube * CCube::Create(LPDIRECT3DDEVICE9 pGraphic_Device)
{
	CCube*	pInstance = new CCube(pGraphic_Device);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created CCube"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CCube::Clone(void * pArg)
{
	CCube*	pInstance = new CCube(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CCube"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CCube::Free()
{
	__super::Free();

	Safe_Release(m_pTransformCom);
	Safe_Release(m_pTextureCom);
	Safe_Release(m_pVIBufferCom);
	Safe_Release(m_pRendererCom);

}
