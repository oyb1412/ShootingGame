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
#include "Mouse.h"
#include "Fade.h"
static bool Mouse_Zone_Next = false;
static int Choice_Fade = 255;
static bool Choice_Trigger = false;
static float CursorTime;
static bool Cursor;
void Tex_Init()
{
	Mouse_Zone_Next = false;
	Choice_Fade = 255;
	Choice_Trigger = false;
	Number_Init();
	Fade_Init();
	CursorTime = 0;
	Cursor = false;
}
void Tex_Update()
{
	if (Boss_Info().Hp <= 0)
	{
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
	}

	if (/*MouseInput.PushLeft() && */MouseInput.Mouse_Collsion(Texture.Tex[Next2_Texture], SCREEN_WIDTH * 0.5, SCREEN_HEIGHT * 0.8))
	{
		Mouse_Zone_Next = true;
		if (MouseInput.PushLeft() && Mouse_Zone_Next && !Choice_Trigger)
		{
			Choice_Trigger = true;
		}
	}
	else
	{
		Mouse_Zone_Next = false;
	}

	if (Choice_Trigger)
	{
		Choice_Fade-=5;
		/*if (Fade_In())
		{
			Scene_SetNextScene(SCENE_NAME);
		}*/
	}

	if (Choice_Fade <= 0)
	{
		Choice_Fade = 0;
		if (Fade_In())
		{
			Scene_SetNextScene(SCENE_NAME);
		}
	}
}
void Tex_Draw()
{

	//Number_Draw(MouseInput.MouseTrans.y, 30, 30, 70);
	//Number_Draw(MouseInput.MouseTrans.x, 30, 30, 30);

	if (Boss_Info().Hp <= 0)
	{
		Draw_MiddleStandard(Texture.Tex[Crear_Texture], SCREEN_WIDTH * 0.5, SCREEN_HEIGHT * 0.3, 1, 1);
		DebugFont_Draw(SCREEN_WIDTH * 0.25, SCREEN_HEIGHT * 0.5, "Your Score : %.0f", Get_Score());

		if (!Mouse_Zone_Next)
		{
			Draw_MiddleStandard(Texture.Tex[Next_Texture], SCREEN_WIDTH * 0.5, SCREEN_HEIGHT * 0.8, 1, 1, Choice_Fade);
		}
		else if (Mouse_Zone_Next)
		{
			Draw_MiddleStandard(Texture.Tex[Next2_Texture], SCREEN_WIDTH * 0.5, SCREEN_HEIGHT * 0.8, 1, 1, Choice_Fade);
		}
		
	}
	Fade_Draw();
}
