#include "stdafx.h"
#include "GrandfaSkeleton.h"
#include "GameInstance.h"

CGrandfaSkeleton::CGrandfaSkeleton(LPDIRECT3DDEVICE9 pGraphic_Device)
	: CGameObject(pGraphic_Device)
{
}

CGrandfaSkeleton::CGrandfaSkeleton(const CGrandfaSkeleton & rhs)
	: CGameObject(rhs)

{
}

HRESULT CGrandfaSkeleton::NativeConstruct_Prototype()
{
	if (FAILED(__super::NativeConstruct_Prototype()))
		return E_FAIL;

	return S_OK;
}

HRESULT CGrandfaSkeleton::NativeConstruct(void * pArg)
{
	if (FAILED(__super::NativeConstruct(pArg)))
		return E_FAIL;
	if (FAILED(SetUp_Components()))
		return E_FAIL;
	_float4x4 temp;
	memcpy(temp, pArg, sizeof(_float4x4));
	m_pTransformCom->Set_State(CTransform::STATE_RIGHT, _float3(temp.m[0][0], temp.m[0][1], temp.m[0][2]));
	m_pTransformCom->Set_State(CTransform::STATE_UP, _float3(temp.m[1][0], temp.m[1][1], temp.m[1][2]));
	m_pTransformCom->Set_State(CTransform::STATE_LOOK, _float3(temp.m[2][0], temp.m[2][1], temp.m[2][2]));
	m_pTransformCom->Set_State(CTransform::STATE_POSITION, _float3(temp.m[3][0], temp.m[3][1]+0.5f, temp.m[3][2]));


	return S_OK;
}

void CGrandfaSkeleton::Tick(_float fTimeDelta)
{
	__super::Tick(fTimeDelta);


	if (Action == false)
	{
		Stay(fTimeDelta);
	}

}

void CGrandfaSkeleton::LateTick(_float fTimeDelta)
{
	__super::LateTick(fTimeDelta);

	//파츠별 위치 맞추기-------------------------------------------------------------
	_float3 Right;
	_float3 Up;
	_float3 Look;
	_float3 Pos;

	//어깨 위치 몸통에 맞추기
	Right = *D3DXVec3Normalize(&Right, &m_vTF[1]->Get_State(CSubTransform::STATE_RIGHT));
	Up = *D3DXVec3Normalize(&Up, &m_vTF[1]->Get_State(CSubTransform::STATE_UP));
	Look = *D3DXVec3Normalize(&Look, &m_vTF[1]->Get_State(CSubTransform::STATE_LOOK));
	Pos = m_vTF[1]->Get_State(CSubTransform::STATE_POSITION);
	m_vTF[6]->Set_State(CSubTransform::STATE_POSITION, Pos + (Right * 0.4f) + (Up * 0.25f));
	m_vTF[7]->Set_State(CSubTransform::STATE_POSITION, Pos + -(Right * 0.4f) + (Up * 0.25f));

	//머리 위치 몸통에 맞추기
	Up = *D3DXVec3Normalize(&Up, &m_vTF[1]->Get_State(CSubTransform::STATE_UP));
	Pos = m_vTF[1]->Get_State(CSubTransform::STATE_POSITION);
	m_vTF[0]->Set_State(CSubTransform::STATE_POSITION, Pos + Up / 1.5f + Look / 5.f);


	m_pRendererCom->Add_RenderGroup(CRenderer::GROUP_NONBLEND, this);

	for (int i = 0; i < 9; ++i)
	{
		m_vRD[i]->Add_RenderGroup(CRenderer::GROUP_NONBLEND, this);
	}

}

HRESULT CGrandfaSkeleton::Render()
{
	if (FAILED(__super::Render()))
		return E_FAIL;

	if (FAILED(m_pTextureCom->Bind_OnGraphicDevice(2)))
		return E_FAIL;

	if (FAILED(m_pTransformCom->Bind_OnGraphicDevice()))
		return E_FAIL;



	for (int i = 0; i < 9; ++i)
	{
		m_vTF[i]->Set_WorldMatrix(m_pTransformCom->Get_WorldMatrix());
	}
	//손발 파츠 상하체에 고정
	Set_Part(2, 1, m_vTF[6]->Get_StateWorld(CSubTransform::STATE_POSITION));
	Set_Part(3, 1, m_vTF[7]->Get_StateWorld(CSubTransform::STATE_POSITION));
	Set_Part2(4, m_vTF[8]->Get_StateWorld(CSubTransform::STATE_POSITION) + m_vTF[8]->Get_StateWorld(CSubTransform::STATE_RIGHT) / 1.8f);
	Set_Part2(5, m_vTF[8]->Get_StateWorld(CSubTransform::STATE_POSITION) - m_vTF[8]->Get_StateWorld(CSubTransform::STATE_RIGHT) / 1.8f);


	//어깨 각도 손으로 맞추기
	m_vTF[6]->LookAtWorld(m_vTF[2]->Get_StateWorld(CSubTransform::STATE_POSITION));
	m_vTF[7]->LookAtWorld(m_vTF[3]->Get_StateWorld(CSubTransform::STATE_POSITION));

	m_vTF[2]->LookAtWorld(m_vTF[6]->Get_StateWorld(CSubTransform::STATE_POSITION));
	m_vTF[3]->LookAtWorld(m_vTF[7]->Get_StateWorld(CSubTransform::STATE_POSITION));

	//골반 각도 발에 맞추기
	_float3 RF = m_vTF[4]->Get_StateWorld(CSubTransform::STATE_POSITION) + m_vTF[4]->Get_StateWorld(CSubTransform::STATE_RIGHT) * 2;
	_float3 RL = m_vTF[5]->Get_StateWorld(CSubTransform::STATE_POSITION) - m_vTF[5]->Get_StateWorld(CSubTransform::STATE_RIGHT) * 2;
	
	m_vTF[8]->LookRight(RF - RL);


	for (int i = 0; i < 9; ++i)
	{

		if (FAILED(m_vTT[i]->Bind_OnGraphicDevice(15)))
			return E_FAIL;

		if (FAILED(m_vTF[i]->Bind_OnGraphicDevice()))
			return E_FAIL;

		m_vVI[i]->Render();
	}

	return S_OK;
}

