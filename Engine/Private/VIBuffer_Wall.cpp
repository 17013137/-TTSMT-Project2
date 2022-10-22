#include "..\Public\VIBuffer_Wall.h"

CVIBuffer_Wall::CVIBuffer_Wall(LPDIRECT3DDEVICE9 pGraphic_Device)
	: CVIBuffer(pGraphic_Device)
{
}

CVIBuffer_Wall::CVIBuffer_Wall(const CVIBuffer_Wall & rhs)
	: CVIBuffer(rhs)
{
}

HRESULT CVIBuffer_Wall::NativeConstruct_Prototype()
{
	if (FAILED(__super::NativeConstruct_Prototype()))
		return E_FAIL;

	m_iNumVertices = 8;
	m_iStride = sizeof(VTXOBJECTTEX);
	m_dwFVF = D3DFVF_XYZ | D3DFVF_DIFFUSE;;
	m_ePrimitiveType = D3DPT_TRIANGLELIST;
	m_iNumPrimitives = 12;

	if (FAILED(Create_VertexBuffer()))
		return E_FAIL;

	m_pVertices = new VTXOBJECTTEX[m_iNumVertices];


	VTXOBJECTTEX*		pVertices = nullptr;

	m_pVB->Lock(0, 0/*m_iStride * m_iNumVertices*/, (void**)&pVertices, 0);

	/* 값을 바꾸고. */
	pVertices[0].vPosition = _float3(-0.5f, 1.f, 0.4f);
	pVertices[0].vColor = 0xffffffff;
	pVertices[1].vPosition = _float3(0.5f, 1.f, 0.4f);
	pVertices[1].vColor = 0xffffffff;

	pVertices[2].vPosition = _float3(0.5f, 0.f, 0.4f);
	pVertices[2].vColor = 0xffffffff;

	pVertices[3].vPosition = _float3(-0.5f, 0.f, 0.4f);
	pVertices[3].vColor = 0xffffffff;

	pVertices[4].vPosition = _float3(-0.5f, 1.f, 0.5f);
	pVertices[4].vColor = 0xffbcbcbc;

	pVertices[5].vPosition = _float3(0.5f, 1.f, 0.5f);
	pVertices[5].vColor = 0xffbcbcbc;

	pVertices[6].vPosition = _float3(0.5f, 0.f, 0.5f);
	pVertices[6].vColor = 0xffbcbcbc;

	pVertices[7].vPosition = _float3(-0.5f, 0.f, 0.5f);
	pVertices[7].vColor = 0xffbcbcbc;

	memcpy(m_pVertices, pVertices, sizeof(VTXOBJECTTEX) * m_iNumVertices);

	m_pVB->Unlock();

	m_iPrimitiveIndicesSize = sizeof(FACELISTINDICES16);
	m_eFormat = D3DFMT_INDEX16;

	m_pIndices = new FACELISTINDICES16[m_iNumPrimitives];
	ZeroMemory(m_pIndices, sizeof(FACELISTINDICES16) * m_iNumPrimitives);

	if (FAILED(Create_IndexBuffer()))
		return E_FAIL;

	FACELISTINDICES16*		pIndices = nullptr;

	m_pIB->Lock(0, 0, (void**)&pIndices, 0);

	/* +x */
	pIndices[0]._0 = 1; pIndices[0]._1 = 5; pIndices[0]._2 = 6;
	pIndices[1]._0 = 1; pIndices[1]._1 = 6; pIndices[1]._2 = 2;

	/* -x */
	pIndices[2]._0 = 4; pIndices[2]._1 = 0; pIndices[2]._2 = 3;
	pIndices[3]._0 = 4; pIndices[3]._1 = 3; pIndices[3]._2 = 7;

	/* +y */
	pIndices[4]._0 = 4; pIndices[4]._1 = 5; pIndices[4]._2 = 1;
	pIndices[5]._0 = 4; pIndices[5]._1 = 1; pIndices[5]._2 = 0;

	/* -y */
	pIndices[6]._0 = 3; pIndices[6]._1 = 2; pIndices[6]._2 = 6;
	pIndices[7]._0 = 3; pIndices[7]._1 = 6; pIndices[7]._2 = 7;

	/* +z */
	pIndices[8]._0 = 5; pIndices[8]._1 = 4; pIndices[8]._2 = 7;
	pIndices[9]._0 = 5; pIndices[9]._1 = 7; pIndices[9]._2 = 6;

	/* -z */
	pIndices[10]._0 = 0; pIndices[10]._1 = 1; pIndices[10]._2 = 2;
	pIndices[11]._0 = 0; pIndices[11]._1 = 2; pIndices[11]._2 = 3;	

	memcpy(m_pIndices, pIndices, sizeof(FACELISTINDICES16) * m_iNumPrimitives);

	m_pIB->Unlock();

	return S_OK;
}

HRESULT CVIBuffer_Wall::NativeConstruct(void * pArg)
{
	if (FAILED(__super::NativeConstruct(pArg)))
		return E_FAIL;

	return S_OK;
}

CVIBuffer_Wall * CVIBuffer_Wall::Create(LPDIRECT3DDEVICE9 pGraphic_Device)
{
	CVIBuffer_Wall*	pInstance = new CVIBuffer_Wall(pGraphic_Device);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created CVIBuffer_Wall"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CComponent * CVIBuffer_Wall::Clone(void * pArg)
{
	CVIBuffer_Wall*	pInstance = new CVIBuffer_Wall(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CVIBuffer_Wall"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CVIBuffer_Wall::Free()
{
	__super::Free();


}
