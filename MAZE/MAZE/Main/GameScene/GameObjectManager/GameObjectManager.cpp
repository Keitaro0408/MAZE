/**
 * @file   GameObjectManager.cpp
 * @brief  GameObjectManagerクラスの実装
 * @author kotani
 */
#include "GameObjectManager.h"
#include "GameObjectBase\GameBackGround\GameBackGround.h"
#include "GameObjectBase\Stage\Stage.h"
#include "GameObjectBase\Player\Player.h"


GameObjectManager::GameObjectManager()
{
	m_pGameObjectBase[0] = Lib::MakeUnique<GameBackGround>();
	m_pGameObjectBase[1] = Lib::MakeUnique<Stage>();
	m_pGameObjectBase[2] = Lib::MakeUnique<Player>();
}

GameObjectManager::~GameObjectManager()
{
}
