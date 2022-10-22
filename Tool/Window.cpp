#include "stdafx.h"
#include "Window.h"
#include "GameInstance.h"

CWindow::CWindow(LPDIRECT3DDEVICE9 pGraphic_Device)
	:CGameObject(pGraphic_Device)
{
}

CWindow::CWindow(const CWindow & rhs)
	:CGameObject(rhs)
{
}

HRESULT CWindow::NativeConstruct_Prototype()
{
	if (FAILED(__super::NativeConstruct_Prototype()))
		return E_FAIL;

	return S_OK;
}

HRESULT CWindow::NativeConstruct(void * pArg)
{
	if (FAILED(__super::NativeConstruct(pArg)))
		return E_FAIL;

	if (FAILED(SetUp_Components()))
		return E_FAIL;

	_float4x4 temp;
	memcpy(temp, pArg, sizeof(_float4x4));
	m_pTransformCom->Set_State(CTransform::STATE_RIGHT, _float3(temp.m[0][0], temp.m[0][1], temp.m[0][2]));
	m_pTransformCom->Set_State(CTransform::STATE_UP, _float3(temp.m[1][0], temp.m[1][1], temp.m[1][2]));
	m_pTransformCom->Set_State(CTransform::STATE_LOOK, _float3(temp.m[2][0], temp.m[2][1], temp.m[2][2]));
	m_pTransformCom->Set_State(CTransform::STATE_POSITION, _float3(temp.m[3][0], temp.m[3][1], temp.m[3][2]));

	
	return S_OK;
}

void CWindow::Tick(_float fTimeDelta)
{
	__super::Tick(fTimeDelta);
}

void CWindow::LateTick(_float fTimeDelta)
{
	__super::LateTick(fTimeDelta);

	m_pRendererCom->Add_RenderGroup(CRenderer::GROUP_NONBLEND, this);
}

HRESULT CWindow::Render()
{
	if (FAILED(__super::Render()))
		return E_FAIL;

	if (FAILED(m_pTransformCom->Bind_OnGraphicDevice()))
		return E_FAIL;

	
	m_pVIBufferCom->Render();

	return S_OK;
}

HRESULT CWindow::SetUp_Components()
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

	if (FAILED(__super::SetUp_Components(TEXT("Com_VIBuffer"), STAGE_SCENE, TEXT("Prototype_Component_VIBuffer_Window"), (CComponent**)&m_pVIBufferCom)))
		return E_FAIL;

	return S_OK;
}

_bool CWindow::Picking(_float3 * _pickpos)
{
	_float3	vOut;
	if (true == m_pVIBufferCom->Picking(m_pTransformCom, &vOut)) {
		D3DXVec3TransformCoord(&vOut, &vOut, &m_pTransformCom->Get_WorldMatrix());
		*_pickpos = vOut;
		return true;
	}

	return false;
}

CWindow * CWindow::Create(LPDIRECT3DDEVICE9 pGraphic_Device)
{
	CWindow*	pInstance = new CWindow(pGraphic_Device);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created CWindow"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CWindow::Clone(void * pArg)
{
	CWindow*	pInstance = new CWindow(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CWindow"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CWindow::Free()
{
	__super::Free();

	Safe_Release(m_pTransformCom);
	Safe_Release(m_pVIBufferCom);
	Safe_Release(m_pRendererCom);
}