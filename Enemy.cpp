#include "texture.h"
#include "mydirect3d.h"
#include "input.h"
#include <d3d9.h>
#include <tchar.h>
#include <d3dx9.h>
#include "Debug.h"
#include "sprite.h"
#include "debug_font.h"
#include "Collision.h"
#include "Fade.h"
#include "Number.h"
#include "EnemyGenerater.h"
#include "judgement.h"
#include "Enemy.h"
#include "sound.h"
#include "Number.h"
#include "Enemy_Bullet.h"
#include "Item.h"
#include <time.h>

#include "Effect.h"
#include "palyer.h"
#define ENEMY_BULLET_TIME 150
#define ENEMY_SPEED 2.0f
#define ENEMY_2_SPEED 2.0f
#define ENEMY_3_SPEED 2.0f
#define ENEMY_POSITION_INIT 0.0f
#define ENEMY_SIZE_X 350
#define ENEMY_SIZE_Y 300
#define ENEMY_2_SIZE_X 450
#define ENEMY_2_SIZE_Y 350
#define ENEMY_3_SIZE_X 800
#define ENEMY_3_SIZE_Y 800

#define ENEMY_RADIUS 0.17f
#define ENEMY_2_RADIUS 0.15f
#define ENEMY_3_RADIUS 0.13f
#define ENEMY_DESTROY_YP 1100.0f
#define ENEMY_DESTROY_XP 900.0f
#define ENEMY_3_DESTROY_YP 1100.0f
#define ENEMY_3_DESTROY_XP 1200.0f
#define ENEMY_DESTROY_XM -50.0f
#define ENEMY_2_DESTROY_YM 0.0f
#define ENEMY_HP 5
#define ENEMY_2_HP 23
#define ENEMY_3_HP 25
#define ENEMY_DEATH 5
#define TEX_MAX 5
static float Score = 0;
static int Boss_Count = 0;
static short Bullet_Time = 0;
static bool Boss_Skill = false;
static bool Effect_Trigger = false;
static int Skill_Level = 0;
void Enemy_Init(void)
{
	Score = 0;
	Boss_Count = 0;
	Bullet_Time = 0;
	Boss_Skill = false;
	Effect_Trigger = false;
	Skill_Level = 0;
	Number_Init();
	for (short i = 0; i < ENEMY_MAX; i++)
	{
		Enemy[i].Speed = 0;
		Enemy[i].Hp = ENEMY_HP;
		Enemy[i].Position.x = ENEMY_POSITION_INIT;
		Enemy[i].Position.y = ENEMY_POSITION_INIT;
		Enemy[i].Visible = false;
		Enemy[i].Size.x = ENEMY_SIZE_X;
		Enemy[i].Size.y = ENEMY_SIZE_Y;
		Enemy[i].Enemy_Circle.radius = Enemy[i].Size.x * ENEMY_RADIUS;
		Enemy[i].r = 0; 
		Enemy[i].Trigger = false;
		Enemy[i].Dis_Trigger = false;

		Enemy_2[i].Hp = ENEMY_2_HP;
		Enemy_2[i].Position.x = ENEMY_POSITION_INIT;
		Enemy_2[i].Position.y = ENEMY_POSITION_INIT;
		Enemy_2[i].Visible = false;
		Enemy_2[i].Size.x = ENEMY_SIZE_X;
		Enemy_2[i].Size.y = ENEMY_SIZE_Y;
		Enemy_2[i].Enemy_Circle.radius = Enemy_2[i].Size.x * ENEMY_RADIUS;
		Enemy_2[i].Trigger = false;

		Enemy_3[i].Hp = ENEMY_3_HP;
		Enemy_3[i].Position.x = ENEMY_POSITION_INIT;
		Enemy_3[i].Position.y = ENEMY_POSITION_INIT;
		Enemy_3[i].Visible = false;
		Enemy_3[i].Size.x = ENEMY_SIZE_X;
		Enemy_3[i].Size.y = ENEMY_SIZE_Y;
		Enemy_3[i].Enemy_Circle.radius = Enemy_3[i].Size.x * ENEMY_RADIUS;
		Enemy_3[i].Trigger = false;
		Enemy_3[i].Fade =0;

		Enemy_4[i].Hp = ENEMY_3_HP;
		Enemy_4[i].Position.x = ENEMY_POSITION_INIT;
		Enemy_4[i].Position.y = ENEMY_POSITION_INIT;
		Enemy_4[i].Visible = false;
		Enemy_4[i].Size.x = ENEMY_SIZE_X;
		Enemy_4[i].Size.y = ENEMY_SIZE_Y;
		Enemy_4[i].Enemy_Circle.radius = Enemy_4[i].Size.x * ENEMY_RADIUS;

		Enemy_5[i].Hp = ENEMY_3_HP;
		Enemy_5[i].Position.x = ENEMY_POSITION_INIT;
		Enemy_5[i].Position.y = ENEMY_POSITION_INIT;
		Enemy_5[i].Visible = false;
		Enemy_5[i].Size.x = ENEMY_SIZE_X;
		Enemy_5[i].Size.y = ENEMY_SIZE_Y;
		Enemy_5[i].Enemy_Circle.radius = Enemy_5[i].Size.x * ENEMY_RADIUS;

		Warning[i].Visible = false;
		Warning[i].Trigger = false;
		
	}
	Boss.Hp = 700;
	Boss.Position.x = ENEMY_POSITION_INIT;
	Boss.Position.y = ENEMY_POSITION_INIT;
	Boss.Visible = false;
	Boss.Size.x = ENEMY_SIZE_X;
	Boss.Size.y = ENEMY_SIZE_Y;
	Boss.Enemy_Circle.radius = Boss.Size.x * 1;
	Boss.Trigger = false;
	Boss.Move_Trigger = false;
}
void Enemy_Update(void)
{

	if (Player_Iki())
	{
		Bullet_Time++;

		if (Score > 0 && Boss.Hp > 0)
		{
			Score -= 0.01;
		}
		if (Boss.Visible)
		{
			if (!Boss.Trigger)
			{
				Effect_create(FIRE_EFFECT, 450, -50);
				Boss.Trigger = true;
			}

			Boss.Enemy_Circle.position.x = Boss.Position.x;
			Boss.Enemy_Circle.position.y = Boss.Position.y - 200;

			if (Boss.Hp <= 0)
			{
				StopSound();
				PlaySound(SOUND_LABEL_SE_BOSS_DISTROY);
				PlaySound(SOUND_LABER_VICTORYBGM);
				Effect_create(BOSS_DISTROY_EFFECT, Boss.Position.x, Boss.Position.y);
				Score += 500;
				Boss.Visible = false;
			}
			if (Boss.Position.y <= 100)
			{
				Boss.Position.y += 0.5f;
			}
			if (Boss.Position.y >= 100)
			{
				Boss_Count++;
				if (!Boss_Skill)
					Boss_Move();
				else
					Boss_Used_Skill(1);



			}
		}
		for (short i = 0; i < ENEMY_MAX; i++)
		{
			if (Player_Iki() == false)
			{
				Enemy[i].Hp = ENEMY_HP;

			}
			Enemy[i].Enemy_Circle.position = Enemy[i].Position;
			Enemy_2[i].Enemy_Circle.position = Enemy_2[i].Position;
			Enemy_3[i].Enemy_Circle.position = Enemy_3[i].Position;
			Enemy_4[i].Enemy_Circle.position = Enemy_4[i].Position;
			Enemy_5[i].Enemy_Circle.position = Enemy_5[i].Position;
			if (Warning[i].Visible && !Warning[i].Trigger)
			{
				Warning[i].Fade += 5;
			}
			if (Warning[i].Fade >= 200)
			{
				Warning[i].Trigger = true;
			}
			if (Warning[i].Trigger)
			{
				Warning[i].Fade -= 5;
			}
			if (Warning[i].Trigger && Warning[i].Fade <= 0)
			{
				Warning[i].Visible = false;
				Warning[i].Trigger = false;
			}
			if (!Enemy[i].Visible)
			{
				Enemy[i].Trigger = false;
			}
			if (Enemy[i].Visible)
			{
				
				if (Enemy[i].Hp <= 0 )
				{
					PlaySound(SOUND_LABEL_SE_ENEMY_DIS);
					Score += 10;
					Effect_create(ENEMY_DISTORY_EFFECT, Enemy[i].Position.x, Enemy[i].Position.y);
					Enemy[i].Visible = false;

				}
				if (Enemy[i].Position.y < 500 && !Enemy[i].Trigger)
					Enemy[i].Position.y += 2;

				if (Enemy[i].Position.y >= 500 && !Enemy[i].Trigger)
					Enemy[i].Trigger = true;

				if (Enemy[i].Trigger)
				{
					Enemy[i].Position.y -= 1.5;
				}
				if (Bullet_Time % 100 == 10 && Enemy[i].Position.x >= 50 && Enemy[i].Position.x <= 750 && Enemy[i].Position.y >= 190)
				{
					Enemy_Bullet_create(Enemy[i].Position.x, Enemy[i].Position.y + 25);
				}
			}
			if (!Enemy_2[i].Visible)
			{
				Enemy_2[i].Trigger = false;
			}
			if (Enemy_2[i].Visible)
			{
				if (Enemy_2[i].Hp <= 0)
				{
					PlaySound(SOUND_LABEL_SE_ENEMY_DIS);

					Score += 20;
					Enemy_2[i].Visible = false;
					Effect_create(ENEMY_DISTORY_EFFECT, Enemy_2[i].Position.x, Enemy_2[i].Position.y);

				}
				if (!Enemy_2[i].Trigger)
					Enemy_2[i].Position.y += 1;

				if (Enemy_2[i].Position.y >= 400)
					Enemy_2[i].Trigger = true;

				if (Enemy_2[i].Trigger && Enemy_2[i].Position.y >= 400)
				{
					if (Enemy_2[i].Position.x < SCREEN_WIDTH * 0.5)
						Enemy_2[i].Position.x -= 0.5;
					else
						Enemy_2[i].Position.x += 0.5;
				}

				if (Enemy_2[i].Position.x >= 50 && Enemy_2[i].Position.x <= 750 && Enemy_2[i].Position.y >= 190)
				{
					if (Bullet_Time % 200 == 10)
					{
						Enemy_Bullet_create(Enemy_2[i].Position.x, Enemy_2[i].Position.y + 25);
					}
					if (Bullet_Time % 200 == 20)
					{
						Enemy_Bullet_create(Enemy_2[i].Position.x, Enemy_2[i].Position.y + 25);
					}
				}
			}
			if (Enemy_3[i].Visible)
			{
				if (Enemy_3[i].Hp <= 0)
				{
					PlaySound(SOUND_LABEL_SE_ENEMY_DIS);

					Score += 30;
					Enemy_3[i].Visible = false;
					Effect_create(ENEMY_DISTORY_EFFECT, Enemy_3[i].Position.x, Enemy_3[i].Position.y);

				}
				Enemy_3[i].Fade++;
				if (Enemy_3[i].Fade >= 300)
					Enemy_3[i].Fade = 0;


				if (Bullet_Time % 300 == 10)
				{
					Enemy_Bullet_create(Enemy_3[i].Position.x, Enemy_3[i].Position.y + 25);
				}
				if (Bullet_Time % 300 == 20)
				{
					Enemy_Bullet_create(Enemy_3[i].Position.x, Enemy_3[i].Position.y + 25);
				}
				if (Bullet_Time % 300 == 30)
				{
					Enemy_Bullet_create(Enemy_3[i].Position.x, Enemy_3[i].Position.y + 25);
				}
			}
			if (Enemy_4[i].Visible)
			{
				if (Enemy_4[i].Hp <= 0)
				{
					PlaySound(SOUND_LABEL_SE_ENEMY_DIS);

					Score += 40;
					Enemy_4[i].Visible = false;
					Effect_create(ENEMY_DISTORY_EFFECT, Enemy_4[i].Position.x, Enemy_4[i].Position.y);

				}
				if (Enemy_4[i].Position.y < 700)
				{
					if (Player_Info().position.x > Enemy_4[i].Position.x)
						Enemy_4[i].Position.x += 2;
					else
						Enemy_4[i].Position.x -= 2;
				}

				Enemy_4[i].Position.y += 4;
			}
			if (Enemy_5[i].Visible)
			{

				if (Enemy_5[i].Hp <= 0)
				{
					PlaySound(SOUND_LABEL_SE_ENEMY_DIS);

					Score += 50;
					Enemy_5[i].Visible = false;
					Effect_create(ENEMY_DISTORY_EFFECT, Enemy_5[i].Position.x, Enemy_5[i].Position.y);

				}
				Enemy_5[i].Position.y += 1.5;
				if (Bullet_Time % 100 == 10)
				{
					PlaySound(SOUND_LABEL_SE_EXPLOSION);

					Effect_create(ENEMY_5_EFFECT, Enemy_5[i].Position.x, Enemy_5[i].Position.y + 25);
				}
			}
		}
	}
}
void Enemy_create(int type,float x, float y)
{
	if (type == BOSS)
	{
		if (!Boss.Visible)
		{
			Boss.Position.x = x;
			Boss.Position.y = y;
			Boss.Visible = true;
		}
	}
	for (short i = 0; i < ENEMY_MAX; i++)
	{
		if (type == 1)
		{
			if (!Enemy[i].Visible)
			{
				Enemy[i].Position.x = x;
				Enemy[i].Position.y = y;
				Enemy[i].Hp = 6;
				Enemy[i].Visible = true;
				break;
			}
		}
		if (type == 2)
		{
			if (!Enemy_2[i].Visible)
			{
				Enemy_2[i].Position.x = x;
				Enemy_2[i].Position.y = y;
				Enemy_2[i].Hp =15;

				Enemy_2[i].Visible = true;
				break;
			}
		}
		if (type == 3)
		{
			if (!Enemy_3[i].Visible)
			{
				Enemy_3[i].Position.x = x;
				Enemy_3[i].Position.y = y;
				Enemy_3[i].Hp = 20;

				Enemy_3[i].Visible = true;
				break;
			}
		}
		if (type == 4)
		{
			if (!Enemy_4[i].Visible)
			{
				Enemy_4[i].Position.x = x;
				Enemy_4[i].Position.y = y;
				Enemy_4[i].Hp = 20;

				Enemy_4[i].Visible = true;
				break;
			}
		}
		if (type == 5)
		{
			if (!Enemy_5[i].Visible)
			{
				Enemy_5[i].Position.x = x;
				Enemy_5[i].Position.y = y;
				Enemy_5[i].Hp = 30;

				Enemy_5[i].Visible = true;
				break;
			}
		}
	
	
	}
}





