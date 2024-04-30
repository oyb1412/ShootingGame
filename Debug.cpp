#include <d3d9.h>
#include <d3dx9.h>
#include "Collision.h"
#include "mydirect3d.h"

#define DEBUG_CIRCLE_VERTEX_NUM (8)
#define DEBUG_CIRCLE_MAX (4096)

typedef struct DebugCircleVertex_Tag
{
	D3DXVECTOR4 position;
	D3DCOLOR color;
}DebugCircleVertex;
#define FVF_DEBUG_CIRCLE_VERTEX (D3DFVF_XYZRHW|D3DFVF_DIFFUSE)

LPDIRECT3DVERTEXBUFFER9 pVertexBuffer = NULL;
LPDIRECT3DINDEXBUFFER9 pIndexBuffer = NULL;
D3DCOLOR g_color = D3DCOLOR_RGBA(255, 255, 255, 255);
D3DCOLOR g_colors[DEBUG_CIRCLE_MAX];
Circle g_Circles[DEBUG_CIRCLE_MAX];
short g_CirclecCount = 0;
void Debug_Init(void)
{
#if defined(_DEBUG) || defined(DEBUG)

	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	pDevice->CreateVertexBuffer(sizeof(DebugCircleVertex) *DEBUG_CIRCLE_VERTEX_NUM* DEBUG_CIRCLE_MAX, D3DUSAGE_WRITEONLY, FVF_DEBUG_CIRCLE_VERTEX, D3DPOOL_MANAGED, &pVertexBuffer, NULL);
	pDevice->CreateIndexBuffer(sizeof(WORD) * DEBUG_CIRCLE_VERTEX_NUM*2* DEBUG_CIRCLE_MAX , D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_MANAGED, &pIndexBuffer, NULL);
#endif // _DEBUG || DEBU

}
void Debug_Uninit(void)
{
#if defined(_DEBUG) || defined(DEBUG)

#endif // _DEBUG || DEBU
}
void Debug_DrawCircle(float x, float y, float radius)
{
	if (g_CirclecCount >= DEBUG_CIRCLE_MAX)
	{
		MessageBox(0, "—Ìˆæ‚ð’´‚¦‚Ä‘‚«ž‚à‚¤‚Æ‚µ‚Ä‚¢‚Ü‚·", "ƒGƒ‰[", MB_OKCANCEL | MB_DEFBUTTON2);
	}
	else
	{
#if defined(_DEBUG) || defined(DEBUG)

		g_colors[g_CirclecCount] = g_color;
		g_Circles[g_CirclecCount].position.x = x;
		g_Circles[g_CirclecCount].position.y = y;
		g_Circles[g_CirclecCount].radius = radius;
		g_CirclecCount++;
#endif // _DEBUG || DEBU
	}

}
void Debug_SetColor(D3DCOLOR color)
{
#if defined(_DEBUG) || defined(DEBUG)

	g_color = color;
#endif // _DEBUG || DEBU

}
void Debug_Begin(void)
{
#if defined(_DEBUG) || defined(DEBUG)
	g_CirclecCount = 0;
#endif // _DEBUG || DEBU

}
void Debug_End(void)
{
#if defined(_DEBUG) || defined(DEBUG)

	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	static const float A = D3DX_PI * 2.0f / DEBUG_CIRCLE_VERTEX_NUM;
	DebugCircleVertex* pV;
	pVertexBuffer->Lock(0, 0, (void**)&pV, D3DLOCK_DISCARD);
	for (short i = 0; i < g_CirclecCount; i++)
	{
		int startIndex = i * DEBUG_CIRCLE_VERTEX_NUM;
		for (short j = 0; j < DEBUG_CIRCLE_VERTEX_NUM; j++)
		{
			pV[startIndex + j].position.x = cosf(A*j)*g_Circles[i].radius + g_Circles[i].position.x;
			pV[startIndex + j].position.y = sinf(A*j)*g_Circles[i].radius + g_Circles[i].position.y;
			pV[startIndex + j].position.z = 0.0f;
			pV[startIndex + j].position.w = 1.0f;
			pV[startIndex + j].color = g_colors[i];
		}
	}
	pVertexBuffer->Unlock();

	WORD* pI;
	pIndexBuffer->Lock(0, 0, (void**)&pI, D3DLOCK_DISCARD);
	for (short i = 0; i < g_CirclecCount; i++)
	{
		int startIndex =  DEBUG_CIRCLE_VERTEX_NUM * 2*i;
		for (short j = 0; j < DEBUG_CIRCLE_VERTEX_NUM; j++)
		{
			pI[startIndex +0+j*2] = startIndex + j;
			pI[startIndex +1+j*2] = startIndex + ((j + 1) % DEBUG_CIRCLE_VERTEX_NUM);
		}
	}
	pIndexBuffer->Unlock();
	pDevice->SetStreamSource(0, pVertexBuffer, 0, sizeof(DebugCircleVertex));
	pDevice->SetIndices(pIndexBuffer);
	pDevice->SetFVF(FVF_DEBUG_CIRCLE_VERTEX);
	pDevice->SetTexture(0, NULL);
	pDevice->DrawIndexedPrimitive(D3DPT_LINELIST, 0, 0, g_CirclecCount * DEBUG_CIRCLE_VERTEX_NUM, 0, g_CirclecCount * DEBUG_CIRCLE_VERTEX_NUM);
#endif // _DEBUG || DEBU

}