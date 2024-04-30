#include <d3d9.h>
#include <tchar.h>
#include <d3dx9.h>
#include "texture.h"
#include "sprite.h"
#include "Collision.h"
#include "Debug.h"
#include "sound.h"
#include "debug_font.h"
#include "Effect.h"
#include "Enemy.h"
#include "Number.h"
#include "mydirect3d.h"
#include "sprite.h"
#include "EnemyGenerater.h"
#define BULLET_EFFECT_MAX 100
#define ENEMY_DIS_EFFECT_MAX 100
#define AUTO_BULLET_EFFECT_SIZE_X 1200
#define AUTO_BULLET_EFFECT_SIZE_Y 1200
#define PLAYER_BULLET_EFFECT_SIZE_X 400
#define PLAYER_BULLET_EFFECT_SIZE_Y 400
#define ENEMY_BULLET_EFFECT_SIZE_X 600
#define ENEMY_BULLET_EFFECT_SIZE_Y 600
#define BOSS_BULLET_EFFECT_SIZE_X 400
#define BOSS_BULLET_EFFECT_SIZE_Y 400
#define ULT_EFFECT_SIZE_X 5000
#define ULT_EFFECT_SIZE_Y 5000
#define ENEMY_DIS_EFFECT_SIZE_X 800
#define ENEMY_DIS_EFFECT_SIZE_Y 800
#define PLAYER_DISTROY_EFFECT_SIZE_X 800
#define PLAYER_DISTROY_EFFECT_SIZE_Y 800
#define BOSS_DISTROY_EFFECT_SIZE_X 3000
#define BOSS_DISTROY_EFFECT_SIZE_Y 2100
#define ENEMY_3_DISTROY_EFFECT_SIZE_X 1600
#define ENEMY_3_DISTROY_EFFECT_SIZE_Y 1600
#define PLAYER_BULLET_EFFECT_DISTROY 28
#define ENEMY_BULLET_EFFECT_DISTROY 20
#define BOSS_BULLET_EFFECT_DISTROY 20
#define ENEMY_3_DISTROY_EFFECT_DISTROY 35
#define AUTO_BULLET_EFFECT_DISTROY 30
#define PLAYER_EFFECT_DISTROY 25
#define BOSS_EFFECT_DISTROY 30
#define ULT_EFFECT_DISTROY 30
#define ENEMY_DIS_EFFECT_DISTROY 28
#define PLAYER_BULLET_EFFECT_UV_X 80
#define PLAYER_BULLET_EFFECT_UV_Y 100
#define ENEMY_BULLET_EFFECT_UV_X 75
#define ENEMY_BULLET_EFFECT_UV_Y 300
#define BOSS_BULLET_EFFECT_UV_X 80
#define BOSS_BULLET_EFFECT_UV_Y 100
#define PLAYER_DISTROY_EFFECT_UV_X 200
#define PLAYER_DISTROY_EFFECT_UV_Y 200
#define BOSS_DISTROY_EFFECT_UV_X 600
#define BOSS_DISTROY_EFFECT_UV_Y 700
#define ENEMY_3_DISTROY_EFFECT_UV_X 320
#define ENEMY_3_DISTROY_EFFECT_UV_Y 320
#define AUTO_BULLET_EFFECT_UV_X 240
#define AUTO_BULLET_EFFECT_UV_Y 240
#define ULT_EFFECT_UV_X 1000
#define ULT_EFFECT_UV_Y 1000
#define ENEMY_DIS_EFFECT_UV_X 200
#define ENEMY_DIS_EFFECT_UV_Y 200
#define PLAYER_BULLET_EFFECT_SPEED 7
#define ENEMY_BULLET_EFFECT_SPEED 7
#define BOSS_BULLET_EFFECT_SPEED 5
#define ULT_EFFECT_SPEED 6
#define ENEMY_DIS_EFFECT_SPEED 7
#define PLAYER_DISTROY_EFFECT_SPEED 7
#define ENEMY_3_DISTROY_EFFECT_SPEED 5
#define AUTO_BULLET_EFFECT_SPEED 7

