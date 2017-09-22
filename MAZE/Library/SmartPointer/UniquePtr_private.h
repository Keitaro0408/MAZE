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
	if (m_pInstance != nullptr)
	{
		(*m_pDeleter)(m_pInstance);
	}
	m_pInstance = nullptr;
}

template<typename Type>
void UniquePtr<Type>::Reset()
{
	if (m_pInstance != nullptr)
	{
		(*m_pDeleter)(m_pInstance);
	}
	m_pInstance = nullptr;
}

template<typename Type>
void UniquePtr<Type>::Reset(Type* _type)
{
	if (m_pInstance != nullptr)
	{
		(*m_pDeleter)(m_pInstance);
		delete m_pDeleter;
		m_pDeleter = nullptr;
	}
	m_pDeleter = new DeleterImpl<Type>();
	m_pInstance = nullptr;
	m_pInstance = _type;
}

template<typename Type>
Type* UniquePtr<Type>::operator->() const
{
	return m_pInstance;
}



#endif
