#pragma once

#include "VIBuffer.h"

BEGIN(Engine)

class ENGINE_DLL CVIBuffer_Wall final : public CVIBuffer
{
protected:
	explicit CVIBuffer_Wall(LPDIRECT3DDEVICE9 pGraphic_Device);
	explicit CVIBuffer_Wall(const CVIBuffer_Wall& rhs);
	virtual ~CVIBuffer_Wall() = default;

public:
	virtual HRESULT NativeConstruct_Prototype() override;
	virtual HRESULT NativeConstruct(void* pArg) override;

public:
	static CVIBuffer_Wall* Create(LPDIRECT3DDEVICE9 pGraphic_Device);
	virtual CComponent* Clone(void* pArg);
	virtual void Free() override;
};

END