void Enemy_Draw(void)
{
	if (Boss.Visible)
	{
		Draw_MiddleStandard(Texture.Tex[Enemy_Boss_Texture], Boss.Position.x, Boss.Position.y, 1, 1);
		//Debug_DrawCircle(Boss.Position.x, Boss.Position.y-200, Boss.Enemy_Circle.radius);

	}
	for (short i = 0; i < ENEMY_MAX; i++)
	{
		if (Enemy[i].Visible)
		{
			Draw_MiddleStandard(Texture.Tex[Enemy_Texture_1], Enemy[i].Position.x, Enemy[i].Position.y, 0.9, 0.9);
			//Debug_DrawCircle(Enemy[i].Position.x,Enemy[i].Position.y, Enemy[i].Enemy_Circle.radius);
		}
		if (Enemy_2[i].Visible)
		{
			Draw_MiddleStandard(Texture.Tex[Enemy_Texture_2], Enemy_2[i].Position.x, Enemy_2[i].Position.y, 0.9, 0.9);
			//Debug_DrawCircle(Enemy_2[i].Position.x , Enemy_2[i].Position.y, Enemy_2[i].Enemy_Circle.radius);
		}
		if (Enemy_3[i].Visible)
		{
			Draw_MiddleStandard(Texture.Tex[Enemy_Texture_3], Enemy_3[i].Position.x, Enemy_3[i].Position.y, 1,1,Enemy_3[i].Fade);
			//Debug_DrawCircle(Enemy_3[i].Position.x, Enemy_3[i].Position.y , Enemy_3[i].Enemy_Circle.radius);
		}
		if (Enemy_4[i].Visible)
		{
			Draw_MiddleStandard(Texture.Tex[Enemy_Texture_4], Enemy_4[i].Position.x, Enemy_4[i].Position.y, 1.2, 1.2);
			//Debug_DrawCircle(Enemy_4[i].Position.x, Enemy_4[i].Position.y , Enemy_4[i].Enemy_Circle.radius);
		}
		if (Enemy_5[i].Visible)
		{
			//Number_Draw(Enemy_5[0].Hp, 630, 30, 80);

			Draw_MiddleStandard(Texture.Tex[Enemy_Texture_5], Enemy_5[i].Position.x, Enemy_5[i].Position.y, 1.3, 1.3);
			//Debug_DrawCircle(Enemy_5[i].Position.x, Enemy_5[i].Position.y , Enemy_5[i].Enemy_Circle.radius);
		}
		if (Warning[i].Visible)
		{
			Draw_MiddleStandard(Texture.Tex[Red_Texture], Warning[i].Position.x, Warning[i].Position.y, 1, 0.11, Warning[i].Fade);
		}
	}
}
bool Enemy_IsUsed(int type,int index)
{
	if(type == ENEMY)
	return Enemy[index].Visible;

	if (type == ENEMY2)
		return Enemy_2[index].Visible;

	if (type == ENEMY3)
		return Enemy_3[index].Visible;

	if (type == ENEMY4)
		return Enemy_4[index].Visible;

	if (type == ENEMY5)
		return Enemy_5[index].Visible;
}
bool Boss_IsUsed()
{
	return Boss.Visible;
}



