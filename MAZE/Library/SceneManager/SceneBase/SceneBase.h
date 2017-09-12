/**
 * @file   SceneBase.h
 * @brief  SceneBaseクラスのヘッダファイル(未実装)
 * @author kotani
 */
#ifndef SCENEBASE_H
#define SCENEBASE_H
#include <string>

namespace Lib
{
	class SceneBase
	{
	public:
		/**
		 * コンストラクタ
		 * @param[in] _sceneName Sceneの名前
		 */
		SceneBase(std::string _sceneName);

		/**
		 * デストラクタ
		 */
		virtual ~SceneBase() = default;
	
		/**
		 * 初期化処理
		 * シーンが遷移した最初に呼ばれる
		 */
		virtual bool Initialize() = 0;

		/**
		 * 終了処理
		 * シーンが遷移する前に呼ばれる
		 */
		virtual void Finalize() = 0;

		/**
		 * 実行処理
		 */
		virtual void Execute() = 0;

		/**
		 * Sceneの名前の取得
		 * @return Sceneの名前
		 */
		std::string GetSceneName()
		{
			return m_SceneName;
		}

	private:
		std::string m_SceneName;

	};
}

#endif
