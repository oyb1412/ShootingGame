#ifndef _TEXTURE_H_	// ２重インクル?ド防?の?クロ定?
#define _TEXTURE_H_

#include <d3d9.h>
#include <windows.h>
#include "common.h"
#define TEXTURENAME_MAX (256)
#define TEXTUREDATA_MAX (256)
enum
{
	Player_Texture,
	Player_Texture_Life,
	Player_Texture_Bullet,
	Player_Texture_Ult,
	Player_Texture_Bullet_Effect,
	Player_Texture_Distroy_Effect,
	Player_Texture_Auto_Bullet,
	Player_Texture_Auto_Bullet_Effect,
	BG_Texture,
	Enemy_Texture_1,
	Enemy_Texture_2,
	Enemy_Texture_3,
	Enemy_Texture_4,
	Enemy_Texture_5,

	Enemy_Boss_Texture,
	Enemy_Boss_Texture_Life,
	Enemy_Texture_Bullet,
	Enemy_Texture_Bullet2,
	Enemy_Texture_Bullet_Effect,
	Enemy_Texture_Distory_Effect,
	Enemy_Boss_Texture_Bullet,
	Enemy_Texture_5_Effect,
	Enemy_Texture_Boss_Bullet_Shot_Effect,
	Enemy_Texture_Boss_Skill_Effect,

	Item_Texture,
	Item_Texture_Effect,

	Number_Texture,

	Summoner_Texture,
	Summoner_Texture_Bullet,
	Summoner_Texture_Bullet_Effect,

	Red_Texture,
	Warning_Texture,

	Fire_Texture,

	Crear_Texture,
	Next_Texture,
	Next2_Texture,
	Name_Texture,
	StartGame_Texture,
	StartGame2_Texture,
	Fade_Texture,

	Cur_Texture,

	GoTitle_Texture,
	GoTitle2_Texture,
};
class tag_Texture
{
private:
	struct TextureData
	{
		char filename[TEXTURENAME_MAX];
		float width;
		float height;
		LPDIRECT3DTEXTURE9 pTexture;
	};
	LPDIRECT3DDEVICE9 g_pDevice = NULL;
	TextureData g_TextureData[TEXTUREDATA_MAX] = {};
	HRESULT hr[TEXTUREDATA_MAX] = {};
public:
	void Init();
	int SetLoadFile(const char* pFilename, float width, float height);
	void Load(HWND hWnd);
	LPDIRECT3DTEXTURE9 Get(int id);
	void Destroy(int texIds[], int count);
	void Destroy(void);
	float GetWidth(int id);
	float GetHeight(int id);
	int Tex[50];

};
extern tag_Texture Texture;
#endif

