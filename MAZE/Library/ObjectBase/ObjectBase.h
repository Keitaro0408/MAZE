/**
 * @file   ObjectBase.h
 * @brief  ObjectBaseクラスのヘッダファイル
 * @author kotani
 */
#ifndef OBJECT_BASE_H
#define OBJECT_BASE_H
#include "../Helper/Helper.h"

namespace Lib
{
	class UpdateTask;
	class DrawTask;
	class DrawSetupTask;

	/**
	 * タスクの実行等に使用されるオブジェクトの基底クラス
	 */
	class ObjectBase
	{
	public:
		ObjectBase() = default;

		virtual ~ObjectBase() = default;

		/**
		 * 更新処理
		 */
		virtual void Update() = 0;

		/**
		 * 描画前処理
		 */
		virtual void DrawSetup(){};

		/**
		 * 描画処理
		 */
		virtual void Draw() = 0;

		/**
		 * タスクの初期化
		 * @param[in] _updatePriority Updateの順番高い方が後に実行される
		 * @param[in] _drawPriority Drawの順番高い方が後に実行される
		 * @param[in] _drawSetupPriority DrawSetupの順番高い方が後に実行される
		 */
		void InitializeTask(int _updatePriority = 0, int _drawPriority = 0, int _drawSetupPriority = 0);

		/**
		 * タスクの解放処理
		 */
		void FinalizeTask();

	protected:
		UpdateTask*	   m_pUpdateTask;
		DrawTask*	   m_pDrawTask;
		DrawSetupTask* m_pDrawSetupTask;

	};
}


#endif
