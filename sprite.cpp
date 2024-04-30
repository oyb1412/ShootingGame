#include <d3d9.h>
#include <d3dx9.h>
#include "mydirect3d.h"
#include "texture.h"
#include "sprite.h"

struct Sprite
{
	D3DXVECTOR4 position;
	D3DCOLOR color;
	D3DXVECTOR2 uv;
};

#define FVF_VERTEX2D (D3DFVF_XYZRHW|D3DFVF_DIFFUSE|D3DFVF_TEX1)

static D3DCOLOR g_color = D3DCOLOR_RGBA(255, 255, 255, 255);
LPDIRECT3DVERTEXBUFFER9 g_VertexBuffer = NULL;
LPDIRECT3DINDEXBUFFER9 g_pIndexBuffer = NULL;
void Sprite_Init(void)
{
	
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	pDevice->CreateVertexBuffer(sizeof(Sprite) * 4, D3DUSAGE_WRITEONLY, FVF_VERTEX2D, D3DPOOL_MANAGED,&g_VertexBuffer,NULL );
	pDevice->SetStreamSource(0, g_VertexBuffer, 0, sizeof(Sprite));
	pDevice->SetIndices(g_pIndexBuffer);
	//pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	pDevice->CreateIndexBuffer(sizeof(WORD) * 6, D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_MANAGED, &g_pIndexBuffer, NULL);
	WORD* pIndex;
	g_pIndexBuffer->Lock(0, 0, (void**)&pIndex, D3DLOCK_DISCARD);
	pIndex[0] = 0;
	pIndex[1] = 1;
	pIndex[2] = 2;
	pIndex[3] = 1;
	pIndex[4] = 3;
	pIndex[5] = 2;
	g_pIndexBuffer->Unlock();
}
void Sprite_Uninit(void)
{
	if (g_VertexBuffer) {
		g_VertexBuffer->Release();
		g_VertexBuffer = NULL;
	}
	if (g_pIndexBuffer)
	{
		g_pIndexBuffer->Release();
		g_pIndexBuffer = NULL;
	}
}
void Draw_MiddleStandard(int TextureID, float dx, float dy, float size_x,float size_y, int fade,float Angle)
{
	int w = Texture.GetWidth(TextureID);
	int h = Texture.GetHeight(TextureID);

	D3DXMATRIX  mtxScaling, mtxTransration, mtxITransration, mtxWorld,mtxRotation;

	D3DXMatrixTranslation(&mtxITransration, -dx, -dy, 0.0f);
	D3DXMatrixTranslation(&mtxTransration, dx, dy, 0.0f);
	D3DXMatrixScaling(&mtxScaling, size_x, size_y, 0.0f);
	D3DXMatrixRotationZ(&mtxRotation, Angle);
	mtxWorld = mtxITransration * mtxScaling * mtxRotation * mtxTransration;

	Sprite v[] = {
	{ D3DXVECTOR4(dx - 0.5f * w,dy - 0.5f * h,0.0f,1.0f) ,D3DCOLOR_RGBA(255, 255, 255,  fade), D3DXVECTOR2(0.0f, 0.0f) },
	{ D3DXVECTOR4(dx + 0.5f * w,dy - 0.5f * h,0.0f,1.0f) ,D3DCOLOR_RGBA(255, 255, 255, fade), D3DXVECTOR2(1.0f, 0.0f) },
	{ D3DXVECTOR4(dx - 0.5f * w,dy + 0.5f * h,0.0f,1.0f) ,D3DCOLOR_RGBA(255, 255, 255, fade), D3DXVECTOR2(0.0f, 1.0f) },
	{ D3DXVECTOR4(dx + 0.5f * w,dy + 0.5f * h,0.0f,1.0f) ,D3DCOLOR_RGBA(255, 255, 255, fade), D3DXVECTOR2(1.0f, 1.0f) },
	};

	for (int i = 0; i < 4; i++)
	{
		D3DXVec4Transform(&v[i].position, &v[i].position, &mtxWorld);
	}
	LPDIRECT3DDEVICE9 g_pDevice = GetDevice();
	g_pDevice->SetFVF(FVF_VERTEX2D);
	g_pDevice->SetTexture(0, Texture.Get(TextureID));
	g_pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, v, sizeof(Sprite));
}
void PlusEffect()
{

}
void Sprite_Draw_Change(int textureID, float dx, float dy, float cut_x, float cut_y, float cut_w, float cut_h, float angle, float cx, float cy, float x_change, float y_change, float z_change)
{
	int w = Texture.GetWidth(textureID);
	int h = Texture.GetHeight(textureID);
	D3DXMATRIX mtxR, mtxT, mtxIT, mtxW, mtxS;
	D3DXMatrixTranslation(&mtxT, -cx, -cy, 0.0f);
	D3DXMatrixTranslation(&mtxIT, cx, cy, 0.0f);
	D3DXMatrixRotationZ(&mtxR, angle);
	D3DXMatrixScaling(&mtxS,x_change,y_change,z_change);
	mtxW = mtxT * mtxS*mtxR*mtxIT;
	float u0 = cut_x / (float)w;
	float v0 = cut_y / (float)h;
	float u1 = (cut_x+cut_w) / (float)w;
	float v1 = (cut_y + cut_h) / (float)w;
	Sprite v[] = {
		{ D3DXVECTOR4(dx - 0.5f - 0.5f * cut_w,dy - 0.5f - 0.5f * cut_h,0.0f,1.0f) ,g_color, D3DXVECTOR2(0.0f, 0.0f) },
		{ D3DXVECTOR4(dx - 0.5f + 0.5f * cut_w,dy - 0.5f - 0.5f * cut_h,0.0f,1.0f) ,g_color, D3DXVECTOR2(1.0f, 0.0f) },
		{ D3DXVECTOR4(dx - 0.5f - 0.5f * cut_w,dy - 0.5f + 0.5f * cut_h,0.0f,1.0f) ,g_color, D3DXVECTOR2(0.0f, 1.0f) },
		{ D3DXVECTOR4(dx - 0.5f + 0.5f * cut_w,dy - 0.5f + 0.5f * cut_h,0.0f,1.0f) ,g_color, D3DXVECTOR2(1.0f, 1.0f) }
	};
	D3DXVec4Transform(&v[0].position, &v[0].position, &mtxW);
	D3DXVec4Transform(&v[1].position, &v[1].position, &mtxW);
	D3DXVec4Transform(&v[2].position, &v[2].position, &mtxW);
	D3DXVec4Transform(&v[3].position, &v[3].position, &mtxW);
	LPDIRECT3DDEVICE9 g_pDevice = GetDevice();
	g_pDevice->SetFVF(FVF_VERTEX2D);
	g_pDevice->SetTexture(0, Texture.Get(textureID));
	g_pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, v, sizeof(Sprite));

}
void Sprite_SetColor(D3DCOLOR color)
{
	g_color = color;
}
void Sprite_Draw_No_Tex(float dx, float dy)
{
	int w = 1000;
	int h = 1000;

	Sprite v[] = {
		{ D3DXVECTOR4(dx - 0.5f - 0.3f * w,dy - 0.4f - 0.3f * h,0.0f,1.0f) , D3DCOLOR_RGBA(63, 81, 181, 100), D3DXVECTOR2(0.0f, 0.0f) },
		{ D3DXVECTOR4(dx - 0.5f + 0.3f * w,dy - 0.4f - 0.3f * h,0.0f,1.0f) , D3DCOLOR_RGBA(63, 81, 181, 100), D3DXVECTOR2(1.0f, 0.0f) },
		{ D3DXVECTOR4(dx - 0.5f - 0.3f * w,dy - 0.4f + 0.3f * h,0.0f,1.0f) , D3DCOLOR_RGBA(63, 81, 181, 100), D3DXVECTOR2(0.0f, 1.0f) },
		{ D3DXVECTOR4(dx - 0.5f + 0.3f * w,dy - 0.4f + 0.3f * h,0.0f,1.0f) , D3DCOLOR_RGBA(63, 81, 181, 100), D3DXVECTOR2(1.0f, 1.0f) },

	};

	LPDIRECT3DDEVICE9 g_pDevice = GetDevice();
	g_pDevice->SetFVF(FVF_VERTEX2D);
	g_pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, v, sizeof(Sprite));
}
void Sprite_Drawindex(int textureID, float dx, float dy)//’¸?ƒoƒbƒt?
{
	Sprite * pV;
	g_VertexBuffer->Lock(0, 0, (void**)&pV, D3DLOCK_DISCARD);

	int w = Texture.GetWidth(textureID);
	int h = Texture.GetHeight(textureID);
	
	Sprite v[] = {
		{ D3DXVECTOR4(dx - 0.5f - 0.5f * w,dy - 0.5f - 0.5f * h,0.0f,1.0f) , g_color, D3DXVECTOR2(0.0f, 0.0f) },
		{ D3DXVECTOR4(dx - 0.5f + 0.5f * w,dy - 0.5f - 0.5f * h,0.0f,1.0f) , g_color, D3DXVECTOR2(1.0f, 0.0f) },
		{ D3DXVECTOR4(dx - 0.5f - 0.5f * w,dy - 0.5f + 0.5f * h,0.0f,1.0f) , g_color, D3DXVECTOR2(0.0f, 1.0f) },
		{ D3DXVECTOR4(dx - 0.5f + 0.5f * w,dy - 0.5f + 0.5f * h,0.0f,1.0f) , g_color, D3DXVECTOR2(1.0f, 1.0f) },

	};
	memcpy(pV, v, sizeof(v));
	g_VertexBuffer->Unlock();
	LPDIRECT3DDEVICE9 g_pDevice = GetDevice();
	g_pDevice->SetFVF(FVF_VERTEX2D);
	g_pDevice->SetTexture(0, Texture.Get(textureID));
	WORD index[] = { 0,1,2,1,3,2 };
	g_pDevice->DrawIndexedPrimitiveUP(D3DPT_TRIANGLELIST , 0 , 4 , 2 , index , D3DFMT_INDEX16,v,sizeof(Sprite));
}
void Sprite_Draw_Tex_x_y_angle(int textureID, float dx, float dy, float angle)
{

	int w = Texture.GetWidth(textureID);
	int h = Texture.GetHeight(textureID);
	D3DXMATRIX mtxR, mtxT, mtxIT, mtxW;

	D3DXMatrixTranslation(&mtxT, -dx, -dy, 0.0f);
	D3DXMatrixRotationZ(&mtxR, angle);
	D3DXMatrixTranslation(&mtxIT, dx, dy, 0.0f);

	mtxW = mtxT * mtxR * mtxIT;
	Sprite v[] = {
		{ D3DXVECTOR4(dx - 0.5f - 0.3f * w,dy - 0.4f - 0.3f * h,0.0f,1.0f) , g_color, D3DXVECTOR2(0.0f, 0.0f) },
		{ D3DXVECTOR4(dx - 0.5f + 0.01f * w,dy - 0.4f - 0.3f * h,0.0f,1.0f) , g_color, D3DXVECTOR2(1.0f, 0.0f) },
		{ D3DXVECTOR4(dx - 0.5f - 0.3f * w,dy - 0.4f + 0.01f * h,0.0f,1.0f) , g_color, D3DXVECTOR2(0.0f, 1.0f) },
		{ D3DXVECTOR4(dx - 0.5f + 0.01f * w,dy - 0.4f + 0.01f * h,0.0f,1.0f) , g_color, D3DXVECTOR2(1.0f, 1.0f) },

	};
	D3DXVec4Transform(&v[0].position, &v[0].position, &mtxW);
	D3DXVec4Transform(&v[1].position, &v[1].position, &mtxW);
	D3DXVec4Transform(&v[2].position, &v[2].position, &mtxW);
	D3DXVec4Transform(&v[3].position, &v[3].position, &mtxW);
	LPDIRECT3DDEVICE9 g_pDevice = GetDevice();
	g_pDevice->SetFVF(FVF_VERTEX2D);
	g_pDevice->SetTexture(0, Texture.Get(textureID));
	g_pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, v, sizeof(Sprite));
}
void Sprite_Draw_Tex_x_y(int textureID, float dx, float dy)
{
	int w = Texture.GetWidth(textureID);
	int h = Texture.GetHeight(textureID);

	Sprite v[] = {
		{ D3DXVECTOR4(dx - 0.5f - 0.3f * w,dy - 0.4f - 0.3f * h,0.0f,1.0f) , g_color, D3DXVECTOR2(0.0f, 0.0f) },
		{ D3DXVECTOR4(dx - 0.5f + 0.01f * w,dy - 0.4f - 0.3f * h,0.0f,1.0f) , g_color, D3DXVECTOR2(1.0f, 0.0f) },
		{ D3DXVECTOR4(dx - 0.5f - 0.3f * w,dy - 0.4f + 0.01f * h,0.0f,1.0f) , g_color, D3DXVECTOR2(0.0f, 1.0f) },
		{ D3DXVECTOR4(dx - 0.5f + 0.01f * w,dy - 0.4f + 0.01f * h,0.0f,1.0f) , g_color, D3DXVECTOR2(1.0f, 1.0f) },

	};

	LPDIRECT3DDEVICE9 g_pDevice = GetDevice();
	g_pDevice->SetFVF(FVF_VERTEX2D);
	g_pDevice->SetTexture(0, Texture.Get(textureID));
	g_pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, v, sizeof(Sprite));
}
void Sprite_Draw_Tex_x_y_Fade(int textureID, float dx, float dy,int fade)
{
	int w = Texture.GetWidth(textureID);
	int h = Texture.GetHeight(textureID);

	Sprite v[] = {
		{ D3DXVECTOR4(dx - 0.5f - 0.3f * w,dy - 0.4f - 0.3f * h,0.0f,1.0f) , D3DCOLOR_RGBA(255, 255, 255,  fade), D3DXVECTOR2(0.0f, 0.0f) },
		{ D3DXVECTOR4(dx - 0.5f + 0.01f * w,dy - 0.4f - 0.3f * h,0.0f,1.0f) , D3DCOLOR_RGBA(255, 255, 255, fade), D3DXVECTOR2(1.0f, 0.0f) },
		{ D3DXVECTOR4(dx - 0.5f - 0.3f * w,dy - 0.4f + 0.01f * h,0.0f,1.0f) , D3DCOLOR_RGBA(255, 255, 255, fade), D3DXVECTOR2(0.0f, 1.0f) },
		{ D3DXVECTOR4(dx - 0.5f + 0.01f * w,dy - 0.4f + 0.01f * h,0.0f,1.0f) , D3DCOLOR_RGBA(255, 255, 255, fade), D3DXVECTOR2(1.0f, 1.0f) },

	};

	LPDIRECT3DDEVICE9 g_pDevice = GetDevice();
	g_pDevice->SetFVF(FVF_VERTEX2D);
	g_pDevice->SetTexture(0, Texture.Get(textureID));
	g_pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, v, sizeof(Sprite));
}
void Sprite_Draw_Tex_x_y_cx_cy_cw_ch(int textureID, float dx, float dy, float cut_x, float cut_y, float cut_w, float cut_h)
{
	int w = Texture.GetWidth(textureID);
	int h = Texture.GetHeight(textureID);

	float u0 = cut_x / (float)w;
	float v0 = cut_y / (float)h;
	float u1 = (cut_x + cut_w) / (float)w;
	float v1 = (cut_y + cut_h) / (float)h;

	Sprite v[] = {
		{ D3DXVECTOR4(dx - 0.5f - 0.5f * cut_w,dy - 0.5f - 0.5f * cut_h,0.0f,1.0f) , g_color, D3DXVECTOR2(u0, v0) },
		{ D3DXVECTOR4(dx - 0.5f + 0.5f * cut_w,dy - 0.5f - 0.5f * cut_h,0.0f,1.0f) , g_color, D3DXVECTOR2(u1, v0) },
		{ D3DXVECTOR4(dx - 0.5f - 0.5f * cut_w,dy - 0.5f + 0.5f * cut_h,0.0f,1.0f) , g_color, D3DXVECTOR2(u0, v1) },
		{ D3DXVECTOR4(dx - 0.5f + 0.5f * cut_w,dy - 0.5f + 0.5f * cut_h,0.0f,1.0f) , g_color, D3DXVECTOR2(u1, v1) },

	};
	LPDIRECT3DDEVICE9 g_pDevice = GetDevice();
	g_pDevice->SetFVF(FVF_VERTEX2D);
	g_pDevice->SetTexture(0, Texture.Get(textureID));
	g_pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, v, sizeof(Sprite));
}
void Sprite_Draw_Tex_x_y_cx_cy_xc_yc_zc(int textureID, float dx, float dy,  float cx, float cy, float x_change, float y_change, float z_change)
{
	int w = Texture.GetWidth(textureID);
	int h = Texture.GetHeight(textureID);

	D3DXMATRIX mtxW,  mtxT, mtxIT, mtxS;

	D3DXMatrixTranslation(&mtxT, -cx, -cy, 0.0f);
	D3DXMatrixTranslation(&mtxIT, cx, cy, 0.0f);
	D3DXMatrixScaling(&mtxS, x_change, y_change, z_change);

	mtxW = mtxT * mtxS * mtxIT;


	Sprite v[] = {
		{ D3DXVECTOR4(dx - 0.5f - 0.5f * w,dy - 0.5f - 0.5f * h,0.0f,1.0f) , g_color, D3DXVECTOR2(0, 0) },
		{ D3DXVECTOR4(dx - 0.5f + 0.5f * w,dy - 0.5f - 0.5f * h,0.0f,1.0f) , g_color, D3DXVECTOR2(1, 0) },
		{ D3DXVECTOR4(dx - 0.5f - 0.5f * w,dy - 0.5f + 0.5f * h,0.0f,1.0f) , g_color, D3DXVECTOR2(0, 1) },
		{ D3DXVECTOR4(dx - 0.5f + 0.5f * w,dy - 0.5f + 0.5f * h,0.0f,1.0f) , g_color, D3DXVECTOR2(1, 1) },

	};

	D3DXVec4Transform(&v[0].position, &v[0].position, &mtxW);
	D3DXVec4Transform(&v[1].position, &v[1].position, &mtxW);
	D3DXVec4Transform(&v[2].position, &v[2].position, &mtxW);
	D3DXVec4Transform(&v[3].position, &v[3].position, &mtxW);

	LPDIRECT3DDEVICE9 g_pDevice = GetDevice();
	g_pDevice->SetFVF(FVF_VERTEX2D);
	g_pDevice->SetTexture(0, Texture.Get(textureID));
	g_pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, v, sizeof(Sprite));
}
void Sprite_Draw_Tex_x_y_cx_cy_xc_yc_zc_fade(int textureID, float dx, float dy, float cx, float cy, float x_change, float y_change, float z_change,int fade)
{
	int w = Texture.GetWidth(textureID);
	int h = Texture.GetHeight(textureID);

	D3DXMATRIX mtxW, mtxT, mtxIT, mtxS;

	D3DXMatrixTranslation(&mtxT, -cx, -cy, 0.0f);
	D3DXMatrixTranslation(&mtxIT, cx, cy, 0.0f);
	D3DXMatrixScaling(&mtxS, x_change, y_change, z_change);

	mtxW = mtxT * mtxS * mtxIT;


	Sprite v[] = {
		{ D3DXVECTOR4(dx - 0.5f - 0.5f * w,dy - 0.5f - 0.5f * h,0.0f,1.0f) , D3DCOLOR_RGBA(255, 255, 255,  fade), D3DXVECTOR2(0, 0) },
		{ D3DXVECTOR4(dx - 0.5f + 0.5f * w,dy - 0.5f - 0.5f * h,0.0f,1.0f) , D3DCOLOR_RGBA(255, 255, 255,  fade), D3DXVECTOR2(1, 0) },
		{ D3DXVECTOR4(dx - 0.5f - 0.5f * w,dy - 0.5f + 0.5f * h,0.0f,1.0f) , D3DCOLOR_RGBA(255, 255, 255,  fade), D3DXVECTOR2(0, 1) },
		{ D3DXVECTOR4(dx - 0.5f + 0.5f * w,dy - 0.5f + 0.5f * h,0.0f,1.0f) , D3DCOLOR_RGBA(255, 255, 255,  fade), D3DXVECTOR2(1, 1) },

	};

	D3DXVec4Transform(&v[0].position, &v[0].position, &mtxW);
	D3DXVec4Transform(&v[1].position, &v[1].position, &mtxW);
	D3DXVec4Transform(&v[2].position, &v[2].position, &mtxW);
	D3DXVec4Transform(&v[3].position, &v[3].position, &mtxW);

	LPDIRECT3DDEVICE9 g_pDevice = GetDevice();
	g_pDevice->SetFVF(FVF_VERTEX2D);
	g_pDevice->SetTexture(0, Texture.Get(textureID));
	g_pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, v, sizeof(Sprite));
}