_bool CGrandfaSkeleton::Picking(_float3 * _pickpos)
{
	_float3	vOut;
	if (true == m_pVIBufferCom->Picking(m_pTransformCom, &vOut)) {
		D3DXVec3TransformCoord(&vOut, &vOut, &m_pTransformCom->Get_WorldMatrix());
		*_pickpos = vOut;
		return true;
	}

	return false;
}

HRESULT CGrandfaSkeleton::SetUp_Components()
{
	/* For.Com_Transform */
	CTransform::TRANSFORMDESC		TransformDesc;
	ZeroMemory(&TransformDesc, sizeof(CTransform::TRANSFORMDESC));

	TransformDesc.fSpeedPerSec = 10.f;
	TransformDesc.fRotationPerSec = D3DXToRadian(90.0f);
	TransformDesc.fScalePerSec = 1.f;

	if (FAILED(__super::SetUp_Components(TEXT("Com_Transform"), STAGE_STATIC, TEXT("Prototype_Component_Transform"), (CComponent**)&m_pTransformCom, &TransformDesc)))
		return E_FAIL;

	/* For.Com_Renderer */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Renderer"), STAGE_STATIC, TEXT("Prototype_Component_Renderer"), (CComponent**)&m_pRendererCom)))
		return E_FAIL;

	/* For.Com_VIBuffer */
	if (FAILED(__super::SetUp_Components(TEXT("Com_VIBuffer"), STAGE_SCENE, TEXT("Prototype_Component_VIBuffer_Cube"), (CComponent**)&m_pVIBufferCom)))
		return E_FAIL;

	/* For.Com_Texture */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Texture"), STAGE_SCENE, TEXT("Prototype_Component_Texture_Cube"), (CComponent**)&m_pTextureCom)))
		return E_FAIL;

	CVIBuffer_Cube*		m_CubeVI = nullptr;
	CSubTransform*		m_CubeTF = nullptr;
	CTexture*			m_CubeTT = nullptr;
	CRenderer*			m_CubeRD = nullptr;

	_tchar		szPath1[10][MAX_PATH] = { TEXT(""),TEXT(""),TEXT(""),TEXT(""),TEXT(""),TEXT(""),TEXT(""),TEXT(""),TEXT("") };
	_tchar		szPath2[10][MAX_PATH] = { TEXT(""),TEXT(""),TEXT(""),TEXT(""),TEXT(""),TEXT(""),TEXT(""),TEXT(""),TEXT("") };
	_tchar		szPath3[10][MAX_PATH] = { TEXT(""),TEXT(""),TEXT(""),TEXT(""),TEXT(""),TEXT(""),TEXT(""),TEXT(""),TEXT("") };
	_tchar		szPath4[10][MAX_PATH] = { TEXT(""),TEXT(""),TEXT(""),TEXT(""),TEXT(""),TEXT(""),TEXT(""),TEXT(""),TEXT("") };

	for (int i = 0; i < 10; ++i)
	{
		wsprintf(szPath1[i], TEXT("Com_Transform_%d"), i);
		if (FAILED(__super::SetUp_Components(szPath1[i], STAGE_STATIC, TEXT("Prototype_Component_SubTransform"), (CComponent**)&m_CubeTF)))
			return E_FAIL;
		m_vTF.push_back(m_CubeTF);

		wsprintf(szPath2[i], TEXT("Com_Renderer_%d"), i);
		if (FAILED(__super::SetUp_Components(szPath2[i], STAGE_STATIC, TEXT("Prototype_Component_Renderer"), (CComponent**)&m_CubeRD)))
			return E_FAIL;
		m_vRD.push_back(m_CubeRD);

		wsprintf(szPath3[i], TEXT("Com_VIBuffer_%d"), i);
		if (FAILED(__super::SetUp_Components(szPath3[i], STAGE_SCENE, TEXT("Prototype_Component_VIBuffer_Cube"), (CComponent**)&m_CubeVI)))
			return E_FAIL;
		m_vVI.push_back(m_CubeVI);

		wsprintf(szPath4[i], TEXT("Com_CTexture_%d"), i);
		if (FAILED(__super::SetUp_Components(szPath4[i], STAGE_SCENE, TEXT("Prototype_Component_Texture_Cube"), (CComponent**)&m_CubeTT)))
			return E_FAIL;
		m_vTT.push_back(m_CubeTT);
	}
	Set_Stay();



	return S_OK;
}



