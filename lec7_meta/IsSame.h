/*
 * IsSame.h
 *
 *  Created on: Sep 16, 2015
 *      Author: stud
 */

#ifndef ISSAME_H_
#define ISSAME_H_

template<typename T1, typename T2>
struct IsSame {
	enum { value = 0 };
};

template<typename T>
struct IsSame<T, T> {
	enum { value = 1 };
};


#endif /* ISSAME_H_ */
