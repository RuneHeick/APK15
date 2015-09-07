#include "MyArray.h"
#include "MyItr.h"


int main()
{
	MyArray<int> a; 
	a.fill(5);

	MyIterator<int, 10> itr(a); 



}