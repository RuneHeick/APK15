/*
 * main.cpp
 *
 *  Created on: Sep 14, 2015
 *      Author: stud
 */

#include <iostream>

#include "binary.h"
#include "Typelist.h"
#include "IsSame.h"
#include "Contains.h"
#include "AtIndex.h"
#include "PrintT.h"

void Test2() {
	std::cout << "Binary <1011 >:: value = " << Binary <1011 >:: value << std::endl;
	/* Should generate a compiler error , but does not! */
}

void Test3_1() {
	typedef TYPELIST1(int) IntTL;
	typedef TYPELIST4(char , int , long , short) MixTL;
}

void Test3_2_1() {
	/* Must be true */
	std::cout << "IsSame <int , int >:: value=" << IsSame <int , int >::value << std::endl;

	/* Must be false */
	std::cout << "IsSame <int , char >:: value=" << IsSame <int , char >::value << std::endl;
}

void Test3_2_2() {
	typedef TYPELIST3(int , char , long) TL;
	/* Must be true */
	std::cout << "Contains <TL , int >:: value=" << Contains <TL , int >::result << std::endl;

	/* Must be false */
	std::cout << "Contains <TL , std::string >:: value=" << Contains <TL , std::string >::result << std::endl;
}

void Test3_2_3() {
	typedef TYPELIST3(long , char , int) TL;
	/* Must be true */
	std::cout << "IsSame <typename AtIndex <TL , 2>::type , int >:: value="
			<< IsSame <typename AtIndex <TL , 2>::Type , int >::value << std::endl;

	/* Must be false */
	std::cout << "IsSame <typename AtIndex <TL , 2>::type , char >:: value=" <<
			IsSame <typename AtIndex <TL , 2>::Type , char >::value << std::endl;
}

class myclass {};

void Test3_2_4() {
	// Print types in typelist.
	typedef TYPELIST4(long , char , int, myclass) TL;
	PrintT<TL>::print();
}

int main()
{
	Test2();
	Test3_1();
	Test3_2_1();
	Test3_2_2();
	Test3_2_3();
	Test3_2_4();

	return 0;
}

