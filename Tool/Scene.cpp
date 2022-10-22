#include "stdafx.h"
#include "Scene.h"

#include "MainFrm.h"
#include "ToolView.h"
#include "MenuView.h"
#include "TabDlg.h"

#include "Tab1.h"
#include "Tab2.h"
#include "Tab3.h"
#include "Tab4.h"

#include "KeyMgr.h"
#include "GameInstance.h"
#include "Terrain.h"
#include "Cube.h"
#include "Camera_Default.h"

#include "Layer.h"

CScene::CScene(LPDIRECT3DDEVICE9 pGraphic_Device)
	: CLevel(pGraphic_Device)
{
}

HRESULT CScene::NativeConstruct()
{
	if (FAILED(__super::NativeConstruct()))
		return E_FAIL;

	if (FAILED(Ready_Layer_Camera(TEXT("Layer_Camera"))))
		return E_FAIL;
	if (FAILED(Ready_Layer_BackGround(TEXT("Layer_BackGround"))))
		return E_FAIL;

	m_Gameinstance = CGameInstance::GetInstance();
	Safe_AddRef(m_Gameinstance);

	CMainFrame* mainFrm = dynamic_cast<CMainFrame*>(AfxGetMainWnd());
	m_toolView = dynamic_cast<CToolView*>(mainFrm->m_MainSplitter.GetPane(0, 1));
	CMenuView* menuView = dynamic_cast<CMenuView*>(mainFrm->m_MainSplitter.GetPane(0, 0));
	m_tabDlg = &(menuView->m_TabDlg);

	return S_OK;
}

void CScene::Tick(_float fTimeDelta)
{
	__super::Tick(fTimeDelta);

	TabManaged(fTimeDelta);
}

HRESULT CScene::Render()
{
	return E_NOTIMPL;
}

void CScene::TabManaged(_float fTimeDelta)
{
	switch (m_tabDlg->m_Tab.GetCurSel())
	{
	case 0:
		Tab1(fTimeDelta);
		break;

	case 1:
		Tab2(fTimeDelta);
		break;

	case 2:
		Tab3(fTimeDelta);
		break;

	case 3:
		Tab4(fTimeDelta);
		break;

	default:
		break;
	}
}

