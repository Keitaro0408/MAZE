/**
 * @file   CollisionBase.h
 * @brief  CollisionBaseクラスのヘッダファイル(未実装)
 * @author kotani
 */
#ifndef COLLISIONBASE_H
#define COLLISIONBASE_H
#include <string>
#include "../Math/Math.h"

namespace Lib
{
	enum COLLISION_TYPE
	{
		COLLISION_SQUARE,	//矩形で判定を取る
		COLLISION_DISTANCE
	};

	struct SQUARE
	{
		VECTOR2 LeftTop;
		VECTOR2 RightDown;
	};

	class CollisionBase
	{
	public:
		CollisionBase(){};
		virtual ~CollisionBase(){};

		virtual void HitAction(std::string _CollisionName) = 0;

		bool GetIsHitAction()
		{
			return m_isHitAction;
		}

	protected:
		VECTOR2			m_Position;
		COLLISION_TYPE  m_CollisionType;
		SQUARE			m_Square;
		std::string		m_CollisionName; //当たり判定の名前
		bool			m_isHitAction;   //当たった時にActionを行うか
		bool			m_isEnable;		 //判定を行うか

	};
}


#endif
