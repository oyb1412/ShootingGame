#include <d3dx9.h>
#include "Collision.h"
#define PLAYER_HP 5

#pragma once
struct player
{
	bool Visible;
	int hp;
	D3DXVECTOR2 position;
	D3DCOLOR color;
	D3DXVECTOR2 uv;
	D3DXVECTOR2 size;
	Circle player_circle;
	float speed;
};
static player Player;
void player_Init(void);
void player_Update(void);
void player_Draw(void);
void player_Uninit(void);
int Player_HitPoint(void);
int Player_Hp_Init(int x);
int Player_Fade_Begin(void);
void Player_Destroy(void);
player Player_Info();
void Player_Reset(void);
Circle_tag* Player_GetCollision(void);
float Player_Position_Y(void);
void Player_Fade_Reset(void);
void Player_IsUsed(void);
float Player_Position_X(void);
bool Fade_Trigger(void);
bool Player_Iki();