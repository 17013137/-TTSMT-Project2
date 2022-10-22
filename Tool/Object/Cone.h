#pragma once

#include "Tool_Define.h"
#include "GameObject.h"

BEGIN(Engine)
class CRenderer;
class CTransform;
class CVIBuffer_Cone;
END

class CCone final : public CGameObject
{
private:
	explicit CCone(LPDIRECT3DDEVICE9 pGraphic_Device);
	CCone(const CCone& rhs);
	virtual ~CCone() = default;
public:
	virtual HRESULT NativeConstruct_Prototype();
	virtual HRESULT NativeConstruct(void* pArg);
	virtual void Tick(_float fTimeDelta);
	virtual void LateTick(_float fTimeDelta);
	virtual HRESULT Render();

private:
	/* �����δ�.(���¸� ǥ���Ѵ�.) */
	CTransform*			m_pTransformCom = nullptr;

	/* �������� �׸�����?! (��) */
	CVIBuffer_Cone*		m_pVIBufferCom = nullptr;

	/* �׸���!!! */
	CRenderer*			m_pRendererCom = nullptr;

private:
	HRESULT SetUp_Components();

public:
	_bool Picking(_float3* _pickpos);

public:
	static CCone* Create(LPDIRECT3DDEVICE9 pGraphic_Device);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};