void CScene::Tab1(_float fTimeDelta)		//타일탭
{
	CTab1* tab = m_tabDlg->pDlg1;
	CTerrain* _terrain = (CTerrain*)CGameInstance::GetInstance()->Get_Terrain(STAGE_SCENE, TEXT("Layer_BackGround"));
	_float3 __pos;
	int flag = 0;

	if (CKeyMgr::Get_Instance()->Key_Down(VK_MBUTTON)) {
		for (auto& iter : m_toolView->v_TileList) {
			if (iter->Object->Picking(&__pos)) {
				tab->m_Scene_ListBox.SetCurSel(flag);
				return;
			}
			flag++;
		}
	}

	if (tab->m_Tile_Listbox.GetCurSel() >= 0) {
		tab->m_Blend_ListBox.SetCurSel(-1);
		//타일생성
		if (CKeyMgr::Get_Instance()->Key_Pressing(VK_LBUTTON)) {

			for (auto& iter : m_toolView->v_TileList)   //이미 타일 존재할 경우 생성X
				if (iter->Object->Picking(&__pos))
					return;

			//피킹세팅
			_float3 _Pos;
			if (!(_terrain->Tile_Picking(&_Pos)))  //터렌의 중점위치로 던져줘야함
				return;
			CString _curselName;
			tab->m_Tile_Listbox.GetText(tab->m_Tile_Listbox.GetCurSel(), _curselName);
			int _sel = _ttoi(_curselName);  //이미지타일 넘버
			_float4x4 temp_Mtx;
			D3DXMatrixIdentity(&temp_Mtx);
			temp_Mtx.m[3][0] = _Pos.x;
			temp_Mtx.m[3][1] = _Pos.y + 0.01f;
			temp_Mtx.m[3][2] = _Pos.z;
			temp_Mtx.m[0][3] = (_float)_sel;
			m_Gameinstance->Add_GameObjectToLayer(STAGE_SCENE, L"TILE", L"Prototype_GameObject_Tile", temp_Mtx);
			CLayer* obj_layer = m_Gameinstance->Get_GameObejct_Layer(STAGE_SCENE, L"TILE");
	
			size_t cnt = obj_layer->m_ObjectList.size();
			CGameObject* _obj = m_Gameinstance->Get_Obj_in_Layer(obj_layer, int(cnt - 1));
	
			CTransform* _trans = (CTransform*)_obj->Get_Component(L"Com_Transform");
	
			TILEDATA* _data = new TILEDATA;
			_data->TileID = _sel;
			_data->Transform = _trans;
			_data->Object = _obj;
			m_toolView->v_TileList.push_back(_data);										//map에 오브젝트 추가 , 스테이지안에 모든 오브젝트들을 관리할거임
			tab->m_Scene_ListBox.AddString(_curselName);
		}
	}

	if (tab->m_Scene_ListBox.GetCurSel() >= 0) {
		if (CKeyMgr::Get_Instance()->Key_Down(VK_DELETE)) {
			tab->Tile_Delete_Button();
			return;
		}

		if (CKeyMgr::Get_Instance()->Key_Down('Q'))
			m_toolView->v_TileList[tab->m_Scene_ListBox.GetCurSel()]->Transform->Turn90(_float3(0.f, 1.f, 0.f));
		
		if (CKeyMgr::Get_Instance()->Key_Down('E'))
			m_toolView->v_TileList[tab->m_Scene_ListBox.GetCurSel()]->Transform->Turn90(_float3(0.f, -1.f, 0.f));
	}


}

