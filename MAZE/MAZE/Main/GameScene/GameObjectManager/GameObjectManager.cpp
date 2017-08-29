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
	m_pGameObjectBase.push_back(new GameBackGround());
	m_pGameObjectBase.push_back(new Stage());
	m_pGameObjectBase.push_back(new Player());
}


GameObjectManager::~GameObjectManager()
{
	for (unsigned i = 0; i < m_pGameObjectBase.size(); i++)
	{
		Lib::SafeDelete(m_pGameObjectBase[i]);
	}
}
