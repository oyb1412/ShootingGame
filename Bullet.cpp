#include "texture.h"
#include "mydirect3d.h"
#include "input.h"
#include <d3d9.h>
#include <tchar.h>
#include <d3dx9.h>
#include "sprite.h"
#include "collision.h"
#include "judgement.h"
#include "palyer.h"
#include "Debug.h"
#include "Bullet.h"
#include "Effect.h"
#include "Enemy.h"
#include "pluseffect.h"
#define ULT_RESET 3

#define ULT_IMAGE_BASE_POSITION_X 30
#define ULT_IMAGE_POSITION_X 50
#define ULT_IMAGE_POSITION_Y 940
#define ULT_EFFECT_POSITION_X 500.0f
#define ULT_EFFECT_POSITION_Y 400.0f
#define BULLET_SIZE_X 80
#define BULLET_SIZE_Y 170
#define AUTO_BULLET_POSITION_X 100
#define AUTO_BULLET_POSITION_Y 100
#define ULT_MAX 5
#define BULLET_ZURE_RIGHT_X 50
#define BULLET_ZURE_Y 20
#define BULLET_ZURE_X 25
#define ENEMY_ZURE_LEFE 50
#define ULT_ZURE_X 25
#define ENEMY_ZURE_RIGHT 100
#define ENEMY_2_ZURE_LEFT 80
#define ENEMY_2_ZURE_RIGHT 100
#define ENEMY_3_ZURE 50
#define ULT_DISTROY 500
#define AUTO_BULLET_SPEED_X 11
#define AUTO_BULLET_SPEED_Y 8
#define AUTO_BULLET_SIZE_X 200
#define AUTO_BULLET_SIZE_Y 130
#define BULLET_RADIUS 0.3f
#define AUTO_BULLET_RADIUS 0.25f
#define BULLET_AUTODESTROY 0.0f
#define BULLET_ANGLE 62.35f
#define BULLET_LEFT_ANGLE 62.2f
#define BULLET_RIGHT_ANGLE 62.5f
#define BULLET_SPEED 10.0f
#define AUTO_BULLET_SPEED 6.0f
#define ULT_POSITION_X 500
#define ULT_POSITION_Y 1000
#define ULT_SIZE_X 50
#define ULT_SIZE_Y 120
#define ULT_AUTODESTROY 0.0f
#define ULT_ANGLE 62.8f
#define ULT_SPEED 10.0f
#define ULT_NUMBER 3
#define AUTO_BULLET_ANGLE 70.67f
#define BULLET_SPEED_X 1.5f
#define AUTO_BULLET_RADIUS_X 50
#define AUTO_BULLET_RADIUS_Y 30
#define TEX_MAX 10
#define SCALE_MAX 100000000
static int Bullet_Level =0;
static long long Enemy_NearestDistance[5] = { SCALE_MAX };
static long Enemy_NearestIndex[5] = { 0};
static float Enemy_xDistance[5] = {0 };
static float Enemy_yDistance[5] = {0 };
static float Enemy_distanceX2[5] ={0 };




