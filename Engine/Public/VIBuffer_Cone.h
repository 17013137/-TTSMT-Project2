#pragma once

#include "VIBuffer.h"

BEGIN(Engine)

class ENGINE_DLL CVIBuffer_Cone final : public CVIBuffer
{
protected:
	explicit CVIBuffer_Cone(LPDIRECT3DDEVICE9 pGraphic_Device);
	explicit CVIBuffer_Cone(const CVIBuffer_Cone& rhs);
	virtual ~CVIBuffer_Cone() = default;

public:
	virtual HRESULT NativeConstruct_Prototype() override;
	virtual HRESULT NativeConstruct(void* pArg) override;

public:
	static CVIBuffer_Cone* Create(LPDIRECT3DDEVICE9 pGraphic_Device);
	virtual CComponent* Clone(void* pArg);
	virtual void Free() override;
};

END