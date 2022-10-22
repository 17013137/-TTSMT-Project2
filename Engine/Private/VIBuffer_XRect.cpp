#include "..\Public\VIBuffer_XRect.h"



CVIBuffer_XRect::CVIBuffer_XRect(LPDIRECT3DDEVICE9 pGraphic_Device)
	: CVIBuffer(pGraphic_Device)
{

}

CVIBuffer_XRect::CVIBuffer_XRect(const CVIBuffer_XRect & rhs)
	: CVIBuffer(rhs)
{

}

HRESULT CVIBuffer_XRect::NativeConstruct_Prototype()
{
	if (FAILED(__super::NativeConstruct_Prototype()))
		return E_FAIL;

	m_iNumVertices = 8;
	m_iStride = sizeof(VTXTEX);
	// m_dwFVF = D3DFVF_XYZ | D3DFVF_TEX2 | D3DFVF_TEXCOORDSIZE2(0) | D3DFVF_TEXCOORDSIZE3(1);
	m_dwFVF = D3DFVF_XYZ | D3DFVF_TEX1;
	m_ePrimitiveType = D3DPT_TRIANGLELIST;
	m_iNumPrimitives = 4;

	if (FAILED(Create_VertexBuffer()))
		return E_FAIL;

	m_pVertices = new VTXTEX[m_iNumVertices];

	VTXTEX*		pVertices = nullptr;

	m_pVB->Lock(0, 0/*m_iStride * m_iNumVertices*/, (void**)&pVertices, 0);

	/* 값을 바꾸고. */
	pVertices[0].vPosition = _float3(-0.5f, 0.5f, 0.f);
	pVertices[0].vTexUV = _float2(0.f, 0.f);

	pVertices[1].vPosition = _float3(0.5f, 0.5f, 0.f);
	pVertices[1].vTexUV = _float2(1.f, 0.f);

	pVertices[2].vPosition = _float3(0.5f, -0.5f, 0.f);
	pVertices[2].vTexUV = _float2(1.f, 1.f);

	pVertices[3].vPosition = _float3(-0.5f, -0.5f, 0.f);
	pVertices[3].vTexUV = _float2(0.f, 1.f);

	// --
	pVertices[4].vPosition = _float3(0.f, 0.5f, -0.5f);
	pVertices[4].vTexUV = _float2(0.f, 0.f);

	pVertices[5].vPosition = _float3(0.f, 0.5f, 0.5f);
	pVertices[5].vTexUV = _float2(1.f, 0.f);

	pVertices[6].vPosition = _float3(0.f, -0.5f, 0.5f);
	pVertices[6].vTexUV = _float2(1.f, 1.f);

	pVertices[7].vPosition = _float3(0.f, -0.5f, -0.5f);
	pVertices[7].vTexUV = _float2(0.f, 1.f);

	memcpy(m_pVertices, pVertices, sizeof(VTXTEX) * m_iNumVertices);

	m_pVB->Unlock();

	m_iPrimitiveIndicesSize = sizeof(FACELISTINDICES16);
	m_eFormat = D3DFMT_INDEX16;

	m_pIndices = new FACELISTINDICES16[m_iNumPrimitives];
	ZeroMemory(m_pIndices, sizeof(FACELISTINDICES16) * m_iNumPrimitives);

	if (FAILED(Create_IndexBuffer()))
		return E_FAIL;

	FACELISTINDICES16*		pIndices = nullptr;

	m_pIB->Lock(0, 0, (void**)&pIndices, 0);

	pIndices[0]._0 = 0;
	pIndices[0]._1 = 1;
	pIndices[0]._2 = 2;

	pIndices[1]._0 = 0;
	pIndices[1]._1 = 2;
	pIndices[1]._2 = 3;

	pIndices[2]._0 = 4;
	pIndices[2]._1 = 5;
	pIndices[2]._2 = 6;

	pIndices[3]._0 = 4;
	pIndices[3]._1 = 6;
	pIndices[3]._2 = 7;

	memcpy(m_pIndices, pIndices, sizeof(FACELISTINDICES16) * m_iNumPrimitives);

	m_pIB->Unlock();

	return S_OK;
}

HRESULT CVIBuffer_XRect::NativeConstruct(void * pArg)
{
	if (FAILED(__super::NativeConstruct(pArg)))
		return E_FAIL;

	return S_OK;
}

CVIBuffer_XRect * CVIBuffer_XRect::Create(LPDIRECT3DDEVICE9 pGraphic_Device)
{
	CVIBuffer_XRect*	pInstance = new CVIBuffer_XRect(pGraphic_Device);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created CVIBuffer_XRect"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CComponent * CVIBuffer_XRect::Clone(void * pArg)
{
	CVIBuffer_XRect*	pInstance = new CVIBuffer_XRect(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CVIBuffer_XRect"));
		Safe_Release(pInstance);
	}

	return pInstance;
}


void CVIBuffer_XRect::Free()
{
	__super::Free();
}
