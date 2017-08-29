/**
 * @file   Stage.cpp
 * @brief  Stageクラスの実装
 * @author kotani
 */
#include "Stage.h"
#include "TaskManager\TaskManager.h"
#include "Ground\Ground.h"


Stage::Stage()
{
	m_pGround = new Ground();
}

Stage::~Stage()
{
	Lib::SafeDelete(m_pGround);
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
