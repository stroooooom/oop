#ifndef __ALLOCATOR__
#define __ALLOCATOR__	

#include <iostream>
#include <cstdlib>
#include <cstring>
#include <memory>

#include "base_container.hpp"
#include "iterator.hpp"
#include "const_iterator.hpp"


template<class T>
class Allocator {
public:
	static void alloc_memory(T **data, size_t capacity, size_t new_capacity)
	{
		T *new_data = new T[new_capacity];
		if (capacity > 0)
		{
			memcpy(new_data, *data, sizeof(T) * (capacity));
		}
		delete[] *data;
		*data = new_data;
	}

	static void free_memory(T *data)
	{
		delete[] data;
	}
};

#endif