#include "Scene.h"
#include <d3d9.h>
#include <tchar.h>
#include "Title.h"
#include <d3dx9.h>
#include "game.h"
#include "HighScore.h"
#include "Pause.h"
#include "Name.h"
//SCENE g_Scene = SCENE_GAME;
//SCENE g_NextScene = SCENE_GAME;
//SCENE g_Scene = SCENE_NAME;
//SCENE g_NextScene = SCENE_NAME;
SCENE g_Scene = SCENE_TITLE;
SCENE g_NextScene = SCENE_TITLE;
//SCENE g_Scene = SCENE_SCORE;
//SCENE g_NextScene = SCENE_SCORE;
tag_HighScore Score;
static bool Ischange = false;
static bool Isfade = false;


void Scene_Init(void)
{
	switch (g_NextScene)
	{
	case SCENE_TITLE:
	{
		Title_Init();
		break;
	}
	case SCENE_GAME:
	{
		game_Init();
		break;
	}
	case SCENE_NAME:
	{
		Name.Init();
		break;
	}
	case SCENE_SCORE:
	{
		Score.Init();
		break;
	}
	
	default:
	break;
	}
}
void Scene_Update(void)
{
	switch (g_Scene)
	{
	case SCENE_TITLE:
	{
		Title_Update();
		break;
	}
	case SCENE_GAME:
	{
		game_Update();
		break;
	}
	case SCENE_NAME:
	{
		Name.Update();
		break;
	}
	case SCENE_SCORE:
	{
		Score.Update();
		break;
	}
	default:
		break;
	}
	if (Ischange)
	{
		Ischange = false;
		//Scene_Uninit();
		//Scene_Init();
		g_Scene = g_NextScene;
	}
}
void Scene_Draw(void)
{
	switch (g_Scene)
	{
	case SCENE_TITLE:
		Title_Draw();
		break;
	case SCENE_GAME:
		game_Draw();
		break;
	case SCENE_NAME:
	{
		Name.Draw();
		break;
	}
	case SCENE_SCORE:
	{
		Score.Draw();
		break;
	}
	default:
		break;
	}
}
void Scene_Uninit(void)
{
	switch (g_Scene)
	{
	case SCENE_TITLE:
		break;
	case SCENE_GAME:
		//game_Uninit();
		break;
	case SCENE_NAME:
	{
		break;
	}
	case SCENE_SCORE:
	{

		break;
	}
	default:
		break;
	}


}

void Scene_SetNextScene(SCENE next_scene)
{
	g_NextScene = next_scene;
}


bool Scene_Change()
{
	if (g_Scene != g_NextScene && !Ischange)
	{
		if (g_NextScene == SCENE_MAX)
		{
			return true;
		}
		Ischange = true;
		Scene_Uninit();
		Scene_Init();
		g_Scene = g_NextScene;
	}
	return false;
}



