/*
 * binary.h
 *
 *  Created on: Sep 14, 2015
 *      Author: stud
 */

#ifndef BINARY_H_
#define BINARY_H_

template <size_t N>
struct IsNotBinaryDigit;

template <>
struct IsNotBinaryDigit <1>
{
	static const size_t value = 1;
};

template <>
struct IsNotBinaryDigit <0>
{
	static const size_t value = 0;
};

template <size_t N>
struct Binary
{
	static const size_t value = Binary<N/10>::value << 1 | IsNotBinaryDigit<N%10>::value;
};

template <>
struct Binary <0>
{
	static const size_t value = 0;
};

#endif /* BINARY_H_ */
