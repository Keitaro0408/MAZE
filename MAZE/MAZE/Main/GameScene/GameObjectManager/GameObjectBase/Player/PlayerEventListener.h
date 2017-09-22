/**
 * @file   PlayerEventListener.h
 * @brief  PlayerEventListenerクラスのヘッダファイル
 * @author kotani
 */
#ifndef PLAYER_EVENT_LISTENER_H
#define PLAYER_EVENT_LISTENER_H
#include "Event\EventListenerBase.h"
class Player;

class PlayerEventListener : public Lib::EventListenerBase
{
public:
	PlayerEventListener(Player* _player);
	virtual ~PlayerEventListener(){}

	void OnEvent(Lib::Event& _event) override;

private:
	Player* m_pPlayer;

};


#endif
