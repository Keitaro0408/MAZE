/**
 * @file   NextStageScene.h
 * @brief  NextStageSceneクラスのヘッダファイル
 * @author kotani
 */
#ifndef NEXTSTAGESCENE_H
#define NEXTSTAGESCENE_H
#include "SceneManager\SceneBase\SceneBase.h"

class NextStageScene : public Lib::SceneBase
{
public:
	NextStageScene();
	virtual ~NextStageScene();

	bool Initialize() override;
	void Finalize() override;

	void Execute() override;

};


#endif