HRESULT CGrandfaSkeleton::SetUp_OnTerrain()
{
	CGameInstance*			pGameInstance = CGameInstance::GetInstance();
	Safe_AddRef(pGameInstance);

	_float RF = m_vTF[4]->Get_State(CSubTransform::STATE_POSITION).y;
	_float LF = m_vTF[5]->Get_State(CSubTransform::STATE_POSITION).y;

	_float3		vPosition = m_pTransformCom->Get_State(CTransform::STATE_POSITION);



	CVIBuffer_Terrain*		pTerrainBuffer = (CVIBuffer_Terrain*)pGameInstance->Get_Component(STAGE_SCENE, TEXT("Layer_BackGround"), TEXT("Com_VIBuffer"));
	if (nullptr == pTerrainBuffer)
		return E_FAIL;

	CTransform*		pTerrainTransform = (CTransform*)pGameInstance->Get_Component(STAGE_SCENE, TEXT("Layer_BackGround"), TEXT("Com_Transform"));
	if (nullptr == pTerrainTransform)
		return E_FAIL;

	if (RF < LF)
	{
		vPosition.y = pTerrainBuffer->Compute_Height(pTerrainTransform, vPosition).y - RF + 0.5f;
	}

	else if (RF >= LF)
	{
		vPosition.y = pTerrainBuffer->Compute_Height(pTerrainTransform, vPosition).y - LF + 0.5f;
	}



	m_pTransformCom->Set_State(CTransform::STATE_POSITION, vPosition);



	Safe_Release(pGameInstance);
	return S_OK;
}

void CGrandfaSkeleton::Set_Part(int Part, int Local, _float3 Pos)
{
	_float4x4	MX;
	D3DXMatrixIdentity(&MX);
	_float3  Ri = m_vTF[Local]->Get_StateWorld(CSubTransform::STATE_RIGHT);
	_float3  Up = m_vTF[Local]->Get_StateWorld(CSubTransform::STATE_UP);
	_float3  Lo = m_vTF[Local]->Get_StateWorld(CSubTransform::STATE_LOOK);
	D3DXVec3Normalize(&Ri, &Ri);
	D3DXVec3Normalize(&Up, &Up);
	D3DXVec3Normalize(&Lo, &Lo);
	memcpy(&MX.m[0][0], &Ri, sizeof(_float3));
	memcpy(&MX.m[1][0], &Up, sizeof(_float3));
	memcpy(&MX.m[2][0], &Lo, sizeof(_float3));
	memcpy(&MX.m[3][0], &Pos, sizeof(_float3));
	m_vTF[Part]->Set_WorldMatrix(MX);

}

void CGrandfaSkeleton::Set_Part2(int Part, _float3 Pos)
{
	_float4x4	MX;
	D3DXMatrixIdentity(&MX);
	_float3  Ri = m_pTransformCom->Get_State(CTransform::STATE_RIGHT);
	_float3  Up = m_pTransformCom->Get_State(CTransform::STATE_UP);
	_float3  Lo = m_pTransformCom->Get_State(CTransform::STATE_LOOK);
	D3DXVec3Normalize(&Ri, &Ri);
	D3DXVec3Normalize(&Up, &Up);
	D3DXVec3Normalize(&Lo, &Lo);
	memcpy(&MX.m[0][0], &Ri, sizeof(_float3));
	memcpy(&MX.m[1][0], &Up, sizeof(_float3));
	memcpy(&MX.m[2][0], &Lo, sizeof(_float3));
	memcpy(&MX.m[3][0], &Pos, sizeof(_float3));
	m_vTF[Part]->Set_WorldMatrix(MX);

}

