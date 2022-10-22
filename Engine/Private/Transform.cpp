#include "..\Public\Transform.h"


CTransform::CTransform(LPDIRECT3DDEVICE9 pGraphic_Device)
	: CComponent(pGraphic_Device)
{
}

CTransform::CTransform(const CTransform & rhs)
	: CComponent(rhs)
	, m_WorldMatrix(rhs.m_WorldMatrix)
{
}

_float3 CTransform::Get_Scale()
{
	_float3		vRight = Get_State(CTransform::STATE_RIGHT);
	_float3		vUp = Get_State(CTransform::STATE_UP);
	_float3		vLook = Get_State(CTransform::STATE_LOOK);

	return _float3(D3DXVec3Length(&vRight), D3DXVec3Length(&vUp), D3DXVec3Length(&vLook));
}

HRESULT CTransform::NativeConstruct_Prototype()
{
	D3DXMatrixIdentity(&m_WorldMatrix);


	return S_OK;
}

HRESULT CTransform::NativeConstruct(void * pArg)
{
	if (nullptr != pArg)
		memcpy(&m_TransformDesc, pArg, sizeof(TRANSFORMDESC));

	return S_OK;
}

HRESULT CTransform::Bind_OnGraphicDevice() const
{

	if (nullptr == m_pGraphic_Device)
		return E_FAIL;
	m_pGraphic_Device->SetTransform(D3DTS_WORLD, &m_WorldMatrix);

	return S_OK;
}

HRESULT CTransform::Go_Straight(_float fTimeDelta)
{
	/* 위치 += 노멀라이즈(룩) * 스피드 * FtIMNEdELTJ */
	_float3		vPosition = Get_State(CTransform::STATE_POSITION);
	_float3		vLook = Get_State(CTransform::STATE_LOOK);

	vPosition += *D3DXVec3Normalize(&vLook, &vLook) * m_TransformDesc.fSpeedPerSec * fTimeDelta;

	Set_State(CTransform::STATE_POSITION, vPosition);

	return S_OK;
}

HRESULT CTransform::Go_BackWard(_float fTimeDelta)
{
	_float3		vPosition = Get_State(CTransform::STATE_POSITION);
	_float3		vLook = Get_State(CTransform::STATE_LOOK);

	vPosition -= *D3DXVec3Normalize(&vLook, &vLook) * m_TransformDesc.fSpeedPerSec * fTimeDelta;

	Set_State(CTransform::STATE_POSITION, vPosition);

	return S_OK;
}

HRESULT CTransform::Go_Right(_float fTimeDelta)
{
	_float3		vPosition = Get_State(CTransform::STATE_POSITION);
	_float3		vRight = Get_State(CTransform::STATE_RIGHT);

	vPosition += *D3DXVec3Normalize(&vRight, &vRight) * m_TransformDesc.fSpeedPerSec * fTimeDelta;

	Set_State(CTransform::STATE_POSITION, vPosition);

	return S_OK;
}

HRESULT CTransform::Go_Left(_float fTimeDelta)
{
	_float3		vPosition = Get_State(CTransform::STATE_POSITION);
	_float3		vRight = Get_State(CTransform::STATE_RIGHT);

	vPosition -= *D3DXVec3Normalize(&vRight, &vRight) * m_TransformDesc.fSpeedPerSec * fTimeDelta;

	Set_State(CTransform::STATE_POSITION, vPosition);

	return S_OK;
}

HRESULT CTransform::Scaled(_float3 vScale)
{
	_float3		vRight = Get_State(CTransform::STATE_RIGHT);
	_float3		vUp = Get_State(CTransform::STATE_UP);
	_float3		vLook = Get_State(CTransform::STATE_LOOK);

	Set_State(CTransform::STATE_RIGHT, *D3DXVec3Normalize(&vRight, &vRight) * vScale.x);
	Set_State(CTransform::STATE_UP, *D3DXVec3Normalize(&vUp, &vUp) * vScale.y);
	Set_State(CTransform::STATE_LOOK, *D3DXVec3Normalize(&vLook, &vLook) * vScale.z);

	return S_OK;
}

HRESULT CTransform::Scaling(_float fTimeDelta)
{
	_float		fScale = 5.f;

	_float3		vRight = Get_State(CTransform::STATE_RIGHT);
	fScale = D3DXVec3Length(&vRight) + m_TransformDesc.fScalePerSec * fTimeDelta;

	Set_State(CTransform::STATE_RIGHT, *D3DXVec3Normalize(&vRight, &vRight) * fScale);

	_float3		vUp = Get_State(CTransform::STATE_UP);
	fScale = D3DXVec3Length(&vUp) + m_TransformDesc.fScalePerSec * fTimeDelta;

	Set_State(CTransform::STATE_UP, *D3DXVec3Normalize(&vUp, &vUp) * fScale);

	_float3		vLook = Get_State(CTransform::STATE_LOOK);
	fScale = D3DXVec3Length(&vLook) + m_TransformDesc.fScalePerSec * fTimeDelta;

	Set_State(CTransform::STATE_LOOK, *D3DXVec3Normalize(&vLook, &vLook) * fScale);

	return S_OK;
}

