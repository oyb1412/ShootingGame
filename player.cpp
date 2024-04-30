#include "input.h"
#include "texture.h"
#include "sprite.h"
#include "common.h"
#include "mydirect3d.h"
#include "Bullet.h"
#include <d3d9.h>
#include <tchar.h>
#include <d3dx9.h>
#include "pluseffect.h"
#include "debug_font.h"
#include <windows.h>
#include "Collision.h"
#include "Mouse.h"
#include "sound.h"
#include "palyer.h"
#include "judgement.h"
#include "Debug.h"
#include "Enemy.h"
#include "Effect.h"
#include "Fade.h"
#define BULLET_DELAY 10
#define AUTO_BULLET_DELAY 20
#define PLAYER_MOVEWAY ?
#define BG_POSITION_X 400.0f
#define BG_POSITION_Y 500.0f



#define PLAYER_POSITION_X 400.0f
#define PLAYER_POSITION_Y 950.0f
#define PLAYER_SPEED 10
#define FADE_MAX 255
#define PLAYER_DISTROY 1200
#define PLAYER_DETHA 0
#define BOSS_DETHA 5
static float BulletShotTime = 0; 
static float AutoBulletShotTime = 0;
static int SummonerBulletShotTime = 0;
static float BgMoveTime = 0;
static float UltShotTime = 0;
static int Player_Fade = FADE_MAX;
static bool Player_Fade_Start = false;
static bool Player_Fade_Change = false;
static int Player_Auto_Move = 0;
static int Fade_Time = 0;
static bool Fade_Begin = false;
static bool DisPlayer = false;
static int DisPlayerTime = 0;
struct bg
{
	D3DXVECTOR2 position;
	D3DCOLOR color;
	D3DXVECTOR2 uv;
	D3DXVECTOR2 size;
};      
static bg BG;




