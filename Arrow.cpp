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
#include "Arrow.h"
#include "Debug.h"
#define ARROW_POSITION_X 200.0f
#define ARROW_POSITION_Y_UP 690.0f
#define ARROW_POSITION_Y_DOWN 840.0f
#define ARROW_SIZE_X 100
#define ARROW_SIZE_Y 100
#define ARROW_UP 690
#define ARROW_DOWN 840 
#define FADE_MAX 255
#define TEX_MAX 5
static short tex[TEX_MAX];
static short Arrow_Fade = 0;
static short Arrow_Fade_Begin = 0;
static bool Arrow_Choice = true;
static short Arrow_Sound = 0;
struct arrow
{
	D3DXVECTOR2 position;
	D3DCOLOR color;
	D3DXVECTOR2 uv;
	D3DXVECTOR2 size;
	bool Visible;
};
static struct arrow Arrow;
void Arrow_Init(void)
{
	Arrow.position.x = ARROW_POSITION_X;
	Arrow.position.y = ARROW_POSITION_Y_UP;
	Arrow.size.x = ARROW_SIZE_X;
	Arrow.size.y = ARROW_SIZE_Y;
	Arrow.Visible = true;
//	tex[0] = Texture_SetLoadFile("Accet/Texture/Arrow.png", Arrow.size.x, Arrow.size.y);
}
void Arrow_Update(short i)
{
	Arrow_Fade_Begin += 1;
	Arrow_Sound += 1;
	if (Arrow_Fade_Begin >= i)
	{
		Arrow_Fade = FADE_MAX;
	}
	if (Keyboard_IsPress(DIK_W) && Arrow_Fade >= FADE_MAX && Arrow_Sound >= 10 && Arrow.position.y == ARROW_DOWN)
	{
		Arrow.position.y = ARROW_UP;
		Arrow_Choice = true;
		PlaySound(SOUND_LABEL_SE_CHOICE);
		Arrow_Sound = 0;
	}
	if (Keyboard_IsPress(DIK_S) && Arrow_Fade >= FADE_MAX && Arrow_Sound >= 10 && Arrow.position.y == ARROW_UP)
	{
		Arrow.position.y = ARROW_DOWN;
		Arrow_Choice = false;
		PlaySound(SOUND_LABEL_SE_CHOICE);
		Arrow_Sound = 0;
	}
}
void Arrow_Draw(short i)
{
	Sprite_Draw_Tex_x_y_cx_cy_xc_yc_zc_fade(tex[0], Arrow.position.x, Arrow.position.y+i, 500, 500, 1, 1, 1, Arrow_Fade);
}
void Arrow_Reset(void)
{
	Arrow_Fade = 0;
	Arrow_Fade_Begin = 0;
	Arrow_Choice = true;
	Arrow_Sound = 0;
}
bool Arrow_Start(void)
{
	if (Arrow_Choice) 
	{ 
		return true;
	}
	else
	{
		return false;
	}
}