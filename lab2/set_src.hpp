#ifndef __SET_SRC__
#define __SET_SRC__

#include "set.hpp"
#include "iterator.hpp"
#include "const_iterator.hpp"

#include "allocator.hpp"

#define EXTRA_MEM 128

// CONSTRUCTORS
template<class T>
Set<T>::Set()
	:Base_container::Base_container(0), _data(nullptr), _capacity(0)
{
}

template<class T>
Set<T>::Set(const Set<T>& s)
	:Base_container::Base_container(0), _data(nullptr), _capacity(0)
{
	Allocator<T>::alloc_memory(&(this->_data), this->_capacity, EXTRA_MEM);
	this->_capacity = EXTRA_MEM;
	this->_size = s._size;
	memcpy(this->_data, s._data, sizeof(T) * s._size);
}

template<class T>
Set<T>::Set(Set&& other)
	:Base_container::Base_container(other._size), _data(other._data)
{
	other._size = 0;
	other._data = nullptr;

	other._capacity = 0;
}

template<class T>
Set<T>::Set(std::initializer_list<T> list)
	:Base_container::Base_container(0), _data(nullptr), _capacity(0)
{
	for (auto iter = list.begin(); iter != list.end(); iter++)
	{
		if (!this->ismember(*iter))
		{
			this->append(*iter);
		}
	}
}


// OPERATIONS WITH T& ARG
template<class T>
Set<T>& Set<T>::append(const T& element)
{
	if (!this->ismember(element))
	{
		if (this->_size >= this->_capacity)
		{
			Allocator<T>::alloc_memory(&(this->_data), this->_capacity, this->_capacity + EXTRA_MEM);
			this->_capacity = this->_capacity + EXTRA_MEM;
		}
		this->_data[this->_size++] = element;
	}

	return *this;
}

template<class T>
Set<T>& Set<T>::remove(const T& element)
{
	for (Iterator<T> it = this->ncbegin(); it != this->ncend(); ++it)
	{
		if (memcmp(&(*it), &element, sizeof(T)) == 0)
		{
			Iterator<T> last_el = this->ncend();
			--last_el;

			T tmp = *it;				//
			*it = *last_el;				// swap element we want to remove with last one
			*last_el = tmp;				//

			this->_size--;
			break;
		}
	}

	return *this;
}

template<class T>
bool Set<T>::ismember(const T& element) const
{
	bool state = false;

	for (Iterator<T> it = (*this).ncbegin(); it != (*this).ncend(); ++it)
	{
		if (memcmp(&(*it), &element, sizeof(T)) == 0)
		{
			state = true;
		}
	}
	return state;
}

template<class T>
bool Set<T>::isempty() const
{
	return this->_size == 0;
}


// OPERATIONS WITH Set<T>& ARG
template<class T>
Set<T>& Set<T>::add(const Set<T>& s)
{
	for (Iterator<T> it = s.ncbegin(); it != s.ncend(); ++it)
	{
		this->append(*it);
	}

	return *this;
}

template<class T>
Set<T>& Set<T>::subtract(const Set<T>& s)
{
	for (Iterator<T> it = s.ncbegin(); it != s.ncend(); ++it)
	{
		this->remove(*it);
	}

	return *this;
}

template<class T>
Set<T>& Set<T>::intersect(const Set<T>& s)
{
	Set<T> tmp;

	for (Iterator<T> it = (*this).ncbegin(); it != (*this).ncend(); ++it)
	{
		if (!s.ismember(*it))
		{
			tmp.append(*it);
		}
	}

	this->subtract(tmp);

	return *this;
}


// OPERATORS
template<class  T>
Set<T>& Set<T>::operator=(Set<T>&& other)
{
	if (this != &other)
	{
		this->_size = other._size;
		this->_data = other._data;

		other._size = 0;
		other._data = nullptr;
	}
	return *this;
}

template<class T>
Set<T>& Set<T>::operator=(std::initializer_list<T> list)
{
	Set<T> set = Set(list);
	*this = std::move(set);

	return *this;
}

template<class T>
Set<T>& Set<T>::operator=(const Set<T>& other)
{
	this->~Set();
	Set<T> other_copy(other);
	*this = std::move(other_copy);

	return *this;
}


template<class T>
bool Set<T>::operator<(const T& element) const
{
	return this->ismember(element);
}


template<class T>
Set<T> Set<T>::operator+(const T& element) const
{
	Set<T> sum_set(*this);
	sum_set.append(element);

	return sum_set;
}

template<class T>
Set<T> Set<T>::operator-(const T& element) const
{
	Set<T> sub_set(*this);
	sub_set.remove(element);

	return sub_set;
}

template<class T>
Set<T>& Set<T>::operator+=(const T& element)
{
	this->append(element);

	return *this;
}

template<class T>
Set<T>& Set<T>::operator-=(const T& element)
{
	this->remove(element);

	return *this;
}


template<class T>
Set<T> Set<T>::operator+(const Set<T>& s) const
{
	Set<T> union_set = Set(*this);
	union_set.add(s);

	return union_set;
}

template<class T>
Set<T> Set<T>::operator-(const Set<T>& s) const
{
	Set<T> difference_set = Set(*this);
	difference_set.substract(s);

	return difference_set;
}

template<class T>
Set<T> Set<T>::operator*(const Set<T>& s) const
{
	Set<T> intersection_set = Set(*this);
	intersection_set.intersect(s);

	return intersection_set;
}


template<class T>
Set<T>& Set<T>::operator+=(const Set<T>& s)
{
	this->add(s);
	return this;
}

template<class T>
Set<T>& Set<T>::operator-=(const Set<T>& s)
{
	this->substract(s);
	return this;
}

template<class T>
Set<T>& Set<T>::operator*=(const Set<T>& s)
{
	this->intersect(s);
	return this;
}


template<class T>
std::ostream& operator<<(std::ostream& os, const Set<T>& set)
{
	auto iter = set.get_iter();
	for (int i = 0; i < set.power(); ++i)
	{
		os << *iter << " ";
		++iter;
	}

	return os;
}


// FUNCTIONS RETURNING ITERATORS
template<class T>
Const_iterator<T> Set<T>::get_iter() const
{
	Const_iterator<T> iter( (this->_data) );
	return iter;
}

template<class T>
Iterator<T> Set<T>::ncbegin() const
{
	Iterator<T> iter(this->_data);
	return iter;
}

template<class T>
Iterator<T> Set<T>::ncend() const
{
	Iterator<T> iter(this->_data + this->_size);
	return iter;
}


// CURRENT NUMBER OF ELEMENTS IN SET
template<class T>
size_t Set<T>::power() const
{
	return this->_size;
}

// DESTRUCTOR
template<class T>
Set<T>::~Set()
{
	Allocator<T>::free_memory(this->_data);
	this->_data = nullptr;
	this->_size = 0;
}


#endif