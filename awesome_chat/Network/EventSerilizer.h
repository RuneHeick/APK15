
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
#include <iostream>
#include "../event.h"

template<typename T>
struct EventCreatorBase
{
	virtual std::shared_ptr<RawPacket> ToByte(T item) = 0;
	virtual T FromByte(uint8_t* packet, std::size_t size) = 0;
};

template<typename T, typename TVariant>
class EventCreator: public EventCreatorBase<TVariant>
{

	std::shared_ptr<RawPacket> ToByte(TVariant item)
	{
		T event = boost::get<T>(item);
		return T::ToByte(event);
	}

	TVariant FromByte(uint8_t* packet, std::size_t size)
	{
		T item = T::FromByte(packet, size);
		return TVariant(item);
	}

};

template<typename VariantType>
struct value_printer
{
	std::vector< EventCreatorBase<VariantType> * > * serilizers;

	value_printer(std::vector< EventCreatorBase<VariantType> * >* v): serilizers(v)
	{

	}

    template< typename U > void operator()(U x)
    {
    	auto ptr =  new EventCreator<U, VariantType>();
    	serilizers->push_back(ptr);
    }
};

struct interfaceVisitor : boost::static_visitor<Interface*>
{
	template<typename T>
	Interface* operator()(T& i) const
	{
	        return &i;
	}
};

template<typename TList>
class EventSerilizer
{
public:
	typedef typename boost::make_variant_over<TList>::type VariantType;

	EventSerilizer()
	{
		boost::mpl::for_each<TList>( value_printer< VariantType>(&serilizers));
	}

	std::shared_ptr<RawPacket> serilize(VariantType event)
	{
		 Interface* baseEvent = boost::apply_visitor(interfaceVisitor(), event); // works!
		 EventCreatorBase<VariantType> * serilizer = serilizers[baseEvent->ID-1];

		 std::shared_ptr<RawPacket> EventPacket = serilizer->ToByte(event);
		 std::shared_ptr<RawPacket> NewPacket = std::shared_ptr<RawPacket>(new RawPacket(EventPacket->Size()+1));
		 memcpy(&NewPacket->Packet()[1],EventPacket->Packet(), EventPacket->Size());
		 NewPacket->Packet()[0] = baseEvent->ID;
		 return NewPacket;
	}

	VariantType deserilize(std::shared_ptr<RawPacket>  packet)
	{
		auto i = packet->Packet()[0];
		EventCreatorBase<VariantType> * serilizer = serilizers[i-1];
		return serilizer->FromByte(&packet->Packet()[1],packet->Size()-1);
	}

private:
	std::vector< EventCreatorBase<VariantType> * > serilizers;

};







#endif
