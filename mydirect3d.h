#ifndef _MYDIRECT3D_H_	
#define _MYDIRECT3D_H_

#include <windows.h>
#include <d3d9.h>


bool MyDirect3D_Init(HWND hWnd);
void MyDirect3D_Uninit(void);
//void MyDirect3D_Update(void);
//void MyDirect3D_Draw(void);
LPDIRECT3DDEVICE9 GetDevice(void);

#endif

