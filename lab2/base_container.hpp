#ifndef __BASE_CONTAINER__
#define __BASE_CONTAINER__

class Base_container {
public:
	Base_container();
	Base_container(size_t size);
	virtual ~Base_container();

	size_t size() const;
protected:
	size_t _size;
};

Base_container::Base_container()
:_size(0)
{}

Base_container::Base_container(size_t size)
:_size(size)
{}

Base_container::~Base_container()
{
	this->_size = 0;
}

size_t Base_container::size() const
{
	std::cout << "Base_container::size() : returned value:  " << this->_size << "\n";
	return this->_size;
}

#endif