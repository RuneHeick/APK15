// Ex2sharedpointer.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "SharedPtr.h"
#include "DummyFile.h"
#include <iostream>

using namespace std; 

void Del(int* ptr)
{
	delete ptr;
}


void Test1_1()
{
	SharedPtr<int> ptr(new int(5));
	
	{
		SharedPtr<int> ptr_2 = ptr;

		ptr = ptr;

		cout << "count is: " << ptr.count() << " and " << ptr_2.count() << endl;
		cout << "Value is: " << *ptr << " and " << *ptr_2 << endl;
		{
			SharedPtr<int> ptr_3(new int(10));

			ptr = ptr_3; 
			cout << "count is: " << ptr.count() << " and " << ptr_3.count() << endl;
			cout << "Value is: " << *ptr << " and " << *ptr_3 << endl;
		}

		cout << "count is: " << ptr.count() << " and " << ptr_2.count() << endl;
		cout << "Value is: " << *ptr << " and " << *ptr_2 << endl;
	}

	cout << "count is: " << ptr.count() << endl;

}




void Test2_2_3()
{
	SharedPtr<ConfigFile> ptr(new ConfigFile());
	SharedPtr<ConfigFile> ptr2 = ptr;

	if (ptr == ptr2)
	{
		cout << "they are the same" << endl; 
	}

}



void Test2_2_4()
{
	

	
}

int _tmain(int argc, _TCHAR* argv[])
{
	Test1_1();
	Test2_2_3();
	Test2_2_4();
	getchar();
	return 0;
}

