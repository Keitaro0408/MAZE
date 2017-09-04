/**
 * @file   Door.h
 * @brief  Doorクラスのヘッダファイル
 * @author kotani
 */
#ifndef DOOR_H
#define DOOR_H
#include "..\..\GameObjectBase.h"
#include "..\..\..\..\..\GamePlayManager\GamePlayManager.h"
#include "Vertex2D\Vertex2D.h"
#include "Animation\AnimUvController.h"
#include "SmartPointer\UniquePtr.h"

class Door : public GameObjectBase
{
public:
	Door();
	~Door();

	void Update() override;
	void Draw() override;

private:
	void InitializeEvent();

	GamePlayManager::SELECT_STAGE		  m_Stage;
	Lib::UniquePtr<Lib::Vertex2D>		  m_pVertex;
	Lib::UniquePtr<Lib::AnimUvController> m_pStartDoorUv;
	Lib::UniquePtr<Lib::AnimUvController> m_pGoalDoorUv;

};


#endif
