/**
* @file   DrawSetupTask.h
* @brief  DrawSetupTaskクラスのヘッダファイル
* @author kotani
*/
#ifndef DRAW_SETUP_TASK_H
#define DRAW_SETUP_TASK_H

#include "../TaskBase.h"

namespace Lib
{
	/**
	* 描画前処理のタスククラス
	*/
	class DrawSetupTask : public TaskBase
	{
	public:
		/**
		* コンストラクタ
		* @param[in] _priority 優先レベル
		*/
		DrawSetupTask(int _priority = 0) :
			TaskBase(_priority)
		{}

		/**
		* デストラクタ
		*/
		virtual ~DrawSetupTask(){};

		/**
		* 実行
		*/
		void Execute() override
		{
			m_pObject->DrawSetup();
		}

	};
}


#endif
