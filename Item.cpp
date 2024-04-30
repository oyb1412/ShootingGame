#include "texture.h"
#include "mydirect3d.h"
#include "input.h"
#include <d3d9.h>
#include <tchar.h>
#include <d3dx9.h>
#include "sprite.h"
#include "Collision.h"
#include "Debug.h"
#include "Item.h"
#define ITEM_POSITION_INIT 0
#define ITEM_MAX 5
#define ITEM_SIZE_X 200
#define ITEM_SIZE_Y 200
#define ITEM_RADIUS 0.2f
#define ITEM_SPEED_X 6
#define ITEM_SPEED_Y 6
#define TEX_MAX 5
#define ITEM_WAY 0
#define POSITION_Y_MAX 1000
static int Tex[TEX_MAX];


struct item
{
	BOOL Visible;
	D3DXVECTOR2 Position;
	D3DXVECTOR2 Size;
	Circle Item_Circle;
};
static item Item[ITEM_MAX];
static item Item_2[ITEM_MAX];
static item Item_3[ITEM_MAX];

void Item_Init(void)
{
	for (int i = 0; i < ITEM_MAX; i++)
	{
		Item[i].Position.x = ITEM_POSITION_INIT;
		Item[i].Position.y = ITEM_POSITION_INIT;
		Item[i].Visible = false;
		Item[i].Size.x = ITEM_SIZE_X;
		Item[i].Size.y = ITEM_SIZE_Y;
		Item[i].Item_Circle.radius = Item[i].Size.x * ITEM_RADIUS;

		Item_2[i].Position.x = ITEM_POSITION_INIT;
		Item_2[i].Position.y = ITEM_POSITION_INIT;
		Item_2[i].Visible = false;
		Item_2[i].Size.x = ITEM_SIZE_X;
		Item_2[i].Size.y = ITEM_SIZE_Y;
		Item_2[i].Item_Circle.radius = Item_2[i].Size.x * ITEM_RADIUS;

		Item_3[i].Position.x = ITEM_POSITION_INIT;
		Item_3[i].Position.y = ITEM_POSITION_INIT;
		Item_3[i].Visible = false;
		Item_3[i].Size.x = ITEM_SIZE_X;
		Item_3[i].Size.y = ITEM_SIZE_Y;
	}
}
void Item_Update(void)
{

	for (int i = 0; i < ITEM_MAX; i++)
	{

		if (Item[i].Visible)
		{
			Item[i].Position.y += 2;
			Item[i].Item_Circle.position = Item[i].Position;

		}
		
	}
}
void Item_Draw(void)
{
	for (int i = 0; i < ITEM_MAX; i++)
	{
		if (Item[i].Visible)
		{
			Draw_MiddleStandard(Texture.Tex[Item_Texture], Item[i].Position.x, Item[i].Position.y, 0.5,0.5);
			//Debug_DrawCircle(Item[i].Position.x, Item[i].Position.y, Item[i].Item_Circle.radius);
		}
	}
}
void Item_create(int type,float x, float y)
{
	for (int i = 0; i < ITEM_MAX; i++)
	{
		if (type == ITEM)
		{
			if (!Item[i].Visible)
			{
				Item[i].Position.x = x;
				Item[i].Position.y = y;
				Item[i].Visible = true;
				break;
			}
		}
	}
}


bool Item_IsUsed(int type,int index)
{
	if (type == ITEM)
	return Item[index].Visible;
}

void Item_Destroy(int type,int index)
{
	if (type == ITEM)
	Item[index].Visible = false;
}

Circle_tag* Item_GetCollision(int type,int index)
{
	if (type == ITEM)
	return &Item[index].Item_Circle;
}

