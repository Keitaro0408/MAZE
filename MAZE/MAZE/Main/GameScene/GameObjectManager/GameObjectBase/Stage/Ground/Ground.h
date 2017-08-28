/**
 * @file   Ground.h
 * @brief  Groundクラスのヘッダファイル
 * @author kotani
 */
#ifndef GROUND_H
#ifndef GROUND_H
#include "../../GameObjectBase.h"

class Ground
{
public:
	Ground();
	virtual ~Ground();

	void Update() override;
	void Draw() override;

};


#endif