void CGrandfaSkeleton::Set_Stay()
{
	_float4x4 i;
	D3DXMatrixIdentity(&i);


	
	//머리
	m_vTF[0]->Set_LocalMatrix(i);
	m_vTF[0]->Scaled(_float3(0.5f, 0.5f, 0.5f));
	m_vTF[0]->Turn(_float3(1.f, 0.f, 0.f), 1.f);

	//몸통
	m_vTF[1]->Set_LocalMatrix(i);
	m_vTF[1]->Set_State(CSubTransform::STATE_POSITION, _float3(0.f, 0.55f, 0.f));
	m_vTF[1]->Scaled(_float3(0.7f, 0.8f, 0.4f));
	m_vTF[1]->Turn(_float3(1.f, 0.f, 0.f), 0.7f);
	//오른손
	m_vTF[2]->Set_LocalMatrix(i);
	m_vTF[2]->Set_State(CSubTransform::STATE_POSITION, _float3(0.15f, -0.4f, 0.5f));
	m_vTF[2]->Scaled(_float3(0.3f, 0.3f, 0.3f));
	m_vTF[2]->Turn(_float3(0.f, 0.f, 1.f), 5.f);
	//왼손
	m_vTF[3]->Set_LocalMatrix(i);
	m_vTF[3]->Set_State(CSubTransform::STATE_POSITION, _float3(-0.15f, -0.4f, 0.5f));
	m_vTF[3]->Scaled(_float3(0.3f, 0.3f, 0.3f));
	m_vTF[3]->Turn(_float3(0.f, 0.f, 1.f), -5.f);

	//오른발
	m_vTF[4]->Set_LocalMatrix(i);
	m_vTF[4]->Set_State(CSubTransform::STATE_POSITION, _float3(0.f, -0.5f, 0.1f));
	m_vTF[4]->Scaled(_float3(0.4f, 0.3f, 0.6f));
	m_vTF[4]->Turn(_float3(0.f, 1.f, 0.f), 0.15f);
	//왼발
	m_vTF[5]->Set_LocalMatrix(i);
	m_vTF[5]->Set_State(CSubTransform::STATE_POSITION, _float3(0.f, -0.5f, 0.1f));
	m_vTF[5]->Scaled(_float3(0.4f, 0.3f, 0.6f));
	m_vTF[5]->Turn(_float3(0.f, 1.f, 0.f), -0.15f);

	//어꺠
	m_vTF[6]->Set_LocalMatrix(i);
	m_vTF[6]->Scaled(_float3(0.25f, 0.25f, 0.25f));

	m_vTF[7]->Set_LocalMatrix(i);
	m_vTF[7]->Scaled(_float3(0.25f, 0.25f, 0.25f));

	//골반
	m_vTF[8]->Set_LocalMatrix(i);
	m_vTF[8]->Set_State(CSubTransform::STATE_POSITION, _float3(0.f, 0.f, -0.3f));
	m_vTF[8]->Scaled(_float3(0.65f, 0.18f, 0.3f));

}

void CGrandfaSkeleton::Attack(_float fTimeDelta)
{
	_float3 RH = _float3(0.005f, 0.055f, 0.015f);
	_float3 LH = _float3(-0.005f, 0.055f, 0.015f);
	_float3 OnB = _float3(0.0f, 0.0f, 0.13f);
	if (State != STATE_ATTACK)
	{
		Set_Stay();
		State = STATE_ATTACK;
		StandardAnTime = 0.f;
		AnTime = 0.f;
		AnFrame = 0;
		m_vTF[4]->Go_Z(-3.f);
		m_vTF[2]->Set_State(CSubTransform::STATE_POSITION, _float3(0.05f, -0.6f, 0.5f));
		m_vTF[3]->Set_State(CSubTransform::STATE_POSITION, _float3(-0.05f, -0.6f, 0.5f));
		
	}
	//반복
	if (AnFrame < 50)
	{
		//손

		m_vTF[2]->Set_State(CSubTransform::STATE_POSITION, m_vTF[2]->Get_State(CSubTransform::STATE_POSITION) + RH/2 );
		m_vTF[3]->Set_State(CSubTransform::STATE_POSITION, m_vTF[3]->Get_State(CSubTransform::STATE_POSITION) + LH/2 );
		m_vTF[4]->Turn(_float3(1.f, 0.f, 0.f), 0.02f);
		m_vTF[5]->Turn(_float3(1.f, 0.f, 0.f), 0.01f);
		m_vTF[4]->Go_Y(-0.04f);
		m_vTF[5]->Go_Y(-0.04f);

		m_vTF[0]->Turn(_float3(1.f, 0.f, 0.f), -0.03f);
		m_vTF[1]->Turn(_float3(1.f, 0.f, 0.f), -0.02f);
		m_vTF[1]->Go_BackWard(0.05f);
		m_vTF[1]->Go_Up(-0.03f);
		m_vTF[5]->Go_Z(0.05f);
		m_vTF[4]->Go_Z(-0.03f);
	}

	else if (AnFrame >= 50 && AnFrame < 60)
	{
		//손
		m_vTF[2]->Set_State(CSubTransform::STATE_POSITION, m_vTF[2]->Get_State(CSubTransform::STATE_POSITION) - RH * 2.5);
		m_vTF[3]->Set_State(CSubTransform::STATE_POSITION, m_vTF[3]->Get_State(CSubTransform::STATE_POSITION) - LH * 2.5);
		m_vTF[4]->Turn(_float3(1.f, 0.f, 0.f), -0.1f);
		m_vTF[5]->Turn(_float3(1.f, 0.f, 0.f), -0.05f);
		m_vTF[4]->Go_Y(0.2f);
		m_vTF[5]->Go_Y(0.2f);
		//몸통
		m_vTF[0]->Turn(_float3(1.f, 0.f, 0.f), 0.15f);
		m_vTF[1]->Turn(_float3(1.f, 0.f, 0.f), 0.1f);
		m_vTF[1]->Go_Straight(0.25f);
		m_vTF[1]->Go_Up(0.15f);
		m_vTF[5]->Go_Z(-0.25f);
		m_vTF[4]->Go_Z(0.15f);
	}
	else
	{
		
	}



	++AnFrame;

	if (AnFrame == 80)
	{
		AnFrame = 0;
	}
	Action = true;
}

