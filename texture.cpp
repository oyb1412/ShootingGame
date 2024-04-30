#include "texture.h"
#include <d3d9.h>
#include <d3dx9.h>
#include <windows.h>
#include "mydirect3d.h"
void tag_Texture::Init()
{
	Tex[Player_Texture] =SetLoadFile("Accet/Texture/Player.png", 100, 100);
	Tex[Player_Texture_Life] = SetLoadFile("Accet/Texture/Heart.png", 100, 100);
	Tex[Player_Texture_Bullet] = SetLoadFile("Accet/Texture/Player_Bullet.png", 100, 100);
	Tex[Player_Texture_Ult] = SetLoadFile("Accet/Texture/Ult.png", 100, 100);
	Tex[Player_Texture_Bullet_Effect] = SetLoadFile("Accet/Texture/Player_Bullet_Effect.png", 100, 100);
	Tex[Player_Texture_Distroy_Effect] = SetLoadFile("Accet/Texture/Player_Distroy_Effect.png", 100, 100);
	Tex[Player_Texture_Auto_Bullet] = SetLoadFile("Accet/Texture/Auto_Bullet.jpg", 100,100);
	Tex[Player_Texture_Auto_Bullet_Effect] = SetLoadFile("Accet/Texture/Auto_Bullet_Effect.png", 100, 100);

	Tex[BG_Texture] = SetLoadFile("Accet/Texture/bg.png", SCREEN_WIDTH, SCREEN_HEIGHT*2);
	Tex[Enemy_Texture_1] = SetLoadFile("Accet/Texture/Enemy.png", 100, 100);
	Tex[Enemy_Texture_2] = SetLoadFile("Accet/Texture/Enemy2.png", 100, 100);
	Tex[Enemy_Texture_3] = SetLoadFile("Accet/Texture/Enemy3.png", 100, 100);
	Tex[Enemy_Texture_4] = SetLoadFile("Accet/Texture/Enemy4.png", 100, 100);
	Tex[Enemy_Texture_5] = SetLoadFile("Accet/Texture/Enemy5.png", 100, 100);
	Tex[Enemy_Boss_Texture] = SetLoadFile("Accet/Texture/Boss.png", 600, 200);
	Tex[Enemy_Boss_Texture_Life] = SetLoadFile("Accet/Texture/Boss_Hp.png", 3, 80);
	Tex[Enemy_Texture_Bullet] = SetLoadFile("Accet/Texture/Enemy_Bullet.png", 100, 100);
	Tex[Enemy_Texture_Bullet2] = SetLoadFile("Accet/Texture/Enemy_Bullet2.png", 100, 100);
	Tex[Enemy_Texture_Bullet_Effect] = SetLoadFile("Accet/Texture/Enemy_Bullet_Effect.png", 100, 100);
	Tex[Enemy_Texture_Distory_Effect] = SetLoadFile("Accet/Texture/Enemy_Distroy_Effect.png", 100, 100);
	Tex[Enemy_Boss_Texture_Bullet] = SetLoadFile("Accet/Texture/Boss_Bullet.png", 100, 100);
	Tex[Enemy_Texture_5_Effect] = SetLoadFile("Accet/Texture/Enemy_5_Effect.png", 100, 100);
	Tex[Enemy_Texture_Boss_Bullet_Shot_Effect] = SetLoadFile("Accet/Texture/Boss_Bullet_Shot.png", 100, 100);
	Tex[Enemy_Texture_Boss_Skill_Effect] = SetLoadFile("Accet/Texture/Boss_Skill.png", SCREEN_WIDTH*1.3, SCREEN_HEIGHT*0.2);


	Tex[Item_Texture] = SetLoadFile("Accet/Texture/Item.png", 100, 100);
	Tex[Item_Texture_Effect] = SetLoadFile("Accet/Texture/Item_Effect.png", 100, 100);

	Tex[Number_Texture] = SetLoadFile("Accet/Texture/number.tga", 640, 60);

	Tex[Summoner_Texture] = SetLoadFile("Accet/Texture/Summoner.png", 100, 100);
	Tex[Summoner_Texture_Bullet] = SetLoadFile("Accet/Texture/Summoner_Bullet.png", 100, 100);
	Tex[Summoner_Texture_Bullet_Effect] = SetLoadFile("Accet/Texture/Summoner_Bullet_Effect.png", 100, 100);

	Tex[Red_Texture] = SetLoadFile("Accet/Texture/Red.jpg", SCREEN_WIDTH, SCREEN_HEIGHT * 2);
	Tex[Warning_Texture] = SetLoadFile("Accet/Texture/Warning.png", SCREEN_WIDTH,100);

	Tex[Fire_Texture] = SetLoadFile("Accet/Texture/Fire.png", SCREEN_WIDTH*0.9, 200);

	Tex[Crear_Texture] = SetLoadFile("Accet/Texture/Crear.png", SCREEN_WIDTH * 0.5, 200);
	Tex[Next_Texture] = SetLoadFile("Accet/Texture/Next.png", SCREEN_WIDTH * 0.3, 150);
	Tex[Next2_Texture] = SetLoadFile("Accet/Texture/Next2.png", SCREEN_WIDTH * 0.3, 150);
	Tex[Name_Texture] = SetLoadFile("Accet/Texture/Name.png", SCREEN_WIDTH * 0.8, SCREEN_HEIGHT * 0.2);

	Tex[StartGame_Texture] = SetLoadFile("Accet/Texture/StartGame.png", SCREEN_WIDTH * 0.4, SCREEN_HEIGHT * 0.15);
	Tex[StartGame2_Texture] = SetLoadFile("Accet/Texture/StartGame2.png", SCREEN_WIDTH * 0.4, SCREEN_HEIGHT * 0.15);

	Tex[Fade_Texture] = SetLoadFile("Accet/Texture/Fade.png", SCREEN_WIDTH * 1, SCREEN_HEIGHT * 1);

	Tex[Cur_Texture] = SetLoadFile("Accet/Texture/Cur.png", SCREEN_WIDTH * 0.44, SCREEN_HEIGHT * 0.06);

	Tex[GoTitle_Texture] = SetLoadFile("Accet/Texture/GoTitle.png", SCREEN_WIDTH * 0.5, SCREEN_HEIGHT * 0.2);
	Tex[GoTitle2_Texture] = SetLoadFile("Accet/Texture/GoTitle2.png", SCREEN_WIDTH * 0.5, SCREEN_HEIGHT * 0.2);

}


