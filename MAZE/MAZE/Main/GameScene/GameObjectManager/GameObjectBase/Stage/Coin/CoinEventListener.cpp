/**
 * @file   CoinEventListener.cpp
 * @brief  CoinEventListenerクラスの実装
 * @author kotani
 */
#include "CoinEventListener.h"
#include "Coin.h"
#include "..\..\..\..\..\ResourceId.h"

#include "Sound\DSoundManager.h"
#include "Event\EventManager.h"
#include <functional>

CoinEventListener::CoinEventListener(Coin* _coin) :
m_pCoin(_coin)
{
	SINGLETON_INSTANCE(Lib::EventManager).AddListener(this);
}

void CoinEventListener::OnEvent(Lib::Event& _event)
{
	if (_event.eventName == std::hash<char*>()("CoinGet"))
	{
		// 各オブジェクトの描画に使っている配列データは回転を反映していないのでここで合わせる
		m_pCoin->m_Stage = SINGLETON_INSTANCE(GamePlayManager).GetSelectStage();
		float stageAngle = SINGLETON_INSTANCE(GamePlayManager).GetStageAngle();
		while (stageAngle != 0)
		{
			if (stageAngle < 0)
			{
				stageAngle += 90;
				m_pCoin->m_Stage = SINGLETON_INSTANCE(GamePlayManager).RightSpin(m_pCoin->m_Stage);
			}
			else if (stageAngle > 0)
			{
				stageAngle -= 90;
				m_pCoin->m_Stage = SINGLETON_INSTANCE(GamePlayManager).LeftSpin(m_pCoin->m_Stage);
			}
		}

		SINGLETON_INSTANCE(Lib::DSoundManager).SoundOperation(ResourceId::Game::COIN_SE, Lib::DSoundManager::SOUND_STOP_RESET);
		SINGLETON_INSTANCE(Lib::DSoundManager).SoundOperation(ResourceId::Game::COIN_SE, Lib::DSoundManager::SOUND_PLAY);
	}
}
