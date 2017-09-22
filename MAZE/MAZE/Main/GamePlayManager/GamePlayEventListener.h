/**
 * @file   GamePlayEventListener.h
 * @brief  GamePlayEventListenerクラスのヘッダファイル
 * @author kotani
 */
#ifndef COIN_EVENT_LISTENER_H
#define COIN_EVENT_LISTENER_H
#include "Event\EventListenerBase.h"

class GamePlayEventListener : Lib::EventListenerBase
{
public:
	GamePlayEventListener();
	virtual ~GamePlayEventListener(){};

	void OnEvent(Lib::Event& _event) override;

private:

};


#endif
