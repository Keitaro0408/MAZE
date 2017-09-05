/**
 * @file   TitleScene.cpp
 * @brief  TitleSceneクラスの実装
 * @author kotani
 */
#include "TitleScene.h"
#include "SceneManager\SceneManager.h"


TitleScene::TitleScene() :
SceneBase("TitleScene")
{
}


TitleScene::~TitleScene()
{
}


//----------------------------------------------------------------------------------------------------
// Public Functions
//----------------------------------------------------------------------------------------------------

bool TitleScene::Initialize()
{
	SINGLETON_INSTANCE(Lib::SceneManager).ChangeScene("GameScene");
	return true;
}

void TitleScene::Finalize()
{
}

void TitleScene::Execute()
{
}