void CScene::Tab2(_float fTimeDelta)		//오브젝트 탭
{
	CTab2* tab = m_tabDlg->pDlg2;
	CTerrain* _terrain = (CTerrain*)CGameInstance::GetInstance()->Get_Terrain(STAGE_SCENE, TEXT("Layer_BackGround"));
	_float3 __pos;
	int flag = 0;

	if (CKeyMgr::Get_Instance()->Key_Down(VK_MBUTTON)) {
		for (auto& iter : m_toolView->v_ObjList) {
			if (iter->Object->Picking(&__pos)) {
				tab->m_SObj_List.SetCurSel(flag);
				tab->m_Obj_list.SetCurSel(-1);
				return;
			}
			flag++;
		}
	}

	if (CKeyMgr::Get_Instance()->Key_Down(VK_F1))
		tab->Camera_Set_Button();
	if (CKeyMgr::Get_Instance()->Key_Down(VK_F2))
		tab->Tile_Picking_CheckBox();
	if (CKeyMgr::Get_Instance()->Key_Down(VK_F3))
		tab->Rotation_90_CheckBox();


	if (tab->m_Obj_list.GetCurSel() >= 0) {
		if (CKeyMgr::Get_Instance()->Key_Down(VK_LBUTTON)){
			//피킹세팅
			_float3 _Pos;
			if (tab->Tile_PickingMode_Box == 1) {
				if (!(_terrain->Tile_Picking(&_Pos)))
					return;
			}
			else {
				if (!(_terrain->Picking(&_Pos)))
					return;
			}

			_tchar _proto[MAX_PATH] = TEXT("Prototype_GameObject_");
			CString _curselName;
			tab->m_Obj_list.GetText(tab->m_Obj_list.GetCurSel(), _curselName);
			_tchar tt[MAX_PATH] = L"";

			int _sel = 0;

			for (int i = 0; i < OBJ_END; i++)
				if (!lstrcmp(enum_str[i], _curselName)) {
					_sel = i;
					break;
				}

			lstrcpy(tt, _curselName);
			
			//오브젝트 커셀된것들 설치
			lstrcat(_proto, tt);
			_float4x4 temp_Mtx;
			D3DXMatrixIdentity(&temp_Mtx);
			temp_Mtx.m[3][0] = _Pos.x;
			temp_Mtx.m[3][1] = _Pos.y+0.5f;
			temp_Mtx.m[3][2] = _Pos.z;
			m_Gameinstance->Add_GameObjectToLayer(STAGE_SCENE, L"OBJECT", _proto, temp_Mtx);
			CLayer* obj_layer = m_Gameinstance->Get_GameObejct_Layer(STAGE_SCENE, L"OBJECT");
		
			size_t cnt = obj_layer->m_ObjectList.size();
			CGameObject* _obj = m_Gameinstance->Get_Obj_in_Layer(obj_layer, int(cnt-1));
			
			CTransform* _trans = (CTransform*)_obj->Get_Component(L"Com_Transform");

			CString itochar;																//숫자 문자변환
			itochar.Format(_T("%d"), cnt);
			_curselName += itochar;

			TOOLDATA* _data = new TOOLDATA;
			_data->ObjID = _sel;
			_data->Transform = _trans;
			_data->Object = _obj;
			m_toolView->v_ObjList.push_back(_data);									//map에 오브젝트 추가 , 스테이지안에 모든 오브젝트들을 관리할거임
			tab->m_SObj_List.AddString(_curselName); 

		}
	}
	
	if (tab->m_SObj_List.GetCurSel() >= 0) {
		if (CKeyMgr::Get_Instance()->Key_Down(VK_DELETE)) {
			tab->Scene_Delete_Button();
			return;
		}


		int _sel = tab->m_SObj_List.GetCurSel();

		CTransform* _state = m_toolView->v_ObjList[_sel]->Transform;
		_float3 _pos = _state->Get_State(CTransform::STATE_POSITION);

		if (CKeyMgr::Get_Instance()->Key_Pressing('Q')) {  //y축높이 상
			_pos.y += 1.f * fTimeDelta;
			_state->Set_State(CTransform::STATE_POSITION, _pos);
		}
		if (CKeyMgr::Get_Instance()->Key_Pressing('E')) {  //하
			_pos.y -= 1.f * fTimeDelta;
			_state->Set_State(CTransform::STATE_POSITION, _pos);
		}


		// x, y, z 축 스케일링
		if (CKeyMgr::Get_Instance()->Key_Pressing('5')) //X축
			_state->Axis_Scaling(_float3(1.0f, 0.f, 0.f), fTimeDelta);
		if (CKeyMgr::Get_Instance()->Key_Pressing('6')) { 
			_state->Axis_Scaling(_float3(-1.0f, 0.f, 0.f), fTimeDelta);
		}
		if (CKeyMgr::Get_Instance()->Key_Pressing('7')) { //Y축
			_state->Axis_Scaling(_float3(0.f, 1.f, 0.f), fTimeDelta);
		}
		if (CKeyMgr::Get_Instance()->Key_Pressing('8')) {
			_state->Axis_Scaling(_float3(0.f, -1.f, 0.f), fTimeDelta);
		}
		if (CKeyMgr::Get_Instance()->Key_Pressing('9')) { //Z축
			_state->Axis_Scaling(_float3(0.f, 0.f, 1.f), fTimeDelta);
		}
		if (CKeyMgr::Get_Instance()->Key_Pressing('0')) { //Z축
			_state->Axis_Scaling(_float3(0.f, 0.f, -1.f), fTimeDelta);
		}


		if (tab->m_Rotation_90 == TRUE) {							//90도 회전모드
			if (CKeyMgr::Get_Instance()->Key_Down('1'))		
				_state->Turn90(_float3(0.f, 1.f, 0.f));
			if (CKeyMgr::Get_Instance()->Key_Down('2'))		
				_state->Turn90(_float3(0.f, -1.f, 0.f));
			if (CKeyMgr::Get_Instance()->Key_Down('3'))
				_state->Turn90(_float3(1.f, 0., 0.f));
			if (CKeyMgr::Get_Instance()->Key_Down('4'))
				_state->Turn90(_float3(-1.f, 0.f, 0.f));
		}
		else {
			if (CKeyMgr::Get_Instance()->Key_Pressing('1'))		//회전  좌
				_state->Turn(_float3(0.f, 1.f, 0.f), fTimeDelta);
			if (CKeyMgr::Get_Instance()->Key_Pressing('2'))		//우
				_state->Turn(_float3(0.f, 1.f, 0.f), -fTimeDelta);
			if (CKeyMgr::Get_Instance()->Key_Pressing('3'))		//상
				_state->Turn(_state->Get_State(CTransform::STATE_RIGHT), fTimeDelta);
			if (CKeyMgr::Get_Instance()->Key_Pressing('4'))		//하
				_state->Turn(_state->Get_State(CTransform::STATE_RIGHT), -fTimeDelta);
		}
			
		if (CKeyMgr::Get_Instance()->Key_Pressing('A')) {  // 상
			_pos.x -= _speed * fTimeDelta;
			_state->Set_State(CTransform::STATE_POSITION, _pos);
		}
		if (CKeyMgr::Get_Instance()->Key_Pressing('D')) {  // 상
			_pos.x += _speed * fTimeDelta;
			_state->Set_State(CTransform::STATE_POSITION, _pos);
		}
		if (CKeyMgr::Get_Instance()->Key_Pressing('W')) {  // 상
			_pos.z += _speed * fTimeDelta;
			_state->Set_State(CTransform::STATE_POSITION, _pos);
		}
		if (CKeyMgr::Get_Instance()->Key_Pressing('S')) {  // 상
			_pos.z -= _speed * fTimeDelta;
			_state->Set_State(CTransform::STATE_POSITION, _pos);
		}
		if (CKeyMgr::Get_Instance()->Key_Pressing('Z'))		//크기업
			_state->Scaling(fTimeDelta);
		if (CKeyMgr::Get_Instance()->Key_Pressing('X'))		//크기다운
			_state->Scaling(-fTimeDelta);
	}
}

