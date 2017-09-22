/**
 * @file   DoorEventListener.cpp
 * @brief  DoorEventListenerクラスの実装
 * @author kotani
 */
#include "DoorEventListener.h"
#include "Door.h"
#include "..\..\..\..\..\ResourceId.h"

#include "Sound\DSoundManager.h"
#include "Event\EventManager.h"
#include <functional>

DoorEventListener::DoorEventListener(Door* _door) :
m_pDoor(_door)
{
	SINGLETON_INSTANCE(Lib::EventManager).AddListener(this);
}

void DoorEventListener::OnEvent(Lib::Event& _event)
{
	if (_event.eventName == std::hash<char*>()("OpenStartDoor"))
	{
		m_pDoor->m_pStartDoorUv->SetAnimCount(1);
	}
	else if (_event.eventName == std::hash<char*>()("CloseStartDoor"))
	{
		m_pDoor->m_pStartDoorUv->SetAnimCount(0);
	}
	else if (_event.eventName == std::hash<char*>()("OpenGoalDoor"))
	{
		m_pDoor->m_pGoalDoorUv->SetAnimCount(1);
	}
	else if (_event.eventName == std::hash<char*>()("CloseGoalDoor"))
	{
		m_pDoor->m_pGoalDoorUv->SetAnimCount(0);
	}
}
