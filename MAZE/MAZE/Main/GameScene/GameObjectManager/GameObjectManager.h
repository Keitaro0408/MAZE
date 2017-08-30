/**
 * @file   GameObjectManager.h
 * @brief  GameObjectManagerクラスのヘッダファイル
 * @author kotani
 */
#ifndef OBJECTMANAGER_H
#define OBJECTMANAGER_H
#include <array>
#include "SmartPointer\UniquePtr.h"

class GameObjectBase;

class GameObjectManager
{
public:
	GameObjectManager();
	~GameObjectManager();

private:
	std::array<Lib::UniquePtr<GameObjectBase>, 3> m_pGameObjectBase;

};


#endif
