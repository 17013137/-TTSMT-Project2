#pragma once

#include "VIBuffer.h"

BEGIN(Engine)

class ENGINE_DLL CVIBuffer_Door final : public CVIBuffer
{
protected:
	explicit CVIBuffer_Door(LPDIRECT3DDEVICE9 pGraphic_Device);
	explicit CVIBuffer_Door(const CVIBuffer_Door& rhs);
	virtual ~CVIBuffer_Door() = default;

public:
	virtual HRESULT NativeConstruct_Prototype() override;
	virtual HRESULT NativeConstruct(void* pArg) override;

public:
	static CVIBuffer_Door* Create(LPDIRECT3DDEVICE9 pGraphic_Device);
	virtual CComponent* Clone(void* pArg);
	virtual void Free() override;
};

END