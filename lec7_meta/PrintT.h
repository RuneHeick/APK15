/*
 * PrintT.h
 *
 *  Created on: Sep 16, 2015
 *      Author: stud
 */

#ifndef PRINTT_H_
#define PRINTT_H_

#include <iostream>
#include <typeinfo>

#include "Typelist.h"

template<typename TL>
struct PrintT {
	static void print() {
		std::cout << typeid(typename TL::First).name() << std::endl;
		PrintT<typename TL::Rest>::print();
	}
};

template<>
struct PrintT<NullType> {
	static void print() {
		std::cout << "NullType" << std::endl;
	}
};



#endif /* PRINTT_H_ */
