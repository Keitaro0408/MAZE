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

class Player : public GameObjectBase
{
public:
	Player();
	virtual ~Player();

	void Update() override;
	void Draw() override;

private:
	/**
	 * スタートの座標を設定する
	 */
	void SetStartPos();

	Lib::UniquePtr<Lib::Vertex2D>		  m_pVertex;
	Lib::UniquePtr<Lib::AnimUvController> m_pLeftAnimation;
	Lib::UniquePtr<Lib::AnimUvController> m_pRightAnimation;
	Lib::VECTOR2						  m_Pos;
	bool								  m_IsRightDir; //!< 右を向いていたらtrue
	float								  m_MoveSpeed;

};


#endif
