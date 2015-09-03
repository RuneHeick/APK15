// Ex1templates.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "MyArray.h"
#include "MyFind.h"
#include "myAccumalation.h"
#include <vector>

using namespace std; 


void Test1_1()
{
	const int size(20);

	MyArray<int, size> array;
	array.fill(4); 

	for (size_t i = 0; i < array.size(); i++)
	{
		cout << " In array at element: " << i << " is value: " << array[i] << endl;

		array[i] = i;

		cout << " In array at element: " << i << " is value: " << array[i] << endl;

	}

	auto* ptr = array.begin();
	while (ptr != array.end())
	{
		cout << "value: " << (*ptr) << endl;
		*ptr = 5;
		ptr++;
	}
}

void Test1_2()
{
	const int size(20);
	MyArray<double, size> my;
	my.fill(0); 

	my[3] = 3; // Assuming that 'my' has been appropriately allocated based on MyArray.
		
	cout << "Looking for '3'? " << (myfind(my.begin(), my.end(), 3) !=my.end() ? "found" : "sry no") << endl;

}

void Test1_4()
{
	MyArray <int, 10> myInt; // Array based on 'int'
	MyArray <double, 5 > myDouble; // Array based on 'double'

	myInt.fill(5);
	
	myDouble = myInt; // From an intuitive perspective this should work ,since ints can implicitly be converted to doubles.
	MyArray <int, 10> myInt2(myDouble);

	auto* ptr = myInt2.begin();
	while (ptr != myInt2.end())
	{
		cout << "value: " << (*ptr) << endl;
		*ptr = 5;
		ptr++;
	}


}

void Test2_1()
{
	MyArray <string*, 10> myStrings; // Array based on 'int'

	myStrings[0] = new string("Test at 0");
	myStrings[2] = new string("Test at 2");

	auto* ptr = myStrings.begin();
	while (ptr != myStrings.end())
	{
		if (nullptr != *ptr)
			cout << "value: " << (*(*ptr)).c_str() << endl;
		ptr++;
	}

}

void Test2_2()
{

	MyArray <string*, 10> my;

	my[5] = new std::string("Hello"); // Assuming that my is a MyArray of string pointers
	
	cout << "Looking for 'Hello '? " << (myfind(my.begin(), my.end(),string("Hello")) != my.end() ? "found" : "sry no") << endl;

}


void Test3_1()
{
	const int size(5);
	MyArray<int, size> my;
	my.fill(3);

	auto p = myAccumalation(my);
	cout << "the accumalation is: " << p << endl;

	vector<int> myvector; 
	for (size_t i = 0; i < 5; i++)
	{
		myvector.push_back(3); 
	}
	
	auto i = myAccumalation(myvector);
	cout << "the accumalation is: " << i << endl;


}


int _tmain(int argc, _TCHAR* argv[])
{
	//Test1_1();
	//Test1_2();
	//Test1_4();
	//Test2_1();
	//Test2_2();
	
	Test3_1();

	getchar();
	return 0;
}

