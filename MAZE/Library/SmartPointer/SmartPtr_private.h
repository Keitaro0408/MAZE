#ifndef POINTER_PRIVATE_H
#define POINTER_PRIVATE_H

template<typename Type>
SmartPtr<Type>::SmartPtr(Type* _type) :
m_pInstance(_type),
m_pDeleter(new DeleterImpl<Type>())
{
}

template<typename Type>
SmartPtr<Type>::SmartPtr() :
m_pDeleter(new DeleterImpl<Type>())
{
}

template<typename Type>
SmartPtr<Type>::~SmartPtr()
{
	delete m_pDeleter;
	m_pDeleter = nullptr;
}

template<typename Type>
const Type* SmartPtr<Type>::GetPtr()
{
	return m_pInstance;
}

template<typename Type>
Type* SmartPtr<Type>::operator->() const
{
	return m_pInstance;
}

template<typename Type>
SmartPtr<Type>::operator bool() const
{
	return m_pInstance != nullptr;
}


#endif
