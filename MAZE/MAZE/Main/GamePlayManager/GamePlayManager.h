/**
 * @file   GamePlayManager.h
 * @brief  GamePlayManagerクラスのヘッダファイル
 * @author kotani
 */
#ifndef GAMEPLAYMANAGER_H
#define GAMEPLAYMANAGER_H
#include "Singleton.h"
#include "..\GameScene\GameObjectManager\GameObjectBase\Stage\Stage.h"

/**
 * ゲームの状態を管理するクラス
 */
class GamePlayManager
{
	friend Lib::Singleton<GamePlayManager>;
public:
	struct SELECT_STAGE
	{
		int Data[STAGE_HEIGHT][STAGE_WIDTH];
	};

	void SetStageNum(int _selectNum)
	{
		m_StageNum = _selectNum;
	}

	int GetStageNum()
	{
		return m_StageNum;
	}

	SELECT_STAGE GetSelectStage()
	{
		return m_SelectStage;
	}

	void SetSelectStage(const SELECT_STAGE& _stage)
	{
		m_SelectStage = _stage;
	}

	void SetIsSpin(bool _isSpin)
	{
		m_IsSpin = _isSpin;
	}

	bool GetIsSpin()
	{
		return m_IsSpin;
	}

	float GetStageAngle()
	{
		return m_StageAngle;
	}

	SELECT_STAGE LeftSpin(const SELECT_STAGE& _stage);
	SELECT_STAGE RightSpin(const SELECT_STAGE& _stage);

	bool CheckEnableGimmick(int _x, int _y);
	void StageLoad();
	void InitializeEvent();

private:
	GamePlayManager();
	~GamePlayManager() = default;

	int			 m_StageNum;    //!< 選択されたステージ
	bool		 m_IsPause;     //!< 停止中か?
	bool		 m_IsSpin;      //!< 停止中か?
	float        m_StageAngle;  //!< ステージ角度
	SELECT_STAGE m_SelectStage; //!< 選択されたステージデータ

};


#endif
