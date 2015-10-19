#ifndef EVENTS_EVENTDESERILIZER_H_
#define EVENTS_EVENTDESERILIZER_H_
#include <boost/mpl/vector.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/asio.hpp>

template < typename Begin, typename End, int ID >
struct MetaDeserilizer
{
	typedef typename Begin::type currentType;
	static EventVariant deserilize(std::shared_ptr<RawPacket>  packet)
	{
		if((*packet)[0] == ID)
		{
			EventVariant var = currentType::FromByte(&(*packet)[1], packet->size()-1);
			return var;
		}
		else
		{
			return MetaDeserilizer<typename boost::mpl::next< Begin >::type, End, ID+1>::deserilize(packet);
		}
	}
};


template <typename End, int ID>
struct MetaDeserilizer<End, End, ID >
{
	static EventVariant deserilize(std::shared_ptr<RawPacket>  packet)
	{
		throw boost::system::system_error(boost::asio::error::no_protocol_option);
	}
};


struct Event_Deserilize
{
    typedef typename boost::mpl::begin< IList >::type begin;
    typedef typename boost::mpl::end< IList >::type   end;

    static EventVariant deserilize(std::shared_ptr<RawPacket>  packet)
    {
    	return MetaDeserilizer<begin, end, 1>::deserilize(packet);
    }
};



#endif /* EVENTS_EVENTCOUNT_H_ */
