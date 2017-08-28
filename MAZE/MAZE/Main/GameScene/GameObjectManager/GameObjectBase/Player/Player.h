/**
 * @file   Player.h
 * @brief  Playerクラスのヘッダファイル
 * @author kotani
 */
#ifndef PLAYER_H
#define PLAYER_H
#include "..\GameObjectBase.h"

#include "TaskManager\TaskManager.h"

class Player : public GameObjectBase
{
public:
	Player();
	virtual ~Player();

	void Update() override;
	void Draw() override;

private:

};


#endif
