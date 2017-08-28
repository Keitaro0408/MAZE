/**
 * @file   SmartPtr.h
 * @brief  SmartPtrクラスのヘッダファイル
 * @author kotani
 */
#ifndef SMARTPOINTER_H
#define SMARTPOINTER_H
//#include "UniquePtr.h"
//#include "SharedPtr.h"
//#include "WeakPtr.h"

#define EMPTY_POINTER(ptr) \
		!ptr


namespace Lib
{

	template<typename Type>
	/**
	 * スマートポインタの基底クラス
	 */
	class SmartPtr
	{
	public:
		SmartPtr(Type* _type);
		SmartPtr();

		virtual ~SmartPtr();

		/**
		 * ポインタを取得する
		 */
		const Type* GetPtr();

		/**
		 * メンバにアクセスする
		 */
		Type* operator->() const;

		Type& operator*()
		{
			return *m_pInstance;
		}

		/**
		 * 中身が空かチェック
		 */
		operator bool() const;

	protected:
		Type* m_pInstance;

	};

#include "SmartPtr_private.h"

}

#endif
