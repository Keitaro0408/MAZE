/**
 * @file   GamePlayManager.cpp
 * @brief  GamePlayManagerクラスの実装
 * @author kotani
 */
#include "GamePlayManager.h"
#include <string>


GamePlayManager::GamePlayManager() :
m_StageNum(11)
{
	for (int i = 0; i < STAGE_HEIGHT; i++)
	{
		for (int j = 0; j < STAGE_WIDTH; j++)
		{
			m_SelectStage.Data[i][j] = 0;
		}
	}
}


void GamePlayManager::StageLoad()
{
	std::string m_FileName;
	m_FileName = "Resource\\Stage\\" + std::to_string(m_StageNum) + ".csv";

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