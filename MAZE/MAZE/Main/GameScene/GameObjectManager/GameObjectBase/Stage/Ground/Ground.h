﻿/**
 * @file   Ground.h
 * @brief  Groundクラスのヘッダファイル
 * @author kotani
 */
#ifndef GROUND_H
#define GROUND_H
#include "..\..\GameObjectBase.h"
#include "..\..\..\..\..\GamePlayManager\GamePlayManager.h"
#include "Vertex2D\Vertex2D.h"
#include "Animation\AnimUvController.h"
#include "SmartPointer\UniquePtr.h"

class Ground : public GameObjectBase
{
public:

	Ground();
	virtual ~Ground();

	void Update() override;
	void Draw() override;

private:
	enum COLOR
	{
		GREEN,
		BLUE,
		GREY
	};
	GamePlayManager::SELECT_STAGE		  m_Stage;
	Lib::UniquePtr<Lib::Vertex2D>		  m_pVertex;
	Lib::UniquePtr<Lib::AnimUvController> m_pGreenUv;
	Lib::UniquePtr<Lib::AnimUvController> m_pBlueUv;
	Lib::UniquePtr<Lib::AnimUvController> m_pGreyUv;

};


#endif
