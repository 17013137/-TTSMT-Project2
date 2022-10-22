#pragma once

#include "VIBuffer.h"

BEGIN(Engine)

class ENGINE_DLL CVIBuffer_Window final : public CVIBuffer
{
protected:
	explicit CVIBuffer_Window(LPDIRECT3DDEVICE9 pGraphic_Device);
	explicit CVIBuffer_Window(const CVIBuffer_Window& rhs);
	virtual ~CVIBuffer_Window() = default;

public:
	virtual HRESULT NativeConstruct_Prototype() override;
	virtual HRESULT NativeConstruct(void* pArg) override;

public:
	static CVIBuffer_Window* Create(LPDIRECT3DDEVICE9 pGraphic_Device);
	virtual CComponent* Clone(void* pArg);
	virtual void Free() override;
};

END