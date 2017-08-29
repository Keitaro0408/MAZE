/**
 * @file   Ground.cpp
 * @brief  Groundクラスの実装
 * @author kotani
 */
#include "Ground.h"


Ground::Ground()
{
	m_pUpdateTask = new Lib::UpdateTask();
	m_pUpdateTask->SetObject(this);
	SINGLETON_INSTANCE(Lib::TaskManager).AddTask(m_pUpdateTask);

	m_pDrawTask = new Lib::DrawTask();
	m_pDrawTask->SetObject(this);
	SINGLETON_INSTANCE(Lib::TaskManager).AddTask(m_pDrawTask);
}

Ground::~Ground()
{
	SINGLETON_INSTANCE(Lib::TaskManager).RemoveTask(m_pDrawTask);
	Lib::SafeDelete(m_pDrawTask);

	SINGLETON_INSTANCE(Lib::TaskManager).RemoveTask(m_pUpdateTask);
	Lib::SafeDelete(m_pUpdateTask);
}


//----------------------------------------------------------------------------------------------------
// Public Functions
//----------------------------------------------------------------------------------------------------

void Ground::Update()
{
}

void Ground::Draw()
{
}
