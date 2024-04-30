#include "common.h"
#include <d3d9.h>
#include <d3dx9.h>
#include "mydirect3d.h"
#include "collision.h"
bool Circle_circle(Circle* pA, Circle* pB)
{
    D3DXVECTOR2 diff = pA->position - pB->position;

    return (pA->radius + pB->radius) * (pA->radius + pB->radius) > D3DXVec2LengthSq(&diff);
}