void CGrandfaSkeleton::find(_float fTimeDelta)
{

	_float4x4 Rot, Far, Loc, End;
	if (State != STATE_FIND)
	{
		Set_Stay();
		State = STATE_FIND;
		StandardAnTime = 0.f;
		AnTime = 0.f;

		D3DXMatrixRotationAxis(&Rot, &_float3(0.f, 1.f, 0.f), -0.5f);
		D3DXMatrixTranslation(&Far, 0.f, 0.f, 0.f);
		m_vTF[0]->Turn(_float3(1.f, 0.f, 0.f), D3DXToRadian(-50.f));
		m_vTF[1]->Turn(_float3(1.f, 0.f, 0.f), D3DXToRadian(-20.f));
		m_vTF[0]->Turn(_float3(0.f, 1.f, 0.f), -0.8f);
		m_vTF[1]->Turn(_float3(0.f, 1.f, 0.f), -0.4f);
	}
	StandardAnTime += fTimeDelta;

	if (AnTime + 5.f < StandardAnTime)
		AnTime = StandardAnTime;

	_float Ang;

	if (AnTime + 0.5f > StandardAnTime)
	{
		Ang = 0.025f;

	}
	else if (AnTime + 2.5f > StandardAnTime && AnTime + 0.5f <= StandardAnTime)
	{
		Ang = -0.001f;
	}
	else if (AnTime + 3.f > StandardAnTime && AnTime + 2.5f <= StandardAnTime)
	{
		Ang = -0.025f;
	}

	else
		Ang = 0.001f;


	m_vTF[0]->Turn(_float3(0.f, 1.f, 0.f), Ang*2);
	m_vTF[1]->Turn(_float3(0.f, 1.f, 0.f), Ang);
	m_vTF[1]->Set_Speed(Ang * 2);
	m_vTF[1]->Go_Up(fTimeDelta);

	m_vTF[2]->Set_Speed(Ang * 2);
	m_vTF[2]->Go_Up(fTimeDelta);

	m_vTF[3]->Set_Speed(Ang * 2);
	m_vTF[3]->Go_Up(fTimeDelta);


}

