/**
 * @file   GamePlayManager.h
 * @brief  GamePlayManagerクラスのヘッダファイル
 * @author kotani
 */
#ifndef GAMEPLAYMANAGER_H
#define GAMEPLAYMANAGER_H
#include "Singleton.h"

/**
 * ゲームの状態を管理するクラス
 */
class GamePlayManager
{
	friend Lib::Singleton<GamePlayManager>;
public:

private:
	GamePlayManager() = default;
	~GamePlayManager() = default;

};


#endif
