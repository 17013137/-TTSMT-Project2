#include "stdafx.h"
#include "Camera_Default.h"
#include "GameInstance.h"

#include "MainFrm.h"
#include "ToolView.h"
#include "MenuView.h"
#include "TabDlg.h"
#include "Tab2.h"

CCamera_Default::CCamera_Default(LPDIRECT3DDEVICE9 pGraphic_Device)
	: CCamera(pGraphic_Device)
{
}

CCamera_Default::CCamera_Default(const CCamera_Default & rhs)
	: CCamera(rhs)
{
}

HRESULT CCamera_Default::NativeConstruct_Prototype()
{
	if (FAILED(__super::NativeConstruct_Prototype()))
		return E_FAIL;

	return S_OK;
}

HRESULT CCamera_Default::NativeConstruct(void * pArg)
{
	if (FAILED(__super::NativeConstruct(pArg)))
		return E_FAIL;

	CMainFrame* mainFrm = dynamic_cast<CMainFrame*>(AfxGetMainWnd());
	CToolView* toolView = dynamic_cast<CToolView*>(mainFrm->m_MainSplitter.GetPane(0, 1));
	CMenuView* menuView = dynamic_cast<CMenuView*>(mainFrm->m_MainSplitter.GetPane(0, 0));
	CTabDlg* tabDlg = &(menuView->m_TabDlg);
	tab = tabDlg->pDlg2;

	return S_OK;
}

void CCamera_Default::Tick(_float fTimeDelta)
{
	CGameInstance*		pGameInstance = CGameInstance::GetInstance();

	Safe_AddRef(pGameInstance);

	if (tab->m_Camera_Set == false) {
		if (GetKeyState(VK_UP) & 0x8000)
		{
			m_pTransform->Go_Straight(fTimeDelta);
		}
		if (GetKeyState(VK_DOWN) & 0x8000)
		{
			m_pTransform->Go_BackWard(fTimeDelta);
		}
		if (GetKeyState(VK_LEFT) & 0x8000)
		{
			m_pTransform->Go_Left(fTimeDelta);
		}
		if (GetKeyState(VK_RIGHT) & 0x8000)
		{
			m_pTransform->Go_Right(fTimeDelta);
		}
	}
	_long		MouseMove;

	if (pGameInstance->Get_DIMButtonState(CInput_Device::DIMB_RBUTTON)) {
		if (MouseMove = pGameInstance->Get_DIMMoveState(CInput_Device::DIMM_X))
		{
			m_pTransform->Turn(_float3(0.f, 1.f, 0.f), fTimeDelta * MouseMove * 0.1f);
		}

		if (MouseMove = pGameInstance->Get_DIMMoveState(CInput_Device::DIMM_Y))
		{
			m_pTransform->Turn(m_pTransform->Get_State(CTransform::STATE_RIGHT), fTimeDelta * MouseMove* 0.1f);
		}
	}
	

	__super::Tick(fTimeDelta);

	Safe_Release(pGameInstance);
}

void CCamera_Default::LateTick(_float fTimeDelta)
{
	__super::LateTick(fTimeDelta);
}

HRESULT CCamera_Default::Render()
{
	if (FAILED(__super::Render()))
		return E_FAIL;

	return S_OK;
}

_bool CCamera_Default::Picking(_float3 * _pickpos)
{
	return _bool();
}

CCamera_Default * CCamera_Default::Create(LPDIRECT3DDEVICE9 pGraphic_Device)
{
	CCamera_Default*	pInstance = new CCamera_Default(pGraphic_Device);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created CCamera_Default"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CCamera_Default::Clone(void * pArg)
{
	CCamera_Default*	pInstance = new CCamera_Default(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CCamera_Default"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CCamera_Default::Free()
{
	__super::Free();

}
