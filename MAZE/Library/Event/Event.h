/**
 * @file   Event.h
 * @brief  Eventクラスのヘッダファイル
 * @author kotani
 */
#ifndef EVENT_H
#define EVENT_H
#include <functional>
#include <map>

namespace Lib
{
	struct Event
	{
		typedef size_t StringId;
		Event(char* _eventName)
		{
			eventName = std::hash<char*>()(_eventName);
		}
		union Data
		{
			int   m_Int;
			float m_Float;
			bool  m_Bool;
		};

		std::map<StringId, Data> eventData; //!< 格納されているデータ
		StringId eventName; //!< イベントのハッシュ

	};
}


#endif
