/**
 * @file   Ladder.h
 * @brief  Ladderクラスのヘッダファイル
 * @author kotani
 */
#ifndef LADDER_H
#define LADDER_H
#include "..\..\GameObjectBase.h"
#include "..\..\..\..\..\GamePlayManager\GamePlayManager.h"
#include "Vertex2D\Vertex2D.h"
#include "Animation\AnimUvController.h"
#include "SmartPointer\UniquePtr.h"

class Ladder : public GameObjectBase
{
public:
	Ladder();
	virtual ~Ladder();

	void Update() override;
	void Draw() override;

private:
	GamePlayManager::SELECT_STAGE		  m_Stage;
	Lib::UniquePtr<Lib::Vertex2D>		  m_pVertex;
	Lib::UniquePtr<Lib::AnimUvController> m_pMiddleLadderUv;
	Lib::UniquePtr<Lib::AnimUvController> m_pEndLadderUv;
};


#endif
