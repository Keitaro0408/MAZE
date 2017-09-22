/**
 * @file   StageEventListener.cpp
 * @brief  StageEventListenerクラスの実装
 * @author kotani
 */
#include "StageEventListener.h"
#include "Stage.h"

#include <functional>
#include "Event\EventManager.h"


StageEventListener::StageEventListener(Stage* _stage) :
m_pStage(_stage)
{
	SINGLETON_INSTANCE(Lib::EventManager).AddListener(this);
}

void StageEventListener::OnEvent(Lib::Event& _event)
{
	if (_event.eventName == std::hash<char*>()("LeftSpin"))
	{
		m_pStage->m_SpinType = Stage::LEFT_SPIN;
		m_pStage->m_SpinSpeed = -2;
		m_pStage->m_AddAngleCount = 0;
	}
	else if (_event.eventName == std::hash<char*>()("RightSpin"))
	{
		m_pStage->m_SpinType = Stage::RIGHT_SPIN;
		m_pStage->m_SpinSpeed = 2;
		m_pStage->m_AddAngleCount = 0;
	}
	else if (_event.eventName == std::hash<char*>()("ReversalSpin"))
	{
		m_pStage->m_SpinType = Stage::REVERSAL_SPIN;
		m_pStage->m_SpinSpeed = 4;
		m_pStage->m_AddAngleCount = 0;
	}
	else if (_event.eventName == std::hash<char*>()("ReversalSpin"))
	{
		m_pStage->m_SpinType = Stage::INITIALIZE_SPIN;
		m_pStage->m_SpinSpeed = 4;
		m_pStage->m_AddAngleCount = 0;
	}
}
