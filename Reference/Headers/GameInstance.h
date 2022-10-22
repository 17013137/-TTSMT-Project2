#pragma once

#include "Graphic_Device.h"
#include "Input_Device.h"
#include "Level_Manager.h"
#include "Object_Manager.h"
#include "Component_Manager.h"
#include "Timer_Manager.h"
#include "Picking.h"


/* 클라이언트에 보여줘야할 인터페이스를 보관하고. 보여준다. */

BEGIN(Engine)

class ENGINE_DLL CGameInstance final : public CBase
{
	DECLARE_SINGLETON(CGameInstance)
private:
	CGameInstance();
	virtual ~CGameInstance() = default;

public: /* For.GameInstance */
	HRESULT Initialize_Engine(HINSTANCE hInst, _uint iNumLevels, CGraphic_Device::GRAPHICDESC GraphicDesc, LPDIRECT3DDEVICE9* ppGraphic_Device);
	void Tick_Engine(_float fTimeDelta);
	HRESULT Render_Engine();	
	HRESULT Clear_LevelResource(_uint iLevelIndex);


public: /* For.Graphic_Device */	
	void Render_Begin(void);
	void Render_End();

public: /* For.Input_Device */
	_char Get_DIKeyState(_uchar byKeyID);
	_char Get_DIMButtonState(CInput_Device::MOUSEBUTTONSTATE eDIMBState);
	_long Get_DIMMoveState(CInput_Device::MOUSEMOVESTATE eDIMMState);

public: /* For.Timer_Manager */
	HRESULT Add_Timers(const _tchar* pTimerTag);
	_double Compute_TimeDelta(const _tchar* pTimerTag);

public: /* For.Level_Manager */
	HRESULT Open_Level(_uint iLevelIndex, class CLevel* pLevel);

public: /* For.Object_Manager */
	CComponent* Get_Component(_uint iLevelIndex, const _tchar* pLayerTag, const _tchar* pComponentTag, _uint iIndex = 0);
	CLayer* Get_GameObejct_Layer(_uint iLevelIndex, const _tchar* pLayerTag);
	HRESULT Add_Prototype(const _tchar* pPrototypeTag, class CGameObject* pPrototype);
	HRESULT Add_GameObjectToLayer(_uint iLevelIndex, const _tchar* pLayerTag, const _tchar* pPrototypeTag, void* pArg = nullptr);
	HRESULT Remove_Prototype_Object(const _tchar* pPrototypeTag);
	HRESULT Remove_Layer_Object(CLayer* _layer, _uint iIndex);
	HRESULT Clear_Layer_list(_uint iLevelIndex, const _tchar* pLayerTag);

	class CGameObject* Get_Terrain(_uint iLevelIndex, const _tchar* pLayerTag);
	class CGameObject* Get_Obj_in_Layer(CLayer* _layer, _uint iIndex);

public: /* For.Component_Manager */
	HRESULT Add_Component_Prototype(_uint iLevelIndex, const _tchar* pPrototypeTag, CComponent* pPrototype);
	CComponent* Clone_Component(_uint iLevelIndex, const _tchar* pPrototypeTag, void* pArg = nullptr);
	HRESULT Remove_Prototype_Component(_uint iLevelIndex, const _tchar* pPrototypeTag);

	//Mouse Picking

public:
	CGraphic_Device*			m_pGraphic_Device = nullptr;
	CInput_Device*				m_pInput_Device = nullptr;
	CLevel_Manager*				m_pLevel_Manager = nullptr;
	CObject_Manager*			m_pObject_Manager = nullptr;
	CComponent_Manager*			m_pComponent_Manager = nullptr;
	CTimer_Manager*				m_pTimer_Manager = nullptr;
	CPicking*					m_pPicking = nullptr;


public:
	static void Release_Engine();
	virtual void Free() override;
};

END