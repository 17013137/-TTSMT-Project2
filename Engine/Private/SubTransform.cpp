#include "..\Public\SubTransfrom.h"


CSubTransform::CSubTransform(LPDIRECT3DDEVICE9 pGraphic_Device)
	: CComponent(pGraphic_Device)
{
}

CSubTransform::CSubTransform(const CSubTransform & rhs)
	: CComponent(rhs)
	, m_LocalMatrix(rhs.m_LocalMatrix), m_WorldMatrix(rhs.m_WorldMatrix)
{
}

_float3 CSubTransform::Get_Scale()
{
	_float3		vRight = Get_State(CSubTransform::STATE_RIGHT);
	_float3		vUp = Get_State(CSubTransform::STATE_UP);
	_float3		vLook = Get_State(CSubTransform::STATE_LOOK);

	return _float3(D3DXVec3Length(&vRight), D3DXVec3Length(&vUp), D3DXVec3Length(&vLook));
}

HRESULT CSubTransform::NativeConstruct_Prototype()
{
	D3DXMatrixIdentity(&m_LocalMatrix);
	D3DXMatrixIdentity(&m_WorldMatrix);

	return S_OK;
}

HRESULT CSubTransform::NativeConstruct(void * pArg)
{
	if (nullptr != pArg)
		memcpy(&m_TransformDesc, pArg, sizeof(TRANSFORMDESC));

	return S_OK;
}

HRESULT CSubTransform::Bind_OnGraphicDevice() const
{

	if (nullptr == m_pGraphic_Device)
		return E_FAIL;
	m_pGraphic_Device->SetTransform(D3DTS_WORLD, &m_WorldMatrix);

	return S_OK;
}

HRESULT CSubTransform::Go_Straight(_float fTimeDelta)
{
	/* 위치 += 노멀라이즈(룩) * 스피드 * FtIMNEdELTJ */
	_float3		vPosition = Get_State(CSubTransform::STATE_POSITION);
	_float3		vLook = Get_State(CSubTransform::STATE_LOOK);

	vPosition += *D3DXVec3Normalize(&vLook, &vLook) * m_TransformDesc.fSpeedPerSec * fTimeDelta;

	Set_State(CSubTransform::STATE_POSITION, vPosition);

	return S_OK;
}

HRESULT CSubTransform::Go_BackWard(_float fTimeDelta)
{
	_float3		vPosition = Get_State(CSubTransform::STATE_POSITION);
	_float3		vLook = Get_State(CSubTransform::STATE_LOOK);

	vPosition -= *D3DXVec3Normalize(&vLook, &vLook) * m_TransformDesc.fSpeedPerSec * fTimeDelta;

	Set_State(CSubTransform::STATE_POSITION, vPosition);

	return S_OK;
}

HRESULT CSubTransform::Go_Right(_float fTimeDelta)
{
	_float3		vPosition = Get_State(CSubTransform::STATE_POSITION);
	_float3		vRight = Get_State(CSubTransform::STATE_RIGHT);

	vPosition += *D3DXVec3Normalize(&vRight, &vRight) * m_TransformDesc.fSpeedPerSec * fTimeDelta;

	Set_State(CSubTransform::STATE_POSITION, vPosition);

	return S_OK;
}

HRESULT CSubTransform::Go_Left(_float fTimeDelta)
{
	_float3		vPosition = Get_State(CSubTransform::STATE_POSITION);
	_float3		vRight = Get_State(CSubTransform::STATE_RIGHT);

	vPosition -= *D3DXVec3Normalize(&vRight, &vRight) * m_TransformDesc.fSpeedPerSec * fTimeDelta;

	Set_State(CSubTransform::STATE_POSITION, vPosition);

	return S_OK;
}

HRESULT CSubTransform::Go_Up(_float fTimeDelta)
{
	_float3		vPosition = Get_State(CSubTransform::STATE_POSITION);
	_float3		vUp = Get_State(CSubTransform::STATE_UP);

	vPosition -= *D3DXVec3Normalize(&vUp, &vUp) * m_TransformDesc.fSpeedPerSec * fTimeDelta;

	Set_State(CSubTransform::STATE_POSITION, vPosition);

	return S_OK;
}

HRESULT CSubTransform::Go_X(_float fTimeDelta)
{
	_float3		vPosition = Get_State(CSubTransform::STATE_POSITION);

	vPosition.x += m_TransformDesc.fSpeedPerSec * fTimeDelta;

	Set_State(CSubTransform::STATE_POSITION, vPosition);

	return S_OK;
}

