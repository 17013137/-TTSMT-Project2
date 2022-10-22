#pragma once

#include "Component.h"

/* 객체의 월드상태를 표현하는 월드행렬을 가지고 있는다. */
/* 객체에게 필요한 월드 변환의 기능을 가진다. (직진, 후진, 회전 ) */

BEGIN(Engine)

class ENGINE_DLL CSubTransform final : public CComponent
{
public:
	enum STATE { STATE_RIGHT, STATE_UP, STATE_LOOK, STATE_POSITION, STATE_END };

public:
	typedef struct tagTransformDesc
	{
		_float		fSpeedPerSec;
		_float		fRotationPerSec;
		_float		fScalePerSec;
	}TRANSFORMDESC;


private:
	explicit CSubTransform(LPDIRECT3DDEVICE9 pGraphic_Device);
	explicit CSubTransform(const CSubTransform& rhs);
	virtual ~CSubTransform() = default;

public:
	_float3 Get_State(STATE eState) {
		return *(_float3*)&m_LocalMatrix.m[eState][0];
	}

	void Set_State(STATE eState, const _float3& vState) {
		memcpy(&m_LocalMatrix.m[eState][0], &vState, sizeof(_float3));
	}

	void Set_TransformState(const TRANSFORMDESC& TransformDesc) {
		m_TransformDesc = TransformDesc;
	}

	void Set_Speed(_float Speed) {
		m_TransformDesc.fSpeedPerSec = Speed;
	}

	_float4x4 Get_WorldMatrix() {
		return m_WorldMatrix;
	}

	_float4x4 Get_LocalMatrix() {
		return m_LocalMatrix;
	}
	_float3 Get_Scale();

	void Set_StateWorld(STATE eState, const _float3& vState) {
		memcpy(&m_WorldMatrix.m[eState][0], &vState, sizeof(_float3));
	}


	_float3 Get_StateWorld(STATE eState) {
		return *(_float3*)&m_WorldMatrix.m[eState][0];
	}

	void Set_WorldMatrix(_float4x4 WorldMatrix) {
		m_WorldMatrix = m_LocalMatrix * WorldMatrix;
	}

	void Set_LocalMatrix(_float4x4 LocalMatrix) {
		m_LocalMatrix = LocalMatrix;
	}

public:
	virtual HRESULT NativeConstruct_Prototype();
	virtual HRESULT NativeConstruct(void* pArg);

public:
	HRESULT Bind_OnGraphicDevice() const;

public:
	HRESULT Go_Straight(_float fTimeDelta);
	HRESULT Go_BackWard(_float fTimeDelta);
	HRESULT Go_Right(_float fTimeDelta);
	HRESULT Go_Left(_float fTimeDelta);
	HRESULT Go_Up(_float fTimeDelta);

	HRESULT Go_X(_float fTimeDelta);
	HRESULT Go_Y(_float fTimeDelta);
	HRESULT Go_Z(_float fTimeDelta);

	HRESULT Scaled(_float3 vScale);
	HRESULT Scaling(_float fTimeDelta);

	HRESULT Turn(const _float3& vAxis, _float fTimeDelta);
	HRESULT Chase(const _float3& vTargetPos, _float fTimeDelta, _float fLimitDistance = 1.f);
	HRESULT LookAt(const _float3& vTargetPos);
	HRESULT LookRight(const _float3& vTargetPos);
	HRESULT Look(const _float3& vTargetPos);
	HRESULT LookAtWorld(const _float3& vTargetPos);

private:
	_float4x4			m_LocalMatrix;
	_float4x4			m_WorldMatrix;
	TRANSFORMDESC		m_TransformDesc;

public:
	static CSubTransform* Create(LPDIRECT3DDEVICE9 pGraphic_Device);
	virtual CComponent* Clone(void* pArg);
	virtual void Free() override;
};

END