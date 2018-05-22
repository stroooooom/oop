#include "set.hpp"

#include <iostream>

typedef struct {
	int x, y;
} Point;

using namespace std;


std::ostream& operator<<(std::ostream& os, const Set<Point>& set)
{
	auto iter = set.get_iter();
	for (int i = 0; i < set.power(); ++i)
	{
		os << "(" << iter->x << ", " << iter->y << ") ";
		++iter;
	}
	cout << endl;

	return os;
}

int main()
{
	Point p0 = {0, 0};

	Point p1 = {1, 2};
	Point p2 = {3, 4};
	Point p3 = {4, 5};

	Point p4 = {6, 6};
	Point p5 = {7, 7};
	Point p6 = {8, 8};


	// Set<Point> set11 = {p1, p2};		// 	TEST FOR: Set(std::initializer_list<T> list)

	// Set<Point> set22;				//	TEST FOR:
	// set22 = move(set11);				//	Set<T>& operator=(Set&& other)

	// cout << set11;
	// cout << set22;


	// Set<Point> set0 = {p1, p2, p3, p1};		//	TEST FOR: Set(std::initializer_list<T> list)

	// cout << set0;


	// auto it = set0.get_iter();
	// p6 = *it;
	// Point new_point = *it;

	// cout << new_point.x;

	Set<Point> set1, set2, set3;

	set1.append(p1);					//	TEST FOR: append(const T& element)

	set1.append(p2);
	set1.append(p3);

	set2.append(p4);
	set2.append(p5);
	set2.append(p6);

	set3.append(p1);
	set3.append(p2);
	set3.append(p4);

	cout<<"set1:\n"; cout<<set1;
	cout<<"set2:\n"; cout<<set2;
	cout<<"set3:\n"; cout<<set3;
	cout<<endl;

	set1.add(set2);
	cout<<"set1.add(set2):\n"; cout<<set1;

//	set1.subtract(set2);
//	cout<<"set1.subtract(set2):\n"; cout<<set1;

	set1.intersect(set2);
	cout<<"set1.intersect(set2):\n"; cout<<set1;

	Set<Point> new_set(set1);
	cout<< "new_set(set1):\n" << new_set;

	set1.append(p0);
	cout << "set1.append(p0):\n" << set1;

	cout << "new_set:\n" << new_set;

	Set<Point> copy;
	copy = set1;
	cout << "copy_set (set1):\n" << copy;

	cout << "set1:\n" << set1;

 	return 0;
}