void CScene::Tab3(_float fTimeDelta)		//큐브탭
{
	CTab3* tab = m_tabDlg->pDlg3;
	CTerrain* _terrain = (CTerrain*)CGameInstance::GetInstance()->Get_Terrain(STAGE_SCENE, TEXT("Layer_BackGround"));
	_float _dist = (_float)INT_MAX;
	_float4x4 Camera_World;
	m_pGraphic_Device->GetTransform(D3DTS_VIEW, &Camera_World);
	D3DXMatrixInverse(&Camera_World, nullptr, &Camera_World);
	_float3 CameraPos = _float3(Camera_World.m[3][0], Camera_World.m[3][1], Camera_World.m[3][2]);

	if (CKeyMgr::Get_Instance()->Key_Down(VK_F1)) {
		tab->m_Cube_List.SetCurSel(0);
		return;
	}

	int _sel = 0;
	
	if (tab->m_Scene_ListBox.GetCurSel() >= 0) {
		_sel = tab->m_Scene_ListBox.GetCurSel();
		CTransform* _state = m_toolView->v_CubeList[_sel]->Transform;

		if (CKeyMgr::Get_Instance()->Key_Down('Q')) {
			_state->Turn90(_float3(0.f, 1.f, 0.f));
		}

		if (CKeyMgr::Get_Instance()->Key_Down('E')) {
			_state->Turn90(_float3(0.f, -1.f, 0.f));
		}
	}

	if (CKeyMgr::Get_Instance()->Key_Down(VK_DELETE)) {
		if(tab->m_Scene_ListBox.GetCurSel() >= 0)
			tab->Delete_Button();
		return;
	}

	_float3 _Pos;
	_bool flag = false;

	int i = 0;
	if (CKeyMgr::Get_Instance()->Key_Down(VK_MBUTTON)) {
		for (auto& iter : m_toolView->v_CubeList) {
			CCube* temp = (CCube*)(iter->Object);
			_float3 temppos = iter->Transform->Get_State(CTransform::STATE_POSITION);
			if (temp->CubePicking(&_Pos)) {
				if (_dist > D3DXVec3Length(&(temppos - CameraPos))) {
					_dist = D3DXVec3Length(&(temppos - CameraPos));
					_sel = i;
				}
			}
			i++;
		}

		tab->m_Scene_ListBox.SetCurSel(_sel);
		tab->m_Cube_List.SetCurSel(-1);

		return;
	}

	if (tab->m_Cube_List.GetCurSel() >= 0 && tab->m_Tex_ListBox.GetCurSel() >= 0) {					//큐브 
		if (CKeyMgr::Get_Instance()->Key_Down(VK_LBUTTON)) {
			_float3 tlqkf;
			for (auto& iter : m_toolView->v_CubeList) {
				CCube* temp = (CCube*)(iter->Object);
				_float3 temppos = iter->Transform->Get_State(CTransform::STATE_POSITION);
				if (temp->CubePicking(&_Pos)) {
					if (_dist > D3DXVec3Length(&(temppos - CameraPos))){
						_dist = D3DXVec3Length(&(temppos - CameraPos));
						tlqkf = _Pos;
						flag = true;
					}
				}
			}
			
			for (auto& iter : m_toolView->v_CubeList) {
				CCube* temp = (CCube*)(iter->Object);
				_float3 temppos = iter->Transform->Get_State(CTransform::STATE_POSITION);
				if (temppos == _Pos)
					return;
			}

			if (flag == false) {
				if (!(_terrain->Tile_Picking(&_Pos)))
					return;
				_Pos.y += 0.5f;
			}
			else
				_Pos = tlqkf;
			
			//큐브피킹 함수 구현

			_tchar _proto[MAX_PATH] = TEXT("Prototype_GameObject_Cube");
			CString _curselName;
			tab->m_Cube_List.GetText(tab->m_Cube_List.GetCurSel(), _curselName);

			_uint _sel = 1;

			// 3층이 2.0이상
			// cube_str 순서 = { 콜리즌 / 노말 / 투명 }

			if (_Pos.y > 0.f)
				_sel = 0;
			if (_Pos.y > 1.0f)
				_sel = 1;
			if (_Pos.y > 2.0f)
				_sel = 2;

			_float4x4 temp_Mtx;
			D3DXMatrixIdentity(&temp_Mtx);
			temp_Mtx.m[3][0] = _Pos.x;
			temp_Mtx.m[3][1] = _Pos.y;
			temp_Mtx.m[3][2] = _Pos.z;
			temp_Mtx.m[0][3] = (_float)_sel;
			temp_Mtx.m[1][3] = (_float)tab->m_Tex_ListBox.GetCurSel();

			CLayer* obj_layer;

			m_Gameinstance->Add_GameObjectToLayer(STAGE_SCENE, L"Cube", _proto, temp_Mtx);
			obj_layer = m_Gameinstance->Get_GameObejct_Layer(STAGE_SCENE, L"Cube");

			size_t cnt = obj_layer->m_ObjectList.size();
			CGameObject* _obj = m_Gameinstance->Get_Obj_in_Layer(obj_layer, int(cnt - 1));
			CTransform* _trans = (CTransform*)_obj->Get_Component(L"Com_Transform");

			CUBEDATA* _data = new CUBEDATA;
			_data->CubeID = _sel;
			_data->Transform = _trans;
			_data->Object = _obj;
			_data->TexID = tab->m_Tex_ListBox.GetCurSel();
			m_toolView->v_CubeList.push_back(_data);

			tab->m_Scene_ListBox.AddString(_curselName);
		}
	}


}

