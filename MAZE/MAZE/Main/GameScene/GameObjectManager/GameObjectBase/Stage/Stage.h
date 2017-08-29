/**
 * @file   Stage.h
 * @brief  Stageクラスのヘッダファイル
 * @author kotani
 */
#ifndef STAGE_H
#define STAGE_H
#define STAGE_WIDTH 14
#define STAGE_HEIGHT 14
#include "..\GameObjectBase.h"
#include "Ground\Ground.h"

class Stage : public GameObjectBase
{
public:
	Stage();
	~Stage();

	void Update() override;
	void Draw() override;

private:
	Ground* m_pGround;

};


#endif