int tag_Texture::SetLoadFile(const char* pFilename, float width, float height)
{
	for (int i = 0; i < TEXTUREDATA_MAX; i++)
	{
		if (strcmp(g_TextureData[i].filename, pFilename) == 0)
		{
			return i;
		}
	}
	for (int i = 0; i < TEXTUREDATA_MAX; i++)
	{
		if (g_TextureData[i].filename[0] != 0)
		{
			continue;
		}
		strcpy_s(g_TextureData[i].filename, pFilename);
		g_TextureData[i].width = width;
		g_TextureData[i].height = height;
		return i;
	}
	return -1;
}

void tag_Texture::Load(HWND hWnd)
{
	g_pDevice = GetDevice();
	for (int i = 0; i < TEXTUREDATA_MAX; i++)
	{
		if (g_TextureData[i].pTexture != NULL)
		{
			continue;
		}
		if (g_TextureData[i].filename[0] == 0)
		{
			continue;
		}

		hr[i] = D3DXCreateTextureFromFile(g_pDevice, g_TextureData[i].filename, &g_TextureData[i].pTexture);

		if (FAILED(hr[i]))
		{
			MessageBox(hWnd, "das", "??? ??", MB_OKCANCEL | MB_DEFBUTTON2);
		}
	}
}

void tag_Texture::Destroy(int texIds[], int count)
{
	for (int i = 0; i < count; i++)
	{
		if (g_TextureData[texIds[i]].pTexture != NULL)
		{
			g_TextureData[texIds[i]].pTexture->Release();
			g_TextureData[texIds[i]].pTexture = NULL;
			g_TextureData[texIds[i]].filename[0] = 0;
			g_TextureData[texIds[i]].width = 0;
			g_TextureData[texIds[i]].height = 0;
		}
	}
}

void tag_Texture::Destroy(void)
{
	for (int i = 0; i < TEXTUREDATA_MAX; i++)
	{
		if (g_TextureData[i].pTexture != NULL)
		{
			g_TextureData[i].pTexture->Release();
			g_TextureData[i].pTexture = NULL;
			g_TextureData[i].filename[0] = 0;
			g_TextureData[i].width = 0;
			g_TextureData[i].height = 0;
		}
	}
}


LPDIRECT3DTEXTURE9 tag_Texture::Get(int id)
{
	return g_TextureData[id].pTexture;
}

float tag_Texture::GetWidth(int id)
{
	return g_TextureData[id].width;
}

float tag_Texture::GetHeight(int id)
{
	return g_TextureData[id].height;
}