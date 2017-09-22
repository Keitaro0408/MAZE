/**
 * @file   StageEventListener.h
 * @brief  StageEventListenerクラスのヘッダファイル
 * @author kotani
 */
#ifndef STAGE_EVENT_LISTENER_H
#define STAGE_EVENT_LISTENER_H
#include "Event\EventListenerBase.h"
class Stage;

class StageEventListener : public Lib::EventListenerBase
{
public:
	StageEventListener(Stage* _stage);
	virtual ~StageEventListener(){}

	void OnEvent(Lib::Event& _event) override;

private:
	Stage* m_pStage;

};


#endif

