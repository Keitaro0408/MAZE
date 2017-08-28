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

	/**
	 * タスクの実行等に使用されるオブジェクトの基底クラス
	 */
	class ObjectBase
	{
	public:
		ObjectBase() = default;

		virtual ~ObjectBase() = default;

		virtual void Update() = 0;
		virtual void Draw() = 0;

	protected:
		UpdateTask* m_pUpdateTask;
		DrawTask*   m_pDrawTask;

	};
}


#endif
