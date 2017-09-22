/**
 * @file   DoorEventListener.h
 * @brief  DoorEventListenerクラスのヘッダファイル
 * @author kotani
 */
#ifndef COIN_EVENT_LISTENER_H
#define COIN_EVENT_LISTENER_H
#include "Event\EventListenerBase.h"

class Door;

class DoorEventListener : Lib::EventListenerBase
{
public:
	DoorEventListener(Door* _door);
	virtual ~DoorEventListener(){};

	void OnEvent(Lib::Event& _event) override;

private:
	Door* m_pDoor;

};


#endif