Circle_tag* Enemy_GetCollision(int type,short index)
{
	if(type ==ENEMY)
	return &Enemy[index].Enemy_Circle;

	if(type ==ENEMY2)
	return &Enemy_2[index].Enemy_Circle;

	if (type == ENEMY3)
	return &Enemy_3[index].Enemy_Circle;

	if (type == ENEMY4)
	return &Enemy_4[index].Enemy_Circle;

	if (type == ENEMY5)
	return &Enemy_5[index].Enemy_Circle;
}
Circle_tag* Boss_GetCollision()
{
	return &Boss.Enemy_Circle;
}



int Enemy_HitPoint(int type,short index,int Quantity)
{
	if (type == ENEMY)
		return Enemy[index].Hp+= Quantity;

	if (type == ENEMY2)
		return Enemy_2[index].Hp += Quantity;

	if (type == ENEMY3)
		return Enemy_3[index].Hp += Quantity;

	if (type == ENEMY4)
		return Enemy_4[index].Hp += Quantity;

	if (type == ENEMY5)
		return Enemy_5[index].Hp += Quantity;
}
int Boss_HitPoint(int Quantity)
{
	return Boss.Hp += Quantity;
}
enemy Boss_Info()
{
	return Boss;
}
enemy Enemy_Info(int type,int index)
{	if(type == ENEMY)
	return Enemy[index];

if (type == ENEMY2)
return Enemy_2[index];

if (type == ENEMY3)
return Enemy_3[index];

if (type == ENEMY4)
return Enemy_4[index];

if (type == ENEMY5)
return Enemy_5[index];
}
float Get_Score(void)
{
	return Score;
} 

