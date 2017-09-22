/**
 * @file   EventManager.cpp
 * @brief  EventManagerクラスの実装
 * @author kotani
 */
#include "EventManager.h"
#include "Event.h"
#include "EventListenerBase.h"

namespace Lib
{
//----------------------------------------------------------------------------------------------------
// Public Functions
//----------------------------------------------------------------------------------------------------

	void EventManager::AddListener(EventListenerBase* _pEventListnerBaseList)
	{
		m_pEventListenerBase.push_back(_pEventListnerBaseList);
	}
	
	void EventManager::SendEvent(Event& _pEvent)
	{
		for (auto itr : m_pEventListenerBase)
		{
			itr->OnEvent(_pEvent);
		}
	}

	void EventManager::AddQueueEvent(Event* _pEvent)
	{
		m_pEventQueueList.push_back(*_pEvent);
	}

	void EventManager::Execute()
	{
		std::list<Event>::iterator eventItr = m_pEventQueueList.begin();

		for (auto itr : m_pEventQueueList)
		{
			for (auto itr2 : m_pEventListenerBase)
			{
				itr2->OnEvent(itr);
			}
		}
		m_pEventQueueList.clear();
	}

	void EventManager::AllEventClear()
	{
		m_pEventListenerBase.clear();
	}
}