void Bullet_Init(void)
{
	Bullet_Level = 0;
	Enemy_NearestDistance[5] = { SCALE_MAX };
	Enemy_NearestIndex[5] = { 0 };
	Enemy_xDistance[5] = { 0 };
	Enemy_yDistance[5] = { 0 };
	Enemy_distanceX2[5] = { 0 };



	for (short i = 0; i < BULLET_MAX; i++)
	{


		Auto_Bullet[i].Visible = false;
		Auto_Bullet[i].Size.x = AUTO_BULLET_SIZE_X;
		Auto_Bullet[i].Size.y = AUTO_BULLET_SIZE_Y;
		Auto_Bullet[i].Bullet_Circle.radius = Auto_Bullet[i].Size.x * AUTO_BULLET_RADIUS;

		Auto_Bullet[i].Position.x = AUTO_BULLET_POSITION_X;
		Auto_Bullet[i].Position.y = AUTO_BULLET_POSITION_Y;

		Bullet[i].Visible = false;
		Bullet[i].Size.x = BULLET_SIZE_X;
		Bullet[i].Size.y = BULLET_SIZE_Y;
		Bullet[i].Bullet_Circle.radius = Bullet[i].Size.x * BULLET_RADIUS;

		Bullet_Left[i].Visible = false;
		Bullet_Left[i].Size.x = BULLET_SIZE_X;
		Bullet_Left[i].Size.y = BULLET_SIZE_Y;
		Bullet_Left[i].Bullet_Circle.radius = Bullet_Left[i].Size.x * BULLET_RADIUS;

		Bullet_Right[i].Visible = false;
		Bullet_Right[i].Size.x = BULLET_SIZE_X;
		Bullet_Right[i].Size.y = BULLET_SIZE_Y;
		Bullet_Right[i].Bullet_Circle.radius = Bullet_Right[i].Size.x * BULLET_RADIUS;

		Summoner_Bullet_Left[i].Visible = false;
		Summoner_Bullet_Left[i].Size.x = BULLET_SIZE_X;
		Summoner_Bullet_Left[i].Size.y = BULLET_SIZE_Y;
		Summoner_Bullet_Left[i].Bullet_Circle.radius = Summoner_Bullet_Left[i].Size.x * 0.4;

		Summoner_Bullet_Right[i].Visible = false;
		Summoner_Bullet_Right[i].Size.x = BULLET_SIZE_X;
		Summoner_Bullet_Right[i].Size.y = BULLET_SIZE_Y;
		Summoner_Bullet_Right[i].Bullet_Circle.radius = Summoner_Bullet_Right[i].Size.x * 0.4;
	}
	
}
void Bullet_Update(void)
{
	{
		for (int i = 0; i < 5; i++)
			Enemy_NearestDistance[i] = SCALE_MAX;

		for (short j = 0; j < BULLET_MAX; j++)
		{
			for (int i = 0; i < 5; i++)
			{
				Enemy_xDistance[i] = 0;
				Enemy_yDistance[i] = 0;
				Enemy_distanceX2[i] = 0;
				if (Enemy_IsUsed(i, j))
				{
					Enemy_xDistance[i] = Enemy_Info(i, j).Position.x - Player_Position_X();
					Enemy_yDistance[i] = Enemy_Info(i, j).Position.y - Player_Position_Y();
					Enemy_distanceX2[i] = (Enemy_xDistance[i] * Enemy_xDistance[i]) + (Enemy_yDistance[i] * Enemy_yDistance[i]);
					if (Enemy_distanceX2[i] < Enemy_NearestDistance[i])
					{
						Enemy_NearestDistance[i] = (long long)Enemy_distanceX2[i];
						Enemy_NearestIndex[i] = j;
					}
				}
			}
		}
		for (short j = 0; j < BULLET_MAX; j++)
		{
			for (int i = 0; i < 5; i++)
			{
				if (Auto_Bullet[j].Visible && !Boss_Info().Visible)
				{
					if (Enemy_Info(i, Enemy_NearestIndex[i]).Position.x > Auto_Bullet[j].Position.x)
					{
						if (Player_Info().position.y - Enemy_Info(i, j).Position.y < 800)
							Auto_Bullet[j].Position.x += 7;
					}
					else if (Enemy_Info(i, Enemy_NearestIndex[i]).Position.x < Auto_Bullet[j].Position.x)
					{
						if (Player_Info().position.y - Enemy_Info(i, j).Position.y < 800)
							Auto_Bullet[j].Position.x -= 7;
					}
				}
			}


		}




		for (short i = 0; i < BULLET_MAX; i++)
		{
			Auto_Bullet[i].Position.y -= AUTO_BULLET_SPEED_Y;
			if (Summoner_Bullet_Left[i].Visible)
			{
				if (Get_Bullet_Level() > 3)
				{
					Summoner_Bullet_Left[i].Position.y -= 15;
					Summoner_Bullet_Left[i].Bullet_Circle.position.x = Summoner_Bullet_Left[i].Position.x;
					Summoner_Bullet_Left[i].Bullet_Circle.position.y = Summoner_Bullet_Left[i].Position.y - 30;
				}
			}
			if (Summoner_Bullet_Right[i].Visible)
			{
				if (Get_Bullet_Level() > 4)
				{
					Summoner_Bullet_Right[i].Position.y -= 15;
					Summoner_Bullet_Right[i].Bullet_Circle.position.x = Summoner_Bullet_Right[i].Position.x;
					Summoner_Bullet_Right[i].Bullet_Circle.position.y = Summoner_Bullet_Right[i].Position.y - 30;

				}
			}
			if (Bullet[i].Visible)
			{
				Bullet[i].Position.y -= BULLET_SPEED;
				Bullet[i].Bullet_Circle.position = Bullet[i].Position;
				if (Bullet[i].Position.y <= BULLET_AUTODESTROY)
				{
					Bullet[i].Visible = false;
				}
			}
			if (Bullet_Left[i].Visible)
			{
				Bullet_Left[i].Position.y -= BULLET_SPEED;
				Bullet_Left[i].Position.x -= BULLET_SPEED_X;
				Bullet_Left[i].Bullet_Circle.position = Bullet_Left[i].Position;
				if (Bullet_Left[i].Position.y <= BULLET_AUTODESTROY)
				{
					Bullet_Left[i].Visible = false;
				}
			}
			if (Bullet_Right[i].Visible)
			{
				Bullet_Right[i].Position.y -= BULLET_SPEED;
				Bullet_Right[i].Position.x += BULLET_SPEED_X;

				Bullet_Right[i].Bullet_Circle.position = Bullet_Right[i].Position;
				if (Bullet_Right[i].Position.y <= BULLET_AUTODESTROY)
				{
					Bullet_Right[i].Visible = false;
				}
			}

			if (Auto_Bullet[i].Visible)
			{
				Auto_Bullet[i].Bullet_Circle.position = Auto_Bullet[i].Position;
				PlusEffect_Creat(Auto_Bullet[i].Position.x, Auto_Bullet[i].Position.y, D3DCOLOR_RGBA(255, 192, 203, 255), 50, 1);

			}



		}
	}
} 



