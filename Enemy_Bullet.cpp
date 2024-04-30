#include "texture.h"
#include "mydirect3d.h"
#include "input.h"
#include <d3d9.h>
#include <tchar.h>
#include <d3dx9.h>
#include "sprite.h"
#include "collision.h"
#include "judgement.h"
#include "Debug.h"
#include "Bullet.h"
#include "Enemy.h"
#include "Effect.h"
#include "palyer.h"
#include "Enemy_Bullet.h"
#define ENEMY_BULLET_POSITION_X 0
#define ENEMY_BULLET_POSITION_Y 0
#define ENEMY_BULLET_DISTROY 1200
#define ENEMY_BULLET_SIZE_X 200
#define ENEMY_BULLET_SIZE_Y 50
#define BOSS_BULLET_SIZE_X 500
#define BOSS_BULLET_SIZE_Y 500
#define ENEMY_BULLET_RADIUS 0.10f
#define BOSS_BULLET_RADIUS 0.055f
#define ENEMY_BULLET_DESTROY_YM 0.0f
#define ENEMY_BULLET_DESTROY_YP 1000.0f
#define BOSS_BULLET_DESTROY_XP 1000.0f
#define BOSS_BULLET_DESTROY_XM 0.0f
#define ENEMY_BULLET_ANGLE 1.6f
#define ENEMY_BULLET_SPEED 5.0f
#define BOSS_BULLET_SPEED 5.0f
#define BOSS_DETHA 5
#define TEX_MAX 5







void Enemy_Bullet_Init(void)
{
	for (int i = 0; i < ENEMY_BULLET_MAX; i++)
	{
		Enemy_Bullet[i].Position.x = ENEMY_BULLET_POSITION_X;
		Enemy_Bullet[i].Position.y = ENEMY_BULLET_POSITION_Y;
		Enemy_Bullet[i].Visible = false;
		Enemy_Bullet[i].Size.x = ENEMY_BULLET_SIZE_X;
		Enemy_Bullet[i].Size.y = ENEMY_BULLET_SIZE_Y;
		Enemy_Bullet[i].Bullet_Circle.radius = Enemy_Bullet[i].Size.x * ENEMY_BULLET_RADIUS;

		Boss_Bullet_Left[i].Position.x = ENEMY_BULLET_POSITION_X;
		Boss_Bullet_Left[i].Position.y = ENEMY_BULLET_POSITION_Y;
		Boss_Bullet_Left[i].Visible = false;
		Boss_Bullet_Left[i].Size.x = ENEMY_BULLET_SIZE_X;
		Boss_Bullet_Left[i].Size.y = ENEMY_BULLET_SIZE_Y;
		Boss_Bullet_Left[i].Bullet_Circle.radius = Enemy_Bullet[i].Size.x * ENEMY_BULLET_RADIUS;

		Boss_Bullet_Middle[i].Position.x = ENEMY_BULLET_POSITION_X;
		Boss_Bullet_Middle[i].Position.y = ENEMY_BULLET_POSITION_Y;
		Boss_Bullet_Middle[i].Visible = false;
		Boss_Bullet_Middle[i].Size.x = ENEMY_BULLET_SIZE_X;
		Boss_Bullet_Middle[i].Size.y = ENEMY_BULLET_SIZE_Y;
		Boss_Bullet_Middle[i].Bullet_Circle.radius = Enemy_Bullet[i].Size.x * ENEMY_BULLET_RADIUS;

		Boss_Bullet_Right[i].Position.x = ENEMY_BULLET_POSITION_X;
		Boss_Bullet_Right[i].Position.y = ENEMY_BULLET_POSITION_Y;
		Boss_Bullet_Right[i].Visible = false;
		Boss_Bullet_Right[i].Size.x = ENEMY_BULLET_SIZE_X;
		Boss_Bullet_Right[i].Size.y = ENEMY_BULLET_SIZE_Y;
		Boss_Bullet_Right[i].Bullet_Circle.radius = Enemy_Bullet[i].Size.x * ENEMY_BULLET_RADIUS;
	}

}
void Enemy_Bullet_Update(void)
{
	for (int i = 0; i < ENEMY_BULLET_MAX; i++)
	{
		if (Boss_Bullet_Left[i].Visible)
		{
			Boss_Bullet_Left[i].Position.y += 8.0f;
			Boss_Bullet_Left[i].Position.x -= 6.0f;
			Boss_Bullet_Left[i].Bullet_Circle.position = Boss_Bullet_Left[i].Position;

			if (Boss_Bullet_Left[i].Position.y >= 1000)
			{
				Boss_Bullet_Left[i].Visible = false;
			}
		}

		if (Boss_Bullet_Right[i].Visible)
		{
			Boss_Bullet_Right[i].Position.y += 8.0f;
			Boss_Bullet_Right[i].Position.x += 6.0f;
			Boss_Bullet_Right[i].Bullet_Circle.position = Boss_Bullet_Right[i].Position;

			if (Boss_Bullet_Right[i].Position.y >= 1000)
			{
				Boss_Bullet_Right[i].Visible = false;
			}
		}

		if (Boss_Bullet_Middle[i].Visible)
		{
			Boss_Bullet_Middle[i].Position.y +=8.0f;
			Boss_Bullet_Middle[i].Bullet_Circle.position = Boss_Bullet_Middle[i].Position;

			if (Boss_Bullet_Middle[i].Position.y >= 1000)
			{
				Boss_Bullet_Middle[i].Visible = false;
			}
		}


		if (Enemy_Bullet[i].Visible)
		{
			Enemy_Bullet[i].Bullet_Circle.position = Enemy_Bullet[i].Position;
			Enemy_Bullet[i].Position += (Enemy_Bullet[i].Bullet_Move);
		}
		if (Enemy_Bullet[i].Position.y >= ENEMY_BULLET_DESTROY_YP && Enemy_Bullet[i].Visible)
		{
			Enemy_Bullet[i].Visible = false;
		}

	}
}

