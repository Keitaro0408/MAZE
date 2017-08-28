/**
 * @file   Stage.h
 * @brief  Stageクラスのヘッダファイル
 * @author kotani
 */
#ifndef STAGE_H
#define STAGE_H
#include "..\GameObjectBase.h"

class Stage : public GameObjectBase
{
public:
	Stage();
	~Stage();

	void Update() override;
	void Draw() override;

};


#endif
