#include "palyer.h"
#include "Bullet.h"
#include "EnemyGenerater.h"
#include "Enemy.h"
#include "judgement.h"
#include "Number.h"
#include "item.h"
#include <d3dx9.h>
#include <d3d9.h>
#include "pluseffect.h"
#include "Pause.h"
#include "Victory.h"
#include "Arrow.h"
#include <tchar.h>
#include "Manual.h"
#include <windows.h>
#include "sound.h"
#include "mydirect3d.h"
#include "Fade.h"
#include "common.h"
#include "Debug.h"
#include "Title.h"
#include "game.h"
#include "input.h"
#include "Fade.h"
#include "End.h"
#include "Enemy_Bullet.h"
#include "Effect.h"
#include "Tex.h"
#include "sprite.h"
#include "texture.h"
static int Boss_Time = 0;
static int Auto_Over = 0;
static bool Sound_Begin = false;
static bool Start_Sound_Begin = false;
static bool End_Sound_Begin = false;
static bool Victory_Sound_Begin = false;
static int Title_Begin = 0;
static int End_Begin = 0;
void game_Init(void)
{
		Debug_Init();
		player_Init();
		Bullet_Init();
		Arrow_Init();
		Enemy_Bullet_Init();
		Effect_Init();
		Tex_Init();
		judgement_Init();
		Enemy_Init();
		Item_Init();
		PlusEffect_Init();
		Generater_Init();
		Number_Init();
		Fade_Init();
		Boss_Time = 0;
		Auto_Over = 0;
		Sound_Begin = false;
		Start_Sound_Begin = false;
		End_Sound_Begin = false;
		Victory_Sound_Begin = false;
		Title_Begin = 0;
		End_Begin = 0;
			
		
}
void game_Update(void)
{
	Fade_Out();
	Generater_Update();
	if (!Start_Sound_Begin)
	{
		StopSound();
		PlaySound(SOUND_LABEL_BGM000);
		Start_Sound_Begin = true;
	}
	if (!GetBossUsed())
	{
		player_Update();
		Bullet_Update();
		Enemy_Update();
		Tex_Update();
		Effect_Update();
		Enemy_Bullet_Update();
		judgement_update();
		Item_Update();
		PlusEffect_Update();
	}

}
void game_Draw(void)
{
	Debug_Begin();
	player_Draw();
	Item_Draw();

	PlusEffect_Draw();
	Enemy_Bullet_Draw();
	Enemy_Draw();
	Effect_Draw();

	Tex_Draw();
	//Draw_MiddleStandard(Cur_Texture, 0, 30,1,1);
	Number_Draw(Get_Score(),0,30, 30);
	Bullet_Draw();
	Generater_Draw();

	Debug_End();
	Fade_Draw();
}
void game_Uninit(void) 
{
	player_Uninit();
	Debug_Uninit();
}
