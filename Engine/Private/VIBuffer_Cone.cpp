#include "..\Public\VIBuffer_Cone.h"



CVIBuffer_Cone::CVIBuffer_Cone(LPDIRECT3DDEVICE9 pGraphic_Device)
	:CVIBuffer(pGraphic_Device)
{
}

CVIBuffer_Cone::CVIBuffer_Cone(const CVIBuffer_Cone & rhs)
	:CVIBuffer(rhs)
{
}

HRESULT CVIBuffer_Cone::NativeConstruct_Prototype()
{
	if (FAILED(__super::NativeConstruct_Prototype()))
		return E_FAIL;

	m_iNumVertices = 14;
	m_iStride = sizeof(VTXOBJECTTEX);

	m_dwFVF = D3DFVF_XYZ | D3DFVF_DIFFUSE;
	m_ePrimitiveType = D3DPT_TRIANGLELIST;
	m_iNumPrimitives = 24;

	if (FAILED(Create_VertexBuffer()))
		return E_FAIL;

	m_pVertices = new VTXOBJECTTEX[m_iNumVertices];

	VTXOBJECTTEX*		pVertices = nullptr;

	m_pVB->Lock(0, 0/*m_iStride * m_iNumVertices*/, (void**)&pVertices, 0);

	//¿ø»Ô ²ÀÁöÁ¡
	pVertices[0].vPosition = _float3(0.f, 1.f, 0.f);
	pVertices[0].vColor = 0xff532e08;

	//¿ø»Ô ¹Ø´Ü
	pVertices[1].vPosition = _float3(-0.5f, 0.f, 0.f);
	pVertices[1].vColor = 0xff532e08;

	//¿ø»Ô ¹Ø´Ü
	pVertices[2].vPosition = _float3(-0.43f, 0.f, -0.25f);
	pVertices[2].vColor = 0xff532e08;

	//¿ø»Ô ¹Ø´Ü
	pVertices[3].vPosition = _float3(-0.25f, 0.f, -0.43f);
	pVertices[3].vColor = 0xff532e08;

	//¿ø»Ô ¹Ø´Ü
	pVertices[4].vPosition = _float3(0.f, 0.f, -0.5f);
	pVertices[4].vColor = 0xff532e08;

	//¿ø»Ô ¹Ø´Ü
	pVertices[5].vPosition = _float3(0.25f, 0.f, -0.43f);
	pVertices[5].vColor = 0xff532e08;

	//¿ø»Ô ¹Ø´Ü
	pVertices[6].vPosition = _float3(0.43f, 0.f, -0.25f);
	pVertices[6].vColor = 0xff532e08;

	//¿ø»Ô ¹Ø´Ü
	pVertices[7].vPosition = _float3(0.5f, 0.f, 0.f);
	pVertices[7].vColor = 0xff532e08;

	//¿ø»Ô ¹Ø´Ü
	pVertices[8].vPosition = _float3(0.43f, 0.f, 0.25f);
	pVertices[8].vColor = 0xff532e08;

	//¿ø»Ô ¹Ø´Ü
	pVertices[9].vPosition = _float3(0.25f, 0.f, 0.43f);
	pVertices[9].vColor = 0xff532e08;

	//¿ø»Ô ¹Ø´Ü
	pVertices[10].vPosition = _float3(0.f, 0.f, 0.5f);
	pVertices[10].vColor = 0xff532e08;


	//¿ø»Ô ¹Ø´Ü
	pVertices[11].vPosition = _float3(-0.25f, 0.f, 0.43f);
	pVertices[11].vColor = 0xff532e08;

	//¿ø»Ô ¹Ø´Ü
	pVertices[12].vPosition = _float3(-0.43f, 0.f, 0.25f);
	pVertices[12].vColor = 0xff532e08;


	//¹Ø´ÜÀÇ Áß¾Ó
	pVertices[13].vPosition = _float3(0.f, 0.f, 0.f);
	pVertices[13].vColor = 0xff532e08;
	
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
	
	//³ª¹«¾Æ·¡
	pIndices[0]._0 = 1; 
	pIndices[0]._1 = 2; 
	pIndices[0]._2 = 14;

	pIndices[1]._0 = 2; 
	pIndices[1]._1 = 3; 
	pIndices[1]._2 = 14;

	pIndices[2]._0 = 3; 
	pIndices[2]._1 = 4; 
	pIndices[2]._2 = 14;

	pIndices[3]._0 = 4; 
	pIndices[3]._1 = 5; 
	pIndices[3]._2 = 14;

	pIndices[4]._0 = 5; 
	pIndices[4]._1 = 6; 
	pIndices[4]._2 = 14;

	pIndices[5]._0 = 6; 
	pIndices[5]._1 = 7; 
	pIndices[5]._2 = 14;

	pIndices[6]._0 = 7; 
	pIndices[6]._1 = 8; 
	pIndices[6]._2 = 14;

	pIndices[7]._0 = 8; 
	pIndices[7]._1 = 9; 
	pIndices[7]._2 = 14;

	pIndices[8]._0 = 9;
	pIndices[8]._1 = 10;
	pIndices[8]._2 = 14;

	pIndices[9]._0 = 10;
	pIndices[9]._1 = 11;
	pIndices[9]._2 = 14;

	pIndices[10]._0 = 11;
	pIndices[10]._1 = 12;
	pIndices[10]._2 = 14;

	pIndices[11]._0 = 12;
	pIndices[11]._1 = 1;
	pIndices[11]._2 = 14;

	//»ÏÁ·
	pIndices[12]._0 = 0;
	pIndices[12]._1 = 1;
	pIndices[12]._2 = 12;

	pIndices[13]._0 = 0;
	pIndices[13]._1 = 2;
	pIndices[13]._2 = 1;

	pIndices[14]._0 = 0;
	pIndices[14]._1 = 3;
	pIndices[14]._2 = 2;

	pIndices[15]._0 = 0;
	pIndices[15]._1 = 4;
	pIndices[15]._2 = 3;

	pIndices[16]._0 = 0;
	pIndices[16]._1 = 5;
	pIndices[16]._2 = 4;

	pIndices[17]._0 = 0;
	pIndices[17]._1 = 6;
	pIndices[17]._2 = 5;

	pIndices[18]._0 = 0;
	pIndices[18]._1 = 7;
	pIndices[18]._2 = 6;

	pIndices[19]._0 = 0;
	pIndices[19]._1 = 8;
	pIndices[19]._2 = 7;


	pIndices[20]._0 = 0; 
	pIndices[20]._1 = 9; 
	pIndices[20]._2 = 8;

	pIndices[21]._0 = 0;
	pIndices[21]._1 = 10; 
	pIndices[21]._2 = 9;

	pIndices[22]._0 = 0; 
	pIndices[22]._1 = 11; 
	pIndices[22]._2 = 10;

	pIndices[23]._0 = 0;
	pIndices[23]._1 = 12;
	pIndices[23]._2 = 11;


	memcpy(m_pIndices, pIndices, sizeof(FACELISTINDICES16) * m_iNumPrimitives);

	
	m_pIB->Unlock();
	return S_OK;
}

HRESULT CVIBuffer_Cone::NativeConstruct(void * pArg)
{
	if (FAILED(__super::NativeConstruct(pArg)))
		return E_FAIL;

	return S_OK;
}

CVIBuffer_Cone * CVIBuffer_Cone::Create(LPDIRECT3DDEVICE9 pGraphic_Device)
{
	CVIBuffer_Cone*	pInstance = new CVIBuffer_Cone(pGraphic_Device);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created CVIBuffer_Cone"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CComponent * CVIBuffer_Cone::Clone(void * pArg)
{
	CVIBuffer_Cone*	pInstance = new CVIBuffer_Cone(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CVIBuffer_Cone"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CVIBuffer_Cone::Free()
{
	__super::Free();
}
