/**
 * @file   GameScene.h
 * @brief  GameSceneクラスのヘッダファイル
 * @author kotani
 */
#ifndef GAMESCENE_H
#define GAMESCENE_H
#include "SceneManager\SceneBase\SceneBase.h"

class GameObjectManager;
class UIObjectManager;

class GameScene : public Lib::SceneBase
{
public:
	GameScene();
	virtual ~GameScene();

	bool Initialize() override;
	void Finalize() override;

	void Execute() override;

private:
	GameObjectManager* m_pGameObjectManager;
	UIObjectManager*   m_pUIObjectManager;

};


#endif
