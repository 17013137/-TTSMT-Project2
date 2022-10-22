#pragma once

#include "VIBuffer.h"

BEGIN(Engine)

class ENGINE_DLL CVIBuffer_Drawer final : public CVIBuffer
{
protected:
	explicit CVIBuffer_Drawer(LPDIRECT3DDEVICE9 pGraphic_Device);
	explicit CVIBuffer_Drawer(const CVIBuffer_Drawer& rhs);
	virtual ~CVIBuffer_Drawer() = default;

public:
	virtual HRESULT NativeConstruct_Prototype() override;
	virtual HRESULT NativeConstruct(void* pArg) override;

public:
	static CVIBuffer_Drawer* Create(LPDIRECT3DDEVICE9 pGraphic_Device);
	virtual CComponent* Clone(void* pArg);
	virtual void Free() override;
};

END