#define BOSS_DISTROY_EFFECT_SPEED 10
#define ULT_EFFECT_RADIUS 0.07f
#define TEX_MAX 10
static LPDIRECT3DDEVICE9 m_pd3dDevice;
struct effect
{
	BOOL Visible;
	D3DXVECTOR2 Position;
	D3DXVECTOR2 Size;
	Circle circle;
	short Speed;
};
static effect Player_Bullet_Effect[BULLET_EFFECT_MAX];
static effect Player_Auto_Bullet_Effect[BULLET_EFFECT_MAX];
static effect Boss_Distroy_Effect;

static effect Enemy_Bullet_Effect[BULLET_EFFECT_MAX];
static effect Enemy_Dis_Effect[ENEMY_DIS_EFFECT_MAX];
static effect Fire_Effect[ENEMY_DIS_EFFECT_MAX];
static effect Boss_Skill_Effect[ENEMY_DIS_EFFECT_MAX];

static effect Item_Effect[5];
static effect Enemy_5_Effect[ENEMY_DIS_EFFECT_MAX];
static effect Boss_Shot_Effect;

static effect Player_Distroy_Effect;

void Effect_Init(void)
{
	Number_Init();
	for (short i = 0; i < BULLET_EFFECT_MAX; i++)
	{
		Player_Bullet_Effect[i].Visible = false;
		Player_Bullet_Effect[i].Size.x = PLAYER_BULLET_EFFECT_SIZE_X;
		Player_Bullet_Effect[i].Size.y = PLAYER_BULLET_EFFECT_SIZE_Y;
		Player_Bullet_Effect[i].Speed = 0;

		Player_Auto_Bullet_Effect[i].Speed = 0;
		Player_Auto_Bullet_Effect[i].Visible = false;

		Enemy_Bullet_Effect[i].Visible = false;
		Enemy_Bullet_Effect[i].Size.x = ENEMY_BULLET_EFFECT_SIZE_X;
		Enemy_Bullet_Effect[i].Size.y = ENEMY_BULLET_EFFECT_SIZE_Y;
		Enemy_Bullet_Effect[i].Speed = 0;
	
		Enemy_Dis_Effect[i].Visible = false;
		Enemy_Dis_Effect[i].Size.x = ENEMY_DIS_EFFECT_SIZE_X;
		Enemy_Dis_Effect[i].Size.y = ENEMY_DIS_EFFECT_SIZE_Y;
		Enemy_Dis_Effect[i].Speed = 0;
	

	

		Boss_Skill_Effect[i].Visible = false;
		Boss_Skill_Effect[i].Size.x = ENEMY_DIS_EFFECT_SIZE_X;
		Boss_Skill_Effect[i].Size.y = ENEMY_DIS_EFFECT_SIZE_Y;
		Boss_Skill_Effect[i].Speed = 0;
		Enemy_5_Effect[i].Speed = 0;
		Enemy_5_Effect[i].Visible = false;
		Enemy_5_Effect[i].circle.radius = 120;
		Fire_Effect[i].Speed = 0;
		Fire_Effect[i].Visible = false;
	}
	for (int i = 0; i < 5; i++)
	{
		Item_Effect[i].Speed = 0;
		Item_Effect[i].Visible = false;
	}
	Player_Distroy_Effect.Visible = false;
	Player_Distroy_Effect.Size.x = PLAYER_DISTROY_EFFECT_SIZE_X;
	Player_Distroy_Effect.Size.y = PLAYER_DISTROY_EFFECT_SIZE_Y;
	Player_Distroy_Effect.Speed = 0;

	Boss_Distroy_Effect.Speed = 0;
	Boss_Distroy_Effect.Visible = false;

	Boss_Shot_Effect.Speed = 0;
	Boss_Shot_Effect.Visible = false;
}
void Effect_Dist(void)
{
	for (short i = 0; i < BULLET_EFFECT_MAX; i++)
	{
		Player_Bullet_Effect[i].Visible = false;
		Player_Auto_Bullet_Effect[i].Visible = false;
		Enemy_Bullet_Effect[i].Visible = false;
		Enemy_Dis_Effect[i].Visible = false;
		Boss_Skill_Effect[i].Visible = false;
		Enemy_5_Effect[i].Visible = false;
		Fire_Effect[i].Visible = false;
	
		Boss_Distroy_Effect.Visible = false;
		Boss_Shot_Effect.Visible = false;
	}
}
void Effect_Update(void)
{

	if (Boss_Shot_Effect.Visible)
	{
		Boss_Shot_Effect.Speed += 1;
	}
	for (int i = 0; i < 5; i++)
	{
		if (Item_Effect[i].Visible)
		{
			Item_Effect[i].Speed++;
		}
		if (Item_Effect[i].Speed >= 40)
		{
			Item_Effect[i].Visible = false;
		}
	}

	for (short i = 0; i < BULLET_EFFECT_MAX; i++)
	{

		if (Fire_Effect[i].Visible)
		{
			Fire_Effect[i].Speed += 1;
		}

		if (Boss_Skill_Effect[i].Visible)
		{
			Boss_Skill_Effect[i].Speed++;
		}
		if (Boss_Skill_Effect[i].Speed >= 50)
		{
			Boss_Skill_Effect[i].Visible = false;
		}

		if (Player_Bullet_Effect[i].Visible)
		{
			Player_Bullet_Effect[i].Speed += 1;
		}
		if (Player_Bullet_Effect[i].Speed >= 25)
		{
			Player_Bullet_Effect[i].Visible = false;
		}
		if (Player_Auto_Bullet_Effect[i].Visible)
		{
			Player_Auto_Bullet_Effect[i].Speed += 1;
		}
		if (Player_Auto_Bullet_Effect[i].Speed >= 20)
		{
			Player_Auto_Bullet_Effect[i].Visible = false;
		}
		if (Enemy_Bullet_Effect[i].Visible)
		{
			Enemy_Bullet_Effect[i].Speed += 1;
		}
		if (Enemy_Bullet_Effect[i].Speed >= 25)
		{
			Enemy_Bullet_Effect[i].Visible = false;
		}

		if (Enemy_5_Effect[i].Visible)
		{
			Enemy_5_Effect[i].circle.position = Enemy_5_Effect[i].Position;
			Enemy_5_Effect[i].Speed++;
		}
		if (Enemy_5_Effect[i].Speed >= 50)
		{
			Enemy_5_Effect[i].Visible = false;
		}
		if (Enemy_Dis_Effect[i].Visible)
		{
			Enemy_Dis_Effect[i].Speed += 1;
		}
		if (Enemy_Dis_Effect[i].Speed >= 23)
		{
			Enemy_Dis_Effect[i].Visible = false;
		}

	}
	if (Boss_Distroy_Effect.Visible)
	{	
		Boss_Distroy_Effect.Speed += 1;
	}	
	if (Boss_Distroy_Effect.Speed >= 50)
	{	
		Boss_Distroy_Effect.Visible = false;
	}
	if (Player_Distroy_Effect.Visible)
	{
		Player_Distroy_Effect.Speed += 1;
	}
	if (Player_Distroy_Effect.Speed >= 50)
	{
		Player_Distroy_Effect.Visible = false;
	}
	
}
void Boss_Skill_Effect_Create(float x, float y)
{

	for (short i = 0; i < BULLET_EFFECT_MAX; i++)
	{
		if (!Boss_Skill_Effect[i].Visible)
		{
			Boss_Skill_Effect[i].Position.x = x;
			Boss_Skill_Effect[i].Position.y = y;
			Boss_Skill_Effect[i].Speed = 0;
			Boss_Skill_Effect[i].Visible = true;
			break;
		}
	}
}
void Effect_create(int type,float x, float y)
{

	{
		if (type == BOSS_DISTROY_EFFECT)
		{
			if (!Boss_Distroy_Effect.Visible)
			{
				Boss_Distroy_Effect.Position.x = x;
				Boss_Distroy_Effect.Position.y = y;
				Boss_Distroy_Effect.Speed = 0;
				Boss_Distroy_Effect.Visible = true;
			}
		}
		if (type == PLAYER_DISTROY_EFFECT)
		{
			if (!Player_Distroy_Effect.Visible)
			{
				Player_Distroy_Effect.Position.x = x;
				Player_Distroy_Effect.Position.y = y;
				Player_Distroy_Effect.Speed = 0;
				Player_Distroy_Effect.Visible = true;
			}
		}
		if (type == BOSS_SHOT_EFFECT)
		{
			if (!Boss_Shot_Effect.Visible)
			{
				Boss_Shot_Effect.Position.x = x;
				Boss_Shot_Effect.Position.y = y;
				Boss_Shot_Effect.Speed = 0;
				Boss_Shot_Effect.Visible = true;

			}
		}
		else
		{

			for (short i = 0; i < BULLET_EFFECT_MAX; i++)
			{

				if (type == ENEMY_BULLET_EFFECT)
				{
					if (!Enemy_Bullet_Effect[i].Visible)
					{
						Enemy_Bullet_Effect[i].Position.x = x;
						Enemy_Bullet_Effect[i].Position.y = y;
						Enemy_Bullet_Effect[i].Speed = 0;
						Enemy_Bullet_Effect[i].Visible = true;
						break;
					}
				}
				if (type == PLAYER_BULLET_EFFECT)
				{
					if (!Player_Bullet_Effect[i].Visible)
					{
						Player_Bullet_Effect[i].Position.x = x;
						Player_Bullet_Effect[i].Position.y = y;
						Player_Bullet_Effect[i].Speed = 0;
						Player_Bullet_Effect[i].Visible = true;
						break;
					}
				}
				if (type == PLAYER_AUTO_BULLET_EFFECT)
				{
					if (!Player_Auto_Bullet_Effect[i].Visible)
					{
						Player_Auto_Bullet_Effect[i].Position.x = x;
						Player_Auto_Bullet_Effect[i].Position.y = y;
						Player_Auto_Bullet_Effect[i].Speed = 0;
						Player_Auto_Bullet_Effect[i].Visible = true;
						break;
					}
				}
				if (type == ENEMY_DISTORY_EFFECT)
				{
					if (!Enemy_Dis_Effect[i].Visible)
					{
						Enemy_Dis_Effect[i].Position.x = x;
						Enemy_Dis_Effect[i].Position.y = y;
						Enemy_Dis_Effect[i].Speed = 0;
						Enemy_Dis_Effect[i].Visible = true;
						break;
					}
				}

				if (type == ITEM_EFFECT && i < 5)
				{
					if (!Item_Effect[i].Visible)
					{

						Item_Effect[i].Position.x = x;
						Item_Effect[i].Position.y = y;
						Item_Effect[i].Speed = 0;
						Item_Effect[i].Visible = true;
						break;
					}
				}
				if (type == ENEMY_5_EFFECT)
				{
					if (!Enemy_5_Effect[i].Visible)
					{

						Enemy_5_Effect[i].Position.x = x;
						Enemy_5_Effect[i].Position.y = y;
						Enemy_5_Effect[i].Speed = 0;
						Enemy_5_Effect[i].Visible = true;
						break;
					}
				}

				if (type == FIRE_EFFECT)
				{
					if (!Fire_Effect[i].Visible)
					{
						Fire_Effect[i].Position.x = x;
						Fire_Effect[i].Position.y = y;
						Fire_Effect[i].Speed = 0;
						Fire_Effect[i].Visible = true;
						break;
					}
				}


			}
		}
	}
}
 


