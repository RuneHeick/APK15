/*
 * Events.hpp
 *
 *  Created on: Oct 5, 2015
 *      Author: stud
 */

#ifndef EVENTS_EVENTS_HPP_
#define EVENTS_EVENTS_HPP_
#define _EVENT_LOCK_INCLUDE 1
#include <boost/variant/variant.hpp>
#include "event.h"

//------ ALL EVENTS MUST BE INCLUDED HERE---------------
#include "eventJoin.h"
#include "eventMsg.h"
#include "eventWho.h"

//------------------------------------------------------

// After All Events
typedef ImplemToList<1>::type IList;
typedef boost::make_variant_over<IList>::type EventVariant;
#include "EventSerilizer.h"
#undef _EVENT_LOCK_INCLUDE
#undef MK_EVENT
#endif /* EVENTS_EVENTS_HPP_ */
