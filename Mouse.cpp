#include "Mouse.h"
#include <dinput.h>
#include "debug_font.h"
#include "texture.h"
#include <d3d9.h>
#include <tchar.h>
#include <d3dx9.h>
#include "texture.h"
#include "sprite.h"
#include "Collision.h"
#include "Debug.h"
#include "sound.h"
#include "debug_font.h"
#include "Effect.h"
#include "Enemy.h"
#include "Number.h"
#include "mydirect3d.h"
#include "sprite.h"

HRESULT InputMouse::CreateDevice(HWND hWnd)
{
	HRESULT hr;
	m_hWnd = hWnd;

	if (FAILED(hr = DirectInput8Create(GetModuleHandle(NULL), DIRECTINPUT_VERSION
		, IID_IDirectInput8, (VOID**)&m_pDI, NULL)))
		return hr;

	if (FAILED(hr = m_pDI->CreateDevice(GUID_SysMouse, &m_pMouse, NULL)))
		return hr;

	if (FAILED(hr = m_pMouse->SetDataFormat(&c_dfDIMouse2)))
		return hr;

	hr = m_pMouse->SetCooperativeLevel(m_hWnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);

	if (FAILED(hr))
		return hr;


	MouseTrans.x = SCREEN_WIDTH/2;
	MouseTrans.y = SCREEN_HEIGHT/2;
	SetCursorPos(1920 / 2, 1080 / 2);
	
	m_pMouse->Acquire();

	return S_OK;
}

HRESULT InputMouse::ReadDate()
{
	HRESULT hr;

	if (NULL == m_pMouse)
		return S_OK;

	ZeroMemory(&m_MouseState2, sizeof(m_MouseState2));
	hr = m_pMouse->GetDeviceState(sizeof(DIMOUSESTATE2), &m_MouseState2);

	if (FAILED(hr))
	{
		hr = m_pMouse->Acquire();
		while (hr == DIERR_INPUTLOST)
			hr = m_pMouse->Acquire();

		return S_OK;
	}

	m_ptMouse.x = m_MouseState2.lX;
	m_ptMouse.y = m_MouseState2.lY;
	MouseTrans.x +=  m_ptMouse.x;
	MouseTrans.y += m_ptMouse.y;


	return S_OK;
}
bool InputMouse::MouseMove()
{
	MouseTrans.x = SCREEN_WIDTH / 2;
	MouseTrans.y = SCREEN_HEIGHT / 2;
	return true;
}
BOOL InputMouse::PushLeft()
{
		return (m_MouseState2.rgbButtons[0] & 0x80) ? TRUE : FALSE;
}

BOOL InputMouse::PushRight()
{
	return (m_MouseState2.rgbButtons[1] & 0x80) ? TRUE : FALSE;
}

BOOL InputMouse::PushMiddle()
{
	return (m_MouseState2.rgbButtons[2] & 0x80) ? TRUE : FALSE;
}

void InputMouse::OnActivate(WPARAM wParam)
{
	if (WA_INACTIVE != wParam && m_pMouse)
	{
		m_pMouse->Acquire();
	}
}

VOID InputMouse::FreeDirectInput()
{
	if (m_pMouse)
		m_pMouse->Unacquire();

	SAFE_RELEASE(m_pMouse);
	SAFE_RELEASE(m_pDI);
}
bool InputMouse::Mouse_Collsion(int TexID,float dx,float dy)
{
	int Widht = Texture.GetWidth(TexID);
	int Height = Texture.GetHeight(TexID);

	if (MouseTrans.x < dx + 0.5f * Widht && MouseTrans.x > dx - 0.5f * Widht && MouseTrans.y > dy - 0.5f * Height && MouseTrans.y < dy + 0.5f * Height)
	{
		return true;
	}
	else
		return false;
	
}