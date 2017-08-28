/**
 * @file   TitleScene.h
 * @brief  TitleSceneクラスのヘッダファイル
 * @author kotani
 */
#ifndef TITLESCENE_H
#define TITLESCENE_H
#include "SceneManager\SceneBase\SceneBase.h"

class TitleScene : public Lib::SceneBase
{
public:
	TitleScene();
	virtual ~TitleScene();

	bool Initialize() override;
	void Finalize() override;

	void Execute() override;

};


#endif
