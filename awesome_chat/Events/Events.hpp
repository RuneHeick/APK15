/*
 * Events.hpp
 *
 *  Created on: Oct 5, 2015
 *      Author: stud
 */

#ifndef EVENTS_EVENTS_HPP_
#define EVENTS_EVENTS_HPP_
#include <boost/variant/variant.hpp>
#include "event.h"

#include "eventJoin.h"
#include "eventMsg.h"
#include "eventWho.h"



// After All Events
typedef ImplemToList<Interface>::type IList;
typedef boost::make_variant_over<IList>::type EventVariant;


#endif /* EVENTS_EVENTS_HPP_ */
