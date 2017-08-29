/**
 * @file   GameScene.cpp
 * @brief  GameSceneクラスの実装
 * @author kotani
 */
#include "GameScene.h"
#include "Helper\Helper.h"
#include "TaskManager\TaskManager.h"
#include "GameObjectManager\GameObjectManager.h"
#include "UIObjectManager\UIObjectManager.h"
#include "..\GamePlayManager\GamePlayManager.h"
#include "Dx11\DX11Manager.h"
#include "Texture\TextureManager.h"
#include "DxInput\KeyBoard\KeyDevice.h"
#include "..\ResourceId.h"

GameScene::GameScene() :
SceneBase("GameScene")
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
	int dummy = 0;
	SINGLETON_INSTANCE(Lib::TextureManager).Load("Resource\\GameScene\\Texture\\GameBackGround.png", &dummy);
	SINGLETON_INSTANCE(Lib::TextureManager).Load("Resource\\GameScene\\Texture\\Texture.png", &dummy);
	SINGLETON_INSTANCE(GamePlayManager).StageLoad();
	m_pGameObjectManager = new GameObjectManager();
	m_pUIObjectManager = new UIObjectManager();


	return true;
}

void GameScene::Finalize()
{
	Lib::SafeDelete(m_pUIObjectManager);
	Lib::SafeDelete(m_pGameObjectManager);
	for (int i = 0; i < ResourceId::Game::TEX_MAX; i++)
	{
		SINGLETON_INSTANCE(Lib::TextureManager).ReleaseTexture(i);
	}
}

void GameScene::Execute()
{
	SINGLETON_INSTANCE(Lib::KeyDevice).Update();
	SINGLETON_INSTANCE(Lib::DX11Manager).BeginScene();
	SINGLETON_INSTANCE(Lib::DX11Manager).SetDepthStencilTest(false);
	SINGLETON_INSTANCE(Lib::TaskManager).AllExecute();
	SINGLETON_INSTANCE(Lib::DX11Manager).EndScene();
}
