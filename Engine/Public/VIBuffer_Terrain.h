#pragma once

#include "VIBuffer.h"

BEGIN(Engine)

class ENGINE_DLL CVIBuffer_Terrain final : public CVIBuffer
{
protected:
	explicit CVIBuffer_Terrain(LPDIRECT3DDEVICE9 pGraphic_Device);
	explicit CVIBuffer_Terrain(const CVIBuffer_Terrain& rhs);
	virtual ~CVIBuffer_Terrain() = default;
public:
	virtual HRESULT NativeConstruct_Prototype(_uint iNumVerticesX, _uint iNumVerticesZ);
	virtual HRESULT NativeConstruct_Prototype(const _tchar* pHeightMapPath);	
	virtual HRESULT NativeConstruct(void* pArg) override;

public:
	virtual HRESULT Render() override;
public:
	_float3 Compute_Height(class CTransform * pTerrainWorldMatrix, const _float3 & vPosition);

private:
	_uint	m_iNumVerticesX, m_iNumVerticesZ;

public:
	_float2 Get_Numvertieces() { return _float2((_float)m_iNumVerticesX, (_float)m_iNumVerticesZ); }
	static CVIBuffer_Terrain* Create(LPDIRECT3DDEVICE9 pGraphic_Device, _uint iNumVerticesX, _uint iNumVerticesZ);
	static CVIBuffer_Terrain* Create(LPDIRECT3DDEVICE9 pGraphic_Device, const _tchar* pHeightMapPath);
	virtual CComponent* Clone(void* pArg);
	virtual void Free() override;
};

END