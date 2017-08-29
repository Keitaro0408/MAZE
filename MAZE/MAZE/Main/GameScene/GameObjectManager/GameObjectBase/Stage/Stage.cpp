/**
 * @file   Stage.cpp
 * @brief  Stageクラスの実装
 * @author kotani
 */
#include "Stage.h"
#include "TaskManager\TaskManager.h"


Stage::Stage()
{
	m_pUpdateTask = new Lib::UpdateTask();
	m_pUpdateTask->SetObject(this);
	SINGLETON_INSTANCE(Lib::TaskManager).AddTask(m_pUpdateTask);

	m_pDrawTask = new Lib::DrawTask();
	m_pDrawTask->SetObject(this);
	SINGLETON_INSTANCE(Lib::TaskManager).AddTask(m_pDrawTask);

	m_pGround = new Ground();
}

Stage::~Stage()
{
	Lib::SafeDelete(m_pGround);

	SINGLETON_INSTANCE(Lib::TaskManager).RemoveTask(m_pDrawTask);
	Lib::SafeDelete(m_pDrawTask);

	SINGLETON_INSTANCE(Lib::TaskManager).RemoveTask(m_pUpdateTask);
	Lib::SafeDelete(m_pUpdateTask);
}


//----------------------------------------------------------------------------------------------------
// Public Functions
//----------------------------------------------------------------------------------------------------

void Stage::Update()
{
}

void Stage::Draw()
{
}
