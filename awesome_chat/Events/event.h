#ifndef _EVENT_LOCK_INCLUDE
#error Events must be added in the Events.h file, include this instead.
#else

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

namespace mpl = boost::mpl;

// A type map. Implem #N of type Key is type (default: void)

template <int N>
struct Implem
{
  public:
    typedef void type;
};

// Type vector building functions
// void, the default type, is used to stop the recursion

template <int N = 1>
struct ImplemToList;

template <typename Item, int N>
struct ImplemListItem
{
  public:
    typedef typename mpl::push_front<typename ImplemToList<N + 1>::type, Item>::type type;
};

template <int N>
struct ImplemToList
{
  public:
    typedef typename Implem<N>::type item;
    typedef typename mpl::eval_if<boost::is_same<item, void>, mpl::identity<mpl::vector<> >,ImplemListItem<item, N> >::type type;
};


struct StartCount
{
	enum { value = __COUNTER__};
};

#define MK_EVENT(Implem2) \
class Implem2;\
\
template <>\
struct Implem< __COUNTER__ - StartCount::value>\
{\
  public:\
    typedef Implem2 type;\
};\
\
class Implem2




#endif


#endif
