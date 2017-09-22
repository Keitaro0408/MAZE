/**
 * @file   PlayerEventListener.cpp
 * @brief  PlayerEventListenerクラスの実装
 * @author kotani
 */
#include "PlayerEventListener.h"
#include "Player.h"
#include <functional>

#include "Event\EventManager.h"

PlayerEventListener::PlayerEventListener(Player* _player) :
m_pPlayer(_player)
{
	SINGLETON_INSTANCE(Lib::EventManager).AddListener(this);
}

void PlayerEventListener::OnEvent(Lib::Event& _event)
{
	if (_event.eventName == std::hash<char*>()("GameStart"))
	{
		m_pPlayer->m_IsStart = true;
	}
	else if (_event.eventName == std::hash<char*>()("LeftSpin"))
	{
		int posArrayX = static_cast<int>((m_pPlayer->m_Pos.x - 480) / 64);
		int posArrayY = static_cast<int>((m_pPlayer->m_Pos.y - 60) / 64);
		m_pPlayer->m_Angle = 0;

		m_pPlayer->m_Pos.x = static_cast<float>((posArrayX * 64 + 480) + 32);
		m_pPlayer->m_Pos.y = static_cast<float>((posArrayY * 64 + 60) + 32);
		m_pPlayer->m_SpinType = Player::LEFT_SPIN;
		m_pPlayer->m_SpinSpeed = -2;
	}
	else if (_event.eventName == std::hash<char*>()("RightSpin"))
	{
		int posArrayX = static_cast<int>((m_pPlayer->m_Pos.x - 480) / 64);
		int posArrayY = static_cast<int>((m_pPlayer->m_Pos.y - 60) / 64);
		m_pPlayer->m_Angle = 0;

		m_pPlayer->m_Pos.x = static_cast<float>((posArrayX * 64 + 480) + 32);
		m_pPlayer->m_Pos.y = static_cast<float>((posArrayY * 64 + 60) + 32);
		m_pPlayer->m_SpinType = Player::RIGHT_SPIN;
		m_pPlayer->m_SpinSpeed = 2;
	}
	else if (_event.eventName == std::hash<char*>()("ReversalSpin"))
	{
		int posArrayX = static_cast<int>((m_pPlayer->m_Pos.x - 480) / 64);
		int posArrayY = static_cast<int>((m_pPlayer->m_Pos.y - 60) / 64);
		m_pPlayer->m_Angle = 0;

		m_pPlayer->m_Pos.x = static_cast<float>((posArrayX * 64 + 480) + 32);
		m_pPlayer->m_Pos.y = static_cast<float>((posArrayY * 64 + 60) + 32);
		m_pPlayer->m_SpinType = Player::REVERSAL_SPIN;
		m_pPlayer->m_SpinSpeed = 4;
	}
}
