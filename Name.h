#pragma once

#include "common.h"
#include <d3dx9.h>
#include "Scene.h"
class tag_Name 
{
private:
	HWND hWnd;

	int Tex[10];
	int N_Tex[30];
	bool Fade_Counter;
	int Name[5] = { 0 };
	bool Name_Bgm;
	int ChangeTime;
	int i = 0;
	int g = 0;
	int turm = 0;
	LPDIRECT3DDEVICE9 m_pd3dDevice;
	struct CUBEVERTEX
	{
		D3DXVECTOR2 Position;
		DWORD color;
		D3DXVECTOR2 uv;
	};
public:
	virtual void Init(void);
	virtual void Update(void);
	virtual void Draw(void);
	virtual void Uninit(void);

	int Time_Info();
	int Save(int index);
};
extern tag_Name Name;