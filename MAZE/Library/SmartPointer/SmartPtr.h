/**
 * @file   SmartPtr.h
 * @brief  SmartPtrクラスのヘッダファイル
 * @author kotani
 */
#ifndef SMARTPOINTER_H
#define SMARTPOINTER_H

#define EMPTY_POINTER(ptr) \
		!ptr


namespace Lib
{
	// 動的削除子のファンクタ.
	class DeleterBase
	{
	public:
		virtual ~DeleterBase(){};
		virtual void operator()(void *p) const = 0;
	};

	template< class T >
	class DeleterImpl
		: public DeleterBase
	{
	public:
		virtual ~DeleterImpl()
		{}

		virtual void operator()(void *p) const
		{
			delete static_cast<T*>(p);
		}
	};


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
		DeleterBase *m_pDeleter;

	};

#include "SmartPtr_private.h"

}

#endif
