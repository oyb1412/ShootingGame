#pragma once
#include <d3d9.h>
#include <d3dx9.h>
struct CUBEVERTEX
{
	D3DXVECTOR4 Position;
	DWORD color;
	D3DXVECTOR2 uv;
};
#define FVF_PCT (D3DFVF_XYZ | D3DFVF_DIFFUSE|D3DFVF_TEX1)
#define FVF_VERTEX2D (D3DFVF_XYZRHW|D3DFVF_DIFFUSE|D3DFVF_TEX1) //X궴Y궴Z궴RHW귩귖궰뮯?긢??귩?궥
void Sprite_Init();
void Sprite_Uninit();
void Sprite_Drawindex(int textureID, float dx, float dy);
void Sprite_Draw_Tex_x_y_cx_cy_cw_ch(int textureID, float dx, float dy, float cut_x, float cut_y, float cut_w, float cut_h);
void Sprite_Draw_Tex_x_y_cx_cy_xc_yc_zc(int textureID, float dx, float dy, float cx, float cy, float x_change, float y_change, float z_change);
void Sprite_Draw_Tex_x_y_angle(int textureID, float dx, float dy, float angle);
void Sprite_Draw_Tex_x_y(int textureID, float dx, float dy);
void Sprite_Draw_No_Tex(float dx, float dy);
void Sprite_Draw_Tex_x_y_Fade(int textureID, float dx, float dy, int fade);
void Sprite_Draw_Tex_x_y_cx_cy_xc_yc_zc_fade(int textureID, float dx, float dy, float cx, float cy, float x_change, float y_change, float z_change, int fade);
void Sprite_SetColor(D3DCOLOR color);
void Sprite_Draw(int textureID, float x, float y, float size, float cut_x, float cut_y, float cut_w, float cut_h);
void Draw_MiddleStandard(int TextureID, float dx, float dy, float size_x, float size_y, int fade = 255, float Angle = 0);
void Sprite_Draw_Change(int textureID, float dx, float dy, float cut_x, float cut_y, float cut_w, float cut_h, float angle, float cx, float cy, float x_change, float y_change, float z_change);