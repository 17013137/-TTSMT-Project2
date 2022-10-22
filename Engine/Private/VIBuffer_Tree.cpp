#include "..\Public\VIBuffer_Tree.h"



CVIBuffer_Tree::CVIBuffer_Tree(LPDIRECT3DDEVICE9 pGraphic_Device)
	:CVIBuffer(pGraphic_Device)
{
}

CVIBuffer_Tree::CVIBuffer_Tree(const CVIBuffer_Tree & rhs)
	:CVIBuffer(rhs)
{
}

HRESULT CVIBuffer_Tree::NativeConstruct_Prototype()
{
	if (FAILED(__super::NativeConstruct_Prototype()))
		return E_FAIL;

	m_iNumVertices = 22;
	m_iStride = sizeof(VTXOBJECTTEX);

	m_dwFVF = D3DFVF_XYZ | D3DFVF_DIFFUSE;
	m_ePrimitiveType = D3DPT_TRIANGLELIST;
	m_iNumPrimitives = 40;

	if (FAILED(Create_VertexBuffer()))
		return E_FAIL;

	m_pVertices = new VTXOBJECTTEX[m_iNumVertices];

	VTXOBJECTTEX*		pVertices = nullptr;

	m_pVB->Lock(0, 0/*m_iStride * m_iNumVertices*/, (void**)&pVertices, 0);

	//唱公 怖瘤痢
	pVertices[0].vPosition = _float3(0.f, 1.f, 0.f);
	pVertices[0].vColor = 0xff005500;

	//唱公 关窜
	pVertices[1].vPosition = _float3(-0.5f, 0.f, -0.01f);
	pVertices[1].vColor = 0xff005500;

	//唱公 关窜
	pVertices[2].vPosition = _float3(-0.28f, 0.f, -0.16f);
	pVertices[2].vColor = 0xff005500;

	//唱公 关窜
	pVertices[3].vPosition = _float3(-0.36f, 0.f, -0.36f);
	pVertices[3].vColor = 0xff005500;

	//唱公 关窜
	pVertices[4].vPosition = _float3(-0.16f, 0.f, -0.28f);
	pVertices[4].vColor = 0xff005500;

	//唱公 关窜
	pVertices[5].vPosition = _float3(-0.01f, 0.f, -0.5f);
	pVertices[5].vColor = 0xff005500;

	//唱公 关窜
	pVertices[6].vPosition = _float3(0.01f, 0.f, -0.5f);
	pVertices[6].vColor = 0xff005500;

	//唱公 关窜
	pVertices[7].vPosition = _float3(0.16f, 0.f, -0.28f);
	pVertices[7].vColor = 0xff005500;

	//唱公 关窜
	pVertices[8].vPosition = _float3(0.36f, 0.f, -0.36f);
	pVertices[8].vColor = 0xff005500;

	//唱公 关窜
	pVertices[9].vPosition = _float3(0.28f, 0.f, -0.16f);
	pVertices[9].vColor = 0xff005500;

	//唱公 关窜
	pVertices[10].vPosition = _float3(0.5f, 0.f, -0.01f);
	pVertices[10].vColor = 0xff005500;


	//唱公 关窜
	pVertices[11].vPosition = _float3(0.5f, 0.f, 0.01f);
	pVertices[11].vColor = 0xff005500;

	//唱公 关窜
	pVertices[12].vPosition = _float3(0.28f, 0.f, 0.16f);
	pVertices[12].vColor = 0xff005500;

	//唱公 关窜
	pVertices[13].vPosition = _float3(0.36f, 0.f, 0.36f);
	pVertices[13].vColor = 0xff005500;
					   
	//唱公 关窜	  
	pVertices[14].vPosition = _float3(0.16f, 0.f, 0.28f);
	pVertices[14].vColor = 0xff005500;
					   
	//唱公 关窜	  
	pVertices[15].vPosition = _float3(0.01f, 0.f, 0.5f);
	pVertices[15].vColor = 0xff005500;
					   
	//唱公 关窜	  
	pVertices[16].vPosition = _float3(-0.01f, 0.f, 0.5f);
	pVertices[16].vColor = 0xff005500;
					   
	//唱公 关窜	  
	pVertices[17].vPosition = _float3(-0.16f, 0.f, 0.28f);
	pVertices[17].vColor = 0xff005500;
					   
	//唱公 关窜	  
	pVertices[18].vPosition = _float3(-0.36f, 0.f, 0.36f);
	pVertices[18].vColor = 0xff005500;
	//唱公 关窜	  
	pVertices[19].vPosition = _float3(-0.28f, 0.f, 0.16f);
	pVertices[19].vColor = 0xff005500;

	//唱公 关窜
	pVertices[20].vPosition = _float3(-0.5f, 0.f, 0.01f);
	pVertices[20].vColor = 0xff005500;

	//唱公 关窜 吝缴痢
	pVertices[21].vPosition = _float3(0.f, 0.f, 0.f);
	pVertices[21].vColor = 0xff005500;
	
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
	
	//唱公酒贰
	pIndices[0]._0 = 1; 
	pIndices[0]._1 = 2; 
	pIndices[0]._2 = 21;

	pIndices[1]._0 = 2; 
	pIndices[1]._1 = 3; 
	pIndices[1]._2 = 21;

	pIndices[2]._0 = 3; 
	pIndices[2]._1 = 4; 
	pIndices[2]._2 = 21;

	pIndices[3]._0 = 4; 
	pIndices[3]._1 = 5; 
	pIndices[3]._2 = 21;

	pIndices[4]._0 = 5; 
	pIndices[4]._1 = 6; 
	pIndices[4]._2 = 21;

	pIndices[5]._0 = 6; 
	pIndices[5]._1 = 7; 
	pIndices[5]._2 = 21;

	pIndices[6]._0 = 7; 
	pIndices[6]._1 = 8; 
	pIndices[6]._2 = 21;

	pIndices[7]._0 = 8; 
	pIndices[7]._1 = 9; 
	pIndices[7]._2 = 21;

	pIndices[8]._0 = 9;
	pIndices[8]._1 = 10;
	pIndices[8]._2 = 21;

	pIndices[9]._0 = 10;
	pIndices[9]._1 = 11;
	pIndices[9]._2 = 21;

	pIndices[10]._0 = 11;
	pIndices[10]._1 = 12;
	pIndices[10]._2 = 21;

	pIndices[11]._0 = 12;
	pIndices[11]._1 = 13;
	pIndices[11]._2 = 21;

	pIndices[12]._0 = 13;
	pIndices[12]._1 = 14;
	pIndices[12]._2 = 21;

	pIndices[13]._0 = 14;
	pIndices[13]._1 = 15;
	pIndices[13]._2 = 21;

	pIndices[14]._0 = 15;
	pIndices[14]._1 = 16;
	pIndices[14]._2 = 21;

	pIndices[15]._0 = 16;
	pIndices[15]._1 = 17;
	pIndices[15]._2 = 21;

	pIndices[16]._0 = 17;
	pIndices[16]._1 = 18;
	pIndices[16]._2 = 21;

	pIndices[17]._0 = 18;
	pIndices[17]._1 = 19;
	pIndices[17]._2 = 21;

	pIndices[18]._0 = 19;
	pIndices[18]._1 = 20;
	pIndices[18]._2 = 21;

	pIndices[19]._0 = 20;
	pIndices[19]._1 = 1;
	pIndices[19]._2 = 21;

	//幌练
	pIndices[20]._0 = 0; 
	pIndices[20]._1 = 2; 
	pIndices[20]._2 = 1;

	pIndices[21]._0 = 0;
	pIndices[21]._1 = 3; 
	pIndices[21]._2 = 2;

	pIndices[22]._0 = 0; 
	pIndices[22]._1 = 4; 
	pIndices[22]._2 = 3;

	pIndices[23]._0 = 0;
	pIndices[23]._1 = 5;
	pIndices[23]._2 = 4;

	pIndices[24]._0 = 0;
	pIndices[24]._1 = 6;
	pIndices[24]._2 = 5;

	pIndices[25]._0 = 0;
	pIndices[25]._1 = 7;
	pIndices[25]._2 = 6;

	pIndices[26]._0 = 0;
	pIndices[26]._1 = 8;
	pIndices[26]._2 = 7;

	pIndices[27]._0 = 0;
	pIndices[27]._1 = 9;
	pIndices[27]._2 = 8;

	pIndices[28]._0 = 0;
	pIndices[28]._1 = 10;
	pIndices[28]._2 = 9;

	pIndices[29]._0 = 0;
	pIndices[29]._1 = 11;
	pIndices[29]._2 = 10;

	pIndices[30]._0 = 0;
	pIndices[30]._1 = 12;
	pIndices[30]._2 = 11;

	pIndices[31]._0 = 0;
	pIndices[31]._1 = 13;
	pIndices[31]._2 = 12;

	pIndices[32]._0 = 0;
	pIndices[32]._1 = 14;
	pIndices[32]._2 = 13;

	pIndices[33]._0 = 0;
	pIndices[33]._1 = 15;
	pIndices[33]._2 = 14;

	pIndices[34]._0 = 0;
	pIndices[34]._1 = 16;
	pIndices[34]._2 = 15;

	pIndices[35]._0 = 0;
	pIndices[35]._1 = 17;
	pIndices[35]._2 = 16;

	pIndices[36]._0 = 0;
	pIndices[36]._1 = 18;
	pIndices[36]._2 = 17;

	pIndices[37]._0 = 0;
	pIndices[37]._1 = 19;
	pIndices[37]._2 = 18;

	pIndices[38]._0 = 0;
	pIndices[38]._1 = 20;
	pIndices[38]._2 = 19;

	pIndices[39]._0 = 0;
	pIndices[39]._1 = 1;
	pIndices[39]._2 = 20;

	memcpy(m_pIndices, pIndices, sizeof(FACELISTINDICES16) * m_iNumPrimitives);
	
	m_pIB->Unlock();
	return S_OK;
}

HRESULT CVIBuffer_Tree::NativeConstruct(void * pArg)
{
	if (FAILED(__super::NativeConstruct(pArg)))
		return E_FAIL;

	return S_OK;
}

CVIBuffer_Tree * CVIBuffer_Tree::Create(LPDIRECT3DDEVICE9 pGraphic_Device)
{
	CVIBuffer_Tree*	pInstance = new CVIBuffer_Tree(pGraphic_Device);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created CVIBuffer_Tree"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CComponent * CVIBuffer_Tree::Clone(void * pArg)
{
	CVIBuffer_Tree*	pInstance = new CVIBuffer_Tree(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CVIBuffer_Tree"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CVIBuffer_Tree::Free()
{
	__super::Free();
}
