/**
 * @file   StageGimmick.h
 * @brief  StageGimmickクラスのヘッダファイル
 * @author kotani
 */
#ifndef STAGE_GIMMICK_H
#define STAGE_GIMMICK_H
#include "../../GameObjectBase.h"

class Gimmick : public GameObjectBase
{
public:
	Gimmick();
	virtual ~Gimmick();

	void Update() override;
	void Draw() override;

};


#endif