void Auto_Bullet_create(float x, float y)
{
	for (short i = 0; i < BULLET_MAX; i++)
	{
		if (!Auto_Bullet[i].Visible)
		{
			Auto_Bullet[i].Position.x = x;
			Auto_Bullet[i].Position.y = y;
			Auto_Bullet[i].Visible = true;
			break;
		}
	}
}

void Bullet_create(int type,float x, float y)
{
	for (short i = 0; i < BULLET_MAX; i++)
	{
		if (type == Middle)
		{
			if (!Bullet[i].Visible)
			{
				Bullet[i].Position.x = x;
				Bullet[i].Position.y = y;
				Bullet[i].Visible = true;
				break;
			}
		}
		if (type == Left)
		{
			if (!Bullet_Left[i].Visible)
			{
				Bullet_Left[i].Position.x = x;
				Bullet_Left[i].Position.y = y;
				Bullet_Left[i].Visible = true;
				break;
			}
		}
		if (type == Right)
		{
			if (!Bullet_Right[i].Visible)
			{
				Bullet_Right[i].Position.x = x;
				Bullet_Right[i].Position.y = y;
				Bullet_Right[i].Visible = true;
				break;
			}
		}
		if (type == Summoner_Left)
		{
			if (!Summoner_Bullet_Left[i].Visible)
			{
				Summoner_Bullet_Left[i].Position.x = x;
				Summoner_Bullet_Left[i].Position.y = y;
				Summoner_Bullet_Left[i].Visible = true;
				break;
			}
		}
		if (type == Summoner_Right)
		{
			if (!Summoner_Bullet_Right[i].Visible)
			{
				Summoner_Bullet_Right[i].Position.x = x;
				Summoner_Bullet_Right[i].Position.y = y;
				Summoner_Bullet_Right[i].Visible = true;
				break;
			}
		}
	}
}

