#pragma once
#include "Collision.h"
enum
{
	ITEM,
	ITEM2,
	ITEM3
};
void Item_Init(void);
void Item_Update(void);
void Item_Draw(void);
void Item_create(int type,float x, float y);
Circle_tag* Item_GetCollision(int type,int index);
void Item_Destroy(int type,int index);
bool Item_IsUsed(int type,int index);
