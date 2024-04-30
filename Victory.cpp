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
#include "sound.h"
#include "palyer.h"
#include "judgement.h"
#include "Debug.h"
#define VICTORY_BG_POSITION_X 500.0f
#define VICTORY_BG_POSITION_Y 500.0f
#define VICTORY_BG_SIZE_X 184
#define VICTORY_BG_SIZE_Y 300
#define VICTORY_TEXT_POSITION_X 500.0f
#define VICTORY_TEXT_POSITION_Y 200.0f
#define VICTORY_TEXT_SIZE_X 800
#define VICTORY_TEXT_SIZE_Y 250
#define VICTORY_MAINMENU_POSITION_X 500.0f
#define VICTORY_MAINMENU_POSITION_Y 750.0f
#define VICTORY_MAINMENU_SIZE_X 450
#define VICTORY_MAINMENU_SIZE_Y 150
static int tex[5];
struct victory_bg
{
	D3DXVECTOR2 position;
	D3DCOLOR color;
	D3DXVECTOR2 uv;
	D3DXVECTOR2 size;
	bool Vibisle;
};
static victory_bg Victory_Bg;

struct victory_text
{
	D3DXVECTOR2 position;
	D3DCOLOR color;
	D3DXVECTOR2 uv;
	D3DXVECTOR2 size;
	bool Vibisle;
};
static victory_text Victory_text;

struct victory_mainmenu
{
	D3DXVECTOR2 position;
	D3DCOLOR color;
	D3DXVECTOR2 uv;
	D3DXVECTOR2 size;
	bool Vibisle;
};
static victory_mainmenu Victory_mainmenu;



void Victory_Init(void)
{
	Victory_Bg.Vibisle = true;
	Victory_Bg.position.x = VICTORY_BG_POSITION_X;
	Victory_Bg.position.y = VICTORY_BG_POSITION_Y;
	Victory_Bg.size.x = VICTORY_BG_SIZE_X;
	Victory_Bg.size.y = VICTORY_BG_SIZE_Y;
	Victory_text.Vibisle = true;
	Victory_text.position.x = VICTORY_TEXT_POSITION_X;
	Victory_text.position.y = VICTORY_TEXT_POSITION_Y;
	Victory_text.size.x = VICTORY_TEXT_SIZE_X;
	Victory_text.size.y = VICTORY_TEXT_SIZE_Y;
	Victory_mainmenu.Vibisle = true;
	Victory_mainmenu.position.x = VICTORY_MAINMENU_POSITION_X;
	Victory_mainmenu.position.y = VICTORY_MAINMENU_POSITION_Y;
	Victory_mainmenu.size.x = VICTORY_MAINMENU_SIZE_X;
	Victory_mainmenu.size.y = VICTORY_MAINMENU_SIZE_Y;
	
//	tex[0] = Texture_SetLoadFile("Accet/Texture/Victory_Bg.png", Victory_Bg.size.x, Victory_Bg.size.y);
//	tex[1] = Texture_SetLoadFile("Accet/Texture/Victory_Text.png", Victory_text.size.x, Victory_text.size.y);
//	tex[2] = Texture_SetLoadFile("Accet/Texture/Main_Menu_Text.png", Victory_mainmenu.size.x, Victory_mainmenu.size.y);

}

void Victory_Draw(void)
{
	Sprite_Draw_Tex_x_y_cx_cy_xc_yc_zc(tex[0], Victory_Bg.position.x, Victory_Bg.position.y, 500, 500, (float)5.5, (float)3.7, 1);
	Sprite_Draw_Tex_x_y_cx_cy_xc_yc_zc(tex[1], Victory_text.position.x, Victory_text.position.y, 500, 500, 1, 1, 1);
	Sprite_Draw_Tex_x_y_cx_cy_xc_yc_zc(tex[2], Victory_mainmenu.position.x, Victory_mainmenu.position.y, 500, 500, 1, 1, 1);
}
