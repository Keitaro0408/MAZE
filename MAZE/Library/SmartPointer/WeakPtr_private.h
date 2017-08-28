#ifndef WEAK_PTR_PRIVATE_H
#define WEAK_PTR_PRIVATE_H

template<typename Type>
WeakPtr<Type>::WeakPtr(Type* _instance) :
SmartPtr(_instance),
m_pWeakCount(nullptr)
{
}

template<typename Type>
WeakPtr<Type>::WeakPtr() :
SmartPtr(nullptr),
m_pWeakCount(nullptr)
{
}

template<typename Type>
WeakPtr<Type>::~WeakPtr()
{
	if (m_pWeakCount != nullptr)
	{
		--(*m_pWeakCount);
		if (*m_pWeakCount == 0)
		{
			SafeDelete(m_pWeakCount);
			SafeDelete(m_pRefCount);
		}
	}
}

template<typename Type>
bool WeakPtr<Type>::IsExist()
{
	return m_pWeakCount != nullptr;
}

template<typename Type>
WeakPtr<Type>& WeakPtr<Type>::operator=(const SharedPtr<Type>& _obj)
{
	m_pWeakCount = _obj.m_pWeakCount;
	m_pRefCount = _obj.m_pRefCount;
	++(*m_pWeakCount);
	m_pInstance = _obj.m_pInstance;

	return *this;
}


#endif
