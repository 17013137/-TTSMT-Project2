#include "stdafx.h"
#include "ZombieSpitter.h"
#include "GameInstance.h"
#include<ctime>

CZombieSpitter::CZombieSpitter(LPDIRECT3DDEVICE9 pGraphic_Device)
	: CGameObject(pGraphic_Device)
{
}

CZombieSpitter::CZombieSpitter(const CZombieSpitter & rhs)
	: CGameObject(rhs)

{
}

HRESULT CZombieSpitter::NativeConstruct_Prototype()
{
	if (FAILED(__super::NativeConstruct_Prototype()))
		return E_FAIL;

	return S_OK;
}

HRESULT CZombieSpitter::NativeConstruct(void * pArg)
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
	m_pTransformCom->Set_State(CTransform::STATE_POSITION, _float3(temp.m[3][0], temp.m[3][1], temp.m[3][2]));
	
	iTexture = rand() % 2;
	return S_OK;
}

void CZombieSpitter::Tick(_float fTimeDelta)
{
	__super::Tick(fTimeDelta);

	Action = false;

}

void CZombieSpitter::LateTick(_float fTimeDelta)
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


	

	
	m_vRD[1]->Add_RenderGroup(CRenderer::GROUP_NONBLEND, this);
}

HRESULT CZombieSpitter::Render()
{
	if (FAILED(__super::Render()))
		return E_FAIL;

	//if (FAILED(m_pTextureCom->Bind_OnGraphicDevice(2)))
	//	return E_FAIL;

	if (FAILED(m_pTransformCom->Bind_OnGraphicDevice()))
		return E_FAIL;



	for (int i = 0; i < 9; ++i)
	{
		m_vTF[i]->Set_WorldMatrix(m_pTransformCom->Get_WorldMatrix());
	}
	//손발 파츠 상하체에 고정

	Set_Part2(4, m_vTF[8]->Get_StateWorld(CSubTransform::STATE_POSITION) + m_vTF[8]->Get_StateWorld(CSubTransform::STATE_RIGHT) / 1.8);
	Set_Part2(5, m_vTF[8]->Get_StateWorld(CSubTransform::STATE_POSITION) - m_vTF[8]->Get_StateWorld(CSubTransform::STATE_RIGHT) / 1.8);


	//어깨 각도 손으로 맞추기
	

	

	//골반 각도 발에 맞추기
	_float3 RF = m_vTF[4]->Get_StateWorld(CSubTransform::STATE_POSITION) + m_vTF[4]->Get_StateWorld(CSubTransform::STATE_RIGHT) * 2;
	_float3 RL = m_vTF[5]->Get_StateWorld(CSubTransform::STATE_POSITION) - m_vTF[5]->Get_StateWorld(CSubTransform::STATE_RIGHT) * 2;

	m_vTF[8]->LookRight(RF - RL);


	for (int i = 0; i < 2; ++i)
	{
		
		if (FAILED(m_vTT[i]->Bind_OnGraphicDevice(3)))
			return E_FAIL;

		if (FAILED(m_vTF[i]->Bind_OnGraphicDevice()))
			return E_FAIL;

		m_vVI[i]->Render();
	}
	for (int i = 4; i < 6; ++i)
	{

		if (FAILED(m_vTT[i]->Bind_OnGraphicDevice(3)))
			return E_FAIL;

		if (FAILED(m_vTF[i]->Bind_OnGraphicDevice()))
			return E_FAIL;

		m_vVI[i]->Render();
	}
	
		if (FAILED(m_vTT[8]->Bind_OnGraphicDevice(3)))
			return E_FAIL;

		if (FAILED(m_vTF[8]->Bind_OnGraphicDevice()))
			return E_FAIL;

		m_vVI[8]->Render();
	
	return S_OK;
}

_bool CZombieSpitter::Picking(_float3 * _pickpos)
{
	_float3	vOut;
	if (true == m_pVIBufferCom->Picking(m_pTransformCom, &vOut)) {
		D3DXVec3TransformCoord(&vOut, &vOut, &m_pTransformCom->Get_WorldMatrix());
		*_pickpos = vOut;
		return true;
	}

	return false;
}


HRESULT CZombieSpitter::SetUp_Components()
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



HRESULT CZombieSpitter::SetUp_OnTerrain()
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

