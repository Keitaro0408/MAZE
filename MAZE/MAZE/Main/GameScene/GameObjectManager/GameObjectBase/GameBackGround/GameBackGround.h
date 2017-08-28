/**
 * @file   GameBackGround.h
 * @brief  GameBackGroundクラスのヘッダファイル
 * @author kotani
 */
#ifndef GAMEBACKGROUND_H
#define GAMEBACKGROUND_H
#include "..\GameObjectBase.h"

class GameBackGround : public GameObjectBase
{
public:
	GameBackGround();
	virtual ~GameBackGround();

	void Update() override;
	void Draw() override;

};


#endif
