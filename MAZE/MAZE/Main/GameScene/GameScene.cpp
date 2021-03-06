﻿/**
 * @file   GameScene.cpp
 * @brief  GameSceneクラスの実装
 * @author kotani
 */
#include "GameScene.h"
#include "..\GamePlayManager\GamePlayManager.h"
#include "..\ResourceId.h"
#include "GameObjectManager\GameObjectManager.h"
#include "UIObjectManager\UIObjectManager.h"

#include "Helper\Helper.h"
#include "TaskManager\TaskManager.h"
#include "Dx11\DX11Manager.h"
#include "Event\EventManager.h"
#include "Texture\TextureManager.h"
#include "DxInput\KeyBoard\KeyDevice.h"
#include "Sound\DSoundManager.h"
#include "Window\Window.h"


GameScene::GameScene() :
SceneBase("GameScene"),
m_BGMSoundDelayFrame(120)
{
}

GameScene::~GameScene()
{
}


//----------------------------------------------------------------------------------------------------
// Public Functions
//----------------------------------------------------------------------------------------------------

bool GameScene::Initialize()
{
	m_FrameCount = 0;
	int dummy = 0;
	SINGLETON_INSTANCE(GamePlayManager).NextStage();
	SINGLETON_INSTANCE(GamePlayManager).StageLoad();

	SINGLETON_INSTANCE(Lib::TextureManager).Load("Resource\\GameScene\\Texture\\GameBackGround.png", &dummy);
	SINGLETON_INSTANCE(Lib::TextureManager).Load("Resource\\GameScene\\Texture\\Texture.png", &dummy);
	SINGLETON_INSTANCE(Lib::DSoundManager).LoadSound("Resource\\GameScene\\Sound\\Main.wav", &dummy);
	SINGLETON_INSTANCE(Lib::DSoundManager).LoadSound("Resource\\GameScene\\Sound\\Start.wav", &dummy);
	SINGLETON_INSTANCE(Lib::DSoundManager).LoadSound("Resource\\GameScene\\Sound\\Landing.wav", &dummy);
	SINGLETON_INSTANCE(Lib::DSoundManager).LoadSound("Resource\\GameScene\\Sound\\CoinGet.wav", &dummy);

	m_pGameObjectManager = Lib::MakeUnique<GameObjectManager>();
	m_pUIObjectManager = Lib::MakeUnique<UIObjectManager>();

	return true;
}

void GameScene::Finalize()
{
	m_pUIObjectManager.Reset();
	m_pGameObjectManager.Reset();
	for (int i = 0; i < ResourceId::Game::TEX_MAX; i++)
	{
		SINGLETON_INSTANCE(Lib::TextureManager).ReleaseTexture(i);
	}
	SINGLETON_INSTANCE(Lib::TextureManager).ClearResource();

	for (int i = 0; i < ResourceId::Game::SOUND_MAX; i++)
	{
		SINGLETON_INSTANCE(Lib::DSoundManager).ReleaseSound(i);
	}
	SINGLETON_INSTANCE(Lib::DSoundManager).ClearResource();

	SINGLETON_INSTANCE(Lib::EventManager).AllEventRelease();
}

void GameScene::Execute()
{
	if (m_FrameCount < m_BGMSoundDelayFrame)
	{
		m_FrameCount++;
		if (m_FrameCount == 60)
		{
			SINGLETON_INSTANCE(Lib::DSoundManager).
				SoundOperation(ResourceId::Game::START_SE, Lib::DSoundManager::SOUND_PLAY);
		}
	}
	else if (m_FrameCount == m_BGMSoundDelayFrame)
	{
		SINGLETON_INSTANCE(Lib::EventManager).CallEvent("GameStart");
		SINGLETON_INSTANCE(Lib::DSoundManager).
			SoundOperation(ResourceId::Game::MAIN_BGM,Lib::DSoundManager::SOUND_LOOP);
		m_FrameCount++;
	}
	SINGLETON_INSTANCE(Lib::KeyDevice).Update();
	SINGLETON_INSTANCE(Lib::DX11Manager).BeginScene();
	SINGLETON_INSTANCE(Lib::DX11Manager).SetDepthStencilTest(false);
	SINGLETON_INSTANCE(Lib::TaskManager).AllExecute();
	SINGLETON_INSTANCE(Lib::DX11Manager).EndScene();
}
