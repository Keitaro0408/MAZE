/**
 * @file   Player.cpp
 * @brief  Playerクラスの実装
 * @author kotani
 */
#include "Player.h"


Player::Player()
{
	m_pUpdateTask = new Lib::UpdateTask();
	m_pUpdateTask->SetObject(this);
	SINGLETON_INSTANCE(Lib::TaskManager).AddTask(m_pUpdateTask);

	m_pDrawTask = new Lib::DrawTask();
	m_pDrawTask->SetObject(this);
	SINGLETON_INSTANCE(Lib::TaskManager).AddTask(m_pDrawTask);
}


Player::~Player()
{
	SINGLETON_INSTANCE(Lib::TaskManager).RemoveTask(m_pDrawTask);
	Lib::SafeDelete(m_pDrawTask);

	SINGLETON_INSTANCE(Lib::TaskManager).RemoveTask(m_pUpdateTask);
	Lib::SafeDelete(m_pUpdateTask);
}


//----------------------------------------------------------------------------------------------------
// Public Functions
//----------------------------------------------------------------------------------------------------

void Player::Update()
{
}

void Player::Draw()
{
}
