#pragma once
enum
{
	ENEMY_BULLET_EFFECT,
	ENEMY_DISTORY_EFFECT,
	PLAYER_BULLET_EFFECT,
	PLAYER_AUTO_BULLET_EFFECT,
	PLAYER_DISTROY_EFFECT,
	ITEM_EFFECT,
	BOSS_DISTROY_EFFECT,
	ENEMY_5_EFFECT,
	FIRE_EFFECT,
	BOSS_SHOT_EFFECT,
	BOSS_SKILL_EFFECT,
};

void Boss_Skill_Effect_Create(float x, float y);
void Effect_Init(void);
void Effect_Update(void);
void Effect_Draw(void);
void Effect_create(int type,float x, float y);
void Effectdraw(int tex, float x, float y, float scaling, int speed, int RenderSpeed, int Widht, int Length);
void Sprite_Draw(int textureID, float x, float y, float size, float cut_x, float cut_y, float cut_w, float cut_h);
Circle_tag* Effect_GetCollision(short index);
bool Effect_IsUsed(int index);
void Effect_Dist(void);