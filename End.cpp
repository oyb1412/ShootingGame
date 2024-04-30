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
#include "Debug.h"
#define END_BG_POSITION_X 500.0f
#define END_BG_POSITION_Y 500.0f
#define END_BG_SIZE_X 184
#define END_BG_SIZE_Y 300
#define END_KAERU_POSITION_X 500.0f
#define END_KAERU_POSITION_Y 500.0f
#define END_KAERU_SIZE_X 300
#define END_KAERU_SIZE_Y 300
#define END_GAMEOVER_POSITION_X 500.0f
#define END_GAMEOVER_POSITION_Y 200.0f
#define END_GAMEOVER_SIZE_X 800
#define END_GAMEOVER_SIZE_Y 250
#define END_MAINMENU_POSITION_X 500.0f
#define END_MAINMENU_POSITION_Y 850.0f
#define END_MAINMENU_SIZE_X 450
#define END_MAINMENU_SIZE_Y 100
#define TEX_MAX 5
#define FADE_MAX 255
#define KAERU_FADE_START 240
#define MAINMENU_FADE_START 200
#define GAMEOVER_FADE_START 80
#define GAMEOVER_FADE_SPEED 5
#define KAERU_FADE_SPEED 1

static short tex[TEX_MAX];
static short Kaeru_Fade = 0;
static short GameOver_Fade = 0;
static short MainMenu_Fade = 0;
static short GameOver_Start = 0;

struct end_bg
{
	D3DXVECTOR2 position;
	D3DCOLOR color;
	D3DXVECTOR2 uv;
	D3DXVECTOR2 size;
	bool Vibisle;
};
static end_bg End_Bg;

struct end_kaeru
{
	D3DXVECTOR2 position;
	D3DCOLOR color;
	D3DXVECTOR2 uv;
	D3DXVECTOR2 size;
	bool Vibisle;
};
static end_kaeru End_Kaeru;

struct end_gameover
{
	D3DXVECTOR2 position;
	D3DCOLOR color;
	D3DXVECTOR2 uv;
	D3DXVECTOR2 size;
	bool Vibisle;
};
static end_gameover End_GameOver;

struct end_mainmenu
{
	D3DXVECTOR2 position;
	D3DCOLOR color;
	D3DXVECTOR2 uv;
	D3DXVECTOR2 size;
	bool Vibisle;
};
static end_mainmenu End_MainMenu;

void End_Init(void)
{
	End_Bg.Vibisle = true;
	End_Bg.position.x = END_BG_POSITION_X;
	End_Bg.position.y = END_BG_POSITION_Y;
	End_Bg.size.x = END_BG_SIZE_X;
	End_Bg.size.y = END_BG_SIZE_Y;
	End_Kaeru.Vibisle = true;
	End_Kaeru.position.x = END_KAERU_POSITION_X;
	End_Kaeru.position.y = END_KAERU_POSITION_Y;
	End_Kaeru.size.x = END_KAERU_SIZE_X;
	End_Kaeru.size.y = END_KAERU_SIZE_Y;
	End_GameOver.Vibisle = true;
	End_GameOver.position.x = END_GAMEOVER_POSITION_X;
	End_GameOver.position.y = END_GAMEOVER_POSITION_Y;
	End_GameOver.size.x = END_GAMEOVER_SIZE_X;
	End_GameOver.size.y = END_GAMEOVER_SIZE_Y;
	End_MainMenu.Vibisle = true;
	End_MainMenu.position.x = END_MAINMENU_POSITION_X;
	End_MainMenu.position.y = END_MAINMENU_POSITION_Y;
	End_MainMenu.size.x = END_MAINMENU_SIZE_X;
	End_MainMenu.size.y = END_MAINMENU_SIZE_Y;
	//tex[0] = Texture_SetLoadFile("Accet/Texture/Fade.png", End_Bg.size.x, End_Bg.size.y);
//	tex[1] = Texture_SetLoadFile("Accet/Texture/End_Kaeru.png", End_Kaeru.size.x, End_Kaeru.size.y);
//	tex[2] = Texture_SetLoadFile("Accet/Texture/Game_Over_Tex.png", End_GameOver.size.x, End_GameOver.size.y);
//	tex[3] = Texture_SetLoadFile("Accet/Texture/Main_Menu_Text.png", End_MainMenu.size.x, End_MainMenu.size.y);
}
void End_Update(void)
{
	GameOver_Start += 1;
	if (GameOver_Start >= GAMEOVER_FADE_START && Kaeru_Fade <= KAERU_FADE_START)
	{
		GameOver_Fade += GAMEOVER_FADE_SPEED;
		if (GameOver_Fade >= KAERU_FADE_START && Kaeru_Fade <= FADE_MAX)
		{
			GameOver_Fade = FADE_MAX;
			Kaeru_Fade += KAERU_FADE_SPEED;
		}
		if (Kaeru_Fade >= MAINMENU_FADE_START)
		{
			MainMenu_Fade = FADE_MAX;
		}
	}
}
void End_Draw(void)
{
	Sprite_Draw_Tex_x_y_cx_cy_xc_yc_zc(tex[0], End_Bg.position.x, End_Bg.position.y, 500, 500, (float)5.5, (float)3.7, 1);
	Sprite_Draw_Tex_x_y_cx_cy_xc_yc_zc_fade(tex[1], End_Kaeru.position.x, End_Kaeru.position.y, 500, 500, 1, 1, 1 , Kaeru_Fade);
	Sprite_Draw_Tex_x_y_cx_cy_xc_yc_zc_fade(tex[2], End_GameOver.position.x, End_GameOver.position.y, 500, 500, 1, 1, 1, GameOver_Fade);
	Sprite_Draw_Tex_x_y_cx_cy_xc_yc_zc_fade(tex[3], End_MainMenu.position.x, End_MainMenu.position.y, 500, 500, 1, 1, 1, MainMenu_Fade);

}

void End_Reset(void)
{
	Kaeru_Fade = 0;
	GameOver_Fade = 0;
	MainMenu_Fade = 0;
	GameOver_Start = 0;
}
