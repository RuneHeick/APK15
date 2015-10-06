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
    typedef typename mpl::push_front<typename ImplemToList<Key, N + 1>::type, Item>::type type;
};

template <typename Key, int N>
struct ImplemToList
{
  public:
    typedef typename Implem<Key, N>::type item;
    typedef typename mpl::eval_if<boost::is_same<item, void>, mpl::identity<mpl::vector<> >,ImplemListItem<Key, item, N> >::type type;
};


class Interface
{
};

struct StartCount
{
	enum { value = __COUNTER__};
};

#define MK_EVENT(Implem2) \
class Implem2;\
\
template <>\
struct Implem<Interface, __COUNTER__ - StartCount::value>\
{\
  public:\
    typedef Implem2 type;\
};\
\
class Implem2




#endif


#endif
