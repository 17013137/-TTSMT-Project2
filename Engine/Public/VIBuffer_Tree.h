#pragma once

#include "VIBuffer.h"

BEGIN(Engine)

class ENGINE_DLL CVIBuffer_Tree final : public CVIBuffer
{
protected:
	explicit CVIBuffer_Tree(LPDIRECT3DDEVICE9 pGraphic_Device);
	explicit CVIBuffer_Tree(const CVIBuffer_Tree& rhs);
	virtual ~CVIBuffer_Tree() = default;

public:
	virtual HRESULT NativeConstruct_Prototype() override;
	virtual HRESULT NativeConstruct(void* pArg) override;

public:
	static CVIBuffer_Tree* Create(LPDIRECT3DDEVICE9 pGraphic_Device);
	virtual CComponent* Clone(void* pArg);
	virtual void Free() override;
};

END