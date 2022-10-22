#pragma once

#include "VIBuffer.h"

BEGIN(Engine)

class ENGINE_DLL CVIBuffer_Barricade2 final : public CVIBuffer
{
protected:
	explicit CVIBuffer_Barricade2(LPDIRECT3DDEVICE9 pGraphic_Device);
	explicit CVIBuffer_Barricade2(const CVIBuffer_Barricade2& rhs);
	virtual ~CVIBuffer_Barricade2() = default;

public:
	virtual HRESULT NativeConstruct_Prototype() override;
	virtual HRESULT NativeConstruct(void* pArg) override;

public:
	static CVIBuffer_Barricade2* Create(LPDIRECT3DDEVICE9 pGraphic_Device);
	virtual CComponent* Clone(void* pArg);
	virtual void Free() override;
};

END