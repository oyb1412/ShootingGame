#include "common.h"
#include <d3d9.h>
#include <d3dx9.h>
#include "mydirect3d.h"
#include "texture.h"
#include "sprite.h"
#include "pluseffect.h"
#include "sound.h"
#include "debug.h"

int g_PlusEffectFrameCount = 0;
static float Size = 0;
struct pluseffect
{
	D3DXVECTOR2 size;
	int Texture;
	D3DXVECTOR2 Position;
	bool Visivle;
	int LifeFrame;			
	int SpawnFrame;			
	D3DCOLOR Color;
	float Showsize;
};
pluseffect PlusEffect[PLUSEFFECT_MAX] = {};

void PlusEffect_Init(void)
{
	g_PlusEffectFrameCount = 0;
	Size = 0;
	for (int i = 0; i < PLUSEFFECT_MAX; i++)
	{
		PlusEffect[i].size.x = 100;
		PlusEffect[i].size.y =100;
		//PlusEffect[i].Texture = Texture_SetLoadFile("Accet/Texture/Missile.jpg", PlusEffect[i].size.x, PlusEffect[i].size.y);
		PlusEffect[i].Visivle = false;
		PlusEffect[i].LifeFrame = 0;
		PlusEffect[i].SpawnFrame = -1;
		PlusEffect[i].Showsize = 1;
	}
}

void PlusEffect_Update(void)
{
	for (int i = 0; i < PLUSEFFECT_MAX; i++)
	{
		if (PlusEffect[i].Visivle)
		{
			//PlusEffect[i].size.x -= 1;
			//PlusEffect[i].size.y -= 1;

			int elapsedFrame = g_PlusEffectFrameCount - PlusEffect[i].SpawnFrame;

			float e = elapsedFrame / (float)PlusEffect[i].LifeFrame;

			if (e > 1.0f)
			{
				e = 1.0f;
				PlusEffect[i].LifeFrame = 0;
				PlusEffect[i].SpawnFrame = -1;
				PlusEffect[i].Visivle = false;
			}

			D3DXCOLOR color = PlusEffect[i].Color;
			color.a = 1.0f - e;
			PlusEffect[i].Color = color;
			PlusEffect[i].Showsize = 1 - e / 2;
		}
	}
	g_PlusEffectFrameCount++;
}

void PlusEffect_Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);		
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);	
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);		
	for (int i = 0; i < PLUSEFFECT_MAX; i++)
	{
		if (PlusEffect[i].Visivle)
		{
			Sprite_SetColor(PlusEffect[i].Color);
			Sprite_Draw_Change(Texture.Tex[Player_Texture_Auto_Bullet], PlusEffect[i].Position.x, PlusEffect[i].Position.y, 0, 0, PlusEffect[i].size.x, PlusEffect[i].size.y, 0, PlusEffect[i].Position.x, PlusEffect[i].Position.y, PlusEffect[i].Showsize, PlusEffect[i].Showsize, 0);
		
		}
	}
	Sprite_SetColor(D3DCOLOR_RGBA(255, 255, 255, 255));
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);		
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);	
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

void PlusEffect_Uninit(void)
{

}

void PlusEffect_Creat(float x, float y,D3DCOLOR color,int lifeframe,int size)
{
	for (int i = 0; i < PLUSEFFECT_MAX; i++)
	{
		if (!PlusEffect[i].Visivle)
		{
			PlusEffect[i].Position.x = x;
			PlusEffect[i].Position.y = y;
			PlusEffect[i].Color = color;
			PlusEffect[i].LifeFrame = lifeframe;
			PlusEffect[i].SpawnFrame = g_PlusEffectFrameCount;
			PlusEffect[i].size.x = 80;
			PlusEffect[i].size.y = 80;
			PlusEffect[i].Visivle = true;

			break;
		}
	}
}
