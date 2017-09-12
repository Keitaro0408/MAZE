/**
 * @file   SceneManager.h
 * @brief  SceneManagerクラスのヘッダファイル(未実装)
 * @author kotani
 */
#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H
#include <map>
#include <string>
#include "../Singleton.h"
#include "../Application/ApplicationBase.h"

namespace Lib
{
	class SceneBase;

	/**
	 * ゲームのシーン遷移を管理するクラス
	 */
	class SceneManager
	{
		friend Singleton<SceneManager>;
		friend ApplicationBase;
	public:
		/**
		 * Sceneの追加
		 * @param[in] _pScene 追加するSceneのポインタ
		 */
		void AddScene(SceneBase* _pScene);

		/**
		 * Sceneの削除
		 * @param[in] _sceneName 削除するSceneの名前
		 */
		void RemoveScene(std::string _sceneName);


		/**
		 * Sceneの変更
		 * @param[in] _sceneName 変更先のSceneの名前
		 */
		void ChangeScene(std::string _sceneName);

		/**
		 * ゲームを終了させる
		 */
		void GameEnd()
		{
			m_IsGameEnd = true;
		}

	private:
		SceneManager();

		~SceneManager();

		/**
		 * SceneManagerの実行
		 * @return 終了するときにtrueになる
		 */
		bool Execute();

		/**
		 * SceneManagerの状態
		 */
		enum State
		{
			SCENE_CREATE,	//!< シーンの生成状態
			SCENE_PROC,		//!< シーンの処理状態		
			SCENE_RELEASE	//!< シーンの解放状態
		};

		/**
		 * SceneManagerクラスの制御関数
		 */
		void Update();

		/**
		 * SceneManagerクラスの描画関数
		 */
		void Draw();

		State							  m_State;
		SceneBase*						  m_pCurrentScene; //!< 現在のシーン
		std::string						  m_CurrentSceneName;
		std::map<std::string, SceneBase*> m_pSceneList;
		bool							  m_IsGameEnd;
	};
}


#endif
