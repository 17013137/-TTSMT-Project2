#pragma once

#include "Tool_Define.h"
#include "GameObject.h"

BEGIN(Engine)
class CTexture;
class CRenderer;
class CTransform;
class CVIBuffer_Cube;
class CSubTransform;
END


class CZombieSpitter final : public CGameObject
{
public:
	enum STATE { STATE_STAY, STATE_WALK, STATE_RUN, STATE_FIND, STATE_MOVE, STATE_ATTACK, STATE_FALLING, STATE_DOWN, STATE_UP, STATE_END };
private:
	
	explicit CZombieSpitter(LPDIRECT3DDEVICE9 pGraphic_Device);
	CZombieSpitter(const CZombieSpitter& rhs);
	virtual ~CZombieSpitter() = default;

public:
	virtual HRESULT NativeConstruct_Prototype();
	virtual HRESULT NativeConstruct(void* pArg);
	virtual void Tick(_float fTimeDelta);
	virtual void LateTick(_float fTimeDelta);
	virtual HRESULT Render();

public:
	_bool Picking(_float3* _pickpos);


private:
	CTransform*			m_pTransformCom = nullptr;
	CVIBuffer_Cube*		m_pVIBufferCom = nullptr;
	CTexture*			m_pTextureCom = nullptr;
	CRenderer*			m_pRendererCom = nullptr;
	//CTransform*			pTargetTransform = nullptr;
	vector<CVIBuffer_Cube*>		m_vVI;
	vector<CSubTransform*>		m_vTF;
	vector<CTexture*>			m_vTT;
	vector<CRenderer*>			m_vRD;
	_float	AnTime = 0.f;
	_float	PTime = 0.f;
	_float	StandardAnTime = 0.f;
	_float	AnFrame;
	STATE	State = STATE_STAY;
	_bool	Action = false;
	_bool	AttackOn = true;
	_bool	LockOn = false;
	_float3		vLook;
	_int		iTexture = 0;
	_float	delay = 0.f;

	_bool	MoveNo = false;
private:
	HRESULT SetUp_Components();
	HRESULT SetUp_OnTerrain();
	void Set_Part(int Part, int Local, _float3 Pos);
	void Set_Part2(int Part, _float3 Pos);
	void Set_Stay();

	void Attack(_float fTimeDelta);
public:
	static CZombieSpitter* Create(LPDIRECT3DDEVICE9 pGraphic_Device);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};
