#include <d3d9.h>
#include <tchar.h>
#include <d3dx9.h>
#pragma once
void Debug_Init(void);
void Debug_Uninit(void);
void Debug_DrawCircle(float x, float y,float radius);
void Debug_SetColor(D3DCOLOR color);
void Debug_Begin(void);
void Debug_End(void);