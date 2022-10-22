#pragma once
#include "Transform.h"
#include "GameObject.h"

#define WINCX 1280
#define WINCY 720

#define		VK_MAX		0xff

typedef struct TOOLDATA {
	_uint ObjID;
	CTransform* Transform;
	CGameObject* Object;
}TOOLDATA;

typedef struct TILEDATA {
	_uint TileID;
	CTransform* Transform;
	CGameObject* Object;
}TILEDATA;

typedef struct CUBEDATA {
	_uint CubeID;
	_uint TexID;
	CTransform* Transform;
	CGameObject* Object;

}CUBEDATA;

enum STAGE { STAGE_STATIC, STAGE_SCENE, STAGE_END };

extern HWND g_hWnd;