void Bullet_Draw(void)
{
	if (Player_Iki())
	{
		for (short i = 0; i < BULLET_MAX; i++)
		{
			if (Bullet[i].Visible)
			{
				Draw_MiddleStandard(Texture.Tex[Player_Texture_Bullet], Bullet[i].Position.x, Bullet[i].Position.y, 0.3, 0.5);
				//Debug_DrawCircle(Bullet[i].Position.x, Bullet[i].Position.y, Bullet[i].Bullet_Circle.radius);
			}
			if (Bullet_Left[i].Visible && Bullet_Level > 0)
			{
				Draw_MiddleStandard(Texture.Tex[Player_Texture_Bullet], Bullet_Left[i].Position.x, Bullet_Left[i].Position.y, 0.3, 0.5, 255, D3DXToRadian(-15));
				//Debug_DrawCircle(Bullet_Left[i].Position.x, Bullet_Left[i].Position.y, Bullet_Left[i].Bullet_Circle.radius);
			}
			if (Bullet_Right[i].Visible && Bullet_Level > 1)
			{
				Draw_MiddleStandard(Texture.Tex[Player_Texture_Bullet], Bullet_Right[i].Position.x, Bullet_Right[i].Position.y, 0.3, 0.5, 255, D3DXToRadian(15));
				//Debug_DrawCircle(Bullet_Right[i].Position.x, Bullet_Right[i].Position.y, Bullet_Right[i].Bullet_Circle.radius);
			}

			if (Auto_Bullet[i].Visible)
			{
				//Debug_DrawCircle(Auto_Bullet[i].Position.x, Auto_Bullet[i].Position.y, Auto_Bullet[i].Bullet_Circle.radius);

			}
			if (Summoner_Bullet_Left[i].Visible)
			{
				if (Get_Bullet_Level() > 3)
				{
					Draw_MiddleStandard(Texture.Tex[Summoner_Texture_Bullet], Summoner_Bullet_Left[i].Position.x, Summoner_Bullet_Left[i].Position.y, 0.8, 1.5);
					//Debug_DrawCircle(Summoner_Bullet_Left[i].Position.x, Summoner_Bullet_Left[i].Position.y - 30, Summoner_Bullet_Left[i].Bullet_Circle.radius);

				}
			}

			if (Summoner_Bullet_Right[i].Visible)
			{
				if (Get_Bullet_Level() > 4)
				{
					Draw_MiddleStandard(Texture.Tex[Summoner_Texture_Bullet], Summoner_Bullet_Right[i].Position.x, Summoner_Bullet_Right[i].Position.y, 0.8, 1.5);
					//Debug_DrawCircle(Summoner_Bullet_Right[i].Position.x, Summoner_Bullet_Right[i].Position.y - 30, Summoner_Bullet_Right[i].Bullet_Circle.radius);

				}
			}
		}
	}
}

bullet Bullet_Info(int type,int index)
{
	if (type == Middle)
		return Bullet[index];

	if (type == Left)
		return Bullet_Left[index];

	if (type == Right)
		return Bullet_Right[index];

	if (type == Auto)
		return Auto_Bullet[index];

	if (type == Summoner_Left)
		return Summoner_Bullet_Left[index];

	if (type == Summoner_Right)
		return Summoner_Bullet_Right[index];
}
bool Bullet_IsUsed(int type,short index)
{
	if (type == Middle)
	return Bullet[index].Visible;

	if (type == Left)
		return Bullet_Left[index].Visible;

	if (type == Right)
		return Bullet_Right[index].Visible;

	if (type == Auto)
		return Auto_Bullet[index].Visible;

	if (type == Summoner_Left)
		return Summoner_Bullet_Left[index].Visible;

	if (type == Summoner_Right)
		return Summoner_Bullet_Right[index].Visible;
}
bool Auto_Bullet_IsUsed(short index)
{
	return Auto_Bullet[index].Visible;
}


void Bullet_Destroy(int type,short index)
{
	if (type == Middle)
	Bullet[index].Visible = false;

	if (type == Left)
		Bullet_Left[index].Visible = false;

	if (type == Right)
		Bullet_Right[index].Visible = false;

	if (type == Auto)
		Auto_Bullet[index].Visible = false;

	if (type == Summoner_Left)
		Summoner_Bullet_Left[index].Visible = false;

	if (type == Summoner_Right)
		Summoner_Bullet_Right[index].Visible = false;
}
void Auto_Bullet_Destroy(short index)
{
	Auto_Bullet[index].Visible = false;

}
int Bullet_LevelUp()
{
	return Bullet_Level += 1;
}
int Get_Bullet_Level()
{
	return Bullet_Level;
}
Circle_tag *Bullet_GetCollision(int type,short index)
{
	if (type == Middle)
		return &Bullet[index].Bullet_Circle;
	else if (type == Left)
		return &Bullet_Left[index].Bullet_Circle;
	else if (type == Right)
		return &Bullet_Right[index].Bullet_Circle;
	else if (type == Auto)
		return &Auto_Bullet[index].Bullet_Circle;
	else if (type == Summoner_Left)
		return &Summoner_Bullet_Left[index].Bullet_Circle;
	else if (type == Summoner_Right)
		return &Summoner_Bullet_Right[index].Bullet_Circle;
}





