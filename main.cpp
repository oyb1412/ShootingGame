#include <windows.h>
#include "common.h"
#include "mydirect3d.h"
#include "Scene.h"
#include "texture.h"
#include "system_timer.h"
#include "debug_font.h"
#include <d3d9.h>
#include <tchar.h>
#include <d3dx9.h>
#include "sprite.h"
#include "Debug.h"
#include "input.h"
#include "sound.h"
#include "game.h"
#include "Mouse.h"
#include "Name.h"
#pragma comment(lib,"d3d9.lib")
#if defined(DEBUG)||defined(_DEBUG)
#pragma comment(lib,"d3dx9d.lib")
#else
#pragma comment(lib,"d3dx9.lib")
#endif

#define CLASS_NAME       "GameWindow"
#define WINDOW_CAPTION   "window"
#define r ((unsigned int)100)  
#define pc ((unsigned int)(r * 2 * D3DX_PI))   
#define r1 ((unsigned int)10)  
#define pc1 ((unsigned int)(r1 * 2 * D3DX_PI))   
#define FPS_MEASUREMENT_TIME 1.0
typedef struct Vertex2d_tag
{
	D3DXVECTOR4 position;
	D3DCOLOR color;
	D3DXVECTOR2 uv;
}Vertex2d;
#define FVF_VERTEX2D (D3DFVF_XYZRHW|D3DFVF_DIFFUSE|D3DFVF_TEX1) 
// D3DFVF_DIFFUSE = COLOR , D3DFVF_TEX1 = Texture



LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
static bool Init(HWND hWnd);
static void Uninit(void);
static void Update(void);
static void Draw(void);
static int g_Framecount = 0;
static int g_FPSBaseFrameCount = 0;
static double g_FPSBaseTime = 0.0;
static double g_StaticFramTime = 0.0;
static float g_FPS = 0.0f;
HWND hWnd = NULL;
LPDIRECT3DDEVICE9 g_pDevice = NULL;
static bool flag = false;
static int flame = 0;
static float count = 0;
tag_Texture Texture;
InputMouse MouseInput;
tag_Name Name;

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);
	WNDCLASS wc = {};
	wc.lpfnWndProc = WndProc;
	wc.lpszClassName = CLASS_NAME;
	wc.hInstance = hInstance;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_BACKGROUND + 1);

	RegisterClass(&wc);

	DWORD window_style = WS_OVERLAPPEDWINDOW ^ (WS_THICKFRAME | WS_MAXIMIZEBOX);

	RECT window_rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };
	AdjustWindowRect(&window_rect, window_style, FALSE);

	int window_width = window_rect.right - window_rect.left;
	int window_height = window_rect.bottom - window_rect.top;

	int desktop_width = GetSystemMetrics(SM_CXSCREEN);
	int desktop_height = GetSystemMetrics(SM_CYSCREEN);

	int window_x = max((desktop_width - window_width) / 2, 0);
	int window_y = max((desktop_height - window_height - 150) / 2, 0);

	hWnd = CreateWindow(
		CLASS_NAME,
		WINDOW_CAPTION,
		window_style,
		window_x,
		window_y,
		window_width,
		window_height,
		NULL,
		NULL,
		hInstance,
		NULL
	);
	Keyboard_Initialize(hInstance, hWnd);
	MouseInput.CreateDevice(hWnd);
	InitSound(hWnd);

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	MSG msg = {};
	if (!Init(hWnd))
	{
		return -1;
	}
	while (WM_QUIT != msg.message) {
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else {
			double time = SystemTimer_GetTime();
			if (time - g_StaticFramTime < 1.0 / 60.0)
			{
				Sleep(0);
			}
			else
			{
				g_StaticFramTime = time;
				Scene_Change();
				Update();
				Draw();
			}
		}
	}
	Uninit();
	return(int)msg.wParam;
}
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg) {
	case WM_KEYDOWN:
		if (wParam == VK_ESCAPE) {
			SendMessage(hWnd, WM_CLOSE, 0, 0);
		}
		break;
	case WM_CLOSE:
		if (MessageBox(hWnd, "정말로 종료하시겠습니까?", "종료", MB_OKCANCEL | MB_DEFBUTTON2) == IDOK) {
			DestroyWindow(hWnd);
		}
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	};
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

bool Init(HWND hWnd)
{
	MyDirect3D_Init(hWnd);
	Debug_Init();
	g_pDevice = GetDevice();
	Texture.Init();
	Sprite_Init();
	DebugFont_Initialize();
	Scene_Init();
	Texture.Load(hWnd);

	SystemTimer_Initialize();
	SystemTimer_Start();
	g_Framecount = g_FPSBaseFrameCount = 0;
	g_FPS = 0.0f;
	g_FPSBaseTime = SystemTimer_GetTime();
	g_StaticFramTime = g_FPSBaseTime;
	return true;
}
void Uninit(void)
{
	UninitSound();
	game_Uninit();
	Texture.Destroy();
	MyDirect3D_Uninit();
	DebugFont_Finalize();
	Scene_Uninit();
	Keyboard_Finalize();

	Sprite_Uninit();
	MouseInput.FreeDirectInput();
}
void Update(void)
{
	
	g_Framecount++;
	double time = SystemTimer_GetTime();
	if (time - g_FPSBaseTime >= FPS_MEASUREMENT_TIME)
	{
		g_FPS = (float)((g_Framecount - g_FPSBaseFrameCount) / (time - g_FPSBaseTime));

		g_FPSBaseFrameCount = g_Framecount;
		g_FPSBaseTime = time;
	}
	Keyboard_Update();
	MouseInput.ReadDate();
	Scene_Update();



}
void Draw(void)
{	

	g_pDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_RGBA(0, 0, 0, 255), 1.0f, 0);
	g_pDevice->BeginScene();
	g_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	g_pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	g_pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	g_pDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);


	Scene_Draw();
	g_pDevice->EndScene();
	g_pDevice->Present(NULL, NULL, NULL, NULL);
}
        