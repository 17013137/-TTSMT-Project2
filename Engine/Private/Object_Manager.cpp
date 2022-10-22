#include "..\Public\Object_Manager.h"
#include "GameObject.h"
#include "Layer.h"

IMPLEMENT_SINGLETON(CObject_Manager)

CObject_Manager::CObject_Manager()
{
}

CComponent * CObject_Manager::Get_Component(_uint iLevelIndex, const _tchar * pLayerTag, const _tchar * pComponentTag, _uint iIndex)
{
	if (iLevelIndex >= m_iNumLevels)
		return nullptr;

	CLayer*		pLayer = Find_Layer(iLevelIndex, pLayerTag);
	if (nullptr == pLayer)
		return nullptr;

	return pLayer->Get_Component(pComponentTag, iIndex);	
}

CGameObject * CObject_Manager::Get_Terrain(_uint iLevelIndex, const _tchar * pLayerTag)
{
	CLayer*		pLayer = Find_Layer(iLevelIndex, pLayerTag);
	if (nullptr == pLayer)
		return nullptr;

	return pLayer->Get_LayerList_First();
}

CGameObject * CObject_Manager::Get_Obj_in_Layer(CLayer * _layer, _uint iIndex)
{
	int temp = 0;
	for (auto& iter = _layer->m_ObjectList.begin(); iter != _layer->m_ObjectList.end(); iter++) {
		if (temp == iIndex) {
			return *iter;
		}

		temp++;
	}

	return nullptr;
}

HRESULT CObject_Manager::Reserve_Manager(_uint iNumLevels)
{
	if (0 != m_iNumLevels)
		return E_FAIL;

	m_pLayers = new LAYERS[iNumLevels];

	m_iNumLevels = iNumLevels;

	return S_OK;
}

HRESULT CObject_Manager::Add_Prototype(const _tchar * pPrototypeTag, CGameObject * pPrototype)
{
	if (nullptr == pPrototype || 
		nullptr != Find_Prototype(pPrototypeTag))
		return E_FAIL;

	m_Prototypes.insert(PROTOTYPES::value_type(pPrototypeTag, pPrototype));	

	return S_OK;
}

HRESULT CObject_Manager::Add_GameObjectToLayer(_uint iLevelIndex, const _tchar * pLayerTag, const _tchar * pPrototypeTag, void* pArg)
{
	CGameObject*	pPrototype = Find_Prototype(pPrototypeTag);
	if (nullptr == pPrototype)
		return E_FAIL;

	CGameObject*	pGameObject = pPrototype->Clone(pArg);
	if (nullptr == pGameObject)
		return E_FAIL;

	CLayer*	pLayer = Find_Layer(iLevelIndex, pLayerTag);

	if (nullptr == pLayer)
	{
		pLayer = CLayer::Create();
		if (nullptr == pLayer)
			return E_FAIL;

		if (FAILED(pLayer->Add_GameObject(pGameObject)))
			return E_FAIL;

		m_pLayers[iLevelIndex].insert(LAYERS::value_type(pLayerTag, pLayer));
	}
	else
		pLayer->Add_GameObject(pGameObject);

	return S_OK;
}

HRESULT CObject_Manager::Remove_Prototype_Object(const _tchar * pPrototypeTag)
{
	if (m_Prototypes.erase(pPrototypeTag) == 0)
		return E_FAIL;

	return S_OK;
}

HRESULT CObject_Manager::Remove_Layer_Object(_uint iLevelIndex, const _tchar * pLayerTag, _uint iIndex)
{
	if (m_pLayers == nullptr || m_pLayers[iLevelIndex].erase(pLayerTag) == 0)
		return E_FAIL;
	
	CLayer* _layer = Find_Layer(iLevelIndex, pLayerTag);
	if (_layer == nullptr)
		return E_FAIL;

	_layer->Remove_Object(iIndex);

	return S_OK;
}


HRESULT CObject_Manager::Clear_Layer_list(_uint iLevelIndex, const _tchar * pLayerTag)
{
	CLayer* temp = Find_Layer(iLevelIndex, pLayerTag);
	if (temp == nullptr)
		return E_FAIL;

	temp->Layer_Clear();
	return S_OK;
}

void CObject_Manager::Tick(_float fTimeDelta)
{
	for (_uint i = 0; i < m_iNumLevels; ++i)
	{
		for (auto& Pair : m_pLayers[i])
		{
			Pair.second->Tick(fTimeDelta);
		}
	}
}

void CObject_Manager::LateTick(_float fTimeDelta)
{
	for (_uint i = 0; i < m_iNumLevels; ++i)
	{
		for (auto& Pair : m_pLayers[i])
		{
			Pair.second->LateTick(fTimeDelta);
		}
	}
}

HRESULT CObject_Manager::Clear(_uint iLevelIndex)
{
	if (iLevelIndex >= m_iNumLevels)
		return E_FAIL;

	for (auto& Pair : m_pLayers[iLevelIndex])
		Safe_Release(Pair.second);

	m_pLayers[iLevelIndex].clear();

	return S_OK;
}

CGameObject * CObject_Manager::Find_Prototype(const _tchar * pPrototypeTag)
{
	auto	iter = find_if(m_Prototypes.begin(), m_Prototypes.end(), CTagFinder(pPrototypeTag));
	if (iter == m_Prototypes.end())
		return nullptr;

	return iter->second;	
}

CLayer * CObject_Manager::Find_Layer(_uint iLevelIndex, const _tchar * pLayerTag)
{
	if (iLevelIndex >= m_iNumLevels)
		return nullptr;

	auto	iter = find_if(m_pLayers[iLevelIndex].begin(), m_pLayers[iLevelIndex].end(), CTagFinder(pLayerTag));
	
	if (iter == m_pLayers[iLevelIndex].end())
		return nullptr;

	return iter->second;	
}

void CObject_Manager::Free()
{
	for (_uint i = 0; i < m_iNumLevels; ++i)
	{
		for (auto& Pair : m_pLayers[i])
			Safe_Release(Pair.second);
		m_pLayers[i].clear();
	}
	Safe_Delete_Array(m_pLayers);

	for (auto& Pair : m_Prototypes)
		Safe_Release(Pair.second);

	m_Prototypes.clear();
}
