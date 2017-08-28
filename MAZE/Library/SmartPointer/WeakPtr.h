/**
 * @file   WeakPtr.h
 * @brief  WeakPtrクラスのヘッダファイル
 * @author kotani
 */
#ifndef WEAK_PTR_H
#define WEAK_PTR_H
#include "../Helper/Helper.h"
#include "SharedPtr.h"

namespace Lib
{
	template<typename Type>
	/**
	 * sharedPtrを使う時に循環参照を防止するスマートポインタ
	 */
	class WeakPtr : public SmartPtr<Type>
	{
	public:
		WeakPtr(Type* _instance);
		WeakPtr();

		virtual ~WeakPtr();

		/**
		 * ポインタが存在しているか?
		 * @return 存在していたらtrue
		 */
		bool IsExist();

		WeakPtr<Type>& operator=(const SharedPtr<Type>&);

	private:
		unsigned int* m_pRefCount;
		unsigned int* m_pWeakCount;
	};

#include "WeakPtr_private.h"
}


#endif
