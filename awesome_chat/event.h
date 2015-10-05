#ifndef EVENT_H_
#define EVENT_H_

#include <boost/mpl/vector.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/mpl/for_each.hpp>
#include <boost/mpl/push_front.hpp>
#include <boost/mpl/empty_sequence.hpp>
#include <boost/type_traits/is_same.hpp>
#include <stdint.h>
#include <stddef.h>
#include <memory>

using namespace boost::mpl;
using namespace boost;

// A type map. Implem #N of type Key is type (default: void)

template <typename Key, int N>
struct Implem
{
  public:
    typedef void type;
};

// Type vector building functions
// void, the default type, is used to stop the recursion

template <typename Key, int N = 1>
struct ImplemToList;

template <typename Key, typename Item, int N>
struct ImplemListItem
{
  public:
    typedef typename push_front<typename ImplemToList<Key, N + 1>::type, Item>::type type;
};

template <typename Key, int N>
struct ImplemToList
{
  public:
    typedef typename Implem<Key, N>::type item;
    typedef typename eval_if<is_same<item, void>,
                             identity<vector<> >,
                             ImplemListItem<Key, item, N> >::type type;
};


class Interface
{
	public:
		int ID = 0;
};

template<int i>
class IDSet : public Interface
{
  public:
	IDSet()
	{
		ID = i;
	}
};

struct StartCount
{
	enum { value = __COUNTER__};
};

template<typename T>
struct Holder
{
	enum{ID = 0};
};

#define MK_EVENT(Implem2) \
class Implem2;\
\
template<>\
struct Holder< Implem2 >\
{\
	enum{ID = __COUNTER__ - StartCount::value};\
	\
};\
\
template <>\
struct Implem<Interface, Holder< Implem2 >::ID>\
{\
  public:\
    typedef Implem2 type;\
};\
\
class Implem2 : public IDSet<Holder< Implem2 >::ID>







#endif
