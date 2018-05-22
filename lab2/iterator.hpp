#ifndef __ITERATOR__
#define __ITERATOR__

#include "base_iterator.hpp"

template<class T>
class Set;

template<class T>
class Iterator : public Base_iterator<T> {
public:
	friend class Set<T>;
	
	Iterator(const Iterator<T>& it);

	T& operator*();
	T* operator->();

protected:
	Iterator(T *p);
};

template<class T>
Iterator<T>::Iterator(T *p)
	:Base_iterator<T>::Base_iterator(p)
{
}

template<class T>
Iterator<T>::Iterator(const Iterator<T>& it)
	:Base_iterator<T>::Base_iterator(it.ptr)
{
}


template<class T>
T& Iterator<T>::operator*()
{
	return *this->ptr;
}

template<class T>
T* Iterator<T>::operator->()
{
	return this->ptr;
}

#endif