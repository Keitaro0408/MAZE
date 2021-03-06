﻿/**
 * @file   EventManager.cpp
 * @brief  EventManagerクラスの実装
 * @author kotani
 */
#include "EventManager.h"
#include "EventListnerBase.h"

namespace Lib
{


//----------------------------------------------------------------------------------------------------
// Public Functions
//----------------------------------------------------------------------------------------------------

	void EventManager::AddEvent(std::string _eventName, EventListnerBase* _pEvent)
	{
		m_pEvent[_eventName].push_back(std::bind(&EventListnerBase::Action, _pEvent));
	}
	
	void EventManager::AddEvent(std::string _eventName, std::function<void()> _event)
	{
		m_pEvent[_eventName].push_back(std::bind(_event));
	}
	
	bool EventManager::CallEvent(std::string _eventName)
	{
		if (m_pEvent.find(_eventName) == m_pEvent.end()){
			return false;
		}
	
		for (unsigned int i = 0; i < m_pEvent[_eventName].size();i++)
		{
			if (m_pEvent[_eventName][i] != nullptr)
			{
				m_pEvent[_eventName][i]();
			}
		}
		return true;
	}

	void EventManager::AllEventRelease()
	{
		m_pEvent.clear();
	}
}
