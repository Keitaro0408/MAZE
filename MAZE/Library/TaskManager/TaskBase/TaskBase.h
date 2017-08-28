/**
 * @file   TaskBase.h
 * @brief  TaskBaseクラスのヘッダファイル
 * @author kotani
 */
#ifndef TASKBASE_H
#define TASKBASE_H
#include <string>
#include "../../ObjectBase/ObjectBase.h"

namespace Lib
{
	/**
	 * Taskの基底クラス
	 */
	class TaskBase
	{
	public:
		/**
		 * コンストラクタ
		 * @param[in] _priority 優先レベル
		 */
		TaskBase(int _priority = 0);
		
		/**
		 * デストラクタ
		 */
		virtual ~TaskBase();

		/**
		 * タスクを実行
		 */
		virtual void Execute() = 0;

		/**
		 * 優先レベルのセット
		 * @param[in] 高い方が後に実行される 
		 */
		inline void SetPriority(int _priority)
		{
			m_Priority = _priority;
		}

		/**
		 * タスクにIDを取得する(現在は使っていない)
		 */
		inline int GetTaskId() const
		{
			return m_TaskId;
		}

		/**
		 * 使用するオブジェクトタスクをセット
		 */
		void SetObject(ObjectBase* _object)
		{
			m_pObject = _object;
		}

		inline bool operator > (const TaskBase& _task) const
		{
			return (m_Priority > _task.m_Priority);
		}

		inline bool operator < (const TaskBase& _task) const
		{
			return (m_Priority < _task.m_Priority);
		}

	protected:
		ObjectBase* m_pObject;

	private:
		static int m_TaskMaxNum;
		int		   m_TaskId;
		int		   m_Priority;

	};
}


#endif
