/**
 * @file   TimerUIEventListener.cpp
 * @brief  TimerUIEventListenerクラスの実装
 * @author kotani
 */
#include "TimerUIEventListener.h"
#include "TimerUI.h"
#include "..\..\..\..\GamePlayManager\GamePlayManager.h"

#include <functional>
#include "Event\EventManager.h"

TimerUIEventListener::TimerUIEventListener(TimerUI* _timerUI) :
m_pTimerUI(_timerUI)
{
	SINGLETON_INSTANCE(Lib::EventManager).AddListener(this);
}

void TimerUIEventListener::OnEvent(Lib::Event& _event)
{
	if (_event.eventName == std::hash<char*>()("GameStart"))
	{
		m_pTimerUI->m_IsStart = true;
	}
	else if (_event.eventName == std::hash<char*>()("OpenGoalDoor"))
	{
		SINGLETON_INSTANCE(GamePlayManager).SetClearTime(m_pTimerUI->m_Time);
	}
	else if (_event.eventName == std::hash<char*>()("CoinGet"))
	{
		m_pTimerUI->m_Time += 5;
	}
}
