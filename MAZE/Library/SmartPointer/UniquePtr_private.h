#ifndef UNIQUE_PTR_PRIVATE_H
#define UNIQUE_PTR_PRIVATE_H

template<typename Type>
UniquePtr<Type>::UniquePtr(Type* _type) :
SmartPtr(_type)
{
}

template<typename Type>
UniquePtr<Type>::UniquePtr()
{
	m_pInstance = nullptr;
}

template<typename Type>
UniquePtr<Type>::~UniquePtr()
{
	delete m_pInstance;
	m_pInstance = nullptr;
}

template<typename Type>
void UniquePtr<Type>::Reset()
{
	delete m_pInstance;
	m_pInstance = nullptr;
}

template<typename Type>
void UniquePtr<Type>::Reset(Type* _type)
{
	delete m_pInstance;
	m_pInstance = nullptr;
	m_pInstance = _type;
}

template<typename Type>
Type* UniquePtr<Type>::operator->() const
{
	return m_pInstance;
}



#endif
