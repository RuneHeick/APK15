
#ifndef EVENTSERILIZER_H_
#define EVENTSERILIZER_H_

#include <boost/mpl/vector.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/mpl/for_each.hpp>
#include <boost/mpl/push_front.hpp>
#include <boost/mpl/at.hpp>
#include <boost/mpl/empty_sequence.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/variant.hpp>
#include <boost/variant/apply_visitor.hpp>
#include "EventCount.h"
#include "EventDeserilizer.h"


struct SerilizeVisitor : boost::static_visitor< std::shared_ptr<RawPacket> >
{
	template<typename T>
	std::shared_ptr<RawPacket> operator()(T& event) const
	{
		std::shared_ptr<RawPacket> EventPacket = T::ToByte(event);
		std::shared_ptr<RawPacket> NewPacket = std::shared_ptr<RawPacket>(new RawPacket(EventPacket->Size()+1));
	    memcpy(&NewPacket->Packet()[1],EventPacket->Packet(), EventPacket->Size());
	    NewPacket->Packet()[0] = (char)Event_ID<IList, T>::value;
	    return NewPacket;
	}
};


class EventSerilizer
{
public:

	std::shared_ptr<RawPacket> serilize(EventVariant event)
	{
		return boost::apply_visitor( SerilizeVisitor(), event );
	}

	EventVariant deserilize(std::shared_ptr<RawPacket>  packet)
	{
		return Event_Deserilize::deserilize(packet);
	}

};







#endif
