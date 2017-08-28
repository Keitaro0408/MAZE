/**
 * @file   UpdateTask.h
 * @brief  UpdateTaskクラスのヘッダファイル
 * @author kotani
 */
#ifndef UPDATETASK_H
#define UPDATETASK_H

#include "../TaskBase.h"

namespace Lib
{
	/**
	 * 更新処理のタスククラス
	 */
	class UpdateTask : public TaskBase
	{
	public:
		/**
		 * コンストラクタ
		 * @param[in] _priority 優先レベル
		 */
		UpdateTask(int _priority = 0) :
			TaskBase(_priority)
		{}

		/**
		 * デストラクタ
		 */
		virtual ~UpdateTask(){};

		/**
		 * 実行
		 */
		void Execute() override
		{
			m_pObject->Update();
		}

	};
}


#endif
