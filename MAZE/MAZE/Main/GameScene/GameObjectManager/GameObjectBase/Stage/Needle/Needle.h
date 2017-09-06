/**
 * @file   Needle.h
 * @brief  Needleクラスのヘッダファイル
 * @author kotani
 */
#ifndef NEEDLE_H
#define NEEDLE_H
#include "..\..\GameObjectBase.h"
#include "..\..\..\..\..\GamePlayManager\GamePlayManager.h"
#include "Vertex2D\Vertex2D.h"
#include "Animation\AnimUvController.h"
#include "SmartPointer\UniquePtr.h"

class Needle : public GameObjectBase
{
public:
	Needle();
	virtual ~Needle();

	void Update() override;
	void Draw() override;

private:
	GamePlayManager::SELECT_STAGE		  m_Stage;
	Lib::UniquePtr<Lib::Vertex2D>		  m_pVertex;
	Lib::UniquePtr<Lib::AnimUvController> m_pGreenNeedle;
	Lib::UniquePtr<Lib::AnimUvController> m_pBlueNeedle;

};


#endif

