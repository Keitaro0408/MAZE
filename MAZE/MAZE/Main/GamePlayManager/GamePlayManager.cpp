/**
 * @file   GamePlayManager.cpp
 * @brief  GamePlayManagerクラスの実装
 * @author kotani
 */
#include "GamePlayManager.h"
#include "GamePlayEventListener.h"
#include "../GameScene/GameObjectManager/GameObjectBase/Stage/Stage.h"


#include "Event\EventManager.h"
#include <string>


GamePlayManager::GamePlayManager() :
m_StageNum(1),
m_StageAngle(0.f),
m_ClearTime(0),
m_Angle(0.f),
m_IsSpin(false),
m_IsFirstStage(true)
{
}

bool GamePlayManager::CheckGround(int _x, int _y)
{
	if ((m_SelectStage.Data[_y][_x] % 10) == Stage::TRAMPOLINE_OBJECT &&
		!CheckEnableGimmick(_x, _y))
	{
		return true;
	}
	else if ((m_SelectStage.Data[_y][_x] % 10) == Stage::NEEDLE_OBJECT &&
		!CheckEnableGimmick(_x, _y))
	{
		return true;
	}
	else if ((m_SelectStage.Data[_y][_x] % 10) == Stage::GROUND_OBJECT)
	{
		return true;
	}

	return false;
}

bool GamePlayManager::CheckEnableGimmick(int _x, int _y)
{
	if (((m_SelectStage.Data[_y][_x] / 10) % 10) == 0 &&
		m_StageAngle == 0)
	{
		return true;
	}
	else if (((m_SelectStage.Data[_y][_x] / 10) % 10) == 1)
	{
		if (m_StageAngle == -90 ||
			m_StageAngle == 270)
		{
			return true;
		}
	}
	else if (((m_SelectStage.Data[_y][_x] / 10) % 10) == 2)
	{
		if (m_StageAngle == 180 ||
			m_StageAngle == -180)
		{ 
			return true;
		}
	}
	else if (((m_SelectStage.Data[_y][_x] / 10) % 10) == 3)
	{
		if (m_StageAngle == 90 ||
			m_StageAngle == -270)
		{
			return true;
		}
	}
	return false;
}

bool GamePlayManager::CheckUnderCover(int _x, int _y)
{
	if ((m_SelectStage.Data[_y - 1][_x] % 10) == Stage::COVER_OBJECT)
	{
		if (((m_SelectStage.Data[_y - 1][_x] / 10) % 10) == 0 &&
			m_StageAngle == -180 ||
			m_StageAngle == 180)
		{
			return true;
		}
		else if (((m_SelectStage.Data[_y - 1][_x] / 10) % 10) == 1 &&
			m_StageAngle == 90 ||
			m_StageAngle == -270)
		{
			return true;
		}
		else if (((m_SelectStage.Data[_y - 1][_x] / 10) % 10) == 2 &&
			m_StageAngle == 0)
		{
			return true;
		}
		else if (((m_SelectStage.Data[_y - 1][_x] / 10) % 10) == 3 &&
			m_StageAngle == -90 ||
			m_StageAngle == 270)
		{
			return true;
		}
	}
	else if ((m_SelectStage.Data[_y][_x] % 10) == Stage::COVER_OBJECT &&
		CheckEnableGimmick(_x, _y))
	{
		return true;
	}
	return false;
}
bool GamePlayManager::CheckRightCover(int _x, int _y)
{
	if ((m_SelectStage.Data[_y][_x] % 10) == Stage::COVER_OBJECT)
	{
		if (((m_SelectStage.Data[_y][_x] / 10) % 10) == 3 &&
			m_StageAngle == 0)
		{
			return true;
		}
		//else if (((m_SelectStage.Data[_y][_x - 1] / 10) % 10) == 1 &&
		//	m_StageAngle == 0)
		//{
		//	return true;
		//}

	}
	return false;
}

bool GamePlayManager::CheckLeftCover(int _x, int _y)
{
	if ((m_SelectStage.Data[_y][_x + 1] % 10) == Stage::COVER_OBJECT)
	{
		if (((m_SelectStage.Data[_y][_x + 1] / 10) % 10) == 3 &&
			m_StageAngle == 0)
		{
			return true;
		}
		//else if (((m_SelectStage.Data[_y][_x - 1] / 10) % 10) == 1 &&
		//	m_StageAngle == 0)
		//{
		//	return true;
		//}

	}
	return false;
}


void GamePlayManager::StageLoad()
{
	std::string m_FileName;
	m_FileName = "Resource\\GameScene\\Stage\\" + std::to_string(m_StageNum) + ".csv";

	FILE*  fp;
	if (fopen_s(&fp, m_FileName.c_str(), "r") != 0)
	{
		m_StageNum = 1;
		m_FileName = "Resource\\GameScene\\Stage\\" + std::to_string(m_StageNum) + ".csv";
		fopen_s(&fp, m_FileName.c_str(), "r");
	}

	for (int i = 0; i < STAGE_HEIGHT; i++)
	{
		for (int j = 0; j < STAGE_WIDTH; j++)
		{
			fscanf_s(fp, "%d,", &m_SelectStage.Data[i][j]);
		}
	}

	fclose(fp);
}

GamePlayManager::SELECT_STAGE GamePlayManager::LeftSpin(const SELECT_STAGE& _stage)
{
	SELECT_STAGE Stage;
	for (int i = 0; i < STAGE_HEIGHT; i++)
	{
		for (int j = 0; j < STAGE_WIDTH; j++)
		{
			Stage.Data[STAGE_WIDTH - i - 1][j] = _stage.Data[j][i];
		}
	}
	return Stage;
}

GamePlayManager::SELECT_STAGE GamePlayManager::RightSpin(const SELECT_STAGE& _stage)
{
	SELECT_STAGE Stage;
	for (int i = 0; i < STAGE_HEIGHT; i++)
	{
		for (int j = 0; j < STAGE_WIDTH; j++)
		{
			Stage.Data[i][STAGE_WIDTH - j - 1] = _stage.Data[j][i];
		}
	}
	return Stage;
}

void GamePlayManager::InitializeEvent()
{
	m_pGamePlayEventListener.Reset();
	m_pGamePlayEventListener = Lib::MakeUnique<GamePlayEventListener>();

	m_StageAngle = 0.f;
	for (int i = 0; i < STAGE_HEIGHT; i++)
	{
		for (int j = 0; j < STAGE_WIDTH; j++)
		{
			m_SelectStage.Data[i][j] = 0;
		}
	}
}

void GamePlayManager::NextStage()
{
	InitializeEvent();
	if (!m_IsFirstStage)
	{
		m_StageNum++;
	}
	m_IsFirstStage = false;
}