HRESULT CSubTransform::Go_Y(_float fTimeDelta)
{
	_float3		vPosition = Get_State(CSubTransform::STATE_POSITION);

	vPosition.y += m_TransformDesc.fSpeedPerSec * fTimeDelta;

	Set_State(CSubTransform::STATE_POSITION, vPosition);

	return S_OK;
}

HRESULT CSubTransform::Go_Z(_float fTimeDelta)
{
	_float3		vPosition = Get_State(CSubTransform::STATE_POSITION);

	vPosition.z += m_TransformDesc.fSpeedPerSec * fTimeDelta;

	Set_State(CSubTransform::STATE_POSITION, vPosition);

	return S_OK;
}

HRESULT CSubTransform::Scaled(_float3 vScale)
{
	_float3		vRight = Get_State(CSubTransform::STATE_RIGHT);
	_float3		vUp = Get_State(CSubTransform::STATE_UP);
	_float3		vLook = Get_State(CSubTransform::STATE_LOOK);

	Set_State(CSubTransform::STATE_RIGHT, *D3DXVec3Normalize(&vRight, &vRight) * vScale.x);
	Set_State(CSubTransform::STATE_UP, *D3DXVec3Normalize(&vUp, &vUp) * vScale.y);
	Set_State(CSubTransform::STATE_LOOK, *D3DXVec3Normalize(&vLook, &vLook) * vScale.z);

	return S_OK;
}

HRESULT CSubTransform::Scaling(_float fTimeDelta)
{
	_float		fScale = 0.f;

	_float3		vRight = Get_State(CSubTransform::STATE_RIGHT);
	fScale = D3DXVec3Length(&vRight) + m_TransformDesc.fScalePerSec * fTimeDelta;

	Set_State(CSubTransform::STATE_RIGHT, *D3DXVec3Normalize(&vRight, &vRight) * fScale);

	_float3		vUp = Get_State(CSubTransform::STATE_UP);
	fScale = D3DXVec3Length(&vUp) + m_TransformDesc.fScalePerSec * fTimeDelta;

	Set_State(CSubTransform::STATE_UP, *D3DXVec3Normalize(&vUp, &vUp) * fScale);

	_float3		vLook = Get_State(CSubTransform::STATE_LOOK);
	fScale = D3DXVec3Length(&vLook) + m_TransformDesc.fScalePerSec * fTimeDelta;

	Set_State(CSubTransform::STATE_LOOK, *D3DXVec3Normalize(&vLook, &vLook) * fScale);

	return S_OK;
}

HRESULT CSubTransform::Turn(const _float3& vAxis, _float fTimeDelta)
{
	_float4x4		RotationMatrix;

	D3DXMatrixRotationAxis(&RotationMatrix, &vAxis, fTimeDelta);

	_float3		vRight = Get_State(CSubTransform::STATE_RIGHT);
	_float3		vUp = Get_State(CSubTransform::STATE_UP);
	_float3		vLook = Get_State(CSubTransform::STATE_LOOK);

	D3DXVec3TransformNormal(&vRight, &vRight, &RotationMatrix);
	D3DXVec3TransformNormal(&vUp, &vUp, &RotationMatrix);
	D3DXVec3TransformNormal(&vLook, &vLook, &RotationMatrix);

	Set_State(CSubTransform::STATE_RIGHT, vRight);
	Set_State(CSubTransform::STATE_UP, vUp);
	Set_State(CSubTransform::STATE_LOOK, vLook);

	return S_OK;
}

HRESULT CSubTransform::Chase(const _float3 & vTargetPos, _float fTimeDelta, _float fLimitDistance)
{
	_float3		vPosition = Get_State(CSubTransform::STATE_POSITION);

	_float3		vLook = vTargetPos - vPosition;

	_float		fDistance = D3DXVec3Length(&vLook);

	if (fDistance > fLimitDistance)
		vPosition += *D3DXVec3Normalize(&vLook, &vLook) * m_TransformDesc.fSpeedPerSec * fTimeDelta;

	Set_State(CSubTransform::STATE_POSITION, vPosition);

	return S_OK;
}

