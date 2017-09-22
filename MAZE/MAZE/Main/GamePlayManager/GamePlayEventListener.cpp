/**
 * @file   GamePlayEventListener.cpp
 * @brief  GamePlayEventListenerクラスの実装
 * @author kotani
 */
#include "GamePlayEventListener.h"
#include "GamePlayManager.h"

#include "Sound\DSoundManager.h"
#include "Event\EventManager.h"
#include <functional>

GamePlayEventListener::GamePlayEventListener()
{
	SINGLETON_INSTANCE(Lib::EventManager).AddListener(this);
}

void GamePlayEventListener::OnEvent(Lib::Event& _event)
{
	GamePlayManager& gamePlayManager = SINGLETON_INSTANCE(GamePlayManager);
	if (_event.eventName == std::hash<char*>()("PlayerRespawn"))
	{
		while (gamePlayManager.m_StageAngle != 0)
		{
			if (gamePlayManager.m_StageAngle < 0)
			{
				gamePlayManager.m_StageAngle += 90;
				gamePlayManager.m_SelectStage = SINGLETON_INSTANCE(GamePlayManager).RightSpin(gamePlayManager.m_SelectStage);
			}
			else if (gamePlayManager.m_StageAngle > 0)
			{
				gamePlayManager.m_StageAngle -= 90;
				gamePlayManager.m_SelectStage = SINGLETON_INSTANCE(GamePlayManager).LeftSpin(gamePlayManager.m_SelectStage);
			}
		}

		gamePlayManager.m_StageAngle = 0;
		gamePlayManager.m_IsSpin = true;
	}
	else if (_event.eventName == std::hash<char*>()("LeftSpin"))
	{
		gamePlayManager.m_IsSpin = true;
		gamePlayManager.m_StageAngle -= 90.f;
		gamePlayManager.m_Angle -= 90.f;
		if (gamePlayManager.m_StageAngle <= -360 ||
			gamePlayManager.m_StageAngle >= 360)
		{
			gamePlayManager.m_StageAngle = 0;
		}
		gamePlayManager.m_SelectStage = gamePlayManager.LeftSpin(gamePlayManager.m_SelectStage);
	}
	else if (_event.eventName == std::hash<char*>()("RightSpin"))
	{
		gamePlayManager.m_IsSpin = true;
		gamePlayManager.m_StageAngle += 90.f;
		if (gamePlayManager.m_StageAngle <= -360 ||
			gamePlayManager.m_StageAngle >= 360)
		{
			gamePlayManager.m_StageAngle = 0;
		}

		gamePlayManager.m_SelectStage = gamePlayManager.RightSpin(gamePlayManager.m_SelectStage);
	}
	else if (_event.eventName == std::hash<char*>()("ReversalSpin"))
	{
		gamePlayManager.m_IsSpin = true;
		gamePlayManager.m_StageAngle += 90.f;
		if (gamePlayManager.m_StageAngle <= -360 ||
			gamePlayManager.m_StageAngle >= 360)
		{
			gamePlayManager.m_StageAngle = 0;
		}
		gamePlayManager.m_StageAngle += 90.f;
		if (gamePlayManager.m_StageAngle <= -360 ||
			gamePlayManager.m_StageAngle >= 360)
		{
			gamePlayManager.m_StageAngle = 0;
		}
		gamePlayManager.m_SelectStage = gamePlayManager.RightSpin(gamePlayManager.m_SelectStage);
		gamePlayManager.m_SelectStage = gamePlayManager.RightSpin(gamePlayManager.m_SelectStage);
	}
}
