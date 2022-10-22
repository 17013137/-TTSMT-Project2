#include "stdafx.h"
#include "Mouse.h"
#include "GameInstance.h"
#include "Terrain.h"
IMPLEMENT_SINGLETON(CMouse)

CMouse::CMouse()
{
}

CMouse::CMouse(LPDIRECT3DDEVICE9 _pGraphic_Device)
	: m_pGraphic_Device(_pGraphic_Device)
{
	Safe_AddRef(m_pGraphic_Device);
}

CMouse* CMouse::Create(LPDIRECT3DDEVICE9 _pGraphic_Device)
{
	m_pInstance = new CMouse(_pGraphic_Device);

	return m_pInstance;
}

void CMouse::Free()
{
	Safe_Release(m_pGraphic_Device);
	if (nullptr != m_pInstance)
	{
		delete m_pInstance;
		m_pInstance = nullptr;
	}
}

void CMouse::Tick()
{
	GetCursorPos(&m_ptMouse);
	ScreenToClient(g_hWnd, &m_ptMouse);

	D3DVIEWPORT9 viewport;
	m_pGraphic_Device->GetViewport(&viewport);

	_float4x4 projmat;
	m_pGraphic_Device->GetTransform(D3DTS_PROJECTION, &projmat);

	m_RayVector.x = (((((m_ptMouse.x - viewport.X) * 2 / (float)viewport.Width) - 1.f)) - projmat(2, 0)) / projmat(0, 0);
	m_RayVector.y = ((-(((m_ptMouse.y - viewport.Y) * 2 / (float)viewport.Height) - 1.f)) - projmat(2, 1)) / projmat(1, 1);
	m_RayVector.z = 1.f;
	m_RayPos = _float3(0.f, 0.f, 0.f);
	
	_float4x4 inverseview;
	m_pGraphic_Device->GetTransform(D3DTS_VIEW, &inverseview);
	D3DXMatrixInverse(&inverseview, 0, &inverseview);

	D3DXVec3TransformCoord(&m_RayPos, &m_RayPos, &inverseview);
	D3DXVec3TransformNormal(&m_RayVector, &m_RayVector, &inverseview);
	D3DXVec3Normalize(&m_RayVector, &m_RayVector);
}

_float CMouse::Pick(D3DXVECTOR3& _p1, D3DXVECTOR3& _p2, D3DXVECTOR3& _p3, _float4x4 _worldmat)
{
	float _fDistance = 0.f;

	D3DXMatrixInverse(&_worldmat, 0, &_worldmat);
	D3DXVec3TransformCoord(&m_RayPos, &m_RayPos, &_worldmat);
	D3DXVec3TransformNormal(&m_RayVector, &m_RayVector, &_worldmat);

	if (D3DXIntersectTri(&_p1, &_p2, &_p3, &m_RayPos, &m_RayVector, nullptr, nullptr, &_fDistance)) {
		return _fDistance;
	}

	return -1.f;
}

_float3 CMouse::Get_PeekPos(_float _dist)
{
	_float3 _pos = m_RayPos;
	_float3 _dir = m_RayVector;
	_float3 _temp = _float3(_dir.x * _dist, (_float)_dir.y * (_float)_dist , _dir.z * _dist);
	_temp += _pos;
	return _temp;
}

_float CMouse::Pick_Dist(CTerrain* _Obj, const _tchar* pBuffTag, const _tchar* pTransComTag)
{
	//Terrain Àü¿ë

	CGameInstance* temp = CGameInstance::GetInstance();
	Safe_AddRef(temp);

	CVIBuffer* VIBuff = (CVIBuffer*)_Obj->Get_Component(pBuffTag);
	CTransform* TransformCom = (CTransform*)_Obj->Get_Component(pTransComTag);
	VTXTEX* vtx = (VTXTEX*)VIBuff->GetVertices();

	_float2 numVtxXZ = _Obj->Get_NumvtxXZ();
	
	_float _dist = 0;

	for (_uint i = 0; i < numVtxXZ.y - 1; ++i)
	{
		for (_uint j = 0; j < numVtxXZ.x - 1; ++j)
		{

			_uint iIndex = i * (_uint)numVtxXZ.x + j;

			_uint iIndices[4] = {
				iIndex + (_uint)numVtxXZ.x,
				iIndex + (_uint)numVtxXZ.x + 1,
				iIndex + 1,
				iIndex
			};
			_dist = Pick(vtx[iIndices[0]].vPosition, vtx[iIndices[1]].vPosition, vtx[iIndices[2]].vPosition, TransformCom->Get_WorldMatrix());
			if (_dist > 0) {
				return _dist;
			}
			_dist = Pick(vtx[iIndices[0]].vPosition, vtx[iIndices[2]].vPosition, vtx[iIndices[3]].vPosition, TransformCom->Get_WorldMatrix());
			if (_dist > 0) {
				return _dist;
			}
		}
	}

	Safe_Release(temp);

	return _dist;
}

_bool CMouse::Picking(CGameObject* _Obj, const _tchar* pBuffTag, const _tchar* pTransComTag)
{
	CGameInstance* temp = CGameInstance::GetInstance();
	Safe_AddRef(temp);
	CTransform* TransformCom = (CTransform*)_Obj->Get_Component(pTransComTag);
	CVIBuffer* VIBuff = (CVIBuffer*)_Obj->Get_Component(pBuffTag);
	_float4x4 tlqkf;
	memcpy(tlqkf, TransformCom->Get_WorldMatrix(), sizeof(tlqkf));
	if (VIBuff->m_ePrimitiveType != D3DPT_TRIANGLELIST || TransformCom == nullptr || VIBuff == nullptr)
		return false;

	_uint			iIndexByteSize = VIBuff->m_iPrimitiveIndicesSize / 3;


	for (_uint i = 0; i < VIBuff->m_iNumPrimitives; ++i)
	{
		_uchar*		pData = (_uchar*)VIBuff->m_pIndices + (i * VIBuff->m_iPrimitiveIndicesSize);

		_uint		iIndices[] = {
			VIBuff->m_eFormat == D3DFMT_INDEX16 ? ((_ushort*)pData)[0] : ((_ulong*)pData)[0],
			VIBuff->m_eFormat == D3DFMT_INDEX16 ? ((_ushort*)pData)[1] : ((_ulong*)pData)[1],
			VIBuff->m_eFormat == D3DFMT_INDEX16 ? ((_ushort*)pData)[2] : ((_ulong*)pData)[2]
		};

		_float3		vPoints[] = {
			*(_float3*)((_uchar*)VIBuff->m_pVertices + VIBuff->m_iStride * iIndices[0]),
			*(_float3*)((_uchar*)VIBuff->m_pVertices + VIBuff->m_iStride * iIndices[1]),
			*(_float3*)((_uchar*)VIBuff->m_pVertices + VIBuff->m_iStride * iIndices[2])
		};
		D3DXMatrixIdentity(&tlqkf);
		_float isPick = Pick(vPoints[0], vPoints[1], vPoints[2], tlqkf);
		if (isPick > 0.f)
			return true;
	}

	Safe_Release(temp);

	return false;
}
