#include "..\Public\Picking.h"

IMPLEMENT_SINGLETON(CPicking)

CPicking::CPicking()
{
}

HRESULT CPicking::NativeConstruct(HWND hWnd, LPDIRECT3DDEVICE9 pGraphic_Device)
{
	if (0 == hWnd || 
		nullptr == pGraphic_Device)
		return E_FAIL;

	m_hWnd = hWnd;

	m_pGraphic_Device = pGraphic_Device;
	
	Safe_AddRef(m_pGraphic_Device);

	return S_OK;
}

void CPicking::Update_ToTransform()
{
	if (nullptr == m_pGraphic_Device)
		return;

	POINT		ptMouse;

	GetCursorPos(&ptMouse);

	/* 뷰 포트 영역상의 마우스 좌표를 구했다. */
	ScreenToClient(m_hWnd, &ptMouse);

	D3DVIEWPORT9		Viewport;

	m_pGraphic_Device->GetViewport(&Viewport);

	/* 투영스페이스 상의 마우스 좌표를 구한다. */
	_float4		vMousePos;
	vMousePos.x = ptMouse.x / _float(Viewport.Width >> 1) - 1.f;
	vMousePos.y = -ptMouse.y / _float(Viewport.Height >> 1) + 1.f;
	vMousePos.z = 0.0f;
	vMousePos.w = 1.f;

	/* 뷰스페이스 상의 마우스 좌표를 구한다.(투영상태를 제거하자.)*/
	_float4x4		ProjMatrix;
	m_pGraphic_Device->GetTransform(D3DTS_PROJECTION, &ProjMatrix);
	D3DXMatrixInverse(&ProjMatrix, nullptr, &ProjMatrix);
	D3DXVec4Transform(&vMousePos, &vMousePos, &ProjMatrix);
	m_vWorldRay = _float3(vMousePos.x, vMousePos.y, vMousePos.z);
	m_vWorldRayPos = _float3(0.f, 0.f, 0.f);

	/* 월드스페이스 상의 마우스 Ray, RayPos를 구한다.(뷰변환상태를 제거하자) */
	_float4x4		ViewMatrix;
	m_pGraphic_Device->GetTransform(D3DTS_VIEW, &ViewMatrix);
	D3DXMatrixInverse(&ViewMatrix, nullptr, &ViewMatrix);

	D3DXVec3TransformNormal(&m_vWorldRay, &m_vWorldRay, &ViewMatrix);
	D3DXVec3TransformCoord(&m_vWorldRayPos, &m_vWorldRayPos, &ViewMatrix);
}

void CPicking::Transform_ToLocalSpace(_float4x4 * pWorldMatrixInverse)
{
	D3DXVec3TransformNormal(&m_vLocalRay, &m_vWorldRay, pWorldMatrixInverse);
	D3DXVec3Normalize(&m_vLocalRay, &m_vLocalRay);

	D3DXVec3TransformCoord(&m_vLocalRayPos, &m_vWorldRayPos, pWorldMatrixInverse);
}

_bool CPicking::Picking_OnLocalSpace(_float3 * pLocalPoints, _float3* pPickingPointOut)
{
	_float		fU, fV, fDist;

	if (TRUE == D3DXIntersectTri(&pLocalPoints[0], &pLocalPoints[1], &pLocalPoints[2], &m_vLocalRayPos, &m_vLocalRay,  &fU, &fV, &fDist))
	{
		*pPickingPointOut = m_vLocalRayPos + m_vLocalRay * fDist;

		return true;
	}

	return false;
}

void CPicking::Free()
{
	Safe_Release(m_pGraphic_Device);
}
