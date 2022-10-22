#pragma once

#include "Component.h"

/* 객체의 월드상태를 표현하는 월드행렬을 가지고 있는다. */
/* 객체에게 필요한 월드 변환의 기능을 가진다. (직진, 후진, 회전 ) */

BEGIN(Engine)

class ENGINE_DLL CTransform final : public CComponent
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
	explicit CTransform(LPDIRECT3DDEVICE9 pGraphic_Device);
	explicit CTransform(const CTransform& rhs);
	virtual ~CTransform() = default;

public:
	_float3 Get_State(STATE eState) {
		return *(_float3*)&m_WorldMatrix.m[eState][0];
	}

	void Set_State(STATE eState, const _float3& vState) {
		memcpy(&m_WorldMatrix.m[eState][0], &vState, sizeof(_float3));
	}

	void Set_TransformState(const TRANSFORMDESC& TransformDesc) {
		m_TransformDesc = TransformDesc;
	}

	_float3 Get_Scale();

	_float4x4 Get_WorldMatrix() {
		return m_WorldMatrix;
	}

	_float4x4* Get_WorldMatrixRef() {
		return &m_WorldMatrix;
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

	HRESULT Scaled(_float3 vScale);
	HRESULT Scaling(_float fTimeDelta);
	HRESULT Axis_Scaling(const _float3 VDir, _float fTimeDelta);

	HRESULT Turn90(const _float3& vAxis);
	HRESULT Turn(const _float3& vAxis, _float fTimeDelta);
	HRESULT Chase(const _float3& vTargetPos, _float fTimeDelta, _float fLimitDistance = 1.f);
	HRESULT LookAt(const _float3& vTargetPos);

private:
	_float4x4			m_WorldMatrix;
	TRANSFORMDESC		m_TransformDesc;

public:
	static CTransform* Create(LPDIRECT3DDEVICE9 pGraphic_Device);
	virtual CComponent* Clone(void* pArg);
	virtual void Free() override;
};

END