/**
 * @file   Cover.h
 * @brief  Coverクラスのヘッダファイル
 * @author kotani
 */
#ifndef COVER_H
#define COVER_H
#include "..\..\GameObjectBase.h"
#include "..\..\..\..\..\GamePlayManager\GamePlayManager.h"
#include "Vertex2D\Vertex2D.h"
#include "Animation\AnimUvController.h"
#include "SmartPointer\UniquePtr.h"

class Cover : public GameObjectBase
{
public:

	Cover();
	virtual ~Cover();

	void Update() override;
	void Draw() override;

private:
	GamePlayManager::SELECT_STAGE		  m_Stage;
	Lib::UniquePtr<Lib::Vertex2D>		  m_pVertex;
	Lib::UniquePtr<Lib::AnimUvController> m_pUvController;

};


#endif
