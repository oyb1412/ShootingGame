#include "sprite.h"
#include "texture.h"
#include <d3d9.h>
#include <tchar.h>
#include <d3dx9.h>
#include <windows.h>
#include "Fade.h"
#include "common.h"
static int Fade = 255;
static bool Fade_Out_Trigger = false;
static bool Fade_In_Trigger = false;

void Fade_Init(void)
{
	Fade = 255;
	Fade_Out_Trigger = false;
	Fade_In_Trigger = false;
}
bool Fade_In(void)
{
	if (!Fade_In_Trigger)
	{
		Fade += 5;
	}
	if(Fade >= 255)
	{
		Fade = 255;
		Fade_In_Trigger = true;
	}
	if (Fade_In_Trigger)
	{
		return true;
	}
}
bool Fade_Out(void)
{
	if (!Fade_Out_Trigger)
	{
		Fade -= 5;
	}
	if (Fade <= 0)
	{
		Fade = 0;
		Fade_Out_Trigger = true;
	}

	if (Fade_Out_Trigger)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Fade_Draw(void)
{
	Draw_MiddleStandard(Texture.Tex[Fade_Texture], SCREEN_WIDTH * 0.5, SCREEN_HEIGHT * 0.5, 1, 1, Fade);
}
