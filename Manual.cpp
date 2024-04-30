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
#define MANUAL_BG_POSITION_X 500
#define MANUAL_BG_POSITION_Y 500
#define MANUAL_BG_SIZE_X 184
#define MANUAL_BG_SIZE_Y 300
#define MANUAL_IMAGE_POSITION_X 500
#define MANUAL_IMAGE_POSITION_Y 300
#define MANUAL_IMAGE_SIZE_X 700
#define MANUAL_IMAGE_SIZE_Y 400
#define MANUAL_TEXT_POSITION_X 500
#define MANUAL_TEXT_POSITION_Y 750
#define MANUAL_TEXT_SIZE_X 500
#define MANUAL_TEXT_SIZE_Y 500
#define TEX_MAX 5
struct manual_bg
{
	D3DXVECTOR2 position;
	D3DCOLOR color;
	D3DXVECTOR2 uv;
	D3DXVECTOR2 size;
	bool Visible;
};
static manual_bg Manual_Bg;
struct manual_image
{
	D3DXVECTOR2 position;
	D3DCOLOR color;
	D3DXVECTOR2 uv;
	D3DXVECTOR2 size;
	bool Visible;
};
static manual_image Manual_Image;
struct manual_text
{
	D3DXVECTOR2 position;
	D3DCOLOR color;
	D3DXVECTOR2 uv;
	D3DXVECTOR2 size;
	bool Visible;
};
static manual_text Manual_Text;

static int tex[TEX_MAX];

void Manual_Init(void)
{
	Manual_Bg.position.x = MANUAL_BG_POSITION_X;
	Manual_Bg.position.y = MANUAL_BG_POSITION_Y;
	Manual_Bg.size.x = MANUAL_BG_SIZE_X;
	Manual_Bg.size.y = MANUAL_BG_SIZE_Y;
	Manual_Bg.Visible = true;
	Manual_Image.position.x = MANUAL_IMAGE_POSITION_X;
	Manual_Image.position.y = MANUAL_IMAGE_POSITION_Y;
	Manual_Image.size.x = MANUAL_IMAGE_SIZE_X;
	Manual_Image.size.y = MANUAL_IMAGE_SIZE_Y;
	Manual_Image.Visible = true;
	Manual_Text.position.x = MANUAL_TEXT_POSITION_X;
	Manual_Text.position.y = MANUAL_TEXT_POSITION_Y;
	Manual_Text.size.x = MANUAL_TEXT_SIZE_X;
	Manual_Text.size.y = MANUAL_TEXT_SIZE_Y;
	Manual_Text.Visible = true;
//	tex[0] = Texture_SetLoadFile("Accet/Texture/Manual_Bg.jpg", Manual_Bg.size.x, Manual_Bg.size.y);
//	tex[1] = Texture_SetLoadFile("Accet/Texture/Manual_Image.png", Manual_Image.size.x, Manual_Image.size.y);
//	tex[2] = Texture_SetLoadFile("Accet/Texture/Manual_Text.png", Manual_Text.size.x, Manual_Text.size.y);
}
void Manual_Draw(void)
{
	Sprite_Draw_Tex_x_y_cx_cy_xc_yc_zc(tex[0], Manual_Bg.position.x, Manual_Bg.position.y, 500, 500, (float)5.5, (float)3.7, 1);
	Sprite_Draw_Tex_x_y_cx_cy_xc_yc_zc(tex[1], Manual_Image.position.x, Manual_Image.position.y, 500, 500, 1, 1, 1);
	Sprite_Draw_Tex_x_y_cx_cy_xc_yc_zc(tex[2], Manual_Text.position.x, Manual_Text.position.y, 500, 500, 1, 1, 1);
}