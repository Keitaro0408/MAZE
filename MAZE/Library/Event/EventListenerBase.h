/**
 * @file   EventListenerBase.h
 * @brief  EventListenerBaseクラスのヘッダファイル
 * @author kotani
 */
#ifndef EVENT_LISTENER_BASE
#define EVENT_LISTENER_BASE
#include "Event.h"

namespace Lib
{
	class EventListenerBase
	{
		friend class EventManager;
	public:
		EventListenerBase(){}
		virtual ~EventListenerBase(){}

	protected:
		typedef size_t StringId;
		virtual void OnEvent(Event& _event) = 0;

	};
}
#endif