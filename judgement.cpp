#include "Enemy.h"
#include "Bullet.h"
#include "Collision.h"
#include "judgement.h"
#include "palyer.h"
#include "Item.h"
#include "sound.h"
#include "Enemy_Bullet.h"
#include "Effect.h"
#include "Number.h"
#define INDEX_MAX 100
#define ITEM_INDEX_MAX 5
#define ZEROTENGO 0.5f





static int Attacked = 121;
static int Bullet_Plus=0;
static float Score = 0;
void judgement_Init(void)
{
	Attacked = 121; 
	Bullet_Plus = 0;
	Score = 0;
}
void judgement_update(void)
{
	for (int index = 0; index < 5; index++)
	{
		if (Item_IsUsed(ITEM,index))
		{
			if (Circle_circle(Player_GetCollision(), Item_GetCollision(ITEM,index)))
			{
				PlaySound(SOUND_LABEL_SE_ITEM);
				Item_Destroy(ITEM, index);
				Bullet_LevelUp();
				Effect_create(ITEM_EFFECT, Player_Info().position.x, Player_Info().position.y);
			}
		}
		if (Effect_IsUsed(index))
		{
			if (Circle_circle(Player_GetCollision(), Effect_GetCollision(index)) && Fade_Trigger())
			{
				Player_HitPoint();
				Player_Fade_Begin();
			}
		}
	}
	for (int index = 0; index < INDEX_MAX; index++)
	{
		for (int index1 = 0; index1 < 3; index1++)
		{
			if (Boss_Bullet_IsUsed(index1, index))
			{
				if (Circle_circle(Player_GetCollision(), Boss_Bullet_GetCollision(index1, index)) && Fade_Trigger())
				{
					Player_HitPoint();
					Boss_Bullet_Distroy(index1, index);
					Effect_create(ENEMY_BULLET_EFFECT, (Player_Info().position.x + Boss_Bullet_Info(index1,index).Position.x) * 0.5, (Player_Info().position.y + Boss_Bullet_Info(index1,index).Position.y) * 0.5);
					Player_Fade_Begin();
				}
			}
		}
		if (Enemy_Bullet_IsUsed(index))
		{
			if (Circle_circle(Player_GetCollision(), Enemy_Bullet_GetCollision(index)) && Fade_Trigger())
			{
				Player_HitPoint();
				Enemy_Bullet_Destroy(index);
				Effect_create(ENEMY_BULLET_EFFECT,(Player_Info().position.x+ Enemy_Bullet_Info(index).Position.x) * 0.5, (Player_Info().position.y+Enemy_Bullet_Info(index).Position.y)*0.5);
				Player_Fade_Begin();
			}
		}
		for (int index1 = 0; index1 < 5; index1++)
		{
			if (Enemy_IsUsed(index1, index))
			{
				if (Circle_circle(Player_GetCollision(), Enemy_GetCollision(index1, index)) && Fade_Trigger())
				{
					Player_HitPoint();
					Player_Fade_Begin();
					Effect_create(ENEMY_BULLET_EFFECT, (Player_Info().position.x + Enemy_Info(index1,index).Position.x) * 0.5, (Player_Info().position.y + Enemy_Info(index1,index).Position.y) * 0.5);
				}
			}
		}
	}
	for (int index = 0; index < INDEX_MAX; index++)
	{
		if (Bullet_IsUsed(Auto, index))
		{
			if (Boss_IsUsed())
			{
				if (Circle_circle(Bullet_GetCollision(Auto, index), Boss_GetCollision()))
				{
					Bullet_Destroy(Auto, index);
					Boss_HitPoint(-1);
					Effect_create(PLAYER_AUTO_BULLET_EFFECT, (Bullet_Info(Auto, index).Position.x + Boss_Info().Position.x) * 0.5, (Bullet_Info(Auto, index).Position.y + Boss_Info().Position.y) * 0.5);
				}
			}
			for (int index1 = 0; index1 < INDEX_MAX; index1++)
			{
				for (int index2 = 0; index2 < 5; index2++)
				{
					if (Enemy_IsUsed(index2, index1))
					{
						if (Circle_circle(Bullet_GetCollision(Auto, index), Enemy_GetCollision(index2, index1)))
						{
							Bullet_Destroy(Auto, index);
							Enemy_HitPoint(index2, index1,-5);
							Effect_create(PLAYER_AUTO_BULLET_EFFECT, (Bullet_Info(Auto, index).Position.x+Enemy_Info(index2,index1).Position.x )* 0.5, (Bullet_Info(Auto, index).Position.y+Enemy_Info(index2,index1).Position.y) * 0.5);

						}
					}
				}
			}
		}
	}
	if (Get_Bullet_Level() > 3)
	{
		for (int index = 0; index < INDEX_MAX; index++)
		{
			if (Bullet_IsUsed(Summoner_Left, index))
			{
				if (Boss_IsUsed())
				{
					if (Circle_circle(Bullet_GetCollision(Summoner_Left, index), Boss_GetCollision()))
					{
						Bullet_Destroy(Summoner_Left, index);
						Boss_HitPoint(-2);
						Effect_create(PLAYER_AUTO_BULLET_EFFECT, (Bullet_Info(Summoner_Left, index).Position.x + Boss_Info().Position.x) * 0.5, (Bullet_Info(Summoner_Left, index).Position.y + Boss_Info().Position.y) * 0.5);
					}
				}


				for (int index1 = 0; index1 < INDEX_MAX; index1++)
				{
					for (int index2 = 0; index2 < 5; index2++)
					{
						if (Enemy_IsUsed(index2, index1))
						{
							if (Circle_circle(Bullet_GetCollision(Summoner_Left, index), Enemy_GetCollision(index2, index1)))
							{
								Bullet_Destroy(Summoner_Left, index);
								Enemy_HitPoint(index2, index1, -2);
								Effect_create(PLAYER_AUTO_BULLET_EFFECT, (Bullet_Info(Summoner_Left, index).Position.x + Enemy_Info(index2, index1).Position.x) * 0.5, (Bullet_Info(Summoner_Left, index).Position.y + Enemy_Info(index2, index1).Position.y )* 0.5);
							}
						}
					}
				}
			}
		}
	}
	if (Get_Bullet_Level() > 4)
	{
		for (int index = 0; index < INDEX_MAX; index++)
		{
			if (Bullet_IsUsed(Summoner_Right, index))
			{
				if (Boss_IsUsed())
				{
					if (Circle_circle(Bullet_GetCollision(Summoner_Right, index), Boss_GetCollision()))
					{
						Bullet_Destroy(Summoner_Right, index);
						Boss_HitPoint(-2);
						Effect_create(PLAYER_AUTO_BULLET_EFFECT, (Bullet_Info(Summoner_Right, index).Position.x + Boss_Info().Position.x) * 0.5, (Bullet_Info(Summoner_Right, index).Position.y + Boss_Info().Position.y) * 0.5);
					}
				}
				for (int index1 = 0; index1 < INDEX_MAX; index1++)
				{
					for (int index2 = 0; index2 < 5; index2++)
					{
						if (Enemy_IsUsed(index2, index1))
						{
							if (Circle_circle(Bullet_GetCollision(Summoner_Right, index), Enemy_GetCollision(index2, index1)))
							{
								Bullet_Destroy(Summoner_Right, index);
								Enemy_HitPoint(index2, index1, -2);
								Effect_create(PLAYER_AUTO_BULLET_EFFECT, (Bullet_Info(Summoner_Right, index).Position.x+Enemy_Info(index2, index1).Position.x )* 0.5, (Bullet_Info(Summoner_Right, index).Position.y + Enemy_Info(index2, index1).Position.y) * 0.5);

							}
						}
					}
				}
			}
		}
	}

	for (int index = 0; index < INDEX_MAX; index++)
	{
		if (Bullet_IsUsed(Middle, index))
		{
			if (Boss_IsUsed())
			{
				if (Circle_circle(Bullet_GetCollision(Middle, index), Boss_GetCollision()))
				{
					Bullet_Destroy(Middle, index);
					Boss_HitPoint(-1);
					Effect_create(PLAYER_BULLET_EFFECT, (Bullet_Info(Middle, index).Position.x + Boss_Info().Position.x) * 0.5, (Bullet_Info(Middle, index).Position.y + Boss_Info().Position.y) * 0.5);
				}
			}
			for (int index1 = 0; index1 < INDEX_MAX; index1++)
			{
				for (int index2 = 0; index2 < 5; index2++)
				{
					if (Enemy_IsUsed(index2, index1))
					{
						if (Circle_circle(Bullet_GetCollision(Middle, index), Enemy_GetCollision(index2, index1)))
						{
							Bullet_Destroy(Middle, index);
							Enemy_HitPoint(index2, index1);
							Effect_create(PLAYER_BULLET_EFFECT, (Bullet_Info(Middle,index).Position.x + Enemy_Info(index2, index1).Position.x) * 0.5, (Bullet_Info(Middle, index).Position.y + Enemy_Info(index2, index1).Position.y) * 0.5);
						}

						
					}
				}
			}
		}
	}
	for (int index = 0; index < INDEX_MAX; index++)
	{
		if (Bullet_IsUsed(Left, index))
		{
			if (Boss_IsUsed())
			{
				if (Circle_circle(Bullet_GetCollision(Left, index), Boss_GetCollision()))
				{
					Bullet_Destroy(Left, index);
					Boss_HitPoint(-1);
					Effect_create(PLAYER_BULLET_EFFECT, (Bullet_Info(Left, index).Position.x + Boss_Info().Position.x) * 0.5, (Bullet_Info(Left, index).Position.y + Boss_Info().Position.y) * 0.5);
				}
			}
			for (int index1 = 0; index1 < INDEX_MAX; index1++)
			{
				for (int index2 = 0; index2 < 5; index2++)
				{
					if (Enemy_IsUsed(index2, index1))
					{
						if (Circle_circle(Bullet_GetCollision(Left, index), Enemy_GetCollision(index2, index1)))
						{
							Bullet_Destroy(Left, index);
							Enemy_HitPoint(index2, index1);
							Effect_create(PLAYER_BULLET_EFFECT, (Bullet_Info(Left, index).Position.x + Enemy_Info(index2, index1).Position.x) * 0.5, (Bullet_Info(Left, index).Position.y + Enemy_Info(index2, index1).Position.y) * 0.5);

						}
						
					}
				}
			}
		}
	}
	for (int index = 0; index < INDEX_MAX; index++)
	{
		if (Bullet_IsUsed(Right, index))
		{
			if (Boss_IsUsed())
			{
				if (Circle_circle(Bullet_GetCollision(Right, index), Boss_GetCollision()))
				{
					Bullet_Destroy(Right, index);
					Boss_HitPoint(-1);
					Effect_create(PLAYER_BULLET_EFFECT, (Bullet_Info(Right, index).Position.x + Boss_Info().Position.x) * 0.5, (Bullet_Info(Right, index).Position.y + Boss_Info().Position.y) * 0.5);
				}
			}
			for (int index1 = 0; index1 < INDEX_MAX; index1++)
			{
				for (int index2 = 0; index2 < 5; index2++)
				{
					if (Enemy_IsUsed(index2, index1))
					{
						if (Circle_circle(Bullet_GetCollision(Right, index), Enemy_GetCollision(index2, index1)))
						{
							Bullet_Destroy(Right, index);
							Enemy_HitPoint(index2, index1);
							Effect_create(PLAYER_BULLET_EFFECT, (Bullet_Info(Right, index).Position.x + Enemy_Info(index2, index1).Position.x) * 0.5, (Bullet_Info(Right, index).Position.y + Enemy_Info(index2, index1).Position.y) * 0.5);

						}
						
					}
				}
			}
		}
		
	}
}
