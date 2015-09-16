
#ifndef TYPELIST_H_
#define TYPELIST_H_

struct NullType {};

template <typename L, typename R>
struct TypeList
{
	typedef L First;
	typedef R Rest;
};


#define TYPELIST1(T) TypeList<T, NullType>
#define TYPELIST2(T1, T2) TypeList<T1, TypeList<T2, NullType> >
#define TYPELIST3(T1, T2, T3) TypeList<T1, TypeList<T2, TypeList<T3, NullType> > >
#define TYPELIST4(T1, T2, T3, T4) TypeList<T1, TypeList<T2, TypeList<T3, TypeList< T4, NullType> > > >

#endif // TYPELIST_H_
