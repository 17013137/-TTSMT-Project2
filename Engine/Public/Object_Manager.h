#pragma once

#include "Base.h"
/*1. �� ���ӿ� ���� ��ü(�纻)���� �����ϰ� �����Ѵ�. */
/*2. ������ü���� �����Ѵ�. */
/*3. �纻��ü���� ������ ����Ѵ�.(Tick�Լ�ȣ��) */

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
	/* ������ü���� �����Ѵ�. */
	map<const _tchar*, class CGameObject*>			m_Prototypes;
	typedef map<const _tchar*, class CGameObject*>	PROTOTYPES;
		
	
public:
	/* �纻��ü���� ���̾�α���(�� �����)�Ͽ� �����Ѵ�.  */
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