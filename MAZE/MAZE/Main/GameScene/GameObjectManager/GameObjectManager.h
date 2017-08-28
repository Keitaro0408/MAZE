/**
 * @file   GameObjectManager.h
 * @brief  GameObjectManagerクラスのヘッダファイル
 * @author kotani
 */
#ifndef OBJECTMANAGER_H
#define OBJECTMANAGER_H
#include <vector>

class GameObjectBase;

class GameObjectManager
{
public:
	GameObjectManager();
	~GameObjectManager();

private:
	std::vector<GameObjectBase*> m_pGameObjectBase;

};


#endif