void CScene::Tab4(_float fTimeDelta)				//블렌드 탭
{
	CTab4* tab = m_tabDlg->pDlg4;
	CTerrain* _terrain = (CTerrain*)CGameInstance::GetInstance()->Get_Terrain(STAGE_SCENE, TEXT("Layer_BackGround"));

	_float3 __pos;
	int flag = 0;

	if (CKeyMgr::Get_Instance()->Key_Down(VK_MBUTTON)) {
		for (auto& iter : m_toolView->v_BlendList) {
			if (iter->Object->Picking(&__pos)) {
				tab->m_Scene_ListBox.SetCurSel(flag);
				tab->m_Type_ListBox.SetCurSel(-1);
				return;
			}
			flag++;
		}
	}
	
	if (tab->m_Scene_ListBox.GetCurSel() >= 0) {
		if (CKeyMgr::Get_Instance()->Key_Down(VK_DELETE)) {
			tab->Delete_Button();
			return;
		}


		int _sel = tab->m_Scene_ListBox.GetCurSel();

		CTransform* _state = m_toolView->v_BlendList[_sel]->Transform;
		_float3 _pos = _state->Get_State(CTransform::STATE_POSITION);

		if (CKeyMgr::Get_Instance()->Key_Pressing('Q')) {  //y축높이 상
			_pos.y += 1.f * fTimeDelta;
			_state->Set_State(CTransform::STATE_POSITION, _pos);
		}
		if (CKeyMgr::Get_Instance()->Key_Pressing('E')) {  //하
			_pos.y -= 1.f * fTimeDelta;
			_state->Set_State(CTransform::STATE_POSITION, _pos);
		}


		// x, y, z 축 스케일링
		if (CKeyMgr::Get_Instance()->Key_Pressing('5')) //X축
			_state->Axis_Scaling(_float3(1.0f, 0.f, 0.f), fTimeDelta);
		if (CKeyMgr::Get_Instance()->Key_Pressing('6')) {
			_state->Axis_Scaling(_float3(-1.0f, 0.f, 0.f), fTimeDelta);
		}
		if (CKeyMgr::Get_Instance()->Key_Pressing('7')) { //Y축
			_state->Axis_Scaling(_float3(0.f, 1.f, 0.f), fTimeDelta);
		}
		if (CKeyMgr::Get_Instance()->Key_Pressing('8')) {
			_state->Axis_Scaling(_float3(0.f, -1.f, 0.f), fTimeDelta);
		}
		if (CKeyMgr::Get_Instance()->Key_Pressing('9')) { //Z축
			_state->Axis_Scaling(_float3(0.f, 0.f, 1.f), fTimeDelta);
		}
		if (CKeyMgr::Get_Instance()->Key_Pressing('0')) { //Z축
			_state->Axis_Scaling(_float3(0.f, 0.f, -1.f), fTimeDelta);
		}

		if (CKeyMgr::Get_Instance()->Key_Pressing('A')) {  // 상
			_pos.x -= _speed * fTimeDelta;
			_state->Set_State(CTransform::STATE_POSITION, _pos);
		}
		if (CKeyMgr::Get_Instance()->Key_Pressing('D')) {  // 상
			_pos.x += _speed * fTimeDelta;
			_state->Set_State(CTransform::STATE_POSITION, _pos);
		}
		if (CKeyMgr::Get_Instance()->Key_Pressing('W')) {  // 상
			_pos.z += _speed * fTimeDelta;
			_state->Set_State(CTransform::STATE_POSITION, _pos);
		}
		if (CKeyMgr::Get_Instance()->Key_Pressing('S')) {  // 상
			_pos.z -= _speed * fTimeDelta;
			_state->Set_State(CTransform::STATE_POSITION, _pos);
		}
		if (CKeyMgr::Get_Instance()->Key_Pressing('Z'))		//크기업
			_state->Scaling(fTimeDelta);
		if (CKeyMgr::Get_Instance()->Key_Pressing('X'))		//크기다운
			_state->Scaling(-fTimeDelta);

	}
	if (tab->m_Type_ListBox.GetCurSel() >= 0 && tab->m_Tex_ListBox.GetCurSel() >= 0) {
		if (CKeyMgr::Get_Instance()->Key_Down(VK_LBUTTON)) {
			_float3 _Pos;
			if (!(_terrain->Picking(&_Pos)))  //터렌의 중점위치로 던져줘야함
				return;
			CString _curselName;
			tab->m_Tex_ListBox.GetText(tab->m_Tex_ListBox.GetCurSel(), _curselName);
			int _sel = _ttoi(_curselName);  //이미지타일 넘버
			_float4x4 temp_Mtx;
			D3DXMatrixIdentity(&temp_Mtx);
			temp_Mtx.m[3][0] = _Pos.x;
			temp_Mtx.m[3][1] = _Pos.y + 0.5f;
			temp_Mtx.m[3][2] = _Pos.z;
			temp_Mtx.m[0][3] = (_float)_sel;
			m_Gameinstance->Add_GameObjectToLayer(STAGE_SCENE, L"BLEND", L"Prototype_GameObject_XRect", temp_Mtx);
			CLayer* obj_layer = m_Gameinstance->Get_GameObejct_Layer(STAGE_SCENE, L"BLEND");

			size_t cnt = obj_layer->m_ObjectList.size();
			CGameObject* _obj = m_Gameinstance->Get_Obj_in_Layer(obj_layer, int(cnt - 1));

			CTransform* _trans = (CTransform*)_obj->Get_Component(L"Com_Transform");

			TILEDATA* _data = new TILEDATA;
			_data->TileID = _sel;
			_data->Transform = _trans;
			_data->Object = _obj;
			m_toolView->v_BlendList.push_back(_data);										//map에 오브젝트 추가 , 스테이지안에 모든 오브젝트들을 관리할거임
			tab->m_Scene_ListBox.AddString(_curselName);
		}
	}
}

