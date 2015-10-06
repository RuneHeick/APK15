#ifndef EVENTS_EVENTCOUNT_H_
#define EVENTS_EVENTCOUNT_H_
#include <boost/mpl/vector.hpp>

template < typename Begin, typename Target,typename End, int ID, typename currenttype >
struct Count_event
{
	typedef typename Begin::type currentType;
	enum{value = Count_event<typename boost::mpl::next< Begin >::type,Target,End, ID+1,currentType>::value };
};

template <typename Begin, typename Target,typename End, int ID>
struct Count_event<Begin, Target, End, ID, Target >
{
	enum{value = ID};
};

template < typename Sequence, typename Target>
struct Event_ID
{
    typedef typename boost::mpl::begin< Sequence >::type begin;
    typedef typename boost::mpl::end< Sequence >::type   end;

    typedef typename Sequence::type currentType;

    enum{ value = Count_event<begin,Target,end, 0, currentType>::value };
};



#endif /* EVENTS_EVENTCOUNT_H_ */
