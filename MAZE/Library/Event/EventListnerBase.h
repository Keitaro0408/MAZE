/**
 * @file   EventListnerBase.h
 * @brief  EventListnerBaseクラスのヘッダファイル
 * @author kotani
 */
#ifndef EVENT_H
#define EVENT_H

namespace Lib
{
	class EventManager;
	/**
	 * クラスとして継承させる場合に使う基底クラス
	 */
	class EventListnerBase
	{
		friend class EventManager;
	public:
		EventListnerBase();
		~EventListnerBase();

	private:
		virtual void Action() = 0;

	};
}


#endif