void player_Init(void)
{ 
	Player.Visible = true;
	BG.position.x = BG_POSITION_X;
	BG.position.y = BG_POSITION_Y;
	Player.hp = PLAYER_HP;
	Player.position.x = PLAYER_POSITION_X;
	Player.position.y = PLAYER_POSITION_Y;
	Player.speed = PLAYER_SPEED;
	Player.player_circle.radius = 40;
	Fade_Init();

	BulletShotTime = 0; 
	AutoBulletShotTime = 0;
	SummonerBulletShotTime = 0;
	 BgMoveTime = 0;
	UltShotTime = 0;
	Player_Fade = FADE_MAX;
	Player_Fade_Start = false; 
	Player_Fade_Change = false;
	Player_Auto_Move = 0;
	Fade_Time = 0;
	Fade_Begin = false;
	DisPlayer = false;
	DisPlayerTime = 0;
}
void player_Update(void)
{

	//if (Player.hp == PLAYER_DETHA && Player.Visible)
	//{
	//	PlaySound(SOUND_LABEL_SE_PLAYER_DISTROY);
	//	//Player_Distroy_Effect_create(Player.position.x, Player.position.y);
	//	Player.Visible = false;
	//	Player.position.x = PLAYER_DISTROY;
	//}
//	if (Player.Visible)
	{
		if (Player.hp <= 0 && !DisPlayer)
		{
			StopSound();
			PlaySound(SOUND_LABEL_SE_PLAYER_DISTROY);
		
			DisPlayer = true;
			Effect_create(PLAYER_DISTROY_EFFECT, Player.position.x, Player.position.y);
			Player.Visible = false;
			//if (Fade_In() && !Player.Visible)
			//{
			//	Effect_Dist();
			//	Scene_SetNextScene(SCENE_TITLE);
			//}
		}
		if (DisPlayer)
		{
			DisPlayerTime++;
		}
		if (DisPlayerTime > 100)
		{
			if (Fade_In() && !Player.Visible)
			{
				Scene_SetNextScene(SCENE_NAME);
				DisPlayer = false;
				DisPlayerTime = 0;
			}
		}
	}
	if (Player.hp >= 1)
	{

		{
			BulletShotTime += 1;
			AutoBulletShotTime += 1;
			SummonerBulletShotTime += 1;
			UltShotTime += 1;
			BgMoveTime += 0.5;
			D3DXVECTOR2 dir(0.0f, 0.0f);
			Player.player_circle.position = Player.position;

	

			if (Fade_Time > 100)
			{
				Player_Fade_Change = false;
				Player_Fade_Start = false;
				Player_Fade = 255;
				Fade_Time = 0;
			}
				if (Player_Fade_Start && !Player_Fade_Change)
				{
					Player_Fade -= 30;
					Fade_Time++;
				}
				if (Player_Fade <= 0 && Player_Fade_Start && !Player_Fade_Change)
				{
					Player_Fade_Change = true;
					Player_Fade_Start = false;
				}
				if (Player_Fade_Change && !Player_Fade_Start)
				{
					Player_Fade += 30;
					Fade_Time++;
				}
				if (Player_Fade >= FADE_MAX && Player_Fade_Change && !Player_Fade_Start)
				{
					Player_Fade_Start = true;
					Player_Fade_Change = false;
				}
			
			

			if (Keyboard_IsPress(DIK_UP))
			{
				dir.y -= 1;
			}
			if (Keyboard_IsPress(DIK_RIGHT))
			{
				dir.x += 1;

			}
			if (Keyboard_IsPress(DIK_LEFT))
			{
				dir.x -= 1;
				
			}
			if (Keyboard_IsPress(DIK_DOWN))
			{
				dir.y += 1;

			}
			
			D3DXVec2Normalize(&dir, &dir);

			D3DXVECTOR2 vecSpeed = dir * Player.speed;
			Player.position += vecSpeed;

			if (Player.position.x <= 50.0f)
			{
				Player.position.x = 50.0f;
			}
			if (Player.position.x >= 750.0f)
			{
				Player.position.x = 750.0f;
			}
			if (Player.position.y <= 190.0f)
			{
				Player.position.y = 190.0f;
			}
			if (Player.position.y >= 900.0f)
			{
				Player.position.y = 900.0f;
			}
			if (Keyboard_IsPress(DIK_SPACE) && BulletShotTime >= (BULLET_DELAY ))
			{
				Bullet_create(Middle,Player.position.x, Player.position.y);
				if(Get_Bullet_Level() > 0)
				Bullet_create(Left, Player.position.x, Player.position.y);

				if (Get_Bullet_Level() > 1)
				Bullet_create(Right, Player.position.x, Player.position.y);


			
				BulletShotTime = 0;
				PlaySound(SOUND_LABEL_SE_SHOT);
			}
			if (Keyboard_IsPress(DIK_SPACE) && AutoBulletShotTime >= 80 && Get_Bullet_Level() > 2)
			{
				
				Auto_Bullet_create(Player.position.x, Player.position.y);
				
				AutoBulletShotTime = 0;

				PlaySound(SOUND_LABEL_SE_AUTO_BULLET_SHOT);
			}
			if (Keyboard_IsPress(DIK_SPACE) && SummonerBulletShotTime >= 40)
			{
				if (Get_Bullet_Level() > 3)
				{
					Bullet_create(Summoner_Left, Player.position.x - 70.0f, Player.position.y + 10);
				}
				if (Get_Bullet_Level() > 4)
				{
					Bullet_create(Summoner_Right, Player.position.x + 70.0f, Player.position.y + 10);
				}
				SummonerBulletShotTime = 0;
			}

		
		}
	}
}
void player_Draw(void)
{
	//Debug_DrawCircle(Player.position.x, Player.position.y, Player.player_circle.radius);

	for (int i = 0; i < 100; i++)
	{
		Draw_MiddleStandard(Texture.Tex[BG_Texture], BG.position.x, BG.position.y - 2000 * i + BgMoveTime, 1,1);
	}
	if (Player.Visible)
	{
		Draw_MiddleStandard(Texture.Tex[Player_Texture], Player.position.x, Player.position.y, 0.7, 0.7,Player_Fade);
	}
	for (int i = 0; i < Player.hp; i++)
	{
		Draw_MiddleStandard(Texture.Tex[Player_Texture_Life], (float)35 + 40 * i, (float)960, 0.5, 0.5);
	}
	if (Get_Bullet_Level() > 3)
	{
		Draw_MiddleStandard(Texture.Tex[Summoner_Texture], Player.position.x - 70.0f, Player.position.y+10, 0.5,0.5);
	}
	if (Get_Bullet_Level() > 4)
	{
		Draw_MiddleStandard(Texture.Tex[Summoner_Texture], Player.position.x + 70.0f, Player.position.y+10, 0.5, 0.5);
	}
	Fade_Draw();
}
player Player_Info()
{
	return Player;
}
void player_Uninit(void)
{
	Keyboard_Finalize();
}
Circle_tag* Player_GetCollision(void)
{
	return &Player.player_circle;
}
int Player_HitPoint(void)
{
	return Player.hp--;
}
int Player_Hp(void)
{
	return Player.hp;
}
bool Player_Iki()
{
	if (Player.Visible)
	{
		return true;
	}
	else
	{
		return false;
	}
}
int Player_Hp_Init(int x)
{
	return Player.hp +=x ;
}
void Player_Destroy(void)
{
	Player.Visible = false;
}
void Player_IsUsed(void)
{
	Player.Visible;
}
void Player_Reset(void)
{
	Player.position.x = 600.0f;
	Player.position.y = 1000.0f;
}
int Player_Fade_Begin(void)
{
	return Player_Fade_Start = true;
}
float Player_Position_X(void)
{
	return Player.position.x;
}
float Player_Position_Y(void)
{
	return Player.position.y;
}
bool Fade_Trigger(void)
{
	if (Player_Fade_Start == false && Player_Fade_Change == false)
	{
		return true;
	}
	else
		return false;
}
void Player_Fade_Reset(void)
{
	Player_Fade = FADE_MAX;
	Player_Fade_Start = false;
	Player_Fade_Change = false;
	Player_Auto_Move = 0;
	Player.Visible = true;
}