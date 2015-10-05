#include "eventJoin.h"
#include <string>


EventJoin::EventJoin(std::string user, std::string room)
{
    userName_ = user;
    targetRoom_ = room;
}

EventJoin::~EventJoin()
{
    
}