﻿/**
 * @file   TaskManager.cpp
 * @brief  TaskManagerクラスの実装
 * @author kotani
 */
#include "TaskManager.h"
#include "TaskBase/UpdateTask/UpdateTask.h"
#include "TaskBase/DrawTask/DrawTask.h"
#include "../Dx11/DX11Manager.h"


namespace Lib
{
	TaskManager::TaskManager()
	{
	}

	TaskManager::~TaskManager()
	{
	}

	void TaskManager::AddTask(UpdateTask* _updateTask)
	{
		m_UpdateTaskList.push_back(_updateTask);
		m_UpdateTaskList.sort(std::less<>());
	}

	void TaskManager::AddTask(DrawTask* _drawTask)
	{
		m_DrawTaskList.push_back(_drawTask);
		m_DrawTaskList.sort(std::less<>());
	}

	void TaskManager::AllExecute()
	{
		m_UpdateTaskList.sort(std::less<>());
		m_DrawTaskList.sort(std::less<>());

		for (auto itr : m_UpdateTaskList)
		{
			itr->Execute();
		}

		SINGLETON_INSTANCE(DX11Manager).BeginScene();
		for (auto itr : m_DrawTaskList)
		{
			itr->Execute();
		}
		SINGLETON_INSTANCE(DX11Manager).EndScene();
	}

	void TaskManager::RemoveTask(UpdateTask* _task)
	{
		for (auto itr = m_UpdateTaskList.begin(), end = m_UpdateTaskList.end(); itr != end; itr++) 
		{
			if (*itr == _task)
			{
				m_UpdateTaskList.erase(itr);
				return;
			}
		}

	}

	void TaskManager::RemoveTask(DrawTask* _task)
	{
		for (auto itr = m_DrawTaskList.begin(), end = m_DrawTaskList.end(); itr != end; itr++)
		{
			if (*itr == _task)
			{
				m_DrawTaskList.erase(itr);
				return;
			}
		}
	}
}
