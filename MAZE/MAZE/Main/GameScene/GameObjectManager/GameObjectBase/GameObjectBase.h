/**
 * @file   GameObjectBase.h
 * @brief  GameObjectBaseクラスのヘッダファイル
 * @author kotani
 */
#ifndef GAMEOBJECTBASE_H
#define GAMEOBJECTBASE_H
#include "ObjectBase\ObjectBase.h"

class GameObjectBase : public Lib::ObjectBase
{
public:
	GameObjectBase() = default;
	virtual ~GameObjectBase() = default;

	virtual void Update(){};
	virtual void Draw(){};
};


#endif