HRESULT CScene::Ready_Layer_Camera(const _tchar * pLayerTag)
{
	m_Gameinstance = CGameInstance::GetInstance();

	CCamera::CAMERADESC			CameraDesc;
	ZeroMemory(&CameraDesc, sizeof(CCamera::CAMERADESC));

	CameraDesc.vEye = _float3(0.f, 10.f, -15.f);
	CameraDesc.vAt = _float3(0.f, 0.f, 0.f);
	CameraDesc.vAxisY = _float3(0.f, 1.f, 0.f);
	CameraDesc.fNear = 0.1f;
	CameraDesc.fFar = 300.0f;
	CameraDesc.fFovy = D3DXToRadian(60.0f);
	CameraDesc.fAspect = (_float)WINCX / WINCY;

	CameraDesc.TransformDesc.fSpeedPerSec = 10.f;
	CameraDesc.TransformDesc.fRotationPerSec = 10.f;
	CameraDesc.TransformDesc.fScalePerSec = 1.f;


	if (FAILED(m_Gameinstance->Add_GameObjectToLayer(STAGE_SCENE, pLayerTag, TEXT("Prototype_GameObject_Camera_Default"), &CameraDesc)))
		return E_FAIL;

	return S_OK;
}

HRESULT CScene::Ready_Layer_BackGround(const _tchar * pLayerTag)
{
	m_Gameinstance = CGameInstance::GetInstance();

	if (FAILED(m_Gameinstance->Add_GameObjectToLayer(STAGE_SCENE, pLayerTag, TEXT("Prototype_GameObject_Terrain"))))
		return E_FAIL;


	return S_OK;
}

CScene * CScene::Create(LPDIRECT3DDEVICE9 pGraphic_Device)
{
	CScene*	pInstance = new CScene(pGraphic_Device);

	if (FAILED(pInstance->NativeConstruct()))
	{
		MSG_BOX(TEXT("Failed to Created Scene"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CScene::Free()
{
	__super::Free();

	Safe_Release(m_Gameinstance);

}