HRESULT CSubTransform::LookAt(const _float3 & vTargetPos)
{
	_float3		vPosition = Get_State(CSubTransform::STATE_POSITION);
	_float3		vScale = Get_Scale();

	_float3		vLook = vTargetPos - vPosition;
	_float3		vAxisY = _float3(0.f, 1.f, 0.f);
	_float3		vRight = *D3DXVec3Cross(&vRight, &vAxisY, &vLook);
	_float3		vUp = *D3DXVec3Cross(&vUp, &vLook, &vRight);

	vRight = *D3DXVec3Normalize(&vRight, &vRight) * vScale.x;
	vUp = *D3DXVec3Normalize(&vUp, &vUp) * vScale.y;
	vLook = *D3DXVec3Normalize(&vLook, &vLook) * vScale.z;

	Set_State(CSubTransform::STATE_RIGHT, vRight);
	Set_State(CSubTransform::STATE_UP, vUp);
	Set_State(CSubTransform::STATE_LOOK, vLook);

	return S_OK;
}

HRESULT CSubTransform::LookRight(const _float3 & vTargetPos)
{
	_float3		vPosition = Get_StateWorld(CSubTransform::STATE_POSITION);
	_float3		vScale = Get_Scale();

	_float3		vRight = vTargetPos;
	_float3		vAxisZ = _float3(0.f, 0.f, 1.f);
	_float3		vUp = *D3DXVec3Cross(&vUp, &vAxisZ, &vRight);
	_float3		vLook = *D3DXVec3Cross(&vLook, &vRight, &vUp);

	vRight = *D3DXVec3Normalize(&vRight, &vRight) * vScale.x;
	vUp = *D3DXVec3Normalize(&vUp, &vUp) * vScale.y;
	vLook = *D3DXVec3Normalize(&vLook, &vLook) * vScale.z;

	Set_StateWorld(CSubTransform::STATE_RIGHT, vRight);
	Set_StateWorld(CSubTransform::STATE_UP, vUp);
	Set_StateWorld(CSubTransform::STATE_LOOK, vLook);

	return S_OK;
}



HRESULT CSubTransform::Look(const _float3 & vTargetPos)
{
	_float3		vPosition = Get_StateWorld(CSubTransform::STATE_POSITION);
	_float3		vScale = Get_Scale();

	_float3		vLook = vTargetPos;
	_float3		vAxisY = _float3(0.f, 1.f, 0.f);
	_float3		vRight = *D3DXVec3Cross(&vRight, &vAxisY, &vLook);
	_float3		vUp = *D3DXVec3Cross(&vUp, &vLook, &vRight);

	vRight = *D3DXVec3Normalize(&vRight, &vRight) * vScale.x;
	vUp = *D3DXVec3Normalize(&vUp, &vUp) * vScale.y;
	vLook = *D3DXVec3Normalize(&vLook, &vLook) * vScale.z;

	Set_StateWorld(CSubTransform::STATE_RIGHT, vRight);
	Set_StateWorld(CSubTransform::STATE_UP, vUp);
	Set_StateWorld(CSubTransform::STATE_LOOK, vLook);

	return S_OK;
}

HRESULT CSubTransform::LookAtWorld(const _float3 & vTargetPos)
{
	_float3		vPosition = Get_StateWorld(CSubTransform::STATE_POSITION);
	_float3		vScale = Get_Scale();

	_float3		vLook = vTargetPos - vPosition;
	_float3		vAxisY = _float3(0.f, 1.f, 0.f);
	_float3		vRight = *D3DXVec3Cross(&vRight, &vAxisY, &vLook);
	_float3		vUp = *D3DXVec3Cross(&vUp, &vLook, &vRight);

	vRight = *D3DXVec3Normalize(&vRight, &vRight) * vScale.x;
	vUp = *D3DXVec3Normalize(&vUp, &vUp) * vScale.y;
	vLook = *D3DXVec3Normalize(&vLook, &vLook) * vScale.z;

	Set_StateWorld(CSubTransform::STATE_RIGHT, vRight);
	Set_StateWorld(CSubTransform::STATE_UP, vUp);
	Set_StateWorld(CSubTransform::STATE_LOOK, vLook);

	return S_OK;
}

CSubTransform * CSubTransform::Create(LPDIRECT3DDEVICE9 pGraphic_Device)
{
	CSubTransform*	pInstance = new CSubTransform(pGraphic_Device);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created CSubTransform"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CComponent * CSubTransform::Clone(void * pArg)
{
	CSubTransform*	pInstance = new CSubTransform(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CSubTransform"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CSubTransform::Free()
{
	__super::Free();

}
