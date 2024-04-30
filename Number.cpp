#include "texture.h"
#include "mydirect3d.h"
#include <d3d9.h>
#include <tchar.h>
#include <d3dx9.h>
#include "sprite.h"
#include "Number.h"

#define NUMBER_SIZE_X 64
#define NUMBER_SIZE_Y 64
#define NUMBER_SIZE_X_MAX 640
#define NUMBER_MAX 5 
struct number
{
	D3DXVECTOR2 size;
	bool Visible;
};
static number NUMBER;
void Number_Init(void)
{
	NUMBER.size.x = NUMBER_SIZE_X_MAX;
	NUMBER.size.y = NUMBER_SIZE_Y;
	NUMBER.Visible = true;
}


void Number_Draw(int number,float Trans_X, float x, float y)
{
	int Score;
	for (int i = NUMBER_MAX; i > 0; i--)
	{
		Score = number % 10;
		Sprite_Draw_Tex_x_y_cx_cy_cw_ch(Texture.Tex[Number_Texture],Trans_X+(x * i), y, Score * NUMBER_SIZE_X, 0, NUMBER_SIZE_X, NUMBER_SIZE_Y);
		number /= 10;
	}
}
void Number_Destroy(void)
{
	NUMBER.Visible = false;
}
void Number_Used(void)
{
	NUMBER.Visible;
}
