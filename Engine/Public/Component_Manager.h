#pragma once

#include "Texture.h"
#include "Renderer.h"

#include "Transform.h"
#include "Engine_Obj_Header.h"

/* ������Ʈ���� ������ ��Ƶд�. */

BEGIN(Engine)

class CComponent_Manager final : public CBase
{
	DECLARE_SINGLETON(CComponent_Manager)
private:
	CComponent_Manager();
	virtual ~CComponent_Manager() = default;

public:
	HRESULT Reserve_Manager(_uint iNumLevels);
	HRESULT Add_Component_Prototype(_uint iLevelIndex, const _tchar* pPrototypeTag, CComponent* pPrototype);
	CComponent* Clone_Component(_uint iLevelIndex, const _tchar* pPrototypeTag, void* pArg);
	HRESULT Remove_Prototype_Component(_uint iLevelIndex, const _tchar* pPrototypeTag);

private:
	_uint											m_iNumLevels = 0;
	map<const _tchar*, CComponent*>*				m_pPrototypes = nullptr;
	typedef map<const _tchar*, CComponent*>			PROTOTYPES;

private:
	CComponent* Find_Prototype(_uint iLevelIndex, const _tchar* pPrototypeTag);

public:
	virtual void Free() override;
};

END