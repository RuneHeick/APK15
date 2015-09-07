#pragma once 
#include "MyArray.h"

template<T, U>
class MyIterator : public std::iterator<std::forward_iterator_tag, T>
{
	T* p;
public:
	MyIterator(MyArray<T, U>& x) :p(x.begin()) {}

	MyIterator(const MyIterator& mit) : p(mit.p) {}

	MyIterator& operator++() { p++ ; return *this; }
	MyIterator operator++(T) { MyIterator tmp(*this); operator++(); return tmp; }

	MyIterator& operator--() { p--; return *this; }
	MyIterator operator--(T) { MyIterator tmp(*this); operator--(); return tmp; }

	MyIterator& operator+(int i) { p+= i; return *this; }
	MyIterator& operator-(int i) { p -= i; return *this; }


	bool operator==(const MyIterator& rhs) { return p == rhs.p; }
	bool operator!=(const MyIterator& rhs) { return p != rhs.p; }
	int& operator*() { return *p; }
};