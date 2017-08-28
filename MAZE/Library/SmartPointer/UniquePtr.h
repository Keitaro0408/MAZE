/**
 * @file   UniquePtr.h
 * @brief  UniquePtrクラスのヘッダファイル
 * @author kotani
 */
#ifndef UNIQUE_PTR_H
#define UNIQUE_PTR_H
#include "SmartPtr.h"

namespace Lib
{
	template<typename Type>
	/**
	 * 所有権が1つしか持てない様に振る舞うスマートポインタ
	 * カスタムデリータと配列の生成の実装予定
	 */
	class UniquePtr : public SmartPtr<Type>
	{
	public:
		UniquePtr(Type* _type);
		UniquePtr();

		virtual ~UniquePtr();

		/**
		 * メモリを解放する
		 */
		void Reset();

		/**
		 * メモリを解放した後に引数のポインタを扱う
		 * @param[in] _type 新しく管理するポインタ
		 */
		void Reset(Type* _type);

		/**
		 * メンバにアクセスする
		 */
		Type* operator->() const;

		/**
		 * 直接代入の禁止 
		 */
		UniquePtr& operator=(const UniquePtr&) = delete;

		UniquePtr& operator=(UniquePtr<Type>&& _obj)
		{
			this->m_pInstance = _obj.m_pInstance;
			_obj.m_pInstance = nullptr;
			return *this;
		}

	};

	template<typename Type, class... Args>
	UniquePtr<Type> MakeUnique(Args&&... args)
	{
		return UniquePtr<Type>(new Type(std::forward<Args>(args)...));
	}

#include "UniquePtr_private.h"
}

#endif
