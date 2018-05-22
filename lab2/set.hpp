#ifndef __SET__
#define __SET__	

#include <iostream>
#include <cstdlib>
#include <cstring>
#include <memory>

#include "base_container.hpp"
#include "iterator.hpp"
#include "const_iterator.hpp"

template<class T>
class Set : public Base_container {
public:

	Set();
	explicit Set(const Set<T>& s);
	Set(Set&& other);
	Set(std::initializer_list<T> list);

	~Set();	

	Set<T>& append(const T& element);
	Set<T>& remove(const T& element);

	bool ismember(const T& element) const;
	bool isempty() const;

	Set<T>& add(const Set<T>& s);
	Set<T>& subtract(const Set<T>& s);
	Set<T>& intersect(const Set<T>& s);


	Set<T>& operator=(Set<T>&& other);
	Set<T>& operator=(std::initializer_list<T> list);
	Set<T>& operator=(const Set<T>& other);

	bool operator<(const T& element) const;

	Set<T> operator+(const T& element) const;
	Set<T> operator-(const T& element) const;

	Set<T>& operator+=(const T& element);
	Set<T>& operator-=(const T& element);

	Set<T> operator+(const Set<T>& s) const;
	Set<T> operator-(const Set<T>& s) const;
	Set<T> operator*(const Set<T>& s) const;

	Set<T>& operator+=(const Set<T>& s);
	Set<T>& operator-=(const Set<T>& s);
	Set<T>& operator*=(const Set<T>& s);

	template<class C>
	friend std::ostream& operator<<(std::ostream&, const Set<T>&);


	Const_iterator<T> get_iter() const;
	
	size_t power() const;

private:
	T* _data;
	size_t _capacity;

	Iterator<T> ncbegin() const;
	Iterator<T> ncend() const;

};

#include "set_src.hpp"


#endif