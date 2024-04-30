#include <Windows.h>
#define DIRECTINPUT_VERSION (0x0800)
#include <dinput.h>

#define	NUM_KEY_MAX			(256)	

static bool initialize(HINSTANCE hInstance);
static void finalize(void);


static LPDIRECTINPUT8			g_pInput = NULL;		
static LPDIRECTINPUTDEVICE8	g_pDevKeyboard = NULL;		
BYTE					g_aKeyState[NUM_KEY_MAX];		
BYTE					g_aKeyStateTrigger[NUM_KEY_MAX];
BYTE					g_aKeyStateRelease[NUM_KEY_MAX];

bool initialize(HINSTANCE hInstance)
{
	if(g_pInput == NULL) {

		if(FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&g_pInput, NULL))) {

			return false;
		}
	}

	return true;
}

void finalize(void)
{
	if(g_pInput != NULL) {

		g_pInput->Release();
		g_pInput = NULL;
	}
}


bool Keyboard_Initialize(HINSTANCE hInstance, HWND hWnd)
{
	if (!initialize(hInstance)) {

		MessageBox(hWnd, "InputError", "InputError", MB_ICONWARNING);
		return false;
	}

	if (FAILED(g_pInput->CreateDevice(GUID_SysKeyboard, &g_pDevKeyboard, NULL)))
	{
		MessageBox(hWnd, "InputError", "InputError", MB_ICONWARNING);
		return false;
	}

	if (FAILED(g_pDevKeyboard->SetDataFormat(&c_dfDIKeyboard)))
	{
		MessageBox(hWnd, "InputError", "InputError", MB_ICONWARNING);
		return false;
	}

	if (FAILED(g_pDevKeyboard->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		MessageBox(hWnd, "InputError", "InputError", MB_ICONWARNING);
		return false;
	}

	g_pDevKeyboard->Acquire();

	return true;
}

void Keyboard_Finalize(void)
{
	if(g_pDevKeyboard != NULL)
	{
		g_pDevKeyboard->Unacquire();

		g_pDevKeyboard->Release();
		g_pDevKeyboard = NULL;
	}

	finalize();
}

void Keyboard_Update(void)
{
	BYTE aKeyState[NUM_KEY_MAX];

	if (SUCCEEDED(g_pDevKeyboard->GetDeviceState(sizeof(aKeyState), aKeyState)))
	{
		// aKeyState[DIK_SPACE] & 0x80

		for (int nCnKey = 0; nCnKey < NUM_KEY_MAX; nCnKey++)
		{
			g_aKeyStateTrigger[nCnKey] = (g_aKeyState[nCnKey] ^ aKeyState[nCnKey]) & aKeyState[nCnKey];
			g_aKeyStateRelease[nCnKey] = (g_aKeyState[nCnKey] ^ aKeyState[nCnKey]) & g_aKeyState[nCnKey];


			g_aKeyState[nCnKey] = aKeyState[nCnKey];
		}
	}
	else
	{
		g_pDevKeyboard->Acquire();
	}
}

bool Keyboard_IsPress(int nKey)
{
	return (g_aKeyState[nKey] & 0x80) ? true : false;
}

bool Keyboard_IsTrigger(int nKey)
{
	return (g_aKeyStateTrigger[nKey] & 0x80) ? true: false;
}

bool Keyboard_IsRelease(int nKey)
{
	return (g_aKeyStateRelease[nKey] & 0x80) ? true: false;
}
