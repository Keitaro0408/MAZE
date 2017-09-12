/**
 * @file   App.cpp
 * @brief  Appクラスの実装
 * @author kotani
 */
#include "App.h"
#include "Window\Window.h"
#include "GameScene\GameScene.h"
#include "TitleScene\TitleScene.h"
#include "NextStageScene\NextStageScene.h"
#include "Helper\Helper.h"
#include "GamePlayManager\GamePlayManager.h"
#include "DxInput\KeyBoard\KeyDevice.h"
#include "Event\EventManager.h"


App::App() :
ApplicationBase(TEXT("MAZE"), 1920, 1080)
{
}


//----------------------------------------------------------------------------------------------------
// Public Functions
//----------------------------------------------------------------------------------------------------

void App::Initialize()
{
	SINGLETON_INSTANCE(Lib::Window).ChangeWindowSize(1280,720);
	SINGLETON_CREATE(GamePlayManager);
	m_pScene[TITLE_SCENE] = Lib::MakeUnique<TitleScene>();
	m_pScene[GAME_SCENE] = Lib::MakeUnique<GameScene>();
	m_pScene[NEXT_STAGE_SCENE] = Lib::MakeUnique<NextStageScene>();

	SINGLETON_INSTANCE(Lib::SceneManager).ChangeScene("GameScene");

	SINGLETON_INSTANCE(Lib::KeyDevice).KeyCheckEntry("RightMove", DIK_RIGHTARROW);
	SINGLETON_INSTANCE(Lib::KeyDevice).KeyCheckEntry("LeftMove", DIK_LEFTARROW);
	SINGLETON_INSTANCE(Lib::KeyDevice).KeyCheckEntry("Up", DIK_UPARROW);
	SINGLETON_INSTANCE(Lib::KeyDevice).KeyCheckEntry("Down", DIK_DOWNARROW);
	SINGLETON_INSTANCE(Lib::KeyDevice).KeyCheckEntry("A", DIK_A);
	SINGLETON_INSTANCE(Lib::KeyDevice).KeyCheckEntry("D", DIK_D);
	SINGLETON_INSTANCE(Lib::KeyDevice).KeyCheckEntry("W", DIK_W);
}

void App::Finalize()
{
	SINGLETON_DELETE(GamePlayManager);
}
