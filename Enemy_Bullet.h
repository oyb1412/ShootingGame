#pragma once
#include "Collision.h"
#define ENEMY_BULLET_MAX 100

struct enemy_bullet
{
	BOOL Visible;
	D3DXVECTOR2 Position;
	Circle Bullet_Circle;
	D3DXVECTOR2 Size;
	D3DXVECTOR2 Bullet_Move;
};
static enemy_bullet Enemy_Bullet[ENEMY_BULLET_MAX];
static enemy_bullet Boss_Bullet_Left[ENEMY_BULLET_MAX];
static enemy_bullet Boss_Bullet_Middle[ENEMY_BULLET_MAX];
static enemy_bullet Boss_Bullet_Right[ENEMY_BULLET_MAX];
void Enemy_Bullet_Init(void);
void Enemy_Bullet_Update(void);
void Boss_Bullet_Create(float x, float y);
void Enemy_Bullet_Draw(void);
void Enemy_Bullet_create(float x, float y);
bool Enemy_Bullet_IsUsed(int index);
int Enemy_Bullet_Destroy(int index);
Circle_tag* Enemy_Bullet_GetCollision(int index);
enemy_bullet Enemy_Bullet_Info(int index);
Circle_tag* Boss_Bullet_GetCollision(int type, int index);
enemy_bullet Boss_Bullet_Info(int type, int index);
bool Boss_Bullet_Distroy(int type, int index);
bool Boss_Bullet_IsUsed(int type, int index);