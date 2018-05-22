#ifndef __CONST_ITERATOR__
#define __CONST_ITERATOR__

#include "base_iterator.hpp"

template<class T>
class Set;

template<class T>
class Const_iterator : public Base_iterator<T> {
public:
	friend class Set<T>;

	Const_iterator(const Const_iterator<T>& it);

	const T operator*();
	const T* operator->();

protected:
	Const_iterator(T *p);
};

template<class T>
Const_iterator<T>::Const_iterator(T *p)
	:Base_iterator<T>::Base_iterator(p)
{
}

template<class T>
Const_iterator<T>::Const_iterator(const Const_iterator<T>& it)
	:Base_iterator<T>::Base_iterator(it.ptr)
{
}


template<class T>
const T Const_iterator<T>::operator*()
{
	return *this->ptr;
}

template<class T>
const T* Const_iterator<T>::operator->()
{
	return this->ptr;
}

#endif