#include "..\Public\VIBuffer_Window.h"



CVIBuffer_Window::CVIBuffer_Window(LPDIRECT3DDEVICE9 pGraphic_Device)
	:CVIBuffer(pGraphic_Device)
{
}

CVIBuffer_Window::CVIBuffer_Window(const CVIBuffer_Window & rhs)
	:CVIBuffer(rhs)
{
}

HRESULT CVIBuffer_Window::NativeConstruct_Prototype()
{
	if (FAILED(__super::NativeConstruct_Prototype()))
		return E_FAIL;

	m_iNumVertices = 24;
	m_iStride = sizeof(VTXOBJECTTEX);

	m_dwFVF = D3DFVF_XYZ | D3DFVF_DIFFUSE;
	m_ePrimitiveType = D3DPT_TRIANGLELIST;
	m_iNumPrimitives = 32;

	if (FAILED(Create_VertexBuffer()))
		return E_FAIL;

	m_pVertices = new VTXOBJECTTEX[m_iNumVertices];

	VTXOBJECTTEX*		pVertices = nullptr;

	m_pVB->Lock(0, 0/*m_iStride * m_iNumVertices*/, (void**)&pVertices, 0);

	//창문 안쪽
	pVertices[0].vPosition = _float3(-0.5f, 1.f, 0.4f);
	pVertices[0].vColor = 0xffffffff;

	pVertices[1].vPosition = _float3(-0.5f, 0.7f, 0.4f);
	pVertices[1].vColor = 0xffffffff;

	pVertices[2].vPosition = _float3(-0.5f, 0.3f, 0.4f);
	pVertices[2].vColor = 0xffffffff;

	pVertices[3].vPosition = _float3(-0.5f, 0.f, 0.4f);
	pVertices[3].vColor = 0xffffffff;

	pVertices[4].vPosition = _float3(0.5f, 0.f, 0.4f);
	pVertices[4].vColor = 0xffffffff;

	pVertices[5].vPosition = _float3(0.5f, 0.3f, 0.4f);
	pVertices[5].vColor = 0xffffffff;

	pVertices[6].vPosition = _float3(0.5f, 0.7f, 0.4f);
	pVertices[6].vColor = 0xffffffff;

	pVertices[7].vPosition = _float3(0.5f, 1.f, 0.4f);
	pVertices[7].vColor = 0xffffffff;

	pVertices[8].vPosition = _float3(-0.15f, 0.7f, 0.4f);
	pVertices[8].vColor = 0xffffffff;

	pVertices[9].vPosition = _float3(-0.15f, 0.3f, 0.4f);
	pVertices[9].vColor = 0xffffffff;

	pVertices[10].vPosition = _float3(0.15f, 0.3f, 0.4f);
	pVertices[10].vColor = 0xffffffff;

	pVertices[11].vPosition = _float3(0.15f, 0.7f, 0.4f);
	pVertices[11].vColor = 0xffffffff;

	//창문 뒷쪽
	pVertices[12].vPosition = _float3(-0.5f, 1.f, 0.5f);
	pVertices[12].vColor = 0xffbcbcbc;

	pVertices[13].vPosition = _float3(-0.5f, 0.7f, 0.5f);
	pVertices[13].vColor = 0xffbcbcbc;

	pVertices[14].vPosition = _float3(-0.5f, 0.3f, 0.5f);
	pVertices[14].vColor = 0xffbcbcbc;

	pVertices[15].vPosition = _float3(-0.5f, 0.f, 0.5f);
	pVertices[15].vColor = 0xffbcbcbc;

	pVertices[16].vPosition = _float3(0.5f, 0.f, 0.5f);
	pVertices[16].vColor = 0xffbcbcbc;

	pVertices[17].vPosition = _float3(0.5f, 0.3f, 0.5f);
	pVertices[17].vColor = 0xffbcbcbc;

	pVertices[18].vPosition = _float3(0.5f, 0.7f, 0.5f);
	pVertices[18].vColor = 0xffbcbcbc;

	pVertices[19].vPosition = _float3(0.5f, 1.f, 0.5f);
	pVertices[19].vColor = 0xffbcbcbc;

	pVertices[20].vPosition = _float3(-0.15f, 0.7f, 0.5f);
	pVertices[20].vColor = 0xffbcbcbc;

	pVertices[21].vPosition = _float3(-0.15f, 0.3f, 0.5f);
	pVertices[21].vColor = 0xffbcbcbc;

	pVertices[22].vPosition = _float3(0.15f, 0.3f, 0.5f);
	pVertices[22].vColor = 0xffbcbcbc;

	pVertices[23].vPosition = _float3(0.15f, 0.7f, 0.5f);
	pVertices[23].vColor = 0xffbcbcbc;
	
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
	
	pIndices[0]._0 = 0;
	pIndices[0]._1 = 7;
	pIndices[0]._2 = 6;

	pIndices[1]._0 = 0;
	pIndices[1]._1 = 6;
	pIndices[1]._2 = 1;

	pIndices[2]._0 = 1;
	pIndices[2]._1 = 8;
	pIndices[2]._2 = 9;

	pIndices[3]._0 = 1;
	pIndices[3]._1 = 9;
	pIndices[3]._2 = 2;

	pIndices[4]._0 = 2;
	pIndices[4]._1 = 5;
	pIndices[4]._2 = 4;

	pIndices[5]._0 = 2;
	pIndices[5]._1 = 4;
	pIndices[5]._2 = 3;

	pIndices[6]._0 = 11;
	pIndices[6]._1 = 6;
	pIndices[6]._2 = 5;

	pIndices[7]._0 = 11;
	pIndices[7]._1 = 5;
	pIndices[7]._2 = 10;

	pIndices[8]._0 = 19;
	pIndices[8]._1 = 12;
	pIndices[8]._2 = 13;

	pIndices[9]._0 = 19;
	pIndices[9]._1 = 13;
	pIndices[9]._2 = 18;

	pIndices[10]._0 = 20;
	pIndices[10]._1 = 13;
	pIndices[10]._2 = 14;

	pIndices[11]._0 = 20;
	pIndices[11]._1 = 14;
	pIndices[11]._2 = 21;

	pIndices[12]._0 = 17;
	pIndices[12]._1 = 14;
	pIndices[12]._2 = 15;

	pIndices[13]._0 = 17;
	pIndices[13]._1 = 15;
	pIndices[13]._2 = 16;

	pIndices[14]._0 = 18;
	pIndices[14]._1 = 23;
	pIndices[14]._2 = 22;

	pIndices[15]._0 = 18;
	pIndices[15]._1 = 22;
	pIndices[15]._2 = 17;

	pIndices[16]._0 = 8;
	pIndices[16]._1 = 11;
	pIndices[16]._2 = 23;

	pIndices[17]._0 = 8;
	pIndices[17]._1 = 23;
	pIndices[17]._2 = 20;

	pIndices[18]._0 = 8;
	pIndices[18]._1 = 20;
	pIndices[18]._2 = 21;

	pIndices[19]._0 = 8;
	pIndices[19]._1 = 21;
	pIndices[19]._2 = 9;

	pIndices[20]._0 = 21;
	pIndices[20]._1 = 22;
	pIndices[20]._2 = 10;

	pIndices[21]._0 = 21;
	pIndices[21]._1 = 10;
	pIndices[21]._2 = 9;

	pIndices[22]._0 = 23;
	pIndices[22]._1 = 11;
	pIndices[22]._2 = 10;

	pIndices[23]._0 = 23;
	pIndices[23]._1 = 10;
	pIndices[23]._2 = 22;

	pIndices[24]._0 = 12;
	pIndices[24]._1 = 0;
	pIndices[24]._2 = 3;

	pIndices[25]._0 = 12;
	pIndices[25]._1 = 3;
	pIndices[25]._2 = 15;

	pIndices[26]._0 = 3;
	pIndices[26]._1 = 4;
	pIndices[26]._2 = 16;

	pIndices[27]._0 = 3;
	pIndices[27]._1 = 16;
	pIndices[27]._2 = 15;

	pIndices[28]._0 = 7;
	pIndices[28]._1 = 19;
	pIndices[28]._2 = 16;

	pIndices[29]._0 = 7;
	pIndices[29]._1 = 16;
	pIndices[29]._2 = 4;

	pIndices[30]._0 = 12;
	pIndices[30]._1 = 19;
	pIndices[30]._2 = 7;

	pIndices[31]._0 = 12;
	pIndices[31]._1 = 7;
	pIndices[31]._2 = 0;

	memcpy(m_pIndices, pIndices, sizeof(FACELISTINDICES16) * m_iNumPrimitives);

	m_pIB->Unlock();
	return S_OK;
}

HRESULT CVIBuffer_Window::NativeConstruct(void * pArg)
{
	if (FAILED(__super::NativeConstruct(pArg)))
		return E_FAIL;

	return S_OK;
}

CVIBuffer_Window * CVIBuffer_Window::Create(LPDIRECT3DDEVICE9 pGraphic_Device)
{
	CVIBuffer_Window*	pInstance = new CVIBuffer_Window(pGraphic_Device);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created CVIBuffer_Window"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CComponent * CVIBuffer_Window::Clone(void * pArg)
{
	CVIBuffer_Window*	pInstance = new CVIBuffer_Window(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CVIBuffer_Window"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CVIBuffer_Window::Free()
{
	__super::Free();
}
