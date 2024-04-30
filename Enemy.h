#pragma once
#include "Collision.h"
#define ENEMY_MAX 100
enum
{
	ENEMY,
	ENEMY2,
	ENEMY3,
	ENEMY4,
	ENEMY5,
	ENEMY6,
	BOSS,
};
struct warning
{
	D3DXVECTOR2 Position;
	bool Visible;
	int Fade;
	bool Trigger;
};
struct enemy
{
	BOOL Trigger;
	short Speed;
	int Hp;
	short Bullet_Time;
	int Fade;
	BOOL Visible;
	D3DXVECTOR2 Position;
	D3DXVECTOR2 Size;
	D3DXVECTOR2 Enemy_Move;
	Circle Enemy_Circle;
	bool Move_Trigger;
	bool Dis_Trigger;
	float r;
};
static enemy Enemy[ENEMY_MAX];
static enemy Enemy_2[ENEMY_MAX];
static enemy Enemy_3[ENEMY_MAX];
static enemy Enemy_4[ENEMY_MAX];
static enemy Enemy_5[ENEMY_MAX];
static enemy Boss;
static warning Warning[100];
void Boss_Move();
void Enemy_Init(void);
enemy Boss_Info();
void Enemy_Update(void);
void Enemy_Draw(void);
void Enemy_create(int type, float x, float y);
bool Enemy_IsUsed(int type,int index);
void Boss_Used_Skill(int pattarn);


Circle_tag *Enemy_GetCollision(int type,short index);
int Enemy_HitPoint(int type, short index, int Quantity = -1);
float Get_Score(void);
void Warning_Create(float x, float y);
enemy Enemy_Info(int type, int index);
int Boss_HitPoint(int Quantity);
Circle_tag* Boss_GetCollision();
bool Boss_IsUsed();





