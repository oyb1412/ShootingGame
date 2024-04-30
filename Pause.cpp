#include "texture.h"
#include <d3d9.h>
#include <tchar.h>
#include <d3dx9.h>
#include <windows.h>
#include "sprite.h"

#define PAUSE_POSITION_X 500
#define PAUSE_POSITION_Y 500
#define PAUSE_SIZE_X 60000
#define PAUSE_SIZE_Y 60000
#define PAUSE_TEXT_POSITION_X 500
#define PAUSE_TEXT_POSITION_Y 350
#define PAUSE_TEXT_SIZE_X 500
#define PAUSE_TEXT_SIZE_Y 150
#define PAUSE_CONTINUE_POSITION_X 500
#define PAUSE_CONTINUE_POSITION_Y 700
#define PAUSE_CONTINUE_SIZE_X 350
#define PAUSE_CONTINUE_SIZE_Y 80
#define PAUSE_MAINMENU_POSITION_X 500
#define PAUSE_MAINMENU_POSITION_Y 850
#define PAUSE_MAINMENU_SIZE_X 350
#define PAUSE_MAINMENU_SIZE_Y 80
#define FADE_MAX 255
#define TEX_MAX 5
static int tex[TEX_MAX];
static int Pause_Fade = 110;
static int Pause_Text_Fade = FADE_MAX;
static int Pause_Continue_Fade = FADE_MAX;
static int Pause_Mainmenu_Fade = FADE_MAX;

struct pause
{
	D3DXVECTOR2 Position;
	D3DCOLOR Color;
	D3DXVECTOR2 uv;
	D3DXVECTOR2 size;
	bool Visible;
};
static struct pause Pause;

struct pause_text
{
	D3DXVECTOR2 Position;
	D3DCOLOR Color;
	D3DXVECTOR2 uv;
	D3DXVECTOR2 size;
	bool Visible;
};
static struct pause_text Pause_Text;

struct pause_continue
{
	D3DXVECTOR2 Position;
	D3DCOLOR Color;
	D3DXVECTOR2 uv;
	D3DXVECTOR2 size;
	bool Visible;
};
static struct pause_continue Pause_Continue;

struct pause_mainmenu
{
	D3DXVECTOR2 Position;
	D3DCOLOR Color;
	D3DXVECTOR2 uv;
	D3DXVECTOR2 size;
	bool Visible;
};
static struct pause_mainmenu Pause_Mainmenu;
void Pause_Init(void)
{
	Pause.Position.x = PAUSE_POSITION_X;
	Pause.Position.y = PAUSE_POSITION_Y;
	Pause.size.x = PAUSE_SIZE_X;
	Pause.size.y = PAUSE_SIZE_Y;
	Pause.Visible = false;
	Pause_Text.Position.x = PAUSE_TEXT_POSITION_X;
	Pause_Text.Position.y = PAUSE_TEXT_POSITION_Y;
	Pause_Text.size.x = PAUSE_TEXT_SIZE_X;
	Pause_Text.size.y = PAUSE_TEXT_SIZE_Y;
	Pause_Text.Visible = false;
	Pause_Continue.Position.x = PAUSE_CONTINUE_POSITION_X;
	Pause_Continue.Position.y = PAUSE_CONTINUE_POSITION_Y;
	Pause_Continue.size.x = PAUSE_CONTINUE_SIZE_X;
	Pause_Continue.size.y = PAUSE_CONTINUE_SIZE_Y;
	Pause_Continue.Visible = false;
	Pause_Mainmenu.Position.x = PAUSE_MAINMENU_POSITION_X;
	Pause_Mainmenu.Position.y = PAUSE_MAINMENU_POSITION_Y;
	Pause_Mainmenu.size.x = PAUSE_MAINMENU_SIZE_X;
	Pause_Mainmenu.size.y = PAUSE_MAINMENU_SIZE_Y;
	Pause_Mainmenu.Visible = false;
//	tex[0] = Texture_SetLoadFile("Accet/Texture/Pause.png", Pause.size.x, Pause.size.y);
//	tex[1] = Texture_SetLoadFile("Accet/Texture/Pause_Text.png", Pause_Text.size.x, Pause_Text.size.y);
//	tex[2] = Texture_SetLoadFile("Accet/Texture/Continue.png", Pause_Continue.size.x, Pause_Continue.size.y);
//	tex[3] = Texture_SetLoadFile("Accet/Texture/Main_Menu_Pause.png", Pause_Mainmenu.size.x, Pause_Mainmenu.size.y);

}

void Pause_Draw(void)
{
	Sprite_Draw_Tex_x_y_Fade(tex[0], Pause.Position.x, Pause.Position.y, Pause_Fade);
	Sprite_Draw_Tex_x_y_cx_cy_xc_yc_zc_fade(tex[1], Pause_Text.Position.x, Pause_Text.Position.y, 500, 500, 1, 1, 1, Pause_Text_Fade);
	Sprite_Draw_Tex_x_y_cx_cy_xc_yc_zc_fade(tex[2], Pause_Continue.Position.x, Pause_Continue.Position.y, 500, 500, 1, 1, 1, Pause_Continue_Fade);
	Sprite_Draw_Tex_x_y_cx_cy_xc_yc_zc_fade(tex[3], Pause_Mainmenu.Position.x, Pause_Mainmenu.Position.y, 500, 500, 1, 1, 1, Pause_Mainmenu_Fade);
}