/*
 * Contains.h
 *
 *  Created on: Sep 16, 2015
 *      Author: stud
 */

#ifndef CONTAINS_H_
#define CONTAINS_H_

#include <boost/mpl/if.hpp>

#include "Typelist.h"
#include "IsSame.h"



template<class TL, typename T>
struct Contains {
	enum { result = (IsSame<T, typename TL::First>::value ? 1 : Contains<typename TL::Rest, T>::result )};
};

template<typename T>
struct Contains<NullType, T> {
	enum { result = 0 };
};

#endif /* CONTAINS_H_ */
