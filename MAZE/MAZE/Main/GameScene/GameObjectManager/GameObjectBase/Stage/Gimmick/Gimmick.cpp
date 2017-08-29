/**
 * @file   Gimmick .cpp
 * @brief  Gimmick クラスの実装
 * @author kotani
 */
#include "Gimmick.h"


Gimmick::Gimmick()
{
	m_pUpdateTask = new Lib::UpdateTask();
	m_pUpdateTask->SetObject(this);
	SINGLETON_INSTANCE(Lib::TaskManager).AddTask(m_pUpdateTask);

	m_pDrawTask = new Lib::DrawTask();
	m_pDrawTask->SetObject(this);
	SINGLETON_INSTANCE(Lib::TaskManager).AddTask(m_pDrawTask);
}


Gimmick ::~Gimmick()
{
	SINGLETON_INSTANCE(Lib::TaskManager).RemoveTask(m_pDrawTask);
	Lib::SafeDelete(m_pDrawTask);

	SINGLETON_INSTANCE(Lib::TaskManager).RemoveTask(m_pUpdateTask);
	Lib::SafeDelete(m_pUpdateTask);
}


//----------------------------------------------------------------------------------------------------
// Public Functions
//----------------------------------------------------------------------------------------------------

void Gimmick::Update()
{
}

void Gimmick::Draw()
{
}