void CGrandfaSkeleton::Crawl(_float fTimeDelta)
{
	//움직이는 속도
	_float3 RH = _float3(-0.004f, 0.03f, 0.03f);
	_float3 LH = _float3(0.004f, 0.03f, 0.03f);
	_float3 RF = _float3(-0.004f, 0.03f, 0.03f);
	_float3 OnF = _float3(0.0f, 0.0f, 0.13f);
	_float3 UpF = _float3(0.0f, 0.03f, -0.03f);
	_float3 DownF = _float3(0.0f, -0.03f, 0.03f);
	_float3 DownFCompensation = _float3(0.0f, 0.09f, 0.0f);

	//준비
	if (State != STATE_RUN)
	{
		Set_Stay();
		State = STATE_RUN;
		StandardAnTime = 0.f;
		AnTime = 0.f;
		AnFrame = 0;

		m_vTF[0]->Turn(_float3(1.f, 0.f, 0.f), -0.8f);
		//몸통
		m_vTF[1]->Set_Speed(0.1f);
		m_vTF[1]->Turn(_float3(1.f, 0.f, 0.f), 0.5f);
		m_vTF[1]->Go_Straight(3.f);
		m_vTF[1]->Turn(_float3(0.f, 1.f, 0.f), -0.6f);


		//손
		m_vTF[2]->Set_Speed(0.1f);
		m_vTF[2]->Set_State(CSubTransform::STATE_POSITION, m_vTF[2]->Get_State(CSubTransform::STATE_POSITION) + RH * 20);

		m_vTF[3]->Set_Speed(0.1f);
		m_vTF[3]->Set_State(CSubTransform::STATE_POSITION, m_vTF[3]->Get_State(CSubTransform::STATE_POSITION) - LH * 10);

		//발
		m_vTF[4]->Set_Speed(0.1f);
		m_vTF[4]->Set_State(CSubTransform::STATE_POSITION, m_vTF[4]->Get_State(CSubTransform::STATE_POSITION) - (OnF * 6) + (UpF * 3));
		m_vTF[4]->Turn(_float3(1.f, 0.f, 0.f), 0.9f);

		m_vTF[5]->Set_Speed(0.1f);
		m_vTF[5]->Set_State(CSubTransform::STATE_POSITION, m_vTF[5]->Get_State(CSubTransform::STATE_POSITION) + (OnF * 6) + (DownF * 3) + DownFCompensation);

	}


	//반복
	if (AnFrame < 15)
	{
		//손

		m_vTF[2]->Set_State(CSubTransform::STATE_POSITION, m_vTF[2]->Get_State(CSubTransform::STATE_POSITION) - RH * 2);
		m_vTF[3]->Set_State(CSubTransform::STATE_POSITION, m_vTF[3]->Get_State(CSubTransform::STATE_POSITION) + LH * 2);

		//발
		if (AnFrame < 12)
		{
			m_vTF[4]->Set_State(CSubTransform::STATE_POSITION, m_vTF[4]->Get_State(CSubTransform::STATE_POSITION) + (OnF));
			m_vTF[4]->Turn(_float3(1.f, 0.f, 0.f), -0.15f);
			m_vTF[5]->Set_State(CSubTransform::STATE_POSITION, m_vTF[5]->Get_State(CSubTransform::STATE_POSITION) - (OnF));
		}
		if (AnFrame >= 12)
		{
			m_vTF[4]->Set_State(CSubTransform::STATE_POSITION, m_vTF[4]->Get_State(CSubTransform::STATE_POSITION) + (DownF));
			m_vTF[5]->Set_State(CSubTransform::STATE_POSITION, m_vTF[5]->Get_State(CSubTransform::STATE_POSITION) + (UpF));
			m_vTF[4]->Turn(_float3(1.f, 0.f, 0.f), 0.3f);
			m_vTF[5]->Turn(_float3(1.f, 0.f, 0.f), 0.3f);
		}
		//몸통
		m_vTF[1]->Turn(_float3(0.f, 1.f, 0.f), 0.08f);
	}

	if (AnFrame >= 15)
	{
		//손
		m_vTF[2]->Set_State(CSubTransform::STATE_POSITION, m_vTF[2]->Get_State(CSubTransform::STATE_POSITION) + RH * 2);
		m_vTF[3]->Set_State(CSubTransform::STATE_POSITION, m_vTF[3]->Get_State(CSubTransform::STATE_POSITION) - LH * 2);


		if (AnFrame < 27)
		{
			m_vTF[4]->Set_State(CSubTransform::STATE_POSITION, m_vTF[4]->Get_State(CSubTransform::STATE_POSITION) - (OnF));
			m_vTF[5]->Set_State(CSubTransform::STATE_POSITION, m_vTF[5]->Get_State(CSubTransform::STATE_POSITION) + (OnF));
			m_vTF[5]->Turn(_float3(1.f, 0.f, 0.f), -0.15f);
		}
		if (AnFrame >= 27)
		{
			m_vTF[4]->Set_State(CSubTransform::STATE_POSITION, m_vTF[4]->Get_State(CSubTransform::STATE_POSITION) + (UpF));
			m_vTF[5]->Set_State(CSubTransform::STATE_POSITION, m_vTF[5]->Get_State(CSubTransform::STATE_POSITION) + (DownF));
			m_vTF[4]->Turn(_float3(1.f, 0.f, 0.f), 0.3f);
			m_vTF[5]->Turn(_float3(1.f, 0.f, 0.f), 0.3f);
		}
		//몸통
		m_vTF[1]->Turn(_float3(0.f, 1.f, 0.f), -0.08f);
	}




	++AnFrame;

	if (AnFrame == 30)
	{
		AnFrame = 0;
	}
	Action = true;
}

