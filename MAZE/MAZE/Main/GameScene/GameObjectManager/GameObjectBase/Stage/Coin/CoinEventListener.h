/**
 * @file   CoinEventListener.h
 * @brief  CoinEventListenerクラスのヘッダファイル
 * @author kotani
 */
#ifndef COIN_EVENT_LISTENER_H
#define COIN_EVENT_LISTENER_H
#include "Event\EventListenerBase.h"

class Coin;

class CoinEventListener : Lib::EventListenerBase
{
public:
	CoinEventListener(Coin* _coin);
	virtual ~CoinEventListener(){};

	void OnEvent(Lib::Event& _event) override;

private:
	Coin* m_pCoin;

};


#endif
