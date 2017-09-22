/**
 * @file   TimerUIEventListener.h
 * @brief  TimerUIEventListenerクラスのヘッダファイル
 * @author kotani
 */
#ifndef TIMERUI_EVENT_LISTENER_H
#define TIMERUI_EVENT_LISTENER_H
#include "Event\EventListenerBase.h"
class TimerUI;

class TimerUIEventListener : public Lib::EventListenerBase
{
public:
	TimerUIEventListener(TimerUI* _timerUI);
	virtual ~TimerUIEventListener(){}

	void OnEvent(Lib::Event& _event) override;

private:
	TimerUI* m_pTimerUI;

};


#endif
