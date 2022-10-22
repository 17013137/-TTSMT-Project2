#include "..\Public\Layer.h"
#include "GameObject.h"


CLayer::CLayer()
{
}

CComponent * CLayer::Get_Component(const _tchar * pComponentTag, _uint iIndex)
{
	if (iIndex >= m_ObjectList.size())
		return nullptr;

	auto	iter = m_ObjectList.begin();

	for (_uint i = 0; i < iIndex; ++i)
		++iter;

	return (*iter)->Get_Component(pComponentTag);
}

CGameObject * CLayer::Get_LayerList_First()
{
	auto&	iter = m_ObjectList.begin();

	return *iter;
}

HRESULT CLayer::Remove_Object(_uint iIndex)
{
	if (m_ObjectList.begin() == m_ObjectList.end())
		return E_FAIL;

	auto iter = m_ObjectList.begin();
	for (_uint i = 0; i < iIndex; i++)
		iter++;

	m_ObjectList.erase(iter);

	return S_OK;
}

HRESULT CLayer::Add_GameObject(CGameObject * pGameObject)
{
	if (nullptr == pGameObject)
		return E_FAIL;

	m_ObjectList.push_back(pGameObject);

	return S_OK;
}

void CLayer::Tick(_float fTimeDelta)
{
	for (auto& pGameObject : m_ObjectList)
		pGameObject->Tick(fTimeDelta);

}

void CLayer::LateTick(_float fTimeDelta)
{
	for (auto& pGameObject : m_ObjectList)
		pGameObject->LateTick(fTimeDelta);
}

HRESULT CLayer::Layer_Clear()
{
	m_ObjectList.clear();

	return S_OK;
}

CLayer * CLayer::Create()
{
	return new CLayer();
}

void CLayer::Free()
{
	for (auto& pGameObject : m_ObjectList)
		Safe_Release(pGameObject);

	m_ObjectList.clear();

}
