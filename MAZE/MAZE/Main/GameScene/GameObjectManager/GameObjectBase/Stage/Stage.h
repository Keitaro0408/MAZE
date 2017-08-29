/**
 * @file   Stage.h
 * @brief  Stageクラスのヘッダファイル
 * @author kotani
 */
#ifndef STAGE_H
#define STAGE_H
#define STAGE_WIDTH 15
#define STAGE_HEIGHT 15
#include "..\GameObjectBase.h"

class Ground;

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