void CGrandfaSkeleton::Walk(_float fTimeDelta)
{
	//움직이는 속도
	_float3 RH = _float3(-0.0015f, 0.01f, 0.01f);
	_float3 LH = _float3(0.0015f, 0.01f, 0.01f);
	_float3 RF = _float3(-0.004f, 0.03f, 0.03f);
	_float3 OnF = _float3(0.0f, 0.0f, 0.05f) / 2.f;
	_float3 UpF = _float3(0.0f, 0.03f, -0.02f) / 2.f;
	_float3 DownF = _float3(0.0f, -0.03f, 0.02f) / 2.f;
	_float3 DownFCompensation = _float3(0.0f, 0.09f, 0.0f) / 2.f;

	//준비
	if (State != STATE_WALK)
	{
		Set_Stay();
		State = STATE_WALK;
		StandardAnTime = 0.f;
		AnTime = 0.f;
		AnFrame = 0;


		m_vTF[0]->Turn(_float3(1.f, 0.f, 0.f), -0.8f);


		//손
		m_vTF[2]->Set_Speed(0.1f);
		m_vTF[2]->Set_State(CSubTransform::STATE_POSITION, _float3(0.15f, -0.f, 0.5f));
		m_vTF[2]->Set_State(CSubTransform::STATE_POSITION, m_vTF[2]->Get_State(CSubTransform::STATE_POSITION) + RH * 20);

		m_vTF[3]->Set_Speed(0.1f);
		m_vTF[3]->Set_State(CSubTransform::STATE_POSITION, _float3(-0.15f, -0.4f, 0.5f));
		m_vTF[3]->Set_State(CSubTransform::STATE_POSITION, m_vTF[3]->Get_State(CSubTransform::STATE_POSITION) - LH * 10);

		//몸통
		m_vTF[1]->Set_Speed(0.1f);

		//발
		m_vTF[4]->Set_Speed(0.1f);
		m_vTF[4]->Set_State(CSubTransform::STATE_POSITION, m_vTF[4]->Get_State(CSubTransform::STATE_POSITION) - (OnF * 6) + (UpF * 3));

		m_vTF[5]->Set_Speed(0.1f);
		m_vTF[5]->Set_State(CSubTransform::STATE_POSITION, m_vTF[5]->Get_State(CSubTransform::STATE_POSITION) + (OnF * 6) + (DownF * 3) + DownFCompensation);
		m_vTF[4]->Turn(_float3(1.f, 0.f, 0.f), 0.6f);

	}


	//반복

	if (AnFrame < 30)
	{
		//발
		if (AnFrame < 24)
		{
			m_vTF[4]->Set_State(CSubTransform::STATE_POSITION, m_vTF[4]->Get_State(CSubTransform::STATE_POSITION) + (OnF));
			m_vTF[4]->Turn(_float3(1.f, 0.f, 0.f), -0.05f);
			m_vTF[5]->Set_State(CSubTransform::STATE_POSITION, m_vTF[5]->Get_State(CSubTransform::STATE_POSITION) - (OnF));
		}
		if (AnFrame >= 24)
		{
			m_vTF[4]->Set_State(CSubTransform::STATE_POSITION, m_vTF[4]->Get_State(CSubTransform::STATE_POSITION) + (DownF));
			m_vTF[5]->Set_State(CSubTransform::STATE_POSITION, m_vTF[5]->Get_State(CSubTransform::STATE_POSITION) + (UpF));
			m_vTF[4]->Turn(_float3(1.f, 0.f, 0.f), 0.1f);
			m_vTF[5]->Turn(_float3(1.f, 0.f, 0.f), 0.1f);

		}
		//몸통
		m_vTF[1]->Turn(_float3(0.f, 1.f, 0.f), 0.01f);
	}

	if (AnFrame >= 30)
	{
		//발
		if (AnFrame < 54)
		{
			m_vTF[4]->Set_State(CSubTransform::STATE_POSITION, m_vTF[4]->Get_State(CSubTransform::STATE_POSITION) - (OnF));
			m_vTF[5]->Set_State(CSubTransform::STATE_POSITION, m_vTF[5]->Get_State(CSubTransform::STATE_POSITION) + (OnF));
			m_vTF[5]->Turn(_float3(1.f, 0.f, 0.f), -0.05f);
		}
		if (AnFrame >= 54)
		{
			m_vTF[4]->Set_State(CSubTransform::STATE_POSITION, m_vTF[4]->Get_State(CSubTransform::STATE_POSITION) + (UpF));
			m_vTF[5]->Set_State(CSubTransform::STATE_POSITION, m_vTF[5]->Get_State(CSubTransform::STATE_POSITION) + (DownF));
			m_vTF[4]->Turn(_float3(1.f, 0.f, 0.f), 0.1f);
			m_vTF[5]->Turn(_float3(1.f, 0.f, 0.f), 0.1f);
		}
		//몸통
		m_vTF[1]->Turn(_float3(0.f, 1.f, 0.f), -0.01f);

	}




	++AnFrame;

	if (AnFrame == 60)
	{
		AnFrame = 0;
	}
	Action = true;
}

