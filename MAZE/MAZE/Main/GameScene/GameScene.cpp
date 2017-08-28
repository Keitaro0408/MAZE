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
	m_pGameObjectManager = new GameObjectManager();
	m_pUIObjectManager = new UIObjectManager();
	return true;
}

void GameScene::Finalize()
{
	Lib::SafeDelete(m_pUIObjectManager);
	Lib::SafeDelete(m_pGameObjectManager);
}

void GameScene::Execute()
{
	SINGLETON_INSTANCE(Lib::TaskManager).AllExecute();
}