void Effectdraw(int tex, float x, float y, float scaling, int speed, int RenderSpeed, int Widht, int Length)
{
	float cutU = (float)1 / (float)Widht;
	float cutV = (float)1 / (float)Length;
	int X = (speed / RenderSpeed) % Widht;
	int Y = (speed / (RenderSpeed * Widht)) % Length;
	float u = cutU * X;
	float v = cutV * Y;
	Sprite_Draw(tex, x, y, scaling, u,v, cutU, cutV);
	

}


void Effect_Draw(void)
{
	if (Boss_Distroy_Effect.Visible)
	{
		Effectdraw(Texture.Tex[Summoner_Texture_Bullet_Effect], Boss_Distroy_Effect.Position.x, Boss_Distroy_Effect.Position.y, 6, Boss_Distroy_Effect.Speed, 4, 5, 3);
	}
	if (Player_Distroy_Effect.Visible)
	{
		Effectdraw(Texture.Tex[Player_Texture_Distroy_Effect], Player_Distroy_Effect.Position.x, Player_Distroy_Effect.Position.y, 1.5, Player_Distroy_Effect.Speed, 4, 2, 8);
	}
	else
	{

		for (short i = 0; i < BULLET_EFFECT_MAX; i++)
		{
			if (Boss_Skill_Effect[i].Visible)
			{
				Effectdraw(Texture.Tex[Enemy_Texture_Boss_Skill_Effect], Boss_Skill_Effect[i].Position.x, Boss_Skill_Effect[i].Position.y, 1, Boss_Skill_Effect[i].Speed, 4, 2, 7);
			}

			if (Enemy_Bullet_Effect[i].Visible)
			{
				Effectdraw(Texture.Tex[Enemy_Texture_Bullet_Effect], Enemy_Bullet_Effect[i].Position.x, Enemy_Bullet_Effect[i].Position.y, 1, Enemy_Bullet_Effect[i].Speed, 2, 2, 7);
			}
			if (Player_Bullet_Effect[i].Visible)
			{
				Effectdraw(Texture.Tex[Player_Texture_Bullet_Effect], Player_Bullet_Effect[i].Position.x, Player_Bullet_Effect[i].Position.y, 1, Player_Bullet_Effect[i].Speed, 2, 2, 6);
			}
	
			if (Player_Auto_Bullet_Effect[i].Visible)
			{
				Effectdraw(Texture.Tex[Player_Texture_Auto_Bullet_Effect], Player_Auto_Bullet_Effect[i].Position.x, Player_Auto_Bullet_Effect[i].Position.y, 2, Player_Auto_Bullet_Effect[i].Speed, 2, 2, 5);
			}
			if (Enemy_Dis_Effect[i].Visible)
			{
				Effectdraw(Texture.Tex[Enemy_Texture_Distory_Effect], Enemy_Dis_Effect[i].Position.x, Enemy_Dis_Effect[i].Position.y, 1, Enemy_Dis_Effect[i].Speed, 2, 2, 6);
			}

			if (Item_Effect[i].Visible && i < 5)
			{
				Effectdraw(Texture.Tex[Item_Texture_Effect], Item_Effect[i].Position.x, Item_Effect[i].Position.y, 1.5, Item_Effect[i].Speed, 2, 2, 10);
			}
			if (!BossUsed())
			{
				if (Enemy_5_Effect[i].Visible)
				{
					Effectdraw(Texture.Tex[Enemy_Texture_5_Effect], Enemy_5_Effect[i].Position.x, Enemy_5_Effect[i].Position.y, 5, Enemy_5_Effect[i].Speed, 2, 5, 5);
					//Debug_DrawCircle(Enemy_5_Effect[i].Position.x, Enemy_5_Effect[i].Position.y, Enemy_5_Effect[i].circle.radius);
				}
			}
			if (Fire_Effect[i].Visible && Boss_Info().Visible)
			{
				Effectdraw(Texture.Tex[Fire_Texture], Fire_Effect[i].Position.x, Fire_Effect[i].Position.y, 3, Fire_Effect[i].Speed, 4, 2, 3);
			}

		}
		if (Boss_Shot_Effect.Visible && Boss_Info().Visible)
		{
			Effectdraw(Texture.Tex[Enemy_Texture_Boss_Bullet_Shot_Effect], Boss_Info().Position.x, Boss_Info().Position.y + 20, 3, Boss_Shot_Effect.Speed, 4, 5, 2);
		}
	}
}
bool Effect_IsUsed(int index)
{
	return Enemy_5_Effect[index].Visible;
}
Circle_tag* Effect_GetCollision(short index)
{
	return &Enemy_5_Effect[index].circle;
}