void CGrandfaSkeleton::Move(_float fTimeDelta)
{
	//움직이는 속도
	_float3 RH = _float3(-0.0015f, 0.01f, 0.01f);
	_float3 LH = _float3(0.0015f, 0.01f, 0.01f);
	_float3 RF = _float3(-0.004f, 0.03f, 0.03f);
	_float3 OnF = _float3(0.0f, 0.0f, 0.05f) / 2.f;
	_float3 UpF = _float3(0.0f, 0.03f, -0.02f) / 2.f;
	_float3 DownF = _float3(0.0f, -0.03f, 0.02f) / 2.f;
	_float3 DownFCompensation = _float3(0.0f, 0.09f, 0.0f) / 2.f;

	//준비
	if (State != STATE_WALK)
	{
		Set_Stay();
		State = STATE_WALK;
		StandardAnTime = 0.f;
		AnTime = 0.f;
		AnFrame = 0;


		


		

		//몸통
		m_vTF[1]->Set_Speed(0.1f);

		//발
		m_vTF[4]->Set_Speed(0.1f);
		m_vTF[4]->Set_State(CSubTransform::STATE_POSITION, m_vTF[4]->Get_State(CSubTransform::STATE_POSITION) - (OnF * 3) + (UpF * 3));

		m_vTF[5]->Set_Speed(0.1f);
		m_vTF[5]->Set_State(CSubTransform::STATE_POSITION, m_vTF[5]->Get_State(CSubTransform::STATE_POSITION) + (OnF * 3) + (DownF * 3) + DownFCompensation);
		m_vTF[4]->Turn(_float3(1.f, 0.f, 0.f), 0.6f);

	}


	//반복

	if (AnFrame < 30)
	{
		//발
		if (AnFrame < 24)
		{
			m_vTF[4]->Set_State(CSubTransform::STATE_POSITION, m_vTF[4]->Get_State(CSubTransform::STATE_POSITION) + (OnF/2));
			m_vTF[4]->Turn(_float3(1.f, 0.f, 0.f), -0.05f);
			m_vTF[5]->Set_State(CSubTransform::STATE_POSITION, m_vTF[5]->Get_State(CSubTransform::STATE_POSITION) - (OnF/2));
		}
		if (AnFrame >= 24)
		{
			m_vTF[4]->Set_State(CSubTransform::STATE_POSITION, m_vTF[4]->Get_State(CSubTransform::STATE_POSITION) + (DownF));
			m_vTF[5]->Set_State(CSubTransform::STATE_POSITION, m_vTF[5]->Get_State(CSubTransform::STATE_POSITION) + (UpF));
			m_vTF[4]->Turn(_float3(1.f, 0.f, 0.f), 0.1f);
			m_vTF[5]->Turn(_float3(1.f, 0.f, 0.f), 0.1f);

		}
		//몸통
		m_vTF[1]->Turn(_float3(0.f, 1.f, 0.f), 0.01f);
	}

	if (AnFrame >= 30)
	{
		//발
		if (AnFrame < 54)
		{
			m_vTF[4]->Set_State(CSubTransform::STATE_POSITION, m_vTF[4]->Get_State(CSubTransform::STATE_POSITION) - (OnF/2));
			m_vTF[5]->Set_State(CSubTransform::STATE_POSITION, m_vTF[5]->Get_State(CSubTransform::STATE_POSITION) + (OnF/2));
			m_vTF[5]->Turn(_float3(1.f, 0.f, 0.f), -0.05f);
		}
		if (AnFrame >= 54)
		{
			m_vTF[4]->Set_State(CSubTransform::STATE_POSITION, m_vTF[4]->Get_State(CSubTransform::STATE_POSITION) + (UpF));
			m_vTF[5]->Set_State(CSubTransform::STATE_POSITION, m_vTF[5]->Get_State(CSubTransform::STATE_POSITION) + (DownF));
			m_vTF[4]->Turn(_float3(1.f, 0.f, 0.f), 0.1f);
			m_vTF[5]->Turn(_float3(1.f, 0.f, 0.f), 0.1f);
		}
		//몸통
		m_vTF[1]->Turn(_float3(0.f, 1.f, 0.f), -0.01f);

	}




	++AnFrame;

	if (AnFrame == 60)
	{
		AnFrame = 0;
	}
	Action = true;
}

void CGrandfaSkeleton::Stay(_float fTimeDelta)
{

	_float4x4 Rot, Far, Loc, End;
	if (State != STATE_STAY)
	{
		Set_Stay();
		State = STATE_STAY;
		StandardAnTime = 0.f;
		AnTime = 0.f;

		D3DXMatrixRotationAxis(&Rot, &_float3(0.f, 1.f, 0.f), -0.5f);
		D3DXMatrixTranslation(&Far, 0.f, 0.f, 0.f);
		Loc = m_vTF[0]->Get_LocalMatrix();
		End = Loc * Rot * Far;
		m_vTF[0]->Set_LocalMatrix(End);
	}
	StandardAnTime += fTimeDelta;

	if (AnTime + 3.f < StandardAnTime)
		AnTime = StandardAnTime;

	_float Ang;

	if (AnTime + 1.5f > StandardAnTime)
	{
		Ang = 0.03f;

	}
	else
		Ang = -0.03f;

	D3DXMatrixRotationAxis(&Rot, &_float3(0.f, 1.f, 0.f), Ang / 5);
	D3DXMatrixTranslation(&Far, 0.f, 0.f, 0.f);
	Loc = m_vTF[0]->Get_LocalMatrix();
	End = Loc * Rot * Far;
	m_vTF[0]->Set_LocalMatrix(End);

	m_vTF[1]->Set_Speed(Ang * 2);
	m_vTF[1]->Go_Up(fTimeDelta);

	m_vTF[2]->Set_Speed(Ang * 2);
	m_vTF[2]->Go_Up(fTimeDelta);

	m_vTF[3]->Set_Speed(Ang * 2);
	m_vTF[3]->Go_Up(fTimeDelta);


}


CGrandfaSkeleton * CGrandfaSkeleton::Create(LPDIRECT3DDEVICE9 pGraphic_Device)
{
	CGrandfaSkeleton*	pInstance = new CGrandfaSkeleton(pGraphic_Device);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to First Created CGrandfaSkeleton"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CGrandfaSkeleton::Clone(void * pArg)
{
	CGrandfaSkeleton*	pInstance = new CGrandfaSkeleton(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Clone Created CGrandfaSkeleton"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CGrandfaSkeleton::Free()
{
	__super::Free();

	for (auto& pGameObject : m_vVI)
		Safe_Release(pGameObject);

	m_vVI.clear();

	for (auto& pGameObject : m_vTF)
		Safe_Release(pGameObject);

	m_vTF.clear();

	for (auto& pGameObject : m_vTT)
		Safe_Release(pGameObject);

	m_vTT.clear();

	for (auto& pGameObject : m_vRD)
		Safe_Release(pGameObject);

	m_vRD.clear();

	Safe_Release(m_pTransformCom);
	Safe_Release(m_pTextureCom);
	Safe_Release(m_pVIBufferCom);
	Safe_Release(m_pRendererCom);

}