void CZombieSpitter::Set_Part(int Part, int Local, _float3 Pos)
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

void CZombieSpitter::Set_Part2(int Part, _float3 Pos)
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

void CZombieSpitter::Set_Stay()
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
	
	//왼손
	

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
	
	//골반
	m_vTF[8]->Set_LocalMatrix(i);
	m_vTF[8]->Set_State(CSubTransform::STATE_POSITION, _float3(0.f, 0.f, -0.3f));
	m_vTF[8]->Scaled(_float3(0.65f, 0.18f, 0.3f));

}

void CZombieSpitter::Attack(_float fTimeDelta)
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

		AttackOn = true;
	}
	//반복
	_float Time = fTimeDelta* 72.f;
	RH = RH *Time;
	LH = LH*Time;
	OnB = OnB*Time;

	if (AnFrame < 40)
	{
		//손


		m_vTF[4]->Turn(_float3(1.f, 0.f, 0.f), 0.02f*Time);
		m_vTF[5]->Turn(_float3(1.f, 0.f, 0.f), 0.01f*Time);
		m_vTF[4]->Go_Y(-0.04f);
		m_vTF[5]->Go_Y(-0.04f);

		m_vTF[0]->Turn(_float3(1.f, 0.f, 0.f), -0.03f*Time);
		m_vTF[1]->Turn(_float3(1.f, 0.f, 0.f), -0.02f*Time);
		m_vTF[1]->Go_BackWard(0.05f*Time);
		m_vTF[1]->Go_Up(-0.03f*Time);
		m_vTF[5]->Go_Z(0.05f*Time);
		m_vTF[4]->Go_Z(-0.03f*Time);
	}

	else if (AnFrame >= 40 && AnFrame < 48)
	{
		//손

		m_vTF[4]->Turn(_float3(1.f, 0.f, 0.f), -0.13f*Time);
		m_vTF[5]->Turn(_float3(1.f, 0.f, 0.f), -0.07f*Time);
		m_vTF[4]->Go_Y(0.25f*Time);
		m_vTF[5]->Go_Y(0.25f*Time);
		//몸통
		m_vTF[0]->Turn(_float3(1.f, 0.f, 0.f), 0.2f*Time);
		m_vTF[1]->Turn(_float3(1.f, 0.f, 0.f), 0.11f*Time);
		m_vTF[1]->Go_Straight(0.3f*Time);
		m_vTF[1]->Go_Up(0.2f*Time);
		m_vTF[5]->Go_Z(-0.3f*Time);
		m_vTF[4]->Go_Z(0.2f*Time);
	}
	else if (AnFrame >= 48 && AnFrame < 64)
	{
		if (AttackOn)
		{
			CGameInstance*		pGameInstance = CGameInstance::GetInstance();
			Safe_AddRef(pGameInstance);

			m_vTF[4]->Turn(_float3(1.f, 0.f, 0.f), 0.01f*Time);
			m_vTF[5]->Turn(_float3(1.f, 0.f, 0.f), 0.005f*Time);
			m_vTF[4]->Go_Y(-0.02f*Time);
			m_vTF[5]->Go_Y(-0.02f*Time);

			m_vTF[0]->Turn(_float3(1.f, 0.f, 0.f), -0.015f*Time);
			m_vTF[1]->Turn(_float3(1.f, 0.f, 0.f), -0.01f*Time);
			m_vTF[1]->Go_BackWard(0.025f*Time);
			m_vTF[1]->Go_Up(-0.015f*Time);
			m_vTF[5]->Go_Z(0.025f*Time);
			m_vTF[4]->Go_Z(-0.015f*Time);
		}



		AnFrame += Time;

		if (AnFrame >= 64)
		{
			LockOn = false;
			AnFrame = 0;
			State = STATE_STAY;

		}
		Action = true;
	}
}

CZombieSpitter * CZombieSpitter::Create(LPDIRECT3DDEVICE9 pGraphic_Device)
{
	CZombieSpitter*	pInstance = new CZombieSpitter(pGraphic_Device);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created CZombieSpitter"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CZombieSpitter::Clone(void * pArg)
{
	CZombieSpitter*	pInstance = new CZombieSpitter(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CZombieSpitter"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CZombieSpitter::Free()
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