void Boss_Move()
{
	if (Boss.Visible)
	{
		if (!Boss.Move_Trigger)
		{
			Boss.Position.x += 2;
		}
		if (Boss.Position.x >= 600 && !Boss.Move_Trigger)
		{
			Boss.Move_Trigger = true;
		}
		if (Boss.Move_Trigger)
		{
			Boss.Position.x -= 2;
		}
		if (Boss.Position.x <= 200 && Boss.Move_Trigger)
		{
			Boss.Move_Trigger = false;
		}
		if (Boss_Count % 100 == 10)
		{
			if (!Effect_Trigger)
			{
				Effect_create(BOSS_SHOT_EFFECT, Boss.Position.x, Boss.Position.y);
				Effect_Trigger = true;
			}
			PlaySound(SOUND_LABEL_SE_BOSS_BULLET);
			Boss_Bullet_Create(Boss.Position.x, Boss.Position.y + 50);
		}
		if (Boss_Count % 100 == 15)
		{
			PlaySound(SOUND_LABEL_SE_BOSS_BULLET);

			Boss_Bullet_Create(Boss.Position.x, Boss.Position.y + 50);
		}
		if (Boss_Count % 100 == 20)
		{
			PlaySound(SOUND_LABEL_SE_BOSS_BULLET);

			Boss_Bullet_Create(Boss.Position.x, Boss.Position.y + 50);
		}

		if (Boss_Count % 100 == 50)
		{
			PlaySound(SOUND_LABEL_SE_BOSS_BULLET);

			Boss_Bullet_Create(Boss.Position.x, Boss.Position.y + 50);
		}
		if (Boss_Count % 100 == 55)
		{
			PlaySound(SOUND_LABEL_SE_BOSS_BULLET);

			Boss_Bullet_Create(Boss.Position.x, Boss.Position.y + 50);
		}
		if (Boss_Count % 100 == 60)
		{
			PlaySound(SOUND_LABEL_SE_BOSS_BULLET);

			Boss_Bullet_Create(Boss.Position.x, Boss.Position.y + 50);
		}
		if (Boss_Count % 1000 == 200)
		{
			Warning_Create(400, 950);
		}
		if (Boss_Count % 1000 == 350)
		{
			PlaySound(SOUND_LABEL_SE_BOSS_SKILL);

			Effect_create(ENEMY_5_EFFECT, 100, 950);
			Effect_create(ENEMY_5_EFFECT, 300, 950);
			Effect_create(ENEMY_5_EFFECT, 500, 950);
			Effect_create(ENEMY_5_EFFECT, 700, 950);
			Boss_Skill_Effect_Create(SCREEN_WIDTH * 0.5, 950);


		}
		if (Boss_Count % 1000 == 500)
		{
			Warning_Create(400, 600);
		}
		if (Boss_Count % 1000 == 650)
		{
			PlaySound(SOUND_LABEL_SE_BOSS_SKILL);

			Effect_create(ENEMY_5_EFFECT, 100, 600);
			Effect_create(ENEMY_5_EFFECT, 300, 600);
			Effect_create(ENEMY_5_EFFECT, 500, 600);
			Effect_create(ENEMY_5_EFFECT, 700, 600);
			Boss_Skill_Effect_Create(SCREEN_WIDTH * 0.5, 600);

		}
		if (Boss_Count % 1000 == 850)
		{
			Warning_Create(400, 300);
		}
		if (Boss_Count % 1000 == 999)
		{
			PlaySound(SOUND_LABEL_SE_BOSS_SKILL);

			Effect_create(ENEMY_5_EFFECT, 100, 300);
			Effect_create(ENEMY_5_EFFECT, 300, 300);
			Effect_create(ENEMY_5_EFFECT, 500, 300);
			Effect_create(ENEMY_5_EFFECT, 700, 300);
			Boss_Skill_Effect_Create(SCREEN_WIDTH * 0.5, 300);

		}
		if (Boss_Count % 2000 == 1500)
		{
			Warning_Create(400, 950);
			Warning_Create(400, 600);
			Warning_Create(400, 300);
		}
		if (Boss_Count % 2000 == 1650)
		{
			PlaySound(SOUND_LABEL_SE_BOSS_SKILL);

			Effect_create(ENEMY_5_EFFECT, 100, 950);
			Effect_create(ENEMY_5_EFFECT, 300, 950);
			Effect_create(ENEMY_5_EFFECT, 500, 950);
			Effect_create(ENEMY_5_EFFECT, 700, 950);
			Effect_create(ENEMY_5_EFFECT, 100, 600);
			Effect_create(ENEMY_5_EFFECT, 300, 600);
			Effect_create(ENEMY_5_EFFECT, 500, 600);
			Effect_create(ENEMY_5_EFFECT, 700, 600);
			Effect_create(ENEMY_5_EFFECT, 100, 300);
			Effect_create(ENEMY_5_EFFECT, 300, 300);
			Effect_create(ENEMY_5_EFFECT, 500, 300);
			Effect_create(ENEMY_5_EFFECT, 700, 300);
			Boss_Skill_Effect_Create(SCREEN_WIDTH * 0.5, 950);
			Boss_Skill_Effect_Create(SCREEN_WIDTH * 0.5, 600);
			Boss_Skill_Effect_Create(SCREEN_WIDTH * 0.5, 300);

		}
	}
}
void Warning_Create(float x, float y)
{
	for (int i = 0; i < 100; i++)
	{
		if (!Warning[i].Visible)
		{
			Warning[i].Position.x = x;
			Warning[i].Position.y = y;
			Warning[i].Fade = 0;
			Warning[i].Visible = true;
			break;
		}
	}
}
void Boss_Used_Skill(int pattarn)
{
	if (pattarn == 1)
	{
		++Skill_Level;

		switch (Skill_Level)
		{
		case 1:
			Warning_Create(400, 950);
			Warning_Create(400, 750);
			Warning_Create(400, 550);
			Warning_Create(400, 350);
			break;
		case 150:
			
		
				Effect_create(ENEMY_5_EFFECT, 100, 950);
				Effect_create(ENEMY_5_EFFECT, 300, 950);
				Effect_create(ENEMY_5_EFFECT, 500, 950);
				Effect_create(ENEMY_5_EFFECT, 700, 950);

				Effect_create(ENEMY_5_EFFECT, 100, 650);
				Effect_create(ENEMY_5_EFFECT, 300, 650);
				Effect_create(ENEMY_5_EFFECT, 500, 650);
				Effect_create(ENEMY_5_EFFECT, 700, 650);
			break;



		default:
			break;
		}

	}
}