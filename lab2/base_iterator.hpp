#ifndef __BASE_BASE_ITERATOR__
#define __BASE_BASE_ITERATOR__

#include <iostream>

template<class T>
class Base_iterator {
public:
	Base_iterator(const Base_iterator& it);
	~Base_iterator();

	Base_iterator<T>& operator=(const Base_iterator& it);

	Base_iterator<T>& operator++();		// prefix increment operator
	Base_iterator<T> operator++(int);	// postfix incement operator

	Base_iterator<T>& operator--();
	Base_iterator<T> operator--(int);

	bool operator==(const Base_iterator& it) const;
	bool operator!=(const Base_iterator& it) const;

protected:
	Base_iterator(T *p);

	T *ptr;
};

template<class T>
Base_iterator<T>::Base_iterator(T *p)
	:ptr(p)
{
}

template<class T>
Base_iterator<T>::Base_iterator(const Base_iterator& it)
	:ptr(it.ptr)
{
}

template<class T>
Base_iterator<T>::~Base_iterator()
{
	this->ptr = nullptr;
}


template <class T>
Base_iterator<T>& Base_iterator<T>::operator=(const Base_iterator<T>& it)
{
	if (this != &it)
	{
		this->ptr = it.ptr;
	}
	return *this;
}


template <class T>
Base_iterator<T>& Base_iterator<T>::operator++()
{
	++this->ptr;
	return *this;
}


template <class T>
Base_iterator<T> Base_iterator<T>::operator++(int)
{
	Base_iterator<T> tmp(*this);
	++*this;
	return tmp;
}


template <class T>
Base_iterator<T>& Base_iterator<T>::operator--()
{
	--this->ptr;
	return *this;
}


template <class T>
Base_iterator<T> Base_iterator<T>::operator--(int)
{
	Base_iterator<T> tmp(*this);
	--*this;
	return tmp;
}

template <class T>
bool Base_iterator<T>::operator==(const Base_iterator<T>& it) const { return ptr == it.ptr; }

template <class T>
bool Base_iterator<T>::operator!=(const Base_iterator<T>& it) const { return ptr != it.ptr; }



#endif