/**
 * @file   ObjectBase.cpp
 * @brief  ObjectBaseクラスの実装
 * @author kotani
 */
#include "ObjectBase.h"
#include "..\TaskManager\TaskManager.h"

namespace Lib
{
	void ObjectBase::InitializeTask(int _updatePriority, int _drawPriority)
	{
		m_pUpdateTask = new Lib::UpdateTask(_updatePriority);
		m_pUpdateTask->SetObject(this);
		SINGLETON_INSTANCE(Lib::TaskManager).AddTask(m_pUpdateTask);

		m_pDrawTask = new Lib::DrawTask(_drawPriority);
		m_pDrawTask->SetObject(this);
		SINGLETON_INSTANCE(Lib::TaskManager).AddTask(m_pDrawTask);
	}

	void ObjectBase::FinalizeTask()
	{
		SINGLETON_INSTANCE(Lib::TaskManager).RemoveTask(m_pDrawTask);
		Lib::SafeDelete(m_pDrawTask);

		SINGLETON_INSTANCE(Lib::TaskManager).RemoveTask(m_pUpdateTask);
		Lib::SafeDelete(m_pUpdateTask);
	}
}