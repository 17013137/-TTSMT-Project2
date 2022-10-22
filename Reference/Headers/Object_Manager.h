#pragma once

#include "Base.h"
/*1. 내 게임에 사용될 객체(사본)들을 보관하고 관리한다. */
/*2. 원형객체들을 보관한다. */
/*3. 사본객체들의 갱신을 담당한다.(Tick함수호출) */

BEGIN(Engine)
class CLayer;
class CObject_Manager final : public CBase
{
	DECLARE_SINGLETON(CObject_Manager)
private:
	CObject_Manager();
	virtual ~CObject_Manager() = default;

public:
	class CComponent* Get_Component(_uint iLevelIndex, const _tchar* pLayerTag, const _tchar* pComponentTag, _uint iIndex = 0);
	class CGameObject* Get_Terrain(_uint iLevelIndex, const _tchar* pLayerTag);
	class CGameObject* Get_Obj_in_Layer(CLayer * _layer, _uint iIndex);

public:
	HRESULT Reserve_Manager(_uint iNumLevels);
	HRESULT Add_Prototype(const _tchar* pPrototypeTag, class CGameObject* pPrototype);
	HRESULT Add_GameObjectToLayer(_uint iLevelIndex, const _tchar* pLayerTag, const _tchar* pPrototypeTag, void* pArg);

	HRESULT Remove_Prototype_Object(const _tchar* pPrototypeTag);
	HRESULT Remove_Layer_Object(_uint iLevelIndex, const _tchar* pLayerTag, _uint iIndex);

	HRESULT Clear_Layer_list(_uint iLevelIndex, const _tchar* pLayerTag);

	void Tick(_float fTimeDelta);
	void LateTick(_float fTimeDelta);
	HRESULT Clear(_uint iLevelIndex);

public:
	/* 원형객체들을 보관한다. */
	map<const _tchar*, class CGameObject*>			m_Prototypes;
	typedef map<const _tchar*, class CGameObject*>	PROTOTYPES;
		
	
public:
	/* 사본객체들을 레이어로구분(니 맘대로)하여 보관한다.  */
	map<const _tchar*, CLayer*>*			m_pLayers = nullptr;
	typedef map<const _tchar*, CLayer*>		LAYERS;

private:
	_uint			m_iNumLevels = 0;

public:
	class CGameObject* Find_Prototype(const _tchar* pPrototypeTag);
	CLayer* Find_Layer(_uint iLevelIndex, const _tchar* pLayerTag);

public:
	virtual void Free() override;
};

END