void Boss_Bullet_Create(float x, float y)
{
	for (int i = 0; i < ENEMY_BULLET_MAX; i++)
	{
		if (!Boss_Bullet_Left[i].Visible)
		{
			Boss_Bullet_Left[i].Position.x = x;
			Boss_Bullet_Left[i].Position.y = y;
			Boss_Bullet_Left[i].Visible = true;
			
		}
		if (!Boss_Bullet_Right[i].Visible)
		{
			Boss_Bullet_Right[i].Position.x = x;
			Boss_Bullet_Right[i].Position.y = y;
			Boss_Bullet_Right[i].Visible = true;
			
		}
		if (!Boss_Bullet_Middle[i].Visible)
		{
			Boss_Bullet_Middle[i].Position.x = x;
			Boss_Bullet_Middle[i].Position.y = y;
			Boss_Bullet_Middle[i].Visible = true;
			break;
		}
	}
}
void Enemy_Bullet_create(float x, float y)
{
	for (int i = 0; i < ENEMY_BULLET_MAX; i++)
	{
		if (!Enemy_Bullet[i].Visible)
		{
			Enemy_Bullet[i].Position.x = x;
			Enemy_Bullet[i].Position.y = y;
			Enemy_Bullet[i].Bullet_Move = Player_Info().position - Enemy_Bullet[i].Position;
			D3DXVec2Normalize(&Enemy_Bullet[i].Bullet_Move, &Enemy_Bullet[i].Bullet_Move);
			Enemy_Bullet[i].Bullet_Move *= 5;
			Enemy_Bullet[i].Visible = true;
			break;
		}
	}
}


void Enemy_Bullet_Draw(void)
{
	for (int i = 0; i < ENEMY_BULLET_MAX; i++)
	{
		if (Enemy_Bullet[i].Visible)
		{
			Draw_MiddleStandard(Texture.Tex[Enemy_Texture_Bullet2], Enemy_Bullet[i].Position.x, Enemy_Bullet[i].Position.y, 0.5, 0.5);
			//Debug_DrawCircle(Enemy_Bullet[i].Position.x, Enemy_Bullet[i].Position.y , Enemy_Bullet[i].Bullet_Circle.radius);
		}
		if (Boss_Bullet_Left[i].Visible)
		{
			Draw_MiddleStandard(Texture.Tex[Enemy_Boss_Texture_Bullet], Boss_Bullet_Left[i].Position.x, Boss_Bullet_Left[i].Position.y, 1, 1);
		
			//Debug_DrawCircle(Boss_Bullet_Left[i].Position.x, Boss_Bullet_Left[i].Position.x, Boss_Bullet_Left[i].Bullet_Circle.radius);
		}
		if (Boss_Bullet_Right[i].Visible)
		{
			Draw_MiddleStandard(Texture.Tex[Enemy_Boss_Texture_Bullet], Boss_Bullet_Right[i].Position.x, Boss_Bullet_Right[i].Position.y, 1, 1);
			//Debug_DrawCircle(Boss_Bullet_Right[i].Position.x, Boss_Bullet_Right[i].Position.x, Boss_Bullet_Right[i].Bullet_Circle.radius);

		}
		if (Boss_Bullet_Middle[i].Visible)
		{
			Draw_MiddleStandard(Texture.Tex[Enemy_Boss_Texture_Bullet], Boss_Bullet_Middle[i].Position.x, Boss_Bullet_Middle[i].Position.y, 1, 1);
			Debug_DrawCircle(Boss_Bullet_Middle[i].Position.x, Boss_Bullet_Middle[i].Position.x, Boss_Bullet_Middle[i].Bullet_Circle.radius);

		}
	}
}
bool Enemy_Bullet_IsUsed(int index)
{
	return Enemy_Bullet[index].Visible;
}

int Enemy_Bullet_Destroy(int index)
{
	return Enemy_Bullet[index].Visible = false;
}

Circle_tag *Enemy_Bullet_GetCollision(int index)
{
	return &Enemy_Bullet[index].Bullet_Circle;
}
enemy_bullet Enemy_Bullet_Info(int index)
{
	return Enemy_Bullet[index];
}
bool Boss_Bullet_IsUsed(int type, int index)
{
	if (type == 0)
		return Boss_Bullet_Left[index].Visible;

	if (type == 1)
		return Boss_Bullet_Right[index].Visible;

	if (type == 2)
		return Boss_Bullet_Middle[index].Visible;
}

bool Boss_Bullet_Distroy(int type, int index)
{
	if (type == 0)
		return Boss_Bullet_Left[index].Visible=false;

	if (type == 1)
		return Boss_Bullet_Right[index].Visible = false;

	if (type == 2)
		return Boss_Bullet_Middle[index].Visible = false;
}

Circle_tag* Boss_Bullet_GetCollision(int type,int index)
{
	if (type == 0)
		return &Boss_Bullet_Left[index].Bullet_Circle;

	if (type == 1)
		return &Boss_Bullet_Right[index].Bullet_Circle;

	if(type == 2)
	return &Boss_Bullet_Middle[index].Bullet_Circle;
}
enemy_bullet Boss_Bullet_Info(int type, int index)
{
	if (type == 0)
	{
		return Boss_Bullet_Left[index];
	}
	if (type == 1)
	{
		return Boss_Bullet_Right[index];
	}
	if (type == 2)
	{
		return Boss_Bullet_Middle[index];
	}
}