#include "input.h"
#include "texture.h"
#include "sprite.h"
#include "common.h"
#include "mydirect3d.h"
#include "Bullet.h"
#include <d3d9.h>
#include <tchar.h>
#include <d3dx9.h>
#include <windows.h>
#include "Collision.h"
#include "sound.h"
#include "palyer.h"
#include "judgement.h"
#include "Mouse.h"
#include "Debug.h"
#include "Fade.h"
static float BgMoveTime = 0;
static int Tex_Fade = 255;
static bool Tex_Fade_Trigger = false;
static bool Fade_Begin = false;
static float CursorTime;
static bool Start_Sound_Begin = false;

static bool Cursor;
struct bg
{
	D3DXVECTOR2 position;
	D3DCOLOR color;
	D3DXVECTOR2 uv;
	D3DXVECTOR2 size;
};
static bg BG;

void Title_Init(void)
{
	BgMoveTime = 0;
	CursorTime = 0;
	Cursor = false;
	Tex_Fade = 255;
	Tex_Fade_Trigger = false;
	Fade_Begin = false;
	Start_Sound_Begin = false;
	Fade_Init();
	BG.position.x = 400;
	BG.position.y = 500;

}
void Title_Update(void)
{
		Fade_Out();
		if (!Start_Sound_Begin)
		{
			StopSound();
			PlaySound(SOUND_LABEL_STARTBGM);
			Start_Sound_Begin = true;
		}
		if (Cursor == false)
		{
			MouseInput.MouseMove();
			SetCursorPos(1920 / 2, 1080 / 2);
			CursorTime += 0.5f;
		}
		if (CursorTime >= 1)
		{
			Cursor = true;
			CursorTime = 0;
		}
		BgMoveTime += 0.5f;
		


		if (MouseInput.Mouse_Collsion(Texture.Tex[StartGame_Texture], SCREEN_WIDTH * 0.5, SCREEN_HEIGHT * 0.7) )
		{
			Tex_Fade_Trigger = true;
		}
		else
		{
			Tex_Fade_Trigger = false;
		}
		if (MouseInput.PushLeft() && Tex_Fade_Trigger && !Fade_Begin)
		{
			PlaySound(SOUND_LABEL_SE_CHOICE);

			Fade_Begin = true;
		}
		if (Fade_Begin)
		{
			Tex_Fade -= 5;
		/*	if (Fade_In())
			{
				Scene_SetNextScene(SCENE_GAME);
			}*/
		}
		if (Tex_Fade <= 0)
		{
			Tex_Fade = 0;
			if (Fade_In())
			{
				Scene_SetNextScene(SCENE_GAME);
			}
		}
		
	
}
void Title_Draw(void)
{
	for (int i = 0; i < 100; i++)
	{
		Draw_MiddleStandard(Texture.Tex[BG_Texture], BG.position.x, BG.position.y - 2000 * i + BgMoveTime, 1, 1);
	}
	Draw_MiddleStandard(Texture.Tex[Name_Texture], SCREEN_WIDTH * 0.5,SCREEN_HEIGHT * 0.2, 1, 1);
	if (!Tex_Fade_Trigger)
	{
		Draw_MiddleStandard(Texture.Tex[StartGame_Texture], SCREEN_WIDTH * 0.5, SCREEN_HEIGHT * 0.7, 1, 1, Tex_Fade);
	}
	else if (Tex_Fade_Trigger)
	{
		Draw_MiddleStandard(Texture.Tex[StartGame2_Texture], SCREEN_WIDTH * 0.5, SCREEN_HEIGHT * 0.7, 1, 1, Tex_Fade);
	}
	Fade_Draw();
}

