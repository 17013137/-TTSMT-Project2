#pragma once

#include "VIBuffer.h"

BEGIN(Engine)

class ENGINE_DLL CVIBuffer_Tile final : public CVIBuffer
{
protected:
	explicit CVIBuffer_Tile(LPDIRECT3DDEVICE9 pGraphic_Device);
	explicit CVIBuffer_Tile(const CVIBuffer_Tile& rhs);
	virtual ~CVIBuffer_Tile() = default;
public:
	virtual HRESULT NativeConstruct_Prototype() override;
	virtual HRESULT NativeConstruct(void* pArg) override;

public:

	static CVIBuffer_Tile* Create(LPDIRECT3DDEVICE9 pGraphic_Device);
	virtual CComponent* Clone(void* pArg);
	virtual void Free() override;
};

END