void Sprite_Draw(int textureID, float x, float y, float size, float cut_x, float cut_y, float cut_w, float cut_h)
{
	int w = Texture.GetWidth(textureID);
	int h = Texture.GetHeight(textureID);
	float u0 = cut_x;
	float v0 = cut_y;
	float u1 = (cut_x + cut_w);
	float v1 = (cut_y + cut_h);
	D3DXMATRIX matTrans, matWorld, matScal, mtxITransration;
	D3DXMatrixTranslation(&mtxITransration, -x, -y, 0.0f);
	D3DXMatrixTranslation(&matTrans, x, y, 0.0f);
	D3DXMatrixScaling(&matScal, size, size, 0.0f);
	matWorld = mtxITransration * matScal * matTrans;


	CUBEVERTEX Cube[] = {
	{ D3DXVECTOR4(x - 0.5f * w,y - 0.5f * h,0.0f,1.0f) ,D3DCOLOR_RGBA(255, 255, 255,  255), D3DXVECTOR2(u0, v0) },
	{ D3DXVECTOR4(x + 0.5f * w,y - 0.5f * h,0.0f,1.0f) ,D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(u1, v0) },
	{ D3DXVECTOR4(x - 0.5f * w,y + 0.5f * h,0.0f,1.0f) ,D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(u0, v1) },
	{ D3DXVECTOR4(x + 0.5f * w,y + 0.5f * h,0.0f,1.0f) ,D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(u1, v1) },
	};
	for (int i = 0; i < 4; i++)
	{
		D3DXVec4Transform(&Cube[i].Position, &Cube[i].Position, &matWorld);
	}
	LPDIRECT3DDEVICE9 g_pDevice = GetDevice();
	g_pDevice->SetFVF(FVF_VERTEX2D);
	g_pDevice->SetTexture(0, Texture.Get(textureID));
	g_pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, Cube, sizeof(CUBEVERTEX));
}