#pragma once

typedef struct tagInfo
{
	D3DXVECTOR3		vPos;
	D3DXVECTOR3		vDir;
	D3DXVECTOR3		vLook;

	D3DXMATRIX		matWorld;

}INFO;

typedef	struct tagTexture
{
	// 텍스처 컴객체
	LPDIRECT3DTEXTURE9		pTexture;

	// 이미지 정보를 보관하기 위한 구조체
	D3DXIMAGE_INFO			tImgInfo;

}TEXINFO;


typedef struct	tagFrame 
{
	int			iFrameStart;
	int			iFrameEnd;
	int			iFrameScene;

}FRAME;