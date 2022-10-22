#pragma once

#include "GameObject.h"

BEGIN(Engine)

class ENGINE_DLL CBlendObject abstract : public CGameObject
{
protected:
	explicit CBlendObject(LPDIRECT3DDEVICE9 pGraphic_Device);
	CBlendObject(const CBlendObject& rhs);
	virtual ~CBlendObject() = default;

public:
	_float Get_CamDistance() const {
		return m_fCamDistance;
	}

public:
	virtual HRESULT NativeConstruct_Prototype();
	virtual HRESULT NativeConstruct(void* pArg);
	virtual void Tick(_float fTimeDelta);
	virtual void LateTick(_float fTimeDelta);
	virtual HRESULT Render();

protected:
	_float			m_fCamDistance = 0.f;

protected:
	void Compute_CamDistance(class CTransform* pTransform);


public:	
	virtual CGameObject* Clone(void* pArg) = 0;
	virtual void Free() override;
};

END