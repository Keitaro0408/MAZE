/**
 * @file   EventManager.h
 * @brief  EventManagerクラスのヘッダファイル
 * @author kotani
 */
#ifndef EVENTMANAGER_H
#define EVENTMANAGER_H

#include <list>
#include <functional>
#include "..\Singleton.h"
#include "Event.h"

namespace Lib
{
	class EventListenerBase;

	/**
	 * コールバックのイベントを管理する
	 */
	class EventManager
	{
		friend Singleton<EventManager>;
	public:
		/**
		 * イベントの追加
		 * @param[in] _pEventListnerBaseList イベント待受クラス
		 */
		void AddListener(EventListenerBase* _pEventListenerBaseList);

		/**
		 * イベントを送信する
		 * @param[in] _pEvent イベントクラス
		 */
		void SendEvent(Event& _pEvent);

		/**
		 * キューにイベントをセットする
		 * @param[in] _pEvent イベントクラス
		 */
		void AddQueueEvent(Event* _pEvent);

		/**
		 * キューに登録しているイベントを実行して、キューを削除する。
		 */
		void Execute();

		/**
		 * 登録されている全てのイベントをリストから削除する
		 */
		void AllEventClear();

	private:
		EventManager(){};
		~EventManager(){};

		std::list<EventListenerBase*> m_pEventListenerBase;
		std::list<Event>			  m_pEventQueueList;
	};
}


#endif
