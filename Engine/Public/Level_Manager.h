#pragma once

#include "Base.h"

/* ���� ȭ�鿡 ��������ψd ������ �ּҸ� ������ �ִ´�. */
/* ���� ������ ƽ ����ȣ��. */
/* ���� ������ ���� ����ȣ��. */

BEGIN(Engine)

class CLevel_Manager final : public CBase
{
	DECLARE_SINGLETON(CLevel_Manager)
private:
	CLevel_Manager();
	virtual ~CLevel_Manager() = default;

public:
	HRESULT OpenLevel(_uint iLevelIndex, class CLevel* pLevel);
	void Tick(_float fTimeDelta); /* ũ�� �ǹ̴� ����. */
	HRESULT Render(); /* ũ�� �ǹ̴� ����. */

private:
	_uint					m_iLevelIndex = 0;
	class CLevel*			m_pCurrentLevel = nullptr;

public:
	virtual void Free() override;
};

END