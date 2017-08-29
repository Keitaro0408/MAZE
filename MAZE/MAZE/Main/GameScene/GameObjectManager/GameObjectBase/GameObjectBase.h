/**
 * @file   GameObjectBase.h
 * @brief  GameObjectBaseクラスのヘッダファイル
 * @author kotani
 */
#ifndef GAMEOBJECTBASE_H
#define GAMEOBJECTBASE_H
#include "ObjectBase\ObjectBase.h"
#include "TaskManager\TaskManager.h"

class GameObjectBase : public Lib::ObjectBase
{
public:
	GameObjectBase() = default;
	virtual ~GameObjectBase() = default;

	void InitializeTask(int _updateTask = 0,int _drawTask = 0);
	void FinalizeTask();

	virtual void Update(){};
	virtual void Draw(){};
};


#endif