HRESULT CTransform::Axis_Scaling(const _float3 vDir, _float fTimeDelta)
{
	_float		fScale = 5.f;

	if (vDir.y == 0.f && vDir.z == 0.f) {
		_float3		vRight = Get_State(CTransform::STATE_RIGHT);
		fScale = D3DXVec3Length(&vRight) + m_TransformDesc.fScalePerSec * (fTimeDelta * vDir.x);

		Set_State(CTransform::STATE_RIGHT, *D3DXVec3Normalize(&vRight, &vRight) * fScale);
	}
	else if (vDir.x == 0.f && vDir.z == 0.f) {
		_float3		vUp = Get_State(CTransform::STATE_UP);
		fScale = D3DXVec3Length(&vUp) + m_TransformDesc.fScalePerSec * (fTimeDelta * vDir.y);

		Set_State(CTransform::STATE_UP, *D3DXVec3Normalize(&vUp, &vUp) * fScale);
	}
	else if (vDir.x == 0.f && vDir.y == 0.f) {
		_float3		vLook = Get_State(CTransform::STATE_LOOK);
		fScale = D3DXVec3Length(&vLook) + m_TransformDesc.fScalePerSec * (fTimeDelta * vDir.z);

		Set_State(CTransform::STATE_LOOK, *D3DXVec3Normalize(&vLook, &vLook) * fScale);
	}
	
	return S_OK;
}

HRESULT CTransform::Turn90(const _float3 & vAxis)
{
	_float3		vRight = Get_State(CTransform::STATE_RIGHT);
	_float3		vUp = Get_State(CTransform::STATE_UP);
	_float3		vLook = Get_State(CTransform::STATE_LOOK);

	if (vAxis.x == 0 && vAxis.z == 0) {
		vLook = vRight*vAxis.y;
		D3DXVec3Cross(&vRight, &vUp, &vLook);
		D3DXVec3Cross(&vUp, &vLook, &vRight);
		Set_State(CTransform::STATE_RIGHT, vRight);
		Set_State(CTransform::STATE_UP, vUp);
		Set_State(CTransform::STATE_LOOK, vLook);
	}
	else {
		vLook = vUp*vAxis.x;
		D3DXVec3Cross(&vUp, &vLook, &vRight);
		D3DXVec3Cross(&vRight, &vUp, &vLook);
		Set_State(CTransform::STATE_RIGHT, vRight);
		Set_State(CTransform::STATE_UP, vUp);
		Set_State(CTransform::STATE_LOOK, vLook);

	}

	return S_OK;
}

HRESULT CTransform::Turn(const _float3& vAxis, _float fTimeDelta)
{
	_float4x4		RotationMatrix;

	D3DXMatrixRotationAxis(&RotationMatrix, &vAxis, fTimeDelta);

	_float3		vRight = Get_State(CTransform::STATE_RIGHT);
	_float3		vUp = Get_State(CTransform::STATE_UP);
	_float3		vLook = Get_State(CTransform::STATE_LOOK);

	D3DXVec3TransformNormal(&vRight, &vRight, &RotationMatrix);
	D3DXVec3TransformNormal(&vUp, &vUp, &RotationMatrix);
	D3DXVec3TransformNormal(&vLook, &vLook, &RotationMatrix);

	Set_State(CTransform::STATE_RIGHT, vRight);
	Set_State(CTransform::STATE_UP, vUp);
	Set_State(CTransform::STATE_LOOK, vLook);

	return S_OK;
}

HRESULT CTransform::Chase(const _float3 & vTargetPos, _float fTimeDelta, _float fLimitDistance)
{
	_float3		vPosition = Get_State(CTransform::STATE_POSITION);

	_float3		vLook = vTargetPos - vPosition;	

	_float		fDistance = D3DXVec3Length(&vLook);

	if(fDistance > fLimitDistance)
		vPosition += *D3DXVec3Normalize(&vLook, &vLook) * m_TransformDesc.fSpeedPerSec * fTimeDelta;

	Set_State(CTransform::STATE_POSITION, vPosition);

	return S_OK;
}

HRESULT CTransform::LookAt(const _float3 & vTargetPos)
{
	_float3		vPosition = Get_State(CTransform::STATE_POSITION);
	_float3		vScale = Get_Scale();

	_float3		vLook = vTargetPos - vPosition;
	_float3		vAxisY = _float3(0.f, 1.f, 0.f);
	_float3		vRight = *D3DXVec3Cross(&vRight, &vAxisY, &vLook);
	_float3		vUp = *D3DXVec3Cross(&vUp, &vLook, &vRight);

	vRight = *D3DXVec3Normalize(&vRight, &vRight) * vScale.x;
	vUp = *D3DXVec3Normalize(&vUp, &vUp) * vScale.y;
	vLook = *D3DXVec3Normalize(&vLook, &vLook) * vScale.z;

	Set_State(CTransform::STATE_RIGHT, vRight);
	Set_State(CTransform::STATE_UP, vUp);
	Set_State(CTransform::STATE_LOOK, vLook);

	return S_OK;
}

CTransform * CTransform::Create(LPDIRECT3DDEVICE9 pGraphic_Device)
{
	CTransform*	pInstance = new CTransform(pGraphic_Device);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created CTransform"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CComponent * CTransform::Clone(void * pArg)
{
	CTransform*	pInstance = new CTransform(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CTransform"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CTransform::Free()
{
	__super::Free();

}
