#pragma once
#include "Collision.h"
#define BULLET_LEFT_ISUSED 1
#define BULLET_RIGHT_ISUSED 2
#define AUTO_BULLET_ISUSED 0
#define BULLET_MAX 100

enum
{
	Middle,
	Left,
	Right,
	Auto,
	Summoner_Left,
	Summoner_Right,
};
struct bullet
{
	BOOL Visible;
	D3DXVECTOR2 Position;
	Circle Bullet_Circle;
	D3DXVECTOR2 Size;
};
static bullet Bullet[BULLET_MAX];
static bullet Bullet_Left[BULLET_MAX];
static bullet Bullet_Right[BULLET_MAX];
static bullet Auto_Bullet[BULLET_MAX];
static bullet Summoner_Bullet_Left[BULLET_MAX];
static bullet Summoner_Bullet_Right[BULLET_MAX];

void Bullet_Init(void);
void Bullet_Update(void);
void Bullet_Draw(void);
int Bullet_LevelUp();
void Bullet_create(int type,float x, float y);
bool Bullet_IsUsed(int type,short index);
void Bullet_Destroy(int type,short index);
Circle_tag* Bullet_GetCollision(int type,short index);
bullet Bullet_Info(int type, int index);
void Auto_Bullet_create(float x, float y);
bool Auto_Bullet_IsUsed(short index);
void Auto_Bullet_Destroy(short index);
int Get_Bullet_Level();