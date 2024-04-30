#include "texture.h"
#include "common.h"
#include "sprite.h"
#include <time.h>

#include "sound.h"
#include <d3d9.h>
#include <d3dx9.h>
#include "Scene.h"
#include "Name.h"
#include "Fade.h"
#include "mydirect3d.h"
#include "input.h"
#include "Enemy.h"

struct bg
{
	D3DXVECTOR2 position;
	D3DCOLOR color;
	D3DXVECTOR2 uv;
	D3DXVECTOR2 size;
};
static bg BG;
static float BgMoveTime = 0;
void tag_Name::Init()
{
	BgMoveTime = 0;
	BG.position.x = 400;
	BG.position.y = 500;
	for (int i = 0; i < 5; i++)
	{
		Name[i] = 0;
	}
	srand((unsigned int)time(NULL));
	Fade_Counter = false;
	Name_Bgm = false;
	Tex[0] = Texture.SetLoadFile("Accet/Texture/Number/Name/Score_Tex.png", 2500,500);
	Tex[1] = Texture.SetLoadFile("Accet/Texture/Number/Name/Space.png", 2000, 700);
	Tex[2] = Texture.SetLoadFile("Accet/Texture/bg.png", 4250, 3000);

	N_Tex[0] = Texture.SetLoadFile("Accet/Texture/Number/Name/Q.png", 500, 500);
	N_Tex[1] = Texture.SetLoadFile("Accet/Texture/Number/Name/W.png", 500, 500);
	N_Tex[2] = Texture.SetLoadFile("Accet/Texture/Number/Name/E.png", 500, 500);
	N_Tex[3] = Texture.SetLoadFile("Accet/Texture/Number/Name/R.png", 500, 500);
	N_Tex[4] = Texture.SetLoadFile("Accet/Texture/Number/Name/T.png", 500, 500);
	N_Tex[5] = Texture.SetLoadFile("Accet/Texture/Number/Name/Y.png", 500, 500);
	N_Tex[6] = Texture.SetLoadFile("Accet/Texture/Number/Name/U.png", 500, 500);
	N_Tex[7] = Texture.SetLoadFile("Accet/Texture/Number/Name/I.png", 500, 500);
	N_Tex[8] = Texture.SetLoadFile("Accet/Texture/Number/Name/O.png", 500, 500);
	N_Tex[9] = Texture.SetLoadFile("Accet/Texture/Number/Name/P.png", 500, 500);
	N_Tex[10] = Texture.SetLoadFile("Accet/Texture/Number/Name/A.png", 500, 500);
	N_Tex[11] = Texture.SetLoadFile("Accet/Texture/Number/Name/S.png", 500, 500);
	N_Tex[12] = Texture.SetLoadFile("Accet/Texture/Number/Name/D.png", 500, 500);
	N_Tex[13] = Texture.SetLoadFile("Accet/Texture/Number/Name/F.png", 500, 500);
	N_Tex[14] = Texture.SetLoadFile("Accet/Texture/Number/Name/G.png", 500, 500);
	N_Tex[15] = Texture.SetLoadFile("Accet/Texture/Number/Name/H.png", 500, 500);
	N_Tex[16] = Texture.SetLoadFile("Accet/Texture/Number/Name/J.png", 500, 500);
	N_Tex[17] = Texture.SetLoadFile("Accet/Texture/Number/Name/K.png", 500, 500);
	N_Tex[18] = Texture.SetLoadFile("Accet/Texture/Number/Name/L.png", 500, 500);
	N_Tex[19] = Texture.SetLoadFile("Accet/Texture/Number/Name/Z.png", 500, 500);
	N_Tex[20] = Texture.SetLoadFile("Accet/Texture/Number/Name/X.png", 500, 500);
	N_Tex[21] = Texture.SetLoadFile("Accet/Texture/Number/Name/C.png", 500, 500);
	N_Tex[22] = Texture.SetLoadFile("Accet/Texture/Number/Name/V.png", 500, 500);
	N_Tex[23] = Texture.SetLoadFile("Accet/Texture/Number/Name/B.png", 500, 500);
	N_Tex[24] = Texture.SetLoadFile("Accet/Texture/Number/Name/N.png", 500, 500);
	N_Tex[25] = Texture.SetLoadFile("Accet/Texture/Number/Name/M.png", 500, 500);
	ChangeTime = /*Get_Score()*/111;
	Texture.Load(hWnd);
	Fade_Init();

}
void tag_Name::Update()
{
	Fade_Out();
	BgMoveTime += 0.5f;

	turm--;
	if (!Name_Bgm)
	{
		//Sound.Play(SOUND_LABEL_TITLEBGM);
		Name_Bgm = true;
	}
	if (!Fade_Counter)
	{
		//Fade.Fade_Funtion(false);
	}

	{
		if (Name[0] == 0 && Name[1] == 0 && Name[2] == 0 && Name[3] == 0 && Name[4] == 0)
		{
			if (Keyboard_IsPress(DIK_Q) && turm < 0)
			{
				turm = 10;
				Name[0] = 1;
			}
		}
		if (Name[0] > 0 && Name[1] == 0 && Name[2] == 0 && Name[3] == 0 && Name[4] == 0)
		{
			if (Keyboard_IsPress(DIK_Q) && turm < 0)
			{
				turm = 10;
				Name[1] = 1;
			}
		}
		if (Name[0] > 0 && Name[1] > 0 && Name[2] == 0 && Name[3] == 0 && Name[4] == 0)
		{
			if (Keyboard_IsPress(DIK_Q) && turm < 0)
			{
				turm = 10;
				Name[2] = 1;
			}
		}
		if (Name[0] > 0 && Name[1] > 0 && Name[2] > 0 && Name[3] == 0 && Name[4] == 0)
		{
			if (Keyboard_IsPress(DIK_Q) && turm < 0)
			{
				turm = 10;
				Name[3] = 1;
			}
		}
		if (Name[0] > 0 && Name[1] > 0 && Name[2] > 0 && Name[3] > 0 && Name[4] == 0)
		{
			if (Keyboard_IsPress(DIK_Q) && turm < 0)
			{
				turm = 10;
				Name[4] = 1;
			}
		}
	}
	{
		if (Name[0] == 0 && Name[1] == 0 && Name[2] == 0 && Name[3] == 0 && Name[4] == 0)
		{
			if (Keyboard_IsPress(DIK_W) && turm < 0)
			{
				turm = 10;
				Name[0] = 2;
			}
		}
		if (Name[0] > 0 && Name[1] == 0 && Name[2] == 0 && Name[3] == 0 && Name[4] == 0)
		{
			if (Keyboard_IsPress(DIK_W) && turm < 0)
			{
				turm = 10;
				Name[1] = 2;
			}
		}
		if (Name[0] > 0 && Name[1] > 0 && Name[2] == 0 && Name[3] == 0 && Name[4] == 0)
		{
			if (Keyboard_IsPress(DIK_W) && turm < 0)
			{
				turm = 10;
				Name[2] = 2;
			}
		}
		if (Name[0] > 0 && Name[1] > 0 && Name[2] > 0 && Name[3] == 0 && Name[4] == 0)
		{
			if (Keyboard_IsPress(DIK_W) && turm < 0)
			{
				turm = 10;
				Name[3] = 2;
			}
		}
		if (Name[0] > 0 && Name[1] > 0 && Name[2] > 0 && Name[3] > 0 && Name[4] == 0)
		{
			if (Keyboard_IsPress(DIK_W) && turm < 0)
			{
				turm = 10;
				Name[4] = 2;
			}
		}
	}
	{
		if (Name[0] == 0 && Name[1] == 0 && Name[2] == 0 && Name[3] == 0 && Name[4] == 0)
		{
			if (Keyboard_IsPress(DIK_E) && turm < 0)
			{
				turm = 10;
				Name[0] = 3;
			}
		}
		if (Name[0] > 0 && Name[1] == 0 && Name[2] == 0 && Name[3] == 0 && Name[4] == 0)
		{
			if (Keyboard_IsPress(DIK_E) && turm < 0)
			{
				turm = 10;
				Name[1] = 3;
			}
		}
		if (Name[0] > 0 && Name[1] > 0 && Name[2] == 0 && Name[3] == 0 && Name[4] == 0)
		{
			if (Keyboard_IsPress(DIK_E) && turm < 0)
			{
				turm = 10;
				Name[2] = 3;
			}
		}
		if (Name[0] > 0 && Name[1] > 0 && Name[2] > 0 && Name[3] == 0 && Name[4] == 0)
		{
			if (Keyboard_IsPress(DIK_E) && turm < 0)
			{
				turm = 10;
				Name[3] = 3;
			}
		}
		if (Name[0] > 0 && Name[1] > 0 && Name[2] > 0 && Name[3] > 0 && Name[4] == 0)
		{
			if (Keyboard_IsPress(DIK_E) && turm < 0)
			{
				turm = 10;
				Name[4] = 3;
			}
		}
	}
	{
		if (Name[0] == 0 && Name[1] == 0 && Name[2] == 0 && Name[3] == 0 && Name[4] == 0)
		{
			if (Keyboard_IsPress(DIK_R) && turm < 0)
			{
				turm = 10;
				Name[0] = 4;
			}
		}
		if (Name[0] > 0 && Name[1] == 0 && Name[2] == 0 && Name[3] == 0 && Name[4] == 0)
		{
			if (Keyboard_IsPress(DIK_R) && turm < 0)
			{
				turm = 10;
				Name[1] = 4;
			}
		}
		if (Name[0] > 0 && Name[1] > 0 && Name[2] == 0 && Name[3] == 0 && Name[4] == 0)
		{
			if (Keyboard_IsPress(DIK_R) && turm < 0)
			{
				turm = 10;
				Name[2] = 4;
			}
		}
		if (Name[0] > 0 && Name[1] > 0 && Name[2] > 0 && Name[3] == 0 && Name[4] == 0)
		{
			if (Keyboard_IsPress(DIK_R) && turm < 0)
			{
				turm = 10;
				Name[3] = 4;
			}
		}
		if (Name[0] > 0 && Name[1] > 0 && Name[2] > 0 && Name[3] > 0 && Name[4] == 0)
		{
			if (Keyboard_IsPress(DIK_R) && turm < 0)
			{
				turm = 10;
				Name[4] = 4
;
			}
		}
	}
	{
		if (Name[0] == 0 && Name[1] == 0 && Name[2] == 0 && Name[3] == 0 && Name[4] == 0)
		{
			if (Keyboard_IsPress(DIK_T) && turm < 0)
			{
				turm = 10;
				Name[0] = 5;
			}
		}
		if (Name[0] > 0 && Name[1] == 0 && Name[2] == 0 && Name[3] == 0 && Name[4] == 0)
		{
			if (Keyboard_IsPress(DIK_T) && turm < 0)
			{
				turm = 10;
				Name[1] = 5;
			}
		}
		if (Name[0] > 0 && Name[1] > 0 && Name[2] == 0 && Name[3] == 0 && Name[4] == 0)
		{
			if (Keyboard_IsPress(DIK_T) && turm < 0)
			{
				turm = 10;
				Name[2] = 5;
			}
		}
		if (Name[0] > 0 && Name[1] > 0 && Name[2] > 0 && Name[3] == 0 && Name[4] == 0)
		{
			if (Keyboard_IsPress(DIK_T) && turm < 0)
			{
				turm = 10;
				Name[3] = 5;
			}
		}
		if (Name[0] > 0 && Name[1] > 0 && Name[2] > 0 && Name[3] > 0 && Name[4] == 0)
		{
			if (Keyboard_IsPress(DIK_T) && turm < 0)
			{
				turm = 10;
				Name[4] = 5
;
			}
		}
	}
	{
		if (Name[0] == 0 && Name[1] == 0 && Name[2] == 0 && Name[3] == 0 && Name[4] == 0)
		{
			if (Keyboard_IsPress(DIK_Y) && turm < 0)
			{
				turm = 10;
				Name[0] = 6;
			}
		}
		if (Name[0] > 0 && Name[1] == 0 && Name[2] == 0 && Name[3] == 0 && Name[4] == 0)
		{
			if (Keyboard_IsPress(DIK_Y) && turm < 0)
			{
				turm = 10;
				Name[1] = 6;
			}
		}
		if (Name[0] > 0 && Name[1] > 0 && Name[2] == 0 && Name[3] == 0 && Name[4] == 0)
		{
			if (Keyboard_IsPress(DIK_Y) && turm < 0)
			{
				turm = 10;
				Name[2] = 6;
			}
		}
		if (Name[0] > 0 && Name[1] > 0 && Name[2] > 0 && Name[3] == 0 && Name[4] == 0)
		{
			if (Keyboard_IsPress(DIK_Y) && turm < 0)
			{
				turm = 10;
				Name[3] = 6;
			}
		}
		if (Name[0] > 0 && Name[1] > 0 && Name[2] > 0 && Name[3] > 0 && Name[4] == 0)
		{
			if (Keyboard_IsPress(DIK_Y) && turm < 0)
			{
				turm = 10;
				Name[4] = 6;
			}
		}
	}
	{
		if (Name[0] == 0 && Name[1] == 0 && Name[2] == 0 && Name[3] == 0 && Name[4] == 0)
		{
			if (Keyboard_IsPress(DIK_U) && turm < 0)
			{
				turm = 10;
				Name[0] = 7;
			}
		}
		if (Name[0] > 0 && Name[1] == 0 && Name[2] == 0 && Name[3] == 0 && Name[4] == 0)
		{
			if (Keyboard_IsPress(DIK_U) && turm < 0)
			{
				turm = 10;
				Name[1] = 7;
			}
		}
		if (Name[0] > 0 && Name[1] > 0 && Name[2] == 0 && Name[3] == 0 && Name[4] == 0)
		{
			if (Keyboard_IsPress(DIK_U) && turm < 0)
			{
				turm = 10;
				Name[2] = 7;
			}
		}
		if (Name[0] > 0 && Name[1] > 0 && Name[2] > 0 && Name[3] == 0 && Name[4] == 0)
		{
			if (Keyboard_IsPress(DIK_U) && turm < 0)
			{
				turm = 10;
				Name[3] = 7;
			}
		}
		if (Name[0] > 0 && Name[1] > 0 && Name[2] > 0 && Name[3] > 0 && Name[4] == 0)
		{
			if (Keyboard_IsPress(DIK_U) && turm < 0)
			{
				turm = 10;
				Name[4] = 7
;
			}
		}
	}
	{
		if (Name[0] == 0 && Name[1] == 0 && Name[2] == 0 && Name[3] == 0 && Name[4] == 0)
		{
			if (Keyboard_IsPress(DIK_I) && turm < 0)
			{
				turm = 10;
				Name[0] = 8;
			}
		}
		if (Name[0] > 0 && Name[1] == 0 && Name[2] == 0 && Name[3] == 0 && Name[4] == 0)
		{
			if (Keyboard_IsPress(DIK_I) && turm < 0)
			{
				turm = 10;
				Name[1] = 8;
			}
		}
		if (Name[0] > 0 && Name[1] > 0 && Name[2] == 0 && Name[3] == 0 && Name[4] == 0)
		{
			if (Keyboard_IsPress(DIK_I) && turm < 0)
			{
				turm = 10;
				Name[2] = 8;
			}
		}
		if (Name[0] > 0 && Name[1] > 0 && Name[2] > 0 && Name[3] == 0 && Name[4] == 0)
		{
			if (Keyboard_IsPress(DIK_I) && turm < 0)
			{
				turm = 10;
				Name[3] = 8;
			}
		}
		if (Name[0] > 0 && Name[1] > 0 && Name[2] > 0 && Name[3] > 0 && Name[4] == 0)
		{
			if (Keyboard_IsPress(DIK_I) && turm < 0)
			{
				turm = 10;
				Name[4] = 8
;
			}
		}
	}
	{
		if (Name[0] == 0 && Name[1] == 0 && Name[2] == 0 && Name[3] == 0 && Name[4] == 0)
		{
			if (Keyboard_IsPress(DIK_O) && turm < 0)
			{
				turm = 10;
				Name[0] = 9;
			}
		}
		if (Name[0] > 0 && Name[1] == 0 && Name[2] == 0 && Name[3] == 0 && Name[4] == 0)
		{
			if (Keyboard_IsPress(DIK_O) && turm < 0)
			{
				turm = 10;
				Name[1] = 9;
			}
		}
		if (Name[0] > 0 && Name[1] > 0 && Name[2] == 0 && Name[3] == 0 && Name[4] == 0)
		{
			if (Keyboard_IsPress(DIK_O) && turm < 0)
			{
				turm = 10;
				Name[2] = 9;
			}
		}
		if (Name[0] > 0 && Name[1] > 0 && Name[2] > 0 && Name[3] == 0 && Name[4] == 0)
		{
			if (Keyboard_IsPress(DIK_O) && turm < 0)
			{
				turm = 10;
				Name[3] = 9;
			}
		}
		if (Name[0] > 0 && Name[1] > 0 && Name[2] > 0 && Name[3] > 0 && Name[4] == 0)
		{
			if (Keyboard_IsPress(DIK_O) && turm < 0)
			{
				turm = 10;
				Name[4] = 9;
			}
		}
	}
	{
		if (Name[0] == 0 && Name[1] == 0 && Name[2] == 0 && Name[3] == 0 && Name[4] == 0)
		{
			if (Keyboard_IsPress(DIK_P) && turm < 0)
			{
				turm = 10;
				Name[0] = 10;
			}
		}
		if (Name[0] > 0 && Name[1] == 0 && Name[2] == 0 && Name[3] == 0 && Name[4] == 0)
		{
			if (Keyboard_IsPress(DIK_P) && turm < 0)
			{
				turm = 10;
				Name[1] = 10;
			}
		}
		if (Name[0] > 0 && Name[1] > 0 && Name[2] == 0 && Name[3] == 0 && Name[4] == 0)
		{
			if (Keyboard_IsPress(DIK_P) && turm < 0)
			{
				turm = 10;
				Name[2] = 10;
			}
		}
		if (Name[0] > 0 && Name[1] > 0 && Name[2] > 0 && Name[3] == 0 && Name[4] == 0)
		{
			if (Keyboard_IsPress(DIK_P) && turm < 0)
			{
				turm = 10;
				Name[3] = 10;
			}
		}
		if (Name[0] > 0 && Name[1] > 0 && Name[2] > 0 && Name[3] > 0 && Name[4] == 0)
		{
			if (Keyboard_IsPress(DIK_P) && turm < 0)
			{
				turm = 10;
				Name[4] = 10;
			}
		}
	}
	{
		if (Name[0] == 0 && Name[1] == 0 && Name[2] == 0 && Name[3] == 0 && Name[4] == 0)
		{
			if (Keyboard_IsPress(DIK_A) && turm < 0)
			{
				turm = 10;
				Name[0] = 11
;
			}
		}
		if (Name[0] > 0 && Name[1] == 0 && Name[2] == 0 && Name[3] == 0 && Name[4] == 0)
		{
			if (Keyboard_IsPress(DIK_A) && turm < 0)
			{
				turm = 10;
				Name[1] = 11;
			}
		}
		if (Name[0] > 0 && Name[1] > 0 && Name[2] == 0 && Name[3] == 0 && Name[4] == 0)
		{
			if (Keyboard_IsPress(DIK_A) && turm < 0)
			{
				turm = 10;
				Name[2] = 11;
			}
		}
		if (Name[0] > 0 && Name[1] > 0 && Name[2] > 0 && Name[3] == 0 && Name[4] == 0)
		{
			if (Keyboard_IsPress(DIK_A) && turm < 0)
			{
				turm = 10;
				Name[3] = 11;
			}
		}
		if (Name[0] > 0 && Name[1] > 0 && Name[2] > 0 && Name[3] > 0 && Name[4] == 0)
		{
			if (Keyboard_IsPress(DIK_A) && turm < 0)
			{
				turm = 10;
				Name[4] = 11;
			}
		}
	}
	{
		if (Name[0] == 0 && Name[1] == 0 && Name[2] == 0 && Name[3] == 0 && Name[4] == 0)
		{
			if (Keyboard_IsPress(DIK_S) && turm < 0)
			{
				turm = 10;
				Name[0] = 12;
			}
		}
		if (Name[0] > 0 && Name[1] == 0 && Name[2] == 0 && Name[3] == 0 && Name[4] == 0)
		{
			if (Keyboard_IsPress(DIK_S) && turm < 0)
			{
				turm = 10;
				Name[1] = 12;
			}
		}
		if (Name[0] > 0 && Name[1] > 0 && Name[2] == 0 && Name[3] == 0 && Name[4] == 0)
		{
			if (Keyboard_IsPress(DIK_S) && turm < 0)
			{
				turm = 10;
				Name[2] = 12;
			}
		}
		if (Name[0] > 0 && Name[1] > 0 && Name[2] > 0 && Name[3] == 0 && Name[4] == 0)
		{
			if (Keyboard_IsPress(DIK_S) && turm < 0)
			{
				turm = 10;
				Name[3] = 12;
			}
		}
		if (Name[0] > 0 && Name[1] > 0 && Name[2] > 0 && Name[3] > 0 && Name[4] == 0)
		{
			if (Keyboard_IsPress(DIK_S) && turm < 0)
			{
				turm = 10;
				Name[4] = 12;
			}
		}
	}
	{
		if (Name[0] == 0 && Name[1] == 0 && Name[2] == 0 && Name[3] == 0 && Name[4] == 0)
		{
			if (Keyboard_IsPress(DIK_D) && turm < 0)
			{
				turm = 10;
				Name[0] = 13;
			}
		}
		if (Name[0] > 0 && Name[1] == 0 && Name[2] == 0 && Name[3] == 0 && Name[4] == 0)
		{
			if (Keyboard_IsPress(DIK_D) && turm < 0)
			{
				turm = 10;
				Name[1] = 13;
			}
		}
		if (Name[0] > 0 && Name[1] > 0 && Name[2] == 0 && Name[3] == 0 && Name[4] == 0)
		{
			if (Keyboard_IsPress(DIK_D) && turm < 0)
			{
				turm = 10;
				Name[2] = 13;
			}
		}
		if (Name[0] > 0 && Name[1] > 0 && Name[2] > 0 && Name[3] == 0 && Name[4] == 0)
		{
			if (Keyboard_IsPress(DIK_D) && turm < 0)
			{
				turm = 10;
				Name[3] = 13;
			}
		}
		if (Name[0] > 0 && Name[1] > 0 && Name[2] > 0 && Name[3] > 0 && Name[4] == 0)
		{
			if (Keyboard_IsPress(DIK_D) && turm < 0)
			{
				turm = 10;
				Name[4] = 13;
			}
		}
	}

	{
		if (Name[0] == 0 && Name[1] == 0 && Name[2] == 0 && Name[3] == 0 && Name[4] == 0)
		{
			if (Keyboard_IsPress(DIK_F) && turm < 0)
			{
				turm = 10;
				Name[0] = 14;
			}
		}
		if (Name[0] > 0 && Name[1] == 0 && Name[2] == 0 && Name[3] == 0 && Name[4] == 0)
		{
			if (Keyboard_IsPress(DIK_F) && turm < 0)
			{
				turm = 10;
				Name[1] = 14;
			}
		}
		if (Name[0] > 0 && Name[1] > 0 && Name[2] == 0 && Name[3] == 0 && Name[4] == 0)
		{
			if (Keyboard_IsPress(DIK_F) && turm < 0)
			{
				turm = 10;
				Name[2] = 14;
			}
		}
		if (Name[0] > 0 && Name[1] > 0 && Name[2] > 0 && Name[3] == 0 && Name[4] == 0)
		{
			if (Keyboard_IsPress(DIK_F) && turm < 0)
			{
				turm = 10;
				Name[3] = 14;
			}
		}
		if (Name[0] > 0 && Name[1] > 0 && Name[2] > 0 && Name[3] > 0 && Name[4] == 0)
		{
			if (Keyboard_IsPress(DIK_F) && turm < 0)
			{
				turm = 10;
				Name[4] = 14
;
			}
		}
	}
	{
		if (Name[0] == 0 && Name[1] == 0 && Name[2] == 0 && Name[3] == 0 && Name[4] == 0)
		{
			if (Keyboard_IsPress(DIK_G) && turm < 0)
			{
				turm = 10;
				Name[0] = 15;
			}
		}
		if (Name[0] > 0 && Name[1] == 0 && Name[2] == 0 && Name[3] == 0 && Name[4] == 0)
		{
			if (Keyboard_IsPress(DIK_G) && turm < 0)
			{
				turm = 10;
				Name[1] = 15;
			}
		}
		if (Name[0] > 0 && Name[1] > 0 && Name[2] == 0 && Name[3] == 0 && Name[4] == 0)
		{
			if (Keyboard_IsPress(DIK_G) && turm < 0)
			{
				turm = 10;
				Name[2] = 15;
			}
		}
		if (Name[0] > 0 && Name[1] > 0 && Name[2] > 0 && Name[3] == 0 && Name[4] == 0)
		{
			if (Keyboard_IsPress(DIK_G) && turm < 0)
			{
				turm = 10;
				Name[3] = 15;
			}
		}
		if (Name[0] > 0 && Name[1] > 0 && Name[2] > 0 && Name[3] > 0 && Name[4] == 0)
		{
			if (Keyboard_IsPress(DIK_G) && turm < 0)
			{
				turm = 10;
				Name[4] = 15;
			}
		}
	}

	{
		if (Name[0] == 0 && Name[1] == 0 && Name[2] == 0 && Name[3] == 0 && Name[4] == 0)
		{
			if (Keyboard_IsPress(DIK_H) && turm < 0)
			{
				turm = 10;
				Name[0] = 16;
			}
		}
		if (Name[0] > 0 && Name[1] == 0 && Name[2] == 0 && Name[3] == 0 && Name[4] == 0)
		{
			if (Keyboard_IsPress(DIK_H) && turm < 0)
			{
				turm = 10;
				Name[1] = 16;
			}
		}
		if (Name[0] > 0 && Name[1] > 0 && Name[2] == 0 && Name[3] == 0 && Name[4] == 0)
		{
			if (Keyboard_IsPress(DIK_H) && turm < 0)
			{
				turm = 10;
				Name[2] = 16;
			}
		}
		if (Name[0] > 0 && Name[1] > 0 && Name[2] > 0 && Name[3] == 0 && Name[4] == 0)
		{
			if (Keyboard_IsPress(DIK_H) && turm < 0)
			{
				turm = 10;
				Name[3] = 16;
			}
		}
		if (Name[0] > 0 && Name[1] > 0 && Name[2] > 0 && Name[3] > 0 && Name[4] == 0)
		{
			if (Keyboard_IsPress(DIK_H) && turm < 0)
			{
				turm = 10;
				Name[4] = 16;
			}
		}
	}
	{
		if (Name[0] == 0 && Name[1] == 0 && Name[2] == 0 && Name[3] == 0 && Name[4] == 0)
		{
			if (Keyboard_IsPress(DIK_J) && turm < 0)
			{
				turm = 10;
				Name[0] =17;
			}
		}
		if (Name[0] > 0 && Name[1] == 0 && Name[2] == 0 && Name[3] == 0 && Name[4] == 0)
		{
			if (Keyboard_IsPress(DIK_J) && turm < 0)
			{
				turm = 10;
				Name[1] = 17;
			}
		}
		if (Name[0] > 0 && Name[1] > 0 && Name[2] == 0 && Name[3] == 0 && Name[4] == 0)
		{
			if (Keyboard_IsPress(DIK_J) && turm < 0)
			{
				turm = 10;
				Name[2] = 17;
			}
		}
		if (Name[0] > 0 && Name[1] > 0 && Name[2] > 0 && Name[3] == 0 && Name[4] == 0)
		{
			if (Keyboard_IsPress(DIK_J) && turm < 0)
			{
				turm = 10;
				Name[3] = 17;
			}
		}
		if (Name[0] > 0 && Name[1] > 0 && Name[2] > 0 && Name[3] > 0 && Name[4] == 0)
		{
			if (Keyboard_IsPress(DIK_J) && turm < 0)
			{
				turm = 10;
				Name[4] = 17;
			}
		}
	}
	{
		if (Name[0] == 0 && Name[1] == 0 && Name[2] == 0 && Name[3] == 0 && Name[4] == 0)
		{
			if (Keyboard_IsPress(DIK_K) && turm < 0)
			{
				turm = 10;
				Name[0] = 18;
			}
		}
		if (Name[0] > 0 && Name[1] == 0 && Name[2] == 0 && Name[3] == 0 && Name[4] == 0)
		{
			if (Keyboard_IsPress(DIK_K) && turm < 0)
			{
				turm = 10;
				Name[1] = 18;
			}
		}
		if (Name[0] > 0 && Name[1] > 0 && Name[2] == 0 && Name[3] == 0 && Name[4] == 0)
		{
			if (Keyboard_IsPress(DIK_K) && turm < 0)
			{
				turm = 10;
				Name[2] = 18;
			}
		}
		if (Name[0] > 0 && Name[1] > 0 && Name[2] > 0 && Name[3] == 0 && Name[4] == 0)
		{
			if (Keyboard_IsPress(DIK_K) && turm < 0)
			{
				turm = 10;
				Name[3] = 18;
			}
		}
		if (Name[0] > 0 && Name[1] > 0 && Name[2] > 0 && Name[3] > 0 && Name[4] == 0)
		{
			if (Keyboard_IsPress(DIK_K) && turm < 0)
			{
				turm = 10;
				Name[4] = 18;
			}
		}
	}

	{
		if (Name[0] == 0 && Name[1] == 0 && Name[2] == 0 && Name[3] == 0 && Name[4] == 0)
		{
			if (Keyboard_IsPress(DIK_L) && turm < 0)
			{
				turm = 10;
				Name[0] = 19;
			}
		}
		if (Name[0] > 0 && Name[1] == 0 && Name[2] == 0 && Name[3] == 0 && Name[4] == 0)
		{
			if (Keyboard_IsPress(DIK_L) && turm < 0)
			{
				turm = 10;
				Name[1] = 19;
			}
		}
		if (Name[0] > 0 && Name[1] > 0 && Name[2] == 0 && Name[3] == 0 && Name[4] == 0)
		{
			if (Keyboard_IsPress(DIK_L) && turm < 0)
			{
				turm = 10;
				Name[2] = 19;
			}
		}
		if (Name[0] > 0 && Name[1] > 0 && Name[2] > 0 && Name[3] == 0 && Name[4] == 0)
		{
			if (Keyboard_IsPress(DIK_L) && turm < 0)
			{
				turm = 10;
				Name[3] = 19;
			}
		}
		if (Name[0] > 0 && Name[1] > 0 && Name[2] > 0 && Name[3] > 0 && Name[4] == 0)
		{
			if (Keyboard_IsPress(DIK_L) && turm < 0)
			{
				turm = 10;
				Name[4] = 19;
			}
		}
	}

	{
		if (Name[0] == 0 && Name[1] == 0 && Name[2] == 0 && Name[3] == 0 && Name[4] == 0)
		{
			if (Keyboard_IsPress(DIK_Z) && turm < 0)
			{
				turm = 10;
				Name[0] = 20;
			}
		}
		if (Name[0] > 0 && Name[1] == 0 && Name[2] == 0 && Name[3] == 0 && Name[4] == 0)
		{
			if (Keyboard_IsPress(DIK_Z) && turm < 0)
			{
				turm = 10;
				Name[1] = 20;
			}
		}
		if (Name[0] > 0 && Name[1] > 0 && Name[2] == 0 && Name[3] == 0 && Name[4] == 0)
		{
			if (Keyboard_IsPress(DIK_Z) && turm < 0)
			{
				turm = 10;
				Name[2] = 20;
			}
		}
		if (Name[0] > 0 && Name[1] > 0 && Name[2] > 0 && Name[3] == 0 && Name[4] == 0)
		{
			if (Keyboard_IsPress(DIK_Z) && turm < 0)
			{
				turm = 10;
				Name[3] = 20;
			}
		}
		if (Name[0] > 0 && Name[1] > 0 && Name[2] > 0 && Name[3] > 0 && Name[4] == 0)
		{
			if (Keyboard_IsPress(DIK_Z) && turm < 0)
			{
				turm = 10;
				Name[4] = 20;
			}
		}
	}

	{
		if (Name[0] == 0 && Name[1] == 0 && Name[2] == 0 && Name[3] == 0 && Name[4] == 0)
		{
			if (Keyboard_IsPress(DIK_X) && turm < 0)
			{
				turm = 10;
				Name[0] = 21;
			}
		}
		if (Name[0] > 0 && Name[1] == 0 && Name[2] == 0 && Name[3] == 0 && Name[4] == 0)
		{
			if (Keyboard_IsPress(DIK_X) && turm < 0)
			{
				turm = 10;
				Name[1] = 21;
			}
		}
		if (Name[0] > 0 && Name[1] > 0 && Name[2] == 0 && Name[3] == 0 && Name[4] == 0)
		{
			if (Keyboard_IsPress(DIK_X) && turm < 0)
			{
				turm = 10;
				Name[2] = 21;
			}
		}
		if (Name[0] > 0 && Name[1] > 0 && Name[2] > 0 && Name[3] == 0 && Name[4] == 0)
		{
			if (Keyboard_IsPress(DIK_X) && turm < 0)
			{
				turm = 10;
				Name[3] = 21;
			}
		}
		if (Name[0] > 0 && Name[1] > 0 && Name[2] > 0 && Name[3] > 0 && Name[4] == 0)
		{
			if (Keyboard_IsPress(DIK_X) && turm < 0)
			{
				turm = 10;
				Name[4] = 21;
			}
		}
	}

	{
		if (Name[0] == 0 && Name[1] == 0 && Name[2] == 0 && Name[3] == 0 && Name[4] == 0)
		{
			if (Keyboard_IsPress(DIK_C) && turm < 0)
			{
				turm = 10;
				Name[0] = 22;
			}
		}
		if (Name[0] > 0 && Name[1] == 0 && Name[2] == 0 && Name[3] == 0 && Name[4] == 0)
		{
			if (Keyboard_IsPress(DIK_C) && turm < 0)
			{
				turm = 10;
				Name[1] = 22;
			}
		}
		if (Name[0] > 0 && Name[1] > 0 && Name[2] == 0 && Name[3] == 0 && Name[4] == 0)
		{
			if (Keyboard_IsPress(DIK_C) && turm < 0)
			{
				turm = 10;
				Name[2] = 22;
			}
		}
		if (Name[0] > 0 && Name[1] > 0 && Name[2] > 0 && Name[3] == 0 && Name[4] == 0)
		{
			if (Keyboard_IsPress(DIK_C) && turm < 0)
			{
				turm = 10;
				Name[3] = 22;
			}
		}
		if (Name[0] > 0 && Name[1] > 0 && Name[2] > 0 && Name[3] > 0 && Name[4] == 0)
		{
			if (Keyboard_IsPress(DIK_C) && turm < 0)
			{
				turm = 10;
				Name[4] = 22;
			}
		}
	}

	{
		if (Name[0] == 0 && Name[1] == 0 && Name[2] == 0 && Name[3] == 0 && Name[4] == 0)
		{
			if (Keyboard_IsPress(DIK_V) && turm < 0)
			{
				turm = 10;
				Name[0] = 23;
			}
		}
		if (Name[0] > 0 && Name[1] == 0 && Name[2] == 0 && Name[3] == 0 && Name[4] == 0)
		{
			if (Keyboard_IsPress(DIK_V) && turm < 0)
			{
				turm = 10;
				Name[1] = 23;
			}
		}
		if (Name[0] > 0 && Name[1] > 0 && Name[2] == 0 && Name[3] == 0 && Name[4] == 0)
		{
			if (Keyboard_IsPress(DIK_V) && turm < 0)
			{
				turm = 10;
				Name[2] = 23;
			}
		}
		if (Name[0] > 0 && Name[1] > 0 && Name[2] > 0 && Name[3] == 0 && Name[4] == 0)
		{
			if (Keyboard_IsPress(DIK_V) && turm < 0)
			{
				turm = 10;
				Name[3] = 23;
			}
		}
		if (Name[0] > 0 && Name[1] > 0 && Name[2] > 0 && Name[3] > 0 && Name[4] == 0)
		{
			if (Keyboard_IsPress(DIK_V) && turm < 0)
			{
				turm = 10;
				Name[4] = 23;
			}
		}
	}

	{
		if (Name[0] == 0 && Name[1] == 0 && Name[2] == 0 && Name[3] == 0 && Name[4] == 0)
		{
			if (Keyboard_IsPress(DIK_B) && turm < 0)
			{
				turm = 10;
				Name[0] = 24;
			}
		}
		if (Name[0] > 0 && Name[1] == 0 && Name[2] == 0 && Name[3] == 0 && Name[4] == 0)
		{
			if (Keyboard_IsPress(DIK_B) && turm < 0)
			{
				turm = 10;
				Name[1] = 24;
			}
		}
		if (Name[0] > 0 && Name[1] > 0 && Name[2] == 0 && Name[3] == 0 && Name[4] == 0)
		{
			if (Keyboard_IsPress(DIK_B) && turm < 0)
			{
				turm = 10;
				Name[2] = 24;
			}
		}
		if (Name[0] > 0 && Name[1] > 0 && Name[2] > 0 && Name[3] == 0 && Name[4] == 0)
		{
			if (Keyboard_IsPress(DIK_B) && turm < 0)
			{
				turm = 10;
				Name[3] = 24;
			}
		}
		if (Name[0] > 0 && Name[1] > 0 && Name[2] > 0 && Name[3] > 0 && Name[4] == 0)
		{
			if (Keyboard_IsPress(DIK_B) && turm < 0)
			{
				turm = 10;
				Name[4] = 24;
			}
		}
	}
	{
		if (Name[0] == 0 && Name[1] == 0 && Name[2] == 0 && Name[3] == 0 && Name[4] == 0)
		{
			if (Keyboard_IsPress(DIK_N) && turm < 0)
			{
				turm = 10;
				Name[0] = 25;
			}
		}
		if (Name[0] > 0 && Name[1] == 0 && Name[2] == 0 && Name[3] == 0 && Name[4] == 0)
		{
			if (Keyboard_IsPress(DIK_N) && turm < 0)
			{
				turm = 10;
				Name[1] = 25;
			}
		}
		if (Name[0] > 0 && Name[1] > 0 && Name[2] == 0 && Name[3] == 0 && Name[4] == 0)
		{
			if (Keyboard_IsPress(DIK_N) && turm < 0)
			{
				turm = 10;
				Name[2] = 25;
			}
		}
		if (Name[0] > 0 && Name[1] > 0 && Name[2] > 0 && Name[3] == 0 && Name[4] == 0)
		{
			if (Keyboard_IsPress(DIK_N) && turm < 0)
			{
				turm = 10;
				Name[3] = 25;
			}
		}
		if (Name[0] > 0 && Name[1] > 0 && Name[2] > 0 && Name[3] > 0 && Name[4] == 0)
		{
			if (Keyboard_IsPress(DIK_N) && turm < 0)
			{
				turm = 10;
				Name[4] = 25;
			}
		}
	}

	{
		if (Name[0] == 0 && Name[1] == 0 && Name[2] == 0 && Name[3] == 0 && Name[4] == 0)
		{
			if (Keyboard_IsPress(DIK_M) && turm < 0)
			{
				turm = 10;
				Name[0] = 26;
			}
		}
		if (Name[0] > 0 && Name[1] == 0 && Name[2] == 0 && Name[3] == 0 && Name[4] == 0)
		{
			if (Keyboard_IsPress(DIK_M) && turm < 0)
			{
				turm = 10;
				Name[1] = 26;
			}
		}
		if (Name[0] > 0 && Name[1] > 0 && Name[2] == 0 && Name[3] == 0 && Name[4] == 0)
		{
			if (Keyboard_IsPress(DIK_M) && turm < 0)
			{
				turm = 10;
				Name[2] = 26;
			}
		}
		if (Name[0] > 0 && Name[1] > 0 && Name[2] > 0 && Name[3] == 0 && Name[4] == 0)
		{
			if (Keyboard_IsPress(DIK_M) && turm < 0)
			{
				turm = 10;
				Name[3] = 26;
			}
		}
		if (Name[0] > 0 && Name[1] > 0 && Name[2] > 0 && Name[3] > 0 && Name[4] == 0)
		{
			if (Keyboard_IsPress(DIK_M) && turm < 0)
			{
				turm = 10;
				Name[4] = 26;
			}
		}
	}

	if (Name[4] > 0)
	{
		Fade_Counter = true;
	}
	if (Fade_Counter)
	{
		
		if (Fade_In())
		{
			Scene_SetNextScene(SCENE_SCORE);
		}
	}
}
void tag_Name::Draw()
{
	
	//Sprite_Draw_Tex_x_y(Tex[2], 1260, 850);
	for (int i = 0; i < 100; i++)
	{
		Draw_MiddleStandard(Texture.Tex[BG_Texture], BG.position.x, BG.position.y - 2000 * i + BgMoveTime, 1, 1);
	}
	Sprite_Draw_Tex_x_y(Tex[0], 760 ,300);
	Sprite_Draw_Tex_x_y(Tex[1], 700, 550);
	for (int g = 0; g < 27; g++)
	{
		for (int i = 0; i < 5; i++)
		{
			if (Name[i] == g+1)
			{
				Sprite_Draw_Tex_x_y(N_Tex[g], 260.0f + (110.0f * i), 530.0f);
			}
		}
	}
	Fade_Draw();

}

int tag_Name::Time_Info()
{
	return ChangeTime;
}
int tag_Name::Save(int index)
{
	return Name[index];
}
void tag_Name::Uninit()
{
	if (m_pd3dDevice != NULL)
	{
		m_pd3dDevice->Release();
	}
}