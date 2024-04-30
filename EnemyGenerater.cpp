#include "mydirect3d.h"
#include "input.h"
#include <d3d9.h>
#include <tchar.h>
#include <stdlib.h>
#include <time.h>
#include <d3dx9.h>
#include "Enemy.h"
#include "texture.h"
#include "game.h"
#include "Item.h"
#include "sound.h"
#include <time.h>
#include "sprite.h"
#define CREATE_SPEED_ITEM 1000
#define CREATE_SPEED_ITEM_2 1500
#define CREATE_SPEED_ENEMY 100
#define CREATE_SPEED_ENEMY_2 200
#define CREATE_SPEED_ENEMY_3 300
#define CREATE_NUMBER_ITEM 1
#define CREATE_NUMBER_ITEM_2 1
#define CREATE_NUMBER_ENEMY 6
#define CREATE_NUMBER_ENEMY_2 6
#define CREATE_NUMBER_ENEMY_3 6
#define CREATE_BOSS 111111110
#define CREATE_ENEMY_2 0
#define CREATE_ENEMY_3 1300


static int Create_Time = 0;
static int ItemUsed = 0;
static bool Boss_IsUsede = false;
static bool Fade_Trigger = false;
static int Fade = 0;
static float Warning_Move = 0;
static bool Boss_Begin = false;
void Generater_Init(void)
{
	Create_Time = 0;
	ItemUsed = 0;
	Boss_IsUsede = false;
	Fade_Trigger = false;
	Fade = 0;
	Warning_Move = 0;
	Boss_Begin = false;
	srand((unsigned int)time(NULL));
	ItemUsed = (rand() % 700) +100;

}
void Generater_Update(void)
{
	ItemUsed = (rand() % 700) + 100;
	Warning_Move += 0.5f;
	Create_Time++;
	switch (Create_Time)
	{

	case 100:
		Enemy_create(1, 200.0f, 0.0f);
		Enemy_create(1, 200.0f, -50.0f);
		Enemy_create(1, 200.0f, -100.0f);
		break;
	case 300:
		Enemy_create(1, 600.0f, 0.0f);
		Enemy_create(1, 600.0f, -50.0f);
		Enemy_create(1, 600.0f, -100.0f);
		break;
	case 500:
		Item_create(ITEM, (float)ItemUsed, 0.0f);
		Enemy_create(1, 350.0f, 0.0f);
		Enemy_create(1, 450.0f, 0.0f);
		Enemy_create(2, 150.0f, 0.0f);
		Enemy_create(2, 650.0f, 0.0f);
		break;
	case 700:
		Enemy_create(1, 200.0f, 0.0f);
		Enemy_create(1, 600.0f, 0.0f);
		Enemy_create(1, 200.0f, -50.0f);
		Enemy_create(1, 600.0f, -50.0f);
		Enemy_create(3, 400.0f, 200.0f);
		break;
	case 1000:
		Enemy_create(1, 100.0f, 0.0f);
		Enemy_create(1, 700.0f, 0.0f);
		Enemy_create(1, 100.0f, -50.0f);
		Enemy_create(1, 700.0f, -50.0f);
		Enemy_create(4, 400.0f, 0.0f);
		Item_create(ITEM, (float)ItemUsed, 0.0f);
		break;
	case 1400:
		Enemy_create(1, 200.0f, 0.0f);
		Enemy_create(1, 200.0f, -50.0f);

		Enemy_create(1, 600.0f, 0.0f);
		Enemy_create(1, 600.0f, -50.0f);

		Enemy_create(5, 400.0f, 0.0f);
		break;
	case 1600:
		Item_create(ITEM, (float)ItemUsed, 0.0f);
		Enemy_create(2, 150.0f, 0.0f);
		Enemy_create(2, 650.0f, 0.0f);
		break;

	case 2000:
		Item_create(ITEM, (float)ItemUsed, 0.0f);

		Enemy_create(1, 200.0f, 0.0f);
		Enemy_create(2, 200.0f, -50.0f);
		Enemy_create(4, 400.0f, 0.0f);
		Enemy_create(1, 600.0f, 0.0f);
		Enemy_create(2, 600.0f, -50.0f);
		break;

	case 2500:
		Enemy_create(5, 200.0f, 0.0f);
		Enemy_create(5, 600.0f, 0.0f);
		Enemy_create(3, 200.0f, 300.0f);
		Enemy_create(3, 400.0f, 300.0f);
		Enemy_create(3, 600.0f, 300.0f);
		break;

	case 3000:
		Item_create(ITEM, (float)ItemUsed, 0.0f);
		Enemy_create(4, 200.0f, 0.0f);
		Enemy_create(4, 400.0f, 0.0f);
		Enemy_create(4, 600.0f, 0.0f);
		Enemy_create(1, 100.0f, 0.0f);
		Enemy_create(1, 700.0f, 0.0f);
		break;

	case 3500:
		StopSound();
		Boss_IsUsede = true;
		break;
	case 3900:
		PlaySound(SOUND_LABER_BOSSBGM);
		Boss_IsUsede = false;
		Boss_Begin = true;
		Enemy_create(6, 400.0f, 0.0f);
		break;
	default:
		break;
	} 

	if (!Fade_Trigger && Boss_IsUsede)
	{
		Fade += 5;
	}
	if (Fade >= 200)
	{
		Fade_Trigger = true;
	}
	if (Fade_Trigger)
	{
		Fade -= 5;
	}
	if (Fade_Trigger && Fade <= 0)
	{
		Fade_Trigger = false;
	}

}
	

void Generater_Draw(void)
{
	if (Boss_IsUsede)
	{
		Draw_MiddleStandard(Texture.Tex[Red_Texture], 400, 500, 1, 1, Fade);
		for (int i = 0; i <10; i++)
		{
			Draw_MiddleStandard(Texture.Tex[Warning_Texture], 400 - 800 * i+ Warning_Move, 500, 1, 1, 200);
		}
	}

}
bool GetBossUsed()
{
	return Boss_IsUsede;
}
bool BossUsed()
{
	return Boss_Begin;
}