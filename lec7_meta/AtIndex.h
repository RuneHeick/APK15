/*
 * AtIndex.h
 *
 *  Created on: Sep 16, 2015
 *      Author: stud
 */

#ifndef ATINDEX_H_
#define ATINDEX_H_

#include "Typelist.h"
#include "IsSame.h"



template<class TL, int idx>
struct AtIndex {
	typedef typename AtIndex<typename TL::Rest, idx-1>::Type Type;
};

template<typename TL>
struct AtIndex<TL, 0> {
	typedef typename TL::First Type;
};

#endif /* ATINDEX_H_ */
