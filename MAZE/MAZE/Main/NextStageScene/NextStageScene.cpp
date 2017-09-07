/**
* @file   NextStageScene.cpp
* @brief  NextStageSceneクラスの実装
* @author kotani
*/
#include "NextStageScene.h"
#include "SceneManager\SceneManager.h"
#include "..\GamePlayManager\GamePlayManager.h"
#include "Event\EventManager.h"


NextStageScene::NextStageScene() :
SceneBase("NextStageScene")
{
}


NextStageScene::~NextStageScene()
{
}


//----------------------------------------------------------------------------------------------------
// Public Functions
//----------------------------------------------------------------------------------------------------

bool NextStageScene::Initialize()
{
	SINGLETON_INSTANCE(Lib::SceneManager).ChangeScene("GameScene");
	return true;
}

void NextStageScene::Finalize()
{
}

void NextStageScene::Execute()
{
}
