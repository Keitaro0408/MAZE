﻿/**
 * @file   App.cpp
 * @brief  Appクラスの実装
 * @author kotani
 */
#include "App.h"
#include "Window\Window.h"
#include "GameScene\GameScene.h"
#include "TitleScene\TitleScene.h"
#include "Helper\Helper.h"
#include "GamePlayManager\GamePlayManager.h"

App::App() :
ApplicationBase(TEXT("MAZE"), 1920, 1080)
{
}


//----------------------------------------------------------------------------------------------------
// Public Functions
//----------------------------------------------------------------------------------------------------

void App::Initialize()
{
	SINGLETON_INSTANCE(Lib::Window).ChangeWindowSize(1280,720);
	SINGLETON_CREATE(GamePlayManager);
	m_pScene.push_back(new TitleScene());
	m_pScene.push_back(new GameScene());

	SINGLETON_INSTANCE(Lib::SceneManager).AddScene(m_pScene[TITLE_SCENE]);
	SINGLETON_INSTANCE(Lib::SceneManager).AddScene(m_pScene[GAME_SCENE]);

	SINGLETON_INSTANCE(Lib::SceneManager).ChangeScene("GameScene");
}

void App::Finalize()
{
	for (int i = 0; i < SCENE_MAX; i++)
	{
		m_pScene[i]->Finalize();
		Lib::SafeDelete(m_pScene[i]);
	}
	SINGLETON_DELETE(GamePlayManager);
}