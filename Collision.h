#pragma once
#include <d3dx9.h>
typedef struct Circle_tag
{
	D3DXVECTOR2 position;
	float radius;
}Circle;
bool Circle_circle(Circle*pA, Circle*pB);

