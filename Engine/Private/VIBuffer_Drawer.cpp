#include "..\Public\VIBuffer_Drawer.h"



CVIBuffer_Drawer::CVIBuffer_Drawer(LPDIRECT3DDEVICE9 pGraphic_Device)
	:CVIBuffer(pGraphic_Device)
{
}

CVIBuffer_Drawer::CVIBuffer_Drawer(const CVIBuffer_Drawer & rhs)
	:CVIBuffer(rhs)
{
}

HRESULT CVIBuffer_Drawer::NativeConstruct_Prototype()
{
	if (FAILED(__super::NativeConstruct_Prototype()))
		return E_FAIL;

	m_iNumVertices = 40;
	m_iStride = sizeof(VTXOBJECTTEX);
	m_dwFVF = D3DFVF_XYZ | D3DFVF_DIFFUSE;
	m_ePrimitiveType = D3DPT_TRIANGLELIST;
	m_iNumPrimitives = 60;

	if (FAILED(Create_VertexBuffer()))
		return E_FAIL;

	m_pVertices = new VTXOBJECTTEX[m_iNumVertices];

	VTXOBJECTTEX*		pVertices = nullptr;

	m_pVB->Lock(0, 0/*m_iStride * m_iNumVertices*/, (void**)&pVertices, 0);

	//몸체
	pVertices[0].vPosition = _float3(-0.5f, 1.f, 0.05f);
	pVertices[0].vColor = 0xff532e08;

	pVertices[1].vPosition = _float3(0.5f, 1.f, 0.05f);
	pVertices[1].vColor = 0xff532e08;

	pVertices[2].vPosition = _float3(0.5f, 0.f, 0.05f);
	pVertices[2].vColor = 0xff532e08;

	pVertices[3].vPosition = _float3(-0.5f, 0.f, 0.05f);
	pVertices[3].vColor = 0xff532e08;

	pVertices[4].vPosition = _float3(-0.5f, 1.f, 0.4f);
	pVertices[4].vColor = 0xff532e08;

	pVertices[5].vPosition = _float3(0.5f, 1.f, 0.4f);
	pVertices[5].vColor = 0xff532e08;

	pVertices[6].vPosition = _float3(0.5f, 0.f, 0.4f);
	pVertices[6].vColor = 0xff532e08;;

	pVertices[7].vPosition = _float3(-0.5f, 0.f, 0.4f);
	pVertices[7].vColor = 0xff532e08;

	//1번서랍
	pVertices[8].vPosition = _float3(-0.4f, 0.96f, 0.f);
	pVertices[8].vColor = 0xff795A2B;

	pVertices[9].vPosition = _float3(0.4f, 0.96f, 0.f);
	pVertices[9].vColor = 0xff795A2B;

	pVertices[10].vPosition = _float3(0.4f, 0.76f, 0.f);
	pVertices[10].vColor = 0xff795A2B;

	pVertices[11].vPosition = _float3(-0.4f, 0.76f, 0.f);
	pVertices[11].vColor = 0xff795A2B;

	pVertices[12].vPosition = _float3(-0.4f, 0.96f, 0.05f);
	pVertices[12].vColor = 0xff795A2B;

	pVertices[13].vPosition = _float3(0.4f, 0.96f, 0.05f);
	pVertices[13].vColor = 0xff795A2B;

	pVertices[14].vPosition = _float3(0.4f, 0.76f, 0.05f);
	pVertices[14].vColor = 0xff795A2B;

	pVertices[15].vPosition = _float3(-0.4f, 0.76f, 0.05f);
	pVertices[15].vColor = 0xff795A2B;



	//2번서랍
	pVertices[16].vPosition = _float3(-0.4f, 0.72f, 0.f);
	pVertices[16].vColor = 0xff795A2B;

	pVertices[17].vPosition = _float3(0.4f, 0.72f, 0.f);
	pVertices[17].vColor = 0xff795A2B;

	pVertices[18].vPosition = _float3(0.4f, 0.52f, 0.f);
	pVertices[18].vColor = 0xff795A2B;

	pVertices[19].vPosition = _float3(-0.4f, 0.52f, 0.f);
	pVertices[19].vColor = 0xff795A2B;

	pVertices[20].vPosition = _float3(-0.4f, 0.72f, 0.05f);
	pVertices[20].vColor = 0xff795A2B;

	pVertices[21].vPosition = _float3(0.4f, 0.72f, 0.05f);
	pVertices[21].vColor = 0xff795A2B;

	pVertices[22].vPosition = _float3(0.4f, 0.52f, 0.05f);
	pVertices[22].vColor = 0xff795A2B;

	pVertices[23].vPosition = _float3(-0.4f, 0.52f, 0.05f);
	pVertices[23].vColor = 0xff795A2B;



	//3번서랍
	pVertices[24].vPosition = _float3(-0.4f, 0.48f, 0.f);
	pVertices[24].vColor = 0xff795A2B;

	pVertices[25].vPosition = _float3(0.4f, 0.48f, 0.f);
	pVertices[25].vColor = 0xff795A2B;

	pVertices[26].vPosition = _float3(0.4f, 0.28f, 0.f);
	pVertices[26].vColor = 0xff795A2B;

	pVertices[27].vPosition = _float3(-0.4f, 0.28f, 0.f);
	pVertices[27].vColor = 0xff795A2B;

	pVertices[28].vPosition = _float3(-0.4f, 0.48f, 0.05f);
	pVertices[28].vColor = 0xff795A2B;

	pVertices[29].vPosition = _float3(0.4f, 0.48f, 0.05f);
	pVertices[29].vColor = 0xff795A2B;

	pVertices[30].vPosition = _float3(0.4f, 0.28f, 0.05f);
	pVertices[30].vColor = 0xff795A2B;

	pVertices[31].vPosition = _float3(-0.4f, 0.28f, 0.05f);
	pVertices[31].vColor = 0xff795A2B;


	//4번서랍
	pVertices[32].vPosition = _float3(-0.4f, 0.24f, 0.f);
	pVertices[32].vColor = 0xff795A2B;

	pVertices[33].vPosition = _float3(0.4f, 0.24f, 0.f);
	pVertices[33].vColor = 0xff795A2B;

	pVertices[34].vPosition = _float3(0.4f, 0.04f, 0.f);
	pVertices[34].vColor = 0xff795A2B;

	pVertices[35].vPosition = _float3(-0.4f, 0.04f, 0.f);
	pVertices[35].vColor = 0xff795A2B;

	pVertices[36].vPosition = _float3(-0.4f, 0.24f, 0.05f);
	pVertices[36].vColor = 0xff795A2B;

	pVertices[37].vPosition = _float3(0.4f, 0.24f, 0.05f);
	pVertices[37].vColor = 0xff795A2B;

	pVertices[38].vPosition = _float3(0.4f, 0.04f, 0.05f);
	pVertices[38].vColor = 0xff795A2B;

	pVertices[39].vPosition = _float3(-0.4f, 0.04f, 0.05f);
	pVertices[39].vColor = 0xff795A2B;

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
	//몸체
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




	//1번서랍
	/* +x */
	pIndices[12]._0 = 9; pIndices[12]._1 = 13; pIndices[12]._2 = 14;
	pIndices[13]._0 = 9; pIndices[13]._1 = 14; pIndices[13]._2 = 10;

	/* -x */
	pIndices[14]._0 = 12; pIndices[14]._1 = 8; pIndices[14]._2 = 11;
	pIndices[15]._0 = 12; pIndices[15]._1 = 11; pIndices[15]._2 = 15;

	/* +y */
	pIndices[16]._0 = 12; pIndices[16]._1 = 13; pIndices[16]._2 = 9;
	pIndices[17]._0 = 12; pIndices[17]._1 = 9; pIndices[17]._2 = 8;

	/* -y */
	pIndices[18]._0 = 11; pIndices[18]._1 = 10; pIndices[18]._2 = 14;
	pIndices[19]._0 = 11; pIndices[19]._1 = 14; pIndices[19]._2 = 15;

	/* +z */
	pIndices[20]._0 = 13; pIndices[20]._1 = 12; pIndices[20]._2 = 15;
	pIndices[21]._0 = 13; pIndices[21]._1 = 15; pIndices[21]._2 = 14;

	/* -z */
	pIndices[22]._0 = 8; pIndices[22]._1 = 9; pIndices[22]._2 = 10;
	pIndices[23]._0 = 8; pIndices[23]._1 = 10; pIndices[23]._2 = 11;




	//2번서랍
	/* +x */
	pIndices[24]._0 = 17; pIndices[24]._1 = 21; pIndices[24]._2 = 22;
	pIndices[25]._0 = 17; pIndices[25]._1 = 22; pIndices[25]._2 = 18;

	/* -x */
	pIndices[26]._0 = 20; pIndices[26]._1 = 16; pIndices[26]._2 = 19;
	pIndices[27]._0 = 20; pIndices[27]._1 = 19; pIndices[27]._2 = 23;

	/* +y */
	pIndices[28]._0 = 20; pIndices[28]._1 = 21; pIndices[28]._2 = 17;
	pIndices[29]._0 = 20; pIndices[29]._1 = 17; pIndices[29]._2 = 16;

	/* -y */
	pIndices[30]._0 = 19; pIndices[30]._1 = 18; pIndices[30]._2 = 22;
	pIndices[31]._0 = 19; pIndices[31]._1 = 22; pIndices[31]._2 = 23;

	/* +z */
	pIndices[32]._0 = 21; pIndices[32]._1 = 20; pIndices[32]._2 = 23;
	pIndices[33]._0 = 21; pIndices[33]._1 = 23; pIndices[33]._2 = 22;

	/* -z */
	pIndices[34]._0 = 16; pIndices[34]._1 = 17; pIndices[34]._2 = 18;
	pIndices[35]._0 = 16; pIndices[35]._1 = 18; pIndices[35]._2 = 19;




	//3번서랍
	/* +x */
	pIndices[36]._0 = 25; pIndices[36]._1 = 29; pIndices[36]._2 = 30;
	pIndices[37]._0 = 25; pIndices[37]._1 = 30; pIndices[37]._2 = 26;

	/* -x */
	pIndices[38]._0 = 28; pIndices[38]._1 = 24; pIndices[38]._2 = 27;
	pIndices[39]._0 = 28; pIndices[39]._1 = 27; pIndices[39]._2 = 31;

	/* +y */
	pIndices[40]._0 = 28; pIndices[40]._1 = 29; pIndices[40]._2 = 25;
	pIndices[41]._0 = 28; pIndices[41]._1 = 25; pIndices[41]._2 = 24;

	/* -y */
	pIndices[42]._0 = 27; pIndices[42]._1 = 26; pIndices[42]._2 = 30;
	pIndices[43]._0 = 27; pIndices[43]._1 = 30; pIndices[43]._2 = 31;

	/* +z */
	pIndices[44]._0 = 29; pIndices[44]._1 = 28; pIndices[44]._2 = 31;
	pIndices[45]._0 = 29; pIndices[45]._1 = 31; pIndices[45]._2 = 30;

	/* -z */
	pIndices[46]._0 = 24; pIndices[46]._1 = 25; pIndices[46]._2 = 26;
	pIndices[47]._0 = 24; pIndices[47]._1 = 26; pIndices[47]._2 = 27;




	////4번서랍
	/* +x */
	pIndices[48]._0 = 33; pIndices[48]._1 = 37; pIndices[48]._2 = 38;
	pIndices[49]._0 = 33; pIndices[49]._1 = 38; pIndices[49]._2 = 34;

	/* -x */
	pIndices[50]._0 = 36; pIndices[50]._1 = 32; pIndices[50]._2 = 35;
	pIndices[51]._0 = 36; pIndices[51]._1 = 35; pIndices[51]._2 = 39;

	/* +y */
	pIndices[52]._0 = 36; pIndices[52]._1 = 37; pIndices[52]._2 = 33;
	pIndices[53]._0 = 36; pIndices[53]._1 = 33; pIndices[53]._2 = 32;

	/* -y */
	pIndices[54]._0 = 35; pIndices[54]._1 = 34; pIndices[54]._2 = 38;
	pIndices[55]._0 = 35; pIndices[55]._1 = 38; pIndices[55]._2 = 39;

	/* +z */
	pIndices[56]._0 = 37; pIndices[56]._1 = 36; pIndices[56]._2 = 39;
	pIndices[57]._0 = 37; pIndices[57]._1 = 39; pIndices[57]._2 = 38;

	/* -z */
	pIndices[58]._0 = 32; pIndices[58]._1 = 33; pIndices[58]._2 = 34;
	pIndices[59]._0 = 32; pIndices[59]._1 = 34; pIndices[59]._2 = 35;

	memcpy(m_pIndices, pIndices, sizeof(FACELISTINDICES16) * m_iNumPrimitives);


	m_pIB->Unlock();
	return S_OK;
}

HRESULT CVIBuffer_Drawer::NativeConstruct(void * pArg)
{
	if (FAILED(__super::NativeConstruct(pArg)))
		return E_FAIL;

	return S_OK;
}

CVIBuffer_Drawer * CVIBuffer_Drawer::Create(LPDIRECT3DDEVICE9 pGraphic_Device)
{
	CVIBuffer_Drawer*	pInstance = new CVIBuffer_Drawer(pGraphic_Device);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created CVIBuffer_Drawer"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CComponent * CVIBuffer_Drawer::Clone(void * pArg)
{
	CVIBuffer_Drawer*	pInstance = new CVIBuffer_Drawer(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CVIBuffer_Drawer"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CVIBuffer_Drawer::Free()
{
	__super::Free();
}
