/**
 * @file   GameBackGround.h
 * @brief  GameBackGroundクラスのヘッダファイル
 * @author kotani
 */
#ifndef GAMEBACKGROUND_H
#define GAMEBACKGROUND_H
#include "..\GameObjectBase.h"
#include "SmartPointer\UniquePtr.h"
#include "Vertex2D\Vertex2D.h"

class GameBackGround : public GameObjectBase
{
public:
	GameBackGround();
	virtual ~GameBackGround();

	void Update() override;
	void Draw() override;

private:
	Lib::UniquePtr<Lib::Vertex2D> m_pVertex;
	Lib::VECTOR2				  m_Uv[4];

};


#endif
