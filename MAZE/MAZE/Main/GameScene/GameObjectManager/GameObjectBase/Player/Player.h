/**
 * @file   Player.h
 * @brief  Playerクラスのヘッダファイル
 * @author kotani
 */
#ifndef PLAYER_H
#define PLAYER_H
#include "..\GameObjectBase.h"

#include "SmartPointer\UniquePtr.h"
#include "Vertex2D\Vertex2D.h"
#include "Animation\AnimUvController.h"
#include <array>

class Player : public GameObjectBase
{
public:
	Player();
	virtual ~Player();

	void Update() override;
	void Draw() override;

private:
	enum SPIN_TYPE
	{
		LEFT_SPIN,
		RIGHT_SPIN,
		REVERSAL_SPIN,
		NON_SPIN
	};

	enum ANIMATION
	{
		WAIT_ANIM,
		LEFT_WALK_ANIM,
		RIGHT_WALK_ANIM,
		LEFT_FALL_ANIM,
		RIGHT_FALL_ANIM,
		LADDER_UP_DOWN_ANIM,
		LADDER_DANGLE,
		DOOR_OPEN,
		ANIM_MAX
	};

	void InitializeEvent();

	/**
	 * アニメーションの読み込み
	 * @param[in] _animEnum 読み込み先のEnum
	 * @param[in] _animName 読み込むアニメーションの名前
	 * @param[in] _setAnimFrame 何フレームでアニメーションを進めるか
	 */
	void LoadAnimation(ANIMATION _animEnum, std::string _animName, int _setAnimFrame);

	/**
	 * スタートの座標を設定する
	 */
	void SetStartPos();

	/**
	 * ステージが回転した時の処理
	 */
	void StageSpinUpdate();

	/**
	 * 移動更新処理
	 */
	void MoveUpdate();

	/**
	 * 当たり判定
	 */
	void CheckCollision();

	/**
	 * 梯子をつかむことが出来るかチェックする
	 * @return 掴むことが出来るならtrue
	 */
	bool CheckGrabLadder();

	/**
	 * ギミックに対しての処理
	 */
	void GimmickControl();

	typedef std::array<Lib::UniquePtr<Lib::AnimUvController>, ANIM_MAX> UvController;

	UvController				  m_pUvController;
	ANIMATION					  m_Animation;
	Lib::UniquePtr<Lib::Vertex2D> m_pVertex;
	Lib::VECTOR2				  m_Pos;
	float						  m_MoveSpeed;
	float						  m_Scale;
	float						  m_AddScaleValue;
	SPIN_TYPE					  m_SpinType;
	float						  m_SpinSpeed;
	float						  m_Angle;
	bool						  m_IsRightDir; //!< 右を向いていたらtrue
	bool						  m_IsSky;
	bool						  m_IsStart;
	bool						  m_UseLadder; //!< 梯子を使っているか?
	bool						  m_IsDangle;  //!< ぶら下がっているか?
	bool						  m_DangleEnable; //!< ぶら下がる事が出来るか
	float						  m_Acceleration;

};


#endif
