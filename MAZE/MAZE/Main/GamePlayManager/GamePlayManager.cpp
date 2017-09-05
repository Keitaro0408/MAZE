/**
 * @file   GamePlayManager.cpp
 * @brief  GamePlayManagerクラスの実装
 * @author kotani
 */
#include "GamePlayManager.h"
#include "Event\EventManager.h"
#include <string>


GamePlayManager::GamePlayManager() :
m_StageNum(11),
m_StageAngle(0.f),
m_IsSpin(false)
{
}


void GamePlayManager::StageLoad()
{
	std::string m_FileName;
	m_FileName = "Resource\\GameScene\\Stage\\" + std::to_string(m_StageNum) + ".csv";

	FILE*  fp;
	fopen_s(&fp, m_FileName.c_str(), "r");

	for (int i = 0; i < STAGE_HEIGHT; i++)
	{
		for (int j = 0; j < STAGE_WIDTH; j++)
		{
			fscanf_s(fp, "%d,", &m_SelectStage.Data[i][j]);
		}
	}

	fclose(fp);
}

void GamePlayManager::InitializeEvent()
{
	m_StageAngle = 0.f;
	for (int i = 0; i < STAGE_HEIGHT; i++)
	{
		for (int j = 0; j < STAGE_WIDTH; j++)
		{
			m_SelectStage.Data[i][j] = 0;
		}
	}

	SINGLETON_INSTANCE(Lib::EventManager).AddEvent("LeftSpin", [this]()
	{
		m_IsSpin = true;
		m_StageAngle -= 90.f;

		SELECT_STAGE Stage = m_SelectStage;
		for (int i = 0; i < STAGE_HEIGHT; i++)
		{
			for (int j = 0; j < STAGE_WIDTH; j++)
			{
				m_SelectStage.Data[STAGE_WIDTH - i - 1][j] = Stage.Data[j][i];
			}
		}
	});

	SINGLETON_INSTANCE(Lib::EventManager).AddEvent("RightSpin", [this]()
	{
		m_IsSpin = true;
		m_StageAngle += 90.f;

		SELECT_STAGE Stage = m_SelectStage;
		for (int i = 0; i < STAGE_HEIGHT; i++)
		{
			for (int j = 0; j < STAGE_WIDTH; j++)
			{
				m_SelectStage.Data[i][STAGE_WIDTH - j - 1] = Stage.Data[j][i];
			}
		}
	});

	SINGLETON_INSTANCE(Lib::EventManager).AddEvent("ReversalSpin", [this]()
	{
		m_IsSpin = true;
		m_StageAngle += 180.f;
		SELECT_STAGE Stage = m_SelectStage;

		for (int i = 0; i < STAGE_HEIGHT; i++)
		{
			for (int j = 0; j < STAGE_WIDTH; j++)
			{
				m_SelectStage.Data[i][STAGE_WIDTH - j - 1] = Stage.Data[j][i];
			}
		}

		Stage = m_SelectStage;
		for (int i = 0; i < STAGE_HEIGHT; i++)
		{
			for (int j = 0; j < STAGE_WIDTH; j++)
			{
				m_SelectStage.Data[i][STAGE_WIDTH - j - 1] = Stage.Data[j][i];
			}
		}
	});
}
