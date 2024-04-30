#pragma once
#include <dinput.h>
#include "Scene.h"
#include "common.h"
#define SAFE_RELEASE(x) {if(x) x->Release(); x = NULL;}
class InputMouse
{
	LPDIRECTINPUT8 m_pDI;
	LPDIRECTINPUTDEVICE8 m_pMouse;
	DIMOUSESTATE2 m_MouseState2;
	HWND m_hWnd;

public:
	//InputMouse(void);
	//~InputMouse(void);

	HRESULT CreateDevice(HWND hWnd);
	HRESULT ReadDate();
	VOID FreeDirectInput();
	void OnActivate(WPARAM wParam);
	POINT m_ptMouse;
	POINT MouseTrans;
	BOOL PushLeft();
	BOOL PushRight();
	BOOL PushMiddle();
	bool MouseMove();
	bool Mouse_Collsion(int TexID, float dx, float dy);
};
extern InputMouse